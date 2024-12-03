//
// Created by Giancarlo Vidal on 12/2/24.
//
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Node.h"
#include "MaxHeap.h"
#include "SplayTree.h"

using namespace std;

//Miguel Goizueta's Contributions
/*//trying to make sure the directory is working
void printWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Current working directory: " << cwd << endl;
    } else {
        cerr << "Error getting current working directory." << endl;
    }
}*/


// Function to read the CSV file and populate the MaxHeap and SplayTree
void readCSV(const string& filePath, MaxHeap& maxHeap, SplayTree& splayTree, bool choice, int numPool) {
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return;
    }

    // Skip the header
    getline(file, line);

    while (getline(file, line) && numPool > 0) {
        stringstream ss(line);
        string title, genre, director, company, ratingStr;
        double rating;

        // Parse each column
        // Parse the title, handling possible commas inside quotes
        char ch;
        while (ss.get(ch)) {
            if (ch == '"') {
                // Skip the starting quote
                while (ss.get(ch) && ch != '"') {
                    title += ch;  // Add characters inside quotes to title
                }
            } else if (ch == ',') {
                break;  // End of title
            } else {
                title += ch;  // Add non-comma characters to title
            }
        }

        getline(ss, genre, ',');
        getline(ss, ratingStr, ',');
        getline(ss, director, ',');
        getline(ss, company, ',');

        // Skip rows with empty or invalid ratings
        if (ratingStr.empty() || ratingStr.find_first_not_of(" \t\n\r") == string::npos) {
            // If the rating is empty or consists only of spaces, skip this line
            continue;
        }

        // Convert rating to double
        try {
            rating = stod(ratingStr);
        } catch (const invalid_argument& e) {
            cerr << "Invalid rating for show: " << title << " rating:" << ratingStr << " genre: "<< genre << endl;
            continue;
        }

        // Create a new Node
        Node node(title, rating, genre, director);
        //making sure we read the file properly
        //cout << node.title << " " << node.genre << " " << node.rating << " " << node.director << endl;

        // Since the dataset has 150,000 entries we'll let
        // the user decide the size of the pool 10000 to 150000

        maxHeap.insert(node);
        splayTree.insert(node);
        numPool--;

    }
    file.close();
    cout << "File successfully loaded into MaxHeap or SplayTree.\n";
}


int main() {
    MaxHeap maxHeap;
    SplayTree splayTree;

    //printWorkingDirectory();

    cout << "Welcome to The Bingeinator!" << std::endl;

    cout << "Before we begin, what size pool of shows would you like to pull from?\n10000, 50,000, 100,000, or 150,000?\nEnter as an integer:\n";
    string input;
    cin >> input; // Get a single character input

    if (input == "10000" || input == "50000" || input == "100000" || input == "150000") {
        cout << "You chose .\n";
        readCSV("src/tvs.csv", maxHeap, splayTree, true, stoi(input));
    } else {
        cout << "Invalid input.\n";
        cout << "Make sure to enter one of the four numbers.\n";
    }
    return 0;
}