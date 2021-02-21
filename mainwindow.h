#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Service.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Service s, QWidget *parent = nullptr);
    ~MainWindow();

private:

    QWidget* m_qwidget;
    QHBoxLayout* m_layout;
    QLabel* m_label;
    QLineEdit *m_input;
    QPushButton *m_saveBtn;

    Service m_service;
    Ui::MainWindow *ui;


public slots:
    void onSaveBtnClicked(bool checked = false);
};

#endif // MAINWINDOW_H
