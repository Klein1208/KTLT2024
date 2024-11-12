#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class KhachHang
{
private:
    string maKhachHang;
    string tenKhachHang;
    string diaChi;
    string soDienThoai;

public:
    KhachHang();
    KhachHang(string maKhachHang, string tenKhachHang, string diaChi, string soDienThoai);
    string autoGenerateMaKhachHang();
    void docDanhSachKhachHang();
    void ghiDanhSachKhachHang();
    void themKhachHang();
    void hienThiKhachHang();
    void suaKhachHang();
    void xoaKhachHang();
};

using namespace std;

vector<KhachHang> khachHangs;

KhachHang::KhachHang() {};

KhachHang::KhachHang(string maKhachHang, string tenKhachHang, string diaChi, string soDienThoai)
    : maKhachHang(maKhachHang), tenKhachHang(tenKhachHang), diaChi(diaChi), soDienThoai(soDienThoai) {}

string KhachHang::autoGenerateMaKhachHang()
{ // auto fill ma khach hang theo dinh dang KH001,KH002....
    if (khachHangs.size() == 0)
    {
        return "KH001";
    }
    string lastId = khachHangs[khachHangs.size() - 1].maKhachHang;
    int number = stoi(lastId.substr(2, 3)) + 1;
    string newId = "KH";
    if (number < 10)
    {
        newId += "00";
    }
    else if (number < 100)
    {
        newId += "0";
    }
    newId += to_string(number);
    return newId;
}

void KhachHang::themKhachHang()
{
    maKhachHang = autoGenerateMaKhachHang();
    cin.ignore();
    cout << "Nhap ten khach hang: ";
    getline(cin, tenKhachHang);
    cout << "Nhap dia chi: ";
    getline(cin, diaChi);
    cout << "Nhap so dien thoai: ";
    cin >> soDienThoai;
    KhachHang khachHang(maKhachHang, tenKhachHang, diaChi, soDienThoai);
    khachHangs.push_back(khachHang);
    cout << "Them khach hang thanh cong!" << endl;
}

void KhachHang::hienThiKhachHang()
{
    if (khachHangs.size() == 0)
    {
        cout << "Danh sach khach hang rong!" << endl;
        return;
    }

    // Print table header
    cout << left << setw(15) << "Ma khach hang"
         << left << setw(25) << "Ten khach hang"
         << left << setw(30) << "Dia chi"
         << left << setw(15) << "So dien thoai" << endl;
    cout << string(85, '-') << endl; // Print a separator line

    // Print each customer's information
    for (unsigned int i = 0; i < khachHangs.size(); i++)
    {
        cout << left << setw(15) << khachHangs[i].maKhachHang
             << left << setw(25) << khachHangs[i].tenKhachHang
             << left << setw(30) << khachHangs[i].diaChi
             << left << setw(15) << khachHangs[i].soDienThoai << endl;
    }
}

void KhachHang::xoaKhachHang()
{
    string maKhachHang;
    cout << "Nhap ma khach hang can xoa: ";
    cin >> maKhachHang;
    cin.ignore();
    for (unsigned int i = 0; i < khachHangs.size(); i++)
    {
        if (khachHangs[i].maKhachHang == maKhachHang)
        {
            khachHangs.erase(khachHangs.begin() + i);
            cout << "Xoa khach hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay khach hang can xoa!" << endl;
}

void KhachHang::suaKhachHang()
{
    string maKhachHang;
    cout << "Nhap ma khach hang can sua: ";
    cin >> maKhachHang;
    cin.ignore();
    for (unsigned int i = 0; i < khachHangs.size(); i++)
    {
        if (khachHangs[i].maKhachHang == maKhachHang)
        {
            cout << "Nhap ten khach hang: ";
            getline(cin, tenKhachHang);
            cout << "Nhap dia chi: ";
            getline(cin, diaChi);
            cout << "Nhap so dien thoai: ";
            cin >> soDienThoai;
            khachHangs[i].tenKhachHang = tenKhachHang;
            khachHangs[i].diaChi = diaChi;
            khachHangs[i].soDienThoai = soDienThoai;
            cout << "Sua khach hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay khach hang can sua!" << endl;
}

void KhachHang::docDanhSachKhachHang()
{
    ifstream fileIn("data/khachhang.txt");
    if (fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            getline(fileIn, maKhachHang);
            getline(fileIn, tenKhachHang);
            getline(fileIn, diaChi);
            getline(fileIn, soDienThoai);
            if (maKhachHang == "")
            {
                continue;
            }
            KhachHang khachHang(maKhachHang, tenKhachHang, diaChi, soDienThoai);
            khachHangs.push_back(khachHang);
        }
        fileIn.close();
    }
}

void KhachHang::ghiDanhSachKhachHang()
{
    ofstream fileOut("data/khachhang.txt");
    if (fileOut.is_open())
    {
        for (unsigned int i = 0; i < khachHangs.size(); i++)
        {
            fileOut << khachHangs[i].maKhachHang << endl;
            fileOut << khachHangs[i].tenKhachHang << endl;
            fileOut << khachHangs[i].diaChi << endl;
            fileOut << khachHangs[i].soDienThoai << endl;
        }
        fileOut.close();
    }
}
void QuanLyKhachHang(){
    KhachHang khachHang;
    khachHang.docDanhSachKhachHang();
    int choice;
    do{
        cout << "=== Quan ly khach hang ==="
             << "1. Them khach hang" << endl
             << "2. Hien thi danh sach khach hang" << endl
             << "3. Sua khach hang" << endl
             << "4. Xoa khach hang" << endl
             << "0. Thoat" << endl
             << "Nhap lua chon: ";
        cin.ignore();
        cin >> choice;
        switch(choice){
            case 1:
                khachHang.themKhachHang();
                khachHang.ghiDanhSachKhachHang();
                break;
            case 2:
                khachHang.hienThiKhachHang();
                break;
            case 3:
                khachHang.suaKhachHang();
                khachHang.ghiDanhSachKhachHang();
                break;
            case 4:
                khachHang.xoaKhachHang();
                khachHang.ghiDanhSachKhachHang();
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
                break;
        }
    }while(choice != 0);
};