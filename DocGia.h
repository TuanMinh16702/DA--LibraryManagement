#include <iostream>
#include <ostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX_DOC_GIA 1000
#define stacksize 500
using namespace std;

// KHAI BAO 
struct DocGia{
	int MATHE;
	char ho[25];
	char ten[11];
	int phai;
	int trangthai; // 1: hoat dong 0: Khoa
	DS_MuonTra muontra;
};
struct nodeDocGia{
	DocGia docgia;
	nodeDocGia *right= NULL;
	nodeDocGia *left= NULL;
};
typedef struct nodeDocGia *tree;


// THUAT TOAN
void khoitao(tree &root){
	root = NULL;
}

int random(int start, int end){
	return start + rand() % (end + 1 - start);
}

tree timkiem(tree root, int mathe);
int TongDocGia(tree root);

int XuLyMaThe(tree root) {
	if (root == NULL) {
		int mathe = 50000;
		return mathe;
	} else {
		int tong = TongDocGia(root);
		int mathe;
		if (tong % 2 == 0) {
			mathe = random(9999, 49999);
			tree t = NULL;
			t = timkiem(root, mathe);
			while(t != NULL) {
				mathe = random(9999, 49999);
				t = NULL;
				t = timkiem(root, mathe);
			}
		} else {
			mathe = random(50001, 99999);
			tree t = NULL;
			t = timkiem(root, mathe);
			while(t != NULL) {
				mathe = random(50001, 99999);
				t = NULL;
				t = timkiem(root, mathe);
			}
		}
		return mathe;
	}
	
}
void them(tree &p , DocGia &info){
	if(p == NULL){ // cay khong ton tai phan tu 
		tree q = new nodeDocGia;
		q->docgia = info;
		q->left = NULL;
		q->right= NULL;
		p = q;
	}else{ // cay co ton tai phan tu 
		if(info.MATHE < p->docgia.MATHE){
			them(p->left, info);
		}else if(info.MATHE> p->docgia.MATHE){
			them(p->right, info);
		}
	}
}

int TongDocGia(tree root){
	tree stack[stacksize];
	tree p = root;
	int sp = -1; // khoi stack rong
	int tong = 0;
	do{
		while(p != NULL){
			stack[++sp] = p;
			p= p->left;
		}
		if(sp != -1){
			p = stack[sp--];
			tong++;
			p = p->right;
		}else{
			break;
		}
	}while(1);
	
	return tong;
}
void xoaCase3(tree &r, tree &rp){
	if(r->left != NULL){
		xoaCase3(r->left, rp);
	}else{
		rp->docgia = r->docgia;
		rp = r;
		r = rp->right;
	}
}
void xoa(tree &t, int mathe){
	if(t == NULL){
		ErrorMessage("Khong the xoa", 88, 2, 7);
	}else{
		tree rp;
		if(mathe < t->docgia.MATHE){
			xoa(t->left, mathe);
		}else if(mathe > t->docgia.MATHE){
			xoa(t->right, mathe);
		}else{
			rp = t;
			if(rp->right == NULL){
				t = rp->left;
			}else if(rp->left== NULL){
				t = rp->right;
			}else{
				xoaCase3(rp->right, rp);
			}
			delete rp;
		}
	}
}
tree timkiem(tree root, int mathe){
	tree p;
	p = root;
	while(p != NULL && p->docgia.MATHE != mathe){
		if(mathe < p->docgia.MATHE){
			p = p->left;
		}else{
			p = p->right;
		}
	}
	return p;
}

void ShowDocGia (tree root, char MaThe[]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	draw(19, 75, 23, 5, 7);
	VeKhungDocGia(0, 23, 5);
	
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	int j = 0;
	do{
		while(p != NULL){
			stack[++sp] = p;
			p = p->left;
		}
		if(sp != -1){
			p = stack[sp--];
			
			char str[5];
			itoa(p->docgia.MATHE, str, 10);
			char *pointer = strstr(str, MaThe);
			if(pointer) {
				if (j > 14) { // LON HON 15 DONG THI DUNG XUAT
					break;
				}
				
				SetConsoleTextAttribute(h, 7);
				NoiKhungDocGia(23, 8 + j);
				
				gotoxy(24, 8 + j);
				cout << p->docgia.MATHE;
				
				gotoxy(33, 8 + j);
				cout << p->docgia.ho;
				
				gotoxy(60, 8 + j);
				cout << p->docgia.ten;
				
				if (p->docgia.phai == 0) {
					gotoxy(77, 8 + j);
					cout << "NAM";
				} else if (p->docgia.phai == 1) {
					gotoxy(77, 8 + j);
					cout << "NU";
				}
				
				if (p->docgia.trangthai == 0) {
					gotoxy(89, 8 + j);
					SetConsoleTextAttribute(h, 12);
					cout << "KHOA";
					SetConsoleTextAttribute(h, 7);
				} else if (p->docgia.trangthai == 1) {
					gotoxy(87, 8 + j);
					SetConsoleTextAttribute(h, 10);
					cout << "HOAT DONG";
					SetConsoleTextAttribute(h, 7);
				}
				
				j++;
			}
			
			p = p->right;
		} else {
			break;
		}
	}while(1);
	
	SetConsoleTextAttribute(h, 232);
}

