#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Product{
public:
	int id;
	string name;
	double price;

	Product(int id, string name, double price): id(id), name(name), price(price){}
};

class Customer{
public:
	int customerId;
	string name;

	Customer(int customerId, string name) : customerId(customerId), name(name) {}
};

class Order{
public:
	int orderId;
	Customer customer;
	vector<Product> products;
	double totalAmount;

	Order(int orderId, Customer customer) : orderId(orderId), customer(customer), totalAmount(0){}

	void addProduct(Product product){
		products.push_back(product);
		totalAmount += product.price;
	}

	void displayOrderDetails(){
		cout << "Order id: " << orderId << "\nCustomer: "
		     << customer.name << "\nProducts:\n";
		for (auto &product : products){
			cout << "- " << product.name << " ($" << product.price << ")\n";
		}
		cout << "Total Amount: $" << totalAmount << "\n";
	}


};

class ShoppingApp{
private:
	vector<Product> productCatalog;
	vector<Customer> customers;
	vector<Order> orders;
	int nextOrderId = 1;
public:
	void addProduct(int id, string name, double price){
		productCatalog.emplace_back(id, name, price);
	}

	void addCustomer(int id, string name){
		customers.emplace_back(id, name);
	}

	Order placeOrder(int customerId, vector<int> productIds){
		Customer* customer = nullptr;
		for (auto &c: customers){
			if (c.customerId == customerId){
				customer = &c;
				break;
			}
		}


		if (!customer){
			cout << "Customer not found!" << endl;
			exit(1);
		}

		Order order(nextOrderId++, *customer);
		for (int productId : productIds) {
			for (auto &product : productCatalog){
				if (product.id == productId) {
					order.addProduct(product);
				}
			}
		}

		orders.push_back(order);
		return order;
	}
};
int main(){
	ShoppingApp app;

	app.addProduct(1, "Laptop", 1200.00);
	app.addProduct(2, "Smartphone", 800.00);
	app.addProduct(3, "Headphones", 150.00);

	app.addCustomer(101,"Alice");
	app.addCustomer(102,"Bob");

	Order order = app.placeOrder(101, {1,3});
	order.displayOrderDetails();

	return 0;

}
