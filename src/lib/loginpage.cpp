#include "loginpage.h"
#include "./ui/ui_loginpage.h"
#include "mainwindow.h"
#include "serverconnection.h"

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    // Create an instance of ServerConnection
    m_serverConnection = new ServerConnection(this);

    // Connect the loginSuccess signal to a slot in LoginPage
    connect(m_serverConnection, &ServerConnection::loginSuccess, this, &LoginPage::onLoginSuccess);

    // Connect the loginError signal to a slot in LoginPage
    connect(m_serverConnection, &ServerConnection::loginError, this, &LoginPage::onLoginError);
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::onLoginSuccess(const QString &message)
{
    // Crea una instancia de la ventana principal
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

    // Cierra la ventana de inicio de sesión
    close();
}


void LoginPage::onLoginError(const QString &errorMessage)
{
    // Show an error message
    qDebug() << "Error:" << errorMessage;
}




void LoginPage::on_pushButton_clicked()
{
    QString username = ui->txtUser->text();
    QString password = ui->txtPassword->text();

    // Llama al método de inicio de sesión de ServerConnection
    m_serverConnection->login(username, password);
}

