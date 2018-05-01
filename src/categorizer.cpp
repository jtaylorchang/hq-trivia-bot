//
//  categorizer.cpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/30/18.
//

#include "categorizer.hpp"

/**
 * Check if a question is a negated question
 */
bool GetNegation(string question) {
    string lower_question = ToLowerCase(question);
    return ContainsOneOf(lower_question, negations_);
}

/**
 * Get the category of the given question
 */
Category GetCategory(string question) {
    return SIMPLEFACT;
}
