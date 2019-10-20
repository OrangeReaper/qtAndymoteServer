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
 * File:   utils.h
 * Author: andy
 *
 * Created on 14 July 2018, 18:36
 */

#ifndef UTILS_H
#define UTILS_H

//#include "boost/filesystem.hpp"
#include "lircClient.h"

#include <QString>
#include <QJsonObject>
#include <QDebug>

static int fd=-1;

static void lirc_init(){
    if (fd==-1) fd = lirc_get_local_socket(NULL, 0);
}

static void onError( QJsonObject &jReply, const QString &errorResponse){
    jReply["fault"] = true;
    jReply["error"] = errorResponse;
    qDebug() << "Error: "<< errorResponse << "\n";
}

static bool lirc_send_key(std::string device, std::string key){
    lirc_init();
    return (lirc_send_one(fd, device.c_str(), key.c_str()) != -1) ;
}
static bool lirc_start_sending(std::string device, std::string key){
    lirc_init();
    return (lirc_send_start(fd, device.c_str(), key.c_str()) != -1) ;
}
static bool lirc_stop_sending(std::string device, std::string key){
    lirc_init();
    return (lirc_send_stop(fd, device.c_str(), key.c_str()) != -1) ;
}


#endif /* UTILS_H */

