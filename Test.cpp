#include "Test.h"
#include <assert.h>
#include <iostream>
//-------------------------------------------------------Time-------------------------------------------------------//
void Test::testTimeGet()
{
    Time time{ 10, 23 };
    assert(time.getHour() == 10);
    assert(time.getMinutes() == 23);
}

void Test::testTimeSet()
{
    Time time{ 10, 23 };
    time.setHour(5);
    time.setMinutes(30);
    assert(time.getHour() == 5);
    assert(time.getMinutes() == 30);
}

void Test::testTimeEqual()
{
    Time time1{ 23, 23 };
    Time time2{ 23, 23 };
    assert(time1 == time2);
}

void Test::testTimeConvertToString()
{
    Time time1{ 10, 0 }, time2{ 23, 45 };
    assert(time1.convertTimeToString() == "10:00");
    assert(time2.convertTimeToString() == "23:45");
}

//-------------------------------------------------------Movie-------------------------------------------------------//
void Test::testMovieGet()
{
    Time time{ 20, 20 };
    Movie movie{ "Title", "Comedy", 2012, time, "Location", "Trailer" };
    assert(movie.getTitle() == "Title");
    assert(movie.getGenre() == "Comedy");
    assert(movie.getYearOfRelease() == 2012);
    assert(movie.getTimeOfProjection() == time);
    assert(movie.getLocationOfProjection() == "Location");
    assert(movie.getTrailer() == "Trailer");
}

void Test::testMovieSet()
{
    Time time1{ 15, 30 };
    Movie movie{ "Title1", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    movie.setTitle("Title2");
    movie.setGenre("Mystery");
    movie.setYearOfRelease(2000);
    movie.setTimeOfProjection(time2);
    movie.setLocationOfProjection("Location2");
    movie.setTrailer("Trailer2");
    assert(movie.getTitle() == "Title2");
    assert(movie.getGenre() == "Mystery");
    assert(movie.getYearOfRelease() == 2000);
    assert(movie.getTimeOfProjection() == time2);
    assert(movie.getLocationOfProjection() == "Location2");
    assert(movie.getTrailer() == "Trailer2");
}

void Test::testMovieEqual()
{
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(movie1 == movie2);
}

void Test::testGetMovies()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    repository.addInMovies(movie1);
    repository.addInMovies(movie2);
    assert(repository.getMovies()[0] == movie1);
    assert(repository.getMovies()[1] == movie2);
}

//void Test::testMovieConvertToString()
//{
//	Time time{ 0, 0 };
//	Movie movie{ "", "", 0, time, "", "" };
//	std::cout << movie.convertMovieToString();
//	assert(movie.convertMovieToString() == "Title: \nGenre: \nYear of release: \nTime of projection: 0:00\nLocation of projection: \nTrailer: \n\n");
//}
//
//void Test::testMovieForUserConvertToString()
//{
//	Time time{ 15, 30 };
//	Movie movie{ "Title", "Comedy", 2012, time, "Location", "Trailer" };
//	assert(movie.convertMovieToString() == "Title: Title\nGenre: Comedy\nYear of release: 2012\nTime of projection: 15:30\nLocation of projection: Location\n\n");
//}

//-------------------------------------------------------MovieRepository-------------------------------------------------------//
void Test::testGetWatchList()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    repository.addInWatchList(movie1);
    repository.addInWatchList(movie2);
    assert(repository.getWatchList()[0] == movie1);
    assert(repository.getWatchList()[1] == movie2);
}

void Test::testAddInMovies()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(repository.getMovies().size() == 0);
    repository.addInMovies(movie1);
    assert(repository.getMovies()[0] == movie1);
    assert(repository.getMovies().size() == 1);
    repository.addInMovies(movie2);
    assert(repository.getMovies()[0] == movie1);
    assert(repository.getMovies()[1] == movie2);
    assert(repository.getMovies().size() == 2);
    repository.addInMovies(movie2);
    assert(repository.getMovies()[0] == movie1);
    assert(repository.getMovies()[1] == movie2);
    assert(repository.getMovies().size() == 2);
}

void Test::testDeleteFromMovies()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(repository.getMovies().size() == 0);
    repository.addInMovies(movie1);
    repository.addInMovies(movie2);
    assert(repository.getMovies().size() == 2);
    repository.deleteFromMovies(movie1);
    assert(repository.getMovies()[0] == movie2);
    assert(repository.getMovies().size() == 1);
    repository.deleteFromMovies(movie1);
    assert(repository.getMovies()[0] == movie2);
    assert(repository.getMovies().size() == 1);
    repository.deleteFromMovies(movie2);
    assert(repository.getMovies().size() == 0);
}

