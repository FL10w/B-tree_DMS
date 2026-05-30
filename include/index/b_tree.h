#pragma once

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

template <typename Key>
class BTree {
public:
    BTree(fs::path manifestPath, std::string keyType, int minDegree = 3, bool reset = false);

    static fs::path pagesPathFor(const fs::path& manifestPath);

    bool insert(const Key& key, long long rowId);
    bool remove(const Key& key);
    std::optional<long long> find(const Key& key) const;
    std::vector<std::pair<Key, long long>> inOrder() const;
    std::vector<long long> range(const std::optional<Key>& low,
                                 const std::optional<Key>& high,
                                 bool includeLow,
                                 bool includeHigh) const;

private:
    struct Node {
        long long id = 0;
        bool leaf = true;
        std::vector<Key> keys;
        std::vector<long long> rows;
        std::vector<long long> children;
    };

    fs::path manifestPath_;
    fs::path pagesDir_;
    std::string keyType_;
    int minDegree_ = 3;
    long long rootPage_ = 1;
    long long nextPage_ = 2;

    static bool lessThan(const Key& left, const Key& right);
    static bool equalTo(const Key& left, const Key& right);

    void initializeEmpty(bool reset);
    void loadMetadata();
    void saveMetadata() const;
    fs::path pagePath(long long pageId) const;
    Node readNode(long long pageId) const;
    void writeNode(const Node& node) const;
    long long allocatePageId();

    std::optional<long long> find(long long pageId, const Key& key) const;
    void splitChild(Node& parent, size_t childIndex);
    void insertNonFull(Node node, const Key& key, long long rowId);
    bool remove(long long pageId, const Key& key);
    void removeFromInternal(Node& node, size_t index);
    std::pair<Key, long long> predecessor(long long pageId) const;
    std::pair<Key, long long> successor(long long pageId) const;
    void fillChild(Node& node, size_t childIndex);
    void borrowFromPrevious(Node& node, size_t childIndex);
    void borrowFromNext(Node& node, size_t childIndex);
    void mergeChildren(Node& node, size_t childIndex);
    void collect(long long pageId, std::vector<std::pair<Key, long long>>& result) const;
    bool keyInsideRange(const Key& key,
                        const std::optional<Key>& low,
                        const std::optional<Key>& high,
                        bool includeLow,
                        bool includeHigh) const;
    void collectRange(long long pageId,
                      const std::optional<Key>& low,
                      const std::optional<Key>& high,
                      bool includeLow,
                      bool includeHigh,
                      std::vector<long long>& result) const;
};
