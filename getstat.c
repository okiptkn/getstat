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

#include <dirent.h>
#include <linux/wireless.h>
#include <mpd/client.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

#include "config.h"

char *
smprintf(char *fmt, ...) {
	va_list fmtargs;
	char *retr;
	int len;

	va_start(fmtargs, fmt);
	len = vsnprintf(NULL, 0, fmt, fmtargs);
	va_end(fmtargs);

	retr = malloc(++len);
	if(retr == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	va_start(fmtargs, fmt);
	vsnprintf(retr, len, fmt, fmtargs);
	va_end(fmtargs);

	return retr;
}

/* only support for wifi */
char * // discard lan and fix wifi not displaying essid issues
get_net(struct iwreq wreq, int sockfd) {
		char essid[IW_ESSID_MAX_SIZE+1];

		wreq.u.essid.pointer = essid;
		wreq.u.essid.length = sizeof(essid);
		ioctl(sockfd, SIOCGIWESSID, &wreq);

	if (ioctl(sockfd,SIOCGIWESSID, &wreq) == -1) {
        close(sockfd);
		return wifi_OFF;
	}
    
	if (strcmp(essid, "") == 0)
		return wifi_OFF;
    else
		return smprintf (wifi_ON, essid);
}

char *
get_mpd() {
    struct mpd_song * song = NULL;
	const char * title = NULL;
	const char * artist = NULL;
	char * retstr = NULL;
    struct mpd_connection * conn ;
    int cur_state;
    if (!(conn = mpd_connection_new("localhost", 0, 30000)) ||
        mpd_connection_get_error(conn)){
            return mpd_UNAV;
    }
 
    mpd_command_list_begin(conn, true);
    mpd_send_status(conn);
    mpd_send_current_song(conn);
    mpd_command_list_end(conn);

    struct mpd_status* theStatus = mpd_recv_status(conn);

    mpd_response_next(conn);
    song = mpd_recv_song(conn);
        title = smprintf("%s",mpd_song_get_tag(song, MPD_TAG_TITLE, 0));
        artist = smprintf("%s",mpd_song_get_tag(song, MPD_TAG_ARTIST, 0));

    mpd_song_free(song);
    
    cur_state = mpd_status_get_state(theStatus);   
	switch(cur_state) {
		case(MPD_STATE_PLAY):
			retstr = smprintf(mpd_PLAYING, artist, title);
			break;
		case(MPD_STATE_PAUSE):
			retstr = smprintf(mpd_PAUSED, artist, title);
			break;
		default:
			retstr = smprintf(mpd_STOPPED, "mpd is stopped");
			break;
   
            free((char*)title);
            free((char*)artist);
	}
		mpd_response_finish(conn);
		mpd_connection_free(conn);
        return retstr;
}

/* mailbox counter, set your mail_PATH at getstat.h */
char *
get_mail(char *directory, char *label)
{
    /* directory : Maildir path 
    * return label : number_of_new_mails
    */
    
    int n = 0;
    DIR* dir = NULL;
    struct dirent* rf = NULL;

    dir = opendir(directory); /* try to open directory */
    if (dir == NULL)
        perror("");

    while ((rf = readdir(dir)) != NULL) /*count number of file*/
    {
        if (strcmp(rf->d_name, ".") != 0 &&
            strcmp(rf->d_name, "..") != 0)
            n++;
    }
    closedir(dir);

    if (n == 0) 
       return smprintf("");
    else 
       return smprintf("%s%d",label, n);

}

char *
get_time(void) {
	char clock[60];
	time_t current;

	time(&current);
	if(!strftime(clock, sizeof(clock) - 1, date_CLK, localtime(&current)))
		return clock_UNAV;
	return smprintf(clock);
}

void
setstatus(Display *dpy, char *str) {
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

int
main(void) {
	Display *dpy;
	struct iwreq wreq;
	int sockfd, loops = 60;
	char *status, *mpd, *net, *mailbox, *dateclk;

	if(!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "getstat : unable to open display.\n");
		exit(EXIT_FAILURE);
	}

	memset(&wreq, 0, sizeof(struct iwreq));
	snprintf(wreq.ifr_name, sizeof(wreq.ifr_name), wifi_INTERF);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    for(;;sleep(1)) {
		if(++loops > set_INTERV) {
			loops = 0;
			mpd = get_mpd();
			net = get_net(wreq, sockfd);
			dateclk = get_time();
            mailbox = get_mail(mail_PATH, mail_BOX);
		}
		status = smprintf("%s  %s  %s  %s", mpd, net, mailbox, dateclk);
		setstatus(dpy, status);
		free(status);
	}

	free(mpd);
	free(net);
	free(dateclk);
    free(mailbox);
	exit(EXIT_SUCCESS);
}
