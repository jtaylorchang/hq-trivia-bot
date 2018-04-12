//
//  mitm.cpp
//  Holmes
//
//  Created by Jeff Taylor-Chang on 4/12/18.
//

#include "mitm.hpp"

std::string Mitm::GetLatestMessage() {
    return latest_message_;
}

void Mitm::SetLatestMessage(std::string message) {
    latest_message_ = message;
}