tree SearchDocGia(tree root) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(10, 4);
	cout << "**Nhan ESC de ngung tim kiem**";
	gotoxy(19, 2);
	SetConsoleTextAttribute(h, 232);
	char MaThe[10];
	int i = 0;
	while(true) {
		Showcursortype();
		char key = getch();
		
		if (key == 27) {
			int isConfirm = Confirm("Ban co muon dung tim kiem khong?");
			
			if (isConfirm == 1) {
				tree p = NULL;
				return p;
			} else if (isConfirm == 0) {
				gotoxy(19, 2);
				SetConsoleTextAttribute(h, 232);
				cout << "          ";
				SetConsoleTextAttribute(h, 7);
				ShowDocGia(root, "");
				Showcursortype();
				gotoxy(19, 2);
				SetConsoleTextAttribute(h, 7);
				return SearchDocGia(root);
			}
		}
		
		if (key == 8 && strlen(MaThe) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			MaThe[i] = '\0';
			gotoxy(19 + i, 2);
			cout << " ";
			gotoxy(19 + i, 2);
			ShowDocGia(root, MaThe);
			gotoxy(19 + i, 2);
			continue;
		}
		
		if(key >= 48 && key <= 57) {
			if (strlen(MaThe) >= 10) {
				continue;
			}
			
			MaThe[i] = char(key);
			cout << MaThe[i];
			i++;
			MaThe[i + 1] = '\0';
			ShowDocGia(root, MaThe);
			gotoxy(19 + i, 2);
		}
		
		if (key == 13) {
			SetConsoleTextAttribute(h, 7);
			if(strlen(MaThe) == 0) {
				tree p = NULL;
				return p;
			} else {
				tree stack[stacksize];
				tree p = root;
				int sp = -1;
				int j = 0;
				do {
					while(p != NULL){
						stack[++sp] = p;
						p = p->left;
					}
					if(sp != -1){
						p = stack[sp--];
						
						char str[5];
						itoa(p->docgia.MATHE, str, 10);
						if (strcmp(str, MaThe) == 0) {
							return p;
							break;
						}
						
						p = p->right;
					} else {
						break;
					}
				} while(1);
				
				tree q = NULL;
				return q;
			}
		}
	}
}

void ToArray(tree root, DocGia a[MAX_DOC_GIA]){
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	int tong = 0;
	do{
		while(p != NULL){
			stack[++sp] = p;
			p = p->left;
		}
		if(sp != -1){
			p = stack[sp--];
			
			a[tong] = p->docgia;
			tong++;
			
			p = p->right;
		} else {
			break;
		}
	}while(1);
}

void HoanDoiDocGia (DocGia &dg1, DocGia &dg2) {
	DocGia temp = dg1;
	dg1 = dg2;
	dg2 = temp;
}

