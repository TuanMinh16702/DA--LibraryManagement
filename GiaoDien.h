#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <cstring>
using namespace std;

void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Showcursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void gotoxy(short x, short y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

void draw(int h, int w, int x, int y, int color) {
	char array[w];
	for (int i = 0; i < w; i++) {
		array[i] = ' ';
	}
	array[w] = '\0';
	for (int i = 0; i < h; i++) {
		gotoxy(x, y + i);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, color);
		cout << array;
		SetConsoleTextAttribute(h, 7);
		cout << endl;
	}
}

void drawBG(int h, int w, int x, int y) {
	char array[w];
	for (int i = 0; i < w; i++) {
		array[i] = ' ';
	}
	array[w] = '\0';
	int color = 100;
	for (int i = 0; i < h; i++) {
		gotoxy(x, y + i);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, color + i * 10);
		cout << array;
		SetConsoleTextAttribute(h, 7);
		cout << endl;
	}
}

void VeKhungDauSach (int h, int x, int y){
	gotoxy(x, y);
	cout << "+----------------------------------------------------------------------------------------------------+" << endl;
	gotoxy(x, y + 1);
	cout << "|     ISBN      |         TEN SACH         | SO TRANG |    TAC GIA    | NAM XUAT BAN |    THE LOAI   |" << endl;
	gotoxy(x, y + 2);
	cout << "+----------------------------------------------------------------------------------------------------+" << endl;
	int i;
	for (i = 0; i < h; i++){
	gotoxy(x, y + i + 3);
	cout << "|               |                          |          |               |              |               |" << endl;	
	}
	gotoxy(x, y + i + 3);
	cout << "+----------------------------------------------------------------------------------------------------+" << endl;
}

void NoiKhungDauSach (int x, int y) {
	gotoxy(x, y);
	cout << "|               |                          |          |               |              |               |" << endl;
	gotoxy(x, y + 1);
	cout << "+----------------------------------------------------------------------------------------------------+" << endl;
}

void renderMenuUI (string array[], int lenght, int pointer) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int max = array[0].length();
	for (int i = 1; i < lenght; i++) {
		if (array[i].length() > max){
			max = array[i].length();
		}
	}
	
	for (int i = 0; i < lenght; i++) {
		if (i == pointer) {
			gotoxy(60 - max / 2, 13 + pointer);
			SetConsoleTextAttribute(h, 23);
			cout << array[i] << endl;
			SetConsoleTextAttribute(h, 7);
		} else {
			gotoxy(60 - max / 2, 13 + i);
			SetConsoleTextAttribute(h, 151);
			cout << array[i] << endl;
			SetConsoleTextAttribute(h, 7);
		}
	}
	cout << endl << endl;
}

int listenKeyBoardEvent(string array[], int lenght) {
	int pointer = 0;
	
	renderMenuUI(array, lenght, pointer);
	while(true){
        char c = getch();
        if(c == -32){
            c = getch();
            if(c == 72){
            	pointer--;
            	if (pointer < 0) {
            		pointer = lenght - 1;
				}
            	renderMenuUI(array, lenght, pointer);
            }
            if(c == 80){
            	pointer++;
            	if (pointer > lenght - 1) {
            		pointer = 0;
				}
            	renderMenuUI(array, lenght, pointer);
            }
        }
        if (c == 13) {
        	return pointer;
        	break;
		}
    }
}

int MainMenu(string array[], int lenght, string label) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	
	int labelLenght = label.length();
	
	draw(5, labelLenght + 2, 59 - labelLenght / 2, 1, 151);
	draw(4 + lenght, 30, 45, 10, 151);
	gotoxy(60 - labelLenght / 2, 3);
	SetConsoleTextAttribute(h, 151);
	cout << label << endl;
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(49, 11);
	SetConsoleTextAttribute(h, 151);
	cout << "XIN MOI CHON CHUC NANG" << endl;
	SetConsoleTextAttribute(h, 7);
	
	int target = listenKeyBoardEvent(array, lenght) + 1;
	return target;
}

