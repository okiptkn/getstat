/*    GNU General Public License v3.0
 *
 *    [getstat] fetch and print status on your dwm bar
 *    Copyright (C) 2018  Restu Purnomo <restu.okky[at]gmail[dot].com>
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define wifi_INTERF     "wlp3s0b1" // wifi interface
#define set_INTERV      60 // getstat update interval 
#define mail_PATH       "/home/okiptkn/.mail/rmail/INBOX/new" // offline mail directory

// requires statuscolors patch, or just removes "\xnn" if your dwm isn't patched yet
#define mpd_PLAYING     "\x01.playing\x05%s-%s"
#define mpd_PAUSED      "\x01.paused\x05%s-%s"
#define mpd_STOPPED     "\x01.mpd\06stopped"
#define mpd_UNAV        "\x01.mpd\x06service\x06unavailable"
#define wifi_ON         "\x01.essid\x05%s"
#define wifi_OFF        "\x01.wifi\x06""disconnected"
#define mail_BOX        "\x01.mail\x05"
#define date_CLK        "\x01.%a\x05%d\x01%B  \x02 %R %Z "
#define clock_UNAV      "\x01.\x06unable\x01toget\x06""dateinfo"

