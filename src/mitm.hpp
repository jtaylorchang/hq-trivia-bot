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
    bool connected_;
    std::string latest_message_;
    
public:
    bool IsConnected();
    void SetConnected(bool connected);
    std::string GetLatestMessage();
    void SetLatestMessage(std::string message);
    
};

#endif /* mitm_hpp */
