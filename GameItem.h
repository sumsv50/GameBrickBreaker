#pragma once
#include"Graphics.h"
const int cong10 = 1, cong20 = 2, themmang = 3, taovatcan = 4,vatcan=5 ;
class GameItem
{
private:
	int x, y;// tọa độ của vật phẩm 
	int loai;// loại vật phẩm 
	int color; // màu vật phẩm
	int kitu; // hình dạng của vật phẩm : cout << static_cast <char>(kitu);
	int luot;// biến lượt đi về( dùng cho vật cản)
public:
	
	GameItem(int,int, int); // khởi tạo, tham số đầu vào là tọa độ x,y,loại
	~GameItem();
	int Getx(); // hàm lấy tọa độ x của vật phẩm
	int Gety(); // hàm lấy tọa độ y của vật phẩm
	int GetColor(); // hàm lấy màu của vật phẩm
	int GetLoai(); // hàm lấy loại của vật phẩm
	int Getkitu();// lấy kí tự
	void Setx(int); // thay tọa độ x
	void Sety(int);// thay tọa độ y
	void SetLoai(int);// thay loại
	void Draw(); // Hàm vẽ vật phẩm
	void Delete(); // hàm xóa vật phẩm
	void Move();// hàm di chuyển của vật phẩm

};

