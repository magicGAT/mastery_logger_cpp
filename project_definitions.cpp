#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;

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

// perhap split this into multiple fuctions, one for activities, another for expenditures and a third
// for storing them until the larger recording function is finished
void take_record(string[] act_names , string[] comments , float[] hours, float[] prices, int&, int&)
{
	
}

// fuction called in a loop to write activities, one at a time, to a file
bool Entry::write_act()
{

}
// function called in a loop to write expenditures, one at a time, to a file
bool Entry::write_ex()
{

}
// writes a whole activity to a file by calling the above helper functions
bool Entry::write_to_file()
{

}











