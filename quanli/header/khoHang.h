#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class KhoHang
{
private:
    string maHang;
    string tenHang;
    string loaiHang;
    string soLuongTonKho;
    string viTri;

public:
    KhoHang();
    KhoHang(string maHang, string tenHang, string loaiHang, string soLuongTonKho, string viTri);
    string autoGenerateMaHang();
    void themHangMoi();
    void themHangDaCo();
    void hienThiHang();
    void xoaHang();
    void suaHang();
    void docDanhSachHang();
    void ghiDanhSachHang();
    void xuatKhoHang();
    string getSoLuongTonKho(const string &maHang);
    int kiemTraHang(const string &maHang);
    int kiemTraPhieuXuatHang(const string &maHang);
};

vector<KhoHang> khoHangs;

vector<KhoHang> phieuXuatHangs;

KhoHang::KhoHang() {};

KhoHang::KhoHang(string maHang, string tenHang, string loaiHang, string soLuongTonKho, string viTri)
    : maHang(maHang), tenHang(tenHang), loaiHang(loaiHang), soLuongTonKho(soLuongTonKho), viTri(viTri) {}

string KhoHang::autoGenerateMaHang()
{
    if (khoHangs.size() == 0)
    {
        return "DSKH001";
    }
    string lastId = khoHangs[khoHangs.size() - 1].maHang;
    int number = stoi(lastId.substr(5, 3)) + 1;
    string newId = "DSKH";
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

void KhoHang::themHangMoi()
{
    maHang = autoGenerateMaHang();
    cin.ignore();
    cout << "Nhap ten hang: ";
    getline(cin, tenHang);
    cout << "Nhap loai hang: ";
    getline(cin, loaiHang);
    cout << "Nhap so luong muon nhap hang: ";
    cin >> soLuongTonKho;
    cin.ignore();
    cout << "Nhap vi tri: ";
    getline(cin, viTri);
    KhoHang khoHang(maHang, tenHang, loaiHang, soLuongTonKho, viTri);
    khoHangs.push_back(khoHang);
    cout << "Them hang thanh cong!" << endl;
}

void KhoHang::themHangDaCo()
{
    int index;
    string choice;
    cout << "Nhap ma hang: ";
    cin >> maHang;
    index = kiemTraHang(maHang);
    if (index == -1)
    {
        cout << "Khong tim thay hang!" << endl;
    }
    else
    {
        cout << "Nhap so luong nhap: ";
        int soLuongNhap;
        cin >> soLuongNhap;
        int soLuongTonKho = stoi(getSoLuongTonKho(maHang)) + soLuongNhap;
        khoHangs[index].soLuongTonKho = to_string(soLuongTonKho);
        cout << "Nhap hang thanh cong!" << endl;
    }
}

void KhoHang::hienThiHang()
{
    cout << left << setw(15) << "Ma hang"
         << left << setw(25) << "Ten hang"
         << left << setw(10) << "So luong"
         << left << setw(15) << "Vi Tri" << endl;
    cout << string(65, '-') << endl; // Print a separator line

    // Print each item's information
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        cout << left << setw(15) << khoHangs[i].maHang
             << left << setw(25) << khoHangs[i].tenHang
             << left << setw(10) << khoHangs[i].soLuongTonKho
             << left << setw(15) << khoHangs[i].viTri << endl;
    }
}

void KhoHang::xoaHang()
{
    string maHang;
    cout << "Nhap ma hang can xoa: ";
    cin >> maHang;
    cin.ignore();
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        if (khoHangs[i].maHang == maHang)
        {
            khoHangs.erase(khoHangs.begin() + i);
            cout << "Xoa hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay hang can xoa!" << endl;
}

void KhoHang::suaHang()
{
    string maHang;
    cout << "Nhap ma hang can sua: ";
    cin >> maHang;
    cin.ignore();
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        if (khoHangs[i].maHang == maHang)
        {
            cout << "Nhap ten hang: ";
            getline(cin, khoHangs[i].tenHang);
            cout << "Nhap loai hang: ";
            getline(cin, khoHangs[i].loaiHang);
            cout << "Nhap so luong ton kho: ";
            cin >> khoHangs[i].soLuongTonKho;
            cin.ignore();
            cout << "Nhap vi tri: ";
            getline(cin, khoHangs[i].viTri);
            cout << "Sua hang thanh cong!" << endl;
            return;
        }
    }
    cout << "Khong tim thay hang can sua!" << endl;
}

void KhoHang::docDanhSachHang()
{
    ifstream fileIn("data/khohang.txt");
    if (fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            string maHang;
            string tenHang;
            string loaiHang;
            string soLuongTonKho;
            string viTri;
            getline(fileIn, maHang);
            getline(fileIn, tenHang);
            getline(fileIn, loaiHang);
            getline(fileIn, soLuongTonKho);
            getline(fileIn, viTri);
            if (maHang == "")
            {
                break;
            }
            KhoHang khoHang(maHang, tenHang, loaiHang, soLuongTonKho, viTri);
            khoHangs.push_back(khoHang);
        }
        fileIn.close();
    }
}

void KhoHang::ghiDanhSachHang()
{
    ofstream fileOut("data/khohang.txt");
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        fileOut << khoHangs[i].maHang << endl;
        fileOut << khoHangs[i].tenHang << endl;
        fileOut << khoHangs[i].loaiHang << endl;
        fileOut << khoHangs[i].soLuongTonKho << endl;
        fileOut << khoHangs[i].viTri << endl;
    }
    fileOut.close();
}

string KhoHang::getSoLuongTonKho(const string &maHang)
{
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        if (khoHangs[i].maHang == maHang)
        {
            return khoHangs[i].soLuongTonKho;
        }
    }
    return "";
}

