#ifndef sleuth_hpp
#define sleuth_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "search_cred.hpp"

using std::string;
using std::vector;

/**
 * Chooses a random set of credentials to use to distribute searches across multiple
 *
 * @return the credentials to use
 */
SearchCred &ChooseCredentials();

/**
 * Get a vector of confidence levels for the given answers to the question
 *
 * @param question the question to answer
 * @param answers the vector of possible answers
 * @return the vector of confidence levels
 */
vector<double> Investigate(string question, vector<string> answers);

#endif /* sleuth_hpp */
