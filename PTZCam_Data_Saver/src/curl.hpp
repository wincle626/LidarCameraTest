/*
 * curl.hpp
 *
 *  Created on: 23 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_CURL_HPP_
#define SRC_HEADERS_CURL_HPP_

#include "common.hpp"
#include <curl/curl.h>

// #define PRINT_CURL_MESSAGE

class curl{
public:
	curl();
	~curl();
	void seturl(std::string u);
	void setpost(std::string p);
	void setmsg(std::string msg);
	void setfile(std::string f);
	void setdata(std::string d);
	std::string geturl();
	std::string getpost();
	std::string getmsg();
	std::string getfile();
	std::string getdata();
	void curlget();
	void curlputf();
	void curlput();
	void curlpostf();
	void curlpost();
private:
	std::string url;
	std::string post;
protected:
	std::string message;
	std::string file;
	std::string data;
};

#endif /* SRC_HEADERS_CURL_HPP_ */
