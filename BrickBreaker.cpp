#include "BrickBreaker.h"



BrickBreaker::BrickBreaker()
{
	player = new Paddle(WidthGame / 2 - 4, HeightGame - 1, 13);
	ball = new Ball(WidthGame / 2 + 1, HeightGame - 2, 14);
	ball->SetDirec(upright); //ban đầu cho bóng bay hướng đông bắc
	state = 1; // trạng thái sống
	speed = originalSpeed;
	score = 0;
	mang = omang;
	for (int xo = 2; xo < WidthGame - 2; xo += 6) { // vì mỗi viên gạch có chiều dài là 5 nên ta gán tọa độ x cho mỗi viên gạch cách nhau 6
		for (int yo = 2; yo <= 10; yo += 2)
			brick.push_back(new Brick(xo, yo));
	}
}




BrickBreaker::~BrickBreaker()
{
	delete ball;
	delete player;
	for (int i = 0; i < gItem.size(); i++) {
		delete gItem[i];
	}
	for (int i = 0; i < brick.size(); i++) {
		delete brick[i];
	}
}
int BrickBreaker::GetState() {// hàm lấy trạng thái sống chết của người chơi
	return state;
}
void BrickBreaker::SetState(int s) { // hàm thay đổi trạng thái sống chết của người chơi
	state = s;
}
void BrickBreaker::Draw() {
	player->Draw(); // vẽ thanh trượt
	ball->Draw(); // vẽ bóng
	for (int i = 0; i < brick.size(); i++)
		brick[i]->Draw(); // vẽ gạch
	DrawInfo(); // vẽ điểm, mạng

}
void BrickBreaker::DrawNewRound() { // hàm cập nhật số mạng hiện có
	TextColor(12);
	GotoXY(WidthGame + 3, HeightGame);
	cout << "                                                        ";// xóa cái cũ
	GotoXY(WidthGame + 3, HeightGame);
	cout << "Mang: "; // vẽ lại cái mới
	for (int i = mang; i > 0; i--) { // số mạng hiện có
		TextColor(14);
		cout << "o ";
	}
}
void BrickBreaker::DrawInfo() { // hàm ghi thông tin điểm số, mạng trong game
	TextColor(12);
	GotoXY(WidthGame + 3, HeightGame);
	cout << "Mang: ";
	for (int i = mang; i > 0; i--) {
		TextColor(14);
		cout << "o ";
	}
	TextColor(12);
	GotoXY(WidthGame + 3, HeightGame - 4); cout << "Score: " << score;
	GotoXY(WidthGame + 30, HeightGame - 4); cout << "Press ESC to EXIT";
	GotoXY(WidthGame + 30, HeightGame - 3); cout << "Press P to Pause";
	GotoXY(WidthGame + 30, HeightGame - 2); cout << "Press S to Save Game";

}
int BrickBreaker::GetSpeed() {
	return speed;
}
//bool BrickBreaker::Getquit() {
//	return quit;
//}
void BrickBreaker::SetBricks(vector<Brick*> b) { // hàm thay đổi mảng gạch
	brick = b;
}
void BrickBreaker::BallMove() {
	if (ball->GetDirec() == stop) {//nếu bóng đang đứng yên
		ball->SetDirec(up);// khởi tạo bóng bay theo hướng bắc
	}
	ball->Move(2);// cho bóng di chuyển.
}
void BrickBreaker::GItemMove() { // hàm cho vật phẩm di chuyển
	for (int i = 0; i < gItem.size(); i++) {
		gItem[i]->Move();
		if (gItem[i]->Gety() == HeightGame - 1) {// nếu vật phẩm chạm biên, thì xóa vật phẩm đó
			gItem[i]->Delete();
			gItem.erase(gItem.begin() + i);
		}
		else if (gItem[i]->GetLoai() == vatcan && gItem[i]->Getx() == 1) { // nếu là vật cản và chạm biên trái thì xóa vật cản
			gItem[i]->Delete();
			gItem.erase(gItem.begin() + i);
		}
	}
}
void BrickBreaker::Control() {

	if (_kbhit()) { // Kiểm tra người chơi có nhấn phìm nào không
		char key = _getch();

		if (key == 75) { // mũi tên qua trái
			player->MoveLeft();
			return;
		}
		if (key == 77) { // mũi tên qua phải
			player->MoveRight();
			return;
		}

		//phím esc dùng để thoát game
		if (key == 27) {
			state = 0; // chết, dừng thread
			return;
		}
		if (key == 'p' || key == 'P') {// phím p
			GotoXY(WidthGame + 3, 10);
			TextColor(12);
			cout << "Press any key to continue" << endl; // in ra dòng: nhấn bất kì phím nào để tiếp tục
			TextColor(15);
			while (1) {
				if (_kbhit()) { // Kiểm tra người chơi có nhấn phìm nào không, nếu có thì thoát vòng lặp, game tiếp tục chạy
					GotoXY(WidthGame + 3, 10);
					cout << "                                    " << endl; // xóa dòng chữ trên
					return;
				}
			}
		}
		if (key == 's' || key == 'S') {
			SaveGame();
			return;
		}
	}

}
void BrickBreaker::SaveScore() {// hàm lưu điểm
	GotoXY(WidthGame / 2 - 10, HeightGame / 2);
	cout << "Your score: " << score;// ghi ra điểm số
	GotoXY(WidthGame / 2 - 10, HeightGame / 2 + 1);
	cout << "Your Name: "; // yêu cầu nhập tên
	rewind(stdin);
	string name;
	getline(cin, name);
	ofstream f;
	f.open("BangDiem.text", ios::app); // mở file để ghi điểm
	f << score << ":" << name << endl; // <điểm>:< tên>
	f.close(); // đóng file
	system("cls");//Xóa màn hình
}

