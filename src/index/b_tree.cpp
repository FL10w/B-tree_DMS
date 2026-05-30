#include "index/b_tree.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {

template <typename Key>
json keyToJson(const Key& key) {
    return key;
}

template <typename Key>
Key keyFromJson(const json& data) {
    return data.get<Key>();
}

}  // namespace

template <typename Key>
BTree<Key>::BTree(fs::path manifestPath, std::string keyType, int minDegree, bool reset)
    : manifestPath_(std::move(manifestPath)),
      pagesDir_(pagesPathFor(manifestPath_)),
      keyType_(std::move(keyType)),
      minDegree_(minDegree) {
    if (minDegree_ < 2) {
        throw std::runtime_error("B-tree min degree must be at least 2");
    }
    if (reset || !fs::exists(manifestPath_)) {
        initializeEmpty(reset);
    } else {
        loadMetadata();
    }
}

template <typename Key>
fs::path BTree<Key>::pagesPathFor(const fs::path& manifestPath) {
    return manifestPath.parent_path() / (manifestPath.stem().string() + ".pages");
}

template <typename Key>
bool BTree<Key>::insert(const Key& key, long long rowId) {
    if (find(key).has_value()) {
        return false;
    }

    Node root = readNode(rootPage_);
    if (root.keys.size() == static_cast<size_t>(2 * minDegree_ - 1)) {
        Node newRoot;
        newRoot.id = allocatePageId();
        newRoot.leaf = false;
        newRoot.children.push_back(rootPage_);
        writeNode(newRoot);
        rootPage_ = newRoot.id;
        saveMetadata();
        splitChild(newRoot, 0);
        root = readNode(rootPage_);
    }

    insertNonFull(root, key, rowId);
    return true;
}

template <typename Key>
bool BTree<Key>::remove(const Key& key) {
    if (!find(key).has_value()) {
        return false;
    }

    const bool removed = remove(rootPage_, key);
    Node root = readNode(rootPage_);
    if (!root.leaf && root.keys.empty()) {
        const long long oldRootPage = rootPage_;
        rootPage_ = root.children.front();
        saveMetadata();
        fs::remove(pagePath(oldRootPage));
    }
    return removed;
}

template <typename Key>
std::optional<long long> BTree<Key>::find(const Key& key) const {
    return find(rootPage_, key);
}

template <typename Key>
std::vector<std::pair<Key, long long>> BTree<Key>::inOrder() const {
    std::vector<std::pair<Key, long long>> result;
    collect(rootPage_, result);
    return result;
}

template <typename Key>
std::vector<long long> BTree<Key>::range(const std::optional<Key>& low,
                                         const std::optional<Key>& high,
                                         bool includeLow,
                                         bool includeHigh) const {
    std::vector<long long> result;
    collectRange(rootPage_, low, high, includeLow, includeHigh, result);
    return result;
}

template <typename Key>
bool BTree<Key>::lessThan(const Key& left, const Key& right) {
    return left < right;
}

template <typename Key>
bool BTree<Key>::equalTo(const Key& left, const Key& right) {
    return !(left < right) && !(right < left);
}

template <typename Key>
void BTree<Key>::initializeEmpty(bool reset) {
    if (reset) {
        if (fs::exists(manifestPath_)) {
            fs::remove(manifestPath_);
        }
        if (fs::exists(pagesDir_)) {
            fs::remove_all(pagesDir_);
        }
    }

    fs::create_directories(manifestPath_.parent_path());
    fs::create_directories(pagesDir_);
    rootPage_ = 1;
    nextPage_ = 2;

    Node root;
    root.id = rootPage_;
    root.leaf = true;
    writeNode(root);
    saveMetadata();
}

template <typename Key>
void BTree<Key>::loadMetadata() {
    std::ifstream in(manifestPath_, std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot read index manifest: " + manifestPath_.string());
    }

    json data;
    in >> data;
    const std::string format = data.value("format", "");
    if (format != "disk-btree-index-v1") {
        throw std::runtime_error("unsupported index format: " + manifestPath_.string());
    }
    const std::string storedType = data.value("key_type", "");
    if (storedType != keyType_) {
        throw std::runtime_error("index key type mismatch: " + manifestPath_.string());
    }

    minDegree_ = data.at("min_degree").get<int>();
    rootPage_ = data.at("root_page").get<long long>();
    nextPage_ = data.at("next_page").get<long long>();
    fs::create_directories(pagesDir_);
}

