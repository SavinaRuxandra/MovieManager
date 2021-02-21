#ifndef TIFFGUI_H
#define TIFFGUI_H

#include "Service.h"

#include <QDebug>
#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QSpacerItem>
#include <QDesktopServices>
#include <QUrl>
#include <QShortcut>

class TiffGUI : public QMainWindow
{
    Q_OBJECT;

public:
    explicit TiffGUI(Service* service, QWidget *parent = nullptr);
signals:

public slots:
    void showPrevMovieSlot();
    void showNextMovieSlot();
    void addInMovieListSlot();
    void deleteFromMovieListSlot();
    void updateFromMovieListSlot();
    void saveToWatchListSlot();
    void deleteFomWhlSlot();
    void playTrailerSlot();
    void undoSlot();
    void redoSlot();

private:
    //attributes
    Service* service;
    int posMovie = 0;
    QWidget* updateWidget;
    QWidget* add_widget;
    QListWidget* moviesList;
    QListWidget* watchList;
    QPushButton* nextButton;
    QPushButton* prevButton;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* saveButton;
    QPushButton* deleteWhlButton;
    QPushButton* playTrailerButton;
    QPushButton* finishAddButton;
    QPushButton* finishUpdateButton;
    QLineEdit* title;
    QLineEdit* genre;
    QLineEdit* yearOfRelease;
    QLineEdit* timeOfProjection;
    QLineEdit* locationOfProjection;
    QLineEdit* trailer;
    QShortcut * shortcutUndo;
    QShortcut * shortcutRedo;
    //functions
    QWidget* createCentralWidget();
    QWidget* addMoviesButtons();
    QWidget* addWatchListButtons();
    QWidget* addWidget();

    void showWatchList();
    void raiseError(string error);
};

#endif // TIFFGUI_H
