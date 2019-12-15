#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Graphics.h"
#include"BrickBreaker.h"
using namespace std;
struct taikhoan { // tạo struct gồm tên và điểm
	string ten;
	int diem;
};
void XuatBangThanhTich() { // xuất bảng tahnfh tích điểm
	vector<taikhoan> bangdiem; // vector bảng điểm
	ifstream filein;
	filein.open("BangDiem.text", ios::in); // mở file BangDiem.text
	
	while (filein.get() != EOF) { // ghi lại thông tin vào vector bangdiem
		filein.seekg(-1, 1);
		taikhoan tk;
		filein >> tk.diem;
		filein.seekg(1, 1); //tiến một byte, bỏ qua dấu :
		getline(filein, tk.ten, '\n');
		bangdiem.push_back(tk);
	}
	filein.close();
	for (int i = 0; i < bangdiem.size() - 1; i++) { // sắp xếp các tài khoản trong vector theo thứ tự giảm dần của điểm số
		for (int j = i + 1; j < bangdiem.size(); j++) // j chạy từ 0 đến số điểm trong bảng
			if (bangdiem[i].diem < bangdiem[j].diem) { // nếu điểm i bé hơn j thì hoán đổi vị trí
				taikhoan temp = bangdiem[i]; 
				bangdiem[i] = bangdiem[j];
				bangdiem[j] = temp;
			}

	}
	cout << "\t\t BRICKS BREAKER" << endl;
	cout << "\tXep hang\tScore\t   Player" << endl;
	for (int i = 0; i < bangdiem.size(); i++) {
		if (i < 3)
			TextColor(12); // in chữ màu đỏ cho 3 điểm số cao nhất
		else
			TextColor(15); // màu trắng còn lại
		cout <<"           "<< i + 1 << "\t\t" << bangdiem[i].diem << "\t" << bangdiem[i].ten<< endl;
	}
}



