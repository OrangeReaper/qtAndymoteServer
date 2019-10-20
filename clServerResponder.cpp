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
 * File:   clServerResponder.cpp
 * Author: andy
 * 
 * Created on 10 July 2018, 17:29
 */

//#include <vector>

#include "clServerResponder.h"
#include "requests.h"
#include "clGetRemotesResponder.h"
#include "clListKeysResponder.h"
#include "clKeySeqResponder.h"
#include "clStartSending.h"
#include "clStopSending.h"
#include "utils.h"

#include <QJsonDocument>


clServerResponder::clServerResponder() {
}

clServerResponder::clServerResponder(const clServerResponder& orig) {
}

clServerResponder::~clServerResponder() {
} 

QString clServerResponder::getResponse(QJsonObject jRequest){

   QJsonObject jReply;
   static bool sending=false;
   static QJsonObject jLircKey;
   
   try {
        jReply["fault"] = false;
        
        int request = jRequest["id"].toInt();// .at("id").get<int>();
        if (sending && request!=STOP_SENDING){
            clStopSending::getResponse(jReply, jLircKey);
            onError(jReply, "Unexpected request received, 'Stop Sending' was Expected");
        } else {
            switch (request){
                case TEST_CONNECTION: {
                    break;
                }
                case GET_REMOTES: {
                    clGetRemotesResponder::getResponse(jReply);
                    break;
                }
                case LIST_KEYS: {
                    QString remoteName = jRequest["payload"].toString();//.at("payload").get<std::string>();
                    clListKeysResponder::getResponse(jReply, remoteName);
                    break;
                }
                case SEND_SEQ: {
                    QJsonArray jKeySeq = jRequest["keySeq"].toArray();// .at("keySeq").get<nlohmann::json>();
                    clKeySeqResponder::getResponse(jReply, jKeySeq);
                    break;
                }
                case START_SENDING: {
                    //get jLircKey;
                    jLircKey = jRequest["lircKey"].toObject();//.at("lircKey").get<nlohmann::json>();
                    sending=clStartSending::getResponse(jReply, jLircKey);
                    break;
                }
                case STOP_SENDING: {
                    sending=clStopSending::getResponse(jReply, jLircKey);
                    break;
                }
                default: {
                    onError(jReply, "Invalid Request");

                    break;
                }
            }
        }
        

        
        
        
    } catch (...) {
        // request is not valid JSON
        onError(jReply,"Error in JSON Request");
    }  
    
    QJsonDocument doc(jReply);
    QString strReply(doc.toJson(QJsonDocument::Compact));

    QString replyLength = QString("%1").arg(strReply.length(), 8, 16, QChar('0'));

    QString result = replyLength + strReply;
    
    return result;
}
std::string clServerResponder::getReplyLength(int length){
    std::string result;
    std::stringstream ss;
    ss << std::hex << length;
    ss >> result;
    for (auto & c: result) c = toupper(c);
    while (result.length() < 8 ) result = "0" + result;
    
    return result;
    
}