template <typename Key>
void BTree<Key>::saveMetadata() const {
    fs::create_directories(manifestPath_.parent_path());
    json data;
    data["format"] = "disk-btree-index-v1";
    data["key_type"] = keyType_;
    data["min_degree"] = minDegree_;
    data["root_page"] = rootPage_;
    data["next_page"] = nextPage_;
    data["pages_dir"] = pagesDir_.filename().string();

    std::ofstream out(manifestPath_, std::ios::binary);
    if (!out) {
        throw std::runtime_error("cannot write index manifest: " + manifestPath_.string());
    }
    out << data.dump(2);
}

template <typename Key>
fs::path BTree<Key>::pagePath(long long pageId) const {
    return pagesDir_ / ("page_" + std::to_string(pageId) + ".json");
}

template <typename Key>
typename BTree<Key>::Node BTree<Key>::readNode(long long pageId) const {
    std::ifstream in(pagePath(pageId), std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot read B-tree page: " + pagePath(pageId).string());
    }

    json data;
    in >> data;

    Node node;
    node.id = data.at("id").get<long long>();
    node.leaf = data.at("leaf").get<bool>();
    for (const auto& item : data.value("keys", json::array())) {
        node.keys.push_back(keyFromJson<Key>(item));
    }
    for (const auto& item : data.value("rows", json::array())) {
        node.rows.push_back(item.get<long long>());
    }
    for (const auto& item : data.value("children", json::array())) {
        node.children.push_back(item.get<long long>());
    }
    return node;
}

template <typename Key>
void BTree<Key>::writeNode(const Node& node) const {
    fs::create_directories(pagesDir_);

    json data;
    data["id"] = node.id;
    data["leaf"] = node.leaf;
    data["keys"] = json::array();
    data["rows"] = json::array();
    data["children"] = json::array();

    for (const auto& key : node.keys) {
        data["keys"].push_back(keyToJson(key));
    }
    for (const auto rowId : node.rows) {
        data["rows"].push_back(rowId);
    }
    for (const auto childId : node.children) {
        data["children"].push_back(childId);
    }

    std::ofstream out(pagePath(node.id), std::ios::binary);
    if (!out) {
        throw std::runtime_error("cannot write B-tree page: " + pagePath(node.id).string());
    }
    out << data.dump(2);
}

template <typename Key>
long long BTree<Key>::allocatePageId() {
    const long long pageId = nextPage_++;
    saveMetadata();
    return pageId;
}

template <typename Key>
std::optional<long long> BTree<Key>::find(long long pageId, const Key& key) const {
    const Node node = readNode(pageId);
    const auto it = std::lower_bound(node.keys.begin(), node.keys.end(), key, [](const Key& left, const Key& right) {
        return lessThan(left, right);
    });
    const auto i = static_cast<size_t>(it - node.keys.begin());
    if (i < node.keys.size() && equalTo(node.keys[i], key)) {
        return node.rows[i];
    }
    if (node.leaf) {
        return std::nullopt;
    }
    return find(node.children[i], key);
}

template <typename Key>
void BTree<Key>::splitChild(Node& parent, size_t childIndex) {
    Node child = readNode(parent.children[childIndex]);
    Node right;
    right.id = allocatePageId();
    right.leaf = child.leaf;

    const Key middleKey = child.keys[static_cast<size_t>(minDegree_ - 1)];
    const long long middleRow = child.rows[static_cast<size_t>(minDegree_ - 1)];

    for (int i = 0; i < minDegree_ - 1; ++i) {
        right.keys.push_back(child.keys[static_cast<size_t>(i + minDegree_)]);
        right.rows.push_back(child.rows[static_cast<size_t>(i + minDegree_)]);
    }
    if (!child.leaf) {
        for (int i = 0; i < minDegree_; ++i) {
            right.children.push_back(child.children[static_cast<size_t>(i + minDegree_)]);
        }
    }

    child.keys.resize(static_cast<size_t>(minDegree_ - 1));
    child.rows.resize(static_cast<size_t>(minDegree_ - 1));
    if (!child.leaf) {
        child.children.resize(static_cast<size_t>(minDegree_));
    }

    parent.keys.insert(parent.keys.begin() + static_cast<long long>(childIndex), middleKey);
    parent.rows.insert(parent.rows.begin() + static_cast<long long>(childIndex), middleRow);
    parent.children.insert(parent.children.begin() + static_cast<long long>(childIndex + 1), right.id);

    writeNode(child);
    writeNode(right);
    writeNode(parent);
}

