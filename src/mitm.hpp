//
//  mitm.hpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/12/18.
//

#ifndef mitm_hpp
#define mitm_hpp

#include <stdio.h>
#include <string>

class Mitm {
    
private:
    std::string latest_message_;
    
public:
    std::string GetLatestMessage();
    void SetLatestMessage(std::string message);
    
};

#endif /* mitm_hpp */
