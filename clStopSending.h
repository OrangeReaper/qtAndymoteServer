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
 * File:   clStopSending.h
 * Author: andy
 *
 * Created on 09 August 2018, 10:00
 */

#ifndef CLSTOPSENDING_H
#define CLSTOPSENDING_H

#include "utils.h"

class clStopSending {
public:
    clStopSending();
    clStopSending(const clStopSending& orig);
    virtual ~clStopSending();
    static bool getResponse(QJsonObject &jReply, QJsonObject &jLircKey);
private:

};

#endif /* CLSTOPSENDING_H */

