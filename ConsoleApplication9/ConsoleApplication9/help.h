#include <fstream>
#include <iostream>

using namespace std;

void help(char *N) //creates the help file
				   /*The purpose of function is to write down how everything is supposed to work. (Basically it's the documentation.
				   So update and/or change as necessary! (ASIDE: If we're keeping this, we should probably write a separate section
				   for each function and tie into "function /?" so the document provides the necessary information for that function.*/
{
	ofstream x(N);
	string a;
	x << "The ultimate goal of this program is to provide a user with a four-year class schedule. \nAt the moment, the program does not read "
		<< "spaces." << endl;
	x << "So, if your major is computer science, you need to write something like \"COMPSCI\" or \"CS\" or "
		<< "\"Computer_Science\"." << endl;
	ifstream z(N);
	while (!z.eof())
	{
		getline(z, a);
		cout << a << endl;
	}
	remove(N);
	/*
	int csch = # of times a class meets per week, string crs = course name, char *N = title of file read/created.
	void wk (int csch, string crs, char *N)
	char d = is the day each class meets
	char cwk[14] = is the array the days go into
	void CID (int csch)
	void cmD (string crs)
	void ofile(char *N)
	void MReqs (char *N, int v, string m, int tC)
	int v = number of courses, string m = major, int tC = total credits
	void courselist ()
	*/
}

