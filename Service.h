#pragma once
#include "Repository.h"
#include "Validator.h"
#include "PersistenceEngine.h"
#include "Operation.h"
#include <stack>


//-------------------------------------------------------Service-------------------------------------------------------//
class Service
{
private:
    MovieRepository* repository;
    Validator valid;
    stack<Operation> undo;
    stack<Operation> redo;

public:
    //Constructor - creates an object of class Service
    Service(MovieRepository* repository, Validator valid);
    Service(){}

    //Getter - returns the repository;
    MovieRepository* getMovieRepository();
    stack<Operation>* getUndo();
    stack<Operation>* getRedo();

    //`````````````````````````````````````````````````````movies`````````````````````````````````````````````````````//

    /*
    @brief Reads from a file a list of movies
    IN : -
    OUT : -
    */
    void loadMoviesFromFile();

    /*
    @brief Adds a new movie to the movie repository
    IN : all the attributes of the movie we want to add
    OUT :  true if the operation is possible (the movie doesn't already exist in the movies repository) and false otherwise
    */
    bool addMovieInMovies(string title, string genre, int year_of_release, Time time_of_projection, string location_of_projecition, string trailer);

    /*
    @brief Deletes a movie from the movies repository
    IN : the title of the movie we want to delete
    OUT : true if the movie can be deleted (if the movie exists in the movie repository) and false otherwise
    */
    bool deleteMovieFromMovies(string title);

    /*
    @brief Updates a movie from the movies repository
    IN : the title of the movie we want to update and the new attributes
    OUT : true if the operation is possible (the movie exists in the movie repository) and false otherwise
    */
    bool updateMovieInMovies(string title, string genre, int year_of_release, Time time_of_projection, string location_of_projecition, string trailer);

    /*
    @brief Prints the movies repository
    IN : -
    OUT : returns a string with the repository
    */
    string diplayMovies();

    /*
    @brief Filters the movie list by genre
    IN : an object of class Filter
    OUT : a vector with the filtered movies
    */
    vector<Movie> FilterMoviesByGenre(string genre);

    /*
    @brief Finds the extension of a file
    IN : the name of the file
    OUT : the extension of the file
    */
    string findExtension(string filePath);

    /*
    @brief Loads from a CSV file or JSON file the data for the repository
    IN : a string with the name of the file
    OUT: true if the operation was successful and false otherwise
    */
    bool load(string filePath);

    /*
    @brief Saves in a CSV file or JSON file the data from the repository
    IN : a string with the name of the file
    OUT: true if the operation was successful and false otherwise
    */
    bool save(string filePath);

    //`````````````````````````````````````````````````````watchList`````````````````````````````````````````````````````//
    /*
    @brief Deletes a movie from the watch list repository
    IN : the title of the movie we want to delete
    OUT : true if the movie can be deleted (if the movie exists in the watch list repository) and false otherwise
    */
    bool deleteMovieFromWatchList(string title);

    //`````````````````````````````````````````````````````Undo-Redo`````````````````````````````````````````````````````//
    /*
    @brief undoes the last operation
    @IN: the service
    @OUT: -
    */
    void callUndo();

    /*
    @brief redoes the last operation
    @IN: the service
    @OUT: -
    */
    void callRedo();
};
