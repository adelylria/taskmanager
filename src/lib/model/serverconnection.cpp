#include "./header/serverconnection.h"
#include <QJsonDocument>
#include <QJsonObject>

ServerConnection::ServerConnection(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &ServerConnection::handleNetworkReply);
}

void ServerConnection::login(const QString &username, const QString &password)
{
    QUrl url("http://192.168.1.68:3000/login");

    // Create the JSON object to send in the request
    QJsonObject jsonObject;
    jsonObject["username"] = username;
    jsonObject["password"] = password;

    // Create the JSON document from the jsonObject
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // Configure the HTTP POST request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send the HTTP POST request
    QNetworkReply *reply = m_networkManager->post(request, jsonData);
}

void ServerConnection::handleNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Read the JSON response
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonDoc.object();

        // Get the server message from the JSON response
        QString serverMessage = jsonObject["message"].toString();

        // Emit the loginSuccess signal with the server message
        emit loginSuccess(serverMessage);
    } else {
        // Error while making the HTTP request
        QString errorMessage = reply->errorString();

        // Emit the loginError signal with the error message
        emit loginError(errorMessage);
    }

    // Clean up the QNetworkReply object
    reply->deleteLater();
}

