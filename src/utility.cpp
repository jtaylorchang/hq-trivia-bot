//
//  utility.cpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#include "utility.hpp"

void SetMapValue(map<string, string> &map, string key, string value) {
    map[key] = value;
}

vector<string> GetMapKeys(map<string, string> &map) {
    vector<string> keys;
    for (auto i = map.begin(); i != map.end(); i++) {
        keys.push_back(i->first);
    }
    
    return keys;
}

vector<string> GetMapValues(map<string, string> &map) {
    vector<string> values;
    for (auto i = map.begin(); i != map.end(); i++) {
        values.push_back(i->second);
    }
    
    return values;
}

bool ApproxEquals(double first, double second) {
    return fabs(first - second) < kDoubleThreshold;
}