int KhoHang::kiemTraHang(const string &maHang)
{
    for (unsigned int i = 0; i < khoHangs.size(); i++)
    {
        if (khoHangs[i].maHang == maHang)
        {
            return i;
        }
    }
    return -1;
}

int KhoHang::kiemTraPhieuXuatHang(const string &maHang)
{
    for (unsigned int i = 0; i < phieuXuatHangs.size(); i++)
    {
        if (phieuXuatHangs[i].maHang == maHang)
        {
            return i;
        }
    }
    return -1;
}

void KhoHang::xuatKhoHang()
{ // ham xuat kho hang theo ma hang
    string choice;
    string tenkhachhang;
    cout << "Nhap ten khach hang: ";
    cin.ignore();
    getline(cin, tenkhachhang);
    do
    {
        cout << "Nhap ma hang: ";
        cin >> maHang;

        int index = kiemTraHang(maHang);
        if (index == -1)
        {
            cout << "Khong tim thay hang!" << endl;
        }
        else
        {
            if (kiemTraPhieuXuatHang(maHang) != -1)
            {

                int soLuongXuat;
                cout << "Nhap so luong xuat: ";
                cin >> soLuongXuat;
                if (stoi(khoHangs[kiemTraHang(maHang)].soLuongTonKho) < soLuongXuat)
                {
                    cout << "So luong hang trong kho hang khong du!" << endl;
                }
                else
                {
                    int soLuongTonKho = stoi(getSoLuongTonKho(maHang)) - soLuongXuat;
                    khoHangs[kiemTraHang(maHang)].soLuongTonKho = to_string(soLuongTonKho); // cap nhat lai so luong ton kho

                    int temp = stoi(phieuXuatHangs[kiemTraPhieuXuatHang(maHang)].soLuongTonKho);
                    phieuXuatHangs[kiemTraPhieuXuatHang(maHang)].soLuongTonKho = to_string(temp + soLuongXuat); // cap nhat lai so luong trong phieu xuat hang
                    cout << "Xuat hang thanh cong!" << endl;
                }
            }
            else
            {
                cout << "Nhap so luong xuat: ";
                int soLuongXuat;
                cin >> soLuongXuat;
                if (stoi(getSoLuongTonKho(maHang)) < soLuongXuat)
                {
                    cout << "So luong hang trong kho khong du!" << endl;
                }
                else
                {
                    int soLuongTonKho = stoi(getSoLuongTonKho(maHang)) - soLuongXuat;
                    khoHangs[index].soLuongTonKho = to_string(soLuongTonKho);
                    cout << "Xuat hang thanh cong!" << endl;
                    phieuXuatHangs.push_back(khoHangs[index]);
                    phieuXuatHangs[phieuXuatHangs.size() - 1].soLuongTonKho = to_string(soLuongXuat);
                }
            }
        }
        cout << "Ban co muon xuat tiep khong? (y/n): ";
        cin >> choice;
        while (choice != "y" && choice != "n" && choice != "Y" && choice != "N")
        {
            cout << "Nhap sai! Ban co muon xuat tiep khong? (y/n): ";
            cin >> choice;
        }
    } while (choice == "y" || choice == "Y");
    if (choice == "n" || choice == "N")
    {
        if (phieuXuatHangs.size() == 0)
        {
            cout << "Khong co phieu xuat hang nao!" << endl;
            return;
        }
        else
        {
            ofstream fileOut("data/phieuxuathang.txt", ios::app);
            fileOut << "___________________________________________________________________" << endl;
            fileOut << "|                      PHIEU XUAT HANG                            |" << endl;
            fileOut << "| Ten khach hang: " << left << setw(48) << tenkhachhang << "|" << endl
                    << "|                                                                 |" << endl;
            fileOut << left << setw(15) << "|Ma hang"
                    << left << setw(25) << "Ten hang"
                    << left << setw(10) << "So luong"
                    << left << setw(15) << "Vi Tri" << " |" << endl;
            fileOut << "|" << string(65, '-') << "|" << endl; // Print a separator line
            for (unsigned int i = 0; i < phieuXuatHangs.size(); i++)
            {
                fileOut << "|"
                        << left << setw(15) << phieuXuatHangs[i].maHang
                        << left << setw(25) << phieuXuatHangs[i].tenHang
                        << left << setw(10) << phieuXuatHangs[i].soLuongTonKho
                        << left << setw(15) << phieuXuatHangs[i].viTri << "|" << endl;
            }
            fileOut << "|_________________________________________________________________|" << endl;
        }
    }
}

void QuanLyKhoHang()
{
    KhoHang khoHang;
    khoHang.docDanhSachHang();
    int choice;
    do
    {
        cout << "===Quan ly kho hang===\n";
        cout << "1. Nhap Hang Moi" << endl;
        cout << "2. Nhap Hang Da Co" << endl;
        cout << "3. Hien thi danh sach hang" << endl;
        cout << "4. Sua hang" << endl;
        cout << "5. Xoa hang" << endl;
        cout << "6. Tao phieu xuat kho hang" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin.ignore();
        cin >> choice;
        switch (choice)
        {
        case 1:
            khoHang.themHangMoi();
            khoHang.ghiDanhSachHang();

            break;
        case 2:
            khoHang.themHangDaCo();
            khoHang.ghiDanhSachHang();

            break;
        case 3:
            khoHang.hienThiHang();

            break;
        case 4:
            khoHang.suaHang();
            khoHang.ghiDanhSachHang();

            break;
        case 5:
            khoHang.xoaHang();
            khoHang.ghiDanhSachHang();
            // cout << "1";
            break;
        case 6:
            khoHang.hienThiHang();
            khoHang.xuatKhoHang();
            khoHang.ghiDanhSachHang();
            // cout << "1";
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            break;
        }
    } while (choice != 0);
};