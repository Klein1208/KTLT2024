#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()
#include "doc_ghi_file_voucher.h"
#include "menu_voucher.h"

using namespace std;

void menuVoucher();
void DateEnd(voucherList& vList);

void DateStart(voucherList& vList);

void NhieuNhat(voucherList& vList);

void ThapNhat(voucherList& vList);

void Soluong(voucherList& vList);

void DienMucGiam(voucherList& vList);


string taoMaTuDong(int doDai, string mucgiam) {
    string ma;
    const string kyTu = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < doDai; ++i) {
        ma += kyTu[rand() % kyTu.length()];
    }
    mucgiam+=ma;
    return mucgiam;
}
void Tao(voucherList &vList){
    srand(time(0));
    string n= "Vou"+vList.muc;
    int doDaiMa= 20 - n.length();
    ofstream file;
    file.open("voucher.csv", ios::app);
    for(int i=0; i < stoi(vList.soMa); i++){
        vList.maVoucher=taoMaTuDong(doDaiMa,vList.muc);
        file << vList.ChuongTrinh << "," << vList.muc << "," << vList.maVoucher << "," 
             << "1" << "," << vList.GiaMin << "," << vList.GiamMax << ","
             << vList.time_start << "," << vList.time_end << "," << endl;
    }
    file.close();
    cout << "Tạo Thành Công";
}
void TenChuongTrinh(voucherList& vList){
    cout << "Điền Tên chương trình: "
        << "0.Hủy\n";
    cin.ignore();
    getline(cin, vList.ChuongTrinh);
    if(vList.ChuongTrinh=="0"){
        menuVoucher();
    }
    else{
        DienMucGiam(vList);
    }
}

void DienMucGiam(voucherList& vList){
    cout << "Điền mức giảm (chia hết cho 5 và bỏ dấu %): \n"
        << "0.Trở lại\n";
    cin >> vList.muc;
    if(vList.muc == "0"){
        TenChuongTrinh(vList);
    }
    else{
        Soluong(vList);
    }
}

void Soluong(voucherList& vList){
    cout << "Điền số lượng mã: \n"
        << "0.Trở lại\n";
    cin >> vList.soMa;
    if(vList.soMa == "0"){
        DienMucGiam(vList);
    }
    else{
        ThapNhat(vList);
    }
}

void ThapNhat(voucherList& vList){
    cout << "Điền giá thấp nhất áp dụng: \n"
        << "0.Trở lại\n";
    cin >> vList.GiaMin;
    if (vList.GiaMin == "0")
    {
        Soluong(vList);
    }
    else{
        NhieuNhat(vList);
    }    
}

void NhieuNhat(voucherList& vList){
    cout << "Điền giá tối đa có thể giảm:\n"
            << "0.Trở lại\n";
    cin >> vList.GiamMax;
    if (vList.GiamMax== "0")
    {
        ThapNhat(vList);
    }
    else{
        DateStart(vList);
    }
}

void DateStart(voucherList& vList){
    cout << "Điền thời gian bắt đầu (Theo dạng YYYY-MM-DD HH:MM:SS):\n"
            << "0.Trở lại\n";
    cin.ignore();
    getline(cin,vList.time_start);
    if(vList.time_start=="0"){
        NhieuNhat(vList);
    }
    else{
        DateEnd(vList);
    }
    
}

void DateEnd(voucherList& vList){
    cout << "Điền thời gian kết thúc (Theo dạng YYYY-MM-DD HH:MM:SS):\n"
        << "0.Trở lại\n";
    //cin.ignore();
    getline(cin, vList.time_end);
    if (vList.time_end == "0")
    {
        DateStart(vList);
    }
    else{
        Tao(vList);
    }
}
void TaoVoucher(){
    voucherList vList;
    TenChuongTrinh(vList);   
}

string LayThoiGianThuc(){ // Lấy thời gian thực tế
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_c);

    stringstream ss;
    ss << put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool SoSanhTime(string time1, string time2){
    return time1 > time2;
}

