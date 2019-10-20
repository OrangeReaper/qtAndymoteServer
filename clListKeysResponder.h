/*
 * Copyright (C) 2018 Andy Bond
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

/* 
 * File:   clListKeysResponder.h
 * Author: andy
 *
 * Created on 24 July 2018, 14:58
 */

#ifndef CLLISTKEYSRESPONDER_H
#define CLLISTKEYSRESPONDER_H

#include "constants.h"
#include "utils.h"

#include <sstream>
#include <string>
#include <fstream>

#include <QJsonObject>
#include <QJsonArray>

class clListKeysResponder {
public:
    clListKeysResponder();
    clListKeysResponder(const clListKeysResponder& orig);
    virtual ~clListKeysResponder();
    static void getResponse(QJsonObject &jReply, QString remoteName);
private:
    static bool readUntilLineContains(QTextStream &stream, const QString &searchFor);
    static int readKeys(QTextStream &stream, QJsonArray &jKeys);
    static bool getLine(QTextStream &stream);
    static QString getKeyName();
    static int readRawKeys(QTextStream &stream, QJsonArray &jKeys);
    static QString getRawKeyName();
    static bool lineIsComment();
    static bool isWhitespace(QString strSearch);
    static int find_first_not_of(QString srchStr, QString strNotOf, int start=0);
    static int find_first_of(QString srchStr, QString strOf, int start);
    
};

#endif /* CLLISTKEYSRESPONDER_H */