void BrickBreaker::Reset() {// Reset để bắt đầu hiệp đấu mới (Note: không phải để new game)
	player->Reset();// reset tanh trượt 1,2
	ball->Reset();// reset bóng
	speed = originalSpeed;// cho tốc độ bóng như ban đầu

}
void BrickBreaker::BallTouchItem() { // hàm xử lí bóng chạm vật cản
	for (int i = 0; i < gItem.size(); i++)  // i chạy từ 0 đến số vật phẩm có trong mảng vật phẩm
		if (gItem[i]->GetLoai() == vatcan)  // nếu là vật cản
			if (ball->Gety() == gItem[i]->Gety() - 1 || ball->Gety() == gItem[i]->Gety() + 1 || ball->Gety() == gItem[i]->Gety())// nếu tọa độ y của bóng bằng tọa độ các chiều của vật cản
				for (int j = -1; j <= 10; j++)  // độ dài vật cản, cả rìa
					if (ball->Getx() == gItem[i]->Getx() + j) {// nếu x bóng = x vật cản
						if (ball->GetDirec() == down) { // nếu bóng đang bay hướng nam
							ball->SetDirec(up); // cho bóng bay theo hướng bắc
							return;
						}
						if (ball->GetDirec() == downright) { // đông nam
							ball->SetDirec(upright); // đông bắc
							return;
						}
						if (ball->GetDirec() == downleft) { // tây anm
							ball->SetDirec(upleft); // tây bắc
							return;
						}
						if (ball->GetDirec() == up) { // trường hợp bóng đang bay hướng bắc
							ball->SetDirec(down); // cho bóng bay hướng nam
							return;
						}
						if (ball->GetDirec() == upright) { // đông bắc
							ball->SetDirec(downright); // đông nam
							return;
						}
						if (ball->GetDirec() == upleft) {// tây bắc
							ball->SetDirec(downleft); // tây nam
							return;
						}
					}
}
				
