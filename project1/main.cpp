/*
 * Peter Nguyen
 * CSCI 371 - Project 1
 * Due: Sept. 27, 2017
 * Compile flags: -std=c++11
 */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

const function<int(int)> ADD_100 = [](int i) { return i + 100; };
const function<int(int)> ADD_80 = [](int i) { return i + 80; };
const function<int(int)> ADD_50 = [](int i) { return i + 50; };
const function<int(int)> ADD_30 = [](int i) { return i + 30; };
const function<int(int)> ADD_10 = [](int i) { return i + 10; };
const function<int(int)> ADD_8 = [](int i) { return i + 8; };
const function<int(int)> ADD_5 = [](int i) { return i + 5; };
const function<int(int)> ADD_3 = [](int i) { return i + 3; };
const function<int(int)> ADD_1 = [](int i) { return i + 1; };

const map<
    int,
    map<
        char,
        pair<int, const function<int(int)> *>
    >
> STATE_TABLE = {
    // Start state
    {0, {
        {'C', {1, &ADD_100}},
        {'X', {4, &ADD_10}},
        {'L', {9, &ADD_50}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},

    // 100 - 300
    {1, { // 100
        {'C', {2, &ADD_100}},
        {'X', {4, &ADD_10}},
        {'L', {9, &ADD_50}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {2, { // 200
        {'C', {3, &ADD_100}},
        {'X', {4, &ADD_10}},
        {'L', {9, &ADD_50}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {3, { // 300
        {'X', {4, &ADD_10}},
        {'L', {9, &ADD_50}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},

    // 10 - 40, 90
    {4, { // 10
        {'X', {5, &ADD_10}},
        {'L', {7, &ADD_30}},
        {'C', {8, &ADD_80}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {5, { // 20
        {'X', {6, &ADD_10}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {6, { // 30
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {7, { // 40
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {8, { // 90
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},

    // 50 - 80
    {9, { // 50
        {'X', {10, &ADD_10}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {10, { // 60
        {'X', {11, &ADD_10}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {11, { // 70
        {'X', {12, &ADD_10}},
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},
    {12, { // 80
        {'I', {13, &ADD_1}},
        {'V', {18, &ADD_5}}
    }},

    // 1 - 4, 9
    {13, { // 1
        {'I', {14, &ADD_1}},
        {'V', {16, &ADD_3}},
        {'X', {17, &ADD_8}}
    }},
    {14, { // 2
        {'I', {15, &ADD_1}}
    }},
    {15, {}}, // 3
    {16, {}}, // 4
    {17, {}}, // 9

    // 5 - 8
    {18, { // 5
        {'I', {19, &ADD_1}}
    }},
    {19, { // 6
        {'I', {20, &ADD_1}}
    }},
    {20, { // 7
        {'I', {21, &ADD_1}}
    }},
    {21, {}}, // 8
};

bool promptUser() {
  cout << "Enter a roman numeral (empty to quit): ";
  return true;
}

int main() {
  string input;

  while (promptUser() && !getline(cin, input).fail()) {
    if (input.empty()) // Quit if line is empty
      break;

    int currState = 0, total = 0; // Start at state 0
    string romanNumeral(input); // Copy input

    reverse(input.begin(), input.end()); // Reverse input to allow pop_back

    while (!input.empty()) {
      auto stateIt = STATE_TABLE.find(currState); // Lookup the current state number
      if (stateIt == STATE_TABLE.end()) {
        cout << "Error: Invalid state " << currState << endl; // Error if state not found
        return 1;
      }

      auto transitions = stateIt->second;
      auto transitionsIt = transitions.find(input.back()); // Lookup the transition for the next character
      if (transitionsIt == transitions.end()) { // No transition function
        currState = -1;
        break;
      } else {
        currState = transitionsIt->second.first; // Set state
        total = transitionsIt->second.second->operator()(total); // Apply transition to total
        input.pop_back(); // Pop the last character
      }
    }

    // Output
    if (currState == -1) {
      cout << romanNumeral << " = error, not a roman number" << endl;
    } else {
      cout << romanNumeral << " = " << total << endl;
    }
  }

  return 0;
}
