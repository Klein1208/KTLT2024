#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "source.h"
using namespace std;

// Thông tin cơ bản của sản phẩm
class Product {	
public:
    string name;
    int itemId;
    double price;
    double cost;

    // Nhập thông tin sản phẩm
    void add_infor(const vector<Product>& danhsachspcu) {
        cout << "Nhập tên sản phẩm: ";
        getline(cin, name);
        while (name.empty()) {
            cout << "Tên sản phẩm đang bị bỏ trống. Thử lại: ";
            getline(cin, name);
        }

        do {
            itemId = 10000 + rand() % 90000; // Sinh số ngẫu nhiên từ 10000 đến 99999
        } while (ktID(itemId, danhsachspcu));

        cout << "ID sản phẩm (đã sinh ngẫu nhiên): " << itemId << endl;

        
        while(true){
        	cout<<"Nhập giá nguyên liệu ";
        	string goc;
        	getline(cin, goc);
        	try{
        		cost= stod(goc);
        		if(cost<0){
        			cout<<"Cost không hợp lệ. Thử lại.\n";
        			continue;
				}
				break;
			} catch (const exception& e) {
                cout << "Lỗi " << e.what() << " Thử lại.\n";}
        	
		}
        while (true) {
            cout << "Nhập giá bán: ";
            string gia;
            getline(cin, gia);
            try {
                price = stod(gia);
                if (price < 0) {
                    cout << "Gía nhập không hợp lệ. Thử lại.\n";
                    continue;
                }
                break;
            } catch (const exception& e) {
                cout << "Lỗi " << e.what() << " Thử lại.\n";
            }
        }
    }

    void display() const {
        cout << left << "Tên sản phẩm: " << name << "\n";
        cout << left << "ID sản phẩm: " << itemId << "\n";
        cout << left << "Cost sản phẩm: "<<fixed<<setprecision(3)<<cost <<"\n";
        cout << left << "Gía sản phẩm: " << fixed << setprecision(3) << price << "\n";
        cout << "--------------------------\n";
    }

private:
    // Hàm kiểm tra trùng ID
    bool ktID(int id, const vector<Product>& products) const {
        for (const auto& product : products) {
            if (product.itemId == id) return true;
        }
        return false;
    }
};

// Quản lý danh sách sản phẩm
class List {
public:
    vector<Product> products;

    // Đọc dữ liệu từ file CSV
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Không thể mở file.\n";
            return;
        }
        products.clear(); // Xóa danh sách hiện tại

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, itemIdStr, costStr, priceStr;

            getline(ss, name, ',');
            getline(ss, itemIdStr, ',');
            getline(ss,costStr, ',');
            getline(ss, priceStr, ',');

            Product product;
            product.name = name;
            product.itemId = stoi(itemIdStr);
            product.cost = stod(costStr);
            product.price = stod(priceStr);

            products.push_back(product);
        }
        file.close();
        // cout << "Đã tải dữ liệu từ file " << filename << ".\n";
    }

    // Ghi dữ liệu vào file CSV
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Không thể mở file.\n";
            return;
        }
        for (const auto& product : products) {
            file << product.name << "," << product.itemId << "," <<product.cost<< "," << product.price << "\n";
        }

        file.close();
        cout << "Cập nhật thành công.\n";
    }

    void AddItem() {
        int numItemadd = 0;
        cout << "Nhập số lượng sản phẩm muốn thêm vào: ";
        while (!(cin >> numItemadd) || numItemadd <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Số lượng thêm không hợp lệ.\nThử lại: ";
        }
        cin.ignore();

        for (int i = 0; i < numItemadd; i++) {
            Product newp;
            newp.add_infor(products);
            products.push_back(newp);
            cout << "Thêm sản phẩm thành công!\n";
        }
    }

    void ShowItemList() const {
        if (products.empty()) {
            cout << "Danh sách sản phẩm trống.\n";
            return;
        }
        cout << "\n=== Danh sách sản phẩm ===\n";
        for (size_t i = 0; i < products.size(); i++) {
            cout << "No. " << i + 1 << ":\n";
            products[i].display();
        }
    }

    void Total() const {
        if (products.empty()) {
            cout << "Danh sách sản phẩm trống.\n";
            return;
        }
        double sum = 0.0;
        for (const auto& p : products)
            sum += p.price;
        cout << "Tổng giá sản phẩm: " << fixed << setprecision(3) << sum << "\n";
    }

    void deleteProduct() {
        if (products.empty()) {
            cout << "Danh sách sản phẩm trống.\n";
            return;
        }
        int id;
        cout << "Nhập ID sản phẩm muốn xóa: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID vừa nhập không hợp lệ.\nThử lại: ";
        }
        cin.ignore();

        auto it = find_if(products.begin(), products.end(), [&](const Product& p) {
            return p.itemId == id;
        });

        if (it != products.end()) {
            products.erase(it);
            cout << "Xóa sản phẩm thành công.\n";
        } else {
            cout << "Không tìm thấy sản phẩm với ID vừa nhập.\n";
        }
    }

    void editProduct() {
        if (products.empty()) {
            cout << "Danh sách sản phẩm trống.\n";
            return;
        }
        int id;
        cout << "Nhập ID sản phẩm cần sửa: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ID không hợp lệ.\nThử lại: ";
        }
        cin.ignore();

        auto it = find_if(products.begin(), products.end(), [&](const Product& p) {
            return p.itemId == id;
        });

        if (it != products.end()) {
            cout << "Nhập thông tin mới cho sản phẩm:\n";
            it->add_infor(products);
            cout << "Cập nhật thông tin sản phẩm thành công.\n";
        } else {
            cout << "Không tìm thấy sản phẩm với ID vừa nhập.\n";
        }
        saveToFile("products.csv");
    }

    void searchProduct() const {
        if (products.empty()) {
            cout << "Danh sách sản phẩm trống.\n";
            return;
        }
        cout << "Tìm sản phẩm với :\n"
             << "1. ID\n"
             << "2. Tên sản phẩm\n"
             << "Lựa chọn (1-2): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int id;
            cout << "Nhập ID sản phẩm: ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ID không hợp lệ. Thử lại: ";
            }
            cin.ignore();

            auto it = find_if(products.begin(), products.end(), [&](const Product& p) {
                return p.itemId == id;
            });

            if (it != products.end()) {
                it->display();
            } else {
                cout << "Không tìm thấy sản phẩm với ID vừa nhập.\n";
            }
        } else if (choice == 2) {
            string searchName;
            cout << "Nhập tên sản phẩm: ";
            getline(cin, searchName);
            bool found = false;
            for (const auto& p : products) {
                if (p.name.find(searchName) != string::npos) {
                    p.display();
                    found = true;
                }
            }
            if (!found) {
                cout << "Không tìm thấy sản phẩm với tên vừa nhập.\n";
            }
        } else {
            cout << "Lựa chọn không thỏa mãn.\n";
        }
    }
};

