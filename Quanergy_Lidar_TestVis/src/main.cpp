/*
 * main.cpp
 *
 *  Created on: 25 Sep 2018
 *      Author: Yun Wu
 */

#include "test_m8_thread.hpp"

int main(int argc, char** argv){

	// visualizer(argc, argv);

	// dynamic_connection(argc, argv);

	pthread_t tid;
	int err = pthread_create(&tid, NULL, test_m8_thread, NULL);
	if(err){
		std::cout << "failed to create thread to test the M8 data acquiring" << std::endl;
	}
	pthread_join(tid, NULL);


	return 0;
}
