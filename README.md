🚗 2D RACING CAR: BÀI TẬP LỚN LẬP TRÌNH NÂNG CAO INT 2215

I.   Thông tin tác giả
  - Họ và tên: Nguyễn Quang Nhật Huy
  - MSV: 24021518
  - Lớp: K69I CS2

II. Các phần chính trong game
* Các thư viện được sử dụng: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf.
  1. Khởi tạo cửa sổ & vòng lặp game
    - Dùng SDL2 để tạo cửa sổ game, renderer
    - Game.cpp xử lý:
      + Cập nhật vị trí các đối tượng
      + Kiểm tra va chạm
      + Render mọi thứ lên màn hình
      + Chuyển trạng thái (chơi, menu, game over)

  2. Nhân vật người chơi (Player)
    - Điều khiển bằng phím mũi tên
    - Có giới hạn biên (không đi ra ngoài màn hình)
    - Hàm update() xử lý di chuyển
    - Hàm getRect() dùng để kiểm tra va chạm

  3. Enemy
    - Xuất hiện ngẫu nhiên ở các làn
    - Di chuyển từ trên xuống
    - Khi va chạm → kết thúc game
    - Hàm resetPosition() đảm bảo enemy không đè nhau

  5. Menu & Giao diện
    - Màn hình menu và game over với các nút bấm (Button):
      + Play Again
      + Settings
      + Exit
    - Sử dụng SDL_Rect để vẽ vùng nút và xử lý sự kiện chuột.

  6. Âm thanh
    - Nhạc nền lặp lại khi chơi
    - Âm thanh khi va chạm
    - Tùy chọn mở/tắt âm thanh trong phần setting

III. Tài liệu tham khảo
  1. Tham khảo Code mẫu: Lazyfoo, file tài liệu của giảng viên, Youtube, Github của các anh khoá trước.
  2. Hình ảnh được lấy từ: OpenGameArt
  3. Âm thanh được lấy từ: PixaBay
