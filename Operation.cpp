#include "Operation.h"

//-------------------------------------------------------Operation-------------------------------------------------------//
//CONSTRUCTOR//
Operation::Operation(OperationType type, Movie& movie)
{
    this->movie = movie;
    this->type = type;
}

//GETTERS//
OperationType Operation::getType()
{
    return this->type;
}

Movie* Operation::getMovie()
{
    return &this->movie;
}


//SETTERS//
void Operation::setType(OperationType type)
{
    this->type = type;
}

void Operation::setMovie(Movie& movie)
{
    this->movie = movie;
}

void Operation::operator=(Operation operation)
{
    this->movie = *operation.getMovie();
    this->type = operation.getType();
}
