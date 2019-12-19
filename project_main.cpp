/*
FINAL PROJECT MAPPING AND MAIN FUNCTION
*/

// INCLUDE STATEMENTS
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "log_users.h"


using namespace std;

// main function
int main()
{
	// greeting/load a profile (perhaps include a couple of sample profile for demo purposes)
	User my_user = greeter();

	//cout << endl << endl;
	//display_profile(my_user);
	//cout << endl;

	// INSERT PHILOSOPHICAL/JOKE MESSAGE HERE

	// MAIN MENU
	bool on = true;

	while (on == true)
	{
		char selector = 'g';

		cout << "main menu" << endl;
		cout << "----------" << endl;
		cout << "j) JOURNAL an entry" << endl;
		cout << "r) select one of your entries to READ" << endl;
		cout << "p) make PROJECTIONS based on your entries" << endl;
		cout << "a) learn ABOUT mastery log program" << endl;
		cout << "x) EXIT" << endl;

		cin >> selector;

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
			// option 3: MAKE PROJECTIONS
		case 'p':
				analysis_menu(my_user);
				continue;
			// option 4: about/help
		case 'a':
				about();
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

// work flow
/*
 	 1) Test if the update user file function can be used in the way we originally wanted TEST FAILED, MOVE ON AND CIRCLE BACK LATER
 	 2) We have the XXgreeter set upXX, XXwe can write and save entriesXX, now XXwe need to be able to
 	    view entries that the user has associated with their profileXX AND we need to write the
 	    analysis and projection functions. Finally we will write a main loop function, review,
 	    fix and add all neccessary commments and do the write up.

 	 IDEAS: editing existing files? testing suite for teacher evaluation (premade profile with projections
 	        and ability to create files with custom dates) error handling?

 	 CHANGE: FILE SYSTEM, GIVE EACH USER THEIR OWN FOLDER FOR BETTER ORGANIZATION OR AT LEAST
 	 A PREFIX WHICH CAN DISTINGUISH THEIR ENTRIES FROM OTHER USERS ON THE SAME DAY
 */

// TO DO
// 1) Analysis Function Input Validation

// 3) Bug Test HALF DONE
// 4) Create README for Professor
// 4) Write up SEE NOTES
// 5) Extra features (cool quotes, fav_act utilization )
// 1) WHAT IF USER ENTERS A DATE FOR BEGINNING A RANGE WHICH CANNOT BE COMPLETED?
	// WE NEED TO CATCH THAT SITUATION
	// ALSO, WHAT IF THE QUERY TERM IS NOT IN THE VECTOR OF ACTIVITIES? IT WILL QUERY vector[99]. BAD!

// Implement binary paradigm into file system


