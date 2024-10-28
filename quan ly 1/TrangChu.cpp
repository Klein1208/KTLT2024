#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "menu_nhan_vien.h"
#include "menu_voucher.h"
using namespace std;

// void quan_ly();
void menu(){
    int n;
    cout << "1.Quản lý nhân viên.\n"
         << "2. Quản lý voucher.\n";
    cin >> n;
    if(n==1){
        quan_ly();
    }
    else if(n==2){
        menuVoucher();
    }
}

 int main(){
    menu();
}
