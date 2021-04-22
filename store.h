#pragma once
#include <map>
#include <iostream>

struct Item {
	char nama_barang[10];
	int harga;
};

class Store {
private:
	std::map <std::string, Item> category;
public:
	void insert() {
		category.insert({ "Elektronik", {"RAM", 10} });
	}
	void print() {
		std::cout << category["Elektronik"].harga;
	}
};