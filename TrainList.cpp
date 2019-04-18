// TrainList.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <string>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

void skip_line(istream& in)
{
	in.ignore(numeric_limits<int>::max(), '\n');
}

class train
{
private:
	string place_; // Пункт назначения
	int number_; // Номер поезда
	int time_; // Время отправления

public:
	train() : place_(), number_(0), time_(0) {}
	train(string const& place, int number, int time) : place_(place), number_(number), time_(time) {}
	train(train const& t) : place_(t.place_), number_(t.number_), time_(t.time_) {}
	
	string const& get_place() const { return place_; }
	int get_number() const { return number_; }
	int get_time() const { return time_; }

	// Перегруженный оператор '=='
	bool operator==(const train& t) const { return (place_ == t.place_) && (number_ == t.number_) && (time_ == t.time_) ; }
	// Перегруженный оператор '<'
	bool operator<(const train& t) const { return (number_ < t.number_); }
	
	void read(istream& in)
	{
		cout << "\n\t\tPlace: ";
		string place;
		in >> place;
		cout << "\t\tNumber: ";
		int number;
		in >> number;
		cout << "\t\tTime: ";
		int time;
		in >> time;
		skip_line(in);
			
		place_ = place;
		number_ = number;
		time_ = time;
	}

	void print(ostream& out) { 
		out << "\t\t" << setw(15) << left << place_ << "\t" << number_ << "\t" << time_ << endl; 
	}  
};

int selectMenu()
{
	int item;
	cout << "\n\t 1\tAdd Train\n";
	cout << "\t 2\tPrint Trains\n";
	cout << "\t 3\tDestroy List\n";
	cout << "\t 4\tSort Trains by number\n";
	cout << "\t 5\tSearch Train\n";
	cout << "\t 6\tExit\n\n";
	do
	{
		cout << "\t\tEnter Choice : ";
		cin >> item;
	}
	while(item < 1 || item > 6);
	return item;
}

bool comp (train t1, train t2) {return (t1<t2);}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<train> trains;
	train t;
	string pl;
	int n = 0;

	bool go = true;
	
	while(go)
	{
		switch(selectMenu())
		{
			case 1:
				t.read(cin);
				trains.push_back(t);
				break;
				
			case 2:
				if(!trains.empty())
				{
					cout << "\n\t\tList of all trains:\n\n";
					cout << "\t\tPlace" << "\t\tNumber" << "\tTime" << "\n";
					cout << "\t\t----------------------------\n";
					for (vector<train>::iterator iter(trains.begin()); iter != trains.end(); ++iter)
					{
						iter->print(cout);
					}
					cout << "\n\n";
				}
				else
					cout << "\n\t\tNot Trains\n";

				break;
			case 3:
				if(!trains.empty()) 
				{
					trains.clear();
					cout << "\n\t\tTrains deleted\n";
				}
				else
					cout << "\n\t\tNot Trains\n";
				break;
			case 4:
				if(!trains.empty()) 
				{
					sort(trains.begin(), trains.end(), comp);
				}
				else
					cout << "\n\t\tNot Trains\n";
				break;
			case 5:
				if(!trains.empty()) 
				{
					cout << "\n\t\tEnter place: ";
					cin >> pl;
					
					for (vector<train>::iterator iter(trains.begin()); iter != trains.end(); ++iter)
						{
							if(iter->get_place() == pl)
							{
								iter->print(cout);
								n++;
							}
						}
					if (!n)
					cout << "\n\t\tNot found" << endl;
					n = 0;
				}
				else
					cout << "\n\t\tNot Trains\n";
				break;
			case 6: 
				go = false;
				break;
			default:
				cout << "\n\t\tInternal Error\n";
		} 
	}
	cout << "\n\t\t*** End of Program ***\n";
	trains.clear();

	return 0;
}