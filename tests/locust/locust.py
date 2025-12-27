import random
from locust import HttpUser, task, between

# Giả lập tập dữ liệu mẫu để bắn
PATHS = ["prod/app/db", "dev/payment/stripe", "test/auth/jwt"]
KEYS = [f"secret_key_{i}" for i in range(1000)] # 1000 keys khác nhau

class KaellirAgent(HttpUser):
    # Thời gian nghỉ giữa các request (để giả lập user thật, hoặc set = 0 để DOS)
    wait_time = between(0.1, 0.5) 

    @task(1) # Trọng số 1: Ít khi ghi (Write)
    def write_secret(self):
        path = random.choice(PATHS)
        key = random.choice(KEYS)
        # Payload giả lập Vault
        payload = {
            "data": {
                "key": key,
                "value": "super_secret_value_" + str(random.randint(1, 9999))
            }
        }
        # POST /v1/secret/data/{path}
        self.client.post(f"/v1/secret/data/{path}", json=payload, name="Write Secret")

    @task(4) # Trọng số 4: Chủ yếu là đọc (Read) -> Kiểm chứng tốc độ Cuckoo/B-Tree
    def read_secret(self):
        path = random.choice(PATHS)
        key = random.choice(KEYS)
        
        # GET /v1/secret/data/{path}?key=...
        with self.client.get(
            f"/v1/secret/data/{path}?key={key}", 
            catch_response=True, 
            name="Read Secret"
        ) as response:
            # Kiểm tra xem Server có trả về JSON hợp lệ không
            if response.status_code == 200:
                response.success()
            elif response.status_code == 404:
                # 404 cũng là phản hồi hợp lệ (logic đúng), không phải lỗi server
                response.success()
            else:
                response.failure(f"Failed with status {response.status_code}")

# Chạy lệnh: locust -f locustfile.py --host=http://localhost:8080