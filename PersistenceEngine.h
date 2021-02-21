#ifndef PERSISTENCEENGINE_H
#define PERSISTENCEENGINE_H

#include "Domain.h"
#include "Validator.h"
#include <vector>

using namespace std;

class PersistanceEngine
{
public:
    PersistanceEngine() {}
    virtual vector<Movie> load(string filePath) = 0;
    virtual void save(string filePath, vector<Movie>) = 0;
};

class PersistanceEngineFromCSV : public PersistanceEngine
{
public:
    PersistanceEngineFromCSV() {}
    vector<Movie> load(string filePath) override;
    void save(string filePath, vector<Movie>) override;
};

class PersistanceEngineFromJSON : public PersistanceEngine
{
public:
    PersistanceEngineFromJSON() {}
    vector<Movie> load(string filePath) override;
    void save(string filePath, vector<Movie>) override;
};


#endif // PERSISTENCEENGINE_H
