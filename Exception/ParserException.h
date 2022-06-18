//
//  Exceptions.h
//  SimpleCalculator
//
//  Created by Quinten Soetens on 12/02/14.
//  Copyright (c) 2014 Quinten Soetens. All rights reserved.
//

#ifndef CAR_SIMULATOR_PARSEREXCEPTION_H
#define CAR_SIMULATOR_PARSEREXCEPTION_H
#include <iostream>
#include <exception>

class ParserException : public std::exception{
    const char* message;
public:
    ParserException (const char* messages):
        message(messages){}
    const char* what () const throw(){
        return message;
    }
};


#endif //CAR_SIMULATOR_PARSEREXCEPTION_H
