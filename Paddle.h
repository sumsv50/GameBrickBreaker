#pragma once
#include"Graphics.h"
#define MaxPaddle 10
class Paddle
{
private:
	int x, y;//tọa độ thanh trượt
	int originalX, originalY;// tọa độ ban đầu của thanh trượt
	int color;//màu thanh trượt
public:
	Paddle(int, int,int);
	~Paddle();
	
	int Getx();
	int Gety();
	int GetColor();
	void Setx(int); // thay tọa độ x
	void Sety(int);// thay tọa độ y
    void Draw(); // Hàm vẽ thanh trượt
	void Delete(); // hàm xóa thanh trượt
	void MoveLeft(); // hàm di chuyển thanh trượt qua trái
	void MoveRight();// hàm di chuyển thanh trượt qua phải
	void Reset(); 

};

