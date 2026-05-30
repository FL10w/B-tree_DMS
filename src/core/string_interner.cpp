#include "core/string_interner.h"

#include <algorithm>

namespace app {

StringInterner::StringInterner() = default;

StringInterner& StringInterner::instance() {
    static StringInterner interner;
    return interner;
}

std::shared_ptr<const std::string> StringInterner::intern(const std::string& value) {
    ++requests_;
    const auto it = std::find_if(values_.begin(), values_.end(), [&value](const auto& stored) {
        return *stored == value;
    });
    if (it != values_.end()) {
        return *it;
    }
    auto stored = std::make_shared<const std::string>(value);
    values_.push_back(stored);
    return stored;
}

size_t StringInterner::uniqueCount() const {
    return values_.size();
}

size_t StringInterner::requestCount() const {
    return requests_;
}

}  // namespace app
