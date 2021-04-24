#include <map>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>


#define ITEM_LENGTH 50


struct Item {
	std::string nama_barang;
	int harga;
};

struct less_than_key {
	inline auto operator() (const Item& struct1, const Item& struct2) -> bool
	{
		return (struct1.harga < struct2.harga);
	}
};

struct more_than_key {
	inline auto operator() (const Item& struct1, const Item& struct2) -> bool
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

	static auto intInput(int min, int max) -> int;
	auto askToBuy(int max) -> int;

	static void setColor(int forg_col);
	static void printItem(std::vector <Item>& item_list);

	void cart();
	void deletCartItem();
	void addItem();

	auto findItem() -> std::vector <Item>;
	auto sortItem() -> std::vector <Item>*;

	void footer();

public:
	Store() { defaultItem(); }

	void instruction();


};