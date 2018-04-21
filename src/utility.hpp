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

/**
 * Split a string into a vector of strings divided by the given delimiter
 *
 * @param input the full string
 * @param delimiter the char to split by
 * @return the vector of strings
 */
vector<string> Split(std::string input, char delimiter);

/**
 * Breaks a long sentence into multiple lines with given character size
 *
 * @param source the string to break
 * @param line_width the desired line width
 * @return the broken string
 */
string BreakIntoLines(string source, int line_width);

/**
 * Counts the number of occurrences of a char in a string
 *
 * @param source the string to search in
 * @param search_char the char to search for
 * @return an integer count number
 */
int Count(string source, char search_char);

#endif /* utility_hpp */