void KiemtraChuowngTrinh(){
    //voucherList vlist;
    docFileVoucher();
    cout << "Điền tên chương trình giảm giá:";
    string ten;
    cin.ignore();
    getline(cin,ten);
    int dem1=0, dem0=0, a=0;
    for(int i=0; i<vList.size(); i++){
        if(ten == vList[i].ChuongTrinh){
            a=i;
            if(vList[i].lanSuDung == "1") dem1++;
            else dem0++;
        }
    }
    if (a==0)
    {
        cout << "Không có chương trình ưu đãi.";
    }
    else{
        string now =LayThoiGianThuc();
    //     int a= SoSanhTime(now,vList[a].time_start);
    // int b= SoSanhTime(now,vList[a].time_end);
    cout << "Chương trình: " << vList[a].ChuongTrinh << endl;
    cout << "Số mã giảm giá đã phát hành: " << dem1 + dem0 << endl;
    cout << "Loại mã giảm giá: " << vList[a].muc << endl;
    cout << "Số mã giảm giá đã sử dụng: " << dem0 << endl
         << "Giá trị tối thiểu của sản phẩm: " << vList[a].GiaMin << endl
         << "Giá trị tối đa giảm: " << vList[a].GiamMax << endl
         << "Thời gian bắt đầu: " << vList[a].time_start << endl;
    cout << "Thời gian kết thúc: " << vList[a].time_end << endl;
    if(SoSanhTime(now,vList[a].time_start)==0){
        cout << "Chưonwng trình chưa diễn ra." << endl;
    }
    else if( SoSanhTime(now,vList[a].time_end)==0 ){
        cout << "Chương trình đang diễn ra." << endl;
    }
    else if( SoSanhTime(now,vList[a].time_end)==1){
        cout << "Chương trình đã kết thúc";
    }
    }
    
}

void KtVoucher(){
    docFileVoucher();
    string Ma;
    cout << "Diền mã voucher muốn kiểm tra: ";
    cin.ignore();
    getline(cin,Ma);
    int a=0;
    for(int i=0; i<vList.size(); i++){
        if(Ma== vList[i].maVoucher){
            a=i;
            break;
        }
    }
    if(a==1){
         string now =LayThoiGianThuc();
        int a= SoSanhTime(now,vList[a].time_start);
        int b= SoSanhTime(now,vList[a].time_end);
        cout << "Chương trình giảm giá: " << vList[a].ChuongTrinh << endl
             << "Mức giảm giá: " << vList[a].muc << endl
             << "Giá trị tối thiểu cảu sản phẩm: " << vList[a].GiaMin << endl
             << "Giá trị tối đa giảm được: " << vList[a].GiamMax << endl
             << "Số lượt còn có thể sử dụng: " << vList[a].lanSuDung<< endl
             << "Thời hạn sử dụng: từ " << vList[a].time_start << "đến" << vList[a].time_end << endl;
        if(a==0){
            cout << "Chưonwng trình chưa diễn ra." << endl;
        }
        else if( b==0 ){
            cout << "Chương trình đang diễn ra." << endl;
        }
        else if( b==1){
            cout << "Chương trình đã kết thúc";
        }
    }
    else
    {
        cout << "Không có mã giảm giá hoặc nhập sai mã giảm giá.";
    }
}

void loaiChuongTrinh(){
    docFileVoucher();
    vector<voucherList> vlist;
    cout << "Điền tên chương trình giảm giá:";
    string ChuongTrinh;
    cin.ignore();
    getline(cin,ChuongTrinh);
    int dem1=0, dem0=0, a=0;
    for(int i=0; i<vList.size(); i++){
        if(ChuongTrinh != vList[i].ChuongTrinh){
            vlist.push_back(vList[i]);
        }
        else{
            a++;
        }
    }
    if (a==0)
    {
        cout << "Không có chương trình ưu đãi.";
    }
    else{
        copy(vlist.begin(),vlist.end(), vList.begin());
        ghiFileVoucher();
        cout << "Đã xóa thành công." << endl;
    }
}