template <typename Key>
void BTree<Key>::insertNonFull(Node node, const Key& key, long long rowId) {
    if (node.leaf) {
        const auto it = std::lower_bound(node.keys.begin(), node.keys.end(), key, [](const Key& left, const Key& right) {
            return lessThan(left, right);
        });
        const auto i = static_cast<size_t>(it - node.keys.begin());
        node.keys.insert(node.keys.begin() + static_cast<long long>(i), key);
        node.rows.insert(node.rows.begin() + static_cast<long long>(i), rowId);
        writeNode(node);
        return;
    }

    const auto it = std::lower_bound(node.keys.begin(), node.keys.end(), key, [](const Key& left, const Key& right) {
        return lessThan(left, right);
    });
    auto i = static_cast<size_t>(it - node.keys.begin());

    Node child = readNode(node.children[i]);
    if (child.keys.size() == static_cast<size_t>(2 * minDegree_ - 1)) {
        splitChild(node, i);
        if (lessThan(node.keys[i], key)) {
            ++i;
        }
    }
    insertNonFull(readNode(node.children[i]), key, rowId);
}

template <typename Key>
bool BTree<Key>::remove(long long pageId, const Key& key) {
    Node node = readNode(pageId);
    const auto it = std::lower_bound(node.keys.begin(), node.keys.end(), key, [](const Key& left, const Key& right) {
        return lessThan(left, right);
    });
    auto index = static_cast<size_t>(it - node.keys.begin());

    if (index < node.keys.size() && equalTo(node.keys[index], key)) {
        if (node.leaf) {
            node.keys.erase(node.keys.begin() + static_cast<long long>(index));
            node.rows.erase(node.rows.begin() + static_cast<long long>(index));
            writeNode(node);
            return true;
        }
        removeFromInternal(node, index);
        return true;
    }

    if (node.leaf) {
        return false;
    }

    const bool wasLastChild = index == node.keys.size();
    Node child = readNode(node.children[index]);
    if (child.keys.size() < static_cast<size_t>(minDegree_)) {
        fillChild(node, index);
        node = readNode(pageId);
        if (wasLastChild && index > node.keys.size()) {
            --index;
        }
    }
    return remove(node.children[index], key);
}

template <typename Key>
void BTree<Key>::removeFromInternal(Node& node, size_t index) {
    const Key key = node.keys[index];
    const long long leftPage = node.children[index];
    const long long rightPage = node.children[index + 1];
    const Node left = readNode(leftPage);
    const Node right = readNode(rightPage);

    if (left.keys.size() >= static_cast<size_t>(minDegree_)) {
        const auto replacement = predecessor(leftPage);
        node.keys[index] = replacement.first;
        node.rows[index] = replacement.second;
        writeNode(node);
        remove(leftPage, replacement.first);
        return;
    }

    if (right.keys.size() >= static_cast<size_t>(minDegree_)) {
        const auto replacement = successor(rightPage);
        node.keys[index] = replacement.first;
        node.rows[index] = replacement.second;
        writeNode(node);
        remove(rightPage, replacement.first);
        return;
    }

    mergeChildren(node, index);
    remove(leftPage, key);
}

template <typename Key>
std::pair<Key, long long> BTree<Key>::predecessor(long long pageId) const {
    Node current = readNode(pageId);
    while (!current.leaf) {
        current = readNode(current.children.back());
    }
    return {current.keys.back(), current.rows.back()};
}

template <typename Key>
std::pair<Key, long long> BTree<Key>::successor(long long pageId) const {
    Node current = readNode(pageId);
    while (!current.leaf) {
        current = readNode(current.children.front());
    }
    return {current.keys.front(), current.rows.front()};
}

template <typename Key>
void BTree<Key>::fillChild(Node& node, size_t childIndex) {
    if (childIndex > 0) {
        const Node previous = readNode(node.children[childIndex - 1]);
        if (previous.keys.size() >= static_cast<size_t>(minDegree_)) {
            borrowFromPrevious(node, childIndex);
            return;
        }
    }

    if (childIndex < node.keys.size()) {
        const Node next = readNode(node.children[childIndex + 1]);
        if (next.keys.size() >= static_cast<size_t>(minDegree_)) {
            borrowFromNext(node, childIndex);
            return;
        }
        mergeChildren(node, childIndex);
        return;
    }

    mergeChildren(node, childIndex - 1);
}

