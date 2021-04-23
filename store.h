#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>


#define NAMA_LENGTH 50


struct Item {
	std::string nama_barang;
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
	std::vector <Item> full_item;
	std::vector <Item> modified_vec;
	std::vector <Item> receipt;

	int state = 0;
	int size_buffer = 0;
	void defaultItem();

	void fullItem();

	int intInput(int min, int max);
	int askToBuy(int max);

	void printItem(std::vector <Item>& item_list);

	void cart();
	void deletCartItem();

	std::vector <Item> findItem();
	std::vector <Item>* sortItem();
	void footer();

public:
	Store() { defaultItem(); }

	void instruction();

	void addItem() {
		std::cout << "\033[91m" << "Kategorinya apa?\n";
		for (int i = 0; i < 5; ++i) {
			std::cout << "\033[36m" << (i + 1) << ". " << category[i].first << '\n';
		}
		int input_category = intInput(1, 5);
		std::string nama_barang;
		while (true) {
			std::cout << "\033[36m" << "Masukkan nama item (maks 40 karakter) : ";
			std::cin.ignore();
			std::getline(std::cin, nama_barang);
			if(nama_barang.size() > 40 || nama_barang.size() < 1) {
				std::cout << "\033[36m" << "Nama Barang Jelek\n";
				nama_barang.clear();
				continue;
			}
			break;
		}
		std::cout << "\033[36m" << "Berapa Harganya ? (dalam ribuan)\n";
		int harga = intInput(1,INT_MAX);
		category[input_category - 1].second.push_back({ nama_barang, harga });
	}




};