bool BrickBreaker::BallTouchBrick() { // kiểm tra bóng có chạm gạch không, nếu chạm thì xóa gạch và cộng điểm
	for (int i = 0; i < brick.size(); i++)  // i chạy từ 0 đến số viên gạch
		if (ball->Gety() == brick[i]->Gety() - 1 || ball->Gety() == brick[i]->Gety() || ball->Gety() == brick[i]->Gety() + 1) // bóng chạm viền trên, viền dưới, hoặc viền cạnh viên gạch
			for (int j = 0; j < maxbrick; j++) // j chạy từ 0 đến độ dài gạch là 5
				if (ball->Getx() == brick[i]->Getx() + j) { // nếu x banh bằng x gạch
					srand(time(NULL));
					if (rand() % 10 + 1 > 7) { // random từ 1 đến 10, nếu ra số lớn hơn 7 thì cho xuất hiện vật phẩm thưởng
						srand(time(NULL));
						gItem.push_back(new GameItem(brick[i]->Getx() + 2, 11, rand() % 4 + 1)); // vật phẩm thưởng có tọa độ x bằng tọa độ chính giữa viên gạch, loại thì random
					}
					brick[i]->Delete(); // xóa gạch
					brick.erase(brick.begin() + i); // xóa viên gạch đó khỏi vector
					score += 10; // cộng 10 điểm
					TextColor(12);
					GotoXY(WidthGame + 3, HeightGame - 4); cout << "Score: " << score; // vẽ lại điểm số
					return true;
				}
	return false;
}
bool BrickBreaker::GItemTouchPaddle() { // hàm kiểm tra vật phẩm thưởng có chạm thanh trượt không
	for (int i = 0; i < gItem.size(); i++) // i chạy từ 0 đến số vật phẩm có trong mảng vật phẩm
		if (gItem[i]->Gety() == HeightGame - 2) { // nếu cùng tọa độ y
			for (int j = -1; j <= MaxPaddle; j++) { // j chạy từ -1 đến độ dài thanh trượt
				if (gItem[i]->Getx() == player->Getx() + j) {// nếu cùng tọa độ x
					if (gItem[i]->GetLoai() == cong10) // vật phẩm cộng 10 thì +10 đ
						score += 10;
					if (gItem[i]->GetLoai() == cong20) // vật phẩm +20 thì +20 đ
						score += 20;
					if (gItem[i]->GetLoai() == themmang) // vật phẩm thêm mạng thì cộng 1 mạng
						mang++;
					if (gItem[i]->GetLoai() == taovatcan) { // vật phẩm tạo vật cản thì tạo 1 vật cản
						int k;
						for (k = 0; k < gItem.size(); k++) { // k chạy từ 0 đến số vật phẩm có trong mảng vật phẩm
							if (gItem[k]->GetLoai() == vatcan) {  // nếu vật phẩm i là vật cản
								gItem[k]->Delete();// xóa vật cản
								gItem[k]->Setx(2);// cho vật cản chạy lại từ đầu
								break;// thoát vòng lặp
							}
						}
						if (k == gItem.size()) { // nếu k chạy đến size mảng, tức trong mảng ko có vật cản nào thì tạo vật cản mới
						// đảm bảo rằng trong mảng vật phẩm chỉ có 1 vật cản duy nhất
							GameItem *Vatcan = new GameItem(2, 11, vatcan);
							gItem.push_back(Vatcan); // thêm vật cản mới vào mảng các vật phẩm
						}
					}
					gItem[i]->Delete();// xóa vật phẩm
					gItem.erase(gItem.begin() + i); // xóa vật phẩm đó khỏi vector các vật phẩm hiện có
					DrawInfo();// vẽ lại số mạng
					return true;
				}
			}
		}
	return false;
}

