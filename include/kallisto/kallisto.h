#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace kallisto {

struct SecretEntry {
    std::string key;
    std::string value;
    std::string path;
    std::chrono::system_clock::time_point created_at;
    uint32_t ttl; // in seconds
};

class KallistoServer {
public:
    KallistoServer();
    ~KallistoServer();
    // Yêu cầu: các hàm tương tác dữ liệu cần đẩy hẳn đi theo tính đóng gói,
    // TL;DR: gói đủ dữ liệu xong mới chuyển đi xuống storage hoặc trả kết quả
    bool put_secret(const std::string& path, const std::string& key, const std::string& value);
    std::string get_secret(const std::string& path, const std::string& key);
    bool delete_secret(const std::string& path, const std::string& key);

private:
    // Components will be added here
};

} // namespace kallisto
