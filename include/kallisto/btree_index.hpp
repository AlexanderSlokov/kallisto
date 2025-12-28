#pragma once

#include <string>
#include <vector>
#include <memory>

namespace kallisto {

class BTreeIndex {
public:
    BTreeIndex();
    // Thêm path vào btree index
    bool insert_path(const std::string& path);
    // Kiểm tra path có tồn tại trong btree index không
    bool validate_path(const std::string& path) const;

private:
    struct Node {
        // Phải đánh dấu chỉ mục path ở thư mục cuối cùng (lá ở cuối cành),
        // vì có thể gặp tấn công path traversal.
        bool is_leaf;
        // Keys, children? là cái gì nữa?
        std::vector<std::string> keys;
        std::vector<std::unique_ptr<Node>> children;

        Node(bool leaf = true) : is_leaf(leaf) {}
    };

    std::unique_ptr<Node> root;
    // WTF is "t" bro? Đặt tên biến cho tường minh giùm.
    int t; // Minimum degree
};

} // namespace kallisto
