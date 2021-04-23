#include "store.h"
enum CategoryName
{
	Elektronik,
	Pakaian,
	HobiKoleksi,
	Komputer,
	MataUang,
};
void Store::defaultItem() {
	category[Elektronik] = { "Elektronik", {
		{"Rice Cooker", 129}, {"Alat Penghancur Bumi", 10000}, {"Setika", 130}, {"Antena TV", 46}, {"Bluetooth Speaker", 160}, 
		{"Smart Light Bulb", 125}, {"Kipas", 43}, {"Top Up FF", 59}, {"Microwave", 299}, {"Air Conditioner", 2500}
	}};
	category[Pakaian] = { "Pakaian", {
		{"LWIAY Merch", 720}, {"SIMP Tee", 500}, {"Baju Superman", 100}, {"Seragam Sekolah", 40}, {"Baju Polos", 50}, 
		{"Celana Polos", 50}, {"Diamond Free Fire", 20}, {"Sepatu Bagian Kanan", 990}, {"Sepatu Bagian Kiri", 10}, {"Topi", 200}
	}};
	category[HobiKoleksi] = { "Hobi dan Koleksi", {
		{"Jubah Attack On Titan", 100}, {"Jubah FreeFire AOT", 100}, {"Action Figure Ace", 620}, {"Action Figure Luffy", 520}, {"Funko Superman", 395}, 
		{"Top Up Demen FF", 13}, {"Hot Wheels", 120}, {"Light Stick", 20}, {"Gitar Akustik", 1200}, {"Floor Gang Tambourine", 6969}
	}};
	category[Komputer] = { "Komputer", {
		{"RAM 8GB", 700}, {"512GB NVME", 1050}, {"RAM 4GB", 400}, {"512 SSD Sata", 500}, {"Laptopnya Adriel", 9999999}, 
		{"1TB Hardisk", 500}, {"Thermal Paste", 80}, {"Top Up Free Fire", 20}, {"Mouse Geming", 1000}, {"Mouse Bukan Geming", 100}
	}};
	category[MataUang] = { "Mata Uang Digital", {
		{"Ethereum", 3800}, {"Dogecoin", 3}, {"Litecoin", 4000}, {"Antena TV", 46}, {"Bitcoin", 785000}, 
		{"Monero", 5400}, {"Top Up Free FIre", 1000}, {"Theter", 15}, {"Binance", 8000}, {"Uniswap", 540}
	}};
}

void Store::fullItem() {
	full_item.clear();
	for (int i = 0; i < 5; ++i) {
		full_item.insert(full_item.end(), category[i].second.begin(), category[i].second.end());
	}
}


void Store::printItem(std::vector <Item>& item_list) {
	std::string metric = "KMBT";
	for (int i = 0; i < item_list.size(); ++i) {
		float harga = item_list[i].harga;
		int j = 0;
		for (j = 0; harga >= 1000; ++j) {
			harga /= 1000;
		}
		std::cout << (i+1) << "." << std::setw(i < 9 ? 2 : i < 99 ? 1 : 0) << ' ' << item_list[i].nama_barang << std::setw(NAMA_LENGTH - item_list[i].nama_barang.size()) << harga << metric[j] << '\n';
	}
}

void Store::findItem(std::string needle) {
	fullItem();
	std::vector <Item> item_found;
	for (int i = 0; i < full_item.size(); ++i) {
		if (full_item[i].nama_barang.find(needle) != std::string::npos) {
			item_found.push_back(full_item[i]);
		}
	}
	printItem(item_found);
}
void Store::sortItem(bool condition) {
	fullItem();
	if (condition) std::sort(full_item.begin(), full_item.end(), more_than_key());
	else std::sort(full_item.begin(), full_item.end(), less_than_key());
	printItem(full_item);
}

int Store::intInput(int min, int max) {
	int input;
	std::cout << "Silahkan masukan pilihan anda dari " << min << " sampai " << max << " : ";
		std::cin >> input;
		while (true) {
			if (!std::cin) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Inputnya Salah Coba Lagi : ";
			}
			else if (input < min || input > max) std::cout << "Inputnya Salah Coba Lagi : ";
			else return input;
		}
	} 


void Store::footer() {
	std::string kategori = state == 0 ? "Menu" : category[state].first;
	std::cout << "\n0.  Untuk Kembali Ke Menu \n" <<
		"-1. Untuk melakukan pencari item di kategori " + kategori + '\n' <<
		"-2. Untuk melakukan pengurutan item di kategori " + kategori + '\n';
}
