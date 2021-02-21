#ifndef TEST_H
#define TEST_H

#include "Service.h"

class Test
{
private:
//Time
    void testTimeGet();
    void testTimeSet();
    void testTimeEqual();
    void testTimeConvertToString();
//Movie
    void testMovieGet();
    void testMovieSet();
    void testMovieEqual();
    void testGetMovies();
    //void testMovieConvertToString();
    //void testMovieForUserConvertToString();
//MovieRepository
    void testGetWatchList();
    void testAddInMovies();
    void testDeleteFromMovies();
    void testUpdateInMovies();
    void testFilterMovies();
    void testAddInWatchList();
    void testDeleteFromWatchList();
//Service
    void testLoadMoviesFromFile();
    void testAddMovieInMovies();
    void testdeleteMovieFromMovies();
    void testupdateMovieInMovies();
    void testFilterMoviesByGenre();
    void testdeleteMovieFromWatchList();

public:
    void tests();
};


#endif // TEST_H
