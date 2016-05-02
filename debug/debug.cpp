#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;
void wk(int csch, string crs, char *N) // fix this so it returns an array
{
	ofstream x(N); //creates a temporary schedule file (the remove portion will be added later, for now it's run normally and deleted afterward.)
	char d;
	char cwk[14];//formerly char cwk[csch]. CLasses will not meet 14x in a single week, so this si why 14 is used.
	cout << "Which days does " << crs << " meet? " << endl;
	cout << "************************************************************************************************************************" << endl;
	cout << "** M - Monday || " << "T - Tuesday || " << "W - Wednesday || " << "R - Thursday || " << "F - Friday || " << "S - Saturday || " << "U - Sunday **" << endl;
	cout << "************************************************************************************************************************" << endl;
	for (int i = 0; i < csch; i++)
	{
		cin >> d;
		cwk[i] = d;
	}
	x << crs << " meets on: ";
	for (int i = 0; i < csch; i++)
	{
		x << cwk[i];
	}
}
void CID(int crs) //assigns each class a unique ID. (side note: this optional -- but it's purpose is to make scheduling easier)
{
	string csmtr; //semester
	string cyr; //year
	char d, t;//type = general requirements, elective, etc.
	int ID;
	for (int i = 0; i < crs; i++)
	{
		ID = rand();
	}
	cout << "Key: E = elective, G = general requirement, M = major/minor requirement."; //this is here for now; it'll be removed later.
	cout << "This course is a(n): ";
	cin >> t;
	cout << "Semester: (F = Fall or S = Spring) ";
	cin >> csmtr;
	if (csmtr == "F"|| csmtr == "f")
	{
		d = 'F';
	}
	else
	{
		d = 'S';
	}
	cout << "Term Year: ";
	cin >> cyr;
	ID << rand() << rand();
	cout << "course ID: " << t << d << ID << endl;
	/* if this stays in the final version, it'll require a method so that each ID is unique. Basically the idea is that this will become a specific course's "address"
	which is then put into a table (which goes into the output file) where it needs to go on a schedule. */
}
void cmD(string crs) //Creates a schedule (by days); must fix so it also gives times.
{
	/*   string crs; //course name
	cout << "Enter course name to create schedule." << endl << "(Ex: COMP150)" << endl;
	cin >> crs; */
	int csch; //amount of meetings per week
	cout << "How many times does " << crs << " meet per week?" << endl;
	cin >> csch;
	wk(csch, crs, "sch.txt");
	CID(csch);
}
/*It might look better if we change these into classes somehow and separate them from the main file.*/
void ofile(char *N) //reads the selected file
{
	ifstream x(N);
	string a;
	while (!x.eof())
	{
		getline(x, a);
		cout << a << endl;
	}
}
void MReqs(char *N, int v, string m, int tC) // writes the required courses text file
{
	ofstream x(N);
	string a, b, w;
	int y = 1;
	int z = 0;
	int k = 1;
	x << "****************************************************************" << endl;
	x << "Requirements for: " << m << "                      " << "Total Credit Hours: " << tC << endl;
	x << "****************************************************************" << endl;
	do
	{
		if (a != "0")
		{
			for (int i = 1; i < v; i++)
			{
				cout << "Required Course #" << y << ": ";
				cin >> a;
				cmD(a);
				cout << "Credit hours: ";
				cin >> z;
				x << "Required Course #" << y << ": " << a << "| | Credit(s): " << z << endl;
				cout << "Does this course have co- or pre-requisites? Y/N";
				cin >> b;
				cout << b << endl;
				while (b != "N" || b != "n" || b != "Y" || b != "y")
				{
					cout << "\n You may only respond with [Y]es or [N]o. Please enter either y, n, Y, or N. \nDoes this course have co- or pre-requisites? Y/N" << endl;
					cin >> b;
				}
				while (b != "N" || b != "n" || b == "Y" || b == "y")
				{
					cout << "Required Course #" << y << "." << k << ": ";
					cin >> w;
					cmD(w);
					cout << "Credit hours: ";
					cin >> z;
					x << "--->" << "(Co/Pre)-requisite #" << k << ": " << w << "| | Credit(s): " << z << endl;
					cout << "Are there other co- or pre-requisites for " << a << "? Y/N ";
					cin >> b;
					k++;
				}
				
				y++;
				cout << "Press 0 to exit or 1 to continue. ";
				cin >> a;
			}
		}
		else
		{
			break;
		}
	} while (a != "0");
	cout << "Do you have a minor? Y/N " << endl;
	/* Notes: This still needs to be fixed so that it does the exact same thing as the "major" portion of this function.*/
	cin >> a;
	if (a == "Y" || a == "N")
	{
		if (a == "Y" || a == "y")
		{
			cout << "Minor: " << endl;
			cin >> m;
			cout << "Total credit hours required for " << m << ": " << endl;
			cin >> tC;
		}
		if (a == "N" || a == "n")
		{
			m = "NONE";
			tC = 0;
			cout << "To finish, press 0. ";
			cin >> a;
		}
	}

}
void courselist() //creates major/minor requirements doc
{
	/*This function creates the course requirements file.*/
	char *N = "reqs.txt";
	ofstream x;
	x.open(N);
	string maj, minr, gen, a;
	int creds;
	int y = 0; int z = 0; int v = 0;
	// z[total number of classes]

	cout << "To start press 1. To exit press 0. ";
	cin >> a;
	if (a != "0")
	{
		cout << "Major: ";
		cin >> maj;
		cout << "Insert total number of credits needed to graduate. ";
		cin >> creds;
		z += creds;
		cout << "How many courses required? ";
		cin >> v;
		cout << maj << " Requirements. Please insert required courses. (ex: BIOL101)" << endl;
		if (a != "0")
		{
			MReqs(N, v, maj, z);
		}
		char *M = "sch.txt";
		ofile(M); //reads temp. schedule file
		remove(M); //deletes temp. schedule file
	}
	else if (a == "0")
	{
		cout << "Goodbye." << endl;
	}
}
void RunP() //this basically runs the entire program.... leave it until the end.
{
	char *N = "reqs.txt";
	courselist();
	ofile(N);
}
int main()
{
	RunP();
	return 0;
}
