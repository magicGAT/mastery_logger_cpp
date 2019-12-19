 */

#include "log_users.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>



using namespace std;

///////--USER MEMBER FUNCTION--///////
void User::browse_entries()
{

	char gate0 = 'g', gate1 = 'g';

	while (gate0 == 'g')
	{
		int counter = 1;
		cout << "Here are all logs associated with your account (labelled by date):" << endl << endl;

		for (string e : entries)
		{
			cout << "Entry " << counter << ": " << e << endl << endl;
			counter++;
		}

		while (gate1 != 'y' && gate1 != 'n')
		{
			cout << "Would you like to examine one of these entries in detail? ('y'/'n')" << endl;
			cin >> gate1;
			cin.ignore();
		}

		if (gate1 == 'y')
		{
			int entry_choice = 0;
			string entry_title;

			while (entry_choice < 1 || entry_choice > entries.size())
			{
				cout << "Ok!" << endl;
				cout << "Please enter the entry number you would like to see: ";
				cin >> entry_choice;
				cin.ignore();
			}

			entry_choice -= 1;
			entry_title = profile_name + entries[entry_choice] + ".txt";
			// cout << entry_title << endl; //testing
			int a_count, e_count;
			string a_char, e_char;
			ifstream input_file(entry_title);

			getline(input_file, a_char, ',');
			getline(input_file, e_char, ',');

			input_file.close();

			a_count = stoi(a_char);
			e_count = stoi(e_char);

			Entry this_entry(a_count, e_count);

			this_entry = open_entry(entry_title, a_count, e_count); // THE PROBLEM IS WITH THIS FUNCTION =(

			this_entry.display_entry();
		}
		else
		{
			return;
		}

		char gate2 = 'g';

		while (gate2 != 'y' && gate2 != 'n')
		{
			cout << "Would you like to view your entries again? ('y'/'n')" << endl;
			cin >> gate2;
			cin.ignore();
		}
		if (gate2 == 'n')
		{
			gate0 = 'n';
		}
		else
			continue;
	}
}

void User::week_report()
{
	cout << "Weekly Report!" << endl;
	cout << "This will select any 7 day period and display the accumulated activities and expenditures" << endl;
	cout << "Please select a starting date from the following list: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as the starting date: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = 7;

	vector <string> act_names;
	vector <float> act_hours;
	vector <string> ex_names;
	vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		Activity* act_plate;
		Expenditure* ex_plate;

		for (int i = 0; i < this_entry.act_count; i++)
		{
			//cout << "activity counter" << endl;
			act_plate = &this_entry.act_arr[i];
			//cout << "search result: " << /*search_vector(act_plate -> a_name, act_names) << */endl;
			int place = search_vector(act_plate -> a_name, act_names);
			//cout << "vector searched" << endl;


			if (place == 99)
			{
				act_names.push_back(act_plate -> a_name);
				act_hours.push_back(act_plate -> time);
			}
			else
			{
				float temp = act_hours[place];
				temp += act_plate -> time;
				act_hours[place] = temp;
			}
		}

		for (int i = 0; i < this_entry.ex_count; i++)
		{
			ex_plate = &this_entry.ex_arr[i];
			int place = search_vector(ex_plate -> e_name, ex_names);

			if (place == 99)
			{
				ex_names.push_back(ex_plate -> e_name);
				ex_prices.push_back(ex_plate -> price);
			}
			else
			{
				float temp = ex_prices[place];
				temp += ex_plate -> price;
				ex_prices[place] = temp;
			}
		}

		entry_choice++;
		day_count--;
	}

	cout << "--.WEEKLY TOTALS REPORT.--" << endl;
	cout << "Activities:" << endl;
	for (int i = 0; i < act_names.size(); i++)
	{
		cout << "\t" << act_names[i] << ": ";
		cout << act_hours[i] << " hours" << endl;
	}
	cout << "Expenditures:" << endl;
	for (int i = 0; i < ex_names.size(); i++)
	{
		cout << "\t" << ex_names[i] << ": ";
		cout << "$" << ex_prices[i] << endl;
	}
}

