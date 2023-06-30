#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

class ServerConnection;

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void onLoginSuccess(const QString &message);
    void onLoginError(const QString &errorMessage);

    void on_pushButton_clicked();

private:
    Ui::LoginPage *ui;
    ServerConnection *m_serverConnection;
};

#endif // LOGINPAGE_H

