//
// Created by hartings on 23.05.18.
//

#include "Execption.h"

MyExecption::MyExecption() {
    _message = "Error: No error message specified";
}

MyExecption::MyExecption(std::string errorMessage) {
_message = errorMessage;
}

std::string MyExecption::getMessage() {
    return _message;
}