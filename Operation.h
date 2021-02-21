#pragma once
#include "Domain.h"

typedef enum {
    ADDMOVIES,
    DELETEMOVIES,
    DELETEWATCHLIST,
    UPDATEMOVIES
} OperationType;


class Operation
{
private:
    OperationType type;
    Movie movie;

public:
    //Constructor - Creates a new operation
    Operation(OperationType type, Movie& movie);
    Operation() = default;

    //Getters
    OperationType getType();
    Movie* getMovie();

    //Setters
    void setType(OperationType type);
    void setMovie(Movie& movie);

    //Equal
    void operator=(Operation operation);
};
