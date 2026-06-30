#include "LoginView.h"
#include "ui_loginview.h"
#include <qwidget.h>

LoginView::LoginView(QWidget *parent) : QWidget(parent), ui(new Ui::LoginView) {
    ui->setupUi(this);
}

LoginView::~LoginView() {
    delete ui;
}
