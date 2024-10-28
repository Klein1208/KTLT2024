#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "voucher.h"

using namespace std;

void menuVoucher(){
    cout << "Quản lý voucher:\n"
        << "1. Tạo Chương trình và voucher mới.\n"
        << "2. Kiểm tra thông tin voucher.\n"
        << "3. Kiểm tra chương trình giảm giá.\n"
        << "4. Sử dụng mã giảm giá.\n"
        << "5. Loại bỏ chương trình đã kết thúc.\n";
    int n;
    do
    {
        cin >> n;
        if(n>4) cout << "Sai cú pháp, vui long điền lại.\n";
    } while (n>4);
    if(n==1){
        TaoVoucher();
    }
    else if( n==3){
        KiemtraChuowngTrinh();
    }
    else if( n==2){
        KtVoucher();
    }
    else if( n==5){
        loaiChuongTrinh();
    }
}