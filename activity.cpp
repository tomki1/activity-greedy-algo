/*********************************
 * name: Kimberly Tom
 * CS 325
 * Homework 4 - activity.cpp reads input from act.txt and uses a greedy algorithm to select the last activity to start
 * that is already compatible with all previously selected activities to determine the most number of activities
 * that can be completed.
 * 2/2/19
*********************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

    ifstream inputFile;

    inputFile.open("act.txt");

    if (inputFile.is_open()) {
        cout << "Opened act.txt successfully." << endl;
    } else {
        cout << "Error. Unable to open the act.txt file." << endl;
        return 1;
    }

    // start set count at 1
    int setCount = 1;

    // read until we are at the end of the file
    while (!inputFile.eof()) {
        int activityCount = 0;      // number of activities in the set
        int activityID = 0;         // activity number
        int activityStart = 0;      // activity start time
        int activityEnd = 0;        // activity end time

        // read the line and store the number of activities in the set
        inputFile >> activityCount;

        // create a vector pair, with the first pair being an integer, and the second element being a pair of integers
        vector<pair<int, pair<int, int> > > activityVector;

        // loop for the number of activities in the set
        for (int count = 0; count < activityCount; count++) {
            //  read the activity number
            inputFile >> activityID;
            // read the start time
            inputFile >> activityStart;
            // read the end time
            inputFile >> activityEnd;

            // push the elements where start time is the first element of the vector pair
            // end time is the first element in the second element of the vector pair
            // activity number is the second element in the second element of the vector pair
            activityVector.push_back(make_pair(activityStart, make_pair(activityEnd, activityID)));
        }

        // sort activityVector by the activity start time in ascending order
        sort(activityVector.begin(), activityVector.end());

        // create scheduleVector to hold the activities that will be in the optimal solution
        // with help from https://stackoverflow.com/questions/38222874/how-to-access-pair-elements-nested-inside-pair-in-a-vector-in-stl
        // "first" and "second.first" and "second.second" are used to access the elements of the pairs
        vector<int> scheduleVector;
        int i = activityCount - 1;
        // push the activity with the latest start time into our schedule as it is part of the optimal solution
        scheduleVector.push_back(activityVector[i].second.second);

        // modification of https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
        // loop starting from the end of the vector to the beginning
        for (int m = activityCount - 1; m >= 0; m--) {
            // if the finish time of the next activity is less than or equal to the start time of the
            // most recently added activity in our optimal solution, add the activity to scheduleVector
            if (activityVector[m].second.first <= activityVector[i].first) {
                scheduleVector.push_back(activityVector[m].second.second);
                i = m;
            }
        }

        cout << "Set " << setCount << endl;
        cout << "Number of activities selected = " << scheduleVector.size() << endl;
        cout << "Activities: ";
        for (int i = scheduleVector.size() - 1; i >= 0; i--) {
            cout << scheduleVector[i] << " ";
        }

        cout << endl;
        cout << endl;

        setCount = setCount + 1;
    }

    inputFile.close();

    return 0;
}