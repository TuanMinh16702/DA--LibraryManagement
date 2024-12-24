// Thu vien chuan
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

void Copy (char c[], string s) {
	int lenght;
	
	lenght = s.copy(c, s.size());
	c[lenght] = '\0';
}

// Thu vien do nguoi dung tao
#include "GiaoDien.h"
#include "XuLyInput.h"
#include "DanhMucSach.h"
#include "DauSach.h"
#include "MUonTra.h"
#include "DocGia.h"

// Luu file dau sach
void WriteFileDS (NodeDauSach ds) {
	ofstream FileOut;
	FileOut.open("F:\\Do An CTDL&GT\\DAUSACH.txt", ios_base::out);
	
	if (FileOut.fail() == true) {
		cout << "Khong the mo file" << endl;
	}
	
	FileOut << ds.n << endl;
	
	for(int i = 0; i < ds.n; i++) {
		FileOut << ds.nodes[i]->ISBN << ",";
		FileOut << ds.nodes[i]->TenSach << ",";
		FileOut << ds.nodes[i]->SoTrang << ",";
		FileOut << ds.nodes[i]->TacGia << ",";
		FileOut << ds.nodes[i]->NamSB << ",";
		FileOut << ds.nodes[i]->TheLoai << ",";
		FileOut << ds.nodes[i]->soluong << ",";
		FileOut << ds.nodes[i]->soluotmuon << ",";
		FileOut << endl;
	}
	
	FileOut.close();
	cout << "DANG LUU DAU SACH VAO DATABASE" << endl;
}

void ReadFileDS (NodeDauSach &ds) {
	ifstream FileIn;
	FileIn.open("F:\\Do An CTDL&GT\\DAUSACH.txt", ios_base::in);
	
	if (FileIn.fail() == true) {
		cout << "Khong the mo file" << endl;
	} else {
		int n;
		char temp[10];
		string num;
		
		getline(FileIn, num, '\n');
		Copy(temp, num);
		n = atoi(temp);
		
		for(int i = 0; i < n; i++) {
			string isbn, tensach, sotrang, tacgia, namsb, theloai, soluotmuon;
			char ISBN[15];
			char TenSach[25];
			int SoTrang;
			char TacGia[15];
			int NamSB;
			char TheLoai[15];
			int slm;
			
			string str;
			char temp[10];
			
			getline(FileIn, isbn, ',');
			getline(FileIn, tensach, ',');
			getline(FileIn, sotrang, ',');
			getline(FileIn, tacgia, ',');
			getline(FileIn, namsb, ',');
			getline(FileIn, theloai, ',');
			getline(FileIn, str, ',');
			getline(FileIn, soluotmuon, ',');
			getline(FileIn, str, '\n');
			
			Copy(ISBN, isbn);
			Copy(TenSach, tensach);
			
			Copy(temp, sotrang);
			SoTrang = atoi(temp);
			
			Copy(TacGia, tacgia);
			
			Copy(temp, namsb);
			NamSB = atoi(temp);
			
			Copy(TheLoai, theloai);
			
			Copy(temp, soluotmuon);
			slm = atoi(temp);
			
			DauSach *dausach = new DauSach(ISBN, TenSach, SoTrang, TacGia, NamSB, TheLoai);
			dausach->soluong = 0;
			dausach->soluotmuon = slm;
			
			Insert_Item(ds, ds.n, dausach);
		}	
		cout << "DANG TAI DAU SACH..." << endl;
	}
	
	FileIn.close();
}
// end of luu file dau sach

