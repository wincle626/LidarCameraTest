/*
 * key.hpp
 *
 *  Created on: 24 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_KEY_HPP_
#define SRC_HEADERS_KEY_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

class key{
public:
	key();
	~key();
	bool kbhit();
	int getch_c();
private:
	bool hit=false;
	int k=-1;
protected:
};

#endif /* SRC_HEADERS_KEY_HPP_ */