void SortTen (DocGia a[], int q, int r) {
	int i = q;
	int j = r;
	char Ten[11];
	strcpy(Ten, a[(q + r) / 2].ten);
	do {
		while(strcmp(a[i].ten, Ten) < 0) i++;
		while(strcmp(a[j].ten, Ten) > 0) j--;
		if (i <= j) {
			HoanDoiDocGia(a[i], a[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(q < j) {
		SortTen(a, q, j);
	}
	if(i < r) {
		SortTen(a, i, r);
	}
}

void SortHo (DocGia a[], int q, int r) {
	int i = q;
	int j = r;
	char Ho[25];
	strcpy(Ho, a[(q + r) / 2].ho);
	do {
		while(strcmp(a[i].ho, Ho) < 0) i++;
		while(strcmp(a[j].ho, Ho) > 0) j--;
		if (i <= j) {
			HoanDoiDocGia(a[i], a[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(q < j) {
		SortTen(a, q, j);
	}
	if(i < r) {
		SortTen(a, i, r);
	}
}

void Ten_Quick_sort (DocGia a[], int n) {
	SortTen(a, 0, n - 1);
}

void sapxepten(tree root, DocGia a[MAX_DOC_GIA]){
	int tong = TongDocGia(root);
	
	Ten_Quick_sort(a, tong);
	int start = 0;
	int end = 0;
	while(true) {
		end++;
		if (end == tong) {
			SortHo(a, start, end - 1);
			break;
		}
		if (strcmp(a[start].ten, a[end].ten) != 0) {
			SortHo(a, start, end - 1);
			start = end;
		}
	}
}

int TongTrangDocGia (tree root) {
	int totalPage;
	if (TongDocGia(root) % 15 == 0) {
		totalPage = TongDocGia(root) / 15;
	} else if (TongDocGia(root) % 15 != 0) {
		totalPage = TongDocGia(root) / 15 + 1;
	}
	return totalPage;
}

void ThemDocGia(tree &root) {
	DocGia docgia;
	NhapDocGiaForm();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(h, 232);
	docgia.MATHE = XuLyMaThe(root);
	gotoxy(51, 8);
	cout << docgia.MATHE;
	
	docgia.trangthai = 1;
	gotoxy(55, 17);
	SetConsoleTextAttribute(h, 234);
	cout << "HOAT DONG";
	SetConsoleTextAttribute(h, 232);
	
	int isContinue = 1;
	fflush(stdin);
	isContinue = Name(docgia.ho, 25, 47, 10, 2, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	isContinue = Name(docgia.ten, 15, 48, 12, 1, 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	fflush(stdin);
	isContinue = OnlyZeroOne(docgia.phai, 54, 14, 3, "NAM", "NU", 232);
	if (isContinue == 0) {
		SetConsoleTextAttribute(h, 7);
		return;
	}
	SetConsoleTextAttribute(h, 7);
	
	them(root, docgia);
	SuccessMessage("Them thanh cong!", 86, 2, 7);
}

void XoaDocGia(tree &root) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	tree t = NULL;
	gotoxy(19, 2);
	t = SearchDocGia(root);
	if (t != NULL) {
		draw(7, 40, 40, 10, 7);
		int isConfirm = Confirm("BAN CHAN CHAN MUON XOA?");
		switch(isConfirm) {
			case 1:{
				if (t->docgia.muontra.total == 0) {
					//xoa ds muon tra
					ClearMuonTra(t->docgia.muontra);
					xoa(root, t->docgia.MATHE);
					SuccessMessage("Da xoa thanh cong", 87, 2, 7);
				} else {
					ErrorMessage("Doc gia van con dang muon hoac mat sach", 77, 2, 7);
				}
				break;
			}
			case 0: {
				break;
			}
		}
	} else if (t == NULL) {
		ErrorMessage("Khong tim thay thong tin doc gia", 80, 2, 7);
	}
}

void MenuChinhSuaDG(DocGia &docgia) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	MenuChinhSuaDGUI();
	
	gotoxy(24, 26);
	cout << docgia.MATHE;
	
	gotoxy(33, 26);
	cout << docgia.ho;
	
	gotoxy(60, 26);
	cout << docgia.ten;
	
	if (docgia.phai == 0) {
		gotoxy(77, 26);
		cout << "NAM";
	} else if (docgia.phai == 1) {
		gotoxy(77, 26);
		cout << "NU";
	}
	
	if (docgia.trangthai == 0) {
		gotoxy(89, 26);
		SetConsoleTextAttribute(h, 12);
		cout << "KHOA";
		SetConsoleTextAttribute(h, 7);
	} else if (docgia.trangthai == 1) {
		gotoxy(87, 26);
		SetConsoleTextAttribute(h, 10);
		cout << "HOAT DONG";
		SetConsoleTextAttribute(h, 7);
	}
	
	string array[4] = {"HO" ,"TEN", "GIOI TINH", "KET THUC CHINH SUA"};
	int target = ChildMenu(array, 4, "CHON THONG TIN CAN CHINH SUA");
	int isContinue = 1;
	switch(target) {
		case 1:{
			char Ho[25];
			CharForm("NHAP HO");
			SetConsoleTextAttribute(h, 232);
			isContinue = Name(Ho, 25, 55, 13, 2, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDG(docgia);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			strcpy(docgia.ho, Ho);
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 3, 7);
			MenuChinhSuaDG(docgia);
			break;
		}
		case 2:{
			char Ten[11];
			CharForm("NHAP TEN");
			SetConsoleTextAttribute(h, 232);
			isContinue = Name(Ten, 11, 55, 13, 1, 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDG(docgia);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			strcpy(docgia.ten, Ten);
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 3, 7);
			MenuChinhSuaDG(docgia);
			break;
		}
		case 3:{
			int phai;
			NumberForm("NHAP GIOI TINH");
			SetConsoleTextAttribute(h, 232);
			isContinue = OnlyZeroOne(phai, 52, 13, 3, "NAM", "NU", 232);
			if (isContinue == 0) {
				SetConsoleTextAttribute(h, 7);
				MenuChinhSuaDG(docgia);
				break;
			}
			SetConsoleTextAttribute(h, 7);
			docgia.phai = phai;
			SuccessMessage("Chinh sua thong tin thanh cong", 80, 3, 7);
			MenuChinhSuaDG(docgia);
			break;
		}
		case 4: {
			SuccessMessage("Da luu thong tin chinh sua", 82, 3, 7);
			break;
		}
	}
}

void HieuChinhDocGia(tree &root) { // TIM KIEM DE HIEU CHINH
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	tree t = NULL;
	gotoxy(19, 2);
	t = SearchDocGia(root);
	if (t != NULL) {
		MenuChinhSuaDG(t->docgia);
	} else if (t == NULL) {
		ErrorMessage("Khong tim thay thong tin doc gia", 80, 2, 7);
	}
}

//XU LY GIAO DIEN

void XuatTrangDocGia(NodeDauSach ds, int currentPage, int totalPage, tree &root, char &SortBy) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (currentPage == 0 || totalPage == 0) {
		renderDocGia(1, 1, 0, 'x');
		ErrorMessage("Danh sach rong", 88, 2, 7);
		Nocursortype();
	} else {  // XUAT TRANG CUOI
		int start = (currentPage - 1) * 15;
	
		int totalLine;
		
		int tong = TongDocGia(root);
		if (start + 15 > tong) {
			totalLine = tong % 15;
		} else totalLine = 15;
		
		renderDocGia(currentPage, totalPage, totalLine, 'x');
		DocGia a[tong];
		ToArray(root, a);
		if (SortBy == 't') {
			sapxepten(root, a);
		}
		int i = 0;  //KIEM SOAT HANG 
		for (int j = start; j < start + totalLine; j++) { // J LA KIEM TRA INDEX
			gotoxy(24, 8 + i);
			cout << a[j].MATHE;
			
			gotoxy(33, 8 + i);
			cout << a[j].ho;
			
			gotoxy(60, 8 + i);
			cout << a[j].ten;
			
			if (a[j].phai == 0) {
				gotoxy(77, 8 + i);
				cout << "NAM";
			} else if (a[j].phai == 1) {
				gotoxy(77, 8 + i);
				cout << "NU";
			}
			
			if (a[j].trangthai == 0) {
				gotoxy(89, 8 + i);
				SetConsoleTextAttribute(h, 12);
				cout << "KHOA";
				SetConsoleTextAttribute(h, 7);
			} else if (a[j].trangthai == 1) {
				gotoxy(87, 8 + i);
				SetConsoleTextAttribute(h, 10);
				cout << "HOAT DONG";
				SetConsoleTextAttribute(h, 7);
			}
			
			i++;
		}
	}
	while(true) {
		char key = getch();
		
		if (key == 27) {
			break;
		}
		
		if (key == 0) {
			key = getch();
			if (key == 59) {
				SortBy = 'm';
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
			if (key == 60) {
				SortBy = 't';
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
			
			if (key == 62) {
				ThemDocGia(root);
				int currentPage = TongTrangDocGia(root);
				int totalPage = TongTrangDocGia(root);
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;	
			}
			
			if (key == 63) {
				XoaDocGia(root);
				int currentPage = TongTrangDocGia(root);
				int totalPage = TongTrangDocGia(root);
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
			
			if (key == 64) {
				HieuChinhDocGia(root);
				int currentPage = TongTrangDocGia(root);
				int totalPage = TongTrangDocGia(root);
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
			
			if (key == 65) {
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				tree t = NULL;
				gotoxy(19, 2);
				t = SearchDocGia(root);
				if (t != NULL) {
					XuLyMuonTraSach(ds, t->docgia.muontra, t->docgia.MATHE, t->docgia.ho, t->docgia.ten, t->docgia.phai, t->docgia.trangthai);
					int currentPage = TongTrangDocGia(root);
					int totalPage = TongTrangDocGia(root);
					XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
					break;
				} else if (t == NULL) {
					ErrorMessage("Khong tim thay thong tin doc gia", 80, 2, 7);
					int currentPage = TongTrangDocGia(root);
					int totalPage = TongTrangDocGia(root);
					XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
					break;
				}
			}
		}
		
		if (key == -32) {
			key = getch();
			if (key == 75) {
				currentPage--;
				if (currentPage < 1) {
					currentPage = 1;
				}
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
			
			if (key == 77) {
				currentPage++;
				if (currentPage > totalPage) {
					currentPage = totalPage;
				}
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
		}
	}
}

void KhoiTaoDocGia(NodeDauSach ds, tree &root, char &SortBy){
	int i = TongDocGia(root) % 15;
	while(true) {
		if (i > 14) {
			renderDocGia(TongDocGia(root) / 15 + 1, TongDocGia(root) / 15 + 1, 1, 'n');
			i = 0;
		}
		
		DocGia docgia;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		
		docgia.trangthai = 1;
		gotoxy(87, 8 + i);
		SetConsoleTextAttribute(h, 10);
		cout << "HOAT DONG";
		SetConsoleTextAttribute(h, 7);
		
		docgia.MATHE = XuLyMaThe(root);
		gotoxy(24, 8 + i);
		cout << docgia.MATHE;
		
		int isContinue = 1;
		isContinue = Name(docgia.ho, 25, 33, 8 + i, 2, 7);
		if (isContinue == 0) {
			int currentPage = TongTrangDocGia(root);
			int totalPage = TongTrangDocGia(root);
			XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
			break;
		}
		isContinue = Name(docgia.ten, 15, 60, 8 + i, 1, 7);
		if (isContinue == 0) {
			int currentPage = TongTrangDocGia(root);
			int totalPage = TongTrangDocGia(root);
			XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
			break;
		}
		isContinue = OnlyZeroOne(docgia.phai, 77, 8 + i, 3, "NAM", "NU", 7);
		if (isContinue == 0) {
			int currentPage = TongTrangDocGia(root);
			int totalPage = TongTrangDocGia(root);
			XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
			break;
		}
		
		them(root, docgia);
		
		char key = getch();
		
		if(key == 13) {
			NoiKhungDocGia(23, 9 + i);
			i++;
		}
		
		if (key == 27) {
			break;
		} 
		
		if (key == 0) {
			key = getch();
			if (key == 62) {
				int currentPage = TongTrangDocGia(root);
				int totalPage = TongTrangDocGia(root);
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
		}
	}
}

void XuLyDocGia (NodeDauSach ds, tree &root) {
	char SortBy = 'm';
	if (root == NULL) {
		int isConfirm = Confirm("Ban muon khoi tao danh sach moi khong?");
		switch(isConfirm) {
			case 1: {
				renderDocGia(1, 1, 1, 'n');
				KhoiTaoDocGia(ds, root, SortBy);
				break;
			}
			case 0: {
				int currentPage = TongTrangDocGia(root);
				int totalPage = TongTrangDocGia(root);
				XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
				break;
			}
		}
	} else {
		int currentPage = TongTrangDocGia(root);
		int totalPage = TongTrangDocGia(root);
		XuatTrangDocGia(ds, currentPage, totalPage, root, SortBy);
	}
}

// Doc gia muon sach qua han
struct DGQuaHan {
	int MATHE;
	char ho[25];
	char ten[11];
	char MaSach[20];
	char TenSach[25];
	int TongNgayMuon = 1;
};

void HoanDoiMuonTra (DGQuaHan &dg1,  DGQuaHan &dg2) {
	DGQuaHan temp = dg1;
	dg1 = dg2;
	dg2 = temp;
}

void SortTongNgayMuon (DGQuaHan array[], int q, int r) {
	int i = q;
	int j = r;
	char TNM = array[(q + r) / 2].TongNgayMuon;
	do {
		while(array[i].TongNgayMuon > TNM) i++;
		while(array[j].TongNgayMuon < TNM) j--;
		if (i <= j) {
			HoanDoiMuonTra(array[i], array[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(q < j) {
		SortTongNgayMuon(array, q, j);
	}
	if(i < r) {
		SortTongNgayMuon(array, i, r);
	}
}

void TongNgayMuon_Quick_sort (DGQuaHan array[], int n) {
	SortTongNgayMuon(array, 0, n - 1);
}

int TongDGQH (tree root) {
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	int tong = 0;
	do{
		while(p != NULL){
			stack[++sp] = p;
			p = p->left;
		}
		if(sp != -1){
			p = stack[sp--];
			
			NodeMT q;
			for (q = p->docgia.muontra.First; q != NULL; q = q->next){
				if (q->muontra.TongNgayMuon > 7 && (q->muontra.TrangThai == 0 || q->muontra.TrangThai == 2)) {
					tong++;
				}
			}
			
			p = p->right;
		} else {
			break;
		}
	}while(1);
	
	return tong;
}

int TongTrangDGQH (tree root) {
	int tong = TongDGQH(root);
	int totalPage;
	if (tong % 15 == 0) {
		totalPage = tong / 15;
	} else if (tong % 15 != 0) {
		totalPage = tong / 15 + 1;
	}
	
	return totalPage;
}

void DocGiaQuaHan(NodeDauSach ds, tree &root, int currentPage, int totalPage) {
	if (currentPage == 0 || totalPage == 0) {
		docgiaquahan(1, 1, 1);
	} else {
		int index = 0;
		int tong = TongDGQH(root);
		int start = (currentPage - 1) * 15;
	
		int totalLine;
		if (start + 15 > tong) {
			totalLine = tong % 15;
		} else totalLine = 15;
		
		docgiaquahan(totalLine, currentPage, totalPage);
		
		DGQuaHan array[tong];
		tree stack[stacksize];
		tree p = root;
		int sp = -1;
		do{
			while(p != NULL){
				stack[++sp] = p;
				p = p->left;
			}
			if(sp != -1){
				p = stack[sp--];
				
				NodeMT q;
				for (q = p->docgia.muontra.First; q != NULL; q = q->next){
					if (q->muontra.TongNgayMuon > 7 && (q->muontra.TrangThai == 0 || q->muontra.TrangThai == 2)) {
						array[index].MATHE = p->docgia.MATHE;
						strcpy(array[index].ho, p->docgia.ho);
						strcpy(array[index].ten, p->docgia.ten);
						strcpy(array[index].MaSach, q->muontra.MaSach);
						array[index].TongNgayMuon = q->muontra.TongNgayMuon;
						
						char *isbn;
						char ms[20];
						strcpy(ms, q->muontra.MaSach);
						isbn = strtok(ms, "-");
						
						for (int i = 0; i < ds.n; i++) {
							if(strcmp(ds.nodes[i]->ISBN, isbn) == 0) {
								strcpy(array[index].TenSach, ds.nodes[i]->TenSach);
							}
						}
						
						index++;
					}
				}
				
				p = p->right;
			} else {
				break;
			}
		}while(1);
		
		TongNgayMuon_Quick_sort(array, index);
		int j = 0;
		for (int i = start; i < start + totalLine; i++) {
			gotoxy(10, 8 + j);
			cout << array[i].MATHE;
			
			gotoxy(19, 8 + j);
			cout << array[i].ho;
			
			gotoxy(46, 8 + j);
			cout << array[i].ten;
			
			gotoxy(59, 8 + j);
			cout << array[i].MaSach;
			
			gotoxy(80, 8 + j);
			cout << array[i].TenSach;
			
			gotoxy(108, 8 + j);
			cout << array[i].TongNgayMuon;
			j++;
		}
	}
	
	while(true) {
		char key = getch();
		if (key == 27) {
			break;
		}
		
		if (key == -32) {
			key = getch();
			
			if (key == 75) {
				currentPage--;
				if (currentPage < 1) {
					currentPage = 1;
				}
				totalPage = TongTrangDGQH(root);
				DocGiaQuaHan(ds, root, currentPage, totalPage);
				break;
			}
			
			if (key == 77) {
				totalPage = TongTrangDGQH(root);
				currentPage++;
				if (currentPage > totalPage) {
					currentPage = totalPage;
				}
				DocGiaQuaHan(ds, root, currentPage, totalPage);
				break;
			}
		}
	}
}
