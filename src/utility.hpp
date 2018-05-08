//
//  utility.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using std::string;
using std::vector;
using std::map;
using std::cin;
using std::cout;
using std::endl;

const double kDoubleThreshold = 0.01;

const vector<string> kUrlEncodeKeys = {
    "\n", "%", "~", ".", "!", "*", "(", ")", "'", "\"", "&", "#", "?", " "
};
const vector<string> kUrlEncodeValues = {
    " ", "", "%7E", "%2E", "%21", "%2A", "%28", "%29", "%27", "%22", "%26", "%23", "%3F", "%20"
};

const int kMaxConvertableNumeral = 10;

const vector<string> kSimpleWords = {
    "", "a", "an", "i", "to", "is", "not", "the", "can", "and", "of", "da"
};

enum ConsoleColor {
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA
};

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
 * Trim invalid starting and ending characters
 *
 * @param source the string to trim
 * @return the trimmed string
 */
string Trim(string source);

/**
 * Convert a string to lower case
 *
 * @param source the string to turn to lower case
 * @return the lower case version
 */
string ToLowerCase(string source);

/**
 * URL Encodes a given string
 *
 * @param source the string to URL encode
 * @return an encoded string
 */
string UrlEncode(string source);

/**
 * Counts the number of occurrences of a char in a string
 *
 * @param source the string to search in
 * @param search_char the char to search for
 * @return an integer count number
 */
int Count(string source, char search_char);

/**
 * Counts the number of occurrences of a string in a larger string
 *
 * @param source the string to search in
 * @param search_str the string to search for
 * @return an integer count number
 */
int Count(string source, string search_str);

/**
 * Check if a string contains a substring
 *
 * @param source the string to check in
 * @param search_str the string to search for
 * @return if the source string contains the search string
 */
bool Contains(string source, string search_str);

/**
 * Check if a string contains at least one string from a vector
 *
 * @param source the string to check in
 * @param search_strs the vector of strings to search for
 * @return if the source string contains one of the search strings
 */
bool ContainsOneOf(string source, vector<string> search_strs);

/**
 * Check if a string can be converted to a number that can be converted to English
 *
 * @param source the string to check
 * @return if the string is convertable
 */
bool IsConvertableNumber(string source);

/**
 * Convert an arabic numeral to an english word
 *
 * @param num the number to convert
 * @return the english representation
 */
string NumeralToEnglish(int num);

/**
 * Check if a word is complex enough to include in searching
 *
 * @param word the word to check
 * @return if the word is complex
 */
bool IsComplex(string word);

/**
 * Add color codes into the console output (only works on Mac terminal)
 *
 * @param color the color to use (from an enum)
 */
void SetConsoleColor(ConsoleColor color);

/**
 * Prints a message using a specific color then resets
 *
 * @param message the message to print
 * @param color the color to use
 */
void PrintColorful(string message, ConsoleColor color);

/**
 * Get a string input from the commandline
 *
 * @return the string
 */
string ReceiveString();

/**
 * Get the contents of a file as a string
 *
 * @param file_path the path to the file
 * @return the string contents
 */
string ReadFileAsString(const std::string &file_path);

#endif /* utility_hpp */
