/*
 * main.cpp
 *
 *  Created on: 6 Jul 2018
 *      Author: Yun Wu
 */
#include "common.hpp"
#include "ptzcam.hpp"
#include "curl.hpp"
#include "key.hpp"

void test(ptzcam &dev_ptzcam){

	pthread_t pid1;
	pthread_t pid2;
	int err1 = pthread_create(&pid1, NULL, display_pthread, &dev_ptzcam);
	if (err1)
	{
		std::cout << "Thread creation failed : " << strerror(err1) << std::endl;
		exit(err1);
	}
	int err2 = pthread_create(&pid2, NULL, ptz_pthread, &dev_ptzcam);
	if (err2)
	{
		std::cout << "Thread creation failed : " << strerror(err2) << std::endl;
		exit(err2);
	}
	pthread_join(pid2, NULL);
	pthread_join(pid1, NULL);

}

int main(int argc, char **argv){

	if(argc<=1){
		printf("Please input camera IP. ");
		exit(0);
	}

	//PTZ_DISPLAY_TEST
	char* ip = argv[1];
	printf("q: quit. (In both image and terminal windows)\n");
	printf("PTZ: up arrow, down arrow, left arrow, right arrow. (In terminal window)\n");
	printf("Press Any Key to Continue ... \n");
	getchar();
	ptzcam dev_ptzcam(std::string("ADMIN"), std::string("Qwer1234"), std::string(ip));
	test(dev_ptzcam);

	std::cout << "ptz done !" << std::endl;

	return 0;
}


