/*
 * Copyright (C) 2013  Christophe De Wagter
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include "fireswarm_communication.h"

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int sim_uart_p = 0;


void fireswarm_payload_link_init(void)
{
  sim_uart_p = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);  
  if (sim_uart_p == -1)
  {
    perror("OpenPort failed");
  }
  else
  {
    struct termios options;
    
    fcntl(sim_uart_p, F_SETFL, 0);
    fcntl(sim_uart_p, F_SETFL, FNDELAY);
    
    tcgetattr(sim_uart_p, &options);
    cfsetispeed(&options, B57600);
    cfsetospeed(&options, B57600);
    options.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(sim_uart_p, TCSANOW, &options); 
  }
}

uint8_t fsw_crc = 0;

void fireswarm_payload_link_start(void)
{
  fsw_crc = 0;
}

void fireswarm_payload_link_crc(void)
{
  int n = write(sim_uart_p, &fsw_crc, 1);
  if (n < 0)
  {
    printf("Write Failed");
  }
}


void fireswarm_payload_link_transmit(uint8_t* buff, int size)
{
  for (int i=0; i<size;i++) fsw_crc += buff[i];
  
  int n = write(sim_uart_p, buff, size);
  if (n < 0)
  {
    printf("Write Failed");
  }
}

int fireswarm_payload_link_has_data(void)
{
  int bytes;
  ioctl(sim_uart_p, FIONREAD, &bytes);
  return bytes;
}

char fireswarm_payload_link_get(void)
{
  char c;
  int ret = read(sim_uart_p, &c, 1);
  if (ret > 0)
  {
    fprintf(stderr,"%x ",(uint8_t)c);
    return c;
  }
  else
    printf("read(1)_error\n");
  return 0;
}