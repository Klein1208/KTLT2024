#pragma once
#include "sanpham&don.h"
#include "NhanVien.h"
#include "Voucher.h"
#include "khoHang.h"
#include "khachHang.h"
#include "NhaCungCap.h"
#include "BaoCao.h"

using namespace std;

void menu()
{
    cout << "===== Cửa Hàng =====\n";
    cout << "1. Sản phẩm cửa hàng.\n"
         << "2. Quản lý đơn hàng.\n"
         << "3. Quản lý kho hàng.\n"
         << "4. Quản lý khách hàng.\n"
         << "5. Nhà cung cấp.\n"
         << "6. Quản lý nhân viên.\n"
         << "7. Chương trình khuyến mãi và voucher.\n"
         << "8. Báo cáo doanh thu.\n"
         << "0. Kết thúc chương trình\n"
         << "Lựa chọn: ";
}

void Chon()
{
    int luachon;
    do
    {
        menu();
        cin >> luachon;
        cout << endl;
        if (luachon > 8)
        {
            cout << "Lựa chọn sai.\n";
        }
    } while (luachon > 8);
    switch (luachon)
    {
    case 0:
        cout << "Chào tạm biệt.\n";
        break;
    case 1:
        menuSanPham();
        cin.ignore();
        break;
    case 2:
        menuDon();
        cin.ignore();
        break;
    case 3:
        QuanLyKhoHang();
        cin.ignore();
        break;
    case 4:
        QuanLyKhachHang();
        cin.ignore();
        break;
    case 5:
        menu_Supplier();
        cin.ignore();
        break;
    case 6:
        menuNhanVien();
        cin.ignore();
        break;
    case 7:
        menuVoucher();
        cin.ignore();
        break;
    case 8:
        menuBaoCao();
        cin.ignore();
        break;
    default:
        cin.ignore();
        break;
    }
}