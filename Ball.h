#pragma once
#include"Graphics.h"
#include"Paddle.h"
#include"Brick.h"
enum Direc { stop, up, upleft, upright, down, downleft, downright };// các hướng di chuyển của bóng
class Ball
{
protected:
	int x, y; //tọa độ bóng
	int originalX, originalY;// toạ độ ban đầu của bóng
	int color;
	Direc direc; // hướng
public:
	Ball();
	~Ball();
	Ball(int, int, int);
	int Getx();
	int Gety();
	void Setx(int); // thay tọa độ x
	void Sety(int);// thay tọa độ y
	Direc GetDirec();
	void SetDirec(Direc);
	void Draw(); // vẽ bóng trong gam tennis
	void Move(int); // hàm di chuyển bóng, tham số đầu vào là 1 hoặc 2. 1 là trong game tennis, 2 là game  brick breaker
	bool TouchPaddleTop(Paddle );// kiểm tra bóng có chạm thanh trượt 1 không?
	bool TouchPaddleDown(Paddle );// kiểm tra bóng có chạm thanh trượt 2 không?
	void Delete(int);// tham số đầu vào là 1 hoặc 2. 1: xóa bóng trong game tennis, nếu bóng đang ở vị trí lưới thì vẽ lại lưới, 2: xóa bóng trong game brick breaker, tức xóa mà không cần vẽ lại lưới
	void Reset();
	
};

