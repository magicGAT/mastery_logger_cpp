/*
FINAL PROJECT MAPPING AND MAIN FUNCTION
*/

// INCLUDE STATEMENTS
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

// main function
int main()
{
	// greeting/load a profile (perhaps include a couple of sample profile for demo purposes)
	User my_user = greeter(); 

	cout << endl << endl << display_profile(my_user) << endl;

	// INSERT PHILOSOPHICAL/JOKE MESSAGE HERE

	// MAIN MENU
	char selector;
	bool on = true;

	while (on == true)
	{
		char selector = 'g';

		cout << "main menu" << endl;
		cout << "----------" << endl;
		cout << "j) JOURNAL an entry" << endl;
		cout << "r) select one of your entries to READ" << endl;
		cout << "p) make PROJECTIONS based on your entries" << endl;
		cout << "a) learn ABOUT mastery family" << endl;
		cout << "x) EXIT" << endl;
	
		cin >> selector

		switch (selector)
		{
			// option 1: JOURNAL AN ENTRY 
			// how can we enfore that a users new activity/expenditure objects will match exisiting ones
			// to prevent massive failure from simple typos (a function that compares strings and asks the
			// user if they are the same in the event of minor char differences?)
		case 'j':
				generate_entry(my_user);
				continue;
			// option 2: READ AN ENTRY
		case 'r':
				my_user.browse_entries();
				continue;
			// option 3: MAKE PROJECTIONS (interesting design decision... should there be any automation
			// to the process based on profile? Should my profile keep a standing count of how many hours
			// I have in my favored activity, or should it all be file based when I access this part of the
			// program? Probably depends largely on the speed of file I/O and processing)
		case 'p':
				continue;
			// option 4: about/help
		case 'a':
				continue;
		case 'x':
			cout << "Until next time..." << endl;
			(my_user.sex == 1 ? cout << "Sir " : cout << "Madame ");
			cout << my_user.preferred_name << endl;

			on = false;
			break;
		}
	}

	return 0; 
}



