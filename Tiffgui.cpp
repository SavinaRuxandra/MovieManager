#include "Tiffgui.h"
#include "Tiffgui.h"

TiffGUI::TiffGUI(Service* service, QWidget *parent) : QMainWindow(parent)
{
    this->service = service;
    this->service->loadMoviesFromFile();
    this->setWindowTitle("Movies");
    this->setMinimumSize(QSize(500, 200));
    QWidget *addW = createCentralWidget();
    this->setCentralWidget(addW);
}

QWidget* TiffGUI::createCentralWidget()
{
    QWidget* widget = new QWidget(this);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();

    //left layout
    QLabel* title1 = new QLabel("Movies");
    title1->setAlignment(Qt::AlignHCenter);
    moviesList = new QListWidget();
    this->moviesList->addItem(QString::fromStdString(this->service->getMovieRepository()->getMovies()[0].convertMovieToString()));
    QWidget* moviesButtons = this->addMoviesButtons();

    leftLayout->addWidget(title1);
    leftLayout->addWidget(moviesList);
    leftLayout->addWidget(moviesButtons);

    //middle layout
    this->saveButton = new QPushButton(">");
    connect(saveButton, SIGNAL(pressed()), this, SLOT(saveToWatchListSlot()));

    //right layout
    QLabel* title2 = new QLabel("WatchList");
    title2->setAlignment(Qt::AlignHCenter);
    watchList = new QListWidget();
    this->showWatchList();
    QWidget* watchListButtons = this->addWatchListButtons();

    rightLayout->addWidget(title2);
    rightLayout->addWidget(watchList);
    rightLayout->addWidget(watchListButtons);

    //main layout
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(saveButton);
    mainLayout->addLayout(rightLayout);
    mainLayout->setMargin(20);
    widget->setLayout(mainLayout);

    //combination of keys
    shortcutUndo = new QShortcut(QKeySequence(tr("Ctrl+x")),this,SLOT(undoSlot()));
    shortcutRedo = new QShortcut(QKeySequence(tr("Ctrl+z")),this,SLOT(redoSlot()));

    return widget;
}

QWidget *TiffGUI::addMoviesButtons()
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout();
    QGridLayout* firstDivision = new QGridLayout();
    QGridLayout* secondDivision = new QGridLayout();
    this->prevButton = new QPushButton{"<"};
    this->prevButton->setMaximumWidth(28);
    this->nextButton = new QPushButton{">"};
    this->nextButton->setMaximumWidth(28);
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->updateButton = new QPushButton{"Update"};

    firstDivision->setColumnStretch(2, 1);
    firstDivision->addWidget(this->prevButton, 1, 1);
    firstDivision->addWidget(this->nextButton, 1, 3);

    connect(prevButton, SIGNAL(pressed()), this, SLOT(showPrevMovieSlot()));
    connect(nextButton, SIGNAL(pressed()), this, SLOT(showNextMovieSlot()));

    QSpacerItem* space = new QSpacerItem(1, 10);

    secondDivision->addWidget(this->addButton, 1, 1);
    secondDivision->addWidget(this->deleteButton, 1, 2);
    secondDivision->addWidget(this->updateButton, 1, 3);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addInMovieListSlot()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteFromMovieListSlot()));
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateFromMovieListSlot()));

    layout->addLayout(firstDivision);
    layout->addItem(space);
    layout->addLayout(secondDivision);

    widget->setLayout(layout);
    return widget;
}

QWidget *TiffGUI::addWatchListButtons()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout();
    this->playTrailerButton = new QPushButton("Play");
    this->deleteWhlButton = new QPushButton("Delete");

    connect(deleteWhlButton, SIGNAL(pressed()), this, SLOT(deleteFomWhlSlot()));
    connect(playTrailerButton, SIGNAL(pressed()), this, SLOT(playTrailerSlot()));

    layout->addWidget(playTrailerButton);
    layout->addWidget(deleteWhlButton);

    widget->setLayout(layout);
    return widget;
}

void TiffGUI::showPrevMovieSlot()
{
    this->moviesList->clear();
    if(this->posMovie == 0)
        this->posMovie = int(this->service->getMovieRepository()->getMovies().size()) - 1;
    else
        this->posMovie--;
    Movie movie =  this->service->getMovieRepository()->getMovies()[this->posMovie];
    this->moviesList->addItem(QString::fromStdString(movie.convertMovieToString()));
}

void TiffGUI::showNextMovieSlot()
{
    this->moviesList->clear();
    if(this->posMovie == int(this->service->getMovieRepository()->getMovies().size()) - 1)
        this->posMovie = 0;
    else
        this->posMovie++;
    Movie movie =  this->service->getMovieRepository()->getMovies()[this->posMovie];
    this->moviesList->addItem(QString::fromStdString(movie.convertMovieToString()));
}

