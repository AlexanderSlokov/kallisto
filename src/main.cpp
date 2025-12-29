#include <iostream>
#include "kallisto/kallisto.hpp"
#include "kallisto/logger.hpp"

int main() {
    // 1. Setup Logger
    kallisto::LogConfig config("kallisto.server.log");
    config.logFilePath = "logs/";
    config.name = "Kallisto";
    config.logLevel = "debug";
    
    try {
        kallisto::Logger::getInstance().setup(config);
        
        kallisto::info("===============");
        kallisto::info("   KALLISTO    ");
        kallisto::info("===============");
        
        kallisto::KallistoServer server;
        kallisto::info("Initializing subsystems: [SipHash] [CuckooTable] [B-Tree]...");
        // Thiếu bước validate
        // Nếu đã dev validate, chèn log debug để debug sâu vào tiến trình khởi tạo
        
        // 1. Path: /prod/payment, Key: db_pass
        std::string path = "/prod/payment";
        std::string key = "db_pass";
        std::string secret = "SuperSecretPassword123";

        kallisto::info("Scenario: Storing secret in production...");
        if (server.put_secret(path, key, secret)) {
            kallisto::info("Successfully stored secret.");
        }

        kallisto::info("------------------------------------------");
        
        // 2. Retrieval Demo
        kallisto::info("Scenario: Client 'Kaellir' requesting secret...");
        std::string result = server.get_secret(path, key);
        
        if (!result.empty()) {
            kallisto::info("RESULT: 200 OK - Value: " + result);
        } else {
            kallisto::error("RESULT: 404 NOT FOUND");
        }

        kallisto::info("------------------------------------------");

        // 3. Invalid Path Demo
        kallisto::info("Scenario: Requesting secret from invalid path...");
        server.get_secret("/dev/hack", "root_pass");
        
    } catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