void User::month_report()
{
	cout << "Weekly Report!" << endl;
	cout << "This will select any 30 day period and display the accumulated activities and expenditures" << endl;
	cout << "Please select a starting date from the following list: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as the starting date: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = 30;

	vector <string> act_names;
	vector <float> act_hours;
	vector <string> ex_names;
	vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		Activity* act_plate;
		Expenditure* ex_plate;

		for (int i = 0; i < this_entry.act_count; i++)
		{
			cout << "activity counter" << endl;
			act_plate = &this_entry.act_arr[i];
			//cout << "search result: " << /*search_vector(act_plate -> a_name, act_names) << */endl;
			int place = search_vector(act_plate -> a_name, act_names);
			//cout << "vector searched" << endl;


			if (place == 99)
			{
				act_names.push_back(act_plate -> a_name);
				act_hours.push_back(act_plate -> time);
			}
			else
			{
				float temp = act_hours[place];
				temp += act_plate -> time;
				act_hours[place] = temp;
			}
		}

		for (int i = 0; i < this_entry.ex_count; i++)
		{
			ex_plate = &this_entry.ex_arr[i];
			int place = search_vector(ex_plate -> e_name, ex_names);

			if (place == 99)
			{
				ex_names.push_back(ex_plate -> e_name);
				ex_prices.push_back(ex_plate -> price);
			}
			else
			{
				float temp = ex_prices[place];
				temp += ex_plate -> price;
				ex_prices[place] = temp;
			}
		}

		entry_choice++;
		day_count--;
	}

	cout << "--.MONTHLY TOTALS REPORT.--" << endl;
	cout << "Activities:" << endl;
	for (int i = 0; i < act_names.size(); i++)
	{
		cout << "\t" << act_names[i] << ": ";
		cout << act_hours[i] << " hours" << endl;
	}
	cout << "Expenditures:" << endl;
	for (int i = 0; i < ex_names.size(); i++)
	{
		cout << "\t" << ex_names[i] << ": ";
		cout << "$" << ex_prices[i] << endl;
	}
	cout << endl;
}
void User::day_mproj(string query_term)
{
	cout << "This will give you an estimated time frame to achieve mastery in " << query_term << " based on a single day's performance" << endl;
	cout << "Here are you availiable data points: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as your sample: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = 1;

	vector <string> act_names;
	vector <float> act_hours;
	//vector <string> ex_names;
	//vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		Activity* act_plate;

		for (int i = 0; i < this_entry.act_count; i++)
		{
			act_plate = &this_entry.act_arr[i];
			//cout << "search result: " << /*search_vector(act_plate -> a_name, act_names) << */endl;
			int place = search_vector(act_plate -> a_name, act_names);
			//cout << "vector searched" << endl;


			if (place == 99)
			{
				act_names.push_back(act_plate -> a_name);
				act_hours.push_back(act_plate -> time);
			}
			else
			{
				float temp = act_hours[place];
				temp += act_plate -> time;
				act_hours[place] = temp;
			}
		}

		//entry_choice++;
		day_count--;
	}

	int place = search_vector(query_term, act_names);

	float total = act_hours[place];

	if (total == 0)
	{
		cout << "Please check your sample, no activity hours detected" << endl << endl;
	}
	else
	{
		cout << "Based on this sample, you will reach mastery of " << query_term << " in " << (10000 / total) << " days";
		cout << endl << endl;
	}
}
void User::week_mproj(string query_term)
{
	cout << "This will give you an estimated time frame to achieve mastery in " << query_term << " based on a your performance totals during any 7 day period" << endl;
	cout << "Here are you availiable entries: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as your starting point: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = 7;

	vector <string> act_names;
	vector <float> act_hours;
	//vector <string> ex_names;
	//vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		Activity* act_plate;

		for (int i = 0; i < this_entry.act_count; i++)
		{
			act_plate = &this_entry.act_arr[i];
			//cout << "search result: " << /*search_vector(act_plate -> a_name, act_names) << */endl;
			int place = search_vector(act_plate -> a_name, act_names);
			//cout << "vector searched" << endl;


			if (place == 99)
			{
				act_names.push_back(act_plate -> a_name);
				act_hours.push_back(act_plate -> time);
			}
			else
			{
				float temp = act_hours[place];
				temp += act_plate -> time;
				act_hours[place] = temp;
			}
		}

		//entry_choice++;
		day_count--;
	}

	int place = search_vector(query_term, act_names);

	float total = act_hours[place];

	if (total == 0)
	{
		cout << "Please check your sample, no activity hours detected" << endl << endl;
	}
	else
	{
		cout << "Based on this sample, you will reach mastery of " << query_term << " in " << (10000 / total) << " weeks";
		cout << endl << endl;
	}
}
void User::month_mproj(string query_term)
{
	cout << "This will give you an estimated time frame to achieve mastery in " << query_term << " based on a your performance totals during any 30 day period" << endl;
	cout << "Here are you availiable entries: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as your starting point: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = 30;

	vector <string> act_names;
	vector <float> act_hours;
	//vector <string> ex_names;
	//vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		Activity* act_plate;

		for (int i = 0; i < this_entry.act_count; i++)
		{
			act_plate = &this_entry.act_arr[i];
			//cout << "search result: " << /*search_vector(act_plate -> a_name, act_names) << */endl;
			int place = search_vector(act_plate -> a_name, act_names);
			//cout << "vector searched" << endl;


			if (place == 99)
			{
				act_names.push_back(act_plate -> a_name);
				act_hours.push_back(act_plate -> time);
			}
			else
			{
				float temp = act_hours[place];
				temp += act_plate -> time;
				act_hours[place] = temp;
			}
		}

		//entry_choice++;
		day_count--;
	}

	int place = search_vector(query_term, act_names);

	float total = act_hours[place];

	if (total == 0)
	{
		cout << "Please check your sample, no activity hours detected" << endl << endl;
	}
	else
	{
		cout << "Based on this sample, you will reach mastery of " << query_term << " in " << (10000 / total) << " months";
		cout << endl << endl;
	}
}
void User::ex_dweek()
{
	string query, frame = "week";
	float total;


	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 1);

	cout << "Projected expense over the next " << frame << " : $" << (total * 7) << endl << endl;
}
void User::ex_dmonth()
{
	string query , frame = "month";
	float total;

	cout << "For What expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 1);

	cout << "Projected expense over the next " << frame << " : $" << (total * 30) << endl << endl;
}
void User::ex_dyear()
{
	string query, frame = "year";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 1);

	cout << "Projected expense over the next " << frame << " : $" << (total * 365) << endl << endl;
}
void User::ex_wmonth()
{
	string query, frame = "month";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 7);

	cout << "Projected expense over the next " << frame << " : $" << (total * 4) << endl << endl;
}
void User::ex_wquart()
{
	string query, frame = "quarter";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 7);

	cout << "Projected expense over the next " << frame << " : $" << (total * 12) << endl << endl;
}
void User::ex_wyear()
{
	string query, frame = "year";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 7);

	cout << "Projected expense over the next " << frame << " : $" << (total * 48) << endl << endl;
}
void User::ex_mquart()
{
	string query, frame = "quarter";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 30);

	cout << "Projected expense over the next " << frame << " : $" << (total * 3) << endl << endl;
}
void User::ex_myear()
{
	string query, frame = "year";
	float total;

	cout << "For what expenditure would you like to calculate a projection?" << endl;
	getline(cin, query);

	total = total_cost(query, frame, 30);

	cout << "Projected expense over the next " << frame << " : $" << (total * 12) << endl << endl;
}

