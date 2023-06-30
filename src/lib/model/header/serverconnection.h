#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit ServerConnection(QObject *parent = nullptr);
    void login(const QString &username, const QString &password);

signals:
    void loginSuccess(const QString &token);
    void loginError(const QString &errorMessage);

private slots:
    void handleNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
};

#endif // SERVERCONNECTION_H
