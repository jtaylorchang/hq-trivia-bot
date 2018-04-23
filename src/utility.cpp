//
//  utility.cpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#include "utility.hpp"

/**
 * Set a key and value pair in a given map
 */
void SetMapValue(map<string, string> &map, string key, string value) {
    map[key] = value;
}

/**
 * Get a vector of keys from a given map
 */
vector<string> GetMapKeys(map<string, string> &map) {
    vector<string> keys;
    for (auto i = map.begin(); i != map.end(); i++) {
        keys.push_back(i->first);
    }
    
    return keys;
}

/**
 * Get a vector of values from a given map
 */
vector<string> GetMapValues(map<string, string> &map) {
    vector<string> values;
    for (auto i = map.begin(); i != map.end(); i++) {
        values.push_back(i->second);
    }
    
    return values;
}

/**
 * Check if two doubles are approximately equal within the predefined threshold
 */
bool ApproxEquals(double first, double second) {
    return fabs(first - second) < kDoubleThreshold;
}

/**
 * Replace a given value with a new value in a string
 */
string Replace(string source, string old_value, string new_value) {
    string new_string = source;
    std::size_t old_pos = new_string.find(old_value);
    
    while (old_pos != string::npos) {
        // found one to replace
        new_string.replace(old_pos, old_value.length(), new_value);
        old_pos = new_string.find(old_value);
    }
    
    return new_string;
}

/**
 * Split a string into a vector of strings divided by the given delimiter
 */
vector<string> Split(string input, char delimiter) {
    vector<string> elements;
    string current_element;
    
    for (const char character : input) {
        if (character == delimiter) {
            // Found a new word delimiter
            if (!current_element.empty()) {
                elements.push_back(current_element);
                current_element.clear();
            }
        } else {
            current_element += character;
        }
    }
    
    if (!current_element.empty()) {
        elements.push_back(current_element);
    }
    return elements;
}

/**
 * Breaks a long sentence into multiple lines with given character size
 */
string BreakIntoLines(string source, int line_width) {
    string broken_word;
    vector<string> words = Split(source, ' ');
    
    int count = 0;
    for (string word : words) {
        broken_word.append(word);
        
        if (count >= line_width) {
            // Break to next line
            broken_word.append("\n");
            count = 0;
        } else {
            // Add a space between words
            broken_word.append(" ");
            count += word.length() + 1;
        }
    }
    
    return broken_word;
}

/**
 * Counts the number of occurrences of a char in a string
 */
int Count(string source, char search_char) {
    std::size_t count = std::count(source.begin(), source.end(), search_char);
    return static_cast<int>(count);
}
