#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "source.h"
using namespace std;

struct NhanVien
{
    string ID;
    string Chuc;
    string Name;
    string date;
    string numberphone;
    string time;
    string salary;
    string Money;
};

vector<NhanVien> List;

void docFile()
{
    NhanVien nv;
    ifstream file;
    file.open("data/ nhan_vien.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, nv.ID, ',');
        getline(ss, nv.Chuc, ',');
        getline(ss, nv.Name, ',');
        getline(ss, nv.date, ',');
        getline(ss, nv.numberphone, ',');
        getline(ss, nv.time, ',');
        getline(ss, nv.salary, ',');
        getline(ss, nv.Money, ',');
        List.push_back(nv);
    }
    file.close();
}

void ghiFile()
{
    ofstream f;
    f.open("data/ nhan_vien.csv", ios::trunc);
    for (int i = 0; i < List.size(); i++)
    {
        f << List[i].ID << "," << List[i].Chuc << "," << List[i].Name << "," << List[i].date << ","
          << List[i].numberphone << "," << List[i].time << "," << List[i].salary << ","
          << List[i].Money << "," << endl;
    }
    f.close();
}

void NhapSalary(NhanVien &nv);

void NhapSĐT(NhanVien &nv);

void Nhapdate(NhanVien &nv);

void NhapTen(NhanVien &nv);

void menuNhanVien();

void NhapID(NhanVien &nv);

void ThemNhanVien();

void NhapChuc(NhanVien &nv)
{
    string Chuc;
    int n=0;
    do
    {
        cout << "Nhập chức vụ nhân viên:\n0.Hủy.\n";
        cin.ignore();
        getline(cin, Chuc);
        if (Chuc.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.Chuc=Chuc;
            n=1;
        }
    } while (n==0);
    NhapTen(nv);
}

void NhapTen(NhanVien &nv)
{
    string Name;
    int n=0;
    do
    {
        cout << "Nhập họ tên nhân viên: \n0.Hủy.\n";
        getline(cin, Name);
        if (Name.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.Name=Name;
            n=1;
        }
    } while (n == 0);
        Nhapdate(nv);
}

void Nhapdate(NhanVien &nv)
{
    string date;
    int n=0;
    do
    {
         cout << "Nhập ngày tháng năm sinh nhân viên (DD/MM/YYYY):\n0.Hủy.\n ";
    getline(cin, date);
    if (date.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.date=date;
            n=1;
        }
    } while (n==0);
        NhapSĐT(nv);
}

void NhapSĐT(NhanVien &nv)
{
    string number;
    int n=0;
    do
    {
        cout << "Nhập số điện thoại nhân viên:\n0.Hủy.\n ";
    getline(cin, number);
        if (number.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.numberphone=number;
            n=1;
        }
    } while (n==0);
        NhapSalary(nv);
}

void NhapSalary(NhanVien &nv)
{
    string luong;
    int n=0;
    do
    {
           cout << "Nhập lương theo giờ:\n0.Hủy.\n ";
    getline(cin, luong);
    if (luong.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.salary=luong;
            n=1;
        }
    } while (n==0);
    NhapID(nv);
}

void ThemVaoDS(NhanVien &nv)
{
    int n;
    nv.time = "0";
    //nv.salary = "0";
    nv.Money = "0";
    List.push_back(nv);
    ofstream file;
    file.open("data/nhan_vien.csv", ios::app);
    file << nv.ID << "," << nv.Chuc << "," << nv.Name << "," << nv.date << ",";
    file << nv.numberphone << "," << nv.time << "," << nv.salary << "," << nv.Money << endl;
    file.close();
    cout << "Thêm thành công!\n0.Quay trở lại.";
    cin >> n;
    if (n == 0)
    {
        menuNhanVien();
    }
}

void NhapID(NhanVien &nv)
{
    string ID;
    do
    {cout << "Nhập ID nhân viên: ";
    getline(cin, ID);
        if (ID.empty()){
            cout << "Nhập sai cú pháp, vui lòng nhập lại.";
        }
        else
        {
            nv.ID=ID;
        }
    } while (ID.empty());

    int n = 0;
    for (int i = 0; i < List.size(); i++)
    {
        if (List[i].ID == nv.ID && List[i].Name == nv.Name && List[i].date == nv.date)
        {
            n = 1;
            break;
        }
    }
    if (n == 1)
    {
        cout << "Đã tồn tại nhân viên.\n0.Hủy.\n1.Thêm lại.\n";
        cin >> n;
        if (n == 1)
        {
            ThemNhanVien();
        }
        else if (n == 0)
        {
            menuNhanVien();
        }
    }
    else
    {
        ThemVaoDS(nv);
    }
}

void ThemNhanVien()
{
    docFile();
    NhanVien nv;
    NhapChuc(nv);
    NhapID(nv);
}

void Cop(string A, int n)
{
    cout << A;
    for (int i = 0; i < n - A.length(); i++)
    {
        cout << " ";
    }
    cout << "| ";
}

void tt(int i)
{
    Cop(to_string(i), 5);
    Cop(List[i].ID, 20);
    Cop(List[i].Chuc, 15);
    Cop(List[i].Name, 30);
    Cop(List[i].date, 30);
    Cop(List[i].numberphone, 20);
    Cop(List[i].salary, 20);
    cout << endl;
}

