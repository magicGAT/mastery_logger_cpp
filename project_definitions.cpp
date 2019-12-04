#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std; 
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

User create_profile()
{
	User loadee;
	cout << "We are so glad you would like to become a permanent member of the MASTERY FAMILY!" << endl;
	cout << "Let's begin!" << endl;
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

bool find_profile(string prof_name)
{
	ifstream input_file(prof_name)
	if (!)
}

User load_profile(string prof_name)
{
	User loadee;
}

bool save_profile(User to_save)
{

}

User load_guest()
{
	char gate = 'g';
	User loadee;

	loadee = load_profile("guest");
	
	while (gate != 's' && gate != 'm')
	{	
		cout << "Would you prefer to be called 'sir' or 'madame'? (s/m)" << endl;
		cin >> gate
	}

	(gate = 's' ? loadee.sex = true : loadee.sex = false);

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











