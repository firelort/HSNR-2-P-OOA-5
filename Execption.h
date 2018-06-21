//
// Created by hartings on 23.05.18.
//

#ifndef OOA3_EXECPTION_H
#define OOA3_EXECPTION_H

#include <string>

class MyExecption {
private:
    std::string _message;
public:
    MyExecption();
    MyExecption(std::string errorMessage);
    std::string getMessage();

};

#endif //OOA3_EXECPTION_H
