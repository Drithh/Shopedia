#include "store.h"

enum ConsoleColor {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White,
};


#ifdef  _WIN32
#include <windows.h>
#undef max
void Store::setColor(const int forg_col)
{
	const auto h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(h_std_out, &csbi) != 0)
	{
		const WORD w_color = (csbi.wAttributes & 0xF0) + (forg_col & 0x0F);
		SetConsoleTextAttribute(h_std_out, w_color);
	}
}
#else
void Store::setColor(const int forg_col) {
}
#endif // ! WIN32


void Store::instruction() {
	enum Hub
	{
		AddItem = -4,
		Cart,
		SortItem,
		FindItem,
		Menu,
	};
	while (true)
	{
		if (size_buffer == 0) {
			if (state == Menu) {
				setColor(LightRed);
				std::cout << "Selamat Datang Di Shopedia\n" <<
					"Silakhan pilih menu yang ada dibawah\n";
				for (int i = 0; i < 5; ++i) {
					setColor(Cyan);
					std::cout << (i + 1) << ". " << category[i].first << '\n';
				}
			}
			else {
				setColor(Cyan);
				std::cout << std::setw((ITEM_LENGTH + 5) / 2) << "Kategori" << " " << category[state - 1].first << '\n';
				printItem(category[state - 1].second);
			}
		}
		else {
			printItem(vec_item);
		}

		footer();

		int user_input = state == 0 && size_buffer == 0 ? intInput(-4, 5) : askToBuy(size_buffer != 0 ? size_buffer : category[state - 1].second.size());
		if (state == 0 && size_buffer == 0 && user_input > 0) {
			vec_item = category[user_input - 1].second;
			state = user_input;
		}
		size_buffer = 0;

		switch (user_input)
		{
		case Cart:
			cart();
			break;
		case FindItem:
			vec_item = findItem();
			size_buffer = vec_item.size();
			break;
		case SortItem:
			vec_item = sortItem();
			size_buffer = vec_item.size();
			break;
		case AddItem:
			addItem();
			break;
		}
	}

}



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
	vec_item.clear();
	for (int i = 0; i < 5; ++i) {
		vec_item.insert(vec_item.end(), category[i].second.begin(), category[i].second.end());
	}
}


auto Store::intInput(const int min, const int max) -> int {
	int input;
	setColor(LightCyan);
	std::cout << "Silahkan masukan pilihan anda dari " << min << " sampai " << max << " : ";
	while (true) {
		while (!(std::cin >> input)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Inputnya Salah Coba Lagi : ";
		}
		if (input < min || input > max) { std::cout << "Inputnya Salah Coba Lagi : ";
		} else {
			std::cout << "\n\n";
			return input;
		}
	}
}


auto Store::askToBuy(const int max) -> int {
	setColor(LightCyan);
	std::cout << "Masukkan angka yang disebelah kiri nama barang jika kamu ingin membelinya\n";
	int user_input = intInput(-4, max);
	user_input == 0 ? state = 0 : 0;
	if (user_input > 0) {
		std::cout << '\n' << vec_item.at(user_input - 1).nama_barang;
		std::cout << " Berhasil Ditambahkan Ke keranjang\n\n";
		receipt.push_back(vec_item.at(user_input - 1));
	}
	return user_input;
}


