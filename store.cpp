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
	category[Elektronik] = { "Elektronik", {{"Rice Cooker", 129}, {"Alat Penghancur Bumi", 10000}, {"Setika", 130}, {"Antena TV", 46}, {"Bluetooth Speaker", 160}, {"Smart Light Bulb", 125}, {"Kipas", 43}, {"Top Up FF", 59}, {"Microwave", 299}, {"Air Conditioner", 2500}} };
	category[Pakaian] = { "Pakaian", {{"LWIAY Merch", 720}, {"SIMP Tee", 500}, {"Baju Superman", 100}, {"Seragam Sekolah", 40}, {"Baju Polos", 50}, {"Celana Polos", 50}, {"Diamond Free Fire", 20}, {"Sepatu Bagian Kanan", 990}, {"Sepatu Bagian Kiri", 10}, {"Topi", 200}} };
	category[HobiKoleksi] = { "Hobi dan Koleksi", {{"Jubah Attack On Titan", 100}, {"Jubah FreeFire AOT", 100}, {"Action Figure Ace", 620}, {"Action Figure Luffy", 520}, {"Funko Superman", 395}, {"Top Up Demen FF", 13}, {"Hot Wheels", 120}, {"Light Stick", 20}, {"Gitar Akustik", 1200}, {"Floor Gang Tambourine", 6969}} };
	category[Komputer] = { "Komputer", {{"RAM 8GB", 700}, {"512GB NVME", 1050}, {"RAM 4GB", 400}, {"512 SSD Sata", 500}, {"Laptopnya Adriel", 9999999}, {"1TB Hardisk", 500}, {"Thermal Paste", 80}, {"Top Up Free Fire", 20}, {"Mouse Geming", 1000}, {"Mouse Bukan Geming", 100}} };
	category[MataUang] = { "Mata Uang Digital", {{"Ethereum", 3800}, {"Dogecoin", 3}, {"Litecoin", 4000}, {"Antena TV", 46}, {"Bitcoin", 785000}, {"Monero", 5400}, {"Top Up Free FIre", 1000}, {"Theter", 15}, {"Binance", 8000}, {"Uniswap", 540}} };
}