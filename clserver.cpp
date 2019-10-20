/*
 * Copyright (C) 2019 Andy Bond
 *
 * This file is part of AndyMOTE Server
 *
 * AndyMOTE Server is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 3.0 as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

// Ref: https://riptutorial.com/qt/example/29874/tcp-server

#include "clserver.h"

#include <QEventLoop>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

clServer::clServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer();
    responder = new clServerResponder();
}
clServer::~clServer(){
    delete server;
    delete responder;
}
void clServer::exec(int port){
    QEventLoop loop;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    server->listen(QHostAddress::Any, port);

    loop.exec();

}
void clServer::newConnection(){
    // need to grab the socket
    if (socket==nullptr){
        socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    }
}
void clServer::readyRead(){
    QByteArray received=socket->readAll();
    qDebug() << "AndyMote Received: " << received;
    received.remove(0,8);
    QJsonDocument document = QJsonDocument::fromJson(received);
    QJsonObject jReceived = document.object();//    nlohmann::json::parse(received.toStdString());//(received);
    QByteArray response=responder->getResponse(jReceived).toUtf8();
    socket->write(response);
    socket->flush();
    qDebug() << "AndyMote Sent: " << response;
    socket->waitForBytesWritten(3000);
    socket->close();
}
void clServer::stateChanged(QAbstractSocket::SocketState state){
    if (state == QAbstractSocket::UnconnectedState){
        socket->close();
        socket=nullptr;
    }
}