// luu file doc gia
void WriteDocGia(tree root){
	ofstream f;
	f.open("F:\\Do An CTDL&GT\\DOCGIA.txt", ios_base::out);
	if(f.fail() == true ){
		cout<<"Khong the mo file" << endl;	
	}
	
	
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	
	int tong = TongDocGia(root);
	f << tong << '\n';
	
	while(p != NULL){
		f << p->docgia.MATHE << ',';
		f << p->docgia.ho << ',';
		f << p->docgia.ten << ',';
		f << p->docgia.phai << ',';
		f << p->docgia.trangthai << ',';
		f << endl;
		if(p->right != NULL){
			stack[++sp] = p->right;
		} 
		if (p->left != NULL) {
			p = p->left;
		} else if (sp == -1)
			break;
		else {
			p = stack[sp--];
		}
	}
	
	f.close();
	cout << "DANG LUU DOC GIA VAO DATABASE" << endl;
}

void ReadDocGia (tree &root) {
	ifstream filein;
	filein.open("F:\\Do An CTDL&GT\\DOCGIA.txt", ios_base::in);
	if(filein.fail() == true ){
		cout<<"Khong the mo file" << endl;	
	} else {
		tree stack[stacksize];
		tree p = root;
		int sp = -1;
		
		char temp[10];
		string tongDG;
		int TDG;
		getline(filein, tongDG, '\n');
		Copy(temp, tongDG);
		TDG = atoi(temp);
		
		while(TDG > 0){
			
			string mt, ho, ten, phai, tt;
			int MATHE;
			char Ho[25];
			char Ten[11];
			int Phai;
			int TrangThai;
			
			getline(filein, mt, ',');
			getline(filein, ho, ',');
			getline(filein, ten, ',');
			getline(filein, phai, ',');
			getline(filein, tt, ',');
			
			Copy(temp, mt);
			MATHE = atoi(temp);
			
			Copy(Ho, ho);
			Copy(Ten, ten);
			
			Copy(temp, phai);
			Phai = atoi(temp);
			
			Copy(temp, tt);
			TrangThai = atoi(temp);
			
			DocGia docgia;
			docgia.MATHE = MATHE;
			strcpy(docgia.ho, Ho);
			strcpy(docgia.ten, Ten);
			docgia.phai = Phai;
			docgia.trangthai = TrangThai;
			
			them(root, docgia);
			
			TDG--;
		}
		cout << "DANG TAI DOC GIA..." << endl;	
	}
	
	filein.close();
}

//luu file danh muc sach
void WriteFileDMS (NodeDauSach ds) {
	ofstream FileOut;
	FileOut.open("F:\\Do An CTDL&GT\\DANHMUCSACH.txt", ios_base::out);
	
	if (FileOut.fail() == true) {
		cout << "Khong the mo file" << endl;
	}
	
	FileOut << ds.n << endl;
	
	for(int i = 0; i < ds.n; i++) {
		FileOut << ds.nodes[i]->ISBN << ",";
		FileOut << ds.nodes[i]->soluong << ",";
		PTRSach p;
		for (p = ds.nodes[i]->dms; p != NULL; p = p->next) {
			FileOut << p->sach.MaSach << ",";
			FileOut << p->sach.TrangThai << ",";
			FileOut << p->sach.ViTri << ",";
			FileOut << p->sach.DuocMuon << ",";
		}
		FileOut << endl;
	}
	
	FileOut.close();
	cout << "DANG LUU DANH MUC SACH VAO DATABASE" << endl;
}

