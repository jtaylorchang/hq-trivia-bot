#ifndef search_cred_hpp
#define search_cred_hpp

#include <stdio.h>
#include <string>

class SearchCred {
    
private:
    std::string api_key_;
    std::string cx_code_;
    
public:
    SearchCred(std::string key, std::string cx) : api_key_(key), cx_code_(cx) {};
    
    /**
     * Get the url for the Google Custom Search for a given message using the predefined auth.
     *
     * @param search the text to search for
     * @return the url for the Google Custom Search
     */
    std::string GetUrl(std::string query);
    
};


#endif /* search_cred_hpp */
