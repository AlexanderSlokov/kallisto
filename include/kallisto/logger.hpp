#pragma once // Thay cho Include Guard truyền thống

#include <string>
#include <string_view>
#include <memory>
#include <stdexcept>

namespace kallisto {

enum class LogFormat {
    Unspecified = 0,
    Standard = 1,
    JSON = 2
};

struct LogConfig {
    std::string name;
    LogFormat format = LogFormat::Standard;
    std::string logFilePath;
    int logRotateDuration = 24 * 60 * 60; // 1 ngày
    int logRotateBytes = 12 * 1024 * 1024; // 12MB mặc định
    int logRotateMaxFiles = 5;
    std::string defaultFileName = "kallisto.log";
    // Constructor khởi tạo LogConfig nếu muốn dùng
    LogConfig(std::string_view fileName) {
        if (fileName.empty()) {
            throw std::invalid_argument("default file name is required");
        }
        defaultFileName = fileName;
    }
};
} // namespace kallisto