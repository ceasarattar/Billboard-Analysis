   /*  Program 4: BillBoard Analysis
    This program analyzes weekly Billboard data spanning   from 1960 - 2020.
    Author: Ceasar Attaar
    Date: March 29, 2022
    System: Visual Studio Code, macOS
*/

#include <iostream>   // general input/output for program to run
#include <fstream>    // allows inputs and outputs to occur in files
#include <cassert>    // lets use assert statement when reading in a file 
#include <cctype>     // lets you manipulate characters/strings (tolower)
#include <vector>     // for all the vectors
#include <cstring>    // provides functions for dealing with C-style strings 
#include <sstream>    // reads in files and gives access to delimiter 
#include <algorithm>  // For find(), which searches within a vector
using namespace std;  //  is used to decrease or limit the scope of any variable or function

struct Date {  // creates a struct called Date that stores int variables month, day, and year
    int month; // inititializes month as an integer
    int day;   // inititializes month as an integer
    int year;  // inititializes month as an integer
};

struct BillboardData {   // creates a struct called billboard data that stores all
    Date weekStartDate;  // the variables of the billboard data. 
    int weekPosition;    // initializes an int variable that stores the week position of the song 
    string songName;     // initializes a string variable that stores the name of the song 
    string artistName;   // initializes a string variable that stores the artist's name
    int prevWeekPosition;// initializes an int variable that stores the previous week position of the song
    int peakPosition;    // initializes an int variable that stores the peak position of the song 
    int numWeeksOnChart; // initializes an int variable that stores the number of weeks on charts
};

void welcomeMessage()   // displays the welcome message and briefly explains what the program does
{
    cout << "Program 4: BillBoard Analysis \n"
        << "CS 141, Spring 2022, UIC \n"
        << " \n"
        << "This program will analyze weekly Billboard data spanning from 1960 - 2020."
        << endl;
} // end of the welcome message

// reads in the billboard data using parameters fileName and vector billboardRecords and also has a
// reference parameter to refrence to the original variable and avoid the usage of global variables
void readFile(string fileName, vector<BillboardData>& billboardRecords) 
{
    ifstream fin;
    fin.open(fileName);        // opens the file according to the file name (fileOption == 1 || 2 || 3)
    assert(fin.fail() == false);
  
    string recordLine;        // initializes recordLine as a string 
    getline(fin, recordLine); // reads in the first line which is the header and throws it out 

    while (getline(fin, recordLine)) {  // reads in each individual line from the data
        stringstream s_stream(recordLine); 
        BillboardData songRecord;

        int col = 0;
        while (s_stream.good()) {
            string columnVariable;
            getline(s_stream, columnVariable, ','); // gets each substring seperated by a comma 

            switch (col) { // switch case that helps group the data
                case 0: {
                    // seperates each part of the date into different variables 
                    // (day, month, and year are stores as seperate variables)
                    int month = stoi(columnVariable.substr(0, columnVariable.find('/'))); // uses .find to look for a backslash
                    string temp = columnVariable.substr(columnVariable.find('/') + 1); // retuns the date excluding the month
                    int day = stoi(temp.substr(0, temp.find('/')));
                    int year = stoi(temp.substr(temp.find('/') + 1)); // returns the substring that is before year and leaves    
                    songRecord.weekStartDate = { month, day, year };  // the year variable alone to extract
                    break;
                }
                case 1: // switch cases that set each varibale to its value accordingly 
                    if (columnVariable != "") { songRecord.weekPosition = stoi(columnVariable); }
                    else { songRecord.weekPosition = -1; }
                    break;
                case 2:
                    songRecord.songName = columnVariable;
                    break;
                case 3:
                    songRecord.artistName = columnVariable;
                    break;
                case 4:
                    if (columnVariable != "") { songRecord.prevWeekPosition = stoi(columnVariable); }
                    else { songRecord.prevWeekPosition = -1; }
                    break;
                case 5:
                    if (columnVariable != "") { songRecord.peakPosition = stoi(columnVariable); }
                    else { songRecord.peakPosition = -1; }
                    break;
                case 6:
                    if (columnVariable != "") { songRecord.numWeeksOnChart = stoi(columnVariable); }
                    else { songRecord.numWeeksOnChart = -1; }
                    break;
            }
            col++; // increments col
        }
        // pushes back songRecord into the vector
        billboardRecords.push_back(songRecord);
    }
}