float User::total_cost(string query_term, string period, int days)
{
	cout << "Cost Projection!" << endl;
	cout << "This will give you the projected cost of any particular expenditure over the next " << period << " according to the corresponding expenditure during any particular " << sample_frame(days) << endl;
	cout << "Here are you availiable entries: " << endl;

	int counter = 1;

	for (string e : entries)
	{
		cout << "Entry " << counter << ": " << e << endl << endl;
		counter++;
	}

	int entry_choice = 0;
	string entry_title;

	while (entry_choice < 1 || entry_choice > entries.size())
	{
		//cout << "Ok!" << endl;
		cout << "Please enter the entry number you would like to set as the starting date for your data sample: ";
		cin >> entry_choice;
		cin.ignore();
	}

	entry_choice -= 1;

	int day_count = days;

	//vector <string> act_names;
	//vector <float> act_hours;
	vector <string> ex_names;
	vector <float> ex_prices;

	while (day_count > 0)
	{
		entry_title = profile_name + entries[entry_choice] + ".txt";
		//cout << "file name: " << entry_title;
		// cout << entry_title << endl; //testing
		int a_count, e_count;
		string a_char, e_char;
		ifstream input_file(entry_title);

		getline(input_file, a_char, ',');
		getline(input_file, e_char, ',');

		input_file.close();

		a_count = stoi(a_char);
		e_count = stoi(e_char);

		Entry this_entry(a_count, e_count);

		this_entry = open_entry(entry_title, a_count, e_count);

		//Activity* act_plate;
		Expenditure* ex_plate;

		for (int i = 0; i < this_entry.ex_count; i++)
		{
			ex_plate = &this_entry.ex_arr[i];
			int place = search_vector(ex_plate -> e_name, ex_names);

			if (place == 99)
			{
				ex_names.push_back(ex_plate -> e_name);
				ex_prices.push_back(ex_plate -> price);
			}
			else
			{
				float temp = ex_prices[place];
				temp += ex_plate -> price;
				ex_prices[place] = temp;
			}
		}

		entry_choice++;
		day_count--;
	}

	int place = search_vector(query_term, ex_names);
	return ex_prices[place];
}

