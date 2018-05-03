#ifndef sleuth_hpp
#define sleuth_hpp

#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include "search_cred.hpp"
#include "categorizer.hpp"
#include "ofxJSON.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Sleuth {
    
private:
    /**
     * Google Custom Search REST API keys to cycle through
     */
    vector<SearchCred> search_credentials_ = {
        SearchCred("AIzaSyAMeo1WRPJsfDYR8fW389Zia7fl-6rVKvU",
                   "011755180049813977756:txa6on3hysw"),
        SearchCred("AIzaSyCE2PlTlUggSUgydHxFQS8H8ViLJXoMG4M",
                   "017993560926643083890:u9edc5uskmq"),
        SearchCred("AIzaSyAPJBozPxFNJUm7eIS2ZRv9GNMm2P_S0xo",
                   "011027612069579013146:xbt_oj4htzq"),
        SearchCred("AIzaSyBYQcnGoPS1U_4gNZax8ha-XjuFEBIuv6o",
                   "015228221608509576590:togix_mvjza"),
        SearchCred("AIzaSyBeLv2dwgH6UGnmVkeO6PkH0qqGn-Cjznw",
                   "016956300416314494911:qmqbjx-nre4"),
        SearchCred("AIzaSyBJzX61a3Tzdw0OZUxE_l0WXEkDZ9qF8UM",
                   "005382590508470163870:z6zjzrahnfo"),
        SearchCred("AIzaSyBetFvP2q8ftqYFLMz2mZhLKftB1M4umv8",
                   "013433297820653323692:m6nyodgncm8"),
        SearchCred("AIzaSyDhBKJlwzcymLMeZPbFleZZWwy1nxpJNF0",
                   "013936195782275847984:fiqc1zogjp4")
    };

public:
    int basic_search_id_ = -1;
    int basic_wikipedia_search_id_ = -1;
    int result_max_count_ = 0;
    bool finished_basic_ = false;
    bool finished_wikipedia_basic_ = false;

    /**
     * Chooses a random set of credentials to use to distribute searches across multiple
     *
     * @return the credentials to use
     */
    SearchCred &ChooseCredentials();

    /**
     * Receive the response from the urlResponse event
     *
     * @param response the response received
     * @param question the question that is being answered
     * @param answers the possible answers
     * @param confidences the confidence destination vector
     * @param max_confidence the max confidence destination double
     */
    void ReceiveResponse(ofHttpResponse &response, string question, vector<string> answers, vector<double> &confidences);

    /**
     * Get the JSON for the given query
     *
     * @param cred the credentials to use
     * @param query the text to search
     * @return the JSON results
     */
    ofxJSONElement LoadSearchResults(string content);

    /**
     * Prepare the confidence vector to accept answer counts
     *
     * @param confidences the reference to the confidence vector
     */
    void PrepareConfidences(vector<double> &confidences);

    /**
     * Strip the snippets from the given JSON data
     *
     * @param json the json to process
     * @return a vector of string snippets
     */
    vector<string> StripGoogleSnippets(ofxJSONElement &json);
    
    /**
     * Strip the snippets from the wikipedia JSON data
     *
     * @param json the json to process
     * @return a vector of string snippets
     */
    vector<string> StripWikipediaSnippets(ofxJSONElement &json);

    /**
     * Count the number of times a piece of the answer occurs in the source
     *
     * @param source the string to look through
     * @param answer the full answer to break into pieces
     * @return the number of occurrences of each piece
     */
    int CountAnswerOccurrences(string source, string answer);

    /**
     * Increase confidence levels using the default Google search
     *
     * @param cred the credentials to use
     * @param question the question to search
     * @param answers the possible answers
     */
    void SearchGoogleBasic(SearchCred &cred, string question, vector<string> answers);

    /**
     * Increase confidence levels using the default search premise on Wikipedia
     *
     * @param cred the credential object to use
     * @param question the question to search
     * @param answers the possible answers
     */
    void SearchWikipediaBasic(SearchCred &cred, string question, vector<string> answers);

    /**
     * Modifies the confidence values using the given snippets and answers to look for.
     * Same method applies for both Google and Wikipedia results
     *
     * @param snippets the vector of snippets to look through
     * @param lower_answers the vector of answers to look for
     * @param confidences the confidence vector destination
     */
    void ProcessResponse(vector<string> snippets, vector<string> lower_answers, vector<double> &confidences);
    
    /**
     * Process the basic search JSON and update the confidence levels
     *
     * @param json the JSON to process
     * @param question the question to answer
     * @param answers the potential answers
     * @param confidences the confidence vector to update
     */
    void ProcessGoogleBasic(ofxJSONElement &json, string question, vector<string> answers,
                            vector<double> &confidences);

    /**
     * Process the results from the basic Wikipedia search
     *
     * @param json the JSON to process
     * @param question the question to answer
     * @param answers the potential answers
     * @param confidences the confidence vector to update
     */
    void ProcessWikipediaBasic(ofxJSONElement &json, string question, vector<string> answers,
                               vector<double> &confidences);

    
    /**
     * Finalize the result confidences and normalize them to be all out of 1.0
     *
     * @param confidences the confidence vector destination
     */
    void FinalizeResults(vector<double> &confidences);
    
    /**
     * Start the JSON collection for the given question
     *
     * @param question the question to answer
     * @param answers the vector of possible answers
     */
    void Investigate(string question, vector<string> answers);

};
    
#endif /* sleuth_hpp */