void Test::testUpdateInMovies()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    Time time3{ 20, 40 };
    Movie movie3{ "Title", "Horror", 2025, time3, "Location3", "Trailer3" };
    repository.addInMovies(movie1);
    repository.addInMovies(movie2);
    repository.updateInMovies(movie3);
    assert(repository.getMovies().size() == 2);
    assert(repository.getMovies()[0].getTitle() == "Title");
    assert(repository.getMovies()[0].getGenre() == "Horror");
    assert(repository.getMovies()[0].getTimeOfProjection() == time3);
    assert(repository.getMovies()[0].getLocationOfProjection() == "Location3");
    assert(repository.getMovies()[0].getTrailer() == "Trailer3");
    vector<Movie> copy_repository = repository.getMovies();
    movie1.setTitle("Title4");
    repository.updateInMovies(movie1);
    assert(copy_repository[0] == repository.getMovies()[0]);
    assert(copy_repository[1] == repository.getMovies()[1]);
}

void Test::testFilterMovies()
{
    vector<Movie> filtered_movies;
    GenreFilter filter{"Comedy"};
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    Time time3{ 20, 40 };
    Movie movie3{ "Title3", "Horror", 2025, time3, "Location3", "Trailer3" };
    repository.addInMovies(movie1);
    repository.addInMovies(movie2);
    repository.addInMovies(movie3);
    filtered_movies = repository.FilterMovies(filter);
    assert(filtered_movies[0] == movie1);
    assert(filtered_movies[1] == movie2);
    assert(filtered_movies.size() == 2);
}

void Test::testAddInWatchList()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(repository.getWatchList().size() == 0);
    repository.addInWatchList(movie1);
    assert(repository.getWatchList()[0] == movie1);
    assert(repository.getWatchList().size() == 1);
    repository.addInWatchList(movie2);
    assert(repository.getWatchList()[0] == movie1);
    assert(repository.getWatchList()[1] == movie2);
    assert(repository.getWatchList().size() == 2);
    repository.addInWatchList(movie2);
    assert(repository.getWatchList()[0] == movie1);
    assert(repository.getWatchList()[1] == movie2);
    assert(repository.getWatchList().size() == 2);
}

void Test::testDeleteFromWatchList()
{
    MovieRepository repository{};
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(repository.getWatchList().size() == 0);
    repository.addInWatchList(movie1);
    repository.addInWatchList(movie2);
    assert(repository.getWatchList().size() == 2);
    repository.deleteFromWatchList(movie1);
    assert(repository.getWatchList()[0] == movie2);
    assert(repository.getWatchList().size() == 1);
    repository.deleteFromWatchList(movie1);
    assert(repository.getWatchList()[0] == movie2);
    assert(repository.getWatchList().size() == 1);
    repository.deleteFromWatchList(movie2);
    assert(repository.getWatchList().size() == 0);
}

//-------------------------------------------------------Service-------------------------------------------------------//

void Test::testLoadMoviesFromFile()
{
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time{ 20, 30 };
    Movie movie1{ "Dirty Dancing", "Drama", 1987, time,"Central Park", "https ://youtube.com/watch?v=eIcmQNy9FsM"};
    time.setHour(16); time.setMinutes(0);
    Movie movie2{ "Alvin and the chipmunks", "Animation", 2007, time, "Cinema", "https ://www.youtube.com/watch?v=sc-C8uumMkw"};
    time.setHour(23); time.setMinutes(30);
    Movie movie3{ "Zodiac", "Drama", 2007, time, "Central Park", "https ://www.youtube.com/watch?v=yNncHPl1UXg"};
    time.setHour(20); time.setMinutes(0);
    Movie movie4{ "La La Land", "Musical", 2016, time, "Central Park", "https ://www.youtube.com/watch?v=0pdqf4P9MB8"};
    service.loadMoviesFromFile();
    assert(service.getMovieRepository()->getMovies().size() == 10);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    assert(service.getMovieRepository()->getMovies()[3] == movie2);
    assert(service.getMovieRepository()->getMovies()[7] == movie3);
    assert(service.getMovieRepository()->getMovies()[9] == movie4);
}

void Test::testAddMovieInMovies()
{
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    Movie movie3{ "Title", "Horror", 2025, time2, "Location3", "Trailer3" };
    assert(service.getMovieRepository()->getMovies().size() == 0);
    service.addMovieInMovies("Title", "Comedy", 2012, time1, "Location1", "Trailer1");
    assert(service.getMovieRepository()->getMovies().size() == 1);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    service.addMovieInMovies("Title2", "Comedy", 2020, time2, "Location2", "Trailer2");
    assert(service.getMovieRepository()->getMovies().size() == 2);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    assert(service.getMovieRepository()->getMovies()[1] == movie2);
    service.addMovieInMovies("Title", "Horror", 2025, time2, "Location3", "Trailer3");
    assert(service.getMovieRepository()->getMovies().size() == 2);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    assert(service.getMovieRepository()->getMovies()[1] == movie2);
}