// Quản lý đơn hàng
class Order {
public:
    int orderId;
    vector<Product> orderItems;
    string customerName;
    string customerPhone;
    string saleDate;

    Order(int id, string customer, string phone) : orderId(id), customerName(customer), customerPhone(phone) {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        saleDate = to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_year + 1900);
    }

    void addProduct(const Product& product) {
        orderItems.push_back(product);
        cout << "Sản phẩm đã được thêm vào đơn hàng.\n";
    }

    void removeProduct(int itemId) {
        auto it = find_if(orderItems.begin(), orderItems.end(), [&](const Product& p) {
            return p.itemId == itemId;
        });
        if (it != orderItems.end()) {
            orderItems.erase(it);
            cout << "Sản phẩm đã được xóa khỏi đơn hàng.\n";
        } else {
            cout << "Không tìm thấy sản phẩm với mã ID này.\n";
        }
    }

    double totalOrder() const {
        double total = 0.0;
        for (const auto& p : orderItems) {
            total += p.price;
        }
        return total;
    }

    void viewOrderDetails() const {
        cout << "\n=== Chi tiết đơn hàng ===\n";
        cout << "Mã đơn hàng: " << orderId << "\n";
        cout << "Tên khách hàng: " << customerName << "\n";
        cout << "Số điện thoại: " << customerPhone << "\n";
        cout << "Ngày bán: " << saleDate << "\n";
        for (const auto& p : orderItems) {
            p.display();
        }
        cout << "Tổng giá trị đơn hàng: " << fixed << setprecision(3) << totalOrder() << "\n";
    }
};

// Quản lý đơn hàng
class OrderManager {
private:
    vector<Order> orders;

public:
    void createOrder(List& shop) {
        int orderId;
        string customerName, customerPhone;

        do {
            orderId = 10000 + rand() % 90000; // Sinh mã đơn hàng tự động
        } while (ktOrderId(orderId));

        cout << "Nhập tên khách hàng: ";
        cin.ignore();  // Đảm bảo không có ký tự dư thừa trong bộ đệm
        getline(cin, customerName);

        cout << "Nhập số điện thoại khách hàng: ";
        getline(cin, customerPhone);

        Order newOrder(orderId, customerName, customerPhone);
        orders.push_back(newOrder);
        cout << "Đã tạo đơn hàng mới thành công.\n";

        char addMore = 'y';
        while (addMore == 'y') {
            int productId;
            shop.ShowItemList();
            cout << "Nhập mã sản phẩm để thêm vào đơn hàng: ";
            cin >> productId;
            cin.ignore();

            auto it = find_if(shop.products.begin(), shop.products.end(), [&](const Product& p) {
                return p.itemId == productId;
            });

            if (it != shop.products.end()) {
                newOrder.addProduct(*it);
            } else {
                cout << "Không tìm thấy sản phẩm.\n";
            }

            cout << "Bạn có muốn thêm sản phẩm khác vào đơn hàng? (y/n): ";
            cin >> addMore;
            cin.ignore();
        }
    }

