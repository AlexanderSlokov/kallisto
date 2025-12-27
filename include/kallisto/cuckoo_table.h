#pragma once

#include <string>
#include <vector>
#include <optional>
// Thư viện lấy giá trị từ ENV
#include <cstdlib>
#include "kallisto.h"

namespace kallisto {

class CuckooTable {
public:
    // Cho phép declare size thông qua ENV var `KALLISTO_CUCKOO_TABLE_SIZE`
    CuckooTable(size_t size = std::stoi(getenv("KALLISTO_CUCKOO_TABLE_SIZE")));
    
    // Cuckoo table chỉ phục vụ 3 tác vụ chính:
    // - Insert: đưa một hash key vào entry
    // - Lookup: tìm kiếm entry theo hash key
    // - Remove: xóa entry
    bool insert(const std::string& key, const SecretEntry& entry);
    std::optional<SecretEntry> lookup(const std::string& key);
    bool remove(const std::string& key);

private:
    // Mỗi table sẽ có một cái bucket
    struct Bucket {
        bool occupied = false;
        std::string key;
        SecretEntry entry;
    };

    std::vector<Bucket> table_1;
    std::vector<Bucket> table_2;

    size_t capacity;

    size_t hash_1(const std::string& key) const;
    size_t hash_2(const std::string& key) const;
    
    void rehash();
};

} // namespace kallisto
