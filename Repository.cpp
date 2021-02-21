#include "Repository.h"
#include <algorithm>


//-------------------------------------------------------MovieRepository-------------------------------------------------------//
//GETTERS//
vector<Movie> MovieRepository::getMovies()
{
    return this->movies;
}

vector<Movie> MovieRepository::getWatchList()
{
    return this->watchList;
}

//SETTERS//
void MovieRepository::setMovies(vector<Movie> new_movies)
{
    this->movies = new_movies;
}


//`````````````````````````````````````````````````````movies`````````````````````````````````````````````````````//
//ADD//
bool MovieRepository::addInMovies(Movie& movie)
{
    vector<Movie>::iterator iterator = std::find(this->movies.begin(), this->movies.end(), movie);
    if (iterator == this->movies.end())
    {
        this->movies.push_back(movie);
        return true;
    }
    return false;
}


//DELETE//
bool MovieRepository::deleteFromMovies(Movie& movie)
{
    vector<Movie>::iterator iterator = std::find(this->movies.begin(), this->movies.end(), movie);
    if (iterator != this->movies.end())
    {
        this->movies.erase(iterator);
        return true;
    }
    return false;
}


//UPDATE//
bool MovieRepository::updateInMovies(Movie& movie)
{
    vector<Movie>::iterator iterator = std::find(this->movies.begin(), this->movies.end(), movie);
    if (iterator != this->movies.end())
    {
        std::replace(this->movies.begin(), this->movies.end(), *iterator, movie);
        return 1;
    }
    return 0;
}

string MovieRepository::displayMovies()
{
    string movies_repository;
    for (auto movie : this->movies)
        movies_repository += movie.convertMovieToString();
    return movies_repository;
}


//FILTER//
vector<Movie> MovieRepository::FilterMovies(Filter& filter)
{
    vector<Movie> filterd_movies;
    for (auto movie : this->movies)
        if (filter.include(movie))
            filterd_movies.push_back(movie);
    return filterd_movies;
}


//`````````````````````````````````````````````````````watchList`````````````````````````````````````````````````````//
//ADD//
bool MovieRepository::addInWatchList(Movie& movie)
{
    vector<Movie>::iterator iterator = std::find(this->watchList.begin(), this->watchList.end(), movie);
    if (iterator == this->watchList.end())
    {
        this->watchList.push_back(movie);
        return true;
    }
    return false;
}


//DELETE//
bool MovieRepository::deleteFromWatchList(Movie& movie)
{
    vector<Movie>::iterator iterator = std::find(this->watchList.begin(), this->watchList.end(), movie);
    if (iterator != this->watchList.end())
    {
        this->watchList.erase(iterator);
        return true;
    }
    return false;
}

