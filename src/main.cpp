#include "Restaurant.h"
#include "Windows.h"

int main(){

    Restaurant r;

    int table1 = r.addTable();
    r.addMenuItem("Burger", 8.50);
    r.addMenuItem("Fries", 3.00);
    r.addMenuItem("Mudpie", 100.50);

    r.printMenu();
    std::cout << "\n";
    Sleep(5000);

    r.removeMenuItem(3);
    r.printMenu();
    std::cout << "\n";
    Sleep(5000);

    int order = r.createOrder(table1);
    r.addItemToOrder(order, 1, 3);
    r.addItemToOrder(order, 2, 1);

    r.printOrder(order);
    Sleep(5000);
    std::cout << "\nSending to kitchen...\n";
    r.sendOrderToKitchen(order);
    Sleep(5000);

    r.markOrderReady();
    std::cout << "Order ready, closing...\n";
    r.closeOrder(order);
    Sleep(5000);

    std::cout << "Total sales: $" << r.totalSales() << std::endl;
}