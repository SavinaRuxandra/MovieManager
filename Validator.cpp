#include "Validator.h"

//-------------------------------------------------------Valid-------------------------------------------------------//
void Validator::validMovie(Movie movie)
{
    char error[200] = "";
    if (movie.getTitle() == "")
        strcat(error, "!TITLE EMPTY!\n");
    if (movie.getGenre() == "")
        strcat(error, "!GENRE EMPTY!\n");
    if (movie.getYearOfRelease() < 0)
        strcat(error, "!NOT A VALID YEAR!\n");
    if (movie.getTimeOfProjection().getHour() < 0 || movie.getTimeOfProjection().getHour() > 24 || movie.getTimeOfProjection().getMinutes() < 0 || movie.getTimeOfProjection().getMinutes() > 60)
        strcat(error, "!NOT A VALID TIME!\n");
    if (movie.getLocationOfProjection() == "")
        strcat(error, "!LOCATION EMPTY!\n");
    if (movie.getTrailer() == "")
        strcat(error, "!LOCATION EMPTY!\n");
    if (strlen(error) > 0)
        throw MovieException(error);
}
