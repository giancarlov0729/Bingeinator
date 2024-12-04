//
// Created by Giancarlo Vidal on 12/2/24.
//
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cctype>
#include <chrono>
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

//just so we can avoid issues with capitalization
// Convert a string to lowercase
string toLowerCase(const string& str) {
    string result;
    result.reserve(str.size());
    for (char ch : str) {
        result += tolower(static_cast<unsigned char>(ch));
    }
    return result;
}

// Function to read the CSV file and populate the MaxHeap and SplayTree
void readCSV(const string& filePath, vector<Node>& data) {
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return;
    }

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
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

        //Insert node into the data vector
        data.push_back(node);

    }
    file.close();
    cout << "File successfully loaded.\n";
}

// Function to get top 20 recommendations from the max heap based on genre or director
void recommendFromMaxHeap(vector<Node> &data, const string& userGenre, const string& userDirector) {
    vector<Node> genreList;     // List of shows with the same genre
    vector<Node> directorList; // List of shows with the same director

    MaxHeap maxHeap;

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    for (const Node& show : data) {
        maxHeap.insert(show);
    }

    while (!maxHeap.isEmpty() && (genreList.size() < 20 || directorList.size() < 20)) {
        Node topShow = maxHeap.extractMax();


        // Check for same genre or contains the genre
        if (genreList.size() < 20 && toLowerCase(topShow.genre).find(toLowerCase(userGenre)) != string::npos ) {
            genreList.push_back(topShow);
        }

        // Check for same director
        if (directorList.size() < 20 && toLowerCase(topShow.director) == toLowerCase(userDirector)) {
            directorList.push_back(topShow);
        }
    }

    // Record end time
    auto end = chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\n\nMaxHeap completed in " << duration.count() << " milliseconds.\n";

    // Display recommendations
    cout << "\nTop 20 Shows with the Same Genre (" << userGenre << "):" << endl;
    for (const Node& show : genreList) {
        cout << show.title << " (" << show.rating << ")" << endl;
    }

    cout << "\nTop 20 Shows with the Same Director (" << userDirector << "):" << endl;
    for (const Node& show : directorList) {
        cout << show.title << " (" << show.rating << ")" << endl;
    }
}
// QuickSort Partition Function to sort by rating
int partition(vector<Node>& data, int low, int high) {
    float pivot = data[high].rating;
    int i = (low - 1);  // index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (data[j].rating > pivot) {  // If current element is greater than or equal to pivot
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

// QuickSort Function to sort by rating
void quickSort(vector<Node>& data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);  // Partition index
        quickSort(data, low, pi - 1);  // Recursively sort the left part
        quickSort(data, pi + 1, high); // Recursively sort the right part
    }
}
void reccomendFromQuickSort(vector<Node>&data, const string& userGenre, const string& userDirector) {
    vector<Node> genreList;     // List of shows with the same genre
    vector<Node> directorList; // List of shows with the same director

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    // Sort the data using QuickSort based on rating
    quickSort(data, 0, data.size() - 1);

    // Extract top 20 shows for genre and director
    for (const Node& show : data) {
        // Check for same genre
        if (genreList.size() < 20 && toLowerCase(show.genre) == toLowerCase(userGenre)) {
            genreList.push_back(show);
        }

        // Check for same director
        if (directorList.size() < 20 && toLowerCase(show.director) == toLowerCase(userDirector)) {
            directorList.push_back(show);
        }

        // Stop early if both lists have 20 shows
        if (genreList.size() >= 20 && directorList.size() >= 20) {
            break;
        }
    }

    // Record end time
    auto end = chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "\n\nQuickSort completed in " << duration.count() << " milliseconds.\n";

    // Display recommendations
    cout << "\nTop 20 Shows with the Same Genre (" << userGenre << "):" << endl;
    for (const Node& show : genreList) {
        cout << show.title << " (" << show.rating << ")" << endl;
    }

    cout << "\nTop 20 Shows with the Same Creator (" << userDirector << "):" << endl;
    for (const Node& show : directorList) {
        cout << show.title << " (" << show.rating << ")" << endl;
    }
}

int main() {
    vector<Node> data;

    //printWorkingDirectory();

    cout << "Welcome to The Bingeinator!" << std::endl;

    cout << "Before we begin, do you want to use a Max Heap (m) or a Quicksort (Q)? \n";
    string input;
    getline(cin, input); // Get a single character input

    bool whichAlgo = true;
    if (input == "m" || input == "M") {
        cout << "You chose Max Heap.\n";
        readCSV("tvs.csv", data);
    } else if (input == "q" || input == "Q") {
        cout << "You chose Quicksort.\n";
        readCSV("tvs.csv", data);
        whichAlgo = false;
    } else {
        cout << "Invalid input.\n";
    }

    cout << "Now that we everything is set up, let's help you find your next Binge!" << endl;
    cout << "What show did you just recently finish?" << "\nType in the full name of the show here: " << endl;
    string userShow;
    getline(cin, userShow);

    cout << "\"" << userShow << "\"" << " is a great show!" << endl;
    cout << "What's the first and last name of the creator?\nInput here: ";
    string userCreator;
    getline(cin, userCreator);

    cout << "What's the genre of the show?\nInput here: ";
    string userGenre;
    getline(cin, userGenre);

    if(whichAlgo){
        recommendFromMaxHeap(data, userGenre, userCreator);
    } else{
        reccomendFromQuickSort(data, userGenre, userCreator);
    }


    return 0;
}