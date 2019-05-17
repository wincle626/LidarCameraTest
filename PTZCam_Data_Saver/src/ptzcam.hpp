/*
 * ptzcam.hpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#ifndef SRC_HEADERS_PTZCAM_HPP_
#define SRC_HEADERS_PTZCAM_HPP_

#include "common.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include "curl.hpp"
#include "key.hpp"
#include "debug.hpp"

#define PTZ_INTERVAL_MS 80

class ptzcam : public curl, public key{
public:
	pthread_t PTZDataThreadID=0;
	pthread_t PTZDisplayThreadID=0;
	pthread_t PTZControlThreadID=0;
	pthread_mutex_t pkgAccessMuxid;
	ptzcam();
	ptzcam(std::string u, std::string p, std::string ip);
	~ptzcam();
	void setip(char *p);
	void setport(int port);
	void setuser(char *user);
	void setpwd(char *pwd);
	void setport();
	void capture_cv();
	void capture_release();
	void capture_cvframe();
	void capture_cvframe_size();
	void release_cvframe();
	void capture_snapshot();
	void *test_cvdisplay();
    void cvframe2rawdata();
    void pclbgrpointgen(pcl::PointXYZRGB &brgpoint, int i, int j);
    void pclbgrdatagren(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &colored_point_cloud_ptr);
    void cvframe2pclrbgdata();
	void setrawdatatime(unsigned char timebytes[4]);
	void snapshotjgpdata();
	void setjpgdatatime(unsigned char timebytes[4]);
	void setcvcap(cv::VideoCapture cvcap);
	void setcvframe(cv::Mat cvframe);
	void ptzleft();
	void ptzright();
	void ptzup();
	void ptzdown();
	void ptzupleft();
	void ptzupright();
	void ptzdownleft();
	void ptzdownright();
	void ptzzoomin();
	void ptzzoomout();
	void ptzsetspeed(int speed);
	void ptzsetonoff(bool onoff);
	void ptzsetptzcommand();
	void ptzsetzoomcommand();
	void ptzseturl();
	void *ptzptzctrl();
	void *ptzzoomctrl();
	void *ptzctrl(std::string command);
	void ptzstartcommand();
	void ptzstopcommand();
	int *ptzkeyctrl();
	int getframeheight();
	int getframewidth();
	int getport();
	std::string getusername();
	std::string getpassword();
	std::string getipaddr();
	std::string getvideocommand();
	std::string getvideourl();
	std::string getptzcommand();
	std::string getptzdirect();
	std::string getptzzoom();
	std::string getptzspeed();
	std::string getptzonoff();
	std::string getvideosource();
	std::string getptzsource();
	std::string getptzurl();
	cv::VideoCapture getcvcap();
	cv::Mat getcvframe();
	unsigned char* getjpgdata();
	unsigned char* getrawdata();
	unsigned char* getnaludata();


private:
	bool frame_size_captured = false;
	int frame_height=0;
	int frame_width=0;
	int port=80;
	std::string username;
	std::string password;
	std::string ip_addr;
	std::string videocommand;
	std::string videourl;
	std::string ptzcommand;
	std::string ptzdirect;
	std::string ptzzoom;
	std::string ptzspeed;
	std::string ptzonoff;
	std::string snapshotsource;
	std::string videosource;
	std::string ptzsource;
	std::string ptzurl;

protected:
	cv::VideoCapture cv_cap;
	cv::Mat cv_frame;
	unsigned char* jpg_data=NULL;
	unsigned char* raw_data=NULL;
    unsigned char* nalu_data=NULL;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_data;
};

void *display_pthread(void *context);
void *ptz_pthread(void *context);
#endif /* SRC_HEADERS_PTZCAM_HPP_ */
