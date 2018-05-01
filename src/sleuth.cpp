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
        PrepareConfidences(confidences);
    }
    
    int id = response.request.getId();
    if (id == basic_search_id_) {
        ProcessBasic(json, question, answers, confidences);
    } else if (id == basic_wikipedia_search_id_) {
        ProcessWikipediaBasic(json, question, answers, confidences);
    }
    
    if (finished_basic_ && finished_wikipedia_basic_) {
        FinalizeResults(confidences);
    }
}

/**
 * Get the JSON for Google CSE for the given query
 */
ofxJSONElement Sleuth::LoadSearchResults(string content) {
    ofxJSONElement json (content);
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
vector<string> Sleuth::StripSnippets(ofxJSONElement &json) {
    vector<string> snippets;
    
    std::size_t size = json["items"].size();
    for (Json::ArrayIndex i = 0; i < size; i++) {
        snippets.push_back(json["items"][i]["title"].asString());
        snippets.push_back(json["items"][i]["snippet"].asString());
    }
    
    return snippets;
}

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

int Sleuth::CountAnswerOccurrences(string source, string answer) {
    string processed_answer = answer;
    
    if (IsConvertableNumber(source)) {
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
void Sleuth::SearchBasic(SearchCred &cred, string question, vector<string> answers) {
    PrintColorful("Requesting basic search [ASYNC]", MAGENTA);
    basic_search_id_ = ofLoadURLAsync(cred.GetUrl(question));
}

void Sleuth::SearchWikipediaBasic(SearchCred &cred, string question, vector<string> answers) {
    PrintColorful("Requesting basic wikipedia search [ASYNC]", MAGENTA);
    basic_wikipedia_search_id_ = ofLoadURLAsync(cred.GetWikipediaUrl(question));
}

void Sleuth::ProcessResponse(vector<string> snippets, vector<string> lower_answers, vector<double> &confidences) {
    for (string &snippet : snippets) {
        cout << "Reading snippet:" << endl;
        cout << snippet << endl;
        
        string lower_snippet = ToLowerCase(snippet);
        
        for (int i = 0; i < lower_answers.size(); i++) {
            int count = CountAnswerOccurrences(lower_snippet, lower_answers[i]) * (lower_answers.size() - i);
            confidences[i] += count;
            
            cout << "Found count [" << count << "] for answer " << (i + 1) << endl << endl;
        }
    }
}

/**
 * Process the basic search JSON and update the confidence levels
 */
void Sleuth::ProcessBasic(ofxJSONElement &json, string question, vector<string> answers, vector<double> &confidences) {
    PrintColorful("Processing basic search snippets:", MAGENTA);
    
    vector<string> snippets = StripSnippets(json);
    vector<string> lower_answers = answers;
    
    for (int i = 0; i < lower_answers.size(); i++) {
        lower_answers[i] = ToLowerCase(Trim(lower_answers[i]));
    }
    
    ProcessResponse(snippets, lower_answers, confidences);
    finished_basic_ = true;
}

void Sleuth::ProcessWikipediaBasic(ofxJSONElement &json, string question, vector<string> answers, vector<double> &confidences) {
    PrintColorful("Processing basic wikipedia search snippets:", MAGENTA);
    
    vector<string> snippets = StripWikipediaSnippets(json);
    vector<string> lower_answers = answers;
    
    for (int i = 0; i < lower_answers.size(); i++) {
        lower_answers[i] = ToLowerCase(Trim(lower_answers[i]));
    }
    
    ProcessResponse(snippets, lower_answers, confidences);
    finished_wikipedia_basic_ = true;
}

void Sleuth::FinalizeResults(vector<double> &confidences) {
    for (int i = 0; i < confidences.size(); i++) {
        if (confidences[i] > result_max_count_) {
            result_max_count_ = confidences[i];
        }
    }
    
    if (result_max_count_ > 0) {
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
    
    switch (category) {
        case SIMPLEFACT:
            SearchBasic(credentials, question, answers);
            SearchWikipediaBasic(credentials, question, answers);
            break;
    }
}
