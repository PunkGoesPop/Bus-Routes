
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


bool isFoundStop(map<string, vector<string>>& routes, string& stop_name) {
	bool result = false;

	for (auto& item : routes)
	{
		for (string& word : item.second)
		{
			if (word == stop_name)
				result = true;
		}
	}
	return result;
}

bool isFoundBus(map<string, vector<string>> &routes, string& stop_name, string& bus_name) {

	bool res = false;

	for (auto& word : routes[stop_name]) {
		if (word == bus_name) {
			res = true;
		}
	}
	return res;
}

//void PrintFoundBus(map<string, vector<string>>& routes, vector<string>& init_buses) {
//
//	for (auto& item : ) {
//		cout << word << " ";
//	}
//}
	


int main()
{
	map<string, vector<string>> routes;
	vector<string> init_buses;

	int q = 0;
	cin >> q;

	for (int i = 0; i < q; i++)
	{
		string operation;
		cin >> operation;

		//Добавление маршрута автобуса с названием автобуса, кол-во остановок, их название
		if (operation == "NEW_BUS")
		{
			vector<string> stops;
			string bus_name;
			string stop_name;
			int stop_count;
			cin >> bus_name >> stop_count;
			//проверка на введение одного маршрута несколько раз
			if (routes[bus_name].empty()) {
				//заполнение введёных пользавателем данных
				for (int i = 0; i < stop_count; i++) { 
					cin >> stop_name; stops.push_back(stop_name); 
				}
				//заполнение массива изначально заданных автобусов
				init_buses.push_back(bus_name);

			}
			
			for (auto& word : stops) {
				routes[bus_name].push_back(word);
			}
		}
		//Вывод всех маршрутных автобусов, проходящих через заданую пользователем остановку
		if (operation == "BUSES_FOR_STOP")
		{
			string stop_name;
			cin >> stop_name;
			if (isFoundStop(routes, stop_name)) {
				for (auto item : init_buses)
					for (string word : routes[item]) {
						if (word == stop_name) {
							cout << item << " ";
						}
					}
				cout << endl;
			}
			else {
				cout << "No stop" << endl;
			}
		}
		//Вывод всех остановок bus_name, и список автобусов на которые можно пересесит на каждой из остановок
		if (operation == "STOPS_FOR_BUS")
		{
			string bus_name;
			cin >> bus_name;

			if (!(routes[bus_name].empty())) {
				for (auto& z : routes[bus_name]) {
					cout << "Stop " << z << ": ";
					vector<string> buses;
					for (auto& item : routes) {
						for (string& word : item.second) {
							if (word == z && item.first != bus_name) {
								buses.push_back(item.first);
							}
						}
					}
					if (!buses.empty()) {
						// ZDES'
						for (auto& i : init_buses) {
							for (auto& j : buses) {
								if (i == j) {
									cout << i << " ";
								}
							}
						}
						cout << endl;
					}
					else {
						cout << "no interchange";
						cout << endl;
					}
				}
			}
			else {
				cout << "No bus" << endl;
				routes.erase(bus_name);
			}
		}
		//Вывод всех маршрутов с остановками
		if (operation == "ALL_BUSES")
		{
			if(!(routes.empty()))
			for (auto& item : routes) {
				cout << "Bus " << item.first << ": ";
				for (string& word : item.second) {
					cout << word << " ";
				}
				cout << endl;
			}
			else {
				cout << "No buses" << endl;
			}
		}

		//TEST
		if (operation == "TEST")
		{
			for (auto& i : init_buses)
				cout << i << " ";
			cout << endl;
			string stop_name;
			cin >> stop_name;
			for(auto item : init_buses)
				for (string word : routes[item]) {
					if (word == stop_name) {
						cout << item<< " ";
					}
				}
			cout << endl;
		}
	}
	return 0;
}




