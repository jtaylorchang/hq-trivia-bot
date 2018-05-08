#include "sleuth.hpp"

/**
 * Chooses a random set of credentials to use to distribute searches across multiple
 */
SearchCred &Sleuth::ChooseCredentials() {
    int index = rand() % search_credentials_.size();
    return search_credentials_[index];
}

/**
 * Receive the response from the urlResponse event
 */
void Sleuth::ReceiveResponse(ofHttpResponse &response, string question, vector<string> answers, vector<double> &confidences) {
    PrintColorful("Received response in Sleuth [ASYNC]", MAGENTA);
    
    ofxJSONElement json = LoadSearchResults(response.data.getText());
    
    if (!finished_basic_ && !finished_wikipedia_basic_) {
        // If neither have been done, prepare the results
        PrepareConfidences(confidences);
    }
    
    int id = response.request.getId();
    if (id == basic_search_id_) {
        // The request being handled is Google
        ProcessGoogleBasic(json, question, answers, confidences);
    } else if (id == basic_wikipedia_search_id_) {
        // The request being handled is Wikipedia
        ProcessWikipediaBasic(json, question, answers, confidences);
    }
    
    if (finished_basic_ && finished_wikipedia_basic_) {
        // If both are done, normalize the results
        FinalizeResults(confidences);
    }
}

/**
 * Get the JSON for the given query
 */
ofxJSONElement Sleuth::LoadSearchResults(string content) {
    ofxJSONElement json(content);
    return json;
}

/**
 * Prepare the confidence vector to accept answer counts
 */
void Sleuth::PrepareConfidences(vector<double> &confidences) {
    for (int i = 0; i < confidences.size(); i++) {
        confidences[i] = 0;
    }
}

/**
 * Strip the snippets from the given JSON data
 */
vector<string> Sleuth::StripGoogleSnippets(ofxJSONElement &json) {
    vector<string> snippets;
    
    std::size_t size = json["items"].size();
    for (Json::ArrayIndex i = 0; i < size; i++) {
        snippets.push_back(json["items"][i]["title"].asString());
        snippets.push_back(json["items"][i]["snippet"].asString());
    }
    
    return snippets;
}

/**
 * Strip the snippets from the wikipedia JSON data
 */
vector<string> Sleuth::StripWikipediaSnippets(ofxJSONElement &json) {
    vector<string> snippets;
    
    std::size_t size = json["query"]["search"].size();
    for (Json::ArrayIndex i = 0; i < size; i++) {
        snippets.push_back(json["query"]["search"][i]["title"].asString());
        
        string snippet = json["query"]["search"][i]["snippet"].asString();
        snippet = Replace(snippet, "<span class=\"searchmatch\">", "");
        snippet = Replace(snippet, "</span>", "");
        cout << snippet << endl;
        snippets.push_back(snippet);
    }
    
    return snippets;
}

/**
 * Count the number of times a piece of the answer occurs in the source
 */
int Sleuth::CountAnswerOccurrences(string source, string answer) {
    string processed_answer = answer;
    
    if (IsConvertableNumber(source)) {
        // Also search for english variants of number answers
        int value = stoi(source);
        processed_answer.append(" ");
        processed_answer.append(NumeralToEnglish(value));
    }
    
    vector<string> pieces = Split(processed_answer, ' ');
    
    int count = 0;
    for (string &piece : pieces) {
        if (IsComplex(piece)) {
            count += Count(source, piece);
        }
    }
    
    return count;
}

/**
 * Increase confidence levels using the default search
 */
void Sleuth::SearchGoogleBasic(SearchCred &cred, string question, vector<string> answers) {
    PrintColorful("Requesting basic search [ASYNC]", MAGENTA);
    basic_search_id_ = ofLoadURLAsync(cred.GetGoogleUrl(question));
}

/**
 * Increase confidence levels using the default search premise on Wikipedia
 */
void Sleuth::SearchWikipediaBasic(SearchCred &cred, string question, vector<string> answers) {
    PrintColorful("Requesting basic wikipedia search [ASYNC]", MAGENTA);
    basic_wikipedia_search_id_ = ofLoadURLAsync(cred.GetWikipediaUrl(question));
}

/**
 * Modifies the confidence values using the given snippets and answers to look for.
 * Same method applies for both Google and Wikipedia results
 */
void Sleuth::ProcessResponse(vector<string> snippets, vector<string> lower_answers, vector<double> &confidences, double weight) {
    for (string &snippet : snippets) {
        cout << "Reading snippet:" << endl;
        cout << snippet << endl;
        
        string lower_snippet = ToLowerCase(snippet);
        
        for (int i = 0; i < lower_answers.size(); i++) {
            int count = CountAnswerOccurrences(lower_snippet, lower_answers[i]);
            // Possibility to weight based on how early a result is: * (lower_answers.size() - i);
            confidences[i] += weight * count;
            
            cout << "Found count [" << count << "] for answer " << (i + 1) << endl << endl;
        }
    }
}

/**
 * Process the basic search JSON and update the confidence levels
 */
void Sleuth::ProcessGoogleBasic(ofxJSONElement &json, string question, vector<string> answers, vector<double> &confidences) {
    PrintColorful("Processing basic search snippets:", MAGENTA);
    
    vector<string> snippets = StripGoogleSnippets(json);
    vector<string> lower_answers = answers;
    
    for (int i = 0; i < lower_answers.size(); i++) {
        lower_answers[i] = ToLowerCase(Trim(lower_answers[i]));
    }
    
    ProcessResponse(snippets, lower_answers, confidences, kGoogleWeight);
    finished_basic_ = true;
}

/**
 * Process the results from the basic Wikipedia search
 */
void Sleuth::ProcessWikipediaBasic(ofxJSONElement &json, string question, vector<string> answers, vector<double> &confidences) {
    PrintColorful("Processing basic wikipedia search snippets:", MAGENTA);
    
    vector<string> snippets = StripWikipediaSnippets(json);
    vector<string> lower_answers = answers;
    
    for (int i = 0; i < lower_answers.size(); i++) {
        lower_answers[i] = ToLowerCase(Trim(lower_answers[i]));
    }
    
    ProcessResponse(snippets, lower_answers, confidences, kWikipediaWeight);
    finished_wikipedia_basic_ = true;
}

/**
 * Finalize the result confidences and normalize them to be all out of 1.0
 */
void Sleuth::FinalizeResults(vector<double> &confidences) {
    for (int i = 0; i < confidences.size(); i++) {
        if (confidences[i] > result_max_count_) {
            result_max_count_ = confidences[i];
        }
    }
    
    if (result_max_count_ > 0) {
        // Normalize the results
        for (int i = 0; i < confidences.size(); i++) {
            confidences[i] /= result_max_count_;
            
            if (confidences[i] > 1) {
                confidences[i] = 1;
            }
        }
    }
}

/**
 * Start the JSON collection for the given question
 */
void Sleuth::Investigate(string question, vector<string> answers) {
    finished_basic_ = false;
    finished_wikipedia_basic_ = false;
    basic_search_id_ = -1;
    basic_wikipedia_search_id_ = -1;
    result_max_count_ = 0;
    
    SearchCred &credentials = ChooseCredentials();
    Category category = GetCategory(question);
    
    // An idea to implement outside of the project to extend it
    switch (category) {
        case SIMPLEFACT:
            SearchGoogleBasic(credentials, question, answers);
            SearchWikipediaBasic(credentials, question, answers);
            break;
    }
}

