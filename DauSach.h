#include <iostream>
#include <conio.h>
#include <math.h>
#include <ctime>

using namespace std;

#define MAX_DAUSACH 100

struct DauSach {
	char ISBN[15];
	char TenSach[25];
	int SoTrang;
	char TacGia[15];
	int NamSB;
	char TheLoai[15];
	PTRSach dms = NULL;
	int soluotmuon;
	int soluong;
	
	DauSach(char isbn[15], char tensach[25], int st, char tacgia[15], int namsb, char theloai[15]){
		strcpy(ISBN, isbn);
		strcpy(TenSach, tensach);
		SoTrang = st;
		strcpy(TacGia, tacgia);
		NamSB = namsb;
		strcpy(TheLoai, theloai);
		dms = NULL;
		
		soluong = 0;
		soluotmuon = 0;
	}
};

// danh sach dau sach
struct NodeDauSach {
	int n = 0;
	DauSach *nodes[MAX_DAUSACH];
};

// thuat toan danh sach tuyen tinh

int Empty(NodeDauSach &ds) {
	return ds.n == 0;
}

int Full(NodeDauSach ds){
	return ds.n == MAX_DAUSACH;
}

int Insert_Item(NodeDauSach &ds, int i, DauSach *dausach) {
	if (i < 0 || i > ds.n || Full(ds)){
		return 0;
	}
	for (int j = ds.n - 1; j >= i; j--){
		ds.nodes[j+1] = ds.nodes[j];
	}
	ds.nodes[i] = dausach;
	ds.n++;
	return 1;
}

int Delete_item(NodeDauSach &ds, int i) {
	if (i < 0 || i >= ds.n || ds.n == 0) {
		return 0;
	}
	
	for (int j = i + 1; j < ds.n; j++) {
		ds.nodes[j - 1] = ds.nodes[j];
	}
	
	ds.n--;
	return 1;
}

int Search_info (NodeDauSach &ds, char isbn[]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(ds.nodes[i]->ISBN, isbn) == 0) {
			return i;
		}
	}
	return -1;
}

int SearchByName (NodeDauSach &ds, char TenSach[]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(ds.nodes[i]->TenSach, TenSach) == 0) {
			return i;
		}
	}
	return -1;
}

void Traverse(NodeDauSach &plist)
{
 	for(int i = 0 ; i < plist.n ; i++)
		cout << plist.nodes[i]->ISBN << " ";
	
	while (true) {
		char key = getch();
		if (key == 27) {
			break;
		}
 	}
}



// thuat toan xu ly dau sach

void ThemDauSach(NodeDauSach &ds);
void XuatTrang(int currentPage, int totalPage, NodeDauSach &ds);
void NextPage(int currentPage, int totalPage, NodeDauSach &ds);

void ShowDauSach(NodeDauSach ds, char TenSach[]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	
	// xoa khoang trang thua
	char ts[25];
	strcpy(ts, TenSach);
	deleteSpace(ts);
	
	draw(19, 102, 9, 5, 7);
	VeKhungDauSach(0, 9, 5);
	int j = 0;
	for (int k = 0; k < ds.n; k++) {
		char *p = strstr(ds.nodes[k]->TenSach, ts);
		if (p) {
			if (j > 14) {
				break;
			}
			
			SetConsoleTextAttribute(h, 7);
			NoiKhungDauSach(9, 8 + j);
			gotoxy(10, 8 + j);
			cout << ds.nodes[k]->ISBN;
			
			gotoxy(26, 8 + j);
			cout << ds.nodes[k]->TenSach;
			
			gotoxy(53, 8 + j);
			cout << ds.nodes[k]->SoTrang;
			
			gotoxy(64, 8 + j);
			cout << ds.nodes[k]->TacGia;
			
			gotoxy(80, 8 + j);
			cout << ds.nodes[k]->NamSB;
			
			gotoxy(95, 8 + j);
			cout << ds.nodes[k]->TheLoai;
			SetConsoleTextAttribute(h, 232);
			j++;	
		}
	}
}

