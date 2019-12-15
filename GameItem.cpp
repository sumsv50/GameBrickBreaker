#include "GameItem.h"



GameItem::GameItem(int a,int b, int c) // hàm dựng, tham số đầu vào là tọa độ x,y, loại vật phẩm
{ 
	x = a;
	y = b;
	loai = c;
	if (loai == cong10) // cộng 10 đ
		color = 9; // loại 1 thì màu xanh dương
	if (loai == cong20)// cộng 20đ
		color = 10; // loại 2 thì màu xanh lá
	if (loai == themmang) // thêm mạng
		color = 12; // loại 3 thì màu đỏ
	kitu = 254; //hình vuông
	if (loai == taovatcan) { // tạo vật cản
		color = 12; // màu đỏ
		kitu = 88; // chữ X
	}
	if (loai == vatcan) {// vật cản
		color = 15;// trắng
		kitu = 254; // hình vuông
	}
	luot = 0;
	
}


GameItem::~GameItem()
{
}
int GameItem::Getx() { // hàm lấy tọa độ x của vật phẩm
	return x;
}
int GameItem::Gety() { // hàm lấy tọa độ y của vật phẩm
	return y;
}
int GameItem::GetColor() {// hàm lấy màu của vật phẩm
	return color;
}
int GameItem::Getkitu() {// lấy kí tự
	return kitu;
}
int GameItem::GetLoai() { // hàm lấy loại của vật phẩm
	return loai;
}
void GameItem::Setx(int a) { // thay tọa độ x
	x = a;
}
void GameItem::Sety(int a) {// thay tọa độ y
	y = a;
}
void GameItem::SetLoai(int a) {// thay loại
	loai = a;
}
void GameItem::Draw(){ // Hàm vẽ vật phẩm
	TextColor(color);
	GotoXY(x, y);
	if (loai == vatcan) { // nếu là vật cản
		for(int i=0;i<10;i++)// vật cản có độ dài 10
			cout << static_cast <char>(kitu);
	}
	else 
		cout << static_cast <char>(kitu);
}
void GameItem::Delete() { // hàm xóa vật phẩm
	GotoXY(x, y);
	if (loai == vatcan) { // nếu là vật cản
		for (int i = 0; i < 10; i++)// vật cản có độ dài 10
			cout << " ";
	}
	else
	cout << " ";
	
}
void GameItem::Move() {
	if (loai == vatcan) {// nếu là vật cản
		if (x + 9 < WidthGame - 1 && luot==0) { // nếu chưa chạm biên và đang là lượt đi
			Delete();// xóa thanh cũ
			x++; //tăng x
			Draw();// vẽ mới
		}
		else { // nếu chạm biên phải thì cho quay về
			luot = 1; // lượt về
			Delete();// xóa thanh cũ
			x--; //tăng x
			Draw();// vẽ mới
		}
		if(x==1)// nếu chạm biên phải thì xóa
			Delete();
	}
	else { // những vật phẩm khác thì cho rơi xuống
		if (y < HeightGame - 1) {
			Delete();
			y++;
			Draw();
		}
	}
}
