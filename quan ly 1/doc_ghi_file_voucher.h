#pragma once
#include <fstream>
#include <vector>

using namespace std;

struct voucherList
{   
    string ChuongTrinh;
    string muc;
    string maVoucher;
    string time_start;
    string time_end;
    string soMa;
    string lanSuDung;
    string GiaMin;
    string GiamMax;
};

vector<voucherList> vList;

void docFileVoucher(){
    voucherList vL;
    ifstream file;
    file.open("voucher.csv");
    string line;
    while(getline(file ,line)){
        stringstream ss(line);
        getline(ss,vL.ChuongTrinh,',');
        getline(ss, vL.muc,',');
        getline(ss, vL.maVoucher,',');
        getline(ss, vL.lanSuDung,',');
        getline(ss, vL.GiaMin,',');
        getline(ss, vL.GiamMax,',');
        getline(ss, vL.time_start,',');
        getline(ss, vL.time_end,',');
        vList.push_back(vL);
    }
    file.close();
}

void ghiFileVoucher(){
    ofstream f;
    f.open("voucher.csv", ios::trunc);
    for( int i=0; i<vList.size(); i++){
        f << vList[i].ChuongTrinh << "," << vList[i].muc << "," << vList[i].maVoucher << "," 
        << vList[i].lanSuDung << "," << vList[i].GiaMin << "," << vList[i].GiamMax << "," 
        << vList[i].time_start << "," << vList[i].time_end << "," << endl; 
    }
    f.close();
}