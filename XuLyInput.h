#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

void deleteChar(char s[], int index) {
	int n = strlen(s);
	for (int i = index; i < n; i++){
		s[i] = s[i + 1];
	}
	s[n] ='\0';
}

void deleteSpace(char s[]) {
	int n = strlen(s);
	for (int i = 0; i < n; i++) {
		if (s[i] == ' ' && s[i + 1] == ' '){
			deleteChar(s, i);
			i--;
		}
	}
	if (s[0] == ' ') {
		deleteChar(s, 0);
	}
	
	if (s[strlen(s) - 1] == ' ') {
		deleteChar(s, strlen(s) - 1);
	}
}

int AutoUppercase(char c[], int lenght, int x, int y, int min, int returnColor);
int OnlyNum (int &num, int x, int y, int min, int returnColor);

void ChuanHoa(char c[], int lenght, int x, int y, int min, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, returnColor);
	gotoxy(x, y);
	
	for (int i = 0; i < strlen(c); i++){
		cout << " ";
	}
	deleteSpace(c);
	
	while (strlen(c) == 0 || c[0] == ' ') {
		gotoxy(0, 15);
		ErrorMessage("Truong nay la bat buoc!", 83, 2, 7);
		SetConsoleTextAttribute(h, returnColor);
		AutoUppercase(c, lenght, x, y, min, returnColor);
	}
	
	gotoxy(x, y);
	cout << c;
}


int AutoUppercase(char c[], int lenght, int x, int y, int min, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(x, y);
	int i = 0;
	while (true) {
		char key = getch();
		
		if (i >= lenght - 1 && key != 13 && key != 8) {
			c[i] = '\0';
			ErrorMessage("So luong ky tu dat toi da", 82, 2, 7);
			SetConsoleTextAttribute(h, returnColor);
			gotoxy(x + i, y);
			continue;
		}
		
		if (key == 27) {
			return 0;
		}
		
		if (key == 13) {
			c[i] = '\0';
			if (strlen(c) < min) {
				gotoxy(0, 15);
				stringstream ss;
				ss << min;
				string str = ss.str();
 				string message = "Vui long nhap toi thieu " + str + " ky tu";
				ErrorMessage(message, 79, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x + i, y);
				continue;	
			}
			ChuanHoa(c, lenght, x, y, min, returnColor);
			return 1;
			break;
		}
		
		if (key == 8 && strlen(c) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			c[i] = '\0';
			gotoxy(x + i, y);
			cout << " ";
			gotoxy(x + i, y);
			continue;
		}
		
		if(key >= 65 && key <= 90 || key >= 97 && key <= 122 || key >= 48 && key <= 57 || key == 32) {
			if (key >= 97 && key <= 122){
				key = key - 32;
				c[i] = char(key);
				cout << c[i];
				i++;
			} else {
				c[i] = char(key);
				cout << c[i];
				i++;	
			}
		}	
	}
}

