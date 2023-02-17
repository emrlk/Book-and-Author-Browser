/** Assignment #3
*   Emily Louk
*   2/17/23
*****************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

///Prototypes
void readBookList(ifstream& inFile, struct book listOfBooks[], int numEntries);
void printBookList(struct book listOfBooks[], int numEntries);
void readAuthorList(ifstream& inFile, struct author listOfAuthors[], struct date listOfDates[], int numEntries);
void printAuthorList(struct author listOfAuthors[],struct date listOfDates[], int numEntries);
void printMatches(ifstream& inFileA, ifstream& inFileB,struct book listOfBooks[], struct author listOfAuthors[], struct date listOfDates[], int numBEntries, int numAEntries);
void Menu();
void displayOptions();


///Structs
struct book{

    string title;
    string author;
    int year;
    string language;
    string genre;
};

struct date{

    string month;
    string year;
};

struct author{

    string name;
    date DOB;
    string nationality;
    string notableWork;
};




int main()
{
    Menu();
    return 0;
}

/** displayOptions() displays the menu options 1-4 to the screen.
*   @return void
*****************/
void displayOptions(){

    cout << "\t" << "\t" << "\t" << "+ ====== Menu ====== +" << endl;
    cout << "\t" << "\t" << "\t" << "| 1. Print Books     |" << endl;
    cout << "\t" << "\t" << "\t" << "| 2. Print Authors   |" << endl;
    cout << "\t" << "\t" << "\t" << "| 3. Print Matches   |" << endl;
    cout << "\t" << "\t" << "\t" << "| 4. Terminate       |" << endl;
    cout << "\t" << "\t" << "\t" << "+ ================== +" << endl;
    cout << "Enter a number 1-4: ";

}
///Function Definitions
/** Menu() Displays options to the user, gets user input,
*   and calls respective functions depending on input.
*   @return void
****************/
void Menu(){

    int choice;
    displayOptions();

    while(cin >> choice){
        switch(choice){
        case 1:
            {
                ///Open input file
                ifstream file;
                file.open("Books-2.txt");

                int numEntries;
                file >> numEntries;

                ///Declare array of book structs
                book bookList[numEntries];

                ///Read and print list of books
                readBookList(file, bookList,numEntries);
                printBookList(bookList, numEntries);

                ///Reprint menu options:
                displayOptions();
                break;
            }
        case 2:
            {

                ///Open input file
                ifstream file;
                file.open("Authors-2.txt");

                int numEntries;
                file >> numEntries;

                ///Declare array of author structs and array of date structs:
                author authorList[numEntries];
                date dateList[numEntries];

                ///Read and print list
                readAuthorList(file, authorList, dateList, numEntries);
                //file.close();
                printAuthorList(authorList, dateList, numEntries);

                ///Reprint menu options:
                displayOptions();
                break;
            }
        case 3:
            {
                ///Open files and read the number of entries for each
                ifstream Afile;
                Afile.open("Authors-2.txt");

                int numAEntries;
                Afile >> numAEntries;

                 ifstream Bfile;
                Bfile.open("Books-2.txt");

                int numBEntries;
                Bfile >> numBEntries;

                ///Declare arrays of author, book, and date structs
                author authorList[numAEntries];
                date dateList[numAEntries];
                book bookList[numBEntries];

                ///search for matches
                printMatches(Afile, Bfile, bookList, authorList, dateList, numBEntries, numAEntries);

                ///Reprint menu
                displayOptions();
                break;
            }
        case 4:
            cout << "Terminating..." << endl;
            exit(1);
            break;

        default:
            cout << "Invalid input. Please enter a number 1-4:" << endl;
            break;
        }
    }
}


/** readBookList() reads the entries from the book file, removes any
*   underscores from the data, and assigns the data to the members
*   of each book struct in the array.
*   @return void
******************/
void readBookList(ifstream& inFile, struct book listOfBooks[], int numEntries){

    string title;
    string author;

    ///Read file data into book structs
    for(int i = 0; i < numEntries; i++){

        ///assign title and author data to strings for manip
        inFile >> title;
        inFile >> author;

        ///Assign remaining data directly to struct members
        inFile >> listOfBooks[i].year;
        inFile >> listOfBooks[i].language;
        inFile >> listOfBooks[i].genre;

        ///replace underscores from author and title strings with spaces
        replace(title.begin(), title.end(), '_', ' ');
        replace(author.begin(), author.end(), '_', ' ');

        ///assign strings to struct variables
        listOfBooks[i].title = title;
        listOfBooks[i].author = author;
    }

    inFile.close();
}


