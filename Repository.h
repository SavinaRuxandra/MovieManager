#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Filter.h"
#include <vector>
using std::vector;

//-------------------------------------------------------MovieRepository-------------------------------------------------------//
class MovieRepository
{
private:
    vector<Movie> movies;
    vector<Movie> watchList;

public:
    //Constructor - creates an object of class MovieRepository
    MovieRepository() = default;

    //Getters - returns the attributes of the class MovieRepository
    vector<Movie> getMovies();
    vector<Movie> getWatchList();

    //Setters - sets the list of movies from the repository
    void setMovies(vector<Movie> new_movies);

    //`````````````````````````````````````````````````````movies`````````````````````````````````````````````````````//
    /*
    @brief Adds a new movie to the movie repository
    IN : the new movie that we want to add
    OUT : true if the operation is possible (the movie doesn't already exist in the repository) and false otherwise
    */
    bool addInMovies(Movie& movie);

    /*
    @brief Deletes a movie from the movies repository
    IN : the movie we want to delete
    OUT : true if the movie can be deleted (if the movie exists in the movie repository) and false otherwise
    */
    bool deleteFromMovies(Movie& movie);

    /*
    @brief Updates a movie from the movies repository
    IN : the title of the movie we want to update and its new attributes
    OUT : true if the operation is possible (the movie exists in the movie repository) and false otherwise
    */
    bool updateInMovies(Movie& movie);

    /*
    @brief Prints the movies repository
    IN : -
    OUT : returns a string with the repository
    */
    string displayMovies();

    /*
    @brief Filters the movie list
    IN : an object of class Filter
    OUT : a vector with the filtered movies
    */
    vector<Movie> FilterMovies(Filter& filter);

    //`````````````````````````````````````````````````````watchList`````````````````````````````````````````````````````//
    /*
    @brief Adds a new movie to the watchList repository
    IN : the new movie that we want to add
    OUT : true if the operation is possible (the movie doesn't already exist in the repository) and false otherwise
    */
    bool addInWatchList(Movie& movie);

    /*
    @brief Deletes a movie from the watchlist repository
    IN : the movie we want to delete
    OUT : true if the movie can be deleted (if the movie exists in the watchlist repository) and false otherwise
    */
    bool deleteFromWatchList(Movie& movie);
};
#endif // REPOSITORY_H