// function for finding the song with the most #1 occurences using multiple paramters 
void songWithMostNumberOneOccurrences(const vector<BillboardData>& data, char timeOption, int decade = -1, int year = -1) {

    // returns the #1 song in the specified time period
    vector<BillboardData> numOneSongs;
    for (int i = 0; i < data.size(); i++) { 
        if (data.at(i).weekPosition != 1 || data.at(i).peakPosition != 1) {
            continue; // checks if the song is not at #1 and ignores it
        }
        if ((timeOption == 'D') && (data.at(i).weekStartDate.year / 10 == decade / 10)) {
            numOneSongs.push_back(data.at(i)); // pushes back data at the i index 
        }
        else if ((timeOption == 'Y') && (data.at(i).weekStartDate.year == year)) {
            numOneSongs.push_back(data.at(i));
        }
    }

    // checks for the songs within the specified time frame 
    if(numOneSongs.size() == 0) {
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        return;
    }
    
    // vectors that keep track of the number of occurences for song and artist 
    vector<string> song; // stores the song name
    vector<string> artist; // stores the artist name 
    vector<int> numOneOccurrences;

    // loop that counts the number of times theres a number 1 song 
    int numOccurrences;
    for (int y = 0; y < numOneSongs.size(); y++) {
        if(find(song.begin(), song.end(), numOneSongs.at(y).songName) != song.end() &&  // gets the song name
           find(artist.begin(), artist.end(), numOneSongs.at(y).artistName) != artist.end() ) { //gets the artist name
            continue;
        }
        numOccurrences = 0;
        for (int w = 0; w < numOneSongs.size(); w++) {
            if (numOneSongs.at(y).songName == numOneSongs.at(w).songName) {
                numOccurrences++;
            }
        }
        song.push_back(numOneSongs.at(y).songName);
        artist.push_back(numOneSongs.at(y).artistName);
        numOneOccurrences.push_back(numOccurrences);
    }

    // Find the highest number of #1 occurences
    int highestCount = 0; 
    for (int m = 0; m < numOneOccurrences.size(); m++) {
        if (numOneOccurrences.at(m) >= highestCount) {
            highestCount = numOneOccurrences.at(m); // Stores into highestCount
        }
    }

    // Chekcs for more than one #1 occurence 
    vector<int> highestOccurrenceCount;
    for (int m = 0; m < numOneOccurrences.size(); m++) {
        if (numOneOccurrences.at(m) == highestCount) {
            // adds index to vector of indices of #1 occurences
            highestOccurrenceCount.push_back(m);
        }
    }
   
    // Display the information for all songs with the highest number of occurrences
    cout << "\n\nThe song(s) with the most #1 occurrences for selected time period is: \n";
    for (int x = 0; x < highestOccurrenceCount.size(); x++) {
        cout << "\tSong Title: " << song.at(highestOccurrenceCount.at(x)) << endl
             << "\tArtist: " << artist.at(highestOccurrenceCount.at(x)) << endl
             << "\t# of occurrences: " << highestCount << endl << endl;
    }

} 


// Find song with the highest number of weeks on the chart
void topSongs(const vector<BillboardData>& billboardRecords, char timeSelection, int decade = -1, int year = -1) {

    // Get songs from given timeframe
    vector<BillboardData> recordsInTime;
    for (int i = 0; i < billboardRecords.size(); i++) {
        if ((timeSelection == 'D') && (billboardRecords.at(i).weekStartDate.year / 10 == decade / 10)) {
            recordsInTime.push_back(billboardRecords.at(i));
        }
        else if ((timeSelection == 'Y') && (billboardRecords.at(i).weekStartDate.year == year)) {
            recordsInTime.push_back(billboardRecords.at(i));
        }
    }

    // Determines if there are songs found in the given timeframe
    if(recordsInTime.size() == 0) {
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        return;
    }

    // looks for song with highest number of weeks on the charts
    int maxWeeks = -1;
    int maxWeeksIndex = -1;
    for (int j = 0; j < recordsInTime.size(); j++) {
        if (recordsInTime.at(j).numWeeksOnChart > maxWeeks) {
            maxWeeksIndex = j;
            maxWeeks = recordsInTime.at(j).numWeeksOnChart;
        }
    }

    // Display information for this song and find the max number of weeks on the chart
    BillboardData topRecord = recordsInTime.at(maxWeeksIndex);
    cout << "The song with the highest number of weeks on the charts is: \n"
        << "\t" << topRecord.songName << " by " << topRecord.artistName << " with " << topRecord.numWeeksOnChart << " weeks on the chart.\n";

} 

