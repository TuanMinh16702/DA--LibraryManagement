#include <iostream>
#include <sstream>
using namespace std;

struct Sach {
	char MaSach[20];
	int TrangThai; // 0: san sang de muon, 1: Co nguoi dang muon, 2: da thanh ly 
	string ViTri;
	bool DuocMuon = false;
};

// danh muc sach
struct NodeSach {
	Sach sach;
	NodeSach *next;
};

typedef NodeSach *PTRSach;

// Thuat toan danh sach lien ket don

void ClearSach (PTRSach &First) {
	PTRSach p;
	while (First != NULL) {
		p = First;
		First = First->next;
		delete p;
	}
}

int TongSach (PTRSach First) { 
	PTRSach p;
    int tong = 0;
    for (p = First; p != NULL; p = p->next){
		tong++;
	}
	return tong;
}

void Insert_First(PTRSach &First, Sach sach) {
	PTRSach p;
	p = new NodeSach;
	p->sach = sach;
	p->next = First;
	First = p;
}

void Insert_after(PTRSach p, Sach sach) {
	PTRSach q;
	if (p == NULL) {
		cout << "Khong them duoc" << endl;
	} else {
		q = new NodeSach;
		q->sach = sach;
		q->next = p->next;
		p->next = q;
	}
}

void ThemSach (PTRSach &dms, Sach sach, int &soluong) {
	if (dms == NULL) {
		Insert_First(dms, sach);
		soluong++;
	} else {
		PTRSach p;
		for (p = dms; p->next != NULL; p = p->next);
		Insert_after(p, sach);
		soluong++;
	}
}

PTRSach Search_Info(PTRSach First, char MaSach[]) {
	PTRSach p;
	for (p = First; p != NULL; p = p->next) 
        if (strcmp(p->sach.MaSach, MaSach) == 0) return p;
	return NULL;
}


int Delete_First (PTRSach &First) {
	PTRSach p;
	if (First == NULL) {
		return 0;
	}
	p = First;
	First = p->next;
	delete p;
	return 1;
}

int Delete_after (PTRSach p) {
	PTRSach q;
	if (p == NULL || p->next == NULL) {
		return 0;
	}
	q = p->next;
	p->next = q->next;
	delete q;
	return 1;
}

int Delete_info(PTRSach &First, char MaSach[]) {
	PTRSach p = First;
	if (First == NULL) {
		return 0;
	}
	if (strcmp(First->sach.MaSach, MaSach) == 0) {
		Delete_First(First);
		return 1;
	}
	for (p = First; p->next != NULL && strcmp(p->next->sach.MaSach, MaSach) != 0; p = p->next);
	if (p->next != NULL) {
		Delete_after(p);
		return 1;
	}
	return 0;
}

void ShowDMS (PTRSach dms, char MaSach[]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	draw(19, 53, 34, 5, 7);
	VeKhungDMS(0, 34, 5);
	int j = 0;
	PTRSach p;
	for (p = dms; p != NULL; p = p->next) {
		char *pointer = strstr(p->sach.MaSach, MaSach);
		if (pointer) {
			if (j > 14) {
				break;
			}
			
			SetConsoleTextAttribute(h, 7);
			NoiKhungDMS(34, 8 + j);
			gotoxy(35, 8 + j);
			cout << p->sach.MaSach;
			
			gotoxy(56, 8 + j);
			switch(p->sach.TrangThai) {
				case 0: {
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(h, 10);
					cout << "CHO MUON DUOC";
					SetConsoleTextAttribute(h, 7);
					break;
				}
				case 1: {
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(h, 12);
					cout << "DA CHO MUON";
					SetConsoleTextAttribute(h, 7);
					break;
				}
				case 2: {
					HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(h, 14);
					cout << "DA THANH LY";
					SetConsoleTextAttribute(h, 7);
					break;
				}
			}
			
			gotoxy(72, 8 + j);
			cout << p->sach.ViTri;
			
			
			SetConsoleTextAttribute(h, 232);
			j++;
		}
	}
}