int ChildMenu(string array[], int lenght, string message) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	
	draw(4 + lenght, 40, 40, 10, 151);
	
	gotoxy(60 - (message.length() / 2), 11);
	SetConsoleTextAttribute(h, 151);
	cout << message << endl;
	SetConsoleTextAttribute(h, 7);
	
	int target = listenKeyBoardEvent(array, lenght) + 1;
	return target;
}

void NhapDSButtons(HANDLE h) {
	gotoxy(3, 1);
	cout << "+-----------LUU Y KHI NHAP SACH-------------+";
	gotoxy(3, 2);
	cout << "| Nhan phim ESC trong luc nhap de ngung nhap|";
	gotoxy(3, 3);
	cout << "+-------------------------------------------+";
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Menu chinh";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(17, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Xem danh sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(34, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ENTER";
	SetConsoleTextAttribute(h, 176);
	cout << " Xuong dong";
	SetConsoleTextAttribute(h, 7);
}

void NhapDMSButtons(HANDLE h) {
	gotoxy(3, 1);
	cout << "+-----------LUU Y KHI NHAP SACH-------------+";
	gotoxy(3, 2);
	cout << "| Nhan phim ESC trong luc nhap de ngung nhap|";
	gotoxy(3, 3);
	cout << "+-------------------------------------------+";
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Menu chinh";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(17, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Xem danh sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(34, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ENTER";
	SetConsoleTextAttribute(h, 176);
	cout << " Xuong dong";
	SetConsoleTextAttribute(h, 7);
}

void NhapDGButtons(HANDLE h) {
	gotoxy(3, 1);
	cout << "+---------LUU Y KHI NHAP DOC GIA----------+";
	gotoxy(3, 2);
	cout << "| Gioi tinh: Nam: 0, Nu: 1                |";
	gotoxy(3, 3);
	cout << "|  Nhan ESC trong luc nhap de ngung nhap  |";
	gotoxy(3, 4);
	cout << "+-----------------------------------------+";
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " DS dau sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(18, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Xem danh sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(35, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ENTER";
	SetConsoleTextAttribute(h, 176);
	cout << " Xuong dong";
	SetConsoleTextAttribute(h, 7);
}

