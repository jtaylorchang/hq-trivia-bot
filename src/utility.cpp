//
//  utility.cpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#include "utility.hpp"
#include <iostream>

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
