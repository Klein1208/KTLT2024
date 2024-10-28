#pragma once
#include "nhan_vien.h"
#include <iostream>
#include <fstream>
#include <string>
#include "doc_ghi_file_nhan_vien.h"
using namespace std;

void quan_ly(){
    cout << "Quản lý nhân viên"<< endl;
    cout << "Chọn chế độ:" << endl;
    cout << "1. Thêm nhân viên."<< endl;
    cout << "2. Thông tin cá nhân nhân viên." << endl;
     cout << "3. Xóa nhân viên." << endl;
     cout << "4.Chỉnh sửa nhân viên." << endl;
    cout << "5. Danh sách nhân viên." << endl;
    int n;
    cin >> n;
    if(n==1){
        ThemNhanVien();
    }
     else if(n==2){
        docFile();
        ThongTinNhanVien();
    }
    else if(n==3){
        XoaNhanVien();
    }
    else if(n==4){
        ChinhSuathongTin();
    }
    else if(n==5){
        InDanhSach();
    }
}