void Test::testdeleteMovieFromMovies()
{
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time1{ 15, 30 };
    Movie movie1{ "Title1", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(service.getMovieRepository()->getMovies().size() == 0);
    service.addMovieInMovies("Title1", "Comedy", 2012, time1, "Location1", "Trailer1");
    service.addMovieInMovies("Title2", "Comedy", 2020, time2, "Location2", "Trailer2");
    assert(service.getMovieRepository()->getMovies().size() == 2);
    service.deleteMovieFromMovies("Title2");
    assert(service.getMovieRepository()->getMovies().size() == 1);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    service.deleteMovieFromMovies("Title");
    assert(service.getMovieRepository()->getMovies().size() == 1);
    assert(service.getMovieRepository()->getMovies()[0] == movie1);
    service.deleteMovieFromMovies("Title1");
    assert(service.getMovieRepository()->getMovies().size() == 0);
}

void Test::testupdateMovieInMovies()
{
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time1{ 15, 30 };
    Movie movie1{ "Title", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    Movie movie3{ "Title", "Horror", 2025, time2, "Location3", "Trailer3" };
    service.addMovieInMovies("Title", "Comedy", 2012, time1, "Location1", "Trailer1");
    service.addMovieInMovies("Title2", "Comedy", 2020, time2, "Location2", "Trailer2");
    service.updateMovieInMovies("Title", "Horror", 2025, time2, "Location3", "Trailer3");
    assert(service.getMovieRepository()->getMovies().size() == 2);
    assert(service.getMovieRepository()->getMovies()[0].getTitle() == "Title");
    assert(service.getMovieRepository()->getMovies()[0].getGenre() == "Horror");
    assert(service.getMovieRepository()->getMovies()[0].getTimeOfProjection() == time2);
    assert(service.getMovieRepository()->getMovies()[0].getLocationOfProjection() == "Location3");
    assert(service.getMovieRepository()->getMovies()[0].getTrailer() == "Trailer3");
    vector<Movie> copy_repository = service.getMovieRepository()->getMovies();
    service.updateMovieInMovies("Title4", "Horror", 2025, time2, "Location3", "Trailer3");
    assert(copy_repository[0] == service.getMovieRepository()->getMovies()[0]);
    assert(copy_repository[1] == service.getMovieRepository()->getMovies()[1]);
}

void Test::testFilterMoviesByGenre()
{
    vector<Movie> filtered_movies;
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time1{ 15, 30 };
    Movie movie1{ "Title1", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    Movie movie3{ "Title3", "Horror", 2025, time2, "Location3", "Trailer3" };
    service.addMovieInMovies("Title1", "Comedy", 2012, time1, "Location1", "Trailer1");
    service.addMovieInMovies("Title2", "Comedy", 2020, time2, "Location2", "Trailer2");
    service.addMovieInMovies("Title3", "Horror", 2025, time2, "Location3", "Trailer3");
    filtered_movies = service.FilterMoviesByGenre("Comedy");
    assert(filtered_movies.size() == 2);
    assert(filtered_movies[0] == movie1);
    assert(filtered_movies[1] == movie2);
}

void Test::testdeleteMovieFromWatchList()
{
    MovieRepository repository{};
    Validator valid;
    Service service{ &repository, valid };
    Time time1{ 15, 30 };
    Movie movie1{ "Title1", "Comedy", 2012, time1, "Location1", "Trailer1" };
    Time time2{ 10, 40 };
    Movie movie2{ "Title2", "Comedy", 2020, time2, "Location2", "Trailer2" };
    assert(service.getMovieRepository()->getWatchList().size() == 0);
    service.getMovieRepository()->addInWatchList(movie1);
    service.getMovieRepository()->addInWatchList(movie2);
    assert(service.getMovieRepository()->getWatchList().size() == 2);
    service.deleteMovieFromWatchList("Title2");
    assert(service.getMovieRepository()->getWatchList().size() == 1);
    assert(service.getMovieRepository()->getWatchList()[0] == movie1);
    service.deleteMovieFromWatchList("Title");
    assert(service.getMovieRepository()->getWatchList().size() == 1);
    assert(service.getMovieRepository()->getWatchList()[0] == movie1);
    service.deleteMovieFromWatchList("Title1");
    assert(service.getMovieRepository()->getWatchList().size() == 0);
}

void Test::tests()
{
    this->testTimeGet();
    this->testTimeSet();
    this->testTimeEqual();
    this->testTimeConvertToString();
    this->testMovieGet();
    this->testMovieSet();
    this->testMovieEqual();
    //this->testMovieConvertToString();
    //this->testMovieForUserConvertToString();
    this->testGetMovies();
    this->testGetWatchList();
    this->testAddInMovies();
    this->testDeleteFromMovies();
    this->testUpdateInMovies();
    this->testFilterMovies();
    this->testAddInWatchList();
    this->testDeleteFromWatchList();
    this->testLoadMoviesFromFile();
    this->testAddMovieInMovies();
    this->testdeleteMovieFromMovies();
    this->testupdateMovieInMovies();
    this->testFilterMoviesByGenre();
    this->testdeleteMovieFromWatchList();
}
