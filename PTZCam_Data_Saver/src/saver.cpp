/*
 * saver.cpp
 *
 *  Created on: 29 Oct 2018
 *      Author: Yun Wu
 */

#include "common.hpp"
#include "ptzcam.hpp"
#include "curl.hpp"
#include "key.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv){

	if(argc<=1){
		printf("Please input camera IP. ");
		exit(0);
	}

	//PTZ_DISPLAY_TEST
	char* ip = argv[1];
	ptzcam dev_ptzcam(std::string("ADMIN"), std::string("Qwer1234"), std::string(ip));
	char* fdind = argv[2];
	std::string folder = std::string("./")+std::string(fdind)+std::string("/imgdata/");
	std::string crtfolder = std::string("mkdir ")+folder;
	std::cout << crtfolder << std::endl;
	system(crtfolder.c_str());
	//mkdir(folder.c_str(), 0777);
	//printf("Press Any Key to Continue ... \n");
	//getchar();

	dev_ptzcam.capture_cv();
	//cv::namedWindow("test_cvDisplay",1);
	for(;;){
		dev_ptzcam.capture_cvframe();
		cv::Mat frame = dev_ptzcam.getcvframe();
		//cv::imshow("test_cvDisplay", frame);
		if(cv::waitKey(30)>=0)
			break;

		char buffer[30];
		struct timeval tv;
		time_t curtime;
		gettimeofday(&tv, NULL);
		curtime=tv.tv_sec;
		strftime(buffer,30,"%m-%d-%Y-%T.",localtime(&curtime));
		//std::string folder = std::string(fdind)+std::string("/imgdata/");
		std::string daytime = std::string(buffer);
		std::string usectime = std::to_string(tv.tv_usec);
		std::string timestamp = daytime + usectime;
		std::string filename = folder + timestamp + std::string(".png");
		bool isSuccess = imwrite(filename, frame); //write the image to a file as PNG
		if (isSuccess == false)
		{
			std::cout << "Failed to save the image" << std::endl;
			std::cin.get(); //wait for a key press
			exit(0);
		}
	}

	return 0;
}


