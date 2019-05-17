/*
 * debug.hpp
 *
 *  Created on: 21 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_DEBUG_HPP_
#define SRC_HEADERS_DEBUG_HPP_

#include "common.hpp"

#define ENTER_FUNC std::cout << "enter function: " << __func__ << std::endl;

#define EXIT_FUNC std::cout << "exit function: " << __func__ << std::endl;

#define FILE_LINE std::cout << "in file: " << __FILE__ << ", at line: " << __LINE__ << std::endl;

#define DATA_TIME std::cout << "Data: " << __DATE__ << ", Time: " << __TIME__ << std::endl;

#endif /* SRC_HEADERS_DEBUG_HPP_ */