template <typename Key>
void BTree<Key>::borrowFromPrevious(Node& node, size_t childIndex) {
    Node child = readNode(node.children[childIndex]);
    Node sibling = readNode(node.children[childIndex - 1]);

    child.keys.insert(child.keys.begin(), node.keys[childIndex - 1]);
    child.rows.insert(child.rows.begin(), node.rows[childIndex - 1]);
    if (!child.leaf) {
        child.children.insert(child.children.begin(), sibling.children.back());
        sibling.children.pop_back();
    }

    node.keys[childIndex - 1] = sibling.keys.back();
    node.rows[childIndex - 1] = sibling.rows.back();
    sibling.keys.pop_back();
    sibling.rows.pop_back();

    writeNode(sibling);
    writeNode(child);
    writeNode(node);
}

template <typename Key>
void BTree<Key>::borrowFromNext(Node& node, size_t childIndex) {
    Node child = readNode(node.children[childIndex]);
    Node sibling = readNode(node.children[childIndex + 1]);

    child.keys.push_back(node.keys[childIndex]);
    child.rows.push_back(node.rows[childIndex]);
    if (!child.leaf) {
        child.children.push_back(sibling.children.front());
        sibling.children.erase(sibling.children.begin());
    }

    node.keys[childIndex] = sibling.keys.front();
    node.rows[childIndex] = sibling.rows.front();
    sibling.keys.erase(sibling.keys.begin());
    sibling.rows.erase(sibling.rows.begin());

    writeNode(sibling);
    writeNode(child);
    writeNode(node);
}

template <typename Key>
void BTree<Key>::mergeChildren(Node& node, size_t childIndex) {
    Node child = readNode(node.children[childIndex]);
    Node sibling = readNode(node.children[childIndex + 1]);

    child.keys.push_back(node.keys[childIndex]);
    child.rows.push_back(node.rows[childIndex]);
    child.keys.insert(child.keys.end(), sibling.keys.begin(), sibling.keys.end());
    child.rows.insert(child.rows.end(), sibling.rows.begin(), sibling.rows.end());
    if (!child.leaf) {
        child.children.insert(child.children.end(), sibling.children.begin(), sibling.children.end());
    }

    node.keys.erase(node.keys.begin() + static_cast<long long>(childIndex));
    node.rows.erase(node.rows.begin() + static_cast<long long>(childIndex));
    node.children.erase(node.children.begin() + static_cast<long long>(childIndex + 1));

    writeNode(child);
    writeNode(node);
    fs::remove(pagePath(sibling.id));
}

template <typename Key>
void BTree<Key>::collect(long long pageId, std::vector<std::pair<Key, long long>>& result) const {
    const Node node = readNode(pageId);
    for (size_t i = 0; i < node.keys.size(); ++i) {
        if (!node.leaf) {
            collect(node.children[i], result);
        }
        result.push_back({node.keys[i], node.rows[i]});
    }
    if (!node.leaf) {
        collect(node.children[node.keys.size()], result);
    }
}

template <typename Key>
bool BTree<Key>::keyInsideRange(const Key& key,
                                const std::optional<Key>& low,
                                const std::optional<Key>& high,
                                bool includeLow,
                                bool includeHigh) const {
    if (low.has_value()) {
        const bool below = includeLow ? lessThan(key, *low) : !lessThan(*low, key);
        if (below) {
            return false;
        }
    }
    if (high.has_value()) {
        const bool above = includeHigh ? lessThan(*high, key) : !lessThan(key, *high);
        if (above) {
            return false;
        }
    }
    return true;
}

template <typename Key>
void BTree<Key>::collectRange(long long pageId,
                              const std::optional<Key>& low,
                              const std::optional<Key>& high,
                              bool includeLow,
                              bool includeHigh,
                              std::vector<long long>& result) const {
    const Node node = readNode(pageId);
    for (size_t i = 0; i < node.keys.size(); ++i) {
        if (!node.leaf) {
            collectRange(node.children[i], low, high, includeLow, includeHigh, result);
        }
        if (keyInsideRange(node.keys[i], low, high, includeLow, includeHigh)) {
            result.push_back(node.rows[i]);
        }
    }
    if (!node.leaf) {
        collectRange(node.children[node.keys.size()], low, high, includeLow, includeHigh, result);
    }
}

template class BTree<long long>;
template class BTree<std::string>;
