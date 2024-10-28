#pragma once
#include <iostream>
#include "doc_ghi_file_nhan_vien.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "menu_nhan_vien.h"
using namespace std;

void NhapSalary(NhanVien& nv);

void NhapSĐT(NhanVien& nv);

void Nhapdate(NhanVien& nv);

void NhapTen(NhanVien& nv);

void quan_ly();

void ThemNhanVien();

void NhapChuc(NhanVien& nv){
    cout << "Nhập chức vụ nhân viên:\n0.Hủy.\n";
    cin.ignore();
    getline(cin, nv.Chuc);
    if(nv.Chuc == "0"){
        quan_ly();
    }
    else NhapTen(nv);
}

void NhapTen(NhanVien& nv){
    cout << "Nhập họ tên nhân viên: \n0.Hủy.\n";
    getline(cin,nv.Name);
    if(nv.Name == "0"){
        NhapChuc(nv);
    }
    else Nhapdate(nv);
}

void Nhapdate(NhanVien& nv){
    cout << "Nhập ngày tháng năm sinh nhân viên (DD/MM/YYYY):\n0.Hủy.\n ";
    getline(cin,nv.date);
    if(nv.date == "0"){
        NhapTen(nv);
    }
    else NhapSĐT(nv);
}

void NhapSĐT(NhanVien& nv){
    cout << "Nhập số điện thoại nhân viên:\n0.Hủy.\n ";
    getline(cin, nv.numberphone);
    if(nv.numberphone == "0"){
        Nhapdate(nv);
    } 
    else NhapSalary( nv);
} 

void NhapSalary(NhanVien& nv){
    cout << "Nhập lương theo giờ:\n0.Hủy.\n ";
    getline(cin, nv.salary);
    if(nv.salary == "0"){
        NhapSĐT(nv);
    }
}

void ThemVaoDS(NhanVien& nv){
    int n;
    nv.time = "0";
    nv.salary = "0";
    nv.Money ="0";
    List.push_back(nv);
    ofstream file;
    file.open("nhan_vien.csv", ios::app);    
    file << nv.ID << "," << nv.Chuc << "," << nv.Name << "," << nv.date << ",";
    file << nv.numberphone << "," << nv.time << "," << nv.salary << "," << nv.Money << endl;
    file.close();
    cout << "Thêm thành công!\n0.Quay trở lại.";
    cin >> n;
    if(n==0){
        quan_ly();
    }    
}

void TaoID(NhanVien& nv) {
    stringstream ss;
    string ID;
    ss << nv.Chuc;
    char chu;
    while (ss >> chu) {
        ID += toupper(chu);
        ss.ignore(1000, ' ');
    }
    ss.clear();
    ss.str(nv.Name);
    while (ss >> chu) {
        ID += toupper(chu);
        ss.ignore(1000, ' ');
    }
    ss.clear();
    ss.str(nv.date);
    string so;
    getline(ss, so, '/');
    ID += so;
    getline(ss, so, '/');
    ID += so;
    getline(ss, so, '/');
    ID += so;
    int n;
    for(int i=0; i<List.size(); i++){
        if(List[i].ID == ID){
            n=1;
            break;
        }
    }
    if ( n==1 )
    {
        cout << "Đã tồn tại nhân viên.\n0.Hủy.\n1.Thêm lại.\n";
        cin >> n;
        if(n==1){
            ThemNhanVien();
        }
        else if(n==0){
            quan_ly();
        }
    }
    else{
        nv.ID = ID;
        cout << "Tạo ID nhân viên thành công.\n";
        cout << "ID nhân viên mới là:\n" << nv.ID << endl;
        ThemVaoDS(nv);
    }   
}

void ThemNhanVien(){
    NhanVien nv;
    NhapChuc(nv);
    docFile();
    TaoID(nv);                                              
}

void Cop(string A, int n){
    cout << A;
    for(int i=0; i< n-A.length(); i++){
        cout <<" ";
    }
    cout << "| ";
}

void tt( int i){
    Cop(to_string(i),5);
    Cop(List[i].ID, 20);
    Cop(List[i].Chuc,15);
    Cop(List[i].Name, 30);
    Cop(List[i].date, 30);
    Cop(List[i].numberphone, 20);
    Cop(List[i].salary,20 );
    cout<< endl;
}


void ThongTinNhanVien(){
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if( ID == "0"){
        quan_ly();
    } else
    {
        int i, a=0;
        for(i=0; i<=List.size(); i++){
            if(List[i].ID == ID) {
                a=1;
                break;
            }
        }
        if(a==1){
            tt(0);
            tt(i);
            cout << "0.Quay trở lại.\n";
            cin >> a;
            if(a==0){
                quan_ly();
            }
        } else
        {
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            ThongTinNhanVien();
        }  
    }    
}

void XoaNhanVien(){
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if( ID == "0"){
        quan_ly();
    } 
    else{
        int i, a=0;
        for(i=0; i<=List.size(); i++){
            if(List[i].ID == ID) {
                a=1;
                break;
            }
        }
        if(a==1){
            tt(0);
            tt(i);
            cout << " Chắc chắn xóa nhân viên này?\n1.Có.\n2.Không.\n";
            cin >> a;
            if( a==1 ){
                List.erase(List.begin() + i);
                ghiFile(); 
                cout << "Xoa thành công.\n0.Trở lại.\n";
                cin >> a;
                if(a==0){
                    XoaNhanVien();
                }              
            }
            else if( a==0 ){
                XoaNhanVien();
            }
        } else
        {
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            XoaNhanVien();
        }  
    }
    
}

void ChonSua(int i, int a){
    tt(0);
    tt(i);
    do{
        cout << "Chọn thuộc tính muốn sửa:\n"
            << "1. Họ và tên.\n"
            << "2. Ngày sinh.\n"
            << "3. Số Điện thoại.\n"
            << "0. Trở về\n";
        cin >> a;
        if(a>3){
            cout << "Không hợp lệ. Vui lòng nhập lại:\n";
        }
    } while (a>3);
}

void ChinhSuathongTin(){
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n 0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if( ID == "0"){
        quan_ly();
    } 
    else{
        int i, a=0;
        for(i=0; i<=List.size(); i++){
            if(List[i].ID == ID) {
                a=1;
                break;
            }
        }
        if(a==1){
            ChonSua(i,a);
            if( a==0 ){
                ChinhSuathongTin();           
            }
            else if( a==1 ){
                cout << " Nhập họ và tên mới:\n"
                    << "0.Quay về.\n";
                cin.ignore();
                getline(cin,List[i].Name);
                if(List[i].Name == "0"){
                    ChonSua(i,a);
                }
            }
            else if( a==2 ){
                cout << "Nhập ngày sinh mới (theo dạng DD/MM/YYYY):\n"
                    << "0.Quay về.\n";
                cin >> List[i].date;
                if(List[i].date == "0"){
                    ChonSua(i,a);
                }
            }
            else if( a==3 ){
                cout << "Nhập Số điện thoại mới;\n"
                    << "0.Quay vè.\n";
                cin >> List[i].numberphone;
                if(List[i].numberphone == "0"){
                    ChonSua(i,a);
                }
            }
            ghiFile();
            cout << "Cập nhật thành công\n"
                << "0.Trở về\n";
            do{
                cin >> a;
                if(a != 0 ) cout << "sai cú pháp, nhập lại\n";
             } while(a!=0);
        }
        else{
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            XoaNhanVien();
        }  
    }
    
}

void InDanhSach(){
    cout << "Danh sách nhân viên:\n"; 
    docFile();     
    for(int i=0; i<List.size(); i++){
        tt(i);
    }
}