void ThongTinNhanVien()
{
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if (ID == "0")
    {
        menuNhanVien();
    }
    else
    {
        int i, a = 0;
        for (i = 0; i <= List.size(); i++)
        {
            if (List[i].ID == ID)
            {
                a = 1;
                break;
            }
        }
        if (a == 1)
        {
            tt(0);
            tt(i);
            cout << "0.Quay trở lại.\n";
            cin >> a;
            if (a == 0)
            {
                menuNhanVien();
            }
        }
        else
        {
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            ThongTinNhanVien();
        }
    }
}

void XoaNhanVien()
{
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if (ID == "0")
    {
        menuNhanVien();
    }
    else
    {
        int i, a = 0;
        for (i = 0; i <= List.size(); i++)
        {
            if (List[i].ID == ID)
            {
                a = 1;
                break;
            }
        }
        if (a == 1)
        {
            tt(0);
            tt(i);
            cout << " Chắc chắn xóa nhân viên này?\n1.Có.\n2.Không.\n";
            cin >> a;
            if (a == 1)
            {
                List.erase(List.begin() + i);
                ghiFile();
                cout << "Xoa thành công.\n0.Trở lại.\n";
                cin >> a;
                if (a == 0)
                {
                    XoaNhanVien();
                }
            }
            else if (a == 0)
            {
                XoaNhanVien();
            }
        }
        else
        {
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            XoaNhanVien();
        }
    }
}

void ChonSua(int i, int a)
{
    tt(0);
    tt(i);
    do
    {
        cout << "Chọn thuộc tính muốn sửa:\n"
             << "1. Họ và tên.\n"
             << "2. Ngày sinh.\n"
             << "3. Số Điện thoại.\n"
             << "0. Trở về\n";
        cin >> a;
        if (a > 3)
        {
            cout << "Không hợp lệ. Vui lòng nhập lại:\n";
        }
    } while (a > 3);
}

void ChinhSuathongTin()
{
    string ID;
    docFile();
    cout << "Điền ID nhân viên: \n 0.Hủy.\n";
    cin.ignore();
    cin >> ID;
    if (ID == "0")
    {
        menuNhanVien();
    }
    else
    {
        int i, a = 0;
        for (i = 0; i <= List.size(); i++)
        {
            if (List[i].ID == ID)
            {
                a = 1;
                break;
            }
        }
        if (a == 1)
        {
            ChonSua(i, a);
            if (a == 0)
            {
                ChinhSuathongTin();
            }
            else if (a == 1)
            {
                cout << " Nhập họ và tên mới:\n"
                     << "0.Quay về.\n";
                cin.ignore();
                getline(cin, List[i].Name);
                if (List[i].Name == "0")
                {
                    ChonSua(i, a);
                }
            }
            else if (a == 2)
            {
                cout << "Nhập ngày sinh mới (theo dạng DD/MM/YYYY):\n"
                     << "0.Quay về.\n";
                cin >> List[i].date;
                if (List[i].date == "0")
                {
                    ChonSua(i, a);
                }
            }
            else if (a == 3)
            {
                cout << "Nhập Số điện thoại mới;\n"
                     << "0.Quay vè.\n";
                cin >> List[i].numberphone;
                if (List[i].numberphone == "0")
                {
                    ChonSua(i, a);
                }
            }
            ghiFile();
            cout << "Cập nhật thành công\n"
                 << "0.Trở về\n";
            do
            {
                cin >> a;
                if (a != 0)
                    cout << "sai cú pháp, nhập lại\n";
            } while (a != 0);
        }
        else
        {
            cout << "ID nhân viên không tồn tại hoặc nhập sai ID.\n";
            XoaNhanVien();
        }
    }
}

void InDanhSach()
{
    cout << "Danh sách nhân viên:\n";
    docFile();
    for (int i = 0; i < List.size(); i++)
    {
        tt(i);
    }
}

void Chon();

void menuNhanVien()
{
    int n;
    do
    {
        cout << "=== Quản lý nhân viên ===" << endl;
    cout << "Chọn chế độ:" << endl;
    cout << "1. Thêm nhân viên." << endl;
    cout << "2. Thông tin cá nhân nhân viên." << endl;
    cout << "3. Xóa nhân viên." << endl;
    cout << "4. Chỉnh sửa nhân viên." << endl;
    cout << "5. Danh sách nhân viên." << endl;
    cout << "0. Quay lại.\n"
         << "Lựa chọn: ";
    cin.ignore();
    cin >> n;
    if (n>5) cout << "Sai cú pháp. Vui lòng nhập lại.\n";
    } while(n>5);

    if (n == 1)
    {
        ThemNhanVien();
    }
    else if (n == 2)
    {
        docFile();
        ThongTinNhanVien();
    }
    else if (n == 3)
    {
        XoaNhanVien();
    }
    else if (n == 4)
    {
        ChinhSuathongTin();
    }
    else if (n == 5)
    {
        InDanhSach();
    }
    else if( n==0 ){
        Chon();
    }
}