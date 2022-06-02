/*
* Name: Sarah Brown
* Course: DSA 5005 - Computing Structures
* Summer 2002
* Project 1: 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int numberOfYears = 51; // number of columns/years, 0 indexed. does not include country/country code

// ----------------------------------------------------------------------------
// Class definition for OneCountry to store one row of data
// ----------------------------------------------------------------------------
class OneCountry {
protected:
	string 		countryName;				// name of the country/region
	string 		countryCode;				// code of the country/region
	long long	yearsData[numberOfYears];	// number of people who travelled that year (first year starts with 1970 to 2021)
	long long 	sumTotal;					// Total of all years of travel data 

public:
	OneCountry();										// default constructor
	OneCountry(string cn, string cc, long long* yd);	//non-default constructor

	void display(); // display method

	// getters
	string		getCountryName(); 
	string		getCountryCode();
	long long*	getYearsData();
	long long	getSumTotal();
};

// ----------------------------------------------------------------------------
// OneCountry default constructor
// ----------------------------------------------------------------------------
OneCountry::OneCountry() {
	countryName = "";
	countryCode = "";
	for (int i = 0; i < numberOfYears; i++) {
		yearsData[i] = 0;
	}
	sumTotal = 0;
}

// ----------------------------------------------------------------------------
// OneCountry non-default constructor
// ----------------------------------------------------------------------------
OneCountry::OneCountry(string cn, string cc, long long* yd) {
	countryName = cn;
	countryCode = cc;
	sumTotal = 0;
	for (int i = 0; i < numberOfYears; i++) {
		yearsData[i] = yd[i];
		sumTotal += yearsData[i];
	}
}

// ----------------------------------------------------------------------------
// OneCountry display method
// ----------------------------------------------------------------------------
void OneCountry::display() {
	// TODO: Change this to match expected format when gradescope and test output are released. 
	cout << "Country Name: " << countryName << ". Country Code: " << countryCode << ". Sum Total: " << sumTotal << "." << endl;
	for (int i = 0; i < numberOfYears; i++) {
		cout << yearsData[i] << ' ';
	}
	cout << sumTotal;
	cout << endl;
}

// ----------------------------------------------------------------------------
// OneCountry accesor method for country name
// ----------------------------------------------------------------------------
string OneCountry::getCountryName() {
	return countryName;
}

// ----------------------------------------------------------------------------
// OneCountry accesor method for 
// ----------------------------------------------------------------------------
string OneCountry::getCountryCode() {
	return countryCode;
}

// ----------------------------------------------------------------------------
// OneCountry accesor method for 
// ----------------------------------------------------------------------------
long long* OneCountry::getYearsData() {
	return yearsData;
}

// ----------------------------------------------------------------------------
// OneCountry accesor method for 
// ----------------------------------------------------------------------------
long long OneCountry::getSumTotal() {
	return sumTotal;
}

// ----------------------------------------------------------------------------
// function to use with sort algorithm to alphabetically sort in A-Z order
// ----------------------------------------------------------------------------
bool comparator_alpha(OneCountry *a, OneCountry *b) {
	return (a->getCountryName() < b->getCountryName()); // sort in ascending order
}

// ----------------------------------------------------------------------------
// function to use with sort algorithm to numerically sort in descending order
// ----------------------------------------------------------------------------
bool comparator_total(OneCountry* a, OneCountry* b) {
	return (a->getSumTotal() > b->getSumTotal()); // sort in descending order
}

// ----------------------------------------------------------------------------
// Class definition for travelData class to store multiple rows of data
// ----------------------------------------------------------------------------
class travelData {
protected:
	OneCountry** allCountries;	// array of pointers of class OneCountry
	int numCountries;			// this will be the first line in the input
	int countriesAdded;			// keeps track of how many countries have been added

public:
	travelData();			// default constructor
	travelData(int numC);	// non-default constructor

	void display();						// display all rows 
	void addCountry(OneCountry* oneC);	// add one country
	void sortDataByCountryName();		// sort alphabetically by name of country

	//Queries
	void displayCountry(string countryCode);			//command C - display specific country row given countryCode
	OneCountry* findCountry(int kthLargestTotal);		//command K - sort allCountries based on sumTotal and find the kth largest country
	long long findTravelNums(string countryCode, int year);	//assume yearsData[0] is year 1970 - command T - return number for given year and countryCode
	string* findAllCountries(int year, long long minTravelNum, long long maxTravelNum); //Range Search - command A - given range of year and min and 
																			// max number, return all countries that fall within
};

// ----------------------------------------------------------------------------
// travelData default constructor
// ----------------------------------------------------------------------------
travelData::travelData() {
	numCountries = 0;
	countriesAdded = 0;
	allCountries = NULL;
}

// ----------------------------------------------------------------------------
// travelData non-default constructor
// ----------------------------------------------------------------------------
travelData::travelData(int numC) {
	numCountries = numC;
	countriesAdded = 0;
	allCountries = new OneCountry*[numC];
}

// ----------------------------------------------------------------------------
// travelData display method
// ----------------------------------------------------------------------------
void travelData::display() {
	for (int i = 0; i < numCountries; i++) {
		allCountries[i]->display();  // loops through and displays all countries
		cout << endl;
	}
}

// ----------------------------------------------------------------------------
// travelData method to add a row of data
// ----------------------------------------------------------------------------
void travelData::addCountry(OneCountry* oneC) {
	allCountries[countriesAdded] = oneC;
	countriesAdded++;
}

// ----------------------------------------------------------------------------
// travelData method to sort data alphabetically
// ----------------------------------------------------------------------------
void travelData::sortDataByCountryName() {
	sort(allCountries, allCountries + numCountries, comparator_alpha);
}

// ----------------------------------------------------------------------------
// travelData method to display a country by country code
// ----------------------------------------------------------------------------
void travelData::displayCountry(string countryCode) {
	for (int i = 0; i < numCountries; i++) {
		if (allCountries[i]->getCountryCode() == countryCode) { // finds matching country code
			allCountries[i]->display();
		}
	}
}

// ----------------------------------------------------------------------------
// travelData method to sort by largest and find the kth largest
// ----------------------------------------------------------------------------
OneCountry* travelData::findCountry(int kthLargestTotal) {
	sort(allCountries, allCountries + numCountries, comparator_total); // sorts numerically
	OneCountry* temp = allCountries[kthLargestTotal];
	sort(allCountries, allCountries + numCountries, comparator_alpha);  // resorts alphabetically
	return temp;
}

// ----------------------------------------------------------------------------
// travelData method to return travel number of a country during a given year
// ----------------------------------------------------------------------------
long long travelData::findTravelNums(string countryCode, int year) {
	long long travelNum = 0;
	for (int i = 0; i < numCountries; i++) {
		if (allCountries[i]->getCountryCode() == countryCode) { // finds right country
			travelNum = allCountries[i]->getYearsData()[year - 1970]; // gets correct year
		}
	}
	return travelNum;
}

// ----------------------------------------------------------------------------
// travelData method to find countries in a certain range
// ----------------------------------------------------------------------------
string* travelData::findAllCountries(int year, long long minTravelNum, long long maxTravelNum) {
	long long travelNum = 0;
	string* temp = new string;

	for (int i = 0; i < numCountries; i++) {
		travelNum = allCountries[i]->getYearsData()[year - 1970];
		if (travelNum >= minTravelNum && travelNum <= maxTravelNum) {
			*temp += allCountries[i]->getCountryCode() + " "; // adds matching country to string
		}
	}
	return temp;
}

// ----------------------------------------------------------------------------
// main method to run code
// ----------------------------------------------------------------------------
int main() {
	travelData* allData = new travelData(); // object to store all the data
	OneCountry* country = new OneCountry(); // temp object to store each row

	ifstream countryFile("dataInput1.txt"); // read in the data file
	ifstream queryFile("queryInput1.txt"); // read in the query file

	int numberOfCountries, numOfQueries;

	// variables to process input file
	string* temp_str;
	string str, buff_line;
	int count, start_substr, end_substr;

	// variables to process queries
	int kthNumber, year;
	long long travelNum, minTravelNum, maxTravelNum;
	char command;

	string countryN, countryCode;	// temp variables to store input
	long long yearD[numberOfYears]; // static array

	countryFile >> numberOfCountries;	// read in the number of countries fromqueryFile
	queryFile >> numOfQueries;			// read in the number of countries fromqueryFile

	allData = new travelData(numberOfCountries); // allocate memory and call non default consturctor

	// loop through and store the data
	while (getline(countryFile, buff_line, '\n')) { // splits data on '\n' character
		if (buff_line == "") { // skips empty strings
			continue;
		}

		start_substr = 0; end_substr = 0; count = 0; // resets variables to 0 per newline

		// splits into substring to find country name
		end_substr = buff_line.find(",");
		str = buff_line.substr(start_substr, end_substr);
		countryN = str;
		start_substr = end_substr + 1;

		// splits into substring to find country code
		end_substr = buff_line.substr(start_substr).find(",");
		str = buff_line.substr(start_substr, end_substr);
		countryCode = str;
		start_substr += end_substr + 1;
		end_substr = buff_line.substr(start_substr).find(",");

		// loops over remaining substrings to find year data
		while (end_substr != -1) {
			str = buff_line.substr(start_substr, end_substr);
			if (count < numberOfYears) {
				yearD[count] = stoll(str);
			}

			start_substr += end_substr + 1;
			count++;
			end_substr = buff_line.substr(start_substr).find(",");
		}

		// creates new OneCountry and adds it to allData per line of data
		country = new OneCountry(countryN, countryCode, yearD);
		allData->addCountry(country);
	}
	
	// sorts allData by country name and displays result of sort
	allData->sortDataByCountryName();
	(*allData).display();

	// loops over queries input file
	for (int i = 0; i < numOfQueries; i++) {
		queryFile >> command; // loads command
		switch (command) { // switch statement to process the various commands
			// command C - display specific country row given countryCode
			case 'C': {
				// loads variable for command C
				queryFile >> countryCode;
				allData->displayCountry(countryCode);
				break;
			}

			// command K - sort allCountries based on sumTotal and find the kth largest country
			case 'K': {
				// loads variable for command K

				queryFile >> kthNumber;
				country = allData->findCountry(kthNumber);
				country->display();
				break;
			}

			// command T - return number for given year and countryCode
			case 'T': {
				// loads variables for command T
				queryFile >> countryCode;
				queryFile >> year;

				travelNum = allData->findTravelNums(countryCode, year);
				cout << "count: " << travelNum << endl;
				break;
			}

			// command A - given range of year and min and max number, return all countries that fall within
			case 'A': {
				// loads variables for command A
				queryFile >> year;
				queryFile >> minTravelNum;
				queryFile >> maxTravelNum;

				temp_str = allData->findAllCountries (year, minTravelNum, maxTravelNum);
				cout << "code: " << *temp_str << endl;
				break;
			}

			// default command, do nothing
			default:
				break;
		}

	}

	return 0;
}