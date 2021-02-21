#include "Domain.h"
#include <windows.h>
#include <shellapi.h>
#include <sstream>

//-------------------------------------------------------Time-------------------------------------------------------//
//CONSTRUCTORS//
Time::Time(const int& hour, const int& minutes)
{
    this->hour = hour;
    this->minutes = minutes;
}

//GETTERS//
int Time::getHour()
{
    return this->hour;
}

int Time::getMinutes()
{
    return this->minutes;
}


//SETTERS//
void Time::setHour(int new_hour)
{
    this->hour = new_hour;
}

void Time::setMinutes(int new_minutes)
{
    this->minutes = new_minutes;
}


//CONVERT//
string Time::convertTimeToString()
{
    string time;
    if(this->minutes / 10 == 0)
        time = std::to_string(this->hour) + ":0" + std::to_string(this->minutes);
    else
        time = std::to_string(this->hour) + ":" + std::to_string(this->minutes);
    return time;
}

Time Time::convertStringToTime(string str)
{
    string word;
    stringstream s(str);
    getline(s, word, ':');
    this->hour = stoi(word);
    getline(s, word, ':');
    this->minutes = stoi(word);
    return *this;
}


//EQUAL//
bool Time::operator==(Time& duration)
{
    return this->hour == duration.getHour() && this->minutes == duration.getMinutes();
}


//READ//
void Time::readTime()
{
    scanf_s("%d:%d", &this->hour, &this->minutes);
}


//-------------------------------------------------------Movie-------------------------------------------------------//
//CONSTRUCTORS//
Movie::Movie(const string& title, const string& genre, const int& year_of_release, const Time& time_of_projection, const string& location_of_projection, const string& trailer)
{
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->time_of_projection = time_of_projection;
    this->location_of_projection = location_of_projection;
    this->trailer = trailer;
}

//GETTERS//
string Movie::getTitle()
{
    return this->title;
}

string Movie::getGenre()
{
    return this->genre;
}

int Movie::getYearOfRelease()
{
    return this->year_of_release;
}

Time Movie::getTimeOfProjection()
{
    return this->time_of_projection;
}

string Movie::getLocationOfProjection()
{
    return this->location_of_projection;
}

string Movie::getTrailer()
{
    return this->trailer;
}


//SETTERS//
void Movie::setTitle(string new_title)
{
    this->title = new_title;
}

void Movie::setGenre(string new_genre)
{
    this->genre = new_genre;
}

void Movie::setYearOfRelease(int new_year_of_release)
{
    this->year_of_release = new_year_of_release;
}

void Movie::setTimeOfProjection(Time new_time_of_projection)
{
    this->time_of_projection = new_time_of_projection;
}

void Movie::setLocationOfProjection(string new_location_of_projection)
{
    this->location_of_projection = new_location_of_projection;
}

void Movie::setTrailer(string new_trailer)
{
    this->trailer = new_trailer;
}


//CONVERT TO STRING//
string Movie::convertMovieToString()
{
    string movie;
    movie = "Title: " + this->title + "\nGenre: " + this->genre + "\nYear of release: " + std::to_string(this->year_of_release) + "\nTime of projection: " + this->time_of_projection.convertTimeToString() + "\nLocation of projection: " + this->location_of_projection + "\nTrailer: " + this->trailer + "\n";
    return movie;
}

string Movie::convertMovieToStringForUsers()
{
    string movie;
    movie = "Title: " + this->title + "\nGenre: " + this->genre + "\nYear of release: " + std::to_string(this->year_of_release) + "\nTime of projection: " + this->time_of_projection.convertTimeToString() + "\nLocation of projection: " + this->location_of_projection + "\n";
    return movie;
}
