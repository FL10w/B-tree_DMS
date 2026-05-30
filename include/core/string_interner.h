#pragma once

#include <memory>
#include <string>
#include <vector>

namespace app {

class StringInterner {
public:
    static StringInterner& instance();

    std::shared_ptr<const std::string> intern(const std::string& value);
    size_t uniqueCount() const;
    size_t requestCount() const;

private:
    StringInterner();

    std::vector<std::shared_ptr<const std::string>> values_;
    size_t requests_ = 0;
};

}  // namespace app
