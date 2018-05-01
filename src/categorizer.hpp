//
//  categorizer.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/30/18.
//

#ifndef categorizer_hpp
#define categorizer_hpp

#include <stdio.h>
#include <string>
#include "utility.hpp"

using std::string;

/**
 * Questions are categorized by searching metholodology.
 */

enum Category {
    SIMPLEFACT,                 // Simple facts use a naive google search
    CHRONOLOGICALFIRST,         // Search the year for each and choose the earliest result
    CHRONOLOGICALLAST,          // Search the year for each and choose the latest result
    UNKNOWNWHICH                // Looks for occurrences of the question in the answer results
};

const vector<string> negations_ = {
    "not", "n't"
};

/**
 * Check if a question is a negated question
 *
 * @param question the question to check
 * @return if the question is negated
 */
bool GetNegation(string question);

/**
 * Get the category of the given question
 *
 * @param question the question to categorize
 * @return the question category
 */
Category GetCategory(string question);

#endif /* categorizer_hpp */