void analysis_menu(User& subject)
{
	bool on = true;
	int selector;

	while (on == true)
	{
		cout << endl << "--.Projection/Analysis Menu.--" << endl;
		cout << "1)Weekly Report" << endl;
		cout << "2)Monthly Report" << endl;
		cout << "3)Mastery Projection by Day" << endl;
		cout << "4)Mastery Projection by Week" << endl;
		cout << "5)Mastery Projection by Month" << endl;
		cout << "(((Expenditure Projections)))" << endl;
				cout << "\t6)Day -> Week" << endl;
		cout << "\t7)Day -> Month" << endl;
		cout << "\t8)Day -> Year" << endl;
		cout << "\t9)Week -> Month" << endl;
		cout << "\t10)Week -> Quarter" << endl;
		cout << "\t11)Week -> Year" << endl;
		cout << "\t12)Month -> Quarter" << endl;
		cout << "\t13)Month -> Year" << endl;
		cout << "14)Exit" << endl << endl;

		cout << "Please enter a selection: ";
		cin >> selector;
		cin.ignore();
		cout << endl << endl;

		string query;

		switch (selector)
		{
		case 1:
			subject.week_report();
			continue;
		case 2:
			subject.month_report();
			continue;
		case 3:
			cout << "Mastery Query!" << endl;
			cout << "What activity would you like to examine?" << endl;
			getline(cin, query);
			subject.day_mproj(query);
			continue;
		case 4:
			cout << "Mastery Query!" << endl;
			cout << "What activity would you like to examine?" << endl;
			getline(cin, query);
			subject.week_mproj(query);
			continue;
		case 5:
			cout << "Mastery Query!" << endl;
			cout << "What activity would you like to examine?" << endl;
			getline(cin, query);
			subject.month_mproj(query);
			continue;
		case 6:
			subject.ex_dweek();
			continue;
		case 7:
			subject.ex_dmonth();
			continue;
		case 8:
			subject.ex_dyear();
			continue;
		case 9:
			subject.ex_wmonth();
			continue;
		case 10:
			subject.ex_wquart();
			continue;
		case 11:
			subject.ex_wyear();
			continue;
		case 12:
			subject.ex_mquart();
			continue;
		case 13:
			subject.ex_myear();
			continue;
		case 14:
			cout << "Returning to main menu..." << endl << endl;
			on = false;
			continue;
		}
	}
}
///////--ENTRY MEMBER FUNCTIONS--///////
// constructor
Entry::Entry(int a_count, int e_count)
{
	// initialization of basic members
	date = day_o_year();
	act_count = a_count;
	ex_count = e_count;

	// allocation of array space
	if (a_count > 0)
	{
		act_arr = new Activity[act_count];
	}
	else
		act_arr = nullptr;

	if (e_count > 0)
	{
		ex_arr = new Expenditure[ex_count];
	}
	else
		ex_arr = nullptr;
}
// destructor
Entry::~Entry()
{
	// prevents memory leaks when object falls out of scope and is destroyed
	delete [] act_arr;
	delete [] ex_arr;
}
// copy constructor
Entry::Entry(const Entry &copy)
{
	cout << "Copy Constructor Called" << endl; // testing
	act_count = copy.act_count;
	ex_count = copy.ex_count;
	date = copy.date;
	if (act_count > 0)
	{
		act_arr = new Activity[act_count];
		Activity* act_plate;
		for (int i = 0; i < act_count; i++ )
		{
			act_plate = &copy.act_arr[i];
			act_arr[i].a_name = act_plate -> a_name;
			act_arr[i].time = act_plate -> time;
		}
	}
	else
		act_arr = nullptr;

	if (ex_count > 0)
	{
		ex_arr = new Expenditure[ex_count];
		Expenditure* ex_plate;
		for (int i = 0; i < ex_count; i++)
		{
			ex_plate = &copy.ex_arr[i];
			ex_arr[i].e_name = ex_plate -> e_name;
			ex_arr[i].price = ex_plate -> price;
		}
	}
	else
		ex_arr = nullptr;

}
// copy assignment operator
Entry& Entry::operator = (const Entry &to_copy)
{
	delete[] act_arr;
	if (to_copy.act_count > 0)
	{
		act_arr = new Activity[to_copy.act_count];
		for (int i = 0; i < to_copy.act_count; i++)
		{
			act_arr[i].a_name = to_copy.act_arr[i].a_name;
			act_arr[i].time = to_copy.act_arr[i].time;
		}
	}
	else
		act_arr = nullptr;

	delete[] ex_arr;
	if (to_copy.ex_count > 0)
	{
		ex_arr = new Expenditure[to_copy.ex_count];
		for (int i = 0; i < to_copy.ex_count; i++)
		{
			ex_arr[i].e_name = to_copy.ex_arr[i].e_name;
			ex_arr[i].price = to_copy.ex_arr[i].price;
		}
	}
	else
		ex_arr = nullptr;

	act_count = to_copy.act_count;
	ex_count = to_copy.ex_count;
	date = to_copy.date;

	return *this;
}

