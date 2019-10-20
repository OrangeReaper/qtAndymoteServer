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
 * File:   clStopSending.cpp
 * Author: andy
 * 
 * Created on 09 August 2018, 10:00
 */

#include "clStopSending.h"

clStopSending::clStopSending() {
}

clStopSending::clStopSending(const clStopSending& orig) {
}

clStopSending::~clStopSending() {
}
bool clStopSending::getResponse(QJsonObject &jReply, QJsonObject &jLircKey){
    QString device = jLircKey["device"].toString();//.at("device");
    QString function = jLircKey["keyFunction"].toString();//.at("keyFunction");
    if (!lirc_stop_sending(device.toStdString(), function.toStdString())){
        onError(jReply, "Stop Sending Failed");
    } 
    return false;

}

