#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtmetamacros.h>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <string>

/*
* The MainWindow class represents the main window of the Film Library Manager application.
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        /*
         * Constructor for the MainWindow class.
         * @param parent The parent widget (default is nullptr).
         * @param title The title of the window (default is "Film Library Manager").
         */
        MainWindow(QWidget *parent = nullptr, const std::string &title = "Film Library Manager");

        /*
         * Destructor for the MainWindow class.
         */
        ~MainWindow();

    private:
        QVBoxLayout *mainLayout; // Window layout
        QStackedLayout *stackedLayout; // Stacked layout for switching between different views
};

#endif // MAINWINDOW_H
