#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const std::string &title) : QMainWindow(parent) {
    resize(800, 600);
    setWindowTitle(title.c_str());
}

// No destructor set
MainWindow::~MainWindow() {}
