/*
Show_dump 0.1.1a

    Copyright 2004,2005,2006 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl.txt

This function, optimized for performace, shows the hex dump of a buffer and
places it in a stream

Usage:
        show_dump(buffer, buffer_length, stdout);
        show_dump(buffer, buffer_length, fd);
*/

#include <string.h>



void show_dump(unsigned char *data, unsigned int len);

