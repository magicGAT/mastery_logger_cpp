
#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

//include statements
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// pre-declaration of ADTs
class User;
class Entry;
struct Activity;
struct Expenditure;


// USER CLASS: ADT representing a user's personal profile. Contain a username (for login),
// a personal name (by which, the program refers to the user), a favorite activity (for
// personalized messages from the program), sex (also for personalization), and a vector
// which holds a list of the user's associated entries
class User
{
	private:
	public:
		string profile_name;
		string preferred_name;
		string fav_act; // CURRENTLY NOT BEING UTILIZED
		bool sex;
		vector<string> entries;
		void browse_entries(); //displays associated entries to the user
};

// ENTRY CLASS: ADT which defines a log entry and contains all it data. It's constructor
// takes two integers as arguments. These determine the size of two dynamically allocated
// arrays. Those integers represent the number of activities and expenditures which the
// log accounts for. And those arrays are groups of the structures `Activity` and `Expenditure`
// respectively. The class also contains a date field (this functions as a title in addition
// to recording chronology of the entry) and, two pointers to the dynamically allocated arrays
// of the appropriate type. Because these arrays, the class requires a customized constructir,
// destructor, copy constructor, and copy assignment operator.
class Entry
{
	public:
		int act_count;
		int ex_count;
		string date;
		Activity * act_arr;
		Expenditure * ex_arr;
		Entry(int, int); // constructor
		~Entry(); // destructor
		Entry(const Entry &copy); // copy constructor
		Entry& operator = (const Entry &to_copy); // copy assignment operator
		void write_act(vector<string>&, int); // called by the function which generates new entries
		void write_ex(vector<string>&, int); // called by the function which generates new entries
		bool write_to_file(); // saves entries to a file in a format which can be loaded correctly later
		bool update_userf(User); // CHECK IF THIS CAN BECOME A USER MEMBER FUNCTION
		void display_entry();// allows an entry object to be viewed in detail by a user
};

// LOG STRUCTURES: These are the elements of which any log is composed. They are stored within
// the entry's respective arrays

// ACTIVITY STRUCTURE: Contains a single activity within an entry. It has a name (ex. `Running`)
// and a record of the amount of time spent on each activity (in hours).
struct Activity
{
	public:
		string a_name;
		float time;
};

// EXPENDITURE STRUCTURE: Contains a single expenditure within an entry. It, also, has a name
// (ex. `Gasoline`) and cost associated with the particular expense (in units of currency (ex. USD)).
struct Expenditure
{
	public:
		string e_name;
		float price;
		// QUANTITY?

};


///////--GENERAL FUNCTION PROTOTYPES--///////
string day_o_year(); // helper function for generating entry dates

int time_o_day(); // helper function for greeter which returns the hour of the day

string generate_dphase(int); // UNFINISHED


///////--LOG WRITING && READING--///////
void generate_entry(User&); // large function for writing and properly saving new log entries

Entry open_entry(string, int, int); // opens an entry file and returns it as an `Entry` object


///////--PROFILE FUNCTIONS--///////
bool find_profile(string); // searches for and loads a user via their file

User create_profile(); // gathers information for a new profile

bool save_new_profile(User); // saves a new profile permanently to a file

User load_profile(string); // loads a profile into the program's `User` object from file

User load_guest(); // loads the pre-packaged `guest` profile

void display_profile(User); // displays a user's details in a readable format

void display_profile(string, string, string, bool); // overloaded form of the above function for use during profile generation
													// when a user object is not available

User greeter(); // fills the program's user object with either and existing user, the guest profile
				// or by generating a new profile

void main_menu(); // the looping main menu function


// WE NEED A FUNCTION WHICH UTILIZES THE RANDOM LIBRARY




#endif /* PROTOTYPES_H_ */




