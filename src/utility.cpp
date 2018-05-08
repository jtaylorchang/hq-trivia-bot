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
    if (source.empty() || old_value.empty()) {
        return source;
    }
    
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

/*
 * Trim the spaces off of a given string
 */
string Trim(string source) {
    string trimmed_str = source;
    
    // code derived from:
    // http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
    const string &kTrimValues = "\t\n\v\f\r ";
    trimmed_str.erase(0, trimmed_str.find_first_not_of(kTrimValues));
    trimmed_str.erase(trimmed_str.find_last_not_of(kTrimValues) + 1);
    return trimmed_str;
}

/**
 * Convert a string to lower case
 */
string ToLowerCase(string source) {
    string lower_str = source;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

/**
 * URL Encodes a given string
 */
string UrlEncode(string source) {
    string encoded_str = Trim(source);
    
    for (int i = 0; i < kUrlEncodeKeys.size(); i++) {
        encoded_str = Replace(encoded_str, kUrlEncodeKeys[i], kUrlEncodeValues[i]);
    }
    
    return encoded_str;
}

/**
 * Counts the number of occurrences of a char in a string
 */
int Count(string source, char search_char) {
    std::size_t count = std::count(source.begin(), source.end(), search_char);
    return static_cast<int>(count);
}

/**
 * Counts the number of occurrences of a string in a larger string
 */
int Count(string source, string search_str) {
    if (source.empty() || search_str.empty()) {
        // No count
        return 0;
    }
    
    if (search_str.size() == 1) {
        // Use the char count function
        return Count(source, search_str[0]);
    }
    
    int count = 0;
    int furthest_start = 0;
    int last_possible_start = source.length() - search_str.length() + 1;
    char starting_char = search_str[0];
    
    for (int i = 0; i < last_possible_start; i++) {
        if (source[i] == starting_char) {
            // Check for the rest of the substring
            furthest_start = i;
            
            bool matches = true;
            for (int search_index = 1; search_index < search_str.length(); search_index++) {
                if (source[i + search_index] == starting_char && furthest_start == i) {
                    // Next possible starting point to check
                    furthest_start = i + search_index;
                }
                
                if (source[i + search_index] != search_str[search_index]) {
                    // Not a match so advance to the latest possible starting location
                    if (furthest_start > i) {
                        i = furthest_start - 1;
                    }
                    matches = false;
                    break;
                }
            }
            
            if (matches) {
                // Found a match
                count++;
                i += search_str.length();
            }
        }
    }
    
    return count;
}

/**
 * Check if a string contains a substring
 */
bool Contains(string source, string search_str) {
    return (source.find(search_str) != string::npos);
}

/**
 * Check if a string contains at least one string from a vector
 */
bool ContainsOneOf(string source, vector<string> search_strs) {
    for (string &search_str : search_strs) {
        if (Contains(source, search_str)) {
            return true;
        }
    }
    
    return false;
}

/**
 * Check if a string can be converted to a number that can be converted to English
 */
bool IsConvertableNumber(string source) {
    string filtered_source = Replace(source, "-", "");
    
    // derived from:
    // http://www.cplusplus.com/forum/beginner/48769/
    if (filtered_source.find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    
    return (stoi(filtered_source) <= kMaxConvertableNumeral);
}

/**
 * Convert an arabic numeral to an english word
 */
string NumeralToEnglish(int num) {
    switch (num) {
        case 0:
            return "zero";
        case 1:
            return "one once";
        case 2:
            return "two twice";
        case 3:
            return "three";
        case 4:
            return "four";
        case 5:
            return "five";
        case 6:
            return "six";
        case 7:
            return "seven";
        case 8:
            return "eight";
        case 9:
            return "nine";
        case 10:
            return "ten";
    }
    
    return "";
}

/**
 * Check if a word is complex enough to include in searching
 */
bool IsComplex(string word) {
    string lower_word = ToLowerCase(word);
    
    for (string simple_word : kSimpleWords) {
        if (lower_word == simple_word) {
            // Matches a simple word
            return false;
        }
    }
    
    return true;
}

/**
 * Add color codes into the console output (only works on Mac terminal)
 */
void SetConsoleColor(ConsoleColor color) {
    switch (color) {
        case WHITE:
            cout << "\033[0m";
            break;
        case RED:
            cout << "\033[31m";
            break;
        case GREEN:
            cout << "\033[32m";
            break;
        case BLUE:
            cout << "\033[34m";
            break;
        case YELLOW:
            cout << "\033[33m";
            break;
        case MAGENTA:
            cout << "\033[35m";
            break;
        default:
            cout << "\033[0m";
            break;
    }
}

/**
 * Prints a message using a specific color then resets
 */
void PrintColorful(string message, ConsoleColor color) {
    SetConsoleColor(color);
    cout << message << endl;
    SetConsoleColor(WHITE);
}

/**
 * Get a string input from the commandline
 */
string ReceiveString() {
    string response;
    getline(cin, response);
    return response;
}

/**
 * Get the contents of a file as a string
 */
string ReadFileAsString(const std::string &file_path) {
    string contents = "";
    
    if (file_path.empty()) {
        return contents;
    }
    
    std::ifstream stream;
    stream.open(file_path);
    if (stream) {
        // File exists
        string line;
        while (getline(stream, line)) {
            contents += line;
        }
    }
    
    stream.close();
    return contents;
}
