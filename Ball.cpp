#include "Ball.h"
#include<iostream>
using namespace std;

Ball::Ball()
{
	originalX = WidthGame / 2;
	originalY = HeightGame / 2;
	x = WidthGame/2;
	y = HeightGame/2;
	direc = stop;
	color = 14;//mau vang
}
Ball::Ball(int a, int b, int c) {
	originalX = a;
	x = originalX;
	originalY = b;
	y = originalY;
	color = c;
	direc = stop;
}
Ball::~Ball()
{
}
int Ball::Getx() {
	return x;
}
int Ball::Gety() {
	return y;
}
void Ball::Setx(int a) { // thay tọa độ x
	x = a;
}
void Ball::Sety(int a) {// thay tọa độ y
	y = a;
}
Direc Ball::GetDirec() {
	return direc;
}
void Ball::SetDirec(Direc dir) {
	direc = dir;
}
void Ball::Draw() {
	
	TextColor(color);
	GotoXY(x,y);
	cout << "O";
}
void Ball::Delete(int g) {
	GotoXY(x, y);
	if (g == 1) { // nếu game tennis
		if (y == HeightGame / 2) { // nếu bóng ở vị trí lưới 
			TextColor(15);
			cout << static_cast<char>(176);// vẽ lại lưới 
		}
		else cout << " ";
	}
	else
	cout << " ";

}

bool Ball::TouchPaddleTop(Paddle p1) {

	if (y == p1.Gety() + 1) {// xét tọa độ bóng và thanh 
		for (int i = 0; i < MaxPaddle; i++) {// i chạy từ 0 đến độ dài thanh là 10
			if (x == p1.Getx() + i)
				return true;
		}
	}
	return false;
}
bool Ball::TouchPaddleDown(Paddle p2) {

	if (y == p2.Gety() - 1) {
		for (int i = -1; i <= MaxPaddle; i++) {// i chạy từ -1 đến độ dài thanh là 10( tính luôn cái rìa của thanh)
			if (x == p2.Getx() + i)
				return true;
		}
	}
	return false;
}


void Ball::Move(int g) {
		if (direc == stop)
			return;
		if (direc == up) {
			if (y > 1) {
				Delete(g);
				y--;
				Draw();
			}
			return;
		}
		if (direc == upleft) {
			if (y > 1 && x > 1) {
				Delete(g);
				x--;
				y--;
				Draw();
			}

		}
		if (direc == upright) {
			if (y > 1 && x < WidthGame - 1) {
				Delete(g);
				x++;
				y--;
				Draw();
			}
			return;

		}
		if (direc == down) {
			if (y < HeightGame - 1) {
				Delete(g);
				y++;
				Draw();
			}
			return;
		}
		if (direc == downleft) {
			if (y < HeightGame - 1 && x>1) {
				Delete(g);
				x--;
				y++;
				Draw();
			}
		}
		if (direc == downright) {
			if (y < HeightGame - 1 && x < WidthGame - 1) {
				Delete(g);
				x++;
				y++;
				Draw();
			}
			return;
		}
	
}
void Ball::Reset() {
	x = originalX;
	y = originalY;
	direc = stop;
}
