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

#ifndef CLSERVER_H
#define CLSERVER_H

#include <QObject>
#include <QTcpServer>

#include "clServerResponder.h"

class clServer : public QObject
{
    Q_OBJECT
public:
    explicit clServer(QObject *parent = nullptr);
    ~clServer();
    void exec(int port);

signals:

public slots:
    void newConnection();
    void readyRead();
    void stateChanged(QAbstractSocket::SocketState state);
private:
    QTcpServer * server = nullptr;
    QTcpSocket * socket = nullptr;
    clServerResponder * responder;

};

#endif // CLSERVER_H
