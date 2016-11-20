// ing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string MD;
	cout << "Введите название вводного файла: ";
	cin >> MD;
	cout << "Дождитесь окончания сортировки..";
	ifstream my_read_file(MD);
	string MAP = "MAP.txt";
	ofstream my_write_file(MAP);

	//проверю, что файлы действительно открыты
	if (!my_read_file.is_open())
	{
		cout << "cannot open file for read" << MD << "\n";
		return -1;
	}

	if (!my_write_file.is_open())
	{
		cout << "cannot open file for write : " << MAP << "\n";
		return -1;
	}

	map<string, int> my_map;

	while (!my_read_file.eof())
	{
		string original_str;
		my_read_file >> original_str;
		string str = "";
		//удаление лишних символов во взятом слове 
		for (int i = 0; i < original_str.length(); i++) {
			char c = original_str[i];
			if (c != '(' &&
				c != ')' &&
				c != '.' &&
				c != ',' &&
				c != '-' &&
				c != ':' &&
				c != ';' &&
				c != '\'' &&
				c != '\"' &&
				c != '!' &&
				c != '&' &&
				c != '{' &&
				c != '}' &&
				c != '/' &&
				c != '\\' &&
				c != '^' &&
				c != '|' &&
				c != '~' &&
				c != '?')
			{
				str += c;
			}
		}

		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		auto it = my_map.find(str);
		if (it != my_map.end())
			//if (my_map.count(str)) 
		{
			//auto it = my_map.find(str);
			(*it).second += 1;
		}
		else
		{
			my_map[str] = 1;
		}
	}
	map<string, int>::iterator it;
	int size = my_map.size();
	for (int i = 0; i < size; i++)
	{
		int value = 0;
		string str;
		map<string, int>::iterator it_found;
		for (it = my_map.begin(); it != my_map.end(); it++)
		{
			if ((*it).second > value)
			{
				str = (*it).first;
				value = (*it).second;
				it_found = it;
			}
		}
		if (str != "")
		{
			my_write_file << my_map[str] << " : " << str << endl;
		}
		my_map.erase(it_found);
	}

	//закрываю файл
	my_read_file.close();
	my_write_file.close();

	return 0;
}