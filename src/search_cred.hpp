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
    string url_ = "https://www.googleapis.com/customsearch/v1?prettyPrint=false&fields=items(title,snippet)&key=API_KEY&cx=CX_CODE&q=";
    string wikipedia_url_ = "https://en.wikipedia.org/w/api.php?action=query&list=search&&srprop=snippet&srinfo=&format=json&srsearch=";
    
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
    string GetUrl(string query);
    
    /**
     * Get the url for the Wikimedia API search for a given question
     *
     * @param query the text to search for
     * @return the url for the Wikimedia search
     */
    string GetWikipediaUrl(string query);
    
};


#endif /* search_cred_hpp */
