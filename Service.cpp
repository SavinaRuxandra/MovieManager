#include "Service.h"
#include <fstream>
#include <iostream>
using namespace std;

//-------------------------------------------------------Service-------------------------------------------------------//
//CONSTRUCTOR//
Service::Service(MovieRepository* repository, Validator valid)
{
    this->repository = repository;
    this->valid = valid;
}


//GETTERS//
MovieRepository* Service::getMovieRepository()
{
    return this->repository;
}

stack<Operation> *Service::getUndo()
{
    return &this->undo;
}

stack<Operation> *Service::getRedo()
{
    return &this->redo;
}


//ADD//
void Service::loadMoviesFromFile()
{
    string title, genre, location_of_projection, trailer;
    int year_of_release = 0, hour, minutes;
    ifstream file;
    file.open("Service.txt");
    while (!file.eof())
    {
        getline(file, title);
        getline(file, genre);
        file >> year_of_release;
        file >> hour >> minutes;
        file.get();
        getline(file, location_of_projection);
        getline(file, trailer);
        file.get();
        Time time_of_projection{ hour, minutes };
        Movie movie{ title, genre, year_of_release, time_of_projection, location_of_projection, trailer };
        this->valid.validMovie(movie);
        this->repository->addInMovies(movie);
    }
    file.close();
}

bool Service::addMovieInMovies(string title, string genre, int year_of_release, Time time_of_projection, string location_of_projection, string trailer)
{
    Movie movie{ title, genre, year_of_release, time_of_projection, location_of_projection, trailer };
    this->valid.validMovie(movie);
    vector<Movie> copy = this->repository->getMovies();
    vector<Movie>::iterator iterator = find(copy.begin(), copy.end(), movie);
    if(iterator != copy.end())
        return false;
    Operation operation{ ADDMOVIES, movie};
    this->undo.push(operation);
    return this->repository->addInMovies(movie);
}


//DELETE//
bool Service::deleteMovieFromMovies(string title)
{
    Movie movie{ title };
    vector<Movie> copy = this->repository->getMovies();
    vector<Movie>::iterator iterator = find(copy.begin(), copy.end(), movie);
    if(iterator == copy.end())
        return false;
    Operation operation{ DELETEMOVIES, *iterator};
    this->undo.push(operation);
    return this->repository->deleteFromMovies(movie);
}


//UPDATE//
bool Service::updateMovieInMovies(string title, string genre, int year_of_release, Time time_of_projection, string location_of_projecition, string trailer)
{
    Movie movie{ title, genre, year_of_release, time_of_projection, location_of_projecition, trailer };
    this->valid.validMovie(movie);
    vector<Movie> copy = this->repository->getMovies();
    vector<Movie>::iterator iterator = find(copy.begin(), copy.end(), movie);
    if(iterator == copy.end())
        return false;
    Operation operation{ UPDATEMOVIES, *iterator};
    this->undo.push(operation);
    return this->repository->updateInMovies(movie);
}


//DISPLAY//
string Service::diplayMovies()
{
    return this->repository->displayMovies();
}


//FILTER//
vector<Movie> Service::FilterMoviesByGenre(string genre)
{
    GenreFilter filter{ genre };
    return this->repository->FilterMovies(filter);
}

string Service::findExtension(string filePath)
{
    std::size_t position;
    string extension = filePath;
    position = filePath.find(".");
    if (position == std::string::npos)
        return "not ok";

    extension = extension.erase(0, position + 1);
    return extension;
}

bool Service::load(string filePath)
{
    PersistanceEngine* persistence;
    string extension;
    extension = findExtension(filePath);
    if (extension == "csv")
        persistence = new PersistanceEngineFromCSV;

    else
        if(extension == "json")
            persistence = new PersistanceEngineFromJSON;
        else
        {
            throw exception("!INCORRECT FILEPATH!");
            return false;
        }
    this->repository->setMovies(persistence->load(filePath));
    return true;
}

bool Service::save(string filePath)
{
    PersistanceEngine* persistence;
    string extension;
    extension = findExtension(filePath);
    if (extension == "csv")
        persistence = new PersistanceEngineFromCSV;

    else
        if (extension == "json")
            persistence = new PersistanceEngineFromJSON;
        else
        {
            throw exception("!INCORRECT FILEPATH!");
            return 0;
        }
    persistence->save(filePath, this->repository->getMovies());
    return true;
}


//`````````````````````````````````````````````````````watchList`````````````````````````````````````````````````````//
//DELETE//
bool Service::deleteMovieFromWatchList(string title)
{
    Movie movie{ title };
    vector<Movie> copy = this->repository->getWatchList();
    vector<Movie>::iterator iterator = find(copy.begin(), copy.end(), movie);
    if(iterator == copy.end())
        return false;
    Operation operation{ DELETEWATCHLIST, *iterator};
    this->undo.push(operation);
    return this->repository->deleteFromWatchList(movie);
}

//`````````````````````````````````````````````````````Undo-Redo`````````````````````````````````````````````````````//
void Service::callUndo()
{
    Operation operation{};
    operation = this->undo.top();
    this->undo.pop();
    if (operation.getType() == ADDMOVIES)
        this->repository->deleteFromMovies(*operation.getMovie());

    if(operation.getType() == DELETEMOVIES)
        this->repository->addInMovies(*operation.getMovie());

    if (operation.getType() == DELETEWATCHLIST)
        this->repository->addInWatchList(*operation.getMovie());

    if (operation.getType() == UPDATEMOVIES)
    {
        vector<Movie> copy = this->repository->getMovies();
        vector<Movie>::iterator iterator = std::find(copy.begin(), copy.end(), operation.getMovie());
        Operation operation_update{ UPDATEMOVIES, *iterator};
        this->repository->updateInMovies(*operation.getMovie());
        operation = operation_update;
    }
    this->redo.push(operation);
}

void Service::callRedo()
{
    Operation operation{};
    operation = this->redo.top();
    this->redo.pop();

    if(operation.getType() == ADDMOVIES)
        this->repository->addInMovies(*operation.getMovie());

    if(operation.getType() == DELETEMOVIES)
        this->repository->deleteFromMovies(*operation.getMovie());

    if(operation.getType() == DELETEWATCHLIST)
        this->repository->deleteFromWatchList(*operation.getMovie());

    if (operation.getType() == UPDATEMOVIES)
    {
        vector<Movie> copy = this->repository->getMovies();
        vector<Movie>::iterator iterator = std::find(copy.begin(), copy.end(), operation.getMovie());
        Operation operation_update{UPDATEMOVIES, *iterator};
        this->repository->updateInMovies(*operation.getMovie());
        operation = operation_update;
    }
    this->undo.push(operation);
}
