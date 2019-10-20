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
 * File:   clListKeysResponder.cpp
 * Author: andy
 * 
 * Created on 24 July 2018, 14:58
 */

#include "clListKeysResponder.h"
#include <QFile>

QString line;
static const QString whitespace = " \t\f\v\n\r";

clListKeysResponder::clListKeysResponder() {
}

clListKeysResponder::clListKeysResponder(const clListKeysResponder& orig) {
}

clListKeysResponder::~clListKeysResponder() {
}
void clListKeysResponder::getResponse(QJsonObject &jReply, QString remoteName){

    QJsonArray jKeys;
    bool fault=true;
    QString path = lircDir + remoteName + ".lircd.conf";

    QFile inFile(path);
    if (inFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inFile);
       if (readUntilLineContains(in,"begin remote")){
           if (readUntilLineContains(in,"flags")){
               if (line.contains("RAW_CODES")){
                   if (readUntilLineContains(in,"begin raw_codes")){
                       fault= !readRawKeys(in, jKeys)>0;
                   }
               } else {
                   if (readUntilLineContains(in,"begin codes")){
                       fault=!readKeys(in, jKeys)>0;
                   }
               }
           }
       }
       if (fault) {
           onError(jReply, "Error in conf file");
       } else {
           jReply["keys"]=jKeys;
       }




 //      while (!in.atEnd())
 //      {
 //         QString line = in.readLine();
 //         ...
 //      }
 //      inputFile.close();
 //   }






/*

    std::string path = lircDir.toStdString() + remoteName.toStdString() + ".lircd.conf";
    //std::ifstream infile(path);
    std::fstream infile;
    //std::cout << "Path: " << path << std::endl;
    infile.open (path, std::fstream::in);
    
    if (readUntilLineContains(infile,"begin remote")){
        if (readUntilLineContains(infile,"flags")){
            if (stringContains(line, "RAW_CODES")){
                if (readUntilLineContains(infile,"begin raw_codes")){
                    fault= !readRawKeys(infile, jKeys)>0;
                }
            } else {
                if (readUntilLineContains(infile,"begin codes")){
                    fault=!readKeys(infile, jKeys)>0;
                }
            }
        }
    } 
    if (fault) {
        onError(jReply, "Error in conf file"); 
    } else {
        jReply["keys"]=jKeys;
    }
    infile.close();
       
*/
    }
}
bool clListKeysResponder::readUntilLineContains(QTextStream &stream, const QString &searchFor){
    bool found=false;
    while (getLine(stream)){
        
        if (line.contains(searchFor)) {
            found=true;
            break;
        }
    }
    return found;
}

int clListKeysResponder::readKeys(QTextStream &stream, QJsonArray &jKeys){
    int keysFound=0;
    while (getLine(stream)){
         if (line.contains("end codes")){
            break;
        } else {
            QString keyName=getKeyName();
            if (keyName.length() != 0){
                jKeys.push_back(keyName);
                keysFound++;
            }
        }
    }
    return keysFound;
}
int clListKeysResponder::readRawKeys(QTextStream &stream, QJsonArray &jKeys){
    int keysFound=0;
    while (getLine(stream)){
        if (line.contains("end raw_codes")) {
            break;
        } else {
            if (line.contains("name ")){
                QString keyName=getRawKeyName();
           
                if (keyName.length() != 0){
                    jKeys.push_back(keyName);
                    keysFound++;
                }
            }
        }
    }
    return keysFound;
}
bool clListKeysResponder::getLine(QTextStream &stream){
    while (!stream.atEnd())
    {
       line = stream.readLine();
       if (!lineIsComment()) return true;
    }
    return false;


//    do {
//        std::getline(stream, line);
//    } while ((line.length()==0 || lineIsComment()) && (!stream.eof()));
//    //std::cout << "Line: " << line << std::endl;
//    return (!stream.eof());
}
bool clListKeysResponder::lineIsComment() {
    if (line.length()==0) return true;
    return isWhitespace(line);
}
bool clListKeysResponder::isWhitespace(QString strSearch)
{
  //return true if text not contains any of char in chars
    foreach (QChar chr, strSearch) {
       if (!whitespace.contains(chr)) return false;
    }
    return true;
}
int clListKeysResponder::find_first_not_of(QString srchStr, QString strNotOf, int start){
    if (start > srchStr.length()) return srchStr.length()+1;

    for(int i = start; i< srchStr.length(); i++)
    {
        if (!strNotOf.contains(srchStr.at(i))) return i;
    }
    return srchStr.length()+1;
}
int clListKeysResponder::find_first_of(QString srchStr, QString strOf, int start){
    if (start > srchStr.length()) return srchStr.length()+1;

    for(int i = start; i< srchStr.length(); i++)
    {
        if (strOf.contains(srchStr.at(i))) return i;
    }
    return srchStr.length()+1;
}
QString clListKeysResponder::getKeyName(){
    
    int start = find_first_not_of(line, whitespace);
    //std::cout << "Start: " << start << std::endl;
    if (start > line.length()) return "";
    int end = find_first_of(line, whitespace, start);
    //std::cout << "end: " << end << std::endl;
    if (end > line.length()) return "";
    //std::cout << "Key: '" << line.substr(start, end-start) << "'" <<std::endl;
    if (end > start) return line.mid(start, end-start);
    return "";
    
}
QString clListKeysResponder::getRawKeyName(){
    int ptr=line.indexOf("name", 0, Qt::CaseInsensitive);
    if (ptr == -1) return ""; //not found
    
    ptr=ptr+5;
    return line.right(line.length()-ptr);
    
}
