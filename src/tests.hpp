#ifndef tests_hpp
#define tests_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "utility.hpp"

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;

/**
 * Run in test mode
 */
void RunTestMode();

/**
 * Run all the tests
 */
void RunTests();

/**
 * Run tests regarding maps and keys / values
 */
void RunSectionMaps();

/**
 * Run tests regarding equality of doubles
 */
void RunSectionDoubles();

/**
 * Run tests regarding string manipulations
 */
void RunSectionStringManipulation();

/**
 * Run tests regarding string properties
 */
void RunSectionStringProperties();

/**
 * Run tests regarding converting numbers to english
 */
void RunSectionNumberConversions();

/**
 * Run tests regarding word complexity
 */
void RunSectionWordComplexity();

/**
 * Print the full test results after the tests are done
 */
void PrintResults();

/**
 * Checks if a boolean is true, and changes the appropriate test counts and prints
 *
 * @param message the message to print
 * @param condition the first boolean
 */
void Assert(string message, bool condition);

#endif /* tests_hpp */