// doc file danh muc sach
void ReadFileDMS (NodeDauSach &ds) {
	ifstream FileIn;
	FileIn.open("F:\\Do An CTDL&GT\\DANHMUCSACH.txt", ios_base::in);
	
	if (FileIn.fail() == true) {
		cout << "Khong the mo file" << endl;
	} else {
		int n;
		char temp[50];
		string num;
		
		getline(FileIn, num, '\n');
		Copy(temp, num);
		n = atoi(temp);
		
		for(int i = 0; i < n; i++) {
			string ISBN, SoLuong;
			char isbn[15];
			int soluong;
			
			getline(FileIn, ISBN, ',');
			getline(FileIn, SoLuong, ',');
			
			Copy(isbn, ISBN);
			Copy(temp, SoLuong);
			soluong = atoi(temp);
			
			for (int j = 0; j < soluong; j++) {
				string MaThe, TrangThai, ViTri, DuocMuon;
				char MT[20];
				int tt;
				
				getline(FileIn, MaThe, ',');
				getline(FileIn, TrangThai, ',');
				getline(FileIn, ViTri, ',');
				getline(FileIn, DuocMuon, ',');
				
				Copy(MT, MaThe);
				
				Copy(temp, TrangThai);
				tt = atoi(temp);
				
				Sach sach;
				strcpy(sach.MaSach, MT);
				sach.TrangThai = tt;
				sach.ViTri = ViTri;
				
				if (DuocMuon == "0") {
					sach.DuocMuon = false;
				} else {
					sach.DuocMuon = true;
				}
				
				ThemSach(ds.nodes[i]->dms, sach, ds.nodes[i]->soluong);
			}
			string temp2;
			getline(FileIn, temp2, '\n');
		}
		cout << "DANG TAI DANH MUC SACH..." << endl;
	}
	
	FileIn.close();
}

// ghi file Muon Tra 
void WriteMuonTra (tree root) {
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	
	ofstream f;
	f.open("F:\\Do An CTDL&GT\\MUONTRA.txt", ios_base::out);
	if(f.fail() == true ){
		cout<<"Khong the mo file"<<endl;	
	}
	
	while(p != NULL){
		f << p->docgia.MATHE << "," << TongMuonTra(p->docgia.muontra) << endl;
		NodeMT q;
		for (q = p->docgia.muontra.First; q != NULL; q = q->next) {
			f << q->muontra.MaSach << ",";
			f << q->muontra.NgayMuon.ngay << "/" << q->muontra.NgayMuon.thang << "/" << q->muontra.NgayMuon.nam << ",";
			f << q->muontra.NgayTra.ngay << "/" << q->muontra.NgayTra.thang << "/" << q->muontra.NgayTra.nam << ",";
			f << q->muontra.TongNgayMuon << ",";
			f << q->muontra.TrangThai << ","  << endl;
		}
		if(p->right != NULL){
			stack[++sp] = p->right;
		} 
		if (p->left != NULL) {
			p = p->left;
		} else if (sp == -1)
			break;
		else {
			p = stack[sp--];
		}
	}
	
	f.close();
	cout << "DANG LUU DANH SACH MUON TRA VAO DATABASE" << endl;
}

