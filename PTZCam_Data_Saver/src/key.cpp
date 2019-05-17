/*
 * key.cpp
 *
 *  Created on: 24 May 2018
 *      Author: Yun Wu
 */

#include "key.hpp"
#include <termios.h>

void reset_terminal_mode();
void set_conio_terminal_mode();

key::key(){
	set_conio_terminal_mode();
}

key::~key(){

}

struct termios orig_termios;

// reset the ternimal
void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

// set the termial mode
void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

// check if there is key hit
bool key::kbhit()
{
    struct timeval tv;
    tv.tv_sec = 0L;
    tv.tv_usec = 0L;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    if(select(1, &fds, NULL, NULL, &tv)){
    	this->hit = true;
    }else{
    	this->hit = false;
    }
    return this->hit;
}

// capture the hit key char value
int key::getch_c()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        this->k = r;
    } else {
    	this->k = (int)c;
    }
    return this->k;
}

/*
void example()
{
    set_conio_terminal_mode();

    int ch;
    while (!kbhit()) {
        // do some work
    }
    if ((ch=getch_c()) == '\033') { // if the first value is esc
    	ch=getch_c(); // skip the [
        switch((ch=getch_c())) { // the real value
            case 'A':
                // code for arrow up
            	printf("up!\n");
                break;
            case 'B':
                // code for arrow down
            	printf("down!\n");
                break;
            case 'C':
                // code for arrow right
            	printf("right!\n");
                break;
            case 'D':
                // code for arrow left
            	printf("left!\n");
                break;
            case 'H':
            	printf("home!\n");
            	break;
            case 'F':
            	printf("end!\n");
            	break;
            case '5':
            	printf("pgup!\n");
            	ch=getch_c();
            	break;
            case '6':
            	printf("pgdown!\n");
            	ch=getch_c();
            	break;
            default:
            	printf("nothing!\n");
            	break;
        }
    }else{
    	switch(ch){
			case '+':
				printf("+!\n");
				break;
			case '-':
				printf("-!\n");
				break;
			case 'q':
				printf("q!\n");
				break;
			default:
				printf("nothing!\n");
				break;
    	}
    }
}*/