void TiffGUI::addInMovieListSlot()
{
    Time time{};
    add_widget = new QWidget();
    add_widget->setWindowTitle("Add movie");
    add_widget->setMinimumSize(QSize(300, 200));
    add_widget->setMaximumSize(QSize(600, 700));

    QFormLayout* layout = new QFormLayout();

    QLabel* comment = new QLabel("Enter movie:");

    this->title = new QLineEdit();
    this->genre = new QLineEdit();
    this->yearOfRelease = new QLineEdit();
    this->timeOfProjection = new QLineEdit();
    this->locationOfProjection = new QLineEdit();
    this->trailer = new QLineEdit();

    layout->addWidget(comment);
    layout->addRow("Title", title);
    layout->addRow("Genre", genre);
    layout->addRow("Year of release", yearOfRelease);
    layout->addRow("Time of projection", timeOfProjection);
    layout->addRow("Location of projection", locationOfProjection);
    layout->addRow("Trailer", trailer);

    this->finishAddButton = new QPushButton("ADD");
    QObject::connect(finishAddButton, &QPushButton::clicked, [&]()
    {
        try{
            this->service->addMovieInMovies(title->text().toStdString(),genre->text().toStdString(), stoi(yearOfRelease->text().toStdString()), time.convertStringToTime(timeOfProjection->text().toStdString()), locationOfProjection->text().toStdString(), trailer->text().toStdString());
            add_widget->close();
        }catch(...){raiseError("Invalid data");}

    });
    layout->addWidget(finishAddButton);

    add_widget->setLayout(layout);
    add_widget->show();

}

void TiffGUI::deleteFromMovieListSlot()
{
    if(this->moviesList->currentRow() == -1)
        this->raiseError("Click on the movie");
    else
    {
        auto movie = this->moviesList->currentItem()->text().toStdString();
        movie.erase(0, movie.find(" ") + 1);
        movie = movie.substr(0, movie.find("\n"));
        this->service->deleteMovieFromMovies(movie);
        this->posMovie--;
        this->showNextMovieSlot();
    }
}

void TiffGUI::updateFromMovieListSlot()
{
    Time time{};
    this->updateWidget = new QWidget();
    updateWidget->setWindowTitle("Update movie");
    updateWidget->setMinimumSize(QSize(350, 250));
    updateWidget->setMaximumSize(QSize(600, 700));

    QFormLayout* layout = new QFormLayout();

    QLabel* comment = new QLabel("Enter movie:");

    this->title = new QLineEdit();
    this->genre = new QLineEdit();
    this->yearOfRelease = new QLineEdit();
    this->timeOfProjection = new QLineEdit();
    this->locationOfProjection = new QLineEdit();
    this->trailer = new QLineEdit();

    layout->addWidget(comment);
    layout->addRow("Genre", genre);
    layout->addRow("Year of release", yearOfRelease);
    layout->addRow("Time of projection", timeOfProjection);
    layout->addRow("Location of projection", locationOfProjection);
    layout->addRow("Trailer", trailer);

    this->finishUpdateButton = new QPushButton("UPDATE");
    QObject::connect(finishUpdateButton, &QPushButton::clicked, [&]()
    {
        try{
            if(this->moviesList->currentRow() == -1)
            {
                this->raiseError("Click on the movie");
                return;
            }
            auto title = this->moviesList->currentItem()->text().toStdString();
            title.erase(0, title.find(" ") + 1);
            title = title.substr(0, title.find("\n"));
            this->service->updateMovieInMovies(title, genre->text().toStdString(), stoi(yearOfRelease->text().toStdString()), time.convertStringToTime(timeOfProjection->text().toStdString()), locationOfProjection->text().toStdString(), trailer->text().toStdString());
            moviesList->clear();
            moviesList->addItem(QString::fromStdString(this->service->getMovieRepository()->getMovies()[posMovie].convertMovieToString()));
            updateWidget->close();
            moviesList->setCurrentRow(0);
        }catch(...){raiseError("Invald data");}

    });
    layout->addWidget(finishUpdateButton);

    updateWidget->setLayout(layout);
    updateWidget->show();
}

void TiffGUI::saveToWatchListSlot()
{
    this->watchList->clear();
    //add
    Movie movie =  this->service->getMovieRepository()->getMovies()[this->posMovie];
    if(this->service->getMovieRepository()->addInWatchList(movie) == 0)
        this->raiseError("Movie already added");
    //show
    for(auto movie : this->service->getMovieRepository()->getWatchList())
        this->watchList->addItem(QString::fromStdString(movie.convertMovieToStringForUsers()));
}

void TiffGUI::deleteFomWhlSlot()
{
    if(this->watchList->currentRow() == -1)
        this->raiseError("Click on a movie");
    else
        {
        auto movie = this->watchList->currentItem()->text().toStdString();
        movie.erase(0, movie.find(" ") + 1);
        movie = movie.substr(0, movie.find("\n"));
        this->service->deleteMovieFromWatchList(movie);
        this->showWatchList();
    }
}

void TiffGUI::playTrailerSlot()
{
    auto index = watchList->currentRow();
    QDesktopServices::openUrl(QUrl(this->service->getMovieRepository()->getWatchList()[index].getTrailer().c_str()));
}

void TiffGUI::undoSlot()
{
    if(this->service->getUndo()->empty())
        this->raiseError("No more undo");
    else
    {
        this->service->callUndo();
        showWatchList();
    }
}

void TiffGUI::redoSlot()
{
    if(this->service->getRedo()->empty())
        this->raiseError("No more redo");
    else
    {
        this->service->callRedo();
        showWatchList();
    }
}

void TiffGUI::showWatchList()
{
    this->watchList->clear();
    for(auto movie : this->service->getMovieRepository()->getWatchList())
        this->watchList->addItem(QString::fromStdString(movie.convertMovieToStringForUsers()));
}

void TiffGUI::raiseError(string error)
{
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Error");
    msg->setText(QString::fromStdString(error));
    msg->show();
}