void ReadMuonTra (tree &root) {
	tree stack[stacksize];
	tree p = root;
	int sp = -1;
	
	ifstream f;
	f.open("F:\\Do An CTDL&GT\\MUONTRA.txt", ios_base::in);
	if(f.fail() == true ){
		cout<<"Khong the mo file"<<endl;	
	} else {
		while(p != NULL){
			string MaThe, soluong, Temp;
			char temp[20];
			int mt, sl;
			getline(f,MaThe, ',');
			getline(f,soluong, '\n');
			
			Copy(temp, MaThe);
			mt = atoi(temp);
			
			Copy(temp, soluong);
			sl = atoi(temp);
			
			if (p->docgia.MATHE == mt) {
				for (int i = 0; i < sl; i++) {
					string MaSach, NgayMuon, ThangMuon, NamMuon, NgayTra, ThangTra, NamTra, TongNgayMuon, TrangThai;
					char ms[20];
					MuonTra muontra;
					getline(f, MaSach, ',');
					getline(f, NgayMuon, '/');
					getline(f, ThangMuon, '/');
					getline(f, NamMuon, ',');
					getline(f, NgayTra, '/');
					getline(f, ThangTra, '/');
					getline(f, NamTra, ',');
					getline(f, TongNgayMuon, ',');
					getline(f, TrangThai, ',');
					getline(f, Temp, '\n');
					
					Copy(ms, MaSach);
					strcpy(muontra.MaSach, ms);
					
					Copy(temp, NgayMuon);
					muontra.NgayMuon.ngay = atoi(temp);
					
					Copy(temp, ThangMuon);
					muontra.NgayMuon.thang = atoi(temp);
					
					Copy(temp, NamMuon);
					muontra.NgayMuon.nam = atoi(temp);
					
					Copy(temp, NgayTra);
					muontra.NgayTra.ngay = atoi(temp);
					
					Copy(temp, ThangTra);
					muontra.NgayTra.thang = atoi(temp);
					
					Copy(temp, NamTra);
					muontra.NgayTra.nam = atoi(temp);
					
					if (muontra.NgayTra.ngay != 0) {
						muontra.TongNgayMuon = ChenhLechGiua2Ngay(muontra.NgayMuon, muontra.NgayTra);
					} else {
						muontra.TongNgayMuon = ChenhLechNgay(muontra.NgayMuon);
					}
					
					Copy(temp, TrangThai);
					muontra.TrangThai = atoi(temp);
					
					if (muontra.TongNgayMuon > 7 && muontra.TrangThai == 0) {
						p->docgia.trangthai = 0;
					}
					
					// co mot sach bi mat thi the bi khoa
					if (muontra.TrangThai == 2) {
						p->docgia.trangthai = 0;
					}
					
					if (muontra.TrangThai == 0 || muontra.TrangThai == 2){
						p->docgia.muontra.total++;
					}
					
					themcuoi(p->docgia.muontra, muontra);
				}
			}
			
			if(p->right != NULL){
				stack[++sp] = p->right;
			} 
			if (p->left != NULL) {
				p = p->left;
			} else if (sp == -1)
				break;
			else {
				p = stack[sp--];
			}
		}	
		cout << "DANG TAI DANH MUC MUON TRA..." << endl;
	}
	
	f.close();
}

// ghi het tat ca cac file
void WriteAllFile(NodeDauSach &ds, tree &root) {
	WriteFileDS(ds);
	WriteDocGia(root);
	WriteFileDMS(ds);
	WriteMuonTra(root);
}

// doc het tat ca cac file
void ReadAllFile(NodeDauSach &ds, tree &root) {
	ReadFileDS(ds);
	ReadDocGia(root);
	ReadFileDMS(ds);
	ReadMuonTra(root);
}

// Xay dung giao dien menu chinh
void RenderMainMenu (NodeDauSach &ds, tree &root) {
	system("cls");
	draw(29, 121, 0, 0, 187);
	string array[6] = {"Danh Muc Dau Sach", "Danh Sach Doc Gia", "Sach duoc muon nhieu nhat", "Tra cuu thong tin sach", "Doc gia muon sach qua han", "Ket thuc chuong trinh"};
	int target = MainMenu(array, 6, "QUAN LY THU VIEN");
	
	switch (target) {
		case 1:
		{
			HandleDauSach(ds);
			RenderMainMenu(ds, root);
			break;
		}
			
		case 2:
		{
			XuLyDocGia(ds, root);
			RenderMainMenu(ds, root);
			break;
		}
		case 3:
			{
				Top10(ds);
				RenderMainMenu(ds, root);
				break;
			}
		case 4:
			{
				TraCuuThongTin(ds);
				RenderMainMenu(ds, root);
				break;
			}
		case 5:
			{
				int currentPage = TongTrangDGQH(root);
				int totalPage = TongTrangDGQH(root);
				DocGiaQuaHan(ds, root, currentPage, totalPage);
				RenderMainMenu(ds, root);
				break;
			}
		case 6:
			{
				system("cls");
				WriteAllFile(ds, root);
			    cout << "DA GHI DU LIEU THANH CONG.";
				break;
			}
	}
}


int main ()
{
	// khai bao danh sach dau sach
	NodeDauSach ds;
	
	// khai bao danh sach doc gia
    tree root;
    khoitao(root);
    
    // doc tat ca file da luu
    ReadAllFile(ds, root);
    cout << "DA TAI DU LIEU THANH CONG.";
    sleep(1);
    
    // khoi dong chuong trinh
	RenderMainMenu(ds, root);
	return 0;
}