PTRSach SearchSach(PTRSach dms) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(10, 4);
	cout << "**Nhan ESC de ngung tim kiem**";
	gotoxy(20, 2);
	SetConsoleTextAttribute(h, 232);
	char MaSach[20];
	int i = 0;
	while(true) {
		Showcursortype();
		char key = getch();
		
		if (key == 27) {
			int isConfirm = Confirm("Ban co muon dung tim kiem khong?");
			
			if (isConfirm == 1) {
				PTRSach p = NULL;
				return p;
			} else if (isConfirm == 0) {
				gotoxy(20, 2);
				SetConsoleTextAttribute(h, 232);
				cout << "                    ";
				SetConsoleTextAttribute(h, 7);
				ShowDMS(dms, "");
				Showcursortype();
				gotoxy(20, 2);
				SetConsoleTextAttribute(h, 7);
				return SearchSach(dms);
			}
		}
		
		if (key == 8 && strlen(MaSach) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			MaSach[i] = '\0';
			gotoxy(20 + i, 2);
			cout << " ";
			gotoxy(20 + i, 2);
			ShowDMS(dms, MaSach);
			gotoxy(20 + i, 2);
			continue;
		}
		
		if(key >= 48 && key <= 57 || key >= 65 && key <= 90 || key >= 97 && key <= 122 || key == 45) {
			if (strlen(MaSach) > 20) {
				continue;
			}
			if (key >= 97 && key <= 122){
				key = key - 32;
				MaSach[i] = char(key);
				cout << MaSach[i];
				i++;
			} else {
				MaSach[i] = char(key);
				cout << MaSach[i];
				i++;	
			}
			MaSach[i + 1] = '\0';
			ShowDMS(dms, MaSach);	
			gotoxy(20 + i, 2);
		}
		
		if (key == 13) {
			if(strlen(MaSach) == 0) {
				PTRSach p = NULL;
				return p;
			} else {
				PTRSach p;
				for (p = dms; p != NULL; p = p->next) {
					if (strcmp(p->sach.MaSach, MaSach) == 0){
						SetConsoleTextAttribute(h, 7);
						return p;
						break;
					}
				}
				
				PTRSach q = NULL;
				return q;
			}
		}
	}
}


char LayMaSach (char MaSach[], PTRSach dms, char ISBN[]) {
	if (dms == NULL) { // MaSach: ISBN-0
		strcpy(MaSach, ISBN);
		int len = strlen(MaSach);
		MaSach[len] = '-';
		len++;
		MaSach[len] = '1';
		len++;
		MaSach[len] = '\0';
	} else { // MaSach: ISBN-stt
		PTRSach p;
		for (p = dms; p->next != NULL; p = p->next); // lay node sach cuoi cung
		strcpy(MaSach, p->sach.MaSach); // isbn-14
		char number[10];
	    int index = 0;
	    for (int i = 0; i < strlen(p->sach.MaSach); i++) {
	   	    if (p->sach.MaSach[i] == '-') {
	   			for (int j = i + 1; j < strlen(p->sach.MaSach); j++) {
					number[index] = p->sach.MaSach[j];
					index++;
				}
		    }
	    }
	    number[index] = '\0';
	    int num = atoi(number);
	    num++;
	    char str[10];
	    stringstream ss;
	    ss << num;
	    ss >> str;
	    str[strlen(str)] = '\0';
	    for (int i = 0; i < strlen(MaSach); i++) {
	    	if (MaSach[i] == '-') {
	    		index = i + 1;
	    		for (int j = 0; j < strlen(str); j++){
	    			MaSach[index] = str[j];
	    			index++;
				}
				break;
			}
		}
		MaSach[strlen(MaSach)] = '\0';	
	}
}

void XoaSach(PTRSach &dms, char ISBN[], int &soluong) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(20, 2);
	PTRSach p = SearchSach(dms);
	if (p != NULL) {
		if (p->sach.DuocMuon == false) { //sach nay chua duoc muon bao gio
			draw(7, 40, 40, 10, 7);
			int isConfirm = Confirm("BAN CHAN CHAN MUON XOA?");
			switch(isConfirm) {
				case 1:{ // co
					int isSuccess = Delete_info(dms, p->sach.MaSach);
					if (isSuccess == 1) {
						soluong--;
						SuccessMessage("Da xoa thanh cong", 87, 2, 7);
					} else if (isSuccess == 0){
						ErrorMessage("Xoa khong thanh cong", 85, 2, 7);
					}
					break;
				}
				case 0: { // khong
					break;
				}
			}	
		} else if (p->sach.TrangThai == 1) { // dang muon
			ErrorMessage("Sach nay dang cho muon", 84, 2, 7);
		} else if (p->sach.DuocMuon == true && p->sach.TrangThai != 1) {
			ErrorMessage("Khong the xoa vi da duoc muon truoc do", 77, 2, 7);
		}
		
	} else if (p == NULL) {
		ErrorMessage("Khong tim thay thong tin sach", 80, 2, 7);
	}
}

