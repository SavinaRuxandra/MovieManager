#include "PersistenceEngine.h"
#include <fstream>
#include <sstream>

#include "rapidjson/include/rapidjson/filereadstream.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include "rapidjson/include/rapidjson/ostreamwrapper.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/prettywriter.h"

using namespace rapidjson;

//-------------------------------------------------------CSV-------------------------------------------------------//
vector<Movie> PersistanceEngineFromCSV::load(string filePath)
{
    fstream file;
    Validator valid{};
    string line, attribute;
    vector<string> row;
    vector<Movie> moviesFromCSV;
    Time time_of_projection{};

    ifstream in(filePath);
    if (in.is_open() == false)
        throw NonExistingFileException("\n!The file does not exist!\n");

    file.open(filePath, ios::in);

    getline(file, line);

    while (getline(file, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, attribute, ','))
            row.push_back(attribute);
        Movie movie{ row[0], row[1], stoi(row[2]), time_of_projection.convertStringToTime(row[3]), row[4], row[5] };
        valid.validMovie(movie);
        moviesFromCSV.push_back(movie);
    }
    return moviesFromCSV;
}

void PersistanceEngineFromCSV::save(string filePath, vector<Movie> moviesToCSV)
{
    fstream file;
    file.open(filePath, ios::out | ios::trunc);
    file << "Title, Genre, Year Of Release, Time Of Projection, Location Of Projection, Trailer\n";
    for(auto movie : moviesToCSV)
        file << movie.getTitle() + "," + movie.getGenre() + "," + std::to_string(movie.getYearOfRelease()) + "," + movie.getTimeOfProjection().convertTimeToString() + "," + movie.getLocationOfProjection() + "," + movie.getTrailer() + "\n";
    file.close();
}

//-------------------------------------------------------JSON-------------------------------------------------------//
vector<Movie> PersistanceEngineFromJSON::load(string filePath)
{
    fstream file;
    Validator valid{};
    vector<Movie> moviesFromJSON;
    Time time_of_projection{};

    ifstream in(filePath);
    if (in.is_open() == false)
        throw NonExistingFileException("\n!The file does not exist!\n");

    file.open(filePath, ios::in);

    IStreamWrapper isw{ file };
    Document doc{};
    doc.ParseStream(isw);
    StringBuffer buffer{};
    Writer<StringBuffer> writer{ buffer };
    doc.Accept(writer);
    const std::string jsonStr{ buffer.GetString() };

    for (int i = 0; i < doc["Movies"].GetArray().Size(); i++)
    {
        Movie movie{};
        movie.setTitle(doc["Movies"].GetArray()[i].GetObject()["Title"].GetString());
        movie.setGenre(doc["Movies"].GetArray()[i].GetObject()["Genre"].GetString());
        movie.setYearOfRelease(stoi(doc["Movies"].GetArray()[i].GetObject()["YearOfRelease"].GetString()));
        movie.setTimeOfProjection(time_of_projection.convertStringToTime(doc["Movies"].GetArray()[i].GetObject()["TimeOfProjection"].GetString()));
        movie.setLocationOfProjection(doc["Movies"].GetArray()[i].GetObject()["LocationOfProjection"].GetString());
        movie.setTrailer(doc["Movies"].GetArray()[i].GetObject()["Trailer"].GetString());
        valid.validMovie(movie);
        moviesFromJSON.push_back(movie);
    }

    file.close();
    return moviesFromJSON;
}


void PersistanceEngineFromJSON::save(string filePath, vector<Movie> moviesToJSON)
{
    fstream file;
    StringBuffer s;
    PrettyWriter<StringBuffer> writer(s);
    file.open(filePath, ios::out | ios::trunc);

    writer.StartObject();
    writer.String("Movies");
    writer.StartArray();
    for (auto movie : moviesToJSON)
    {
        writer.StartObject();
        writer.String("Title");
        writer.String(movie.getTitle().c_str());
        writer.String("Genre");
        writer.String(movie.getGenre().c_str());
        writer.String("YearOfRelease");
        writer.String(to_string(movie.getYearOfRelease()).c_str(), to_string(movie.getYearOfRelease()).size());
        writer.String("TimeOfProjection");
        writer.String(movie.getTimeOfProjection().convertTimeToString().c_str(), movie.getTimeOfProjection().convertTimeToString().size());
        writer.String("LocationOfProjection");
        writer.String(movie.getLocationOfProjection().c_str(), movie.getLocationOfProjection().size());
        writer.String("Trailer");
        writer.String(movie.getTrailer().c_str(), movie.getTrailer().size());
        writer.EndObject();
    }
    writer.EndArray();
    writer.EndObject();

    file << s.GetString() << endl;
    file.close();

}
