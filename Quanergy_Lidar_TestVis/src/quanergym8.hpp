/*
 * quanergym8.hpp
 *
 *  Created on: 25 Sep 2018
 *      Author: Yun Wu
 */

#ifndef SRC_QUANERGYM8_HPP_
#define SRC_QUANERGYM8_HPP_

#include "common.hpp"
#include "udp.hpp"

#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>

#include <quanergy/client/sensor_client.h>
#include <quanergy/parsers/data_packet_parser_00.h>
#include <quanergy/parsers/data_packet_parser_01.h>
#include <quanergy/parsers/data_packet_parser_04.h>
#include <quanergy/parsers/variadic_packet_parser.h>
#include <quanergy/modules/encoder_angle_calibration.h>
#include <quanergy/modules/polar_to_cart_converter.h>

#define WITH_VIS 0

class quanergym8 : public udp{

	public:
		std::mutex m8_onoff_mutex;
		std::mutex m8_dataread_mutex;
		std::timed_mutex pc_mutex_;
		quanergym8();
		quanergym8(int portnum, std::string ipaddr);
		quanergym8(int portnum, int qnum, std::string ipaddr);
		quanergym8(int portnum, int qnum, int rnum, std::string ipaddr);
		~quanergym8();
		int getportnumber();
		int getqueuenumber();
		int getm8datasize();
		std::string getipaddress();
		void setpoitnumber(int pn);
		void setipaddress(std::string ip);
		void setm8datasize(int size);
		void setm8onoffflag(unsigned short flag);
		void setm8visonffflag(unsigned short flag);
		void updatedata(boost::shared_ptr<pcl::PointCloud<quanergy::PointXYZIR>>& pc);
		void m8datareveiver();
		void m8pcldisplay();
		void setm8rawdata(pcl::PointCloud<quanergy::PointXYZIR> data);
		void setm8pcdata(pcl::PointCloud<pcl::PointXYZ> data);
		void setm8data(char* data);
		pcl::PointCloud<quanergy::PointXYZIR> getm8pointcloud();
		pcl::PointCloud<pcl::PointXYZ> getpclpointcloud();
		char* getm8data();


	private:
		int dataportnum = 4141;
		int queuenum = 100;
		int returnnum = 0;
		std::string ipaddress = "192.168.57.141";
		std::vector<boost::signals2::connection> connections;
		unsigned short m8onoffflag = 0;// 0: exit, 1: off, 2: on
		unsigned short m8visonoffflag = 0; // 0: without visualisation, 1, with visualisation

	protected:
		  int m8datasize = 0;
		  pcl::PointCloud<quanergy::PointXYZIR> m8pcldata;
		  char* m8xyzirdata;

};

#endif /* SRC_QUANERGYM8_HPP_ */