void XuatDSButton (HANDLE h) {
	gotoxy(3, 1);
	cout << "+-------------TIM KIEM DAU SACH-------------+";
	gotoxy(3, 2);
	cout << "| TEN SACH: ";
	SetConsoleTextAttribute(h, 232);
	cout << "                               ";
	SetConsoleTextAttribute(h, 7);
	cout << " |";
	gotoxy(3, 3);
	cout << "+-------------------------------------------+";
	
	
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Menu chinh";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(17, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Them";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(25, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F5";
	SetConsoleTextAttribute(h, 176);
	cout << " Xoa";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(32, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F6";
	SetConsoleTextAttribute(h, 176);
	cout << " Chinh sua";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(45, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F7";
	SetConsoleTextAttribute(h, 176);
	cout << " Danh muc sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(62, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang truoc";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(79, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang ke tiep";
	SetConsoleTextAttribute(h, 7);
}

void XuatDGButton (HANDLE h) {
	gotoxy(3, 1);
	cout << "+-------------TIM KIEM DOC GIA--------------+";
	gotoxy(3, 2);
	cout << "| NHAP MA THE: ";
	SetConsoleTextAttribute(h, 232);
	cout << "                            ";
	SetConsoleTextAttribute(h, 7);
	cout << " |";
	gotoxy(3, 3);
	cout << "+-------------------------------------------+";
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Menu chinh";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(17, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F1";
	SetConsoleTextAttribute(h, 176);
	cout << " SX theo Ma DG";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(34, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F2";
	SetConsoleTextAttribute(h, 176);
	cout << " SX theo Ten DG";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(52, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Them";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(60, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F5";
	SetConsoleTextAttribute(h, 176);
	cout << " Xoa";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(67, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F6";
	SetConsoleTextAttribute(h, 176);
	cout << " Chinh sua";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(80, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F7";
	SetConsoleTextAttribute(h, 176);
	cout << " Danh sach MT";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(96, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 176);
	cout << " PREV";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(106, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 176);
	cout << " NEXT";
	SetConsoleTextAttribute(h, 7);
}

void XuatMTButton (HANDLE h) {
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " DS doc gia";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(17, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Muon sach";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(30, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F5";
	SetConsoleTextAttribute(h, 176);
	cout << " Tra sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(42, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F6";
	SetConsoleTextAttribute(h, 176);
	cout << " Bao mat sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(58, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F7";
	SetConsoleTextAttribute(h, 176);
	cout << " Den sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(70, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang truoc";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(87, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang ke tiep";
	SetConsoleTextAttribute(h, 7);
}

void XuatDMSButton (HANDLE h) {
	gotoxy(3, 1);
	cout << "+---------------TIM KIEM SACH---------------+";
	gotoxy(3, 2);
	cout << "| NHAP MA SACH: ";
	SetConsoleTextAttribute(h, 232);
	cout << "                           ";
	SetConsoleTextAttribute(h, 7);
	cout << " |";
	gotoxy(3, 3);
	cout << "+-------------------------------------------+";
	
	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " DS dau sach";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(18, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F4";
	SetConsoleTextAttribute(h, 176);
	cout << " Them";
	SetConsoleTextAttribute(h, 7);	
	
	gotoxy(26, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F5";
	SetConsoleTextAttribute(h, 176);
	cout << " Xoa";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(33, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "F6";
	SetConsoleTextAttribute(h, 176);
	cout << " Chinh sua";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(46, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang truoc";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(63, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang ke tiep";
	SetConsoleTextAttribute(h, 7);
}

void renderDauSach(int currentPage, int totalPage, int totalLine, char type) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	draw(3, 19, 50, 1, 176);
	gotoxy(51, 2);
	SetConsoleTextAttribute(h, 176);
	cout << "DANH MUC DAU SACH";
	SetConsoleTextAttribute(h, 7);
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "+-----------------------------------------------+";
	VeKhungDauSach(totalLine, 9, 5);
	gotoxy(55, 24);
	cout << "Trang " << currentPage << "/" << totalPage;
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";
	//draw(3, 119, 1, 26, 176);
	
	switch(type) {
		case 'n': {
			Showcursortype();
			NhapDSButtons(h);
			break;
		}
		case 'x': {
			Nocursortype();
			XuatDSButton(h);
			break;
		}
 	}
}

void ErrorMessage (string mess, int x, int y, int BackgroundColor) {
	Nocursortype();
	int lenght = mess.length();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(x, y);
	draw(1, lenght + 2, x, y, 71);
	gotoxy(x + 1, y);
	SetConsoleTextAttribute(h, 71);
	cout << mess;
	Sleep(1000);
	draw(1, lenght + 2, x, y, BackgroundColor);
	SetConsoleTextAttribute(h, 7);
	Showcursortype();
}

void SuccessMessage (string mess, int x, int y, int BackgroundColor) {
	Nocursortype();
	int lenght = mess.length();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(x, y);
	draw(1, lenght + 2, x, y, 167);
	gotoxy(x + 1, y);
	SetConsoleTextAttribute(h, 167);
	cout << mess;
	Sleep(1000);
	draw(1, lenght + 2, x, y, BackgroundColor);
	SetConsoleTextAttribute(h, 7);
	Showcursortype();
}

void NhapDauSachForm() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Showcursortype();
	
	draw(17, 40, 40, 5, 176);
	
	SetConsoleTextAttribute(h, 176);
	gotoxy(48, 6);
	cout << "NHAP THONG TIN DAU SACH";
	gotoxy(42, 8);
	cout << "ISBN:";
	gotoxy(42, 10);
	cout << "TEN SACH:";
	gotoxy(42, 12);
	cout << "SO TRANG:";
	gotoxy(42, 14);
	cout << "TAC GIA:";
	gotoxy(42, 16);
	cout << "NAM XUAT BAN:";
	gotoxy(42, 18);
	cout << "THE LOAI:";
	
	gotoxy(42, 20);
	SetConsoleTextAttribute(h, 228);
	cout << " ESC: HUY ";
	
	gotoxy(67, 20);
	SetConsoleTextAttribute(h, 228);
	cout << " ENTER: OK ";
	
	SetConsoleTextAttribute(h, 232);
	gotoxy(52, 8);
	cout << "                          ";
	gotoxy(52, 10);
	cout << "                          ";
	gotoxy(52, 12);
	cout << "                          ";
	gotoxy(52, 14);
	cout << "                          ";
	gotoxy(56, 16);
	cout << "                      ";
	gotoxy(52, 18);
	cout << "                          ";
	SetConsoleTextAttribute(h, 7);
}

void NumberForm(string label) {
	int lenght = label.length();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Showcursortype();
	
	draw(8, 40, 40, 10, 176);
	
	SetConsoleTextAttribute(h, 176);
	gotoxy(60 - (lenght / 2), 11);
	cout << label;
	gotoxy(42, 13);
	cout << "Nhap so:";
	
	SetConsoleTextAttribute(h, 232);
	gotoxy(51, 13);
	cout << "                           ";
	
	gotoxy(42, 15);
	SetConsoleTextAttribute(h, 228);
	cout << " ESC: HUY ";
	
	gotoxy(67, 15);
	SetConsoleTextAttribute(h, 228);
	cout << " ENTER: OK ";
}

void CharForm(string label) {
	int lenght = label.length();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Showcursortype();
	
	draw(7, 40, 40, 10, 176);
	
	SetConsoleTextAttribute(h, 176);
	gotoxy(60 - (lenght / 2), 11);
	cout << label;
	gotoxy(42, 13);
	cout << "Nhap chuoi:";
	
	SetConsoleTextAttribute(h, 232);
	gotoxy(54, 13);
	cout << "                        ";
	
	gotoxy(42, 15);
	SetConsoleTextAttribute(h, 228);
	cout << " ESC: HUY ";
	
	gotoxy(67, 15);
	SetConsoleTextAttribute(h, 228);
	cout << " ENTER: OK ";
}

void renderConfirm (string array[], int lenght, int pointer) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int i = 0; i < lenght; i++) {
		if (i == pointer) {
			if (i == 0) {
				gotoxy(42, 15);
			} else gotoxy(73, 15);
			
			SetConsoleTextAttribute(h, 23);
			cout << array[i] << endl;
			SetConsoleTextAttribute(h, 7);
		} else {
			if (i == 0) {
				gotoxy(42, 15);
			} else gotoxy(73, 15);
			
			SetConsoleTextAttribute(h, 232);
			cout << array[i] << endl;
			SetConsoleTextAttribute(h, 7);
		}
	}
	cout << endl << endl;
}

int listenConfirmKey(string array[], int lenght) {
	int pointer = 0;
	
	renderConfirm(array, lenght, pointer);
	while(true){
        char c = getch();
        if(c == -32){
            c = getch();
            if(c == 75){
            	pointer--;
            	if (pointer < 0) {
            		pointer = lenght - 1;
				}
            	renderConfirm(array, lenght, pointer);
            }
            if(c == 77){
            	pointer++;
            	if (pointer > lenght - 1) {
            		pointer = 0;
				}
            	renderConfirm(array, lenght, pointer);
            }
        }
        if (c == 13) {
        	return pointer;
        	break;
		}
    }
}

int ConfirmMenu(string array[], int lenght, string message) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int len = message.length();
	
	Nocursortype();
	draw(7, 40, 40, 10, 232);
	
	gotoxy(60 - (len / 2), 11);
	SetConsoleTextAttribute(h, 232);
	cout << message;
	SetConsoleTextAttribute(h, 7);
	
	int target = listenConfirmKey(array, lenght) + 1;
	return target;
}

int Confirm(string message) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	string array[2] = {"Co", "Khong"};
	int target = ConfirmMenu(array, 2, message);
	switch(target) {
		case 1: {
			return 1;
			break;
		}
		case 2: {
			return 0;
			break;
		}
	}
}

void MenuChinhSuaDSUI() {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	draw(3, 30, 17, 1, 151);
	gotoxy(18, 2);
	SetConsoleTextAttribute(h, 151);
	cout << "CHINH SUA THONG TIN DAU SACH";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "+-----------------------------------------------+";
	
	VeKhungDauSach(1, 9, 23);
}

void VeKhungDocGia (int h, int x, int y){
	gotoxy(x, y);
	cout << "+-------------------------------------------------------------------------+" << endl;
	gotoxy(x, y + 1);
	cout << "| MA THE |            HO            |     TEN    | GIOI TINH | TRANG THAI |" << endl;
	gotoxy(x, y + 2);
	cout << "+-------------------------------------------------------------------------+" << endl;
	int i;
	for (i = 0; i < h; i++){
	gotoxy(x, y + i + 3);
	cout << "|        |                          |            |           |            |" << endl;	
	}
	gotoxy(x, y + i + 3);
	cout << "+-------------------------------------------------------------------------+" << endl;
}

void NoiKhungDocGia (int x, int y) {
	gotoxy(x, y);
	cout << "|        |                          |            |           |            |" << endl;
	gotoxy(x, y + 1);
	cout << "+-------------------------------------------------------------------------+" << endl;
}

void renderDocGia(int currentPage, int totalPage, int totalLine, char type) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	draw(3, 19, 50, 1, 176);
	gotoxy(51, 2);
	SetConsoleTextAttribute(h, 176);
	cout << "DANH SACH DOC GIA";
	SetConsoleTextAttribute(h, 7);
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "+-----------------------------------------------+";
	VeKhungDocGia(totalLine, 23, 5);
	gotoxy(55, 24);
	cout << "Trang " << currentPage << "/" << totalPage;
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";
	//draw(3, 119, 1, 26, 176);
	
	switch(type) {
		case 'n': {
			Showcursortype();
			NhapDGButtons(h);
			break;
		}
		case 'x': {
			Nocursortype();
			XuatDGButton(h);
			break;
		}
 	}
}

void NhapDocGiaForm() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Showcursortype();
	
	draw(16, 40, 40, 5, 176);
	
	SetConsoleTextAttribute(h, 176);
	gotoxy(48, 6);
	cout << "NHAP THONG TIN DOC GIA";
	gotoxy(42, 8);
	cout << "MA THE:";
	gotoxy(42, 10);
	cout << "HO:";
	gotoxy(42, 12);
	cout << "TEN:";
	gotoxy(42, 14);
	cout << "GIOI TINH:";
	gotoxy(42, 15);
	cout << "            0: NAM, 1: NU";
	gotoxy(42, 17);
	cout << "TRANG THAI:";
	
	gotoxy(42, 19);
	SetConsoleTextAttribute(h, 228);
	cout << " ESC: HUY ";
	
	gotoxy(67, 19);
	SetConsoleTextAttribute(h, 228);
	cout << " ENTER: OK ";
	
	SetConsoleTextAttribute(h, 232);
	gotoxy(50, 8);
	cout << "                            ";
	gotoxy(46, 10);
	cout << "                                ";
	gotoxy(47, 12);
	cout << "                               ";
	gotoxy(53, 14);
	cout << "                         ";
	gotoxy(54, 17);
	cout << "                        ";
	SetConsoleTextAttribute(h, 7);
}

void MenuChinhSuaDGUI() {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	gotoxy(3, 1);
	cout << "+---------LUU Y KHI NHAP DOC GIA----------+";
	gotoxy(3, 2);
	cout << "| Gioi tinh: Nam: 0, Nu: 1                |";
	gotoxy(3, 3);
	cout << "| Trang thai the: Khoa: 0, Binh thuong: 1 |";
	gotoxy(3, 4);
	cout << "+-----------------------------------------+";
	
	draw(4, 19, 50, 1, 151);
	gotoxy(52, 2);
	SetConsoleTextAttribute(h, 151);
	cout << "CHINH SUA THONG" << endl;
	gotoxy(52, 3);
	cout << "  TIN DOC GIA  ";
	SetConsoleTextAttribute(h, 7);
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "|                                               |";
	gotoxy(71, 4);
	cout << "+-----------------------------------------------+";
	
	VeKhungDocGia(1, 23, 23);
}

void VeKhungDMS (int h, int x, int y){
	gotoxy(x, y);
	cout << "+---------------------------------------------------+" << endl;
	gotoxy(x, y + 1);
	cout << "|      MA SACH      |   TRANG THAI  |     VI TRI    |" << endl;
	gotoxy(x, y + 2);
	cout << "+---------------------------------------------------+" << endl;
	int i;
	for (i = 0; i < h; i++){
	gotoxy(x, y + i + 3);
	cout << "|                   |               |               |" << endl;	
	}
	gotoxy(x, y + i + 3);
	cout << "+---------------------------------------------------+" << endl;
}

void NoiKhungDMS (int x, int y) {
	gotoxy(x, y);
	cout << "|                   |               |               |" << endl;
	gotoxy(x, y + 1);
	cout << "+---------------------------------------------------+" << endl;
}

void MenuChinhSuaDMSUI() {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	draw(3, 30, 17, 1, 151);
	gotoxy(18, 2);
	SetConsoleTextAttribute(h, 151);
	cout << "CHINH SUA THONG TIN SACH";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "+-----------------------------------------------+";
	
	VeKhungDMS(1, 34, 23);
}

void renderDMS(int currentPage, int totalPage, int totalLine, char type, char TenSach[]) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	draw(3, strlen(TenSach) + 2, 60 - (strlen(TenSach) + 2) / 2, 1, 176);
	gotoxy(60 - (strlen(TenSach) / 2), 2);
	SetConsoleTextAttribute(h, 176);
	cout << TenSach;
	SetConsoleTextAttribute(h, 7);
	gotoxy(71, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 2);
	cout << "|                                               |";
	gotoxy(71, 3);
	cout << "+-----------------------------------------------+";
	VeKhungDMS(totalLine, 34, 5);
	gotoxy(55, 24);
	cout << "Trang " << currentPage << "/" << totalPage;
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";
	//draw(3, 119, 1, 26, 176);
	
	switch(type) {
		case 'n': {
			Showcursortype();
			NhapDMSButtons(h);
			break;
		}
		case 'x': {
			Nocursortype();
			XuatDMSButton(h);
			break;
		}
 	}
}

void tracuuthongtin(int height, int currentPage, int totalPage) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	draw(3, 40, 18, 1, 176);
	gotoxy(27, 2);
	SetConsoleTextAttribute(h, 176);
	cout << "TRA CUU THONG TIN SACH";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(70, 1);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(70, 2);
	cout << "|                                               |";
	gotoxy(70, 3);
	cout << "+-----------------------------------------------+";
	
	gotoxy(20, 5);
	cout << "+-------------------------------------------------------------------------------+" << endl;
	gotoxy(20, 6);
	cout << "|     ISBN      |        TEN SACH         |    TAC GIA    | NXB |    THE LOAI   |" << endl;
	gotoxy(20, 7);
	cout << "+-------------------------------------------------------------------------------+" << endl;
	gotoxy(20, 8);
	cout << "|               |                         |               |     |               |" << endl;
	gotoxy(20, 9);
	cout << "+-------------------------------------------------------------------------------+" << endl;
	
	VeKhungDMS(height, 15, 10);
	gotoxy(35, 29);
	cout << "Trang " << currentPage << "/" << totalPage;
	gotoxy(75, 10);
	cout << "+----------PHIM NONG----------+";
	gotoxy(75, 11);
	cout << "|                             |";
	gotoxy(75, 12);
	cout << "|                             |";
	gotoxy(75, 13);
	cout << "|                             |";
	gotoxy(75, 14);
	cout << "|                             |";
	gotoxy(75, 15);
	cout << "|                             |";
	gotoxy(75, 16);
	cout << "|                             |";
	gotoxy(75, 17);
	cout << "|                             |";
	gotoxy(75, 18);
	cout << "|                             |";
	gotoxy(75, 19);
	cout << "|                             |";
	gotoxy(75, 20);
	cout << "|                             |";
	gotoxy(75, 21);
	cout << "|                             |";
	gotoxy(75, 22);
	cout << "|                             |";
	gotoxy(75, 23);
	cout << "|                             |";
	gotoxy(75, 24);
	cout << "|                             |";
	gotoxy(75, 25);
	cout << "|                             |";
	gotoxy(75, 26);
	cout << "|                             |";
	gotoxy(75, 27);
	cout << "|                             |";
	gotoxy(75, 28);
	cout << "+-----------------------------+";
	
	gotoxy(77, 12);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 7);
	cout << " Menu chinh";
	
	gotoxy(77, 14);
	SetConsoleTextAttribute(h, 228);
	cout << "F1";
	SetConsoleTextAttribute(h, 7);
	cout << " Tra cuu";
	
	gotoxy(77, 16);
	SetConsoleTextAttribute(h, 228);
	cout << "F2";
	SetConsoleTextAttribute(h, 7);
	cout << " DS Dau Sach";
	
	gotoxy(77, 18);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 7);
	cout << " Trang truoc";
	
	gotoxy(77, 20);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 7);
	cout << " Trang ke tiep";
}

void VeKhungMuonTra(int x, int y, int h) {
	gotoxy(x, y);
	cout << "+---------------------------------------------------------------------------------------------------+" << endl;
	gotoxy(x, y + 1);
	cout << "|      MA SACH       |        TEN SACH         | NGAY MUON |  NGAY TRA  | SO NGAY MUON | TRANG THAI |" << endl;
	gotoxy(x, y + 2);
	cout << "+---------------------------------------------------------------------------------------------------+" << endl;
	int i;
	for (i = 0; i < h; i++){
	gotoxy(x, y + i + 3);
	cout << "|                    |                         |           |            |              |            |" << endl;	
	}
	gotoxy(x, y + i + 3);
	cout << "+---------------------------------------------------------------------------------------------------+" << endl;
}

void NoiKhungMuonTra(int x, int y) {
	gotoxy(x, y);
	cout << "|                    |                         |           |            |              |            |" << endl;	
	gotoxy(x, y + 1);
	cout << "+---------------------------------------------------------------------------------------------------+" << endl;
}

void xulymuontra(char HoDG[], char TenDG[], int height, int currentPage, int totalPage) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	gotoxy(3, 0);
	cout << "+---------------TIM KIEM SACH---------------+";
	gotoxy(3, 1);
	cout << "| NHAP MA SACH: ";
	SetConsoleTextAttribute(h, 232);
	cout << "                           ";
	SetConsoleTextAttribute(h, 7);
	cout << " |";
	gotoxy(3, 2);
	cout << "+-------------------------------------------+";
	
	draw(3, 20, 50, 0, 176);
	gotoxy(51, 1);
	SetConsoleTextAttribute(h, 176);
	cout << "DANH SACH MUON TRA";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(71, 0);
	cout << "+-------------------THONG BAO-------------------+";
	gotoxy(71, 1);
	cout << "|                                               |";
	gotoxy(71, 2);
	cout << "+-----------------------------------------------+";
	
	gotoxy(22, 4);
	cout << "+-------------------------------------------------------------------------+" << endl;
	gotoxy(22, 5);
	cout << "| MA THE |            HO            |     TEN    | GIOI TINH | TRANG THAI |" << endl;
	gotoxy(22, 6);
	cout << "+-------------------------------------------------------------------------+" << endl;
	gotoxy(22, 7);
	cout << "|        |                          |            |           |            |" << endl;
	gotoxy(22, 8);
	cout << "+-------------------------------------------------------------------------+" << endl;
	
	VeKhungMuonTra(10, 9, height);
	gotoxy(55, 24);
	cout << "Trang " << currentPage << "/" << totalPage;
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";
	
	XuatMTButton(h);
}