    void loadFromFile2(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Không thể mở file.\n";
            return;
        }
        orders.clear(); // Xóa danh sách hiện tại

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string orderId, customerName, customerPhone, saleDate;

            getline(ss, orderId, ',');
            getline(ss, customerName, ',');
            getline(ss, customerPhone, ',');
            getline(ss, saleDate, ',');

            Order order(stoi(orderId), customerName, customerPhone);
            orders.push_back(order);
        }
        file.close();
        
    }

    void saveToFile2(const string& filename = "order.csv") const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Không thể mở file.\n";
            return;
        }
        for (const auto& order : orders) {
            file << order.orderId << "," << order.customerName << "," << order.customerPhone << "," << order.saleDate << "\n";
        }

        file.close();
        cout << "Cập nhật thành công.\n";
    }

    void searchOrder() const {
        cout << "Tìm đơn hàng theo:\n"
             << "1. Mã đơn hàng\n"
             << "2. Tên khách hàng\n"
             << "Chọn chức năng (1-2): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
      
            int searchId;
            cout << "Nhập mã đơn hàng: ";
            cin >> searchId;

            auto it = find_if(orders.begin(), orders.end(), [&](const Order& o) {
                return o.orderId == searchId;
            });

            if (it != orders.end()) {
                it->viewOrderDetails();
            } else {
                cout << "Không tìm thấy đơn hàng với mã này.\n";
            }
        } else if (choice == 2) {
            string searchName;
            cout << "Nhập tên khách hàng: ";
            getline(cin, searchName);

            bool found = false;
            for (const auto& order : orders) {
                if (order.customerName == searchName) {
                    order.viewOrderDetails();
                    found = true;
                }
            }

            if (!found) {
                cout << "Không tìm thấy đơn hàng của khách hàng này.\n";
            }
        }
    }

    bool ktOrderId(int orderId) const {
        for (const auto& order : orders) {
            if (order.orderId == orderId) return true;
        }
        return false;
    }
};

void InMenuSanPham(){
    
    cout << "=== Quản lý sản phẩm ===\n";
        cout << "1. Thêm sản phẩm\n";
        cout << "2. Hiển thị danh sách sản phẩm\n";
        cout << "3. Xóa sản phẩm\n";
        cout << "4. Sửa thông tin sản phẩm\n";
        cout << "5. Tìm kiếm sản phẩm\n";
        cout << "6. Tổng các giá trị sản phẩm trong danh sách\n";
        cout << "7. Trở về Menu\n";
        cout << "Lựa chọn (1-7): ";
        
}
void Chon();

void menuSanPham()
{
    List shop;
    int mainChoice;
    int productChoice;
    string link = "data/products.csv";
    shop.loadFromFile(link);
    while (true)
    {
        
        InMenuSanPham();
        cin.ignore();
        cin >> productChoice;
        if (productChoice == 1)
        {
            shop.AddItem();
            shop.saveToFile(link); // Lưu vào file sau khi thêm sản phẩm
        }
        else if (productChoice == 2)
        {
            shop.ShowItemList();
        }
        else if (productChoice == 3)
        {
            shop.deleteProduct();
            shop.saveToFile(link); // Lưu vào file sau khi xóa sản phẩm
        }
        else if (productChoice == 4)
        {
            shop.editProduct();
            shop.saveToFile(link); // Lưu vào file sau khi sửa sản phẩm
        }
        else if (productChoice == 5)
        {
            shop.searchProduct();
        }
        else if (productChoice == 6)
            shop.Total();
        else if (productChoice == 7)
        {   
            Chon();
            break;
        }
        else
        {
            cout << "Lựa chọn không hợp lệ. Thử lại.\n";
        }
    }
};
void InMenuDon(){

    cout << "=== Quản lý đơn hàng ===\n";
        cout << "1. Tạo đơn hàng mới\n";
        cout << "2. Tìm kiếm đơn hàng\n";
        cout << "3. Trở về Menu\n";
        cout << "Lựa chọn (1-3): ";
        
}

void menuDon(){
    int orderChoice;
    List shop;
    OrderManager orderManager;
    shop.loadFromFile("data/products.csv");
    orderManager.loadFromFile2("data/order.csv");
    while (true)
    {
        InMenuDon();
        cin.ignore();
        cin >> orderChoice;
        if (orderChoice == 1)
        {
            orderManager.createOrder(shop);
            orderManager.saveToFile2("data/order.csv");
        }
        else if (orderChoice == 2)
        {
            orderManager.searchOrder();
        }
        else if (orderChoice == 3)
        {
            Chon();
        }
        else
        {
            cout << "Lựa chọn không hợp lệ. Thử lại.\n";
        }
    }
}