string ConvertToString (char a[], int size) {
	string s = "";
	for (int i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

int StringUppercase(string &st, int x, int y, int min, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char c[13];
	gotoxy(x, y);
	int i = 0;
	while (true) {
		char key = getch();
		
		if (i >= 13 && key != 13 && key != 8) {
			c[i] = '\0';
			ErrorMessage("So luong ky tu dat toi da", 82, 2, 7);
			SetConsoleTextAttribute(h, returnColor);
			gotoxy(x + i, y);
			continue;
		}
		
		if (key == 27) {
			return 0;
		}
		
		if (key == 13) {
			c[i] = '\0';
			if (strlen(c) < min) {
				gotoxy(0, 15);
				stringstream ss;
				ss << min;
				string str = ss.str();
 				string message = "Vui long nhap toi thieu " + str + " ky tu";
				ErrorMessage(message, 79, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x + i, y);
				continue;	
			}
			ChuanHoa(c, strlen(c), x, y, min, returnColor);
			st = ConvertToString(c, strlen(c));
			return 1;
			break;
		}
		
		if (key == 8 && strlen(c) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			c[i] = '\0';
			gotoxy(x + i, y);
			cout << " ";
			gotoxy(x + i, y);
			continue;
		}
		
		if(key >= 65 && key <= 90 || key >= 97 && key <= 122 || key >= 48 && key <= 57 || key == 32) {
			if (key >= 97 && key <= 122){
				key = key - 32;
				c[i] = char(key);
				cout << c[i];
				i++;
			} else {
				c[i] = char(key);
				cout << c[i];
				i++;	
			}
		}	
	}
}

int Name(char c[], int lenght, int x, int y, int min, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(x, y);
	int i = 0;
	while (true) {
		char key = getch();
		
		if (i >= lenght - 1 && key != 13 && key != 8) {
			c[i] = '\0';
			ErrorMessage("So luong ky tu dat toi da", 82, 2, 7);
			SetConsoleTextAttribute(h, returnColor);
			gotoxy(x + i, y);
			continue;
		}
		
		if (key == 27) {
			return 0;
		}
		
		if (key == 13) {
			c[i] = '\0';
			if (strlen(c) < min) {
				gotoxy(0, 15);
				stringstream ss;
				ss << min;
				string str = ss.str();
 				string message = "Vui long nhap toi thieu " + str + " ky tu";
				ErrorMessage(message, 79, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x + i, y);
				continue;	
			}
			ChuanHoa(c, lenght, x, y, min, returnColor);
			return 1;
			break;
		}
		
		if (key == 8 && strlen(c) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			c[i] = '\0';
			gotoxy(x + i, y);
			cout << " ";
			gotoxy(x + i, y);
			continue;
		}
		
		if(key >= 65 && key <= 90 || key >= 97 && key <= 122 || key == 32) {
			if (key >= 97 && key <= 122){
				key = key - 32;
				c[i] = char(key);
				cout << c[i];
				i++;
			} else {
				c[i] = char(key);
				cout << c[i];
				i++;	
			}
		}	
	}
}

int OnlyNum (int &num, int x, int y, int min, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char c[7];
	gotoxy(x, y);
	int i = 0;
	while (true) {
		fflush(stdin); 
		char key = getch();
		
		if (key == 27) {
			return 0;
		}
		
		if (i >= 7 && key != 13 && key != 8) {
			c[i] = '\0';
			ErrorMessage("So luong ky tu dat toi da", 82, 2, 7);
			SetConsoleTextAttribute(h, returnColor);
			gotoxy(x + i, y);
			continue;
		}
		
		if (key == 8) {
			if (i == 0) {
				continue;
			}
			i--;
			if (i < 0) {
				i = 0;
			}
			c[i] = '\0';
			gotoxy(x + i, y);
			cout << " ";
			gotoxy(x + i, y);
			continue;
		}
		
		if (key == 13) {
			c[i] = '\0';
			if (strlen(c) < min) {
				gotoxy(0, 15);
				stringstream ss;
				ss << min;
				string str = ss.str();
 				string message = "Vui long nhap toi thieu " + str + " ky tu";
				ErrorMessage(message, 79, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x + i, y);
				continue;	
			} else {
				num = atoi(c);
				if (num == 0) {
					gotoxy(0, 15);
					ErrorMessage("Truong nay phai lon hon 0", 83, 2, 7);
					SetConsoleTextAttribute(h, returnColor);
					gotoxy(x + i, y);
					continue;
				}
				return 1;
				break;
			}
		}
		
		if (key >= 48 && key <= 57){
			if (i > 6){
				c[i] = '\0';
				num = atoi(c);
				break;
			}
			c[i] = char(key);
			cout << c[i];
			i++;
		}	
	}
}

int OnlyZeroOne (int &num, int x, int y, int lenght, string zero, string one, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char c[1];
	gotoxy(x, y);
	while (true) {
		fflush(stdin);
		char key = getch();
		if (key == 48 || key == 49){
			if (strlen(c) != 0) {
				continue;
			} else {
				c[0] = char(key);
				c[1] = '\0';
				num = atoi(c);
				if (num == 0) {
					cout << zero;
				} else if (num == 1) {
					cout << one;
				}
			}	
		}
		
		if (key == 27) {
			return 0;
		}
		
		if (key == 8) {
			c[0] = '\0';
			gotoxy(x, y);
			for (int i = 0; i < lenght; i++) {
				cout << " ";
			}
			gotoxy(x, y);
			continue;
		}
		
		if (key == 13) {
			if (strlen(c) == 0) {
				ErrorMessage("Truong nay la bat buoc!", 83, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x, y);
				continue;
			} else {
				break;
			}
			return 1;
		}
	}
}

int Only012 (int &num, int x, int y, int lenght, string zero, string one, string two, int returnColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char c[1];
	gotoxy(x, y);
	while (true) {
		char key = getch();
		if (key == 48 || key == 49 || key == 50){
			if (strlen(c) != 0) {
				continue;
			} else {
				c[0] = char(key);
				c[1] = '\0';
				num = atoi(c);
				if (num == 0) {
					cout << zero;
				} else if (num == 1) {
					cout << one;
				} else if (num == 2) {
					cout << two;
				}
			}
		}
		
		if (key == 27) {
			return 0;
		}
		
		if (key == 8) {
			c[0] = '\0';
			gotoxy(x, y);
			for (int i = 0; i < lenght; i++) {
				cout << " ";
			}
			gotoxy(x, y);
			continue;
		}
		
		if (key == 13) {
			if (strlen(c) == 0) {
				ErrorMessage("Truong nay la bat buoc!", 83, 2, 7);
				SetConsoleTextAttribute(h, returnColor);
				gotoxy(x, y);
				continue;
			} else {
				break;
			}
			return 1;
		}
	}
}

