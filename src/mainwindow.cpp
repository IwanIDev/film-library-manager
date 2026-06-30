#include "mainwindow.h"
#include "LoginView.h"
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
    
    LoginView *loginView = new LoginView(this);
    this->stackedLayout->addWidget(loginView);
}

// No destructor set
MainWindow::~MainWindow() {}
