# IT3150 _ Đồ án 1 Khoa học máy tính 
(Chi tiết trong báo cáo)
## Phần 1:
### Bài 1: Cài đặt các thuật toán Sắp xếp
  - Sắp xếp Nổi bọt (Bubble sort).
  - Sắp xếp Lựa chọn (Selection sort).
  - Sắp xếp Vun đống (Heap sort).
  - Sắp xếp Nhanh (Quick sort).
  - Sắp xếp Trộn (Merge sort).
  
  Yêu cầu:
  - Input: Nhập từ màn hình; Đọc từ file; Sinh ngẫu nhiên.
  - Output: In ra màn hình; Xuất ra file.
  
### Bài 2: Giải một số bài toán
#### 2.1. Bài toán Mã đi tuần (Knight's tour)
  Thuật toán: Quay lui (Backtracking).
#### 2.2. Bài toán Người đi du lịch (Travelling salesman problem)
  Thuật toán:
  - Vét cạn (Brute force).
  - Quay lui có nhánh cận (Branch and Bound).
  
### Bài 3: Lập bảng chỉ mục
  Mô tả: Cho một file văn bản, yêu cầu in ra bảng chỉ mục gồm danh sách các từ khóa (không phải 'stop word' hay tên riêng), số lần xuất hiện từ đó và các dòng mà từ đó xuất hiện.
  
  Cấu trúc dữ liệu:
  - Danh sách liên kết (Linked List).
  - Mảng băm (Hash table) các danh sách liên kết.
  - Cây nhị phân tìm (Binary search tree).
  
  Yêu cầu:
  - Input: File văn bản, file lưu các 'stop words'.
  - Output: In ra màn hình mỗi dòng gồm: từ khóa, số lần xuất hiện, các dòng mà từ đó xuất hiện.

## Phần 2:
  Mô tả: Khi chương trình thực thi sẽ nhận đầu vào là camera, thuật toán sẽ đọc hình ảnh để nhận diện bàn tay và cử chỉ của bàn tay đó, xác định các thao tác vẽ. Sau khi vẽ xong, hình vẽ sẽ được đưa vào phân loại và cho kết quả là nhãn của hình vẽ.
  
  Công nghệ sử dụng: Python
  - OpenCV: Xử lý hình ảnh.
  - MediaPipe Hands: Nhận diện bàn tay.
  - Tensorflow Keras: Xây dựng model phân loại hình vẽ.
