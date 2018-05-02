#ifndef search_cred_hpp
#define search_cred_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "utility.hpp"

using std::string;

class SearchCred {
    
private:
    string api_key_;
    string cx_code_;
    string google_url_ = "https://www.googleapis.com/customsearch/v1?prettyPrint=false&fields=items(title,snippet)&key=API_KEY&cx=CX_CODE&q=";
    string wikipedia_url_ = "https://en.wikipedia.org/w/api.php?action=query&list=search&&srprop=snippet&srinfo=&format=json&srlimit=100&srsearch=";
    
public:
    /**
     * Create an empty default SearchCred object
     */
    SearchCred();
    
    /**
     * Create a SearchCred object using given key and cx and generate the URL
     */
    SearchCred(string key, string cx);
    
    /**
     * Generates the base url with the appropriate api key and cx code
     */
    void GenerateBaseUrl();
    
    /**
     * Get the url for the Google Custom Search for a given question using the predefined auth
     *
     * @param query the text to search for
     * @return the url for the Google Custom Search
     */
    string GetGoogleUrl(string query);
    
    /**
     * Get the url for the Wikimedia API search for a given question
     *
     * @param query the text to search for
     * @return the url for the Wikimedia search
     */
    string GetWikipediaUrl(string query);
    
    /**
     * Build the url from a base and encode the query
     *
     * @param base the base of the URL that accepts a query at the end
     * @param query the item to encode onto the end of the url
     * @return the encoded and prepared url
     */
    string BuildUrl(string base, string query);
    
};


#endif /* search_cred_hpp */