void Top10Book() {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	draw(3, 40, 40, 1, 176);
	gotoxy(45, 2);
	SetConsoleTextAttribute(h, 176);
	cout << "10 DAU SACH DUOC MUON NHIEU NHAT";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(13, 5);
	cout << "+----------------------------------------------------------------------------------------------+" << endl;
	gotoxy(13, 6);
	cout << "|     ISBN      |        TEN SACH         |    TAC GIA    | NXB |    THE LOAI   | SO LUOT MUON |" << endl;
	gotoxy(13, 7);
	cout << "+----------------------------------------------------------------------------------------------+" << endl;
	gotoxy(13, 8);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 9);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 10);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 11);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 12);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 13);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 14);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 15);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 16);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 17);
	cout << "|               |                         |               |     |               |              |" << endl;
	gotoxy(13, 18);
	cout << "+----------------------------------------------------------------------------------------------+" << endl;
	
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";

	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Ve menu chinh";
	SetConsoleTextAttribute(h, 7);
}

void VeKhungDGQuaHan (int h, int x, int y){
	gotoxy(x, y);
	cout << "+-----------------------------------------------------------------------------------------------------+" << endl;
	gotoxy(x, y + 1);
	cout << "| MA THE |            HO            |     TEN    |       MA SACH      |         TEN SACH        | TNM |" << endl;
	gotoxy(x, y + 2);
	cout << "+-----------------------------------------------------------------------------------------------------+" << endl;
	int i;
	for (i = 0; i < h; i++){
	gotoxy(x, y + i + 3);
	cout << "|        |                          |            |                    |                         |     |" << endl;	
	}
	gotoxy(x, y + i + 3);
	cout << "+-----------------------------------------------------------------------------------------------------+" << endl;
}

void docgiaquahan(int height, int currentPage, int totalPage) {
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	draw(3, 40, 40, 1, 176);
	gotoxy(45, 2);
	SetConsoleTextAttribute(h, 176);
	cout << "DANH SACH DOC GIA MUON QUA HAN";
	SetConsoleTextAttribute(h, 7);
	
	VeKhungDGQuaHan(height, 9, 5);
	
	gotoxy(55, 24);
	cout << "Trang " << currentPage << "/" << totalPage;
	
	gotoxy(0, 25);
	cout << "+-------------------------------------------------------PHIM NONG-------------------------------------------------------+" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "|                                                                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------------------------------------------------------+";

	draw(3, 119, 1, 26, 176);
	gotoxy(2, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "ESC";
	SetConsoleTextAttribute(h, 176);
	cout << " Ve menu chinh";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(20, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "LEFT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang truoc";
	SetConsoleTextAttribute(h, 7);
	
	gotoxy(37, 27);
	SetConsoleTextAttribute(h, 228);
	cout << "RIGHT";
	SetConsoleTextAttribute(h, 176);
	cout << " Trang ke tiep";
	SetConsoleTextAttribute(h, 7);
}