void BrickBreaker::Logic() {
	int x0 = ball->Getx();
	int y0 = ball->Gety();
	Direc dir0 = ball->GetDirec();
	if (x0 == 1 || BallTouchBrick()) {// Bóng chạm biên trái, chạm gạch
		if (dir0 == upleft)//Nếu bóng đang bay theo hướng tây bắc
			ball->SetDirec(upright);// đổi hướng bóng thành đông bắc
		if (dir0 == downleft) // Nếu bóng đang bay theo hướng tây nam
			ball->SetDirec(downright);// đổi hướng bóng thành đông nam
	}
	if (x0 == WidthGame - 1 || BallTouchBrick()) {//Bóng chạm biên phải
		if (dir0 == upright) //Nếu bóng đang bay theo hướng đông bắc
			ball->SetDirec(upleft);//Đổi hướng bóng bay theo hướng tây bắc
		if (dir0 == downright) //Nếu bóng đang bay theo hướng đông nam
			ball->SetDirec(downleft);//đổi hướng bóng bay theo hướng tây nam
	}
	if (BallTouchBrick()) { // nếu bóng chạm gạch
		if (dir0 == upleft)//Nếu bóng đang bay theo hướng tây bắc
			ball->SetDirec(upright);// đổi hướng bóng thành đông bắc
		if (dir0 == downleft)// Nếu bóng đang bay theo hướng tây nam
			ball->SetDirec(downright);// đổi hướng bóng thành đông nam
		if (dir0 == upright)//Nếu bóng đang bay theo hướng đông bắc
			ball->SetDirec(upleft);//Đổi hướng bóng bay theo hướng tây bắc
		if (dir0 == downright)//Nếu bóng đang bay theo hướng đông nam
			ball->SetDirec(downleft);//đổi hướng bóng bay theo hướng tây nam
	}
	if (y0 == 1) {//bóng chạm biên trên
		if (dir0 == upleft) //Nếu bóng đang bay theo hướng tây bắc
			ball->SetDirec(downleft);// đổi hướng bóng thành tây nam
		if (dir0 == upright) //Nếu bóng đang bay theo hướng đông bắc
			ball->SetDirec(downright);//Đổi hướng bóng bay theo hướng đông nam
		if (dir0 == up) //Nếu bóng đang bay theo hướng bắc
			ball->SetDirec(down);//Đổi hướng bóng bay theo hướng nam
	}
	if (ball->TouchPaddleDown(*player)) {// nếu bóng chạm người chơi
		if (_kbhit()) { // Kiểm tra người chơi có nhấn phìm nào không
			char key = _getch();// 
			if (key == 75)  // mũi tên qua trái
				ball->SetDirec(upleft); // nếu người chơi qua trái thì bóng bay hướng tây bắc
			if (key == 77) // mũi tên qua phải
				ball->SetDirec(upright); // nếu người chơi nhấn mũi tên qua phải thì bóng bay hướng đông bắc

		}
		// ngược lại nếu người chơi không nhấn phím nào, nghĩa là người chơi muốn bóng bay theo hướng cũ
		if (ball->GetDirec() == down) // nếu bóng đang bay hướng nam
			ball->SetDirec(up); // cho bóng bay theo hướng bắc
		if (ball->GetDirec() == downright) // đông nam
			ball->SetDirec(upright); // đông bắc
		if (ball->GetDirec() == downleft) // tây anm
			ball->SetDirec(upleft); // tây bắc
		if (ball->GetDirec() == stop) // trường hợp bóng đang đứng yên ( khi bắt đầu ván mới) 
			ball->SetDirec(up); // cho bóng bay hướng bắc

	//srand(time(NULL));
	//ball->SetDirec((Direc)((rand() % 3) + 1));// đổi hướng bóng
		if (speed > 30)
			speed = 0.9*speed; // giảm biến ngủ theo tốc độ
	}
	GItemTouchPaddle(); // kt vật phẩm game chạm thanh trượt
	BallTouchItem(); // hàm xử lí khi bóng chạm vật cản
	if (y0 == HeightGame - 1)
	{//bóng chạm biên dưới
		player->Delete();//xóa thanh trượt 
		ball->Delete(2);// xóa bóng
		ball->Reset(); // reset bóng
		player->Reset(); // reset thanh trượt
		speed = originalSpeed;
		ball->Draw(); // vẽ bóng
		player->Draw(); // vẽ thanh trượt
		mang--; // trừ đi một mạng
		DrawNewRound();// ghi lại số mạng
	}
	if (mang == 0) { // hết mạng
		system("cls");
		TextColor(1);
		state = 0;
		GotoXY(WidthGame / 2 - 10, HeightGame / 2 - 5);
		cout << "YOU LOSE!!!";
	}
	if (brick.size() == 0) { // nếu hết gạch
		system("cls");
		TextColor(1);
		state = 0;
		GotoXY(WidthGame / 2 - 10, HeightGame / 2 - 5);
		cout << "YOU WIN !!!";
		GotoXY(WidthGame / 2 - 10, HeightGame / 2);
	}
}



