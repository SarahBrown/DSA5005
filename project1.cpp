// Summer 2022
// Project 1
// Computing Structures

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int numberOfYears = 51; // number of columns/years, 0 indexed. does not include country/country code

class OneCountry {
protected:
	string 		countryName; // name of the country/region
	string 		countryCode; // code of the country/region
	long long	yearsData[numberOfYears]; // number of people who travelled that year (first year starts with 1970 to 2021)
	long long 	sumTotal; // Total of all years of travel data 

public:
	OneCountry(); // default constructor
	OneCountry(string cn, string cc, long long* yd); //non-default constructor

	void display(); //display method

	string getCountryName(); //getters
	string getCountryCode();
	long long* getYearsData();
	long long getSumTotal();
};
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
void OneCountry::display() {
	cout << "Country Name: " << countryName << ". Country Code: " << countryCode << ". Sum Total: " << sumTotal << "." << endl;
	//cout << "Years Data: ";
	for (int i = 0; i < numberOfYears; i++) {
		cout << yearsData[i] << ' ';
	}
	cout << sumTotal;
	cout << endl;
}
// ---------------------------------------------------------------------------- 
string OneCountry::getCountryName() {
	return countryName;
}
// ---------------------------------------------------------------------------- 
string OneCountry::getCountryCode() {
	return countryCode;
}
// ---------------------------------------------------------------------------- 
long long* OneCountry::getYearsData() {
	return yearsData;
}
// ---------------------------------------------------------------------------- 
long long OneCountry::getSumTotal() {
	return sumTotal;
}
// ----------------------------------------------------------------------------
bool comparator_alpha(OneCountry *a, OneCountry *b) {
	return (a->getCountryName() < b->getCountryName()); // sort in ascending order
}
// ----------------------------------------------------------------------------
bool comparator_total(OneCountry* a, OneCountry* b) {
	return (a->getSumTotal() > b->getSumTotal()); // sort in ascending order
}
// ----------------------------------------------------------------------------
// class to store multiple rows of data
class travelData {
protected:
	OneCountry** allCountries; // array of pointers of class OneCountry
	int numCountries; // This will be the first line in the input
	int countriesAdded; //  

public:
	travelData(); // default constructor
	travelData(int numC); // non-default constructor

	void display(); // display all rows 
	void addCountry(OneCountry* oneC); // add one country
	void sortDataByCountryName(); // sort alphabetically by name of country

	//Queries
	void displayCountry(string countryCode); //command C - display specific country row given countryCode
	OneCountry* findCountry(int kthLargestTotal); //command K - sort allCountries based on sumTotal and find the kth largest country
	int findTravelNums(string countryCode, int year); //assume yearsData[0] is year 1970 - command T - return number for given year and countryCode
	string* findAllCountries(int year, int minTravelNum, int maxTravelNum); //Range Search - command A - given range of year and min and 
																			// max number, return all countries that fall within
};
// ----------------------------------------------------------------------------
travelData::travelData() {
	numCountries = 0;
	countriesAdded = 0;
	allCountries = NULL;
}
// ----------------------------------------------------------------------------
travelData::travelData(int numC) {
	numCountries = numC;
	countriesAdded = 0;
	allCountries = new OneCountry*[numC];
}
// ----------------------------------------------------------------------------
void travelData::display() {
	for (int i = 0; i < numCountries; i++) {
		allCountries[i]->display();
		cout << endl;
	}
}
// ----------------------------------------------------------------------------
void travelData::addCountry(OneCountry* oneC) {
	allCountries[countriesAdded] = oneC;
	countriesAdded++;
}
// ----------------------------------------------------------------------------
void travelData::sortDataByCountryName() {
	sort(allCountries, allCountries+numCountries, comparator_alpha);
}
// ----------------------------------------------------------------------------
void travelData::displayCountry(string countryCode) {
	for (int i = 0; i < numCountries; i++) {
		if (allCountries[i]->getCountryCode() == countryCode) {
			allCountries[i]->display();
		}
	}
}
// ----------------------------------------------------------------------------
OneCountry* travelData::findCountry(int kthLargestTotal) {
	sort(allCountries, allCountries + numCountries, comparator_total);
	OneCountry* temp = allCountries[kthLargestTotal];
	sort(allCountries, allCountries + numCountries, comparator_alpha);
	return temp;
}
// ----------------------------------------------------------------------------
int travelData::findTravelNums(string countryCode, int year) {
	int travelNum = 0;
	for (int i = 0; i < numCountries; i++) {
		if (allCountries[i]->getCountryCode() == countryCode) {
			travelNum = allCountries[i]->getYearsData()[year - 1970];
		}
	}
	return travelNum;
}
// ----------------------------------------------------------------------------
string* travelData::findAllCountries(int year, int minTravelNum, int maxTravelNum) {
	int travelNum = 0;
	string* temp = new string;

	for (int i = 0; i < numCountries; i++) {
		travelNum = allCountries[i]->getYearsData()[year - 1970];
		if (travelNum >= minTravelNum && travelNum <= maxTravelNum) {
			*temp += allCountries[i]->getCountryCode() + " ";
		}
	}
	return temp;
}

