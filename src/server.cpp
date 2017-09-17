/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QHostAddress>
#include <QWebSocket>
#include <QWebSocketServer>

#include "server.h"

Server::Server(QObject *parent)
    : QObject(parent),
      mServer(new QWebSocketServer("", QWebSocketServer::NonSecureMode, this)),
      mSocket(nullptr)
{
    connect(mServer, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
}

Server::~Server()
{
    if (mSocket) {
        mSocket->deleteLater();
    }
}

bool Server::start(quint16 port)
{
    return mServer->listen(QHostAddress::Any, port);
}

void Server::stop()
{
    mServer->close();
}

void Server::onNewConnection()
{
    QWebSocket *socket = mServer->nextPendingConnection();

    // Abort if there is already an active connection
    if (mSocket) {
        socket->abort();
        socket->deleteLater();
        return;
    }

    connect(socket, &QWebSocket::disconnected, this, &Server::onDisconnected);
    connect(socket, &QWebSocket::textMessageReceived, this, &Server::onTextMessageReceived);

    mSocket = socket;
}

void Server::onDisconnected()
{
    mSocket->deleteLater();
    mSocket = nullptr;
}

void Server::onTextMessageReceived(const QString &message)
{
    //...
}