// Find song witgh greatest weekly climb in given timefram
void greatestClimb(const vector<BillboardData>&billboardRecords, char timeSelection, int decade = -1, int year = -1){

    // Retrieve the songs within the timeframe given
    vector<BillboardData> recordsInTimeFrame;
    for (int i = 0; i < billboardRecords.size(); i++) {
        if ((timeSelection == 'D') && (billboardRecords.at(i).weekStartDate.year / 10 == decade / 10)) {
            recordsInTimeFrame.push_back(billboardRecords.at(i));
        }
        else if ((timeSelection == 'Y') && (billboardRecords.at(i).weekStartDate.year == year)) {
            recordsInTimeFrame.push_back(billboardRecords.at(i));
        }
    }

    // Check if there are songs found in the timeframe
    if(recordsInTimeFrame.size() == 0) {
        cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
        return;
    }

    int largestJump = 0;
    int range = 0;
    int previousWeekPosition =0;

    // Find record in timeframe with biggest difference in previous and current week position
    for(int x = 0; x < recordsInTimeFrame.size(); x++) {
        // Finds position of previous week
        previousWeekPosition = (recordsInTimeFrame.at(x).prevWeekPosition == -1) ? 0 : recordsInTimeFrame.at(x).prevWeekPosition;
        // Find difference between previous and current week position
        range = previousWeekPosition - recordsInTimeFrame.at(x).weekPosition;
        // Determine if this song has largest climb yet
        if(range >= largestJump){
            largestJump = range;
        }
    }

    vector<int> highestRange;
    //Check to see if there is a tie for greatest weekly jump range
    for (int i = 0; i < recordsInTimeFrame.size(); i++) {
        // Finds position of previous week
        previousWeekPosition = (recordsInTimeFrame.at(i).prevWeekPosition == -1) ? 0 : recordsInTimeFrame.at(i).prevWeekPosition;
        // Find difference between previous and current week position
        range = previousWeekPosition - recordsInTimeFrame.at(i).weekPosition;
        // Checks if song is tied for greates weekly jump
        if (range == largestJump) {
            highestRange.push_back(i);
        }
    }

    // Displays information for songs with greatest weekly climb
    cout << "\nThe song(s) with the greatest climb from previous week to current week position: \n";
    for (int x = 0; x < highestRange.size(); x++) {
        cout << "\tSong Title: " << recordsInTimeFrame.at(highestRange.at(x)).songName << endl
             << "\t Artist: " << recordsInTimeFrame.at(highestRange.at(x)).artistName << endl
             << "\t Week of: " << recordsInTimeFrame.at(highestRange.at(x)).weekStartDate.month << "/" << recordsInTimeFrame.at(highestRange.at(x)).weekStartDate.day << "/" << recordsInTimeFrame.at(highestRange.at(x)).weekStartDate.year << endl
             << "\t Previous Week Position: " << recordsInTimeFrame.at(highestRange.at(x)).prevWeekPosition << endl
             << "\t Current Week Position: " << recordsInTimeFrame.at(highestRange.at(x)).peakPosition << endl
             << "\t Difference of " << largestJump << " between previous week and current week position" << endl;
    }

} // end greatestWeeklyClimb()

// finds #1 songs with provided input text
void searchByArtist(const vector<BillboardData>& billboardRecords, string searchValue) {

    // vector holding all matching artists
    vector<BillboardData> foundArtists;

    // Convert each character  to lowercase
    for(int i=0; i<searchValue.size(); i++) {
        searchValue.at(i) = tolower(searchValue.at(i));
    }

    // search through record and saves instances of matching search words 
    for (int recordNum = 0; recordNum < billboardRecords.size(); recordNum++) {

        // diregards songs that were not #1 on the charts
        if (billboardRecords.at(recordNum).weekPosition != 1 || billboardRecords.at(recordNum).peakPosition != 1) {
            continue;
        }

        string artistName = billboardRecords.at(recordNum).artistName;

        // changes each character to lowercase
        for(int i=0; i<artistName.size(); i++) {
            artistName.at(i) = tolower(artistName.at(i));
        }

        // checks if search value is in artist name
        if (artistName.find(searchValue) != string::npos) {
            foundArtists.push_back(billboardRecords.at(recordNum));
        }
    }

    // Checks for matching artists found or not. 
    if(foundArtists.size() == 0) {
        cout << "No matching artists were found." << endl;
        return;
    }

    // Displays first 10 songs matching artist name
    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
    for (int x = 0; x < 10; x++) {
        if(x >= foundArtists.size()) {
            break;
        }
        cout << x+1 << ") Song: " << foundArtists.at(x).songName << endl
             << "    Artist: " << foundArtists.at(x).artistName << endl
             << "    Week of: " << foundArtists.at(x).weekStartDate.month << "/" << foundArtists.at(x).weekStartDate.day << "/" << foundArtists.at(x).weekStartDate.year << endl
             << "    Week Position: " << foundArtists.at(x).weekPosition << endl;
    }
   
} // end searchByArtist()