int main() {
	travelData* allData = new travelData(); // object to store all the data
	OneCountry* country = new OneCountry(); // temp object to store each row

	ifstream countryFile("dataInput1.txt"); // read in the data file
	ifstream queryFile("queryInput1.txt"); // read in the query file

	int numberOfCountries;
	int numOfQueries;

	string* temp_str;
	string str, buff_line;
	int count = 0;
	int start_substr, end_substr;

	int kthNumber, year, minTravelNum, maxTravelNum;

	string countryN, countryCode; // temp variables to store input
	long long yearD[numberOfYears]; // static array

	char command; // to store command character from query file
	countryFile >> numberOfCountries; // read in the number of countries fromqueryFile
	queryFile >> numOfQueries; // read in the number of countries fromqueryFile

	allData = new travelData(numberOfCountries); // allocate memory and call non default consturctor

	// loop through and store the data
	while (getline(countryFile, buff_line, '\n')) { // splits data on ',' character
		if (buff_line == "") { // skips empty strings
			continue;
		}
		start_substr = 0; end_substr = 0; count = 0;
		end_substr = buff_line.find(",");
		str = buff_line.substr(start_substr, end_substr);
		countryN = str;
		//cout << countryN << endl;
		start_substr = end_substr + 1;

		end_substr = buff_line.substr(start_substr).find(",");
		str = buff_line.substr(start_substr, end_substr);
		countryCode = str;
		//cout << countryCode << endl;
		start_substr += end_substr + 1;
		end_substr = buff_line.substr(start_substr).find(",");

		while (end_substr != -1) {
			str = buff_line.substr(start_substr, end_substr);
			if (count < numberOfYears) {
				yearD[count] = stoll(str);
				//cout << yearD[count] << " ";
			}

			start_substr += end_substr + 1;
			count++;
			end_substr = buff_line.substr(start_substr).find(",");
		}
		//cout << endl;
		country = new OneCountry(countryN, countryCode, yearD);
		allData->addCountry(country);
	}
	allData->sortDataByCountryName();
	(*allData).display();

	for (int i = 0; i < numOfQueries; i++) {
		queryFile >> command;
		cout << command << endl;
		switch (command)
		{
		case 'C': {
			queryFile >> countryCode;
			cout << countryCode << endl;
			allData->displayCountry(countryCode);
			break;
		}
		case 'K': {
			queryFile >> kthNumber;
			cout << kthNumber << endl;
			country = allData->findCountry(kthNumber);
			country->display();
			break;
		}
		case 'T': {
			queryFile >> countryCode;
			cout << countryCode << endl;

			queryFile >> year;
			cout << year << endl;
			count = allData->findTravelNums(countryCode, year);
			cout << "count: " << count << endl;
			break;
		}
		case 'A': {
			queryFile >> year;
			cout << year << endl;
			queryFile >> minTravelNum;
			cout << minTravelNum << endl;
			queryFile >> maxTravelNum;
			cout << maxTravelNum << endl;
			temp_str = allData->findAllCountries (year, minTravelNum, maxTravelNum);
			cout << "code: " << *temp_str << endl;
			break;
		}
		default:
			// TODO
			break;
		}

	}

	return 0;
}