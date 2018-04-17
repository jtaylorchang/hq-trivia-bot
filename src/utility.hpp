//
//  utility.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/15/18.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

const double kDoubleThreshold = 0.01;

void SetMapValue(map<string, string> &map, string key, string value);
vector<string> GetMapKeys(map<string, string> &map);
vector<string> GetMapValues(map<string, string> &map);

bool ApproxEquals(double first, double second);

#endif /* utility_hpp */