int SearchDauSach(NodeDauSach ds) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(10, 4);
	cout << "**Nhan ESC de ngung tim kiem**";
	gotoxy(17, 2);
	SetConsoleTextAttribute(h, 232);
	char TenSach[25];
	int i = 0;
	while(true) {
		Showcursortype();
		char key = getch();
		
		if (key == 27) {
			int isConfirm = Confirm("Ban co muon dung tim kiem khong?");
			
			if (isConfirm == 1) {
				int index = -1;
				return index;
			} else if (isConfirm == 0) {
				gotoxy(17, 2);
				SetConsoleTextAttribute(h, 232);
				cout << "               ";
				SetConsoleTextAttribute(h, 7);
				ShowDauSach(ds, "");
				Showcursortype();
				gotoxy(17, 2);
				SetConsoleTextAttribute(h, 7);
				return SearchDauSach(ds);
			}
		}
		
		if (key == 8 && strlen(TenSach) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			TenSach[i] = '\0';
			gotoxy(17 + i, 2);
			cout << " ";
			ShowDauSach(ds, TenSach);
			gotoxy(17 + i, 2);
			continue;
		}
		
		if(key >= 65 && key <= 90 || key >= 97 && key <= 122 || key >= 48 && key <= 57 || key == 32) {
			if (strlen(TenSach) > 25) {
				continue;
			}
			if (key >= 97 && key <= 122){
				key = key - 32;
				TenSach[i] = char(key);
				cout << TenSach[i];
				i++;
			} else {
				TenSach[i] = char(key);
				cout << TenSach[i];
				i++;	
			}
			TenSach[i + 1] = '\0';
			ShowDauSach(ds, TenSach);
			gotoxy(17 + i, 2);
		}
		
		if (key == 13) {
			int index = -1;
			if(strlen(TenSach) == 0) {
				index = -1;
			} else {
				SetConsoleTextAttribute(h, 232);
				ChuanHoa(TenSach, 25, 17, 2, 1, 232);
				SetConsoleTextAttribute(h, 7);
				int dem = 0;
				for (int i = 0; i < ds.n; i++) {
					if (strcmp(TenSach, ds.nodes[i]->TenSach) == 0) {
						index = i;
						dem++;
					}
				}
				// neu co nhieu dau sach trung ten
				if(dem > 1) {
					string array[dem];
					int k = 0;
					for (int i = 0; i < ds.n; i++) {
						if (strcmp(TenSach, ds.nodes[i]->TenSach) == 0) {
							array[k] = ConvertToString(ds.nodes[i]->ISBN, strlen(ds.nodes[i]->ISBN));
							array[k] += " ";
							array[k] += ConvertToString(ds.nodes[i]->TenSach, strlen(ds.nodes[i]->TenSach));
							k++;
						}
					}
					
					int target = ChildMenu(array, dem, "VUI LONG CHON DAU SACH");
					char isbn[15];
					Copy(isbn, array[target - 1]);
					strtok(isbn, " ");
					index = Search_info(ds, isbn);
				}
			}
			SetConsoleTextAttribute(h, 7);
			return index;
			break;
		}
	}
}

void XoaDauSach (NodeDauSach &ds) {
	gotoxy(17, 2);
	int vitri = SearchDauSach(ds);
	if (vitri == -1) {
		ErrorMessage("Khong tim thay thong tin dau sach", 79, 2, 7);
	} else {
		if (TongSach(ds.nodes[vitri]->dms) > 0) {
			ErrorMessage("Ton tai sach trong danh muc sach", 80, 2, 7);
		} else if (TongSach(ds.nodes[vitri]->dms) == 0) {
			draw(7, 40, 40, 10, 7);
			int isConfirm = Confirm("BAN CHAN CHAN MUON XOA?");
			switch(isConfirm) {
				case 1:{
					int isSuccess = Delete_item(ds, vitri);
					if (isSuccess == 1) {
						SuccessMessage("Da xoa thanh cong", 87, 2, 7);
					} else if (isSuccess == 0) {
						ErrorMessage("Xoa khong thanh cong", 85, 2, 7);
					}
					break;
				}
				case 0: {
					break;
				}
			}	
		}
	}
}

