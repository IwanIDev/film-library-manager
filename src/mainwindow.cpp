#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  resize(800, 600);
  setWindowTitle("Test Qt 6 Application");
}

// No destructor set
MainWindow::~MainWindow() {}
