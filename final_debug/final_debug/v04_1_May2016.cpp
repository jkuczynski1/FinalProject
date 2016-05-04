#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include "conio.h"
#include "help.h"
using namespace std;
void wk(int csch, string crs, char *N) // fix this so it returns an array
{
	ofstream x(N); //creates a temporary schedule file (the remove portion will be added later, for now it's run normally and deleted afterward.)
	char d;
	char cwk[14];
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
string its(int a) //some compilers don't understand "to_string" ... so a workaround that is this.
{
	stringstream b;
	b << a;
	return b.str();
}
string cts(char a)
{
	stringstream b;
	b << a;
	return b.str();
}
string CID(int csch, char t) //assigns each class a unique ID. (side note: this optional -- but it's purpose is to make scheduling easier)
{
	/*Notes: The 'char t' gives it a course type, and 'char d' which gives it a semester. The numbers themselves aren't as important, provided they
	are unique for each course. The course type gives it a priority - which is M > G > E. So if an M type class is unavailable, the program needs
	to look for a G type course that fits into the schedule, or lastly, if it is available, it looks for an E type class. So, it sorts it by type,
	then by semester, and the numbers should be unique for that specific class to assign to that semester's schedule. Basically every "S" or "F" goes
	into a temporary "S" or "F" text file. This needs to be created by a sorter function.*/
	string csmtr; //semester
	string cyr; //year
	string IDconvertString, IDstring; //strings for the purpose of conversion of rand and adding of ID string together.
	char d;
	int ID;
	for (int i = 0; i < csch; i++)
	{
		ID = rand();
	}
	IDconvertString = its(ID);
	//t input ==type of requirement. Key: E = elective, G = general requirement, M = major/minor requirement.
	cout << "Semester: (F = Fall or S = Spring) ";
	cin >> csmtr;
	if (csmtr == "F")
	{
		d = 'F';
	}
	else
	{
		d = 'S';
	}
	/*cout << "Term Year: ";
	cin >> cyr;*/
	ID << rand() << rand();
	IDstring = cts(d) + cts(t) + IDconvertString;
	/* if this stays in the final version, it'll require a method so that each ID is unique. Basically the idea is that this will become a specific course's "address"
	which is then put into a table (which goes into the output file) where it needs to go on a schedule. */
	return IDstring;
}

string cmD(string crs, char t) //Creates a schedule (by days); must fix so it also gives times.
{
	/*   string crs; //course name
	cout << "Enter course name to create schedule." << endl << "(Ex: COMP150)" << endl;
	cin >> crs; */
	int csch; //amount of meetings per week
	cout << "How many times does " << crs << " meet per week? ";
	cin >> csch;
	wk(csch, crs, "sch.txt");
	return CID(csch, t);
}

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
string ovrwt(char *N, char *M) //merges two documents into one.
{
	ifstream y(N); //file #1
	ifstream z(M); //file #2
	string a = ""; string b = "";
	if (y.is_open() && z.is_open())
	{
		ofstream x(N);
		while (!y.eof() && !z.eof())
		{
			getline(y, a);
			getline(z, b);
			a += a + "\n";
			b += b + "\n";
		}
	}
	y.close();
	z.close();
	remove(M);
	return a + b;
}
bool seek(char *N, string a) //the course name searcher
							 /* This basically searches for string a in the text file char *N. */
{
	ifstream x(N);
	const char *q;
	q = a.c_str();
	while (x.peek() != EOF)
	{
		getline(x, a);
		if (a.c_str() != q)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
string Rwrt(char t, string a, int k, int y) //The (Co/Pre)requisite prompt function
											/*This function acquires the user input for the co- and/or prerequisites. It uses t (the course type), a (the course name), k (the
											(Co/Pre)requisite counter), and y (the course counter). It returns a string that is acquired by Rsk().*/
{
	char s = 0; //switch key
	string b;
	int z;
	while (s != 27)
	{
		switch (s)
		{
		case 78: //ASCII N
		{
			cout << "Required Course #" << y << "." << k << ": ";
			cin >> a;
			cout << "Credit hours: ";
			cin >> z;
			b = "--->(Co/Pre)-requisite #" + its(k) + ": " + a + "|*| Credit(s): " + its(z) + " CID: " + cmD(a, t);
		}
		case 89: //ASCII Y
		{
			cout << "Required Course #" << y << "." << k << " is: " << a << endl;
			cout << "Credit hours for " << a << ": ";
			cin >> z;
			b = "--->(Co/Pre)-requisite #" + its(k) + ": " + a + "|*| Credit(s): " + its(z) + " CID: " + cmD(a, t);
		}
		case 27:
		{
			return b;
		}
		default:
		{
			cout << "Required Course #" << y << "." << k << " is: " << a << endl;
			cout << "Correct? Y/N ";
			s = _getch();
		}
		}
	}
	return b;
}
string RSk(char *N, char t, string a, int y) // Sets up Rwrt() in a way it can be used.
											 /*Rsk() uses seek() to check if the given course (string a) is found in the file (char *N) and sets up the (Co/Pre)-requisite counter k.*/
{
	char s = 0; //switch key
	string b, w; string c = a;
	bool q = seek(N, a);  //searches the course name (string a) in the text file (char *N) and returns true or false
	int k = 1; int z = 0; int i = 0;
	while (s != 27)
	{
		switch (s)
		{
		case 13: //sets up the boolean
		{

			if (q != false)
			{
				i += y;
				cout << a << " found in file." << endl;
				cout << "\nPress ENTER if there are there other co- or pre-requisites for " << a << ". Or press ESC to exit. " << endl;
				s = _getch();
				while (s == 13)
				{
					b = Rwrt('M', a, k, i);
					cout << "\nRequired Course # " << y << "." << k << "-" << i << ": ";
					cin >> c;
					b += "\n" + Rwrt('M', c, k, i);
					i++;
				}
			}
			else
			{
				cout << "\nRequired Course #" << y << "." << k << ": ";
				cin >> c;
				b = Rwrt('M', c, k, y);
			}
			i++;
			k++;
		}
		case 27:
		{
			return b; //ends loop (or switch)
		}
		default:
		{
			cout << "\nPress ENTER if there are co- or prerequisites for " << a << ". Or press ESC to exit. " << endl;
			s = _getch();
			b += "\n" + b;
		}
		}
	}
	return b;
}
string PReqs(char*N, char t, string a, int y)
//The main (Co/Pre)requisite function; *N = is title of file, a = course name, t = course type
/*This sets up the loop to write/prompt the user for the (Co/Pre)requisites. It replaces the lines 111-136 of an earlier draft of MReqs().
It uses Rsk() to provide the string MReqs () and GEReqs() write into the files they create. */
{
	string b, c, w;
	char s = 0; //switch keys
	cout << "If this is a co-requisite for " << a << " press C.\n";
	cout << "If this is a prerequisite for " << a << " press P. Or press ESC to abort.";
	while (s != 27) //start loop
	{
		s = _getch();
		switch (s)
		{
		case 67: // ASCII for C
		{
			w = cts(s);
			if (w == "C")
			{
				cout << endl << "Please enter co-requisite course name. ";
				cin >> a;
				b = RSk(N, t, a, y);
				c += b + "\n";
			}
		} //end case 89
		case 80: //ASCII for P
		{
			w = cts(s);
			if (w == "P")
			{
				cout << endl << "Please enter prerequisite course name. ";
				cin >> a;
				b = RSk(N, t, a, y);
				c += b + "\n";
			}
		} //end case 78
		case 27: //ASCII for ESC
		{
			return c; //ends loop
		}
		default:
		{
			cout << endl << "If the course you are entering is a co-requisite, press C." << endl;
			cout << "If it's a prerequisite, press P.\nOr to abort, press ESC. " << endl;
			s = _getch();
		}
		}
	}
}
/*Notes [4 May 2016]: There is an error somewhere in one of the functions -- PReqs(), Rsk() or Rwrt() so it you need to input the first co- or
prerequisite twice in order for it to appear in the actual file. This needs to be fixed ASAP.*/
void MReqs(char *N, int v, string m, int tC) // writes the required courses text file
{
	ofstream x(N);
	string a, b, w;
	char s, s2, s3, s4; //switch keys
	int y = 1;
	int z = 0;
	int k = 1;
	x << "****************************************************************" << endl;
	x << "Requirements for: " << m << " MAJOR                " << "Total Credit Hours: " << tC << endl;
	x << "================================================================" << endl;
	cout << m << " Requirements. Please enter all required courses as prompted. (ex: BIOL101)\nPress ENTER to continue or ESC to exit." << endl;
	do //begin loop
	{
		s = _getch();
		switch (s)
		{
		case 13: //sets up the loop used to acquire the course requirements to write the requirements file.
		{
			for (int i = 1; i <= v; i++) //starts Major requirement loop
			{
				cout << "\nRequired Course #" << y << ": ";
				cin >> a;
				cout << "Credit hours: ";
				cin >> z;
				x << "Required Course #" << y << ": " << a << "|*| Credit(s): " << z << "|*| CID: " << cmD(a, 'M') << endl;
				cout << endl << "NOTE: For the following Y/N questions, you must enter Y or N only." << endl;
				cout << "\nDoes this course have co- or pre-requisites? Y/N ";
				s2 = _getch();
				switch (s2)
				{
				case 89: //s == "Y"
				{
					w = PReqs(N, 'M', a, y); //acquires (Co/Pre)requirement string using PReqs()
					x << w << endl; //writes the string
					y++;
					cout << "\nPress ESC to exit or ENTER to continue. ";
					s = _getch();
					if (y > v && s == 13)
					{
						cout << "\nYou have exceeded the number of required courses. Please press ESC to exit. " << endl;
						s = _getch();
					}
				}
				case 78:
				{
					s = 27;
				}
				default:
				{
					cout << "\nDoes this course have a co- or prerequisite? Y/N ";
				}
				}
			} //ends major requirements loop

		}//end case 13
		case 27:
		{
			return; //ends loop
		} //end case 27
		default:
		{
			cout << "LOOP @ line 223!!" << endl; //write anything in here to test switch
		}
		} //end switch s
	} while (s != 27);
	/*   do
	{
	cout << "Do you have a minor? Y/N " << endl;
	s2 = getch();
	switch(s2)
	{
	case 89: // s2 == "Y"
	{
	cout << "Minor: ";
	cin >> m;
	cout << "Total credit hours required for " << m << ": ";
	cin >> tC;
	cout << "How many courses are required for minor? ";
	cin >> v;
	a = "1";
	y = 1;
	x << endl << "================================================================" << endl;
	x << "Requirements for: " << m << " MINOR                " << "Total Credit Hours: " << tC << endl;
	x << "****************************************************************" << endl;
	for (int i = 1; i <= v; i++)
	{
	cout << "\nRequired Course #" << y << ": ";
	cin >> a;
	cout << "Credit hours: ";
	cin >> z;
	x << "Required Course #" << y << ": " << a << "|*| Credit(s): " << z << "|*| CID: " << cmD(a,'M') << endl;
	cout << endl << "NOTE: For the following Y/N questions, you must enter Y or N only." << endl;
	cout << "\nDoes this course have co- or pre-requisites? Y/N ";
	s2 = getch();
	switch(s2)
	{
	case 89: //s == "Y"
	{
	w = PReqs(N,'M',a,y); //acquires (Co/Pre)requirement string using PReqs()
	x << w << endl; //writes the string
	y++;
	cout << "\nPress ESC to exit or ENTER to continue. ";
	s = getch();
	if (y > v && s == 13)
	{
	cout << "\nYou have exceeded the number of required courses. Please press ESC to exit. " << endl;
	s = getch();
	}
	}
	case 78:
	{
	s = 27;
	}
	default:
	{
	cout << "\nDoes this course have a co- or prerequisite? Y/N ";
	}
	}

	}
	}
	case 78: //s2 == "N"
	{
	m = "NONE";
	tC = 0;
	a = "0";
	}
	case 27: //ESC
	{
	return;
	}
	default:
	{
	cout << "If you have a minor, press Y.\nTo exit, press ESC. " << endl;
	}
	}
	} while(s2 != 27);
	*/
	if (a == "Y" || a == "N")
	{
		if (a == "Y" || a == "y")
		{
			cout << "Minor: ";
			cin >> m;
			cout << "Total credit hours required for " << m << ": ";
			cin >> tC;
			cout << "How many courses are required for minor? ";
			cin >> v;
			a = "1";
			y = 1;
			x << endl << "================================================================" << endl;
			x << "Requirements for: " << m << " MINOR                " << "Total Credit Hours: " << tC << endl;
			x << "****************************************************************" << endl;

		}
		if (a == "N" || a == "n")
		{
		}
	}
	while (a != "0")
	{
		for (int i = 1; i <= v; i++)
		{
			cout << "Required Course #" << y << ": ";
			cin >> a;
			cout << "Credit hours: ";
			cin >> z;
			x << "Required Course #" << y << ": " << a << "| | Credit(s): " << z << " CID: " << cmD(a, 'M') << endl;
			cout << "NOTE: For the following Y/N questions, you must enter Y or N only.";
			cout << "\nDoes this course have co- or pre-requisites? Y/N ";
			cin >> b;
			if (b == "Y" || b == "y") // So that it doesn't repeat courses in the output file.
			{
				cout << "Is this co- or pre-requisite also a required course for " << m << " minor? Y/N " << endl;
				cin >> b;
				if (b == "Y" || b == "y")
				{
					b = "N";
				}
				else
				{
					b = "Y";
				}
				b;
			}
			while (b != "N" || b != "n" && b == "Y" || b == "y")
			{
				if (b == "Y" || b == "y")
				{
					cout << "Required Course #" << y << "." << k << ": ";
					cin >> w;
					cout << "Credit hours: ";
					cin >> z;
					x << "--->" << "(Co/Pre)-requisite #" << k << ": " << w << "| | Credit(s): " << z << " CID: " << cmD(w, 'M') << endl;
					cout << "Are there other co- or pre-requisites for " << a << "? Y/N ";
					cin >> b;
					k++;
				}
			}
			y++;
			cout << "Press 0 to exit or 1 to continue. ";
			cin >> a;
			if (y > v && a != "0")
			{
				cout << "You have exceeded the number of required courses. Please press 0 to exit. ";
				cin >> a;
			}
		}
	}
}

void GEReqs(char *N, int v, int tC)
{
	/*The goal of this function is to set up the general ed and/or elective requirements. It must add its contents to the file created by MReqs to work properly.*/
	ofstream x(N);
	string a, b, w;
	char s, s2, s3, s4; //switch keys
	int y = 1;
	int z = 0;
	int k = 1;
	//    int j = 0;
	x << "****************************************************************" << endl;
	x << "General Requirements " << "                      " << "Total Credit Hours: " << tC << endl;
	x << "================================================================" << endl;
	cout << "Please enter all required courses as prompted. (ex: BIOL101)\nPress ENTER to continue or ESC to exit." << endl;
	do //begin loop
	{
		s = _getch();
		switch (s)
		{
		case 13: //sets up the loop used to acquire the course requirements to write the requirements file.
		{
			for (int i = 1; i <= v; i++) //starts Major requirement loop
			{
				cout << "\nRequired Course #" << y << ": ";
				cin >> a;
				cout << "Credit hours: ";
				cin >> z;
				x << "Required Course #" << y << ": " << a << "|*| Credit(s): " << z << "|*| CID: " << cmD(a, 'M') << endl;
				cout << endl << "NOTE: For the following Y/N questions, you must enter Y or N only." << endl;
				cout << "\nDoes this course have co- or pre-requisites? Y/N ";
				s2 = _getch();
				switch (s2)
				{
				case 89: //s == "Y"
				{
					w = PReqs(N, 'G', a, y); //acquires (Co/Pre)requirement string using PReqs()
					x << w << endl; //writes the string
					y++;
					cout << "\nPress ESC to exit or ENTER to continue. ";
					s = _getch();
					if (y > v && s == 13)
					{
						cout << "\nYou have exceeded the number of required courses. Please press ESC to exit. " << endl;
						s = _getch();
					}
				}
				case 78:
				{
					s = 27;
				}
				default:
				{
					cout << "\nDoes this course have a co- or prerequisite? Y/N ";
				}
				}
			} //ends major requirements loop

		}//end case 13
		case 27:
		{
			return; //ends loop
		} //end case 27
		default:
		{
			cout << "LOOP @ line 223!!" << endl; //write anything in here to test switch
		}
		} //end switch s
	} while (s != 27);
}
void courselist() //creates major/minor requirements doc
{
	/*This function creates the course requirements file.*/
	char *N = "reqs.txt"; //keep in mind that once we finish writing the entire program, this will be converted into a prompt so the user can come up with their own title.
	ofstream x;
	x.open(N);
	string maj, minr, gen, a;
	int creds;
	int y = 0; int z = 0; int v = 0;
	char s; char s2;
	cout << "You will be asked a series of questions. Please omit all spaces in your replies." << endl;
	cout << "If the program asks a Y/N question, please enter Y or N only. " << endl;
	s = 13;
	while (s != 27)
	{
		switch (s)
		{
		case 63: //? key
		{
			help("help.txt");
			remove("help.txt");
			cout << "Press ENTER to continue or ESC to exit. ";
			s = _getch();
		} //ends case 63 for s
		case 13: //ENTER key
		{
			cout << "The following questions relate to your major ONLY. " << endl;
			cout << "What is your major? ";
			cin >> maj;
			cout << "Enter total number of credits needed for " << maj << ". ";
			cin >> creds;
			z += creds;
			cout << "How many total courses required for " << maj << " major? ";
			cin >> v;
			MReqs(N, v, maj, z);
			cout << "If you would like to enter your general ed requirements, press ENTER. To exit, press ESC. " << endl;
			s2 = _getch();
			switch (s2)
			{
			case 13:
			{
				cout << "The following questions relate your general ed requirements only. " << endl;
				gen = "General Requirements";
				cout << "Enter the total credit hours for your " << gen << ": ";
				cin >> creds;
				z = creds;
				cout << "How many total courses required for " << gen << "? ";
				cin >> v;
				GEReqs("gereq.txt", v, z);
				s = 27;
			}
			case 27:
			{
				s = 27;
			}
			default:
			{
				cout << "Invalid key entered. Please press ENTER, ESC, or ?. " << endl;
			}
			}
		} //ends case 13 for s
		case 27: //ESC key
		{
			break;
		} //ends case 27 for s
		default:
		{
			cout << "Invalid key entered. Please press ENTER, ESC or ?. " << endl;
		}
		} //ends switch
	} // ends while loop
}
void RunP() //this basically runs the entire program.... leave it until the end (either keep or remove)
{
	char *N = "reqs.txt";
	ofstream x(N);
	char s; string b;
	cout << "To start program press ENTER, to exit press ESC. For help, press ?. " << endl;
	s = _getch();
	while (s != 27)
	{
		switch (s) //this is using the ascii char code
		{
		case 13:
		{
			courselist();
		}
		case 27:
		{
			cout << "Program is terminating......" << endl << endl;
			cout << "Goodbye!" << endl << endl;
			char *M = "sch.txt";
			char *P = "gereq.txt";
			ofile(M); //reads temp. schedule file
					  //                    x << ovrwt(N,P) << endl;
			remove(M); //deletes temp. schedule file
			system("cls"); //clears the screen so only the output file shows up on the screen
			ofile(N);
			return;
		}
		case 63:
		{
			help("help.txt");
			remove("help.txt");
			cout << "Press ENTER to continue or ESC to exit." << endl;
			s = _getch();
		}
		default:
		{
			cout << "Please press ENTER, ESC, or ?. " << endl;
		}
		}
	}
}

int main()
{
	RunP();
	return 0;
}

