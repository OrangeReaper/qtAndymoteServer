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
 * File:   requests.h
 * Author: andy
 *
 * Created on 14 July 2018, 16:00
 */

#ifndef REQUESTS_H
#define REQUESTS_H

    // Define SERVER REQUESTS
    const static int TEST_CONNECTION = 0;
    const static int GET_REMOTES = 1;
    const static int LIST_KEYS = 2;
    const static int SEND_SEQ = 3;
    const static int START_SENDING = 4;
    const static int STOP_SENDING = 5;

#endif /* REQUESTS_H */

