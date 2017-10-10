/*
 * Peter Nguyen
 * CSCI 371 - Project 2
 * Due: Oct. 10, 2017
 * Compile flags: -std=c++11
 */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

const map<
    int, // State
    pair<
        bool, // Accept state
        map<char, int> // Transition
    >
> STATE_TABLE = {
    // 004 == 0 through 9
    // Start state
    {0, {
        false,
        {
            {'+', 1},
            {'-', 1},
            {004, 2},
            {'.', 3}
        }
    }},

    // +, -
    {1, {
        false,
        {
            {004, 2},
            {'.', 3}
        }
    }},

    // digits before decimal
    {2, {
        true,
        {
            {004, 2},
            {'.', 4},
            {'e', 6},
            {'E', 6}
        }
    }},

    // decimal with no prefixing digits
    {3, {
        false,
        {
            {004, 5}
        }
    }},

    // decimal with prefixing digits
    {4, {
        true,
        {
            {004, 5}
        }
    }},

    // digits after decimal
    {5, {
        true,
        {
            {004, 5},
            {'e', 6},
            {'E', 6}
        }
    }},

    // E, e
    {6, {
        false,
        {
            {'+', 7},
            {'-', 7},
            {004, 8}
        }
    }},

    // +, - for exponent
    {7, {
        false,
        {
            {004, 8}
        }
    }},

    // exponent
    {8, {
        true,
        {
            {004, 8}
        }
    }}
};

int main() {
  string input;

  while (cin >> input) {
    if (input.empty()) // Quit if line is empty
      break;

    int currState = 0; // Start at state 0
    string number(input); // Copy input

    reverse(input.begin(), input.end()); // Reverse input to allow pop_back

    while (!input.empty()) {
      auto stateIt = STATE_TABLE.find(currState); // Lookup the current state number
      if (stateIt == STATE_TABLE.end()) {
        cout << "Error: Invalid state " << currState << endl; // Error if state not found
        return 1;
      }

      auto transitions = stateIt->second.second;

      char nextChar = input.back();
      if (isdigit(nextChar)) // Convert to `004` if char is digit
        nextChar = 004;

      auto transitionsIt = transitions.find(nextChar); // Lookup the transition for the next character
      if (transitionsIt == transitions.end()) { // No transition function
        currState = -1;
        break;
      } else {
        currState = transitionsIt->second; // Set state
        input.pop_back(); // Pop the last character
      }
    }

    // Output
    cout << number << ' ';

    // If there was no transition function or the state is not an accept state
    if (currState == -1 || !STATE_TABLE.find(currState)->second.first) {
      cout << "no" << endl;
    } else {
      cout << "yes" << endl;
    }
  }

  return 0;
}
