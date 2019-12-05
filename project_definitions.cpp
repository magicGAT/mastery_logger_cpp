#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;

string day_o_year()
{
	int month, day, year;
	string result;

	time_t t = time(0);
	tm* now = localtime(&t);

	month = now -> tm_mon + 1;
	day = now -> tm_mday;
	year = 1900 + now -> tm_year;

	result = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

	return result;
}

///////--ENTRY MEMBER FUNCTIONS--///////
// Constructor
Entry::Entry(int a_count, int e_count)
{
	// initialization of basic members
	date = day_o_year();
	act_count = a_count;
	ex_count = e_count;

	// allocation of array space
	act_arr = new Activity[act_count];
	ex_arr = new Expenditure[ex_count];
}

Entry::~Entry()
{
	// prevents memory leaks when object falls out of scope and is destroyed
	delete act_arr;
	delete ex_arr;
}
// fuction called in a loop to write activities, one at a time, to the object's corresponding array
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
// function called in a loop to write expenditures, one at a time, to the object's corresponding array
// function called in a loop to write expenditures, one at a time, to the object's corresponding array
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
// writes an entire entry to a file
bool Entry::write_to_file()
{
	Activity * act_plate;
	Expenditure * ex_plate;
	string file_name = date + ".txt";

	ofstream output_file(file_name);

	// add protections here for improper file operations

	output_file << date << ",";
	output_file << act_count << ",";

	for (int i = 0; i < act_count; i++)
	{
		act_plate = &act_arr[i];

		output_file << act_plate -> a_name << ",";
		output_file << act_plate -> time << ",";
	}

	output_file << ex_count << ",";

	for (int i = 0; i < ex_count; i++)
	{
		ex_plate = &ex_arr[i];

		output_file << ex_plate -> e_name << ",";
		output_file << ex_plate -> price << ",";
	}

	output_file.close();

	return true;
}
///////----///////

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

				cout << endl << endl << "Do you have more activites to report? ('n' to quit)" << endl;
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

		success0 = this_entry.write_to_file();

		(success0 == true ? cout << "Successfully Logged!" : cout << "Error. Log Unsuccessful...");

		success1 = subject.update_userf(this_entry);

		(success1 == true ? cout << "Entry Connected to User!" : cout << "Entry Not Connected to User!");
	}
}

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

int time_o_day()
{
	time_t my_time = time(0);

	tm* now = localtime(&my_time);

	return now -> tm_hour;
}

string generate_dphase(int hour)
{

}

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
	cout << "Number of Associated Log Entries: " << subject.entries.size() << endl;
}

void display_profile(string u_name, string p_name, string fav, bool s)
{
	cout << "--.PROFILE REPORT.--" << endl;
	cout << "--------------------" << endl;
	cout << "Username: " << u_name << endl;
	cout << "Preferred Name: " << p_name << endl;
	cout << "Favorite Activity: " << fav << endl;
	cout << "Biological Sex: ";
	(s == 1 ? cout << "Male" : cout << "Female");
	cout << endl;
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
			continue;
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

User greeter()
{
	User subject;
	bool gate;
	char flag = 'g';

	// determination of membership status
	while(flag != 'n' || !flag != 'y')
	{
		cout << "Are you already a member? (y/n)" << endl;
		cin >> flag;
	} 

	(flag == 'y' ? gate = true : gate = false);

	// if user indicated they are a user, they are prompted to load their profile
	if (gate = true)
	{
		bool gate_2 = false;
		while (gate_2 = false)
		{
			string u_name, u_file;
		
			cout << "Please enter your username:" << endl;
			cin >> u_name;
			u_file = u_name + ".txt";

			if (find_profile(u_name))
				cout << "Profile Found!" << endl;
				subject = load_profile(u_name);
				gate_2 = true;

			else 
			{
				char flag;
				cout << "Profile not found..." << endl;
				cout << "Would you like to try again? (y/n)" << endl;
				cin >> flag;

				(flag == y ? continue : gate_2 = true)
			} 
		}

		// if user indicates they are not a member, they are prompted to
		// either create a profile or continue as a guest
		if (gate = false)
		{
			char flag_2 = 'g';

			while (flag_2 != 'y' && flag_2 != 'n')
			{
				cout << "Would you like to create a MASTERY FAMILY profile? (y/n)" << endl;
				cin >> flag_2;
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
	}

	string final_name;

	final_name = subject.preferred_name

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