void Entry::write_act(vector<string> &names, int position)
{
	float hours;
	Activity * scope;

	cout << names[position] << endl;
	cout << "How many hours did you spend on this activity: ";
	cin >> hours;

	scope = &act_arr[position];
	scope -> a_name = names[position];
	scope -> time = hours;
}

void Entry::write_ex(vector<string> &names, int position)
{
	float e_cost;
	Expenditure * scope;

	cout << names[position] << endl;
	cout << "How much did you spend on this: " << endl;
	cin >> e_cost;

	scope = &ex_arr[position];
	scope -> e_name = names[position];
	scope -> price = e_cost;
}

bool Entry::write_to_file(User& user)
{
	Activity * act_plate;
	Expenditure * ex_plate;
	string file_name = user.profile_name + date + ".txt";

	ofstream output_file(file_name);

	if (output_file.fail())
		cerr << "Its not opening";

	// add protections here for improper file operations

	output_file << act_count << ",";
	output_file << ex_count << ",";
	output_file << date << ",";

	for (int i = 0; i < act_count; i++)
	{
		act_plate = &act_arr[i];

		output_file << act_plate -> a_name << ",";
		output_file << act_plate -> time << ",";
	}



	for (int i = 0; i < ex_count; i++)
	{
		ex_plate = &ex_arr[i];

		output_file << ex_plate -> e_name << ",";
		output_file << ex_plate -> price << ",";
	}

	output_file.close();

	return true;
}

bool Entry::update_userf(User sub)
{
	string file_name = sub.profile_name + ".txt";
	fstream to_update;
	string addition = date;

	to_update.open(file_name, ios::app);

	to_update << endl << addition;
	to_update.close();

	return true;
}
///////----///////
/*
bool User::update_userf(Entry update_subject)
{
	string file_name = profile_name + ".txt";
	fstream to_update;
	string addition = update_subject.date;

	to_update.open(file_name, ios::app);

	to_update << endl << addition;
	to_update.close();

	return true;
}
*/

void Entry::display_entry()
{
	cout << "!!!--.ENTRY DETAILS.--!!!" << endl;
	cout << "date: " << date << endl;
	cout << "ACTIVITIES:" << endl;

	if (act_count == 0)
	{
		cout << "\t NONE" << endl;
	}
	else
	{
		Activity * act_plate;
		// int counter0 = act_count - 1;

		for (int i = 0; i < act_count; i++)
		{
			act_plate = &act_arr[i];
			cout << "\tActivity: " << act_plate -> a_name << endl;
			cout << "\tHours: " << act_plate -> time << endl;
		}
	}


	if (ex_count == 0)
	{
		return;
	}
	else
	{
		cout << "EXPENDITURES:" << endl;
		Expenditure * ex_plate;
		// int counter1 = ex_count -1;

		for (int i = 0; i < ex_count; i++)
		{
			ex_plate = &ex_arr[i];
			cout << "\tExpenditure: " << ex_plate -> e_name << endl;
			cout << "\tCost: $" << ex_plate -> price << endl;
		}
	}
	cout << endl << endl;
}

///////--GENERAL FUNCTIONS--///////
string day_o_year()
{
	int month, day, year;
	string result;

	time_t t = time(0);
	tm* now = localtime(&t);

	month = now -> tm_mon + 1;
	day = now -> tm_mday;
	year = 1900 + now -> tm_year;

	result = to_string(month) + "-" + to_string(day) + "-" + to_string(year);

	return result;
}

int time_o_day()
{
	time_t my_time = time(0);

	tm* now = localtime(&my_time);

	return now -> tm_hour;
}

string generate_dphase(int hour)
{

}

string sample_frame(int days)
{
	if (days == 1)
	{
		return "day";
	}
	else if (days == 7)
	{
		return "week";
	}
	else if (days == 30)
	{
		return "month";
	}
	else
	{
		return "unknown time period";
	}
}

int search_vector(string objective, vector <string> subject)
{
	for (int i = 0; i < subject.size(); i++)
	{
		if (subject[i] == objective)
		{
			return i;
		}
	}
	return 99;
}

