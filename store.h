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

	std::vector <Item> findItem();
	std::vector <Item>* sortItem();
	void footer();

public:
	Store() { defaultItem(); }

	void instruction() {
		enum Hub
		{
			SortItem = -2,
			FindItem,
			Menu,
		};
		while (true)
		{
			if (!size_buffer) {
				if (state == Menu) {
					std::cout << "Selamat Datang Di Shopedia\n" <<
						"Silakhan pilih menu yang ada dibawah\n";
						for (int i = 0; i < 5; ++i) {
							std::cout << (i + 1) << ". " << category[i].first << '\n';
						}
				}
				else {
					printItem(category[state-1].second);
				}
			}
			else {
				printItem(modified_vec);
			}

			footer();

			int user_input = state == 0 && size_buffer == 0 ? intInput(-2, 5) : askToBuy(size_buffer ? size_buffer : category[state - 1].second.size());
			if (state == 0 && size_buffer == 0 && user_input > 0) {
				modified_vec = category[user_input - 1].second;
				state = user_input;
			}
			size_buffer = 0;

			switch (user_input)
			{
			case FindItem:
				modified_vec  = findItem();
				size_buffer = modified_vec.size();
				break;
			case SortItem:
				modified_vec = *sortItem();
				size_buffer = modified_vec.size();
				break;
			}
		}

	}



};