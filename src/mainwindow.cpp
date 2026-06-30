#include "mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent, const std::string &title) : QMainWindow(parent) {
    resize(800, 600);
    setWindowTitle(title.c_str());

    // Create central widget and add layout to widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Set up the main layout and stacked layout
    this->mainLayout = new QVBoxLayout();
    centralWidget->setLayout(this->mainLayout);
    this->stackedLayout = new QStackedLayout();
    this->mainLayout->addLayout(this->stackedLayout);
    
    // Hard coded example of starting widget
    // TODO: Replace by setting up the initial widget based on the application state

    QWidget *homeScreen = new QWidget();
    QVBoxLayout *homeLayout = new QVBoxLayout(homeScreen);
    QLabel *homeLabel = new QLabel("Welcome to the Home Screen!");
    homeLabel->setAlignment(Qt::AlignCenter); 
    homeLayout->addWidget(homeLabel);

    this->stackedLayout->addWidget(homeScreen);
}

// No destructor set
MainWindow::~MainWindow() {}