void about()
{
	cout << "Welcome to the Mastery Log. This program can be used to do daily logging of activities" << endl;
	cout << "and expenditures in service to one's goal setting and self-management. When entering the" << endl;
	cout << "program you will be asked if you have a profile. If you do, you may enter your username." << endl;
	cout << "If you do not, you will be asked if you would like to create one. The program will guide" << endl;
	cout << "you through that process. If you decline, you will be assigned the 'guest' account." << endl << endl;
	cout << "From the main menu you can log new entries, read previous entries, or apply analytical tools" << endl;
	cout << "to your growing collection of entries. You can receive weekly or monthly summaries. You can" << endl;
	cout << "calculate, based on various sampling sizes, how long before you will reach 10,000 hours of" << endl;
	cout << "practice in any activity within your logs. THis prediction is  based on your progress during the specified time" << endl;
	cout << " period. The 10,000 hour benchmark is regarded by researchers as a universal requirement to reaching the" << endl;
	cout << "mythical, elusive, and exalted state of 'Mastery'.This applies to any skill and any learner." << endl;
	cout << "It is from this concept the program derives it's name." << endl << endl;
	cout << "Finally, you can project your future spending in any category you have logged as an expenditure in your" << endl;
	cout << "entries. You select a category, a sample size, and a time frame which you want to project into." << endl;
	cout << "The program then performs the calculation and presents the results, hopefully assisting in budgeting" << endl;
	cout << "and financial planning." << endl << endl;
	cout << "It is all, mostly, self explanatory so dont be afraid to make a profile and check it all out for yourself!" << endl;
	cout << "We hope you enjoy it and make good use of it. Remember, the key to any system is consistency. So get logging!" << endl << endl;
}

///////--LOG WRITING && READING FUNCTIONS--///////
void generate_entry(User& subject)
{
	vector<string> activity;
	vector<string> expenditures;

	bool gate_0 = false;
	char choice_0 = 'g', choice_1 = 'y' , choice_2 = 'g', choice_3 = 'y', choice_4 = 'y', choice_5 = 'g',
		 choice_6 = 'y', choice_7 = 'g';

	cout << "Now we will write an entry for today's activities and expenditures" << endl;

	while (choice_0 != 'a' && choice_0 != 'e')
	{
		cout << "Which would you like to do first? ('a'/'e')" << endl;
		cin >> choice_0;
		cin.ignore();
	}

	(choice_0 == 'a' ? gate_0 = true : gate_0 = false);

	if (gate_0 == true)
	{
		int counter_0 = 1;
		string name_box0;

		cout << "Ok lets, list some activities" << endl;

		while (choice_1 != 'n')
		{
			 cout << "Please name one of your activities today (" << counter_0 << "): ";

			 getline(cin, name_box0);
			 activity.push_back(name_box0);
			 counter_0++;

			 cout << endl << endl << "Do you have more activites to report? ('n' to quit)" << endl;
			 cin >> choice_1;
			 cin.ignore();
		}

		while (choice_2 != 'y' && choice_2 != 'n')
		{
			cout << "Now that we have a list of activities, would you like to record some expenditures? ('y'/'n')" << endl;
			cin >> choice_2;
			cin.ignore();
		}

		if (choice_2 == 'y')
		{
			int counter_1 = 1;
			string name_box1;

			while (choice_3 != 'n')
			{
				cout << "Please name an expenditure (" << counter_1 << "): ";

				getline(cin, name_box1);
				expenditures.push_back(name_box1);
				counter_1++;


				cout << endl << endl << "Do you have more expenditures to record? ('n' to quit)" << endl;
				cin >> choice_3;
				cin.ignore();
			}
		 }
	}
	else
	{
		cout << "Ok, lets list some expenditures" << endl;

		int counter_2 = 1;
		string name_box2;

		while (choice_4 != 'n')
		{
			cout << "Please name an expenditure (" << counter_2 << "): ";
			getline(cin, name_box2);
			counter_2++;

			cout << endl << endl << "Do you have more expenditures to record? ('n' to quit)" << endl;
			cin >> choice_4;
			cin.ignore();
		}

		while (choice_5 != 'y' && choice_5 != 'n')
		{
			cout << "Now that we have a list of expenditures, would you like to record some activities? ('y'/'n')" << endl;
			cin >> choice_5;
			cin.ignore();
		}

		if (choice_5 == 'y')
		{
			int counter_3 = 1;
			string name_box3;

			while (choice_6 != 'n')
			{
				cout << "Please name one of your activities today (" << counter_3 << "): ";

				getline(cin, name_box3);
				activity.push_back(name_box3);
				counter_3++;

				cout << endl << endl << "Do you have more activities to report? ('n' to quit)" << endl;
				cin >> choice_6;
				cin.ignore();
			}
		}
	}

	cout << "Ok! You have recorded " << activity.size() << " activities and ";
	cout << expenditures.size() << " expenditures!" << endl;
	// insert option to start over here (same with the profile creation) (easier when things are more modular, simply quit and re-call the function)
	// consider saving activity.size() to a variable to avoid the 6 function calls we make here
	// Entry object is instantiated with the adt arrays are filled.

	Entry this_entry(activity.size(), expenditures.size());

	// write activities loop
	for (int i = 0; i < activity.size(); i++)
	{
		this_entry.write_act(activity, i);
	}

	// write expenditures loop
	for (int i = 0; i < expenditures.size(); i++)
	{
		this_entry.write_ex(expenditures, i);
	}

	cout << "Entry Generated and Filled!" << endl;

	// cout a display/summary of the entry, the same one used to read old entries

	while (choice_7 != 'y' && choice_7 != 'n')
	{
		cout << "Would you like to save this entry? ('y'/'n')" << endl;
		cin >> choice_7;
	}

	if (choice_7 == 'y')
	{
		bool success0, success1;

		success0 = this_entry.write_to_file(subject);

		(success0 == true ? cout << "Successfully Logged!" << endl : cout << "Error. Log Unsuccessful..." << endl);

		success1 = this_entry.update_userf(subject);

		(success1 == true ? cout << "Entry Connected to User!" : cout << "Entry Not Connected to User!");

		subject = load_profile(subject.profile_name);
	}

}

