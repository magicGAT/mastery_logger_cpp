
#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_


#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class User;
class Entry;
struct Activity;
struct Expenditure;


// consider implementing this a static class object to avoid confusion
// when using the user object in and around many, many function calls

class User
{
	private:
	public:
		string profile_name;
		string preferred_name;
		string fav_act;
		bool sex;
		vector<string> entries;
		void browse_entries();
		void display_entry();
		// bool update_userf(Entry);

};

// POSSIBLE STRUCTS
// ideas: make an entry an array of structs, then the user can determine how many activities
// and expenditures they will include per journal entry. They we will need "header" like object
// which contains the file name

// Possible key table to store filenames in a system similar to the database design outline in
// adv programming and algo class


// I think we need to ask for a list of activites and expenditures BEFORE generating the Entry
// so that we can fill the two count variables
class Entry
{
	private:


	public:
		int act_count; //number of activities for generating array MUST BE DETERMINED BEFORE INSTANTIATION
		int ex_count; //number of expenditures for
		Entry(int, int); // constructor
		~Entry(); // destructor
		string date; // functions like a title
		Activity * act_arr; // pointer to an array of activities
		Expenditure * ex_arr; // pointer to an array of expenditures
		void write_act(vector<string>&, int);
		void write_ex(vector<string>&, int);
		bool write_to_file();
		bool update_userf(User); // I dont like that this is a member of the Entry class rather than the User struct
		void display_entry();
};

struct Activity
{
	public:
		string a_name;
		float time;
};

struct Expenditure
{
	public:
		string e_name;
		float price;
		// what if we added a metric for quantity? is it better to have general categories
		// so that we increase use across goods AND services :dunno:
};



///////--GENERAL FUNCTION PROTOTYPES--///////

string day_o_year();

void generate_entry(User&);

// helper function for greeter which returns the hour of the day
int time_o_day();

string generate_dphase(int);
///////----///////


///////--LOG WRITING && READING--///////

void generate_entry(User&);

Entry open_entry(string, int, int);


///////----///////


///////--PROFILE FUNCTIONS--///////
// searches a folder for a filename which contain user info used by the greeter() function
bool find_profile(string);

bool save_new_profile(User);

// equates the actual users profile with the user object used by the program
User load_profile(string);

User load_guest();

void display_profile(User);

void display_profile(string, string, string, bool);

// creates a new profile to be saved as a formated .txt file
User create_profile();

// greets user. first prompts for a profile name or to create a new profile
// (male female,
User greeter();

void display_menu();

///////----///////






#endif /* PROTOTYPES_H_ */




