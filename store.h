#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <iomanip>
#define NAMA_LENGTH 30

struct Item {
	char nama_barang[NAMA_LENGTH];
	int harga;
};

class Store {
private:
	std::map <int, std::pair <std::string, std::vector <Item>>> category;
	void defaultItem();

public:
	Store() {
		defaultItem();
	}
	void print() {
		auto item = category[0].second;
		for (int i = 0; i < 10; ++i) {
			auto nama_barang_temp = (item[i].nama_barang);
			std::cout << nama_barang_temp << std::setw(NAMA_LENGTH - strlen(nama_barang_temp)) << item[i].harga << '\n';
			
		}
	}
};