void BrickBreaker::SaveGame() { // hàm save game

	GotoXY(WidthGame + 3, 10);
	cout << "Save game! File name: "; // yêu cầu nhập tên file lưu
	rewind(stdin);
	string name;
	getline(cin, name);
	ofstream fileout;
	fileout.open("SaveGame.text", ios::app); // mở file SaveGame (file lưu toàn bộ những lần người chơi lưu) chế độ ghi thêm
	if (!fileout) { // nếu không mở được file thì thông báo lỗi
		GotoXY(WidthGame + 3, 13);
		cout << "Loi chuong trinh: khong luu duoc game!";
	}
	else {
		fileout << name << ","; // ghi tên lưu vào file
		fileout << player->Getx() << "," << player->Gety() << ","; // ghi tọa độ người chơi
		fileout << ball->Getx() << "," << ball->Gety() << ","; // ghi tọa độ bóng
		fileout << mang << "," << score << "," << speed << ","; // ghi số mạng và số điểm và tốc độ bóng
		fileout << brick.size() << ","; // ghi lại số viên gạch hiện có
		for (int i = 0; i < brick.size(); i++) // i chạy từ 0 đến số viên gạch
			fileout << brick[i]->Getx() << "," << brick[i]->Gety() << ",";// ghi tọa độ của từng viên gạch
		fileout << gItem.size() << ",";// ghi lại số vật phẩm hiện có
		for (int i = 0; i < gItem.size(); i++) // i chạy từ 0 đến số vật phẩm
			fileout << gItem[i]->Getx() << "," << gItem[i]->Gety() << "," << gItem[i]->GetLoai() << ",";// ghi tọa độ và loại của vật phẩm
		fileout << endl; // khi xong thì xuống dòng
		fileout.close(); // đóng file
		GotoXY(WidthGame + 3, 10);
		cout << "                                                            ";// xóa dòng trên
		GotoXY(WidthGame + 3, 11);
		cout << "Success! Press any key to continue"; // yêu cầu nhập phím để tiếp tục game
		while (1) {
			if (_kbhit()) //đợi người chơi nhập phím 
			{
				GotoXY(WidthGame + 3, 11);
				cout << "                                                 "; // xóa dòng trên
				state = 1; // cho thread tiếp tục chạy
				return;
			}
		}
	}

}


