#include "store.h"

void Store::defaultItem() {
	enum CategoryName
	{
		Elektronik,
		Pakaian,
		HobiKoleksi,
		Komputer,
		MataUang,
	};
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


auto Store::intInput(int min, int max) -> int {
	int input;
	std::cout << "\033[96m" << "Silahkan masukan pilihan anda dari " << min << " sampai " << max << " : ";
	while (true) {
		while (!(std::cin >> input)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Inputnya Salah Coba Lagi : ";
		}
		if (input < min || input > max) { std::cout << "Inputnya Salah Coba Lagi : ";
		} else {
			std::cout << "\n\n" << "\033[0m";
			return input;
		}
	}
}


auto Store::askToBuy(int max) -> int {
	std::cout << "\033[96m" << "Masukkan angka yang disebelah kiri nama barang jika kamu ingin membelinya\n" << "\033[0m";
	int user_input = intInput(-4, max);
	user_input == 0 ? state = 0 : 0;
	if (user_input > 0) {
		std::cout << "\033[96m" << '\n' << modified_vec[user_input - 1].nama_barang;
		std::cout << " Berhasil Ditambahkan Ke keranjang\n\n";
		receipt.push_back(modified_vec[user_input - 1]);
	}
	return user_input;
}


void Store::printItem(std::vector <Item>& item_list) {
	std::cout << "\033[93m";
	std::string metric = "KMBT";
	for (unsigned int i = 0; i < item_list.size(); ++i) {
		auto harga = (float) item_list[i].harga;
		int j = 0;
		for (j = 0; harga >= 1000; ++j) {
			harga /= 1000;
		}
		std::cout << (i+1) << "." << std::setw(i < 9 ? 2 : i < 99 ? 1 : 0) << ' ' << item_list[i].nama_barang << std::setw(NAMA_LENGTH - item_list[i].nama_barang.size()) << harga << metric[j] << '\n';
	}
	std::cout << "\033[0m";
}


void Store::cart() {
	enum cart
	{
		Back,
		DeleteCart,
		Pay,
	};
	while (true) {
		if (receipt.empty()) {
			std::cout << "Keranjang Anda Masih Kosong\n\n\n";
			return;
		}
		printItem(receipt);
		std::cout << "\033[97m" << "\n0. Untuk Kembali\n" <<
			"1. Menghapus Item Dalam keranjang\n" <<
			"2. Untuk Membayar\n\n\n" << "\033[0m";
		switch (intInput(0, 2))
		{
		case Back:
			return;
			break;
		case DeleteCart:
			deletCartItem();
			break;
		case Pay:
			std::cout << "Karena ini hanyalah toko Ghoib\n" <<
				"Maka anda tidak perlu membayar, tetapi anda\n" <<
				"juga tidak akan mendapat item yang anda pilih\n" <<
				"Terimakasih telah berbelanja dengan kami :DDDDDDDDDD\n\n\n";
			receipt.clear();
			return;
		}
	}
}


void Store::deletCartItem() {
	std::cout << "\033[96m" << "Apakah Anda Serius ingin menghapus barang dari keranjang ?\n0. Untuk Kembali\n" << "\033[0m";
	int delete_item = intInput(0, receipt.size());
	if ((bool)delete_item) {
		std::cout << "\033[96m" << receipt[delete_item - 1].nama_barang << " berhasil dihapus dari keranjang\n\n\n" << "\033[0m";
		receipt.erase(receipt.begin() + (delete_item - 1));
	}
}


void Store::addItem() {
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
		if (nama_barang.size() > 40 || nama_barang.empty()) {
			std::cout << "\033[36m" << "Nama Barang Jelek\n";
			nama_barang.clear();
			continue;
		}
		break;
	}
	std::cout << "\033[36m" << "Berapa Harganya ? (dalam ribuan)\n";
	int harga = intInput(1, INT_MAX);
	category[input_category - 1].second.push_back({ nama_barang, harga });
	std::cout << "\033[93m" << "Barang dengan nama " << category[input_category - 1].second.back().nama_barang << " sudah ditambah di kategori " << category[input_category - 1].first << "\n\n";
}


auto Store::findItem() -> std::vector <Item> {
	std::string needle;
	std::vector<Item>* v_find;
	std::vector<Item> item_found;

	std::cout << "\033[96m" << "Silahkan Masukkan Nama Barang yang dicari di " << (state == 0 ? "Menu" : category[state - 1].first) << " : ";
	std::cin >> needle;

	fullItem();

	if (state == 0) { v_find = &full_item;
	} else { v_find = &category[state - 1].second;
}


	for (auto i : *v_find) {
		if (i.nama_barang.find(needle) != std::string::npos) {
			item_found.push_back(i);
		}
	}

	if (item_found.empty()) { std::cout << "\033[96m" << "Maaf Itemnya tidak ditemukan di kategori ini\n\n" << "\033[0m";
}
	return item_found;
}


auto Store::sortItem() -> std::vector <Item>* {
	enum Sort {
		Ascending,
		Descending,
	};
	std::vector<Item>* v_sort;

	fullItem();
	if (state == 0) { v_sort = &full_item;
	} else { v_sort = &category[state - 1].second;
}

	std::cout << "\033[97m"  << "Silahkan Pilih\n1. Dari Yang Termurah\n2. Dari Yang Termahal\n" << "\033[0m";
	switch ((intInput(1, 2) - 1))
	{
	case Ascending:
		std::sort(v_sort->begin(), v_sort->end(), less_than_key());
		break;
	case Descending:
		std::sort(v_sort->begin(), v_sort->end(), more_than_key());
		break;
	}
	return v_sort;
}


void Store::footer() {
	std::string kategori = state == 0 ? "Menu" : category[state - 1].first;
	std::cout << "\033[97m" << "\n0.  Untuk Kembali Ke Menu \n" <<
		"-1. Untuk mencari item di kategori " + kategori + '\n' <<
		"-2. Untuk melakukan pengurutan item di kategori " + kategori + '\n' <<
		"-4. Untuk melihat Keranjang belanjaan anda\n" << 
		"-4. Untuk menambahkan item ke toko\n\n" << "\033[0m";
}



void Store::instruction() {
	enum Hub
	{
		AddItem		= -4,
		Cart,
		SortItem,
		FindItem,
		Menu,
	};
	while (true)
	{
		if (size_buffer == 0) {
			if (state == Menu) {
				std::cout << "\033[91m" << "Selamat Datang Di Shopedia\n" <<
					"Silakhan pilih menu yang ada dibawah\n" << "\033[0m";
				for (int i = 0; i < 5; ++i) {
					std::cout << "\033[36m" << (i + 1) << ". " << category[i].first << '\n';
				}
			}
			else {
				std::cout << "\033[36m" << std::setw((NAMA_LENGTH + 5) / 2) << "Kategori" << " " << category[state - 1].first << '\n';
				printItem(category[state - 1].second);
			}
		}
		else {
			printItem(modified_vec);
		}

		footer();

		int user_input = state == 0 && size_buffer == 0 ? intInput(-4, 5) : askToBuy(size_buffer != 0 ? size_buffer : category[state - 1].second.size());
		if (state == 0 && size_buffer == 0 && user_input > 0) {
			modified_vec = category[user_input - 1].second;
			state = user_input;
		}
		size_buffer = 0;

		switch (user_input)
		{
		case Cart:
			cart();
			break;
		case FindItem:
			modified_vec = findItem();
			size_buffer = modified_vec.size();
			break;
		case SortItem:
			modified_vec = *sortItem();
			size_buffer = modified_vec.size();
			break;
		case AddItem:
			addItem();
			break;
		}
	}

}


