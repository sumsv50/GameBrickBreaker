#include"Graphics.h"
void TextColor(int x) { 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
}
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void DrawBoardG1(int width, int height)// vẽ màn hình game BrickBreaker
{
	TextColor(9);
	for (int i = 0; i <= height; i++)// vẽ viền dọc 
	{
		GotoXY(0, i);
		cout << static_cast<char>(219);
	}
	for (int i = 0; i <= height; i++)
	{
		GotoXY(width, i);
		cout << static_cast<char>(219);

	}
	//vẽ viền ngang
	for (int i = 1; i < width; i++)
	{
		GotoXY(i, 0);
		cout << static_cast<char>(219);
	}
	for (int i = 1; i < width; i++)
	{
		GotoXY(i, height);
		cout << static_cast<char>(219);
	}
	TextColor(15);
	for (int i = 1; i < width; i++) {
		GotoXY(i, height / 2);
		cout << static_cast<char>(176);
	}
	GotoXY(0, 0);
}
void DrawBoardG2(int width, int height)// vẽ màn hình game brick breaker
{
	TextColor(9);
	for (int i = 0; i <= height; i++)// vẽ viền dọc 
	{
		GotoXY(0, i);
		cout << static_cast<char>(219);
	}
	for (int i = 0; i <= height; i++)
	{
		GotoXY(width, i);
		cout << static_cast<char>(219);

	}
	//vẽ viền ngang
	for (int i = 1; i < width; i++)
	{
		GotoXY(i, 0);
		cout << static_cast<char>(219);
	}
	for (int i = 1; i < width; i++)
	{
		GotoXY(i, height);
		cout << static_cast<char>(219);
	}
	TextColor(15);
	
	GotoXY(0, 0);
}
void DeleteBoard() { // xóa các viền
	for (int i = 0; i <= HeightGame; i++)
	{
		GotoXY(0, i);
		cout <<" ";
	}
	for (int i = 0; i <= HeightGame; i++)
	{
		GotoXY(WidthGame, i);
		cout <<" ";

	}
	for (int i = 1; i < WidthGame; i++)
	{
		GotoXY(i, 0);
		cout <<" ";
	}
	for (int i = 1; i < WidthGame; i++)
	{
		GotoXY(i, HeightGame);
		cout << " ";
	}
	TextColor(15);
	for (int i = 1; i < WidthGame; i++) {
		GotoXY(i, HeightGame / 2);
		cout <<" ";
	}
	GotoXY(0, 0);
}
void AnConTro() {

	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void DrawName() {
	
	cout << endl;
	TextColor(2);
	cout << R"(	
			 _)"; TextColor(14); cout << R"(/\\\\)"; TextColor(2); cout << R"(______)"; TextColor(14); cout << R"(/\\\\)"; TextColor(2); cout << R"(___)"; TextColor(14); cout << R"(/\\\\///////\)"; TextColor(2); cout << R"(___)"; TextColor(14); cout << R"(/\\\\\\\\\\\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(/\\\\\\\\\\\\\\)"; TextColor(2); cout << R"(___
			 _)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\////////)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\///\/\\\\/////)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\////\/\\\\////)"; TextColor(2); cout << R"(___
			 __)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(///)"; TextColor(2); cout << R"(_______)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(______
			 ___)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(____)"; TextColor(14); cout << R"(///)"; TextColor(2); cout << R"(________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____
			 ____)"; TextColor(14); cout << R"(\/\\\\\\\\\\\\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\\\\\//)"; TextColor(2); cout << R"(_________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(____
			 _____)"; TextColor(14); cout << R"(\/\\\\/////\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\////)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___
			 ______)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_______________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(___________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__
			 _______)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_____)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(__________)"; TextColor(14); cout << R"(/\\\\\/\\\\\\\)"; TextColor(2); cout << R"(________)"; TextColor(14); cout << R"(\/\\\\)"; TextColor(2); cout << R"(_
			 ________)"; TextColor(14); cout << R"(\////)"; TextColor(2); cout << R"(______)"; TextColor(14); cout << R"(\////)"; TextColor(2); cout << R"(___)"; TextColor(14); cout << R"(\////)"; TextColor(2); cout << R"(__________)"; TextColor(14); cout << R"(\/////////////)"; TextColor(2); cout << R"(_________)"; TextColor(14); cout << R"(\////)"; TextColor(2); cout << R"(_
	)";
	cout << endl;
	cout << endl;
	Sleep(500);
	ifstream FileIn("Text.In", ios::in);
	while (!FileIn.eof())
	{
		string text;
		getline(FileIn, text);
		TextColor(14);
		cout << "\t\t" << text << endl;
	}

	FileIn.close();

	Sleep(1000);
}