// Start of main()
int main()
{
    welcomeMessage();

    // Asks for the file in which the results will be displayed for
    int fileOption;
    string fileName;

    cout << endl
        << "Select file option:" << endl
        << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl
        << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl
        << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl
        << "Your choice --> ";
    cin >> fileOption;
    cout << endl;

    switch (fileOption) {
        case 1:
            fileName = "charts_top50_1960_1980.csv";
            break;
        case 2:
            fileName = "charts_top50_1981_2000.csv";
            break;
        case 3:
            fileName = "charts_top50_2001_2020.csv";
            break;
        default: cout << "Invalid value. Exiting Program.";
            exit(-1);
            break;
    }

    // Reads data from a file into a vector 
    vector<BillboardData> songList;
    readFile(fileName, songList);

    // Allows menu selection to continue appearing
    int menuOption = 0;
    while (true) {

        // Prompts menu selection
        cout << endl
            << "Select a menu option: \n"
            << "   1. Display overall information about the data\n"
            << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n"
            << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n"
            << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n"
            << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n"
            << "   6. Exit\n"
            << "Your choice --> ";
        cin >> menuOption;

        // exits program if option 6 is chosen
        if (menuOption == 6) {
            break;     // breaks out of loop to exit program.
        }

        if (menuOption == 1) {
          
          // finds total size/number of rows in data
          cout << "\nTotal number of rows: " << songList.size() << endl;
      
          // Number of unique songs represented in the dataset (this takes about 10-20 seconds)
          vector<string> uniqueSongs;
          for (int i = 0; i < songList.size(); i++) {
              string song = songList.at(i).songName;
              // Push song name to vector
              if (find(uniqueSongs.begin(), uniqueSongs.end(), song) == uniqueSongs.end()) {
                  uniqueSongs.push_back(song);
              }
          }
          cout << "Number of unique songs represented in the dataset: " << uniqueSongs.size() << endl;
          continue;
              }
              else if (menuOption == 2) {
                  char timeSelection = ' ';
                  int decade, year;
                  decade = year = -1;
                
                  do {
                      cout << "Enter D to select a decade or Y to select a year.\n"
                          << "Your choice --> ";
                      cin >> timeSelection;
                      timeSelection = toupper(timeSelection);
              
                      if (timeSelection == 'D') {
                          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                          cin >> decade;
                      }
                      else if (timeSelection == 'Y') {
                          cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                          cin >> year;
                      }
                      else {
                          cout << "Invalid entry. Try again." << endl;
                      }
                  } while (timeSelection != 'D' && timeSelection != 'Y');
                  songWithMostNumberOneOccurrences(songList, timeSelection, decade, year);
              }
              else if (menuOption == 3) {
                  char timeSelection = ' ';
                  int decade, year;
                  decade = year = -1;
                
                  do {
                      cout << "Enter D to select a decade or Y to select a year.\n"
                          << "Your choice --> ";
                      cin >> timeSelection;
                      timeSelection = toupper(timeSelection);
              
                      if (timeSelection == 'D') {
                          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                          cin >> decade;
                      }
                      else if (timeSelection == 'Y') {
                          cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                          cin >> year;
                      }
                      else {
                          cout << "Invalid entry. Try again." << endl;
                      }
                  } while (timeSelection != 'D' && timeSelection != 'Y');
                  topSongs(songList, timeSelection, decade, year);
              }
              else if (menuOption == 4) {
                  char timeSelection = ' ';
                  int decade, year;
                  decade = year = -1;
                
                  do {
                      cout << "Enter D to select a decade or Y to select a year.\n"
                          << "Your choice --> ";
                      cin >> timeSelection;
                      timeSelection = toupper(timeSelection);
              
                      if (timeSelection == 'D') {
                          cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                          cin >> decade;
                      }
                      else if (timeSelection == 'Y') {
                          cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                          cin >> year;
                      }
                      else {
                          cout << "Invalid entry. Try again." << endl;
                      }
                  } while (timeSelection != 'D' && timeSelection != 'Y');
                  greatestClimb(songList, timeSelection, decade, year);
              }
              else if (menuOption == 5) {
                  string searchValue;
                  cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;
                  cin.ignore();
                  getline(cin, searchValue);
                  searchByArtist(songList, searchValue);
              }else{
                  cout << "\nInvalid value.  Please re-enter a value from the menu options below.\n";
              }
    } //end while(true)
  
    return 0;
} // end main()

