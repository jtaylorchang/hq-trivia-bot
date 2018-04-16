//
//  utility.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

void SetMapValue(map<string, string> &map, string key, string value);
vector<string> GetMapKeys(map<string, string> &map);
vector<string> getMapValues(map<string, string> &map);

#endif /* utility_hpp */
