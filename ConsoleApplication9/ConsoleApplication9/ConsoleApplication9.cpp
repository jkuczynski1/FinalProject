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
string its (int a) //some compilers don't understand "to_string" ... so a workaround that is this.
{
    stringstream b;
    b << a;
    return b.str();
}
string cts (char a)
{
    stringstream b;
    b << a;
    return b.str();
}
int CSum (int z) //adds up total credits
{
///WRITE THIS ASAP!!! ///
    return 0;
}
string CID (int csch, char t) //assigns each class a unique ID. (side note: this optional -- but it's purpose is to make scheduling easier)
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
    } else
    {
        d = 'S';
    }
    cout << "For the following question, enter the year the course will be taken." << endl;
    cout << "Freshmen Year = 1  |*| Junior Year = 3 \nSophomore Year = 2 |*| Senior Year = 4" << endl;
    cout << "Year: ";
    cin >> cyr;
    cyr = "Y000" + cyr;
    ID << rand() << rand();
    IDstring = cts(d) + cts(t) + IDconvertString + cyr;
    /* if this stays in the final version, it'll require a method so that each ID is unique. Basically the idea is that this will become a specific course's "address"
    which is then put into a table (which goes into the output file) where it needs to go on a schedule. */
return IDstring;
}
string cmD (string crs, char t) //Creates a schedule (by days); must fix so it also gives times.
{
 /*   string crs; //course name
    cout << "Enter course name to create schedule." << endl << "(Ex: COMP150)" << endl;
    cin >> crs; */
    int csch; //amount of meetings per week
    cout << "\nHow many times does " << crs << " meet per week? ";
    cin >> csch;
    wk(csch, crs,"sch.txt");
    return CID(csch, t);
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
string ovrwt(char *N, char *M, char *V) //merges two documents into one.
{
    ifstream y(N); //file #1
    ifstream z(M); //file #2
    ofstream x(V); //The file N & M are merged into
    ifstream r(V); // so it can read that file.
    string a, b, c, d;
    while(!y.eof())
    {
        getline(y,a);
        a += "\n";
        c += a;
    }
    while (!z.eof())
    {
        getline(z,b);
        b += "\n";
        d += b;
    }
    a = c + d;
    x << a << endl; //merges the contents of N & M into file V
    a.clear();
    while (!r.eof())
    {
        getline(r,b);
        b += "\n";
        a += b;
    }
    return a; //returns the string containing the contents of both documents.
}
bool seek (char *N, string a)
/* This basically searches for string a in the text file char *N. */
{
    ifstream x(N);
    string b;
    size_t c; //if c == npos it means not found
    while(!x.eof())
    {
        getline(x,b);
        c = b.find(a);
        if (c != string::npos)
        {
            break; //so that the loop ends if the search term is found
        }
    }
    if(c != string::npos)
    {
        return true;  //the search term was found in the file
    } else
    {
        return false; //the search term doesn't exist in file (so not found)
    }
}
bool RTF (string a, int k, int y, int z) /*Confirms the course data is correct.*/
// course name = string a, co-/prerequisite counter = k, course counter = y, course credits = z
{
    char s = ' '; //switch key
    string b;
    if (b != "Y")
    {
        cout << "Credit hours: ";
        cin >> z;
        cout << "Required Course #" << y << "." << k << " is: " << a << " with " << its(z) << " credits?" << endl;
    }
    cout << "Correct? Y/N ";
    s = _getch();
    cout << endl;
    switch(s)
    {
        case 78: //ASCII N
        {
            return false;
        }
        case 89: // ASCII Y
        {
            return true;
        }
    }
}
string wrts(char t, string a, int k, int z, int y) //creates the co/prerequisite string
/*course type (char t), course name (string a), (co/prerequisite counter (int k), credit hours (int z), number of courses*/
{
    return "-requisite #" + its(k) + ": " + a + "|*| ";
}
string Rwrt(char *N, char t, string a, int k, int y) //The (Co/Pre)requisite prompt function
/*This function acquires the user input for the co- and/or prerequisites. It uses t (the course type), a (the course name), k (the
 (Co/Pre)requisite counter), and y (the course counter). It returns a string that is acquired by Rsk().*/
{
    char s = ' '; //switch key
    string b, q, w; string c = a;
    int z; int r;
    cout << "How many co- and/or prerequisites does " << a << " have? ";
    cin >> r;
    while (s != 78 && k <= r)
    {
        if (s = 89) // if s == Y
        {
            if (w != "Y")
            {
                cout << "Required Course #" << y << "." << k << ": ";
                cin >> a;
                if(RTF(a,k,y,z)!=true && s != 78)
                {
                    cout << "Required Course #" << y << "." << k << ": ";
                    cin >> a;
                }
                b += wrts(t,a,k,z,y);
            } else
            {
                b += wrts(t,a,k,z,y);
                k++;
                cout << "counter k error @212\n";
            }
        } else if (s == 78)
        {
            b += wrts(t,a,k,z,y);
        }
        cout << "Are there other co- or pre-requisites for " << c << "? Y/N " << endl;
        s = _getch();
        if (s == 89)
        {
            k++;
            cout << "counter k error @223\n";
        }
        cout << "Re-enter " << a << " credit hour(s): "; //so the string picks it up & to confirm the credit hours before writing it to file.
        cin >> z;
        b += "Credit hours: " + its(z) + " |*| ";
        if (seek(N,a)!=true) //if the course isn't already in the file, then it'll provide it with a unique ID.
        {
            b += " CID: " + cmD(a,t);
        }
        if (k > r)
        {
            cout << "You have exceed the number of co- and/or prerequisites you can add. " << endl;
            s = 27;
            return b;
        }
        if (s == 27)
        {
            k = 0;
            return b;
        }
    }
    return b;
}
string RSk(char *N, char t, string a, int y) // Sets up Rwrt() in a way it can be used.
{
/*Rsk() uses seek() to check if the given course (string a) is found in the file (char *N) and sets up the (Co/Pre)-requisite counter k.*/
    char s = ' '; //switch key
    string b, w; string c = a; string v;
//    bool q = seek(N,a);  //searches the course name (string a) in the text file (char *N) and returns true or false
    int k = 1; int z = 0; int i = 0;
    cout << "\nPress ENTER if there are co- or prerequisites for " << c <<". Or press ESC to exit." << endl;
    s = _getch();
    switch (s)
    {
        case 13:
        {
            if (seek(N,a) != false)
            {
                i += y;
                cout << a << " found in file." << endl;
                b += Rwrt(N,t,a,k,i);
                v += b;
                i++;
                break;
            } else
            {
                v += Rwrt(N,t,a,k,y);
                k++;
                cout << "counter k error @268\n";
                break;
            }
        }
        case 27:
        {
            return v;
        }
    }
}
string PReqs(char*N, char t, string a, int y)
//The main (Co/Pre)requisite function; *N = is title of file, a = course name, t = course type
/*This sets up the loop to write/prompt the user for the (Co/Pre)requisites. It replaces the lines 111-136 of an earlier draft of MReqs().
It uses Rsk() to provide the string MReqs () and GEReqs() write into the files they create. */
{
    string b, c, d, w;
    char s = ' '; //switch keys
 //   cout << "\nIf this is a co-requisite for " << a <<" press C.\n";
 //   cout << "\nIf this is a prerequisite for " << a <<" press P. Or press ESC to abort.";
    while (s != 27) //start loop
    {
        switch(s)
        {
        case 67: // ASCII for C
            {
                w = cts(s);
                if(w == "C") //this might be redundant.... consider removing?
                {
                    cout << endl << "Please enter co-requisite course name. ";
                    cin >> a;
                    b = "\t-->Co";
                    c = RSk(N,t,a,y);
                    d = b + c + "\n";
                }
                cout << c << endl;
            } //end case 89
        case 80: //ASCII for P
            {
                w = cts(s);
                if (w == "P")
                {
                    cout << endl << "Please enter prerequisite course name. ";
                    cin >> a;
                    b = "\t-->Pre";
                    c = RSk(N,t,a,y);
                    d = b + c + "\n";
                    return d;
                }
            } //end case 78
        case 27: //ASCII for ESC
            {                                       ///MUST FIND & FIX ERRORS NOT ALLOWING IT TO WRITE TO FILE CORRECTLY
                system("cls");
                return d; //ends loop
            }
        default:
            {
                cout << endl << "If the course you are entering is a co-requisite, press C.";
                cout << "\nIf it's a prerequisite, press P." << endl;
                s = _getch();
            }
        }
    }
}
void MReqs (char *N, int v, string m, int tC) // writes the required courses text file
{
    ofstream x(N);
    string a, b, w;
    char s = ' ', s2; //switch keys
    char t = 'M';
    int y = 1; int c = 0; //c adds up credits
    int z = 0; int k = 0;
    int n = 1; //courses entered counter
    x << "****************************************************************" << endl;
    x << "Requirements for: " << m << " MAJOR                " << "Total Credit Hours: " << tC << endl;
    x << "================================================================" << endl;
    cout << m << " Requirements. Please enter all required courses as prompted. (ex: BIOL101)\nPress ENTER to continue or ESC to exit." << endl;
    s = _getch();

    for (int i = 1; i <= v; i++) // where v = total # of courses required by major
    {
        while (s != 27 && n <= v)
        {
            switch(s)
            {
                case 13: // ENTER KEY
                {
                    //for(int i = 1; i <= v; i++)
                    //{
                    cout << "Required Course #" << y << ": ";
                    cin >> a;
                    if (RTF(a,k,y,z)!=true && s!=27)/*Utilizes RTF() to determine if the required course is correct.*/
                        //a = course name, k = co/prerequisite counter, y = course counter, z = course credit
                    {
                        cout << "Required Course #" << y << ": ";
                        cin >> a;
                        cout << "Credit Hours: ";
                        cin >> z;
                    } else
                    {
                        cout << "Re-enter " << a << " credit hour(s): "; //so the string picks it up & to confirm the credit hours before writing it to file.
                        cin >> z;
                       w += "Required Course # " + its(y) + ":" + a + " |*| Credit Hours: " + its(z) + "|*| ";
                       if(seek(N,a) != true)
                       {
                           w += "CID: " + cmD(a,t) + "\n";
                       }
                    }
                    cout << "The following Y/N questions regard " << a << "'s co- and/or prerequisites.\nPlease enter only Y or N." << endl;
                    cout << "To continue press ENTER to continue or ESC to exit. " << endl;
                    if (_getch()!= 27 && n <= v)
                    {
                        k++;
                        n++;
                        w += PReqs(N,t,a,y) + "\n";
                    } else {k = 0;}
                    y++;
                    n++;
                }
                if (n > v)
                {
                    cout << "\nYou have exceeded number of required courses. Press ESC to exit. " << endl;
                    s = _getch();

                }
                    //}
                case 27: // ESC KEY
                {
                    cout << w << endl;
                    x << w << "\n"; /// convert to write once issue is fixed
                    break;
                }
            }
        }
    }
    cout << "\nThe following questions regard your minor. ";
    cout << "Do you have a minor? Y/N ";
    s2 = _getch();
    switch(s2)
    {
        case 89:
        {
            while(s2 !=27 && s2 != 78)
            {
                cout << "Minor: ";
                cin >> m;
                cout << "Total credit hours required for " << m << ": ";
                cin >> tC;
                cout << "NOTE: keep in mind, the prerequisites not included in your previous requirements count!" << endl;
                cout << "How many courses are required for minor? ";
                cin >> v;
                a = "";
                y = 1;
                x << endl << "================================================================" << endl;
                x << "Requirements for: " << m << " MINOR                " << "Total Credit Hours: " << tC << endl;
                x << "****************************************************************" << endl;
                for (int i = 1; i <= v; i++)
                {
                    cout << "Required Course #" << y << ": ";
                    cin >> a;
                    if (RTF(a,k,y,z)!=true && s!=27)/*Utilizes RTF() to determine if the required course is correct.*/
                        //a = course name, k = co/prerequisite counter, y = course counter, z = course credit
                    {
                        cout << "Required Course #" << y << ": ";
                        cin >> a;
                        cout << "Credit Hours: ";
                        cin >> z;
                    } else
                    {
                        cout << "Re-enter " << a << " credit hour(s): "; //so the string picks it up & to confirm the credit hours before writing it to file.
                        cin >> z;
                       w += "Required Course # " + its(y) + ":" + a + " |*| Credit Hours: " + its(z) + "|*| ";
                       if(seek(N,a) != true)
                       {
                           w += "CID: " + cmD(a,t) + "\n";
                       }
                    }
                    cout << "The following Y/N questions regard " << a << "'s co- and/or prerequisites.\nPlease enter only Y or N." << endl;
                    cout << "To continue press ENTER to continue or ESC to exit. " << endl;
            /// THE CO/PREREQUISITE LOOP STARTS
                    if (_getch()!= 27 && n <= v)
                    {
                        k++;
                        n++;
                        w += PReqs(N,t,a,y) + "\n"; //NOTES: FIND SOURCE OF ERROR & FIX ASAP
                    } else {k = 0;}
                    y++;
                    n++;
                    }
                    if(n > v)
                    {
                        cout << "\nYou have exceeded number of required courses. Press ESC to exit. " << endl;
                        return;
                    }
                }
            }
        case 78:
        {
            cout << endl << w << endl; /// convert to write once issue is fixed
            x << endl << w << endl;
            return;
        }
        default:
        {
            if(s2 !=89 && s2 !=78)
            {
                cout << "You may answer by press Y or N only.\nOr to exit, press ESC.";
                s2 = _getch();
            }
        }
    }
}
void GEReqs(char *N, int v, int tC)
/*The goal of this function is to set up the general ed and/or elective requirements. It must add its contents to the file created by MReqs to work properly.*/
{
    ofstream x(N);
    string a, b, w;
    char s = ' '; //switch key
    char t = 'G';
    int y = 1;
    int z = 0;
    int k = 0;
    int r = 1; //total course counter
//    int j = 0;
    x << "****************************************************************" << endl;
    x << "General Requirements " << "                      " << "Total Credit Hours: " << tC << endl;
    x << "================================================================" << endl;
    cout << "Please enter all required courses as prompted. (ex: BIOL101)\nPress ENTER to continue or ESC to exit." << endl;
    s = _getch();
    for (int i = 1; i <= v; i++)
    {
        while (s != 27 && r <= v)
        {
            switch(s)
            {
                case 13: // ENTER KEY
                {
                    for(int i = 1; i <= v; i++)
                    {
                        cout << "Required Course #" << y << ": ";
                        cin >> a;
                        if (RTF(a,k,y,z)!=true && s!=27)/*Utilizes RTF() to determine if the required course is correct.*/
                            //a = course name, k = co/prerequisite counter, y = course counter, z = course credit
                        {
                            cout << "Required Course #" << y << ": ";
                            cin >> a;
                            cout << "Credit Hours: ";
                            cin >> z;
                        } else
                        {
                            cout << "Re-enter " << a << " credit hour(s): "; //so the string picks it up & to confirm the credit hours before writing it to file.
                            cin >> z;
                            w += "Required Course # " + its(y) + ":" + a + " |*| Credit Hours: " + its(z) + "|*| ";
                            if(seek(N,a) != true)
                            {
                                w += "CID: " + cmD(a,t) + "\n";
                            }
                        }
                        cout << "The following Y/N questions regard " << a << "'s co- and/or prerequisites.\nPlease enter only Y or N." << endl;
                        cout << "To continue press ENTER to continue or ESC to exit. " << endl;
                        if (_getch()!= 27 && r <= v)
                        {
                            k++;
                            r++;
                            w += PReqs(N,t,a,y) + "\n";
                        } else {k = 0;}
                        y++;
                        r++;
                    }
                    if (r > v)
                    {
                        cout << "\nYou have exceeded number of required courses. Press ESC to exit. " << endl;
                        s = _getch();
                    }
                }
                case 27: // ESC KEY
                {
                    cout << endl << w << endl;
                    x << endl << w; /// STILL HAS ISSUES!!!
                    return;
                }
            }
        }
    }
    return;
}
void courselist () //creates major/minor requirements doc
{
    /*This function creates the course requirements file.*/
    char *N = "reqs.txt"; //keep in mind that once we finish writing the entire program, this will be converted into a prompt so the user can come up with their own title.
    ofstream x;
    x.open(N);
    string maj, minr, gen, a;
    int creds;
    int y = 0; int z = 0; int v = 0;
    char s = ' '; char s2 = ' ';
    cout << "You will be asked a series of questions regarding your academic requirements.\n Please omit all spaces in your replies.\n" << endl;
    cout << "If the program asks a Y/N question, please enter Y or N only. " << endl;
    s = 13;
    while(s != 27)
    {
        switch(s)
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
                system("Pause"); // to break apart that really long paragraph......
                cout << "What is your major? ";
                cin >> maj;
                cout << "NOTE: keep in mind, the co/prerequisite courses not included in your requirements count!" << endl;
                cout << "Enter total number of credits needed for " << maj << ". ";
                cin >> creds;
                z += creds;
                cout << "How many total courses required for " << maj << " major? ";
                cin >> v;
                MReqs(N,v,maj,z);
                cout << "\nIf you would like to enter your general ed requirements, press ENTER. To exit, press ESC. " << endl;
                s2 = _getch();
                switch(s2)
                {
                    case 13:
                    {
                        cout << "\nThe following questions relate your general ed requirements only. " << endl;
                        gen = "General Requirements";
                        cout << "Enter the total credit hours for your " << gen << ": ";
                        cin >> creds;
                        z = creds;
                        cout << "How many total courses required for " << gen <<"? ";
                        cin >> v;
                        GEReqs("gereq.txt",v,z);
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
     char s = ' '; string b;
     cout << "To start program press ENTER, to exit press ESC. For help, press ?. " << endl;
     s = _getch();
     while (s!=27)
        {
         switch(s) //this is using the ascii char code
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
                    char *V = "tmp.txt";
                    ofile(M); //reads temp. schedule file
                    x << ovrwt(N,P,V) << endl; //writes the final document
                    remove(V); //deletes temp. merger file
                    remove(M); //deletes temp. schedule file
                    remove(P); //deletes general req. list file
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
					 s = _getch();
                 }
         }
     }
}

int main()
{
          RunP();
//    ofile(V);z
return 0;
}