void Store::printItem(std::vector <Item>& item_list) {
	setColor(Yellow);
	std::string metric = "KMBT";
	for (unsigned int i = 0; i < item_list.size(); ++i) {
		auto harga = (float) item_list[i].harga;
		int j = 0;
		for (j = 0; harga >= 1000; ++j) {
			harga /= 1000;
		}
		std::cout << (i+1) << "." << std::setw(i < 9 ? 2 : i < 99 ? 1 : 0) << ' ' << item_list[i].nama_barang << std::setw(ITEM_LENGTH - item_list[i].nama_barang.size()) << harga << metric[j] << '\n';
	}
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


		double total_cart = 0;
		for (auto i : receipt) {
			total_cart += i.harga;
		}
		int j = 0;
		for (j = 0; total_cart >= 1000; ++j) {
			total_cart /= 1000;
		}
		std::string metric = "KMBT";
		std::string output_text = "Total Belanjaan Anda adalah ";
		std::cout << "\n\n" << output_text << std::setw(ITEM_LENGTH + 4 - output_text.size())<< total_cart << metric[j] << "\n\n";


		setColor(White);
		std::cout << "\n0. Untuk Kembali\n" <<
			"1. Menghapus Item Dalam keranjang\n" <<
			"2. Untuk Membayar\n\n\n";
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
	setColor(LightCyan);
	std::cout << "Apakah Anda Serius ingin menghapus barang dari keranjang ?\n";
	setColor(White);
	std::cout << "0. Untuk Kembali\n" ;
	setColor(LightCyan);
	int delete_item = intInput(0, receipt.size());
	if ((bool)delete_item) {
		std::cout << receipt[delete_item - 1].nama_barang << " berhasil dihapus dari keranjang\n\n\n";
		receipt.erase(receipt.begin() + (delete_item - 1));
	}
}


void Store::addItem() {
	setColor(LightRed);
	std::cout << "Kategorinya apa?\n";
	for (int i = 0; i < 5; ++i) {
		setColor(Cyan);
		std::cout << (i + 1) << ". " << category[i].first << '\n';
	}
	int input_category = intInput(1, 5);
	std::string nama_barang;
	while (true) {
		setColor(Cyan);
		std::cout << "Masukkan nama item (maks 40 karakter) : ";
		std::cin.ignore();
		std::getline(std::cin, nama_barang);
		if (nama_barang.size() > 40 || nama_barang.empty()) {
			std::cout << "Nama Barang Jelek\n";
			nama_barang.clear();
			continue;
		}
		break;
	}
	std::cout << "Berapa Harganya ? (dalam ribuan)\n";
	int harga = intInput(1, INT_MAX);
	category[input_category - 1].second.push_back({ nama_barang, harga });
	setColor(Yellow);
	std::cout << "Barang dengan nama " << category[input_category - 1].second.back().nama_barang << " sudah ditambah di kategori " << category[input_category - 1].first << "\n\n";
}


auto Store::findItem() -> std::vector <Item> {
	std::string needle;
	std::vector<Item>* v_find;
	std::vector<Item> item_found;
	setColor(LightCyan);
	std::cout << "Silahkan Masukkan Nama Barang yang dicari di " << (state == 0 ? "Menu" : category[state - 1].first) << " : ";
	std::cin >> needle;

	fullItem();

	if (state == 0) { v_find = &vec_item;
	} else { v_find = &category[state - 1].second;
	}


	for (auto i : *v_find) {
		if (i.nama_barang.find(needle) != std::string::npos) {
			item_found.push_back(i);
		}
	}

	if (item_found.empty()) { std::cout << "Maaf Itemnya tidak ditemukan di kategori ini\n\n"; }
	return item_found;
}


auto Store::sortItem() -> std::vector <Item> {
	enum Sort {
		Ascending,
		Descending,
	};
	std::vector<Item> v_sort;

	fullItem();
	if (state == 0) { v_sort = vec_item;
	} else { v_sort = category[state - 1].second;
}
	setColor(White);

	std::cout << "Silahkan Pilih\n1. Dari Yang Termurah\n2. Dari Yang Termahal\n";
	switch ((intInput(1, 2) - 1))
	{
	case Ascending:
		std::sort(v_sort.begin(), v_sort.end(), less_than_key());
		break;
	case Descending:
		std::sort(v_sort.begin(), v_sort.end(), more_than_key());
		break;
	}
	return v_sort;
}


void Store::footer() {
	std::string kategori = state == 0 ? "Menu" : category[state - 1].first;
	setColor(White);
	std::cout << "\n0.  Untuk Kembali Ke Menu \n" <<
		"-1. Untuk mencari item di kategori " + kategori + '\n' <<
		"-2. Untuk melakukan pengurutan item di kategori " + kategori + '\n' <<
		"-3. Untuk melihat Keranjang belanjaan anda\n" << 
		"-4. Untuk menambahkan item ke toko\n\n";
}





