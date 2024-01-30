#include <iostream>
#include <exception>

class DoDosBaseException : std::exception{
    ;
};

class DoDosConnectionException : DoDosBaseException{
    ;
};