void MenuChinhSuaDMS(PTRSach &p) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	MenuChinhSuaDMSUI();
	
	gotoxy(35, 26);
	cout << p->sach.MaSach;
	
	gotoxy(56, 26);
	switch(p->sach.TrangThai) {
		case 0: {
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 10);
			cout << "CHO MUON DUOC";
			SetConsoleTextAttribute(h, 7);
			break;
		}
		case 1: {
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 12);
			cout << "DA CHO MUON";
			SetConsoleTextAttribute(h, 7);
			break;
		}
		case 2: {
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, 14);
			cout << "DA THANH LY";
			SetConsoleTextAttribute(h, 7);
			break;
		}
	}
	
	gotoxy(72, 26);
	cout << p->sach.ViTri;
	
	string array[2] = {"VI TRI", "KET THUC CHINH SUA"};
	int target = ChildMenu(array, 2, "MENU CHINH SUA SACH");
	switch(target) {
		case 1:{
			string ViTri;
			int isContinue = 1;
			CharForm("NHAP VI TRI");
			SetConsoleTextAttribute(h, 232);
			isContinue = StringUppercase(ViTri, 55, 13, 2, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDMS(p);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			p->sach.ViTri = ViTri;
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
			MenuChinhSuaDMS(p);
			break;
		}
		case 2:{
			SuccessMessage("Da luu thong tin chinh sua", 82, 2, 7);
			break;
		}
	}
}

void SuaSach (PTRSach &dms) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(20, 2);
	PTRSach p = SearchSach(dms);
	if (p == NULL) {
		ErrorMessage("Khong tim thay thong tin sach", 80, 2, 7);
	} else {
		MenuChinhSuaDMS(p);
	}
}

void Traverse (PTRSach First) { 
	PTRSach p;
    for (p = First ; p != NULL; p = p->next){
		cout << p->sach.MaSach << " " << p->sach.TrangThai << " " << p->sach.ViTri << endl;
	}
}

int TongTrangDMS (PTRSach dms) {
	int totalPage;
	if (TongSach(dms) % 15 == 0) {
		totalPage = TongSach(dms) / 15;
	} else if (TongSach(dms) % 15 != 0) {
		totalPage = TongSach(dms) / 15 + 1;
	}
	
	return totalPage;
}

// Xu ly giao dien danh muc sach
void KhoiTaoDMS(PTRSach &dms, char TenSach[], char ISBN[], int &soluong);

void GotoLastPage (int totalPage, PTRSach &dms, char TenSach[], char ISBN[]) {
	if (dms == NULL) {
		renderDMS(1, 1, 0, 'n', TenSach);
	} else {
		int start = (totalPage - 1) * 15;
	
		int totalLine;
		if (start + 15 > TongSach(dms)) {
			totalLine = TongSach(dms) % 15;
		} else totalLine = 15;
		
		renderDMS(totalPage, totalPage, totalLine, 'n', TenSach);
		
		int i = 0;
		int j = 0;
		PTRSach p;
		for (p = dms; p != NULL; p = p->next) {
			if (i >= start) {
				gotoxy(35, 8 + j);
				cout << p->sach.MaSach;
				
				gotoxy(56, 8 + j);
				switch(p->sach.TrangThai) {
					case 0: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 10);
						cout << "CHO MUON DUOC";
						SetConsoleTextAttribute(h, 7);
						break;
					}
					case 1: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 12);
						cout << "DA CHO MUON";
						SetConsoleTextAttribute(h, 7);
						break;
					}
					case 2: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 14);
						cout << "DA THANH LY";
						SetConsoleTextAttribute(h, 7);
						break;
					}
				}
				
				gotoxy(72, 8 + j);
				cout << p->sach.ViTri;
				j++;
			}
			
			i++;
			
			if (i >= start + totalLine) {
				break;
			}
		}		
	}
}

