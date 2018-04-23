#include "sleuth.hpp"

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
               "016956300416314494911:qmqbjx-nre4")
};

/**
 * Chooses a random set of credentials to use to distribute searches across multiple
 */
SearchCred &ChooseCredentials() {
    int index = rand() % search_credentials_.size();
    return search_credentials_[index];
}

/**
 * Get a vector of confidence levels for the given answers to the question
 */
vector<double> Investigate(string question, vector<string> answers) {
    vector<double> confidences;
    
    return confidences;
}
