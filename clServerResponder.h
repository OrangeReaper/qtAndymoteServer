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
 * File:   clServerResponder.h
 * Author: andy
 *
 * Created on 10 July 2018, 17:29
 */

#ifndef CLSERVERRESPONDER_H
#define CLSERVERRESPONDER_H

//#include <string>

#include <QJsonObject>


class clServerResponder {
public:
    clServerResponder();
    clServerResponder(const clServerResponder& orig);
    virtual ~clServerResponder();
    QString getResponse(QJsonObject jRequest);
private:
    std::string getReplyLength(int length);

};

#endif /* CLSERVERRESPONDER_H */

