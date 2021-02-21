#ifndef FILTER_H
#define FILTER_H

#include "Domain.h"

//-------------------------------------------------------Filter-------------------------------------------------------//
class Filter
{
public:
    virtual bool include(Movie& movie) = 0;
};

//-----------------------------------------------------GenreFilter-----------------------------------------------------//
class GenreFilter : public Filter
{
private:
    std::string genre;

public:
    GenreFilter(std::string genre) : genre{ genre } {}
    bool include(Movie& movie) override;
};

#endif // FILTER_H
