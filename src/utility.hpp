//
//  utility.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

const double kDoubleThreshold = 0.01;

/**
 * Set a key and value pair in a given map
 *
 * @param map the map to set the values in
 * @param key the key of the map element
 * @param value the value of the map element
 */
void SetMapValue(map<string, string> &map, string key, string value);

/**
 * Get a vector of keys from a given map
 *
 * @param map the map to retrieve keys from
 * @return a vector of keys
 */
vector<string> GetMapKeys(map<string, string> &map);

/**
 * Get a vector of values from a given map
 *
 * @param map the map the retrieve keys from
 * @return a vector of values
 */
vector<string> GetMapValues(map<string, string> &map);

/**
 * Check if two doubles are approximately equal within the predefined threshold
 *
 * @param first the first double
 * @param second the second double
 * @return if they are approximately equal
 */
bool ApproxEquals(double first, double second);

/**
 * Replace a given value with a new value in a string
 *
 * @param source the string to replace values in
 * @param old_value the value to replace
 * @param new_values the value to replace with
 * @return the new string
 */
string Replace(string source, string old_value, string new_value);

#endif /* utility_hpp */
