#include "stdafx.h"//forgot this 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "help.h"

using namespace std;

/*
struct MeetingTime
{
	// store a reference to the 'SchoolClass' instance ??
	char day;// day a class meets...may be multiple-see line 25.
	int start_time;//in the format of ABCD, not AB:CD; also in military time, so if in PM, add 12 to AB. 
	//Will reformat for when printed to a schedule.
	int end_time;//see notes on start_time.
};

struct SchoolClass
{
	string courseName;
	string course_id_number;//4 digit # like in locus
	vector<MeetingTime> meeting_times;//days met for a class
	int class_credit_hours;
	bool elective, major, genEd;//is major, elective, gen_ed, as we discussed...
};

/*reference used for lines 12-28: http://www.cplusplus.com/forum/general/74240/  */
void wk (int csch, string crs, char *N) // fix this so it returns an array
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
void CID (int csch) //assigns each class a unique ID. (side note: this optional -- but it's purpose is to make scheduling easier)
{
    /*Notes: The 'char t' gives it a course type, and 'char d' which gives it a semester. The numbers themselves aren't as important, provided they
    are unique for each course. The course type gives it a priority - which is M > G > E. So if an M type class is unavailable, the program needs
    to look for a G type course that fits into the schedule, or lastly, if it is available, it looks for an E type class. So, it sorts it by type,
    then by semester, and the numbers should be unique for that specific class to assign to that semester's schedule. Basically every "S" or "F" goes
    into a temporary "S" or "F" text file. This needs to be created by a sorter function.*/
    string csmtr; //semester
    string cyr; //year
    char d, t;//char t = general requirements, elective, etc.
    int ID;
    for (int i = 0; i < csch; i++)
    {
       ID = rand();
    }
    cout << "Key: E = elective, G = general requirement, M = major/minor requirement."; //this is here for now; it'll be removed later.
    cout << "This course is a(n): ";
    cin >> t;
    cout << "Semester: (F = Fall or S = Spring) ";
    cin >> csmtr;
    if (csmtr == "F")
    {
        d = 'F';
    } else
    {
        d = 'S';
    }
    cout << "Term Year: ";
    cin >> cyr;
    ID << rand() << rand();
    cout <<"course ID: " << d << t << ID << endl;
    /* if this stays in the final version, it'll require a method so that each ID is unique. Basically the idea is that this will become a specific course's "address"
    which is then put into a table (which goes into the output file) where it needs to go on a schedule. */
}
void cmD (string crs) //Creates a schedule (by days); must fix so it also gives times.
{
 /*   string crs; //course name
    cout << "Enter course name to create schedule." << endl << "(Ex: COMP150)" << endl;
    cin >> crs; */
    int csch; //amount of meetings per week
    cout << "How many times does " << crs << " meet per week? ";
    cin >> csch;
    wk(csch, crs,"sch.txt");
    CID(csch);
}
//lines 97-100 not implemented.
void seek(char search_file, string class_to_be_searched)
{

}
void ofile(char *N) //reads the selected file
{
    ifstream x(N);
    string a;
    while(!x.eof())
    {
        getline(x,a);
        cout << a << endl;
    }
}
void MReqs (char *N, int v, string m, int tC) // writes the required courses text file
{
    ofstream x(N);
    string a, b, w;
 //   char t = M //This goes into the CID function
    int y = 1;
    int z = 0;
    int k = 1;
    x << "****************************************************************" << endl;
    x << "Requirements for: " << m << " MAJOR                " << "Total Credit Hours: " << tC << endl;
    x << "================================================================" << endl;
 do
    {
        if (a != "0")
        {
            for (int i = 1; i <= v; i++)
            {
                cout << "Required Course #" << y << ": ";
                cin >> a;
                cmD(a);
                cout << "Credit hours: ";
                cin >> z;
                x << "Required Course #" << y << ": " << a << "| | Credit(s): " << z << endl;
                cout << "NOTE: For the following Y/N questions, you must enter Y or N only.";
                cout << "\nDoes this course have co- or pre-requisites? Y/N ";
                cin >> b;
                if (b == "Y" || b == "y") // So that it doesn't repeat courses in the output file.
                {
                    cout << "Is this co- or pre-requisite also a required course for " << m << " major? Y/N " << endl;
                    cin >> b;
                    if (b == "Y" || b == "y")
                    {
                        b = "Y";
                    } else
                    {
                        b = "N";
                    }
                    b;
                }
				while(b !="N" || b != "n" && b == "Y" || b == "y")
                {
                    if (b == "Y" || b == "y")
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
                }
                y++;
                cout << "Press 0 to exit or 1 to continue. ";
                cin >> a;
                if (y > v)
                {
                    cout << "You have exceeded the number of required courses. Please press 0 to exit. ";
                    cin >> a;
                }
            }
        } else
        {
            break;
        }
    } while(a != "0");
    cout << "Do you have a minor? Y/N " << endl;
    /* Notes: This still needs to be fixed so that it does the exact same thing as the "major" portion of this function.*/
    cin >> a;
	if (a == "Y" || a == "y" || a == "N"||a == "n")//if (a == "Y" || a == "N")
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
                m = "NONE";
                tC = 0;
                a = "0";
            }
    }
    while (a != "0")
    {
            for (int i = 1; i <= v; i++)
            {
                cout << "Required Course #" << y << ": ";
                cin >> a;
                cmD(a);
                cout << "Credit hours: ";
                cin >> z;
                x << "Required Course #" << y << ": " << a << "| | Credit(s): " << z << endl;
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
                    } else
                    {
                        b = "Y";
                    }
                    b;
                }
				while(b !="N" || b != "n" && b == "Y" || b == "y")
                {
                    if (b == "Y" || b == "y")
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
                }
                y++;
                cout << "Press 0 to exit or 1 to continue. ";
                cin >> a;
                if (y > v)
                {
                    cout << "You have exceeded the number of required courses. Please press 0 to exit. ";
                    cin >> a;
                }
            }
    }

}
void courselist () //creates major/minor requirements doc
{
    /*This function creates the course requirements file.*/
    char *N = "reqs.txt"; //keep in mind that once we finish writing the entire program, this will be converted into a prompt so the user can come up with their own title.
    ofstream x;
    x.open(N);
    string maj, minr, gen, a;//no need for gen, I think...
    int creds;
    int y = 0; int z = 0; int v = 0; int m = 0; int g = 0; //m is # of courses for minor, g for gen ed's
    // z[total number of classes]

    cout << "To start program press 1. To exit press 0. For help press \"/?\". ";
    cin >> a;
    if (a == "/?")
    {
        help("help.txt");
        remove("help.txt");
        cout << "Press 1 to continue or 0 to exit. ";
        cin >> a;
    }
	if (a != "0" && a != "?")
	{
		cout << "Major: ";
		cin >> maj;
		while (z-v != m+g ){/*this is to ensure you can graduate. 
		if you cannot enter the correct # of credits to match total credits needed to graduate, 
		this code will force you to enter the right amounts, preventing any numerical error.
		z= total credits to graduate, v=major credits, m = minor credits, and g= gen eds. 
		If the user types correctly and has the correct numberical inputs, this should run once.*/
		cout << "Insert total number of credits needed to graduate. \n";
		cin >> creds;//grabs number of credits needed to graduate from console, and stores to z (next line)
		z += creds;
		cout << "How many courses required for major? \n";
		cin >> v;//stores number of courses needed for major 
		cout << "\nDo you have a minor? Enter y or Y for [Y]es, and n or N for [N]o." << endl;
		//minor code begins here...
		cin >> minr; // stores response temporarily to minor.
		while (minr != "Y" && minr != "y" && minr != "N" && minr != "n")//checks for errors.
		{
			cout << "\nDo you have a minor? Enter y or Y for yes, and n or N for [N]o." << endl;
			cin >> minr; // stores response temporarily to minor.
		}
		if (minr == "Y" || minr == "y" || minr == "N" || minr == "n")//if there is a clear answer...
		{
			cout << "Alright." << endl;
			if ((minr == "Y" || minr == "y")//and there is a minor...
			{
				cout << "Please enter the name of your minor now. " << endl;
				cin >> minr; // stores the name of the minor to minor.
			}
			if ((minr != "Y" || minr != "y")//if there is no minor...
			{
				cout << "No minor...understood. " << endl;
				minr = "";//since there is no minor, sets minor equal to nothing.
			}

		}
		cout << "\nHow many courses required for minor?\n";
		cin >> m;//stores number of courses needed for minor 
		//gen eds begin here...
		cout << "\nDo you have general education (core) classes? \nEnter y or Y for [Y]es, and n or N for [N]o." << endl;
		cin >> gen; // stores response temporarily to gen.
		while (gen != "Y" && gen != "y" && gen != "N" && gen != "n")//checks for errors.
		{
			cout << "\nDo you have general education (core) classes? \nEnter y or Y for [Y]es, and n or N for [N]o." << endl;
			cin >> gen; // stores response temporarily to gen.
		}
		if (gen == "Y" || gen == "y" || gen == "N" || gen == "n")//if there is a clear answer...
		{
			cout << "Alright." << endl;
			if ((gen == "Y" || gen == "y")//and there are gen eds...
			{
				cout << "\nHow many courses required for Gen Eds?\n";
				cin >> g;//stores number of courses needed for gen eds 
			}
			if ((gen != "Y" || gen != "y")//if there are no gen eds...
			{
				cout << "No Gen Eds...understood. " << endl;
				gen = "";
			}
		}
	}//end of while loop.
        cout << maj << "\nPlease insert required courses for your major. (ex: BIOL101)" << endl;
           if(a != "0")
            {
                MReqs(N,v,maj,z);
            }
		   /*formula as follows...
		   if (minr != "")
		   {
		   cout << minr << " Please insert required courses for your minor. (ex: BIOL101)" << endl;
           if(a != "0" && z!= 0)//either you must be able to add courses (have credits left over), or this should not run.
            {
                MinReqs(N,m,minr,z);//labeling formula for minor as MinReqs
            }
			}
			if (gen != "")
			{
			cout << " Please insert required courses for your gen-eds (core classes). (ex: BIOL101)" << endl;
           if(a != "0"&& z!= 0)
            {
                genReqs(N,g,gen,z);//labeled formula for ged-eds as genReqs. no use of Gen, really...
            }//is gen really needed in this code?
			}*/

    char *M = "sch.txt";
    ofile(M); //reads temp. schedule file
    remove(M); //deletes temp. schedule file
    system("cls"); //clears the screen so only the output file shows up on the screen.
    }
     else if(a == "0")
    {
        cout << "Goodbye." << endl;
    }
}
void RunP() //this basically runs the entire program.... leave it until the end (either keep or remove)
{
     char *N = "reqs.txt";
    courselist();
    ofile(N);
}
int main()
{
	/*initializing the 3 vecors again. 
	vector<SchoolClass> Semester_Courses; //list of courses for the semester
	vector<SchoolClass> All_Courses;//list of all classes
	vector<SchoolClass> Already_Picked_Courses; // end test will be if semester # is >8 && Already_Picked_Courses == All_Courses, then kick out of the program.*/
    RunP();
    return 0;
}