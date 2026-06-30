#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr, const std::string &title = "Film Library Manager");
        ~MainWindow();
};

#endif // MAINWINDOW_H
