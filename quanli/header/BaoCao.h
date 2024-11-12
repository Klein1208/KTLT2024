#pragma once
#include <bits/stdc++.h>

using namespace std;

class Sanpham{
public:
    string name;
    int giaban, giagoc;

    Sanpham(string a, int b, int c){
        name = a; giaban = b; giagoc = c;
    }

    void print() const{
        cout << name << "| ban: " << giaban << " goc: " << giagoc << endl;
    }
        // Định nghĩa toán tử == để so sánh hai đối tượng Sanpham
    bool operator==(const Sanpham &other) const {
         return name == other.name && giaban == other.giaban && giagoc == other.giagoc;
    }

};

class History{
public:
    int day, month, year;
    string name;

    History(string a, int b, int c, int d){
        name = a; day = b; month = c; year = d;
    }

    void print() const {
        cout << name << "| " << day << "/" << month << "/" << year << endl;
    }
        // Định nghĩa toán tử == để so sánh hai đối tượng History
    bool operator==(const History &other) const {
        return name == other.name && day == other.day && month == other.month && year == other.year ;
    }
};


void xuhuong(vector<History> s){
    map<string, int> mp1;
    for(History x:s){
        mp1[x.name]++;
    }
    multimap<int, string> mp;
    for(auto x:mp1){
        mp.insert(make_pair(x.second, x.first));
    }

    vector<pair<int, string>> v;
    for(auto x : mp){
        v.push_back(make_pair(x.first, x.second));
    }
    int best = v[v.size()-1].first, worst = v[0].first;
    cout << "danh sach san pham ban chay nhat:  |da ban: " << best << endl;
    int i = v.size() - 1;
    while(i >= 0 && v[i].first == best){
        cout << " - " << v[i].second << endl;
        i--;
    }
    cout << "danh sach san pham ban it nhat:   |da ban: " << worst << endl;
    int j = 0;
    while(j < v.size() && v[j].first == worst){
        cout << " - " << v[j].second << endl;
        j++;
    }
}

int bigger(const History &a, int d, int m, int y) {
    if (a.year > y) return 1;
    if (a.year < y) return 0;

    if (a.month > m) return 1;
    if (a.month < m) return 0;

    if (a.day >= d) return 1;

    return 0;
}

int smaller(const History &a, int d, int m, int y) {
    if (a.year < y) return 1;
    if (a.year > y) return 0;

    if (a.month < m) return 1;
    if (a.month > m) return 0;

    if (a.day <= d) return 1;

    return 0;
}

int check(string s){
    for(auto x : s){
        if(!isdigit(x)) return 1234;
    }
    return stoi(s);
}

int doanhthu(vector<Sanpham> sp, vector<History> his){
    int d1, m1, y1, d2, m2, y2;
    string td1, tm1, ty1, td2, tm2, ty2;
    cout << "TINH DOANH THU BAT DAU TU: " <<  endl;
    while(true){
        cout << "   ngay: ";
        cin >> td1;
        int tmp = check(td1);
        if(tmp != 1234 && tmp < 32){
            d1 = tmp;
            break;
        }
        cout << "chi nhap so ngay hop le( <= 31 ) !!!" << endl;
    }
    while(true){
        cout << "   thang: ";
        cin >> tm1;
        int tmp = check(tm1);
        if(tmp != 1234 && tmp < 13){
            m1 = tmp;
            break;
        }
        cout << "chi nhap so thang hop le ( <= 12 )!!!" << endl;
    }
    while(true){
        cout << "   nam: ";
        cin >> ty1;
        int tmp = check(ty1);
        if(tmp != 1234){
            y1 = tmp;
            break;
        }
        cout << "chi nhap so nam hop le !!!" << endl;
    }

    cout << "TINH DOANH THU DEN NGAY: " <<  endl;
    while(true){
        cout << "   ngay: ";
        cin >> td2;
        int tmp = check(td2);
        if(tmp != 1234 && tmp < 32){
            d2 = tmp;
            break;
        }
        cout << "chi nhap so ngay hop le( <= 31 )!!!" << endl;
    }
    while(true){
        cout << "   thang: ";
        cin >> tm2;
        int tmp = check(tm2);
        if(tmp != 1234 && tmp < 13){
            m2 = tmp;
            break;
        }
        cout << "chi nhap so thang hop le( <= 12 )!!!" << endl;
    }
    while(true){
        cout << "   nam: ";
        cin >> ty2;
        int tmp = check(ty2);
        if(tmp != 1234){
            y2 = tmp;
            break;
        }
        cout << "chi nhap so nam !!!" << endl;
    }

    int ans = 0;
    for(auto x:his){
        if(bigger(x, d1, m1, y1) && smaller(x, d2, m2, y2)){
            x.print();
            for(auto y : sp){
                if(y.name == x.name){
                    ans += (y.giaban - y.giagoc);
                }
            }
        }
    }
    return ans;
}