/** printBookList() outputs the array of structs, displaying each
*   book's data.
*   @return void
****************/
void printBookList(struct book listOfBooks[], int numEntries){

    ///Print Table Header
    cout << "============================ Books ====================================" << endl;
    cout << endl;
    cout << left << setw(40) << setfill(' ') << "Title";
    cout << setw(20) << setfill(' ') << "Author";
    cout << setw(20) << setfill(' ') << "Release Year";
    cout << setw(15) << setfill(' ') << "Language";
    cout << setw(30) << setfill(' ') << "Genre" << endl << endl;

    for(int i = 1; i < numEntries; i++){

        cout << left << setw(40) << listOfBooks[i].title;
        cout << left << setw(20) << listOfBooks[i].author;
        cout << "\t" << setw(16) << listOfBooks[i].year;
        cout << left << setw(16) << listOfBooks[i].language;
        cout << left << setw(30) << listOfBooks[i].genre;
        cout << endl;
    }
    cout << endl;
}


/** readAuthorList() reads the entries from the authors file, removes any
*   underscores from the data, and assigns the data to the members
*   of each author struct in the array.
*   @return void
******************/
void readAuthorList(ifstream& inFile, struct author listOfAuthors[],struct date listOfDates[], int numEntries){


    ///Read file data into author structs
    for(int i = 0; i < numEntries; i++){

        string name;
        string DOBstring;
        string notableWork;

        ///assign the following data to strings for string manip:
        inFile >> name;
        inFile >> DOBstring;
        inFile >> notableWork;

        ///Splits the DOB string into two substrings (month and year)
        ///If month is a single digit, remove the "0"
        if(DOBstring.substr(0,1) == "0")
            listOfDates[i].month = DOBstring.substr(1, 2);
        else
            listOfDates[i].month = DOBstring.substr(0, 3);

        listOfDates[i].year = DOBstring.substr(6, 10);

        ///replace underscores from name and notableWork with spaces
        replace(name.begin(), name.end(), '_', ' ');
        replace(notableWork.begin(), notableWork.end(), '_', ' ');

        ///assign strings to struct variables
        listOfAuthors[i].name = name;
        listOfAuthors[i].notableWork = notableWork;
    }

    inFile.close();
}


/** printBookList() outputs the array of structs, displaying each
*   author's data.
*   @return void
****************/
void printAuthorList(struct author listOfAuthors[], struct date listOfDates[], int numEntries){

    ///Print Table Header
    cout << "============================ Authors ====================================" << endl;
    cout << endl;
    cout << left << setw(30) << setfill(' ') << "Name";
    cout << setw(15) << setfill(' ') << "DOB";
    cout << setw(20) << setfill(' ') << "Notable Work" << endl << endl;

    for(int i = 0; i < numEntries; i++){

        cout << left << setw(30) << listOfAuthors[i].name;
        cout << left << setw(15) << listOfDates[i].month + listOfDates[i].year;
        cout << left<< setw(20) << listOfAuthors[i].notableWork;
        cout << endl;
    }

    cout << endl;
}


/** printMatches() reads both text files, creates arrays of structs,
*   and searches the book and author arrays for matching names.
*   @return void
***************/
void printMatches(ifstream& inFileA,ifstream& inFileB, struct book listOfBooks[], struct author listOfAuthors[], struct date listOfDates[], int numBEntries, int numAEntries){

    readBookList(inFileB, listOfBooks, numBEntries);
    readAuthorList(inFileA, listOfAuthors, listOfDates, numAEntries);

    ///Print header
    cout << "========================== Authors Matched ===========================" << endl;
    cout << endl;
    cout << left << setw(30) << "Name";
    cout << left<< setw(20) << "Nationality";
    cout << left<< setw(20) << "Book" << endl;
    cout << endl;

    ///For each book array element, iterate through the author array and print matches
    for(int i = 0; i < numBEntries; i++){
        for(int j = 0; j < numAEntries; j++){
            if(listOfBooks[i].author == listOfAuthors[j].name){
                cout << left << setw(30) << listOfAuthors[j].name;
                cout << left<< setw(20) << listOfBooks[i].language;
                cout << left<< setw(20) << listOfAuthors[j].notableWork << endl;
            }
        }
    }
    cout << endl;
}
