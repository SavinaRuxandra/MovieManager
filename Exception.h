#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

using namespace std;

//-------------------------------------------------------MovieException-------------------------------------------------------//
class MovieException : public exception
{
private:
    string msg;

public:
    MovieException(string msg) : msg(msg) {}
    const char* what() const throw () { return msg.c_str(); }
};

//-------------------------------------------------------RepositoryException-------------------------------------------------------//
class RepositoryException : public exception
{
private:
    string msg;

public:
    RepositoryException(string msg) : msg(msg) {}
    const char* what() const throw () { return msg.c_str(); }
};

//-------------------------------------------------------NonExistingFileException-------------------------------------------------------//
class NonExistingFileException : public exception
{
private:
    string msg;

public:
    NonExistingFileException(string msg) : msg(msg) {}
    const char* what() const throw () { return msg.c_str(); }
};

#endif // EXCEPTION_H
