#pragma once
#include <fstream>
#include <vector>
using namespace std;

//Class
struct NhanVien
{
    //private:
    string ID;
    string Chuc;
    string Name;
    string date;
    string numberphone;
    string time;
    string salary;
    string Money;
    // public:
    //     if(stoi(time)<100){
    //         Money = to_string(stof(time)*stof(salary));
    //     }
    //     else{
    //         Money = to_string(stof(salary)*(stof(time)+(stof(time)-100)*0.5))
    //     }
};

vector<NhanVien> List;

void docFile(){
    NhanVien nv;
    ifstream file;
    file.open("nhan_vien.csv");
    string line;
    while(getline(file ,line)){
        stringstream ss(line);
        getline(ss,nv.ID,',');
        getline(ss, nv.Chuc,',');
        getline(ss, nv.Name,',');
        getline(ss, nv.date,',');
        getline(ss, nv.numberphone,',');
        getline(ss, nv.time,',');
        getline(ss, nv.salary,',');
        getline(ss, nv.Money,',');
        List.push_back(nv);
    }
    file.close();
}

void ghiFile(){
    ofstream f;
    f.open("nhan_vien.csv", ios::trunc);
    for( int i=0; i<List.size(); i++){
        f << List[i].ID << "," << List[i].Chuc << "," << List[i].Name << "," << List[i].date << ","
        << List[i].numberphone << "," << List[i].time << "," << List[i].salary << "," 
        << List[i].Money << "," << endl; 
    }
    f.close();
}