void BrickBreaker::LoadGame() { // hàm loadgame
	ifstream filein;
	filein.open("SaveGame.text", ios::in);// mở file chế độ đọc
	if (!filein)
	{
		GotoXY(WidthGame + 3, 10);
		cout << "Ban chua luu game nao!" << endl;
	}
	else
	{
		GotoXY(0, 10);
		cout << "------ Kho Game da luu ----------" << endl;
		int i = 1;
		while (filein.get() != EOF)
		{ // nếu chưa gặp kí tự kết thúc file
			filein.seekg(-1, 1); // lùi lại 1 byte
			string name;
			getline(filein, name, ','); // đọc tên mà player đã đặt tên khi lưu
			cout << i << ". " << name << endl; // ghi ra màn hình
			i++;
			while (filein.get() != '\n'); // tạo vòng lặp, lặp cho đến khi gặp kí tự xuống dòng
		}
		filein.close();
		filein.open("SaveGame.text", ios::in);// mở file chế độ đọc
		//filein.seekg(0);// đưa con trỏ về đầu file
		cout << "File name: ";
		rewind(stdin);
		string namef;
		getline(cin, namef);
		while (filein.get() != EOF)
		{ // nếu chưa gặp kí tự kết thúc file
			filein.seekg(-1, 1); // lùi lại 1 byte
			string name;
			getline(filein, name, ',');// đọc tên mà player đã đặt tên khi lưu
			if (name == namef)
			{ // nếu đúng tên player yêu cầu load
				//game = new BrickBreaker;
				int x, y; // biến lưu tọa độ
				filein >> x;
				player->Setx(x); // set tọa độ x thanh trượt
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> y;
				player->Sety(y); // set tọa độ y thanh trượt
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> x;
				ball->Setx(x); // xét tọa x bóng
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> y;
				ball->Sety(y); // xét tọa độ y bóng
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> x;
				mang = x; // set số mạng
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> x;
				score = x; // set số điểm
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				filein >> x;
				speed = x; // set tốc độ bóng
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				int sogach;
				filein >> sogach; // lưu số viên gạch
				//game->brick.resize(x); // resize mảng gạch
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				vector<Brick*> b;
				for (int i = 0; i < sogach; i++)
				{ // cho i chạy từ 0 đến số gạch
					filein >> x;
					filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
					filein >> y;
					filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
					b.push_back(new Brick(x, y)); // thêm gạch vào mảng viên gạch
				}
				SetBricks(b); // thay đổi mảng gạch của game
				int soitem;
				filein >> soitem; // lưu số vật phẩm
				//game->gItem.resize(x); // resize mảng vật phẩm
				filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
				for (int i = 0; i < soitem; i++)
				{ // cho i chạy từ 0 đến số vật phẩm
					filein >> x;
					//game->gItem[i]->Setx(x); // set tọa độ x của vật phẩm thứ i
					filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
					filein >> y;
					//game->gItem[i]->Sety(y); // set tọa độ y của vật phẩm thứ i
					filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
					int loai;
					filein >> loai;
					//game->gItem[i]->SetLoai(x); // set loại của vật phẩm thứ i
					filein.seekg(1, 1); // tiến một byte, ( bỏ dấu ,)
					gItem.push_back(new GameItem(x, y, loai)); // thêm vật phẩm vào mảng vật phẩm
					ball->SetDirec(stop);// cho bóng đứng yên
				}
				cout << "Success Loading!"; // thông báo load thành công
				Sleep(500);
				filein.close(); // đóng file
				system("cls"); // xóa màn hình
				return;
			}
			else
				while (filein.get() != '\n'); // lặp đến khi xuống dòng


		}
	}
}


void BrickBreaker::Automation() { // hàm tự động thanh trượt
	int xball = ball->Getx();
	int yball = ball->Gety();
	int x0 = player->Getx();//toạ độ x của người chơi
	Direc dir = ball->GetDirec();
	if (x0 + 5 < xball && dir == downright) // Nếu tọa độ trung tâm thanh trượt < xball, bóng đang di chuyển theo hướng đông nam
		player->MoveRight();// cho thanh trượt qua phải để hứng bóng
	if (x0 + 5 > xball && dir == downleft) // Nếu tọa độ trung tâm thanh trượt > xball, bóng đang di chuyển theo hướng tây nam
		player->MoveLeft();//cho thanh trượt qua trái để hứng bóng
	if (dir == down) { // nếu bóng đang di chuyển theo hướng bắc
		for (int i = 0; i < MaxPaddle; i++) {
			if (xball == x0 + i) // nếu thanh trượt đang ở vị trí có thể hứng bóng, cho thanh trượt đứng im
				return;
			if (x0 + MaxPaddle < xball) { // nếu thanh trượt bị lệch bên trái so với hướng bóng, cho thanh trượt qua phải để hứng bóng
				player->MoveRight();
				break;
			}
			if (x0 > xball) { //nếu thanh trượt bị lệch bên phải so với hướng bóng, cho thanh trượt qua trái để hứng bóng
				player->MoveLeft();
				break;
			}
		}
	}

	if (_kbhit()) { // Kiểm tra người chơi có nhấn phìm nào không
		char key = _getch();
		if (key == 27) {
			state = 0; // chết, dừng thread
		}
		if (key == 'p' || key == 'P') {// phím p
			GotoXY(WidthGame + 3, 10);
			TextColor(12);
			cout << "Press any key to continue" << endl; // in ra dòng: nhấn bất kì phím nào để tiếp tục
			TextColor(15);
			while (1) {
				if (_kbhit()) { // Kiểm tra người chơi có nhấn phìm nào không, nếu có thì thoát vòng lặp, game tiếp tục chạy
					GotoXY(WidthGame + 3, 10);
					cout << "                                      " << endl; // xóa dòng chữ trên
					return;
				}
			}
		}
	}
}
