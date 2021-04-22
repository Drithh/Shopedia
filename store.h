#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#define NAMA_LENGTH 30

struct Item {
	char nama_barang[NAMA_LENGTH];
	int harga;
};

struct less_than_key {
	inline bool operator() (const Item& struct1, const Item& struct2)
	{
		return (struct1.harga < struct2.harga);
	}
};

struct more_than_key {
	inline bool operator() (const Item& struct1, const Item& struct2)
	{
		return (struct1.harga > struct2.harga);
	}
};

class Store {
private:
	std::map <int, std::pair <std::string, std::vector <Item>>> category;
	void defaultItem();

public:
	Store() {
		defaultItem();
	}
	void printItem() {
		for (int j = 0; j < 5; ++j) {
			auto item = category[j].second;
			for (int i = 0; i < 10; ++i) {
				auto nama_barang_temp = (item[i].nama_barang);
				std::cout << nama_barang_temp << std::setw(NAMA_LENGTH - strlen(nama_barang_temp)) << item[i].harga << '\n';
			}
		}
	}
	
	void sort(bool condition) {
		std::vector <Item> full_item;
		int size = 0;
		for (int i = 0; i < 5; ++i) {
			size += category[0].second.size();
		}
		full_item.reserve(size);
		for (int i = 0; i < 5; ++i) {
			auto item = category[i].second;
			full_item.insert(full_item.end(), item.begin(), item.end());

		}
		if (condition) {
			std::sort(full_item.begin(), full_item.end(), less_than_key());
		}
		for (auto i : full_item) {
			std::cout << i.nama_barang << std::setw(NAMA_LENGTH - strlen(i.nama_barang)) << i.harga << '\n';
		}
	}
};