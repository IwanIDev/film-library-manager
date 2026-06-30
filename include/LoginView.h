#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <qtmetamacros.h>
#include <qwidget.h>
namespace Ui {
    class LoginView;
}

class LoginView : public QWidget {
    Q_OBJECT

    public:
        explicit LoginView(QWidget *parent = nullptr);
        ~LoginView();

    private:
        Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
