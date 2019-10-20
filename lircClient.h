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
 * File:   lircClient.h
 * Author: andy
 *
 * Created on 01 August 2018, 14:04
 */

#ifndef LIRCCLIENT_H
#define LIRCCLIENT_H

#include "/usr/include/lirc/lirc_client.h"


//static int mylirc_send_one(int fd, const char* remote, const char* keysym)
//  {
//          int r;
//          lirc_cmd_ctx command;
//  
//          r = lirc_command_init(&command, "SEND_ONCE %s %s\n", remote, keysym);
//          if (r != 0)
//                  return EMSGSIZE;
//          do
//                  r = lirc_command_run(&command, fd);
//          while (r == EAGAIN);
//          return r;
//  }

static int lirc_send_start (int fd, const char* remote, const char* keysym)
  {
          int r;
          lirc_cmd_ctx command;
  
          r = lirc_command_init(&command, "SEND_START %s %s\n", remote, keysym);
          if (r != 0)
                  return EMSGSIZE;
          do
                  r = lirc_command_run(&command, fd);
          while (r == EAGAIN);
          return r;
  }
static int lirc_send_stop (int fd, const char* remote, const char* keysym)
  {
          int r;
          lirc_cmd_ctx command;
  
          r = lirc_command_init(&command, "SEND_STOP %s %s\n", remote, keysym);
          if (r != 0)
                  return EMSGSIZE;
          do
                  r = lirc_command_run(&command, fd);
          while (r == EAGAIN);
          return r;
  }


#endif /* LIRCCLIENT_H */

