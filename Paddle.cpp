#include "Paddle.h"



Paddle::Paddle(int X, int Y, int Color)
{
	originalX = X;
	originalY = Y;
	x = X;
	y = Y;
	color = Color;
}
Paddle::~Paddle()
{
}



int Paddle::Getx() {
	return x;
}
int Paddle::Gety() {
	return y;
}
int Paddle::GetColor() {
	return color;
}

void Paddle::Setx(int a) { // thay tọa độ x
	x = a;
}
void Paddle::Sety(int a) {// thay tọa độ y
	y = a;
}
void Paddle::Draw() {
	
	
		TextColor(color);
		for (int i = 0; i < MaxPaddle; i++) {// vẽ thanh trượt gồm 10 ô
			GotoXY(x + i, y);
			cout << static_cast <char>(219); 
		}
	
}
void Paddle::Delete() {
	for (int i = 0; i < MaxPaddle; i++) {// xóa thanh trượt gồm 10 ô
		GotoXY(x + i, y);
		TextColor(15);
		cout << " ";
	}
}
void Paddle::MoveRight() {
	int cnt = 0;
	do {
		cnt++; //biến hỗ trợ tăng tốc thanh trượt

		if (x + 10 < WidthGame) {
			GotoXY(x, y);
			TextColor(15);
			cout << " ";
			x++;
			GotoXY(x + 9, y);// di chuyển đến tọa độ mới
			TextColor(color);
			cout << static_cast<char>(219);// vẽ thanh trượt
		}
	} while (cnt < 4);// bước nhảy thanh trượt là 3
	
}
void Paddle::MoveLeft() {
	int cnt = 0;
	do {
		cnt++;
		if (x > 1) {
			GotoXY(x + 9, y);// tọa độ bên phải thanh trượt
			TextColor(15);
			cout << " ";
			x--;// thanh trượt qua trái
			GotoXY(x, y);// 
			TextColor(color);
			cout << static_cast<char>(219);// vẽ thanh trượt
		}
	} while (cnt < 4);// bước nhảy thanh trượt là 3
}
void Paddle::Reset() {
	x = originalX;
	y = originalY;
}
