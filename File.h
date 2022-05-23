#pragma once
#include <iostream>
#include <string>
using namespace std;
struct File
{
	struct Date {
		uint16_t day;
		uint16_t month;
		uint16_t year;
	};
	string cat;
	string name;
	string ext;
	Date date;
	size_t size;
	size_t getKey(size_t capacity) {
		size_t c = capacity / 3;
		size_t sum = 0;
		size_t sum1 = 0;
		for (int i = 0; i < cat.length(); i++) {
			sum += (sum * c + cat[i]) % capacity;
		}
		for (int i = 0; i < name.length(); i++) {
			sum1 += (sum1 * c + name[i]) % capacity;
		}
		return sum+sum1;
	}
	string getValue() {
		return cat + name + ext + ", Size: " + to_string(size) + " bytes, Date: " + to_string(date.day) + '.' + to_string(date.month) + '.' + to_string(date.year);
	}
};