void CapNhatMaSach(DauSach *dausach) {
	PTRSach p;
	for(p = dausach->dms; p != NULL; p = p->next) {
		char *MaSach = new char[20];
		strcpy(MaSach, dausach->ISBN);
		MaSach[strlen(MaSach)] = '\0';
		for (int i = strlen(p->sach.MaSach) - 1; i >= 0 ; i--) {
			if(p->sach.MaSach[i] == '-') {
				int index = strlen(MaSach);
				for(int j = i; j < strlen(p->sach.MaSach); j++) {
					MaSach[index] = p->sach.MaSach[j];
					index++;
					MaSach[index] = '\0';
				}
				strcpy(p->sach.MaSach, MaSach);
				break;
			}
		}
	}
}

void MenuChinhSuaDS(NodeDauSach &ds, int vitri) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	MenuChinhSuaDSUI();
	
	//Xuat Dau Sach dang chinh sua
	gotoxy(10, 26);
	cout << ds.nodes[vitri]->ISBN;
	
	gotoxy(26, 26);
	cout << ds.nodes[vitri]->TenSach;
	
	gotoxy(53, 26);
	cout << ds.nodes[vitri]->SoTrang;
	
	gotoxy(64, 26);
	cout << ds.nodes[vitri]->TacGia;
	
	gotoxy(80, 26);
	cout << ds.nodes[vitri]->NamSB;
	
	gotoxy(95, 26);
	cout << ds.nodes[vitri]->TheLoai;
	
	string array[6] = {"TEN SACH", "SO TRANG", "TAC GIA", "NAM XUAT BAN", "THE LOAI", "KET THUC CHINH SUA"};
	int target = ChildMenu(array, 6, "CHON THONG TIN CAN CHINH SUA");
	
	switch(target) {
		case 1:{
			int isContinue = 1;
			char TenSach[25];
			CharForm("NHAP TEN SACH");
			SetConsoleTextAttribute(h, 232);
			isContinue = AutoUppercase(TenSach, 25, 55, 13, 2, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDS(ds, vitri);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			strcpy(ds.nodes[vitri]->TenSach, TenSach);
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
			MenuChinhSuaDS(ds, vitri);
			break;
		}
		case 2:{
			int isContinue = 1;
			int SoTrang;
			NumberForm("NHAP SO TRANG");
			SetConsoleTextAttribute(h, 232);
			isContinue = OnlyNum(SoTrang, 52, 13, 2, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDS(ds, vitri);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			ds.nodes[vitri]->SoTrang = SoTrang;
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
			MenuChinhSuaDS(ds, vitri);
			break;
		}
		case 3:{
			int isContinue = 1;
			char TacGia[15];
			CharForm("NHAP TAC GIA");
			SetConsoleTextAttribute(h, 232);
			isContinue = Name(TacGia, 15, 55, 13, 4, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDS(ds, vitri);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			strcpy(ds.nodes[vitri]->TacGia, TacGia);
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
			MenuChinhSuaDS(ds, vitri);
			break;
		}
		case 4:{
			int isContinue = 1;
			int NamSB;
			NumberForm("NHAP NAM XUAT BAN");
			SetConsoleTextAttribute(h, 232);
			isContinue = OnlyNum(NamSB, 52, 13, 4, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDS(ds, vitri);
				break;
			}
			time_t now = time(0);
			tm *ltm = localtime(&now);
			
			while(NamSB > 1900 + ltm->tm_year) {
				ErrorMessage("Nam xuat ban khong hop le", 82, 2, 7);
				gotoxy(52, 13);
				SetConsoleTextAttribute(h, 232);
				cout << "       ";
				isContinue = OnlyNum(NamSB, 52, 13, 4, 232);
				if (isContinue == 0) {
					SetConsoleTextAttribute(h, 7);
					MenuChinhSuaDS(ds, vitri);
					break;
				}
			}
			if (isContinue == 1) {
				SetConsoleTextAttribute(h, 7);
				ds.nodes[vitri]->NamSB = NamSB;
				SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
				MenuChinhSuaDS(ds, vitri);
			}
			break;
		}
		case 5:{
			int isContinue = 1;
			char TheLoai[15];
			CharForm("NHAP THE LOAI");
			SetConsoleTextAttribute(h, 232);
			isContinue = Name(TheLoai, 15, 55, 13, 5, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDS(ds, vitri);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			strcpy(ds.nodes[vitri]->TheLoai, TheLoai);
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 2, 7);
			MenuChinhSuaDS(ds, vitri);
			break;
		}
		case 6:{
			SuccessMessage("Da luu thong tin chinh sua", 82, 2, 7);
			break;
		}
	}
}

void SuaDauSach (NodeDauSach &ds) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(17, 2);
	int vitri = SearchDauSach(ds);
	if (vitri == -1) {
		ErrorMessage("Khong tim thay thong tin dau sach", 79, 2, 7);
	} else {
		MenuChinhSuaDS(ds, vitri);
	}
}

void HoanDoiDauSach(DauSach *ds1, DauSach *ds2) {
	DauSach temp = *ds1;
	*ds1 = *ds2;
	*ds2 = temp;
}

void SortTheLoai (NodeDauSach &ds, int q, int r) {
	int i = q;
	int j = r;
	char TheLoai[15];
	strcpy(TheLoai, ds.nodes[(q + r) / 2]->TheLoai);
	do {
		while(strcmp(ds.nodes[i]->TheLoai, TheLoai) < 0) i++;
		while(strcmp(ds.nodes[j]->TheLoai, TheLoai) > 0) j--;
		if (i <= j) {
			HoanDoiDauSach(ds.nodes[i], ds.nodes[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(q < j) {
		SortTheLoai(ds, q, j);
	}
	if(i < r) {
		SortTheLoai(ds, i, r);
	}
}

void SortTenSach (NodeDauSach &ds, int q, int r) {
	int i = q;
	int j = r;
	char TenSach[25];
	strcpy(TenSach, ds.nodes[(q + r) / 2]->TenSach);
	do {
		while(strcmp(ds.nodes[i]->TenSach, TenSach) < 0) i++;
		while(strcmp(ds.nodes[j]->TenSach, TenSach) > 0) j--;
		if (i <= j) {
			HoanDoiDauSach(ds.nodes[i], ds.nodes[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(q < j) {
		SortTenSach(ds, q, j);
	}
	if(i < r) {
		SortTenSach(ds, i, r);
	}
}

void TheLoai_Quick_sort (NodeDauSach &ds, int n) {
	SortTheLoai(ds, 0, n - 1);
}

void SapXepDauSach (NodeDauSach &ds) {
	TheLoai_Quick_sort(ds, ds.n);
	int start = 0;
	int end = 0;
	while(true) {
		end++;
		if (end == ds.n) {
			SortTenSach(ds, start, end - 1);
			break;
		}
		if (strcmp(ds.nodes[end]->TheLoai, ds.nodes[start]->TheLoai) != 0) {
			SortTenSach(ds, start, end - 1);
			start = end;
		}
	}
}

int TongTrang (NodeDauSach ds) {
	int totalPage;
	if (ds.n % 15 == 0) {
		totalPage = ds.n / 15;
	} else if (ds.n % 15 != 0) {
		totalPage = ds.n / 15 + 1;
	}
	
	return totalPage;
}

void ThemDauSach(NodeDauSach &ds) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char ISBN[15];
	char TenSach[25];
	int SoTrang;
	char TacGia[15];
	int NamSB;
	char TheLoai[15];
	int isContinue = 1;
	
	// khung giao dien
	NhapDauSachForm();
	
	SetConsoleTextAttribute(h, 232);
	isContinue = AutoUppercase(ISBN, 15, 53, 8, 1, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	// kiem tra ISBN da ton tai hay chua
	while(Search_info(ds, ISBN) != -1) { // 2 trung => vitri = 2
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		ErrorMessage("ISBN da ton tai", 88, 2, 7);
		SetConsoleTextAttribute(h, 232);
		gotoxy(52, 8);
		cout << "                          ";
		isContinue = AutoUppercase(ISBN, 15, 53, 8, 1, 232);
		if (isContinue == 0) {
			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	
	isContinue = AutoUppercase(TenSach, 25, 53, 10, 2, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	isContinue = OnlyNum(SoTrang, 53, 12, 2, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	isContinue = Name(TacGia, 15, 53, 14, 4, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	isContinue = OnlyNum(NamSB, 57, 16, 4, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	while(NamSB > 1900 + ltm->tm_year) {
		ErrorMessage("Nam xuat ban khong hop le", 82, 2, 7);
		gotoxy(57, 16);
		SetConsoleTextAttribute(h, 232);
		cout << "       ";
		isContinue = OnlyNum(NamSB, 57, 16, 4, 232);
		if (isContinue == 0) {
			SetConsoleTextAttribute(h, 7);
			return;
		}
	}
	
	isContinue = Name(TheLoai, 15, 53, 18, 5, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	SetConsoleTextAttribute(h, 7);
	
	DauSach *dausach = new DauSach(ISBN, TenSach, SoTrang, TacGia, NamSB, TheLoai);
	int isSuccess;
	
	isSuccess = Insert_Item(ds, ds.n, dausach);
	
	if (isSuccess == 1) {
		SuccessMessage("Them thanh cong!", 86, 2, 7);
	} else if (isSuccess == 0) {
		ErrorMessage("Them khong thanh cong!", 84, 2, 7);
	}
}

void PrevPage(int currentPage, int totalPage, NodeDauSach &ds) {
	if (ds.n == 0) {
		XuatTrang(0, 0, ds);
		return;
	}
	currentPage--;
	if (currentPage < 1) {
		currentPage = 1;
	}
	
	XuatTrang(currentPage, totalPage, ds);
}

void NextPage(int currentPage, int totalPage, NodeDauSach &ds) {
	if (ds.n == 0) {
		XuatTrang(0, 0, ds);
		return;
	}
	currentPage++;
	if (currentPage > totalPage) {
		currentPage = totalPage;
	}
	
	XuatTrang(currentPage, totalPage, ds);
}

void XuatTrang(int currentPage, int totalPage, NodeDauSach &ds) {
	if (currentPage == 0 || totalPage == 0) {
		renderDauSach(1, 1, 0, 'x'); // x: xuat
		ErrorMessage("Danh sach rong", 88, 2, 7);
		Nocursortype();
	} else {
		SapXepDauSach(ds);
		
		int start = (currentPage - 1) * 15;
	
		int totalLine;
		if (start + 15 > ds.n) {
			totalLine = ds.n % 15;
		} else totalLine = 15;
		
		renderDauSach(currentPage, totalPage, totalLine, 'x');
		
		int i = 0;
		for (int j = start; j < start + totalLine; j++) {
			gotoxy(10, 8 + i);
			cout << ds.nodes[j]->ISBN;
			
			gotoxy(26, 8 + i);
			cout << ds.nodes[j]->TenSach;
			
			gotoxy(53, 8 + i);
			cout << ds.nodes[j]->SoTrang;
			
			gotoxy(64, 8 + i);
			cout << ds.nodes[j]->TacGia;
			
			gotoxy(80, 8 + i);
			cout << ds.nodes[j]->NamSB;
			
			gotoxy(95, 8 + i);
			cout << ds.nodes[j]->TheLoai;
			
			i++;
		}	
	}
	while(true) {
		char key = getch();
		
		if (key == 27) { //esc
			break;
		}
		
		if (key == 0) { // nhan phim function
			key = getch();
			if (key == 62) { //f4
				ThemDauSach(ds);
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;	
			}
			
			if (key == 63) {
				XoaDauSach(ds);
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
			
			if (key == 64) {
				SuaDauSach(ds);
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
			
			if (key == 65) { // f7: vao danh muc sach
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				gotoxy(17, 2);
				int vitri = SearchDauSach(ds);
				if (vitri == -1) {
					ErrorMessage("Khong tim thay thong tin dau sach", 79, 2, 7);
					int currentPage = TongTrang(ds);
					int totalPage = TongTrang(ds);
					XuatTrang(currentPage, totalPage, ds);
					break;
				} else {
					XuLyDMS(ds.nodes[vitri]->dms, ds.nodes[vitri]->TenSach, ds.nodes[vitri]->ISBN, ds.nodes[vitri]->soluong);
					int currentPage = TongTrang(ds);
					int totalPage = TongTrang(ds);
					XuatTrang(currentPage, totalPage, ds);
					break;
				}
			}
		}
		
		if (key == -32) {
			key = getch();
			if (key == 75) {
				PrevPage(currentPage, totalPage, ds);
				break;
			}
			
			if (key == 77) {
				NextPage(currentPage, totalPage, ds);
				break;
			}
		}
	}
}

void KhoiTaoDauSach(NodeDauSach &ds) { // cho nhap dau sach lien tuc
	int i = ds.n % 15; // i = 0
	while(true) {
		if (i > 14) {
			renderDauSach(ds.n / 15 + 1, ds.n / 15 + 1, 1, 'n');
			i = 0;
		}
		char ISBN[15];
		char TenSach[25];
		int SoTrang;
		char TacGia[15];
		int NamSB;
		char TheLoai[15];
		int isContinue = 1;
		
		isContinue = AutoUppercase(ISBN, 15, 10, 8 + i, 1, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		
		// kiem tra ISBN da ton tai hay chua
		while(Search_info(ds, ISBN) != -1) {
			ErrorMessage("ISBN da ton tai", 88, 2, 7);
			gotoxy(10, 8 + i);
			cout << "               ";
			isContinue = AutoUppercase(ISBN, 15, 10, 8 + i, 1, 7);
			if (isContinue == 0) {
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
		}
		
		isContinue = AutoUppercase(TenSach, 25, 26, 8 + i, 2, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		
		isContinue = OnlyNum(SoTrang, 53, 8 + i, 2, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		isContinue = Name(TacGia, 15, 64, 8 + i, 4, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		isContinue = OnlyNum(NamSB, 80, 8 + i, 4, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		
		// lay ngay thang nam hien tai
		time_t now = time(0);
		tm *ltm = localtime(&now);
		
		while(NamSB > 1900 + ltm->tm_year) {
			ErrorMessage("Nam xuat ban khong hop le", 82, 2, 7);
			gotoxy(80, 8 + i);
			cout << "       ";
			isContinue = OnlyNum(NamSB, 80, 8 + i, 4, 7);
			if (isContinue == 0) {
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
		}
		
		isContinue = Name(TheLoai, 15, 95, 8 + i, 5, 7);
		if (isContinue == 0) {
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		
		DauSach *dausach = new DauSach(ISBN, TenSach, SoTrang, TacGia, NamSB, TheLoai);
		
		int isSuccess = Insert_Item(ds, ds.n, dausach);
		
		if (isSuccess == 0) { // trong truong hop nhap max dau sach
			int currentPage = TongTrang(ds);
			int totalPage = TongTrang(ds);
			XuatTrang(currentPage, totalPage, ds);
			break;
		}
		
		gotoxy(95 + strlen(TheLoai), 8 + i);
		
		char key = getch();
		if (key == 13) { // noi khung va cho nguoi dung nhap tiep
			NoiKhungDauSach(9, 9 + i);
			i++;
		} 
		
		if (key == 27) { // esc: quay ve menu
			break;
		}
		
		if (key == 0) {
			key = getch();
			if (key == 62) { // f4: xem danh sach da nhap
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
		}
	}
}

void HandleDauSach(NodeDauSach &ds) {
	if (Empty(ds)) {
		int isConfirm = Confirm("Ban muon khoi tao danh sach moi khong?");
		switch(isConfirm) {
			case 1: {
				renderDauSach(1, 1, 1, 'n'); // n: nhap
				KhoiTaoDauSach(ds);
				break;
			}
			case 0: {
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				break;
			}
		}	
	} else {
		int currentPage = TongTrang(ds);
		int totalPage = TongTrang(ds);
		XuatTrang(currentPage, totalPage, ds);
	}
}

// Tra cuu thong tin sach
void XuatThongTin(DauSach *dausach, int currentPage, int totalPage) {
	if (currentPage == 0 && totalPage == 0) {
		tracuuthongtin(1, 1, 1);
	
		gotoxy(21, 8);
		cout << dausach->ISBN;
		gotoxy(37, 8);
		cout << dausach->TenSach;
		gotoxy(63, 8);
		cout << dausach->TacGia;
		gotoxy(79, 8);
		cout << dausach->NamSB;
		gotoxy(85, 8);
		cout << dausach->TheLoai;
		
		ErrorMessage("Danh muc sach rong", 86, 2, 7);
		Nocursortype();
	} else {
		Nocursortype();
		int start = (currentPage - 1) * 15;
	
		int totalLine;
		if (start + 15 > TongSach(dausach->dms)) {
			totalLine = TongSach(dausach->dms) % 15;
		} else totalLine = 15;
		
		tracuuthongtin(totalLine, currentPage, totalPage);
	
		gotoxy(21, 8);
		cout << dausach->ISBN;
		gotoxy(37, 8);
		cout << dausach->TenSach;
		gotoxy(63, 8);
		cout << dausach->TacGia;
		gotoxy(79, 8);
		cout << dausach->NamSB;
		gotoxy(85, 8);
		cout << dausach->TheLoai;
		
		int i = 0;
		int j = 0;
		PTRSach p;
		for (p = dausach->dms; p != NULL; p = p->next) {
			if (i >= start) {
				gotoxy(16, 13 + j);
				cout << p->sach.MaSach;
				
				gotoxy(37, 13 + j);
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
				
				gotoxy(53, 13 + j);
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


void TraCuuThongTin(NodeDauSach ds) {
	tracuuthongtin(1, 1, 1);
	int vitri = -1;
	int totalPage;
	int currentPage;
	while(true) {
		char key = getch();
		if (key == 0) {
			key = getch();
			if (key == 59) { // f1
				char TenSach[25];
				int dem = 0;
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				CharForm("NHAP TEN SACH");
				SetConsoleTextAttribute(h, 232);
				AutoUppercase(TenSach, 25, 55, 13, 5, 232);
				SetConsoleTextAttribute(h, 7);
				//vitri = SearchByName(ds, TenSach);
				for (int i = 0; i < ds.n; i++) {
					if (strcmp(ds.nodes[i]->TenSach, TenSach) == 0) {
						vitri = i;
						dem++;
					}
				}
				if (dem > 1) {
					string array[dem];
					int k = 0;
					for (int i = 0; i < ds.n; i++) {
						if (strcmp(TenSach, ds.nodes[i]->TenSach) == 0) {
							array[k] = ConvertToString(ds.nodes[i]->ISBN, strlen(ds.nodes[i]->ISBN));
							array[k] += " ";
							array[k] += ConvertToString(ds.nodes[i]->TenSach, strlen(ds.nodes[i]->TenSach));
							k++;
						}
					}
					
					int target = ChildMenu(array, dem, "VUI LONG CHON DAU SACH");
					char isbn[15];
					Copy(isbn, array[target - 1]);
					strtok(isbn, " ");
					vitri = Search_info(ds, isbn);
				}
				if (vitri == -1) {
					ErrorMessage("Khong tim thay thong tin", 83, 2, 7);
					TraCuuThongTin(ds);
				} else {
					totalPage = TongTrangDMS(ds.nodes[vitri]->dms);
					currentPage = totalPage;
					XuatThongTin(ds.nodes[vitri], currentPage, totalPage);
				}
			}
			
			if (key == 60) {
				int currentPage = TongTrang(ds);
				int totalPage = TongTrang(ds);
				XuatTrang(currentPage, totalPage, ds);
				TraCuuThongTin(ds);
				break;
			}
		}
		
		if (key == 27) {
			break;
		}
		
		if (key == -32) {
			key = getch();
			if (key == 75) {
				if (vitri != -1 && ds.nodes[vitri]->soluong != 0) {
					currentPage--;
					if (currentPage < 1) {
						currentPage = 1;
					}
					totalPage = TongTrangDMS(ds.nodes[vitri]->dms);
					XuatThongTin(ds.nodes[vitri], currentPage, totalPage);
				}
			}
			
			if (key == 77) {
				if (vitri != -1 && ds.nodes[vitri]->soluong != 0) {
					totalPage = TongTrangDMS(ds.nodes[vitri]->dms);
					currentPage++;
					if (currentPage > totalPage) {
						currentPage = totalPage;
					}
					XuatThongTin(ds.nodes[vitri], currentPage, totalPage);
				}
			}
		}
	}
}

// Top 10 sach duoc muon nhieu nhat
void heapify (NodeDauSach &ds, int n, int i) {
	int largest = i;
	int left = 2 * i + 1; // nut trai
	int right = 2 * i + 2; // nut phai
	
	if (left < n && ds.nodes[left]->soluotmuon > ds.nodes[largest]->soluotmuon) {
		largest = left;
	}
	if (right < n && ds.nodes[right]->soluotmuon > ds.nodes[largest]->soluotmuon) {
		largest = right;
	}
	
	if (largest != i) {
		HoanDoiDauSach(ds.nodes[i], ds.nodes[largest]);
		heapify(ds, n, largest);
	}
}

void Heap_sort (NodeDauSach &ds, int n) {
	// n / 2 - 1 la so nut khac nut la
	// Tao mot max heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(ds, n, i);
	}
	// heapsort
	for (int i = n - 1; i >= 0; i--) {
		HoanDoiDauSach(ds.nodes[0], ds.nodes[i]);
		
		heapify(ds, i, 0);
	}
}

void Top10 (NodeDauSach ds) {
	Top10Book();
	Heap_sort(ds, ds.n); // tang dan
	int dem = 0;
	for (int i = ds.n - 1; i >= 0; i--) { // xuat nguoc 10 phan tu lon nhat
		if (dem == 10) {
			break;
		}
		gotoxy(14, 8 + dem);
		cout << ds.nodes[i]->ISBN;
		gotoxy(30, 8 + dem);
		cout << ds.nodes[i]->TenSach;
		gotoxy(56, 8 + dem);
		cout << ds.nodes[i]->TacGia;
		gotoxy(72, 8 + dem);
		cout << ds.nodes[i]->NamSB;
		gotoxy(78, 8 + dem);
		cout << ds.nodes[i]->TheLoai;
		gotoxy(100, 8 + dem);
		cout << ds.nodes[i]->soluotmuon;
		dem++;
	}
	while (true) {
		char key = getch();
		if (key == 27) { //esc
			break;
		}
	}
}
