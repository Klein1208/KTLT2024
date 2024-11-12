#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Supplier
{
public:
    int id;
    string name;
    string contact;
    string address;
    float rating;

    Supplier(int _id, string _name, string _contact, string _address, float _rating = 0.0)
        : id(_id), name(_name), contact(_contact), address(_address), rating(_rating) {}
};

class OrderSup
{
public:
    int id;
    int supplierId;
    string status;
    float amount;
    bool isPaid;

    OrderSup(int _id, int _supplierId, float _amount)
        : id(_id), supplierId(_supplierId), status("Pending"), amount(_amount), isPaid(false) {}
};

class SupplierManagementSystem
{
private:
    vector<Supplier> suppliers;
    vector<Order> orders;
    int nextSupplierId = 1;
    int nextOrderId = 1;

    // Hàm ghi danh sách nhà cung cấp vào file
    void saveSuppliersToFile()
    {
        ofstream outFile("data/nhacungcap.txt");
        if (outFile.is_open())
        {
            for (const auto &supplier : suppliers)
            {
                outFile << supplier.id << " " << supplier.name << " "
                        << supplier.contact << " " << supplier.address << " "
                        << supplier.rating << "\n";
            }
            outFile.close();
        }
        else
        {
            cout << "Khong the mo file de ghi.\n";
        }
    }

    // Hàm đọc danh sách nhà cung cấp từ file
    void loadSuppliersFromFile()
    {
        ifstream inFile("data/nhacungcap.txt");
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                istringstream iss(line);
                int id;
                string name, contact, address;
                float rating;

                // Đọc từng phần tử theo khoảng trắng
                if (iss >> id >> name >> contact >> address >> rating)
                {
                    suppliers.emplace_back(id, name, contact, address, rating);
                    nextSupplierId = max(nextSupplierId, id + 1); // Cập nhật ID tiếp theo
                }
            }
            inFile.close();
        }
    }

public:
    SupplierManagementSystem()
    {
        loadSuppliersFromFile(); // Tải dữ liệu từ file khi khởi động
        // cout << "Danh sach nha cung cap tu file nhacungcap.txt:\n";
        listSuppliers(); // In danh sách nhà cung cấp từ file
    }

    void addSupplier()
    {
        string name, contact, address;
        cout << "Nhap ten nha cung cap: ";
        cin.ignore();
        getline(cin, name);
        cout << "Nhap thong tin lien he nha cung cap: ";
        getline(cin, contact);
        cout << "Nhap dia chi nha cung cap: ";
        getline(cin, address);

        suppliers.emplace_back(nextSupplierId++, name, contact, address);
        cout << "Da them nha cung cap thanh cong.\n";
        saveSuppliersToFile();
        cout << "-----------------\n"; // Thêm dấu ----------------- sau khi nhập truy vấn
    }

    void deleteSupplier()
    {
        int id;
        cout << "Nhap ID nha cung cap can xoa: ";
        cin >> id;

        auto it = find_if(suppliers.begin(), suppliers.end(),
                          [id](const Supplier &s)
                          { return s.id == id; });

        if (it != suppliers.end())
        {
            suppliers.erase(it);
            cout << "Da xoa nha cung cap thanh cong.\n";
            saveSuppliersToFile();
        }
        else
        {
            cout << "Khong tim thay nha cung cap.\n";
        }
        cout << "-----------------\n"; // Thêm dấu ----------------- sau khi nhập truy vấn
    }

    void listSuppliers()
    {
        if (suppliers.empty())
        {
            cout << "Khong co nha cung cap nao.\n";
            return;
        }

        for (const auto &supplier : suppliers)
        {
            cout << "ID: " << supplier.id << ", Name: " << supplier.name
                 << ", Contact: " << supplier.contact << ", Address: " << supplier.address
                 << ", Rating: " << supplier.rating << "\n";
        }
        cout << "-----------------\n"; // Thêm dấu ----------------- sau khi nhập truy vấn
    }

    void rateSupplier()
    {
        int supplierId;
        float rating;

        cout << "Nhap ID nha cung cap can danh gia: ";
        cin >> supplierId;

        auto it = find_if(suppliers.begin(), suppliers.end(),
                          [supplierId](const Supplier &s)
                          { return s.id == supplierId; });

        if (it != suppliers.end())
        {
            cout << "Nhap danh gia (0-5): ";
            cin >> rating;

            if (rating >= 0 && rating <= 5)
            {
                it->rating = rating;
                cout << "Da danh gia nha cung cap thanh cong.\n";
            }
            else
            {
                cout << "Danh gia khong hop le. Vui long nhap gia tri tu 0 den 5.\n";
            }
        }
        else
        {
            cout << "Khong tim thay nha cung cap.\n";
        }
        cout << "-----------------\n"; // Thêm dấu ----------------- sau khi nhập truy vấn
    }

    void exitAndSave()
    {
        saveSuppliersToFile();
    }
};

void menu_Supplier()
{
    SupplierManagementSystem system;
    int choice;

    do
    {
        cout << "=== Quan ly Nha cung cap ===\n";
        cout << "1. Them nha cung cap\n";
        cout << "2. Xoa nha cung cap\n";
        cout << "3. Xem danh sach nha cung cap\n";
        cout << "4. Danh gia nha cung cap\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin.ignore();
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.addSupplier();
            break;
        case 2:
            system.deleteSupplier();
            break;
        case 3:
            system.listSuppliers();
            break;
        case 4:
            system.rateSupplier();
            break;
        case 0:
            system.exitAndSave();
            cout << "Dang thoat...\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (choice != 0);

    //return 0;
}
