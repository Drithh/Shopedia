#include "store.h"
enum CategoryName
{
	Elektronik,
	Pakaian,
	Sepatu,
	Komputer,
	MataUang,
};
void Store::defaultItem() {
	category[Elektronik] = { "Elektronik", {{"Rice Cooker", 129}, {"Alat Penghancur Bumi", 10000}, {"Setika", 130}, {"Antena TV", 46}, {"Bluetooth Speaker", 160}, {"Smart Light Bulb", 125}, {"Kipas", 43}, {"Xiamoi TV BOX", 999}, {"Microwave", 299}, {"Air Conditioner", 2500}} };
}