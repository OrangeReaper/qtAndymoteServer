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
 * File:   clGetRemotesResponder.cpp
 * Author: andy
 * 
 * Created on 14 July 2018, 15:58
 */

#include "clGetRemotesResponder.h"
#include "constants.h"
#include "utils.h"
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <iterator>

#include <QJsonArray>
#include <QDir>

clGetRemotesResponder::clGetRemotesResponder() {
}

clGetRemotesResponder::clGetRemotesResponder(const clGetRemotesResponder& orig) {
}

clGetRemotesResponder::~clGetRemotesResponder() {
}

void clGetRemotesResponder::getResponse(QJsonObject &jReply){
    //std::vector<std::string> fileList;
    QJsonArray jRemotes;

    QDir directory(lircDir);
    QStringList files = directory.entryList(QStringList() << "*.lircd.conf",QDir::Files);
    foreach(QString file, files) {
        file.remove(".lircd.conf");
        jRemotes.push_back(file);
    }

    
/*    read_directory(lircDir, fileList);
    for(auto &value: fileList) {
        if (stringContains(value, "lircd.conf")){
            if (!stringContains(value, "devinput")){
                value = value.substr(0,value.length()-11); //remove '.lircd.conf'
                jRemotes.push_back(value);
            }
        }
    }*/
    if (jRemotes.size() > 0) {
        jReply["remotes"]=jRemotes;
    } else {
        onError(jReply, "lirc has no remotes");
    }
    
    
}


 



