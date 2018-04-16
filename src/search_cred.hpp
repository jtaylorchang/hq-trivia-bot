#ifndef search_cred_hpp
#define search_cred_hpp

#include <stdio.h>
#include <string>

using std::string;

class SearchCred {
    
private:
    string api_key_;
    string cx_code_;
    
public:
    SearchCred(string key, string cx) : api_key_(key), cx_code_(cx) {};
    
    /**
     * Get the url for the Google Custom Search for a given message using the predefined auth.
     *
     * @param search the text to search for
     * @return the url for the Google Custom Search
     */
    string GetUrl(string query);
    
};


#endif /* search_cred_hpp */
