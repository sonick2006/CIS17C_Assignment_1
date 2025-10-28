#include <iostream>
#include <vector>
#include <queue>
#include <map>


struct MenuItem{
        int id;
        std::string itemName;
        double unit_price;
};

struct OrderItem{
    int menuItemID;
    int qty;
};

enum class OrderStatus {
    Created,
    SentToKitchen,
    Ready,
    Closed
};

struct Order{
        int orderID;
        int tableID;
        std::vector<OrderItem> items;
        OrderStatus status = OrderStatus::Created;
};

struct Table{
        int tableID;
        int max_seats;
        bool occupied = false;
};

class Restaurant{
    private:
        std::map<int, MenuItem> menu;
        std::map<int, Table> tables;
        std::map<int, Order> orders;

        std::queue<int> kitchenQueue;

        std::vector<Order> closedOrders;

        int nextMenuItemID;
        int nextOrderID;

    public:
        Restaurant() : nextMenuItemID(1), nextOrderID(1) {}

        int addMenuItem(const std::string& name, double price){
            int id = nextMenuItemID++;
            menu[id] = {id, name,price};
            return id;
        }

        void removeMenuItem(int id){
            menu.erase(id);
            nextMenuItemID--;
        }

        int addTable(){
            int id = tables.size() + 1;
            tables[id] = {id, false};
            return id;
        }

        void removeTable(int id){
            tables.erase(id);
        }

        int createOrder(int tableID){
            if (tables[tableID].occupied) return -1;
            tables[tableID].occupied = true;
            orders[nextOrderID] = Order{nextOrderID, tableID};
            return nextOrderID++;
        }

        bool addItemToOrder(int orderID, int menuID, int qty){
            if (orders.find(orderID) == orders.end() || menu.find(menuID) == menu.end()) return false;
            orders[orderID].items.push_back({menuID, qty});
            return true;
        }

        bool sendOrderToKitchen(int orderId){
            if(orders.find(orderId) == orders.end()) return false;
            orders[orderId].status = OrderStatus::SentToKitchen;
            kitchenQueue.push(orderId);
            return true;
        }

        bool markOrderReady() {
            if(kitchenQueue.empty()) return false;
            int id = kitchenQueue.front();
            kitchenQueue.pop();
            orders[id].status = OrderStatus::Ready;
            return true;
        }

        bool closeOrder(int orderId){
            if(orders.find(orderId) == orders.end()) return false;
            orders[orderId].status = OrderStatus::Closed;
            tables[orders[orderId].tableID].occupied = false;
            closedOrders.push_back(orders[orderId]);
            orders.erase(orderId);
            return true;
        }


        double totalSales() const {
            double total = 0;
            for (auto const& co : closedOrders) {
                for (auto const& item : co.items) {
                    MenuItem mi = menu.at(item.menuItemID);
                    total += mi.unit_price * item.qty;
                }
            }

            return total;
        }

        void printMenu() const {
            std::cout << "Menu:\n";
            for (auto const& m : menu)
            std::cout << m.second.id << ". " << m.second.itemName << " $" << m.second.unit_price << "\n";
        }


        void printOrder(int orderId) const {
            auto it = orders.find(orderId);
            if (it == orders.end()) return;
            std::cout << "Order " << orderId << " (Table " << it->second.tableID << "):\n";
            for (auto const& item : it->second.items) {
                auto mi = menu.at(item.menuItemID);
                std::cout << " - " << mi.itemName << " x" << item.qty<< "\n";
        }
    }
            

};