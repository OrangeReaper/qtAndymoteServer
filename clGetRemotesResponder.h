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
 * File:   clGetRemotesResponder.h
 * Author: andy
 *
 * Created on 14 July 2018, 15:58
 */

#ifndef CLGETREMOTESRESPONDER_H
#define CLGETREMOTESRESPONDER_H

#include <QJsonObject>

class clGetRemotesResponder {
public:
    clGetRemotesResponder();
    clGetRemotesResponder(const clGetRemotesResponder& orig);
    virtual ~clGetRemotesResponder();
    static void getResponse(QJsonObject &jReply);
private:


};

#endif /* CLGETREMOTESRESPONDER_H */

