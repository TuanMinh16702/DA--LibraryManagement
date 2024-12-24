#include <iostream>
#include <ctime>
using namespace std;
// Cau truc ngay
struct date{
	int ngay;
	int thang;
	int nam;
};

int TongSoNgay(date x){
	int day= 0;
	for(int i = 1; i < x.nam; i++){
		if( (i % 400 == 0) ){
			day = day + 366;
		}else if(i % 4 == 0 && i % 100 != 0){
			day = day + 366;
		}else{
			day = day + 365;
		}
	}
	for(int i = 1; i < x.thang; i++){
		switch(i)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:{
			day+=31;
			break;
		}
		case 4: case 6: case 9: case 11:{
			day+=30;
			break;
		}
		case 2:{
			if( (x.nam % 4 == 0 && x.nam % 100 != 0) || (x.nam % 400 == 0) ){
				day+= 29;
			}else{
				day+=28;
			}
			break;
		}
			
		}
	}
	day = day + x.ngay -1 ;
	return day;
}
int GetCurrentDate(){ // lay tong so ngay tu 1/1/1
	int t;
	int day = 0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
    
    for(int i = 1; i < ltm->tm_year + 1900 ; i++){ // lay nam
    	if(i % 400 == 0 || (i % 4 == 0 && i %100 != 0)){
    		day = day + 366;
		}else{
			day = day + 365;
		}
	}
	// lay thang va ngay
	for(int i = 1; i < ltm->tm_mon + 1; i++){
		switch(i){
			case 2:{
				if(ltm->tm_year % 400 == 0 || (ltm->tm_year % 4 == 0 && ltm->tm_year%100 != 0)){
    				day = day + 29;
				}else{
					day = day + 28;
				}		
				break;
			}
			case 1: 
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:{
				day = day + 31;
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11:{
				day = day + 30;
				break;
			}
		}
	}
	day = day + ltm->tm_mday -1 ;
	return day;
}

int ChenhLechNgay (date x) { // LAY NGAY HIEN TAI - NGAY MUON
	int CurrentDate = GetCurrentDate();
	int NgayMuon = TongSoNgay(x);
	return CurrentDate - NgayMuon + 1;
}

int ChenhLechGiua2Ngay (date ngaymuon, date ngaytra) {  // LAY 2 NGAY TRU NHAU
	int NgayMuon = TongSoNgay(ngaymuon);
	int NgayTra = TongSoNgay(ngaytra);
	return NgayTra - NgayMuon + 1;
}

// Cau truc muon tra
struct MuonTra {
	char MaSach[20];
	date NgayMuon;
	date NgayTra;
	int TrangThai = 0; // 0: Dang muon 1: Da tra 2: Mat Sach
	int TongNgayMuon = 1; //Xu ly luc tai file tu .text len cpp (Ngay hien tai - ngay muon)
};

struct NodeMuonTra {
	MuonTra muontra;
	NodeMuonTra *prev;
	NodeMuonTra *next;
};

struct DS_MuonTra {
	int total = 0;
	NodeMuonTra *First = NULL;
	NodeMuonTra *Last = NULL;
};

typedef NodeMuonTra *NodeMT;

int Empty(DS_MuonTra dsmt) {
	return (dsmt.First == NULL ? true : false);
}

void ClearMuonTra (DS_MuonTra &dsmt) {
	NodeMT p;
	while (dsmt.First != NULL) {
		p = dsmt.First;
		dsmt.First = dsmt.First->next;
		delete p;
	}
}

void themcuoi(DS_MuonTra &dsmt, MuonTra mt){
	NodeMT p = new NodeMuonTra;
	p->muontra = mt;
	p->next = NULL;
	p->prev = NULL;
	if(dsmt.First == NULL){
		dsmt.First = p;
		dsmt.Last = p;
	} else {
		dsmt.Last->next = p;  // tao lien ket tiep theo
		p->prev = dsmt.Last;  // tao lien ket phia truoc
		dsmt.Last = p;
	}
}

int TongMuonTra (DS_MuonTra dsmt) {
	NodeMT p;
	int tong = 0;
	if (Empty(dsmt)){
		return tong;
	} else {
		p = dsmt.First;
		for (; p != NULL; p=p->next) {
			tong++;
		}
		return tong;
	}
} 

int TongTrangMT (DS_MuonTra dsmt) {
	int totalPage;
	int tong  = TongMuonTra(dsmt);
	if (tong % 10 == 0) {
		totalPage = tong / 10;
	} else if (tong % 10 != 0) {
		totalPage = tong / 10 + 1;
	}
	
	return totalPage;
}

void ShowSach(NodeDauSach ds, char MaSach[]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();	
	draw(21, 102, 10, 4, 7);
	VeKhungDMS(0, 34, 5);
	int j = 0;
	for (int  k = 0; k < ds.n; k++) {
		PTRSach p;
		for (p = ds.nodes[k]->dms; p != NULL; p = p->next) {
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
}

PTRSach TimSachDeMuon (NodeDauSach ds) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(10, 3);
	cout << "**Nhan ESC de ngung tim kiem**";
	char MaSach[20];
	ShowSach(ds, "");
	gotoxy(20, 1);
	int i = 0;
	while(true) {
		SetConsoleTextAttribute(h, 232);
		Showcursortype();
		fflush(stdin);
		char key = getch();
		
		if (key == 27) {
			int isConfirm = Confirm("Ban co muon dung tim kiem khong?");
			
			if (isConfirm == 1) {
				PTRSach p = NULL;
				return p;
			} else if (isConfirm == 0) {
				gotoxy(20, 1);
				SetConsoleTextAttribute(h, 232);
				cout << "                    ";
				SetConsoleTextAttribute(h, 7);
				return TimSachDeMuon(ds);
			}
		}
		
		if (key == 8 && strlen(MaSach) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			MaSach[i] = '\0';
			gotoxy(20 + i, 1);
			cout << " ";
			gotoxy(20 + i, 1);
			ShowSach(ds, MaSach);
			gotoxy(20 + i, 1);
			continue;
		}
		
		if(key >= 48 && key <= 57 || key >= 65 && key <= 90 || key >= 97 && key <= 122 || key == 45) {
			if (strlen(MaSach) >= 20) {
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
			ShowSach(ds, MaSach);
			gotoxy(20 + i, 1);
		}
		
		if (key == 13) {
			if(strlen(MaSach) == 0) {
				PTRSach p = NULL;
				return p;
			} else {
				PTRSach p;
				for (int k = 0; k < ds.n; k++) {
					for (p = ds.nodes[k]->dms; p != NULL; p = p->next) {
						if (strcmp(p->sach.MaSach, MaSach) == 0){
							SetConsoleTextAttribute(h, 7);
							return p;
							break;
						}
					}
				}
				
				PTRSach q = NULL;
				return q;
			}
		}
	}
}

void ShowMuonTra(NodeDauSach ds, DS_MuonTra &dsmt, char MaSach[]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	draw(15, 102, 10, 9, 7);
	VeKhungMuonTra(10, 9, 0);
	int j = 0;
	NodeMT p;
	for (p = dsmt.First; p != NULL; p = p->next){
		if (strstr(p->muontra.MaSach, MaSach)) {
			if (j > 9) {
				break;
			}
			
			NoiKhungMuonTra(10, 12 + j);
			char ms[20];
			strcpy(ms, p->muontra.MaSach);
			char *isbn;
			isbn = strtok(ms, "-");
			int vitri = Search_info(ds, isbn);
			// xuat thong tin muon tra
			gotoxy(12, 12 + j);
			cout << p->muontra.MaSach;
			gotoxy(33, 12 + j);
			cout << ds.nodes[vitri]->TenSach;
			gotoxy(59, 12 + j);
			cout << p->muontra.NgayMuon.ngay << '/' << p->muontra.NgayMuon.thang << '/' << p->muontra.NgayMuon.nam;
			if (p->muontra.NgayTra.ngay != 0) {
				gotoxy(71, 12 + j);
				cout << p->muontra.NgayTra.ngay << '/' << p->muontra.NgayTra.thang << '/' << p->muontra.NgayTra.nam;
			} else {
				gotoxy(71, 12 + j);
				cout << "--/--/----";
			}
			gotoxy(89, 12 + j);
			if (p->muontra.TongNgayMuon > 7) {
				SetConsoleTextAttribute(h, 12);
				cout << p->muontra.TongNgayMuon;
				SetConsoleTextAttribute(h, 7);
			} else {
				SetConsoleTextAttribute(h, 10);
				cout << p->muontra.TongNgayMuon;
				SetConsoleTextAttribute(h, 7);
			}
			
			gotoxy(99, 12 + j);
			if (p->muontra.TrangThai == 0) {
				SetConsoleTextAttribute(h, 14);
				cout << "DANG MUON";
				SetConsoleTextAttribute(h, 7);
			} else if (p->muontra.TrangThai == 1) {
				SetConsoleTextAttribute(h, 10);
				cout << "DA TRA";
				SetConsoleTextAttribute(h, 7);
			} else if (p->muontra.TrangThai == 2) {
				SetConsoleTextAttribute(h, 12);
				cout << "MAT SACH";
				SetConsoleTextAttribute(h, 7);
			}
			
			j++;
		}
	}
}


NodeMT TimMuonTra (NodeDauSach ds, DS_MuonTra &dsmt, char dieukien) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(10, 3);
	cout << "**Nhan ESC de ngung tim kiem**";
	gotoxy(20, 1);
	char MaSach[20];
	int i = 0;
	while(true) {
		SetConsoleTextAttribute(h, 232);
		Showcursortype();
		fflush(stdin);
		char key = getch();
		
		if (key == 27) {
			int isConfirm = Confirm("Ban co muon dung tim kiem khong?");
			
			if (isConfirm == 1) {
				NodeMT p = NULL;
				return p;
				break;
			} else if (isConfirm == 0) {
				gotoxy(20, 1);
				SetConsoleTextAttribute(h, 232);
				cout << "                    ";
				SetConsoleTextAttribute(h, 7);
				ShowMuonTra(ds, dsmt, "");
				SetConsoleTextAttribute(h, 7);
				return TimMuonTra(ds, dsmt, dieukien);
				break;
			}
		}
		
		if (key == 8 && strlen(MaSach) > 0) {
			if (i == 0) {
				continue;
			}
			i--;
			MaSach[i] = '\0';
			gotoxy(20 + i, 1);
			cout << " ";
			gotoxy(20 + i, 1);
			ShowMuonTra(ds, dsmt, MaSach);	
			gotoxy(20 + i, 1);
			continue;
		}
		
		if(key >= 48 && key <= 57 || key >= 65 && key <= 90 || key >= 97 && key <= 122 || key == 45) {
			if (strlen(MaSach) >= 20) {
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
			ShowMuonTra(ds, dsmt, MaSach);	
			gotoxy(20 + i, 1);
		}
		
		if (key == 13) {
			if(strlen(MaSach) == 0) {
				NodeMT p = NULL;
				return p;
			} else {
				switch(dieukien) {
					// truong hop trang thai la dang muon
					case 't': {
						NodeMT p;
						for(p = dsmt.First; p != NULL; p = p->next) {
							if (strcmp(p->muontra.MaSach, MaSach) == 0 && p->muontra.TrangThai == 0) {
								return p;
							}
						}
						break;
					}
					// truong hop trang thai la mat sach
					case 'd': {
						NodeMT p;
						for(p = dsmt.First; p != NULL; p = p->next) {
							if (strcmp(p->muontra.MaSach, MaSach) == 0 && p->muontra.TrangThai == 2) {
								return p;
							}
						}
						break;
					}
				}
				
				NodeMT q = NULL;
				return q;
			}
		}
	}
}

bool CheckQuaHan (DS_MuonTra dsmt) {
	//chay vong lap de xem co sach nao dang muon qua han
	NodeMT p;
	if (Empty(dsmt)){
		return false;
	} else {
		p = dsmt.First;
		for (; p != NULL; p=p->next){
			if (p->muontra.TongNgayMuon > 7 && p->muontra.TrangThai == 0) {
				return true;
			}
		}
		return false;
	}
}

bool CheckMatSach (DS_MuonTra dsmt) {
	//chay vong lap de xem co sach nao dang muon qua han
	NodeMT p;
	if (Empty(dsmt)){
		return false;
	} else {
		p = dsmt.First;
		for (; p != NULL; p=p->next){
			if (p->muontra.TrangThai == 2) {
				return true;
			}
		}
		return false;
	}
}

bool CheckDaMuon(DS_MuonTra dsmt, char *isbn){
	NodeMT p;
	for(p = dsmt.First; p != NULL; p = p->next){
		if (p->muontra.TrangThai == 0 && strstr(p->muontra.MaSach, isbn)) {
			return true;
		}
	}
	return false;
}

void MuonSach(NodeDauSach &ds, DS_MuonTra &dsmt, int &trangthai) {
	// tao mot muon tra
	if (dsmt.total < 3 && CheckQuaHan(dsmt) == false && trangthai == 1) {
		//Duoc muon them sach;
		// Tim Sach
		PTRSach p;
		p = TimSachDeMuon(ds);
		if (p != NULL && p->sach.TrangThai == 0) {
			// lay isbn
			char *isbn;
			char ms[20];
			strcpy(ms, p->sach.MaSach);
			isbn = strtok(ms, "-");
			
			//check xem sach thuoc dau sach nay da duoc muon truoc do hay chua
			if(CheckDaMuon(dsmt, isbn) == true) {
				ErrorMessage("Khong the muon qua 1 sach/1 dau sach", 77, 1, 7);
				return;
			}
			
			//Them Sach vao DS
			MuonTra q;
			// Lay ngay hien tai
			time_t now = time(0);
			tm *ltm = localtime(&now);
			// Gan ngay hien tai cho ngay muon
			q.NgayMuon.nam = ltm->tm_year + 1900;
			q.NgayMuon.thang = ltm->tm_mon + 1;
			q.NgayMuon.ngay = ltm->tm_mday;
			// Gan ngay tra cho ngay 0/0/0
			q.NgayTra.ngay = 0;
			q.NgayTra.thang = 0;
			q.NgayTra.nam = 0;
			// Gan sach da tim thay cho sach trong node
			strcpy(q.MaSach, p->sach.MaSach);
			// Them node vao danh sach
			themcuoi(dsmt, q);
			// tang so sach da muon
			dsmt.total++;
			// thay doi trang thai cua sach trong dms
			p->sach.TrangThai = 1; // Dang duoc muon
			p->sach.DuocMuon = true;
			// tang so luot muon trong dau sach
			int vitri = Search_info(ds, isbn);
			ds.nodes[vitri]->soluotmuon++;
			
		} else if (p != NULL && p->sach.TrangThai == 1) {
			ErrorMessage("Sach nay dang duoc muon boi nguoi khac", 77, 1, 7);
		} else if (p != NULL && p->sach.TrangThai == 2) {
			ErrorMessage("Sach nay da bi thanh ly", 84, 1, 7);	
		} else if (p == NULL) {
			ErrorMessage("Sach khong ton tai", 86, 1, 7);
		}
		
		//Tang so luot muon trong dau sach
	} else if (dsmt.total >= 3 || CheckQuaHan(dsmt) == true || trangthai == 0) {
		if (trangthai == 0) {
			ErrorMessage("The nay da bi khoa", 86, 1, 7);
		} else if (dsmt.total >= 3){
			ErrorMessage("So sach muon dat toi da", 83, 1, 7);
		} else if (CheckQuaHan(dsmt) == true) {
			ErrorMessage("Ton tai sach muon qua han", 82, 1, 7);
		}
	}
}

void TraSach(NodeDauSach &ds, DS_MuonTra &dsmt, int &trangthai) {
	//Nhap Ma sach can tra (neu cuon do dang muon => buoc tiep theo)
	NodeMT p = TimMuonTra(ds, dsmt, 't');
	if (p != NULL) {
		//Confirm
		int isConfirm = Confirm("Ban co muon tra sach khong?");
		if (isConfirm == 1 && p->muontra.TrangThai == 0) {
			// lay thong tin dau sach
			char ms[20];
			char *isbn;
			strcpy(ms, p->muontra.MaSach);
			isbn = strtok(ms, "-");
			int vitri = Search_info(ds, isbn);
			
			// Lay ngay hien tai
			time_t now = time(0);
			tm *ltm = localtime(&now);
			
			//Lay ngay tra la ngay hien tai
			p->muontra.NgayTra.ngay = ltm->tm_mday;
			p->muontra.NgayTra.thang = ltm->tm_mon + 1;
			p->muontra.NgayTra.nam = ltm->tm_year + 1900;
			// Tinh Tong Ngay muon
			p->muontra.TongNgayMuon = ChenhLechNgay(p->muontra.NgayMuon);
			//Thay doi trang thai tu muon thanh tra
			p->muontra.TrangThai = 1;
			//total giam 1
			if(dsmt.total >= 0) {
				dsmt.total--;
			}
			
			// Trang thai cua sach tra ve San sang de muon
			PTRSach q = ds.nodes[vitri]->dms;
			for (; q != NULL; q = q->next) {
				if (strcmp(q->sach.MaSach, p->muontra.MaSach) == 0) {
					break;
				}
			}
			q->sach.TrangThai = 0;
			
			// Kiem tra neu con sach nao qua han thi khoa the neu khong thi mo the
			if (CheckQuaHan(dsmt) == false && CheckMatSach(dsmt) == false) {
				trangthai = 1;
			}
			
			
		} else if (p->muontra.TrangThai != 0) {
			ErrorMessage("Khong the tra sach", 86, 1, 7);
		}
	} else {
		ErrorMessage("Khong tim thay sach dang muon", 82, 1, 7);
	}
}

void BaoMatSach(NodeDauSach &ds, DS_MuonTra &dsmt, int &trangthai) {
	//Nhap Ma sach can tra (neu cuon do dang muon => buoc tiep theo)
	NodeMT p = TimMuonTra(ds, dsmt, 't');
	if (p != NULL) {
		//Confirm
		int isConfirm = Confirm("Ban co muon bao mat sach khong?");
		if (isConfirm == 1 && p->muontra.TrangThai == 0) {
			// set trang thai muon tra la mat sach
			p->muontra.TrangThai = 2;
			// set trang thai the la khoa
			trangthai = 0;
			
		} else if (p->muontra.TrangThai != 0) {
			ErrorMessage("Khong the bao mat sach", 86, 1, 7);
		}
	} else {
		ErrorMessage("Sach khong ton tai", 86, 1, 7);
	}
}

void DenSach(NodeDauSach &ds, DS_MuonTra &dsmt, int &trangthai) {
	//Nhap Ma sach can tra (neu cuon do dang muon => buoc tiep theo)
	NodeMT p = TimMuonTra(ds, dsmt, 'd');
	if (p != NULL) {
		//Confirm
		int isConfirm = Confirm("Ban co muon den sach khong?");
		if (isConfirm == 1 && p->muontra.TrangThai == 2) {
			// lay thong tin dau sach
			char ms[20];
			char *isbn;
			strcpy(ms, p->muontra.MaSach);
			isbn = strtok(ms, "-");
			int vitri = Search_info(ds, isbn);
			
			// Lay ngay hien tai
			time_t now = time(0);
			tm *ltm = localtime(&now);
			
			//Lay ngay tra la ngay hien tai
			p->muontra.NgayTra.ngay = ltm->tm_mday;
			p->muontra.NgayTra.thang = ltm->tm_mon + 1;
			p->muontra.NgayTra.nam = ltm->tm_year + 1900;
			// Tinh Tong Ngay muon
			p->muontra.TongNgayMuon = ChenhLechNgay(p->muontra.NgayMuon);
			//Thay doi trang thai tu muon thanh tra
			p->muontra.TrangThai = 1;
			//total giam 1
			if(dsmt.total >= 0) {
				dsmt.total--;
			}
			
			// Trang thai cua sach tra ve San sang de muon
			PTRSach q = ds.nodes[vitri]->dms;
			for (; q != NULL; q = q->next) {
				if (strcmp(q->sach.MaSach, p->muontra.MaSach) == 0) {
					break;
				}
			}
			// set trang thai sach la da thanh ly
			q->sach.TrangThai = 2;
			
			// Kiem tra neu con sach nao qua han thi khoa the neu khong thi mo the
			if (CheckQuaHan(dsmt) == false && CheckMatSach(dsmt) == false) {
				trangthai = 1;
			} else {
				trangthai = 0;
			}
		} else if (p->muontra.TrangThai != 2) {
			ErrorMessage("Khong the den sach", 86, 1, 7);
		}
	} else {
		ErrorMessage("Khong tim thay sach bi mat", 82, 1, 7);
	}
}

void XuatTrangMT(NodeDauSach ds, DS_MuonTra &muontra, int mathe, char HoDG[], char TenDG[], int phai, int &trangthai, int currentPage, int totalPage) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Nocursortype();
	NodeMT p;
	if (Empty(muontra)){
		xulymuontra(HoDG, TenDG, 1, 1, 1);
	} else {
		int start = (currentPage - 1) * 10;
		
		int totalLine;
		if (start + 10 > TongMuonTra(muontra)) {
			totalLine = TongMuonTra(muontra) % 10;
		} else totalLine = 10;
		
		
		int i = 0;
		int j = 0;
		
		xulymuontra(HoDG, TenDG, totalLine, currentPage, totalPage);
		for (p = muontra.First; p != NULL; p=p->next){
			if (j >= start && j < start + totalLine) {
				// Tim thong tin sach
				char ms[20];
				strcpy(ms, p->muontra.MaSach);
				char *isbn;
				isbn = strtok(ms, "-");
				int vitri = Search_info(ds, isbn);
				// xuat thong tin muon tra
				gotoxy(12, 12 + i);
				cout << p->muontra.MaSach;
				gotoxy(33, 12 + i);
				cout << ds.nodes[vitri]->TenSach;
				gotoxy(59, 12 + i);
				cout << p->muontra.NgayMuon.ngay << '/' << p->muontra.NgayMuon.thang << '/' << p->muontra.NgayMuon.nam;
				if (p->muontra.NgayTra.ngay != 0) {
					gotoxy(71, 12 + i);
					cout << p->muontra.NgayTra.ngay << '/' << p->muontra.NgayTra.thang << '/' << p->muontra.NgayTra.nam;
				} else {
					gotoxy(71, 12 + i);
					cout << "--/--/----";
				}
				gotoxy(89, 12 + i);
				if (p->muontra.TongNgayMuon > 7) {
					SetConsoleTextAttribute(h, 12);
					cout << p->muontra.TongNgayMuon;
					SetConsoleTextAttribute(h, 7);
				} else {
					SetConsoleTextAttribute(h, 10);
					cout << p->muontra.TongNgayMuon;
					SetConsoleTextAttribute(h, 7);
				}
				
				gotoxy(99, 12 + i);
				if (p->muontra.TrangThai == 0) {
					SetConsoleTextAttribute(h, 14);
					cout << "DANG MUON";
					SetConsoleTextAttribute(h, 7);
				} else if (p->muontra.TrangThai == 1) {
					SetConsoleTextAttribute(h, 10);
					cout << "DA TRA";
					SetConsoleTextAttribute(h, 7);
				} else if (p->muontra.TrangThai == 2) {
					SetConsoleTextAttribute(h, 12);
					cout << "MAT SACH";
					SetConsoleTextAttribute(h, 7);
				}
				
				i++;
				j++;
			} else {
				j++;  // KIEM TRA COI CO XUAT DUOC HAY KO
			}	
		}
	}
	
	gotoxy(23, 7);
	cout << mathe;
	gotoxy(32, 7);
	cout << HoDG;
	gotoxy(59, 7);
	cout << TenDG;
	gotoxy(72, 7);
	if (phai == 0) {
		cout << "NAM";
	} else if (phai == 1) {
		cout << "NU";
	}
	gotoxy(84, 7);
	if (trangthai == 0) {
		SetConsoleTextAttribute(h, 12);
		cout << "KHOA";
		gotoxy(22, 23);
		if (CheckQuaHan(muontra) == true) {
			gotoxy(10, 23);
			cout << "*Doc gia muon sach qua han*";
		}
		if (CheckMatSach(muontra) == true) {
			gotoxy(88, 23);
			cout << "*Doc gia lam mat sach*";
		}
		SetConsoleTextAttribute(h, 7);
	} else if (trangthai == 1) {
		SetConsoleTextAttribute(h, 10);
		cout << "HOAT DONG";
		SetConsoleTextAttribute(h, 7);
	}
	
	while (true) {
		char key = getch();
		if (key == 27) {
			break;
		}
		
		if (key == 0) {
			key = getch();
			if (key == 62) {
				MuonSach(ds, muontra, trangthai);
				int currentPage = 1;
				int totalPage = TongTrangMT(muontra);
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
			
			if (key == 63) {
				TraSach(ds, muontra, trangthai);
				int currentPage = 1;
				int totalPage = TongTrangMT(muontra);
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
			
			if (key == 64) {
				BaoMatSach(ds, muontra, trangthai);
				int currentPage = 1;
				int totalPage = TongTrangMT(muontra);
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
			
			if (key == 65) {
				DenSach(ds, muontra, trangthai);
				int currentPage = 1;
				int totalPage = TongTrangMT(muontra);
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
		}
		
		if (key == -32) {
			key = getch();
			if (key == 75) {
				currentPage--;
				if (currentPage < 1) {
					currentPage = 1;
				}
				totalPage = TongTrangMT(muontra);
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
			
			if (key == 77) {
				totalPage = TongTrangMT(muontra);
				currentPage++;
				if (currentPage > totalPage) {
					currentPage = totalPage;
				}
				XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
				break;
			}
		}
	}
}

void XuLyMuonTraSach(NodeDauSach ds, DS_MuonTra &muontra, int mathe, char HoDG[], char TenDG[], int phai, int &trangthai) {
	int currentPage = 1;
	int totalPage = TongTrangMT(muontra);
	XuatTrangMT(ds, muontra, mathe, HoDG, TenDG, phai, trangthai, currentPage, totalPage);
}
