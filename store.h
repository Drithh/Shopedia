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
	int state = 0;

	void defaultItem();
	void fullItem();

public:
	Store() { defaultItem(); }

	void printItem(std::vector <Item>& item_list);

	void findItem(std::string needle);
	void sortItem(bool condition);

	int intInput(int min, int max);
	void footer();

	void instruction() {
		enum Hub
		{
			SortItem = -2,
			FindItem,
			Hub,
		};
		while (true)
		{
			if (state == 0) {
				std::cout << "Selamat Datang Di Shopedia\n" <<
					"Silakhan pilih menu yang ada dibawah\n";
					for (int i = 0; i < 5; ++i) {
						std::cout << (i + 1) << ". " << category[i].first << '\n';
					}
			}
			else {
				printItem(category[state].second);
			}
			footer();
			state = intInput(-2, state == 0 ? 5 : category[state].second.size());
			switch (state)
			{
			case FindItem: {

			}break;
			case SortItem: {

			}break;
			default: {

			}break;
			}
		}

	}



};