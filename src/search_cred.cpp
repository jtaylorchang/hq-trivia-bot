#include "search_cred.hpp"

/**
 * Create an empty default SearchCred object
 */
SearchCred::SearchCred() : api_key_(""), cx_code_("") {};

/**
 * Create a SearchCred object using given key and cx and generate the URL
 *
 * @param key the api key to use
 * @param cx the cx code to use
 */
SearchCred::SearchCred(string key, string cx) {
    api_key_ = key;
    cx_code_ = cx;
    
    GenerateBaseUrl();
}

/**
 * Generates the base url with the appropriate api key and cx code
 */
void SearchCred::GenerateBaseUrl() {
    url_ = Replace(url_, "API_KEY", api_key_);
    url_ = Replace(url_, "CX_CODE", cx_code_);
}

/**
 * Get the url for the Google Custom Search for a given message using the predefined auth.
 */
string SearchCred::GetUrl(string query) {
    // May need to URL encode the query
    return url_ + query;
}