void XuatTrangDMS(int currentPage, int totalPage, PTRSach &dms, char TenSach[], char ISBN[], int &soluong) {
	if (currentPage == 0 || totalPage == 0) {
		renderDMS(1, 1, 0, 'x', TenSach);
		ErrorMessage("Danh sach rong", 88, 2, 7);
		Nocursortype(); // an con tro chuot
	} else {
		int start = (currentPage - 1) * 15;
	
		int totalLine;
		if (start + 15 > TongSach(dms)) {
			totalLine = TongSach(dms) % 15; // only trang cuoi
		} else totalLine = 15; // may trang khac
		
		renderDMS(currentPage, totalPage, totalLine, 'x', TenSach);
		
		int i = 0; // kiem soat vung xuat ra man hinh (start <= i <= end)
		int j = 0; // kiem soat dong khi xuat ra man hinh
		PTRSach p;
		for (p = dms; p != NULL; p = p->next) {
			if (i >= start) {
				gotoxy(35, 8 + j);
				cout << p->sach.MaSach;
				
				gotoxy(56, 8 + j);
				switch(p->sach.TrangThai) {
					case 0: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 10);
						cout << "CHO MUON DUOC";
						SetConsoleTextAttribute(h, 7);
						break;
					}
					case 1: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 12);
						cout << "DA CHO MUON";
						SetConsoleTextAttribute(h, 7);
						break;
					}
					case 2: {
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(h, 14);
						cout << "DA THANH LY";
						SetConsoleTextAttribute(h, 7);
						break;
					}
				}
				
				gotoxy(72, 8 + j);
				cout << p->sach.ViTri;
				j++;
			}
			
			i++;
			
			if (i >= start + totalLine) {
				break;
			}
		}	
	}
	while(true) {
		char key = getch();
		
		if (key == 27) { //esc: ra menu chinh
			break;
		}
		
		if (key == 0) { // bat phim hang f
			key = getch();
			if (key == 62) { // f4: them sach
				if(TongSach(dms) % 15 == 0) { // trong truong hop trang cuoi dang day
					renderDMS(1, 1, 0, 'n', TenSach);
				} else { // trong truong hop trang cuoi chua day
					int currentPage = TongTrangDMS(dms);
					int totalPage = TongTrangDMS(dms);
					GotoLastPage(totalPage, dms, TenSach, ISBN);
				}
				Showcursortype(); // cho hien con tro chuot
				NoiKhungDMS(34, 8 + (TongSach(dms) % 15));
				KhoiTaoDMS(dms, TenSach, ISBN, soluong);
				break;	
			}
			
			if (key == 63) { // f5: xoa sach
				XoaSach(dms, ISBN, soluong);
				int currentPage = TongTrangDMS(dms);
				int totalPage = TongTrangDMS(dms);
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
			
			if (key == 64) { // f6: sua sach
				SuaSach(dms);
				int currentPage = TongTrangDMS(dms);
				int totalPage = TongTrangDMS(dms);
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
		}
		
		if (key == -32) {
			key = getch();
			if (key == 75) { // left
				currentPage--;
				if (currentPage < 1) {
					currentPage = 1;
				}
				int totalPage = TongTrangDMS(dms);
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
			
			if (key == 77) { // right
				int totalPage = TongTrangDMS(dms);
				currentPage++;
				if (currentPage > totalPage) {
					currentPage = totalPage;
				}
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
		}
	}
}

void KhoiTaoDMS(PTRSach &dms, char TenSach[], char ISBN[], int &soluong) {
	int i = TongSach(dms) % 15;
	while(true) {
		if (i > 14) {
			renderDMS(TongSach(dms) / 15 + 1, TongSach(dms) / 15 + 1, 1, 'n', TenSach);
			i = 0;
		}
		char *MaSach = new char[20];
		int TrangThai;
		string ViTri;
		//char Tong[4];
		
		LayMaSach(MaSach, dms, ISBN);
		gotoxy(35, 8 + i);
		cout << MaSach;
		
		TrangThai = 0;
		gotoxy(56, 8 + i);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 10);
		cout << "CHO MUON DUOC";
		SetConsoleTextAttribute(h, 7);
		
		int isContinue = StringUppercase(ViTri, 72, 8 + i, 2, 7);
		if (isContinue == 0) {
			int currentPage = TongTrangDMS(dms);
			int totalPage = TongTrangDMS(dms);
			XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
			break;
		}
		
		Sach sach;
		strcpy(sach.MaSach, MaSach);
		sach.TrangThai = TrangThai;
		sach.ViTri = ViTri;
		ThemSach(dms, sach, soluong);
		
		gotoxy(72 + ViTri.length(), 8 + i);
		
		char key = getch();
		if (key == 13) { //enter: nhap tiep
			NoiKhungDMS(34, 9 + i);
			i++;
			continue;
		} 
		
		if (key == 27) { // esc: thoat ra menu
			break;
		}
		
		if (key == 0) {
			key = getch();
			if (key == 62) { // f4: xuat trang vua nhap
				int currentPage = TongTrangDMS(dms);
				int totalPage = TongTrangDMS(dms);
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
		}
	}
}

void XuLyDMS(PTRSach &dms, char TenSach[], char ISBN[], int &soluong) {
	if (dms == NULL) {
		int isConfirm = Confirm("Ban muon khoi tao danh sach moi khong?");
		switch(isConfirm) {
			case 1: { // co
				renderDMS(1, 1, 1, 'n', TenSach);
				KhoiTaoDMS(dms, TenSach, ISBN, soluong);
				break;
			}
			case 0: { // khong
				int currentPage = TongTrangDMS(dms); //0
				int totalPage = TongTrangDMS(dms); //0
				XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
				break;
			}
		}	
	} else {
		int currentPage = TongTrangDMS(dms);
		int totalPage = TongTrangDMS(dms);
		XuatTrangDMS(currentPage, totalPage, dms, TenSach, ISBN, soluong);
	}
}