Entry open_entry(string entry_title, int act, int exp)
{
	Entry bucket(act, exp); // problem starts here // IS THE PROBLEM THAT THIS IS A USER FUNCTION???
	//cout << "Did it crash?" << endl;
	string a, e, temp;
	int a_count, e_count;
	Activity * act_plate;
	Expenditure * exp_plate;

	ifstream input_file(entry_title);

	getline(input_file, a,',');
	getline(input_file, e,',');

	a_count = stoi(a);
	e_count = stoi(e);

	a_count -= 1;
	e_count -= 1;

	getline(input_file, bucket.date,',');

	while (a_count >= 0)
	{
		act_plate = &bucket.act_arr[a_count];
		getline(input_file, act_plate -> a_name,',');
		getline(input_file, temp, ',');
		act_plate -> time = stof(temp);
		// cout << act_plate -> a_name << endl; // testing HERE ITS IN

		a_count--;
	}

	while (e_count >= 0)
	{
		exp_plate = &bucket.ex_arr[e_count];
		getline(input_file, exp_plate -> e_name,',');
		getline(input_file, temp, ',');
		exp_plate -> price = stof(temp);

		e_count--;
	}

	return bucket;
}

///////--PROFILE FUNCTIONS--///////
bool find_profile(string profile_name)
{
	string file_name = profile_name + ".txt";

	ifstream input_file(file_name);

	if (!input_file)
	{
		input_file.close();
		return false;
	}
	else
	{
		input_file.close();
		return true;
	}
}

User create_profile()
{
	User loadee;

	string user_name, u_fname, nick_name, fav_act, try_response;
	char elect = 'g', sex;
	bool gate0 = true, gate1 = true;
	int sex_num = 3;

	cout << "We are so glad you would like to become a permanent member of the MASTERY FAMILY!" << endl;
	cout << "Let's begin!" << endl << endl;

	while (gate0)
	{
		cout << "What would you like your username to be:" << endl;
	    getline(cin, user_name);

	    gate0 = find_profile(user_name);

	    (!gate0 ? try_response = "Username availiable!" : try_response = "Username already taken!");

	    cout << endl << try_response << endl << endl;
	}

	cout << "Now that your username has been determined, what would you actually like to be called?" << endl;
	getline(cin, nick_name);
	// cin.ignore();

	do
	{
		cout << endl << "Would you like to select a favorite activity? (y/n)" << endl;
		cin >> elect;
	} while (elect != 'y' && elect != 'n');

	if (elect == 'y')
	{
		cout << "Enter your favorite activity:" << endl;
		getline(cin, fav_act);
		cin.ignore();
	}

	if (elect == 'n')
	{
		cout << "No problem! One can be assigned later" << endl << endl;
		fav_act = "none";
	}

	while (sex_num != 1 && sex_num != 2)
	{
		cout << "Finally, please select one biological sex by which you will be identified: (1 = male, 2 = female)" << endl;
		cin >> sex_num;
	}

	(sex_num == 1 ? sex = 1 : sex = 0);

	cout << "OK! Lets summarize:" << endl;

	display_profile(user_name, nick_name, fav_act, sex);

	while (gate1)
	{
		cout << endl << "Save this profile? (y/n)" << endl;
		cin >> elect;

		if (elect == 'y')
		{
			gate1 = false;
		}
		else
		{
			break;
		}

	}

	loadee.profile_name = user_name;
	loadee.preferred_name = nick_name;
	loadee.fav_act = fav_act;
	loadee.sex = sex;

	bool save_state = save_new_profile(loadee);
	(
		save_state == true ?
		cout << "Profile created and saved successfully" << endl
		:
		cout << "Profile was not saved correctly" << endl
	);

	return loadee;
}

