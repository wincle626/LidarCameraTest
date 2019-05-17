/*
 * curl.cpp
 *
 *  Created on: 23 May 2018
 *      Author: Yun Wu
 */


#include "curl.hpp"

curl::curl(){
	this->url = std::string();
	this->post = std::string();
	this->message = std::string();
	this->file = std::string();
}
curl::~curl(){

}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t retcode;
  curl_off_t nread;
  /* in real-world cases, this would probably get this data differently
     as this fread() stuff is exactly what the library already would do
     by default internally */
  retcode = fread(ptr, size, nmemb, (FILE *)stream);
  nread = (curl_off_t)retcode;
  fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
          " bytes from file\n", nread);
  return retcode;
}

// set the url
void curl::seturl(std::string u){
	this->url = u;
}

// set the post field value
void curl::setpost(std::string p){
	this->post = p;
}

// set the message
void curl::setmsg(std::string msg){
	this->message = msg;
}

// set the file pointer
void curl::setfile(std::string f){
	this->file = f;
}

void curl::setdata(std::string d){
	this->data = d;
}

// get the url
std::string curl::geturl(){
	return this->url;
}

// get the post field value
std::string curl::getpost(){
	return this->post;
}

// get the message
std::string curl::getmsg(){
	return this->message;
}

// get the file id
std::string curl::getfile(){
	return this->file;
}

// get the buffer data
std::string curl::getdata(){
	return this->data;
}

// http the url with GET method
void curl::curlget(){
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	/* get a curl handle */
	curl = curl_easy_init();
	std::string urlstr = this->geturl();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, urlstr.c_str());
		// configure the output from curl
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* HTTP GET please */
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET"); /* !!! */
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
#ifdef PRINT_CURL_MESSAGE
	std::cout << res << std::endl;
	std::cout << "read buffer: " << readBuffer << std::endl;
#endif
	this->setdata(readBuffer);
	curl_global_cleanup();
}

// http the url with the PUT method
void curl::curlputf()
{
	CURL *curl;
#ifdef PRINT_CURL_MESSAGE
	CURLcode res;
#endif
	FILE *fp;
	std::string readBuffer;
	struct stat file_info;
	/* get the file size of the local file */
	std::string f = this->getfile();
	stat(f.c_str(), &file_info);
	/* get a FILE * of the same file, could also be made with
	 fdopen() from the previous descriptor, but hey this is just
	 an example! */
	fp = fopen(f.c_str(), "rb");
	curl = curl_easy_init();
	std::string urlstr = this->geturl();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, urlstr.c_str());
		// configure the output from curl
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	    /* we want to use our own read function */
	    curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadCallback);
		/* HTTP PUT please */
		// curl_easy_setopt(curl, CURLOPT_PUT, 1L); /*dont use this !!!*/
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); /* !!! */
	    /* now specify which file to upload */
	    curl_easy_setopt(curl, CURLOPT_READDATA, fp);
	    /* provide the size of the upload, we specicially typecast the value
	       to curl_off_t since we must be sure to use the correct data size */
	    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
	                     (curl_off_t)file_info.st_size);
#ifdef PRINT_CURL_MESSAGE
		res = curl_easy_perform(curl);
		std::cout << res << std::endl;
#else
		curl_easy_perform(curl);
#endif
		curl_easy_cleanup(curl);
	}
#ifdef PRINT_CURL_MESSAGE
	std::cout << "read buffer: " << readBuffer << std::endl;
#endif
	this->setmsg(readBuffer);
  	curl_global_cleanup();
}

// http the url with the PUT method
void curl::curlput()
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	/* get a curl handle */
	curl = curl_easy_init();
	std::string urlstr = this->geturl();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL,urlstr.c_str());
		// configure the output from curl
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* HTTP PUT please */
		// curl_easy_setopt(curl, CURLOPT_PUT, 1L); /*dont use this !!!*/
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); /* !!! */
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
#ifdef PRINT_CURL_MESSAGE
	std::cout << res << std::endl;
	std::cout << "read buffer: " << readBuffer << std::endl;
#endif
	this->setmsg(readBuffer);
	curl_global_cleanup();
}

// http the url with the POST method
void curl::curlpostf(){
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	/* get a curl handle */
	curl = curl_easy_init();
	std::string urlstr = this->geturl();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, urlstr.c_str());
		// configure the output from curl
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,post.c_str());
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
#ifdef PRINT_CURL_MESSAGE
	std::cout << res << std::endl;
	std::cout << "read buffer: " << readBuffer << std::endl;
#endif
	this->setmsg(readBuffer);
	curl_global_cleanup();
}

// http the url with the POST method
void curl::curlpost(){
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	/* get a curl handle */
	curl = curl_easy_init();
	std::string urlstr = this->geturl();
	if(curl) {
		/* First set the URL that is about to receive our POST. This URL can
		just as well be a https:// URL if that is what should receive the
		data. */
		curl_easy_setopt(curl, CURLOPT_URL, urlstr.c_str());
		// configure the output from curl
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		/* Now specify the POST data */
		/*curl_easy_setopt(curl, CURLOPT_POSTFIELDS,post.c_str());*/
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
#ifdef PRINT_CURL_MESSAGE
	std::cout << res << std::endl;
	std::cout << "read buffer: " << readBuffer << std::endl;
#endif
	this->setmsg(readBuffer);
	curl_global_cleanup();
}