void saveSanphamListToFile(const vector<Sanpham>& sanphamList) {
    ofstream sanphamFile("data/sanpham.txt");
    if (sanphamFile.is_open()) {
        for (const auto& sp : sanphamList) {
            sanphamFile << sp.name << " " << sp.giaban << " " << sp.giagoc << endl;
        }
        sanphamFile.close();
    } else {
        cout << "Khong the mo file sanpham.txt de ghi" << endl;
    }
}

void saveHistoryListToFile(const vector<History>& historyList) {
    ofstream historyFile("data/history.txt");
    if (historyFile.is_open()) {
        for (const auto& h : historyList) {
            historyFile << h.name << " " << h.day << " " << h.month << " " << h.year << endl;
        }
        historyFile.close();
    } else {
        cout << "Khong the mo file history.txt de ghi" << endl;
    }
}

int menuBaoCao() {
    vector<Sanpham> sanphamList;
    vector<History> historyList;

    // Đọc dữ liệu từ file sanpham.txt
    ifstream sanphamFile("data/sanpham.txt");
    if (sanphamFile.is_open()) {
        string name;
        int giaban, giagoc;
        while (sanphamFile >> name >> giaban >> giagoc) {
            sanphamList.emplace_back(name, giaban, giagoc);
        }
        sanphamFile.close();
    } else {
        cout << "Khong the mo file sanpham.txt" << endl;
    }

    // Đọc dữ liệu từ file history.txt
    ifstream historyFile("data/history.txt");
    if (historyFile.is_open()) {
        string name;
        int day, month, year;
        while (historyFile >> name >> day >> month >> year) {
            historyList.emplace_back(name, day, month, year);
        }
        historyFile.close();
    } else {
        cout << "Khong the mo file history.txt" << endl;
    }



    while(true){
        cout << "1. xu huong ban hang" << endl;
        cout << "2. tinh doanh thu" << endl;
        cout << "3. so sanh doanh thu giua cac khoang thoi gian" << endl;
        cout << "4. exit" << endl;
        cout << "nhap lua chon: ";
        string t1; cin >> t1;
        int t = check(t1);
        if(t == 1) xuhuong(historyList);
        else if(t == 2) {
            int ans = doanhthu(sanphamList, historyList);
            cout << "TONG DOANH THU: " << ans << endl;
        }
        else if(t == 3){
            cout << "khoang thoi gian 1:" << endl;
            int res1 = doanhthu(sanphamList, historyList);
            cout << "khoang thoi gian 2:" << endl;
            int res2 = doanhthu(sanphamList, historyList);
            cout << "khoang thoi gian 1 co doanh thu la: " << res1 << endl;
            cout << "khoang thoi gian 2 co doanh thu la: " << res2 << endl;
            cout << "--> ";
            if(res1 > res2) cout << "doanh thu 1 > doanh thu 2: " << res1 - res2;
            else if(res1 < res2) cout << "doanh thu 2 > doanh thu 1: " << res2 - res1;
            else cout << "doanh thu 1 = doanh thu 2";
            cout << endl;
        }
        else if(t == 4){
            cout << "System out..." << endl;
            saveSanphamListToFile(sanphamList);
            saveHistoryListToFile(historyList);
            break;
        }
        else{
            cout << "vui long nhap lai: " << endl;
        }
        cout << "______________" << endl;
    }

    return 0;
}