bool save_new_profile(User to_save)
{
	string file_name = to_save.profile_name + ".txt";

	ofstream output_file(file_name);

	if (!output_file)
	{
		return false;
	}
	else
	{
		output_file << to_save.profile_name << endl;
		output_file << to_save.preferred_name << endl;
		output_file << to_save.fav_act << endl;
		output_file << to_save.sex << endl;

		output_file.close();

		return true;
	}

}

User load_profile(string profile_name)
{
	User loadee;
	string temp, file_name = profile_name + ".txt";

	ifstream input_file(file_name);

	input_file >> loadee.profile_name;
	input_file.ignore();
	getline(input_file, loadee.preferred_name);
	input_file >> loadee.fav_act;
	input_file >> loadee.sex;

	while (!input_file.eof())
	{
		input_file >> temp;

		loadee.entries.push_back(temp);
	}

	input_file.close();

	return loadee;
}

User load_guest()
{
	char gate = 'g';
	User loadee;

	loadee = load_profile("guest");

	while (gate != 's' && gate != 'm')
	{
		cout << "Would you prefer to be called 'sir' or 'madame'? (s/m)" << endl;
		cin >> gate;
	}

	(gate = 's' ? loadee.sex = true : loadee.sex = false);

	return loadee;
}

void display_profile(User subject)
{
	cout << "--.PROFILE REPORT.--" << endl;
	cout << "--------------------" << endl;
	cout << "Username: " << subject.profile_name << endl;
	cout << "Preferred Name: " << subject.preferred_name << endl;
	cout << "Favorite Activity: " << subject.fav_act << endl;
	cout << "Biological Sex: ";
	(subject.sex == 1 ? cout << "Male" : cout << "Female");
	cout << endl;
	cout << "Number of Associated Log Entries: " << subject.entries.size() << endl << endl;
}

void display_profile(string u_name, string p_name, string fav, bool s)
{
	cout << "--.PROFILE REPORT.--" << endl;
	cout << "--------------------" << endl;
	cout << "Username: " << u_name << endl;
	cout << "Preferred Name: " << p_name << endl;
	cout << "Favorite Activity: " << fav << endl;
	cout << "Biological Sex: ";
	(s == 1 ? cout << "Male" : cout << "Female") << endl;
	cout << endl;
}

User greeter()
{
	User subject;
	bool gate;
	char flag = 'g';

	// determination of membership status
	while (flag != 'n' && flag != 'y')
	{
		cout << "Do you have a profile? (y/n)" << endl;
		cin >> flag;
	}

	(flag == 'y' ? gate = true : gate = false);

	// if user indicated they are a user, they are prompted to load their profile
	if (gate == true)
	{
		bool gate_2 = false;

		while (gate_2 == false)
		{
			string u_name, u_file;

			cout << "Please enter your username:" << endl;
			cin >> u_name;
			u_file = u_name + ".txt";
			cin.ignore();

			if (find_profile(u_name))
			{
				cout << "Profile Found!" << endl;
				subject = load_profile(u_name);
				gate_2 = true;
			}
			else
			{
				char flag;
				cout << "Profile not found..." << endl;
				cout << "Would you like to try again? (y/n)" << endl;
				cin >> flag;

				(flag == 'y' ? gate_2 = false : gate_2 = true);
			}
		}
	}

		// if user indicates they are not a member, they are prompted to
		// either create a profile or continue as a guest
	if (gate == false)
	{
		char flag_2 = 'g';

		while (flag_2 != 'y' && flag_2 != 'n')
		{
			cout << "Would you like to create a MASTERY LOG profile? (y/n)" << endl;
			cin >> flag_2;
			cin.ignore();
		}

		if (flag_2 == 'y')
		{
			cout << "Initiating profile creator..." << endl;
			subject = create_profile();
		}

		if (flag_2 == 'n')
		{
			cout << "Generating profile: 'guest'..." << endl;
			subject = load_guest();
		}
	}

	string final_name;

	final_name = subject.preferred_name;

	// determination of time of day
	int hora;
	string d_phase;

	hora = time_o_day();

	if ( hora > 3 && hora < 12 )
		d_phase = "Morning";

	else if ( hora >= 12 && hora < 18 )
		d_phase = "Afternoon";

	else if ( (hora >= 18 && hora <= 24) || (hora >= 0 && hora <= 3) )
		d_phase = "Evening";

	else
		d_phase = "Day";

	// final greeting and termination
	cout << "Good " << d_phase << ", " << final_name << "!" << endl;
	return subject;
}















