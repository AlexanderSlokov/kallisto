#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include "kallisto/secret_entry.hpp"
#include "kallisto/cuckoo_table.hpp"
#include "kallisto/btree_index.hpp"
#include "kallisto/storage_engine.hpp"

namespace kallisto {

class KallistoServer {
public:
    KallistoServer();
    ~KallistoServer();

    /**
     * Stores a secret at a specific path.
     * 1. Validates path in B-Tree.
     * 2. Inserts/Updates entry in Cuckoo Table.
     */
    bool put_secret(const std::string& path, const std::string& key, const std::string& value);

    /**
     * Retrieves a secret.
     * 1. Validates path in B-Tree.
     * 2. O(1) Lookup in Cuckoo Table.
     */
    std::string get_secret(const std::string& path, const std::string& key);

    /**
     * Deletes a secret.
     */
    bool delete_secret(const std::string& path, const std::string& key);

private:
    std::unique_ptr<CuckooTable> storage;
    std::unique_ptr<BTreeIndex> path_index;
    std::unique_ptr<StorageEngine> persistence;

    std::string build_full_key(const std::string& path, const std::string& key) const;

    // Internal helper to rebuild B-Tree after loading from disk
    void rebuild_indices(const std::vector<SecretEntry>& secrets);
};

} // namespace kallisto
