#ifndef DOMAIN_H
#define DOMAIN_H

#pragma once
#include <string>
#include <iostream>
using namespace std;

//-------------------------------------------------------Time-------------------------------------------------------//
class Time
{
private:
    int hour;
    int minutes;

public:
    //Contructors - creates a new object of type "Time"//
    Time(const int& hour, const int& minutes);
    Time() : hour(0), minutes(0) {}

    //Getters - returns the attributes of the class Time//
    int getHour();
    int getMinutes();

    //Setters - sets the values of an object of type Time//
    void setHour(int new_hour);
    void setMinutes(int new_minutes);

    //Convert to string//
    string convertTimeToString();

    //Convert from string to time//
    Time convertStringToTime(string string);

    //Equal//
    bool operator==(Time& time);

    //Read//
    void readTime();

};


//-------------------------------------------------------Movie-------------------------------------------------------//
class Movie
{
private:
    string title;
    string genre;
    int year_of_release;
    Time time_of_projection;
    string location_of_projection;
    string trailer;


public:
    //Contructors - creates an object of class Movie
    Movie(const string& title, const string& genre, const int& year_of_release, const Time& time_of_projection, const string& location_of_projection, const string& trailer);
    Movie(const string& title) : title(title), genre(""), year_of_release(0), time_of_projection{ 0, 0 }, location_of_projection(""), trailer(""){}
    Movie() : title(""), genre(""), year_of_release(0), time_of_projection{ 0, 0 }, location_of_projection(""), trailer(""){}

    //Getters - returns the attributes of an object of class Movie
    string getTitle();
    string getGenre();
    int getYearOfRelease();
    Time getTimeOfProjection();
    string getLocationOfProjection();
    string getTrailer();

    //Setters - sets the values of an object of class Movie
    void setTitle(string new_title);
    void setGenre(string new_genre);
    void setYearOfRelease(int new_year_of_release);
    void setTimeOfProjection(Time new_time_of_projection);
    void setLocationOfProjection(string new_location_of_projection);
    void setTrailer(string new_trailer);

    //Equal - rewrites the operator "==" to verify if two movies are equal (two movies are equal if they have the same title)
    bool operator == (Movie movie) { return this->title == movie.getTitle(); }
    bool operator == (Movie* movie) {return this->title == movie->getTitle();}

    //Convert to string - converts an object of class Movie to string so it can be printed
    string convertMovieToString();

    //Convert to string for Users - returns a string with all the attributes of a movie except the trailer
    string convertMovieToStringForUsers();

    //write - rewrites the ostream operator for a movie
//	friend std::ostream& operator<< (std::ostream& out, Movie& movie);
};

//std::ostream& operator<< (std::ostream& out, Movie& movie)
//{
//	out << "Title: " + movie.getTitle() + "\nGenre: " + movie.getGenre() + "\nYear of release: " + std::to_string(movie.getYearOfRelease()) + "\nTime of projection: " + movie.getTimeOfProjection().convertTimeToString() + "\nLocation of projection: " + movie.getLocationOfProjection() + "\nTrailer: " + movie.getTrailer() + "\n\n";
//	return out;
//}


#endif // DOMAIN_H
