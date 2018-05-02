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
    google_url_ = Replace(google_url_, "API_KEY", api_key_);
    google_url_ = Replace(google_url_, "CX_CODE", cx_code_);
}

/**
 * Get the url for the Google Custom Search for a given message using the predefined auth.
 */
string SearchCred::GetGoogleUrl(string query) {
    return BuildUrl(google_url_, query);
}

/**
 * Get the url for the Wikimedia API search for a given question
 */
string SearchCred::GetWikipediaUrl(string query) {
    return BuildUrl(wikipedia_url_, query);
}

/**
 * Build the url from a base and encode the query
 */
string SearchCred::BuildUrl(string base, string query) {
    string url = base + UrlEncode(query);
    
    cout << "Encoding URL:" << endl;
    cout << url << endl;
    
    return url;
}
