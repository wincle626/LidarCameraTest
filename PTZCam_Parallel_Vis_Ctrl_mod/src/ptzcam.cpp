/*
 * ptzcam.cpp
 *
 *  Created on: 16 May 2018
 *      Author: Yun Wu
 */

#include "ptzcam.hpp"

// constructor
ptzcam::ptzcam(){
	this->username=std::string("ADMIN");
	this->password=std::string("Qwer1234");
	this->ip_addr=std::string("10.42.0.64");
	this->videocommand=std::string("?camera=1&videocodec=h264&compression=10");
	this->ptzcommand=std::string();
	this->ptzdirect=std::string();
	this->ptzzoom=std::string();
	this->ptzspeed=std::string(std::to_string(3));
    this->ptzonoff=std::string("stop");
    this->frame_size_captured = false;
	this->cv_cap=cv::VideoCapture();
	this->cv_frame=cv::Mat();
	this->snapshotsource = std::string("http://")
					   +this->username
					   +std::string(":")
						   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/Streaming/channels/1/picture");
	this->videosource = std::string("rtsp://")
					   +this->username
					   +std::string(":")
					   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/axis-media/media.amp")
					   +this->videocommand;
	this->ptzsource = std::string("http://")
					   +this->username
					   +std::string(":")
	   	   	   	   	   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/PTZ/channels/1/PTZControl?")
					   +this->ptzcommand;
	this->jpg_data=NULL;
	this->raw_data=NULL;
	this->nalu_data=NULL;
#ifdef PRINT_DEFAUT_SETTING
	std::cout << "video address: " << this->videosource << std::endl;
	std::cout << "ptz address: " << this->ptzsource << std::endl;
#endif

}
ptzcam::ptzcam(std::string u, std::string p, std::string ip){
	this->username = u;
	this->password = p;
	this->ip_addr = ip;
	this->videocommand=std::string("?camera=1&videocodec=h264&compression=10");
	this->ptzdirect=std::string();
	this->ptzzoom=std::string();
	this->ptzcommand=std::string();
	this->ptzspeed=std::string(std::to_string(3));
	this->ptzonoff=std::string("stop");
    this->frame_size_captured = false;
	this->cv_cap=cv::VideoCapture();
    this->cv_frame=cv::Mat();
	this->snapshotsource = std::string("http://")
					   +this->username
					   +std::string(":")
						   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/Streaming/channels/1/picture");
	this->videosource = std::string("rtsp://")
					   +this->username
					   +std::string(":")
					   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/axis-media/media.amp")
					   +this->videocommand;
	this->ptzsource = std::string("http://")
					   +this->username
					   +std::string(":")
	   	   	   	   	   +this->password
					   +std::string("@")
					   +this->ip_addr
					   +std::string("/PTZ/channels/1/PTZControl?")
					   +this->ptzcommand;
	this->jpg_data=NULL;
	this->raw_data=NULL;
	this->nalu_data=NULL;
#ifdef PRINT_DEFAUT_SETTING
	std::cout << "video address: " << this->videosource << std::endl;
	std::cout << "ptz address: " << this->ptzsource << std::endl;
#endif
}

// destructor
ptzcam::~ptzcam(){

}

int ptzcam::getframeheight(){
	return this->frame_height;
}
int ptzcam::getframewidth(){
	return this->frame_width;
}
int ptzcam::getport(){
	return this->port;
}
std::string ptzcam::getusername(){
	return this->username;
}
std::string ptzcam::getpassword(){
	return this->password;
}
std::string ptzcam::getipaddr(){
	return this->ip_addr;
}
std::string ptzcam::getvideocommand(){
	return this->videocommand;
}
std::string ptzcam::getvideourl(){
	return this->videourl;
}
std::string ptzcam::getptzcommand(){
	return this->ptzcommand;
}
std::string ptzcam::getptzdirect(){
	return this->ptzdirect;
}
std::string ptzcam::getptzzoom(){
	return this->ptzzoom;
}
std::string ptzcam::getptzspeed(){
	return this->ptzspeed;
}
std::string ptzcam::getptzonoff(){
	return this->ptzonoff;
}
std::string ptzcam::getvideosource(){
	return this->videosource;
}
std::string ptzcam::getptzsource(){
	return this->ptzsource;
}
std::string ptzcam::getptzurl(){
	return this->ptzurl;
}
cv::VideoCapture ptzcam::getcvcap(){
	return this->cv_cap;
}
cv::Mat ptzcam::getcvframe(){
	return this->cv_frame;
}

unsigned char* ptzcam::getjpgdata(){
	pthread_mutex_lock(&this->pkgAccessMuxid);
	return this->jpg_data;
	pthread_mutex_unlock(&this->pkgAccessMuxid);
}

unsigned char* ptzcam::getrawdata(){
	pthread_mutex_lock(&this->pkgAccessMuxid);
	return this->raw_data;
	pthread_mutex_unlock(&this->pkgAccessMuxid);
}

unsigned char* ptzcam::getnaludata(){
	return this->nalu_data;
}

// set the ip address
void ptzcam::setip(char *ip){
	this->ip_addr = std::string(ip);
}

// set the port
void ptzcam::setport(int p){
	this->port  = p;
}

// set the user name
void ptzcam::setuser(char *u){
	this->username = std::string(u);
}

// set the password
void ptzcam::setpwd(char *p){
	this->password = std::string(p);
}

// obtain the OpenCV capture object
void ptzcam::capture_cv(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	std::cout << this->getvideosource() << std::endl;
	cv::VideoCapture cvcap(this->getvideosource().c_str(), cv::CAP_GSTREAMER);
	this->setcvcap(cvcap);
	if(!cvcap.isOpened()){
		std::cout << "cannot found camera " << std::endl;
		exit(0);
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

// release the OpenCV capture object
void ptzcam::capture_release(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->cv_cap.release();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

// capture the OpenCV mat object
void ptzcam::capture_cvframe(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	cv::Mat cvframe;
	this->cv_cap >> cvframe;
	this->setcvframe(cvframe);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void ptzcam::capture_cvframe_size(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	if(!this->frame_size_captured){
		this->frame_height = this->cv_frame.rows;
		this->frame_width = this->cv_frame.cols;
		this->raw_data = (unsigned char*)realloc(this->raw_data,
									   sizeof(unsigned char)
									   *this->frame_height
									   *this->frame_width
									   *3+4);
	}
	this->frame_size_captured = true;
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

// release the OpenCV mat object
void ptzcam::release_cvframe(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	this->cv_frame.release();
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
}

void *ptzcam::test_cvdisplay(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	cv::namedWindow("test_cvDisplay",1);
	this->capture_cv();
	for(;;){
		this->capture_cvframe();
		cv::imshow("test_cvDisplay",this->getcvframe());
		if(cv::waitKey(30)>=0)
			break;
	}
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif
	return NULL;
}

// transform the OpenCV mat to raw rbg data
void ptzcam::cvframe2rawdata(){
#ifdef PRINT_FUNC
	ENTER_FUNC
#endif
	pthread_mutex_lock(&this->pkgAccessMuxid);
	memset( this->raw_data, '\0',
			sizeof(char)*this->frame_height
			*this->frame_width*3+4 );
	for (int i=3; i<this->frame_height+4; i++)
	{
        for (int j=3; j<this->frame_width+4; j++)
		{
            this->raw_data[i*this->frame_width+j*3+5] =
					this->cv_frame.at<cv::Vec3b>(i,j)[0]; // Blue
            this->raw_data[i*this->frame_width+j*3+6] =
					this->cv_frame.at<cv::Vec3b>(i,j)[1]; // Green
            this->raw_data[i*this->frame_width+j*3+7] =
					this->cv_frame.at<cv::Vec3b>(i,j)[2]; // Red
		}
	}
	pthread_mutex_unlock(&this->pkgAccessMuxid);
#ifdef PRINT_FUNC
	EXIT_FUNC
#endif

}

void ptzcam::pclbgrpointgen(pcl::PointXYZRGB &brgpoint, int i, int j){
    brgpoint.x = this->cv_frame.at<cv::Vec3b>(i,j)[0]; // Blue
    brgpoint.y = this->cv_frame.at<cv::Vec3b>(i,j)[1]; // Green
    brgpoint.z = this->cv_frame.at<cv::Vec3b>(i,j)[2]; // Red
}

void ptzcam::pclbgrdatagren(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &colored_point_cloud_ptr){
    for (int i=0; i<this->frame_height; i++)
    {
        for (int j=0; j<this->frame_width; j++)
        {
            pclbgrpointgen(colored_point_cloud_ptr->points.at(i*this->frame_width+j),
                           i, j);
        }
    }
}

// transform the OpenCV mat to pcl rbg data
void ptzcam::cvframe2pclrbgdata(){
#ifdef PRINT_FUNC
    ENTER_FUNC
#endif
    pthread_mutex_lock(&this->pkgAccessMuxid);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
    pclbgrdatagren(colored_point_cloud_ptr);
    pthread_mutex_unlock(&this->pkgAccessMuxid);
#ifdef PRINT_FUNC
    EXIT_FUNC
#endif

}

void ptzcam::setrawdatatime(unsigned char timebytes[4]){
	this->raw_data[0] = timebytes[0];
	this->raw_data[1] = timebytes[1];
	this->raw_data[2] = timebytes[2];
	this->raw_data[3] = timebytes[3];
}


void ptzcam::capture_snapshot(){
	this->seturl(this->snapshotsource);
	this->curlget();
	this->jpg_data = (unsigned char*)realloc(this->jpg_data, sizeof(unsigned char)
								   *this->data.size()+4);
}

void ptzcam::snapshotjgpdata(){
	memcpy(&this->jpg_data[4], this->data.c_str(),this->data.size());
	this->data.clear();
}

void ptzcam::setjpgdatatime(unsigned char timebytes[4]){
	this->jpg_data[0] = timebytes[0];
	this->jpg_data[1] = timebytes[1];
	this->jpg_data[2] = timebytes[2];
	this->jpg_data[3] = timebytes[3];
}
void ptzcam::setcvcap(cv::VideoCapture cvcap){
	this->cv_cap  = cvcap;
}

void ptzcam::setcvframe(cv::Mat cvframe){
	this->cv_frame = cvframe;
}

// set PTZ direction
void ptzcam::ptzleft(){
	this->ptzdirect = std::string("PAN_LEFT");
}
void ptzcam::ptzright(){
	this->ptzdirect = std::string("PAN_RIGHT");
}
void ptzcam::ptzup(){
	this->ptzdirect = std::string("TILT_UP");
}
void ptzcam::ptzdown(){
	this->ptzdirect = std::string("TILT_DOWN");
}
void ptzcam::ptzupleft(){
	this->ptzdirect = std::string("UP_LEFT");
}
void ptzcam::ptzupright(){
	this->ptzdirect = std::string("UP_RIGHT");
}
void ptzcam::ptzdownleft(){
	this->ptzdirect = std::string("DOWN_LEFT");
}
void ptzcam::ptzdownright(){
	this->ptzdirect = std::string("DOWN_RIGHT");
}

// set PTZ zoom
void ptzcam::ptzzoomin(){
	this->ptzzoom = std::string("ZOOM_IN");
}
void ptzcam::ptzzoomout(){
	this->ptzzoom = std::string("ZOOM_OUT");
}

// set PTZ speed: 1~7
void ptzcam::ptzsetspeed(int speed){
	if(speed>0&&speed<8){
		this->ptzspeed = std::string(std::to_string(speed));
	}else{
		std::cout << "speed value must be 1~7, the default value 3 is in use."
				  << std::endl;
	}
}

// set the PTZ start/stop
void ptzcam::ptzsetonoff(bool onoff){
	if(onoff){
		this->ptzonoff = std::string("start");
	}else{
		this->ptzonoff = std::string("stop");
	}
}

// combine the ptz command
void ptzcam::ptzsetptzcommand(){
	this->ptzcommand = std::string("command=")
					   + this->ptzdirect
					   + std::string("&speed=")
					   + this->ptzspeed
					   + std::string("&mode=")
					   + this->ptzonoff;
}
void ptzcam::ptzsetzoomcommand(){
	this->ptzcommand = std::string("command=")
					   + this->ptzzoom
					   + std::string("&speed=")
					   + this->ptzspeed
					   + std::string("&mode=")
					   + this->ptzonoff;
}

// replace stop to start in command
void ptzcam::ptzstartcommand(){
	size_t f = this->ptzcommand.find("stop");
	if(f!=std::string::npos){
		this->ptzcommand = this->ptzcommand.replace(f,std::string("stop").length(),"start");
	}
}

// replace start to stop in command
void ptzcam::ptzstopcommand(){
	size_t f = this->ptzcommand.find("start");
	if(f!=std::string::npos){
		this->ptzcommand = this->ptzcommand.replace(f,std::string("start").length(),"stop");
	}
	std::cout << "stop command: " << this->ptzcommand << std::endl;
}

// combine the ptz control url
void ptzcam::ptzseturl(){
	this->ptzurl = this->ptzsource
				   + std::string("?")
				   + this->ptzcommand;
}

// executing ptz control command internally/externally
void *ptzcam::ptzptzctrl(){
	this->ptzsetptzcommand();
	this->ptzseturl();
	this->seturl(this->ptzurl);
	this->curlput();
	return NULL;
}
void *ptzcam::ptzzoomctrl(){
	this->ptzsetzoomcommand();
	this->ptzseturl();
	this->seturl(this->ptzurl);
	this->curlput();
	return NULL;
}
void *ptzcam::ptzctrl(std::string url){
	this->seturl(url);
	this->curlput();
	return NULL;
}

// using key to control the
int *ptzcam::ptzkeyctrl(){
	int ch;
	while (!this->kbhit()) {
		// do some work
wait:	usleep(PTZ_INTERVAL_MS*1000);
		//std::cout << "ptz control link: " << this->ptzurl << std::endl;
	}
	if ((ch=this->getch_c()) == '\033') { // if the first value is esc
		ch=this->getch_c(); // skip the [
		switch((ch=this->getch_c())) { // the real value
			case 'A':
				// code for arrow up
				//printf("up!\n");
				this->ptzup();
				break;
			case 'B':
				// code for arrow down
				//printf("down!\n");
				this->ptzdown();
				break;
			case 'C':
				// code for arrow right
				//printf("right!\n");
				this->ptzright();
				break;
			case 'D':
				// code for arrow left
				//printf("left!\n");
				this->ptzleft();
				break;
			case 'H':
				//printf("home!\n");
				this->ptzupleft();
				break;
			case 'F':
				//printf("end!\n");
				this->ptzdownleft();
				break;
			case '5':
				//printf("pgup!\n");
				ch=this->getch_c();
				this->ptzupright();
				break;
			case '6':
				//printf("pgdown!\n");
				ch=this->getch_c();
				this->ptzdownright();
				break;
			default:
				printf("unsupported key!\n");
				break;
		}
		this->ptzptzctrl();
		usleep(PTZ_INTERVAL_MS*1000);
		this->ptzsetonoff(false);
		this->ptzptzctrl();
	}else{
		switch(ch){
			case '1':
				this->ptzsetspeed(1);
				break;
			case '2':
				this->ptzsetspeed(2);
				break;
			case '3':
				this->ptzsetspeed(3);
				break;
			case '4':
				this->ptzsetspeed(4);
				break;
			case '5':
				this->ptzsetspeed(5);
				break;
			case '6':
				this->ptzsetspeed(6);
				break;
			case '7':
				this->ptzsetspeed(7);
				break;
			case '+':
				this->ptzzoomin();
				this->ptzzoomctrl();
				usleep(PTZ_INTERVAL_MS*1000);
				this->ptzsetonoff(false);
				this->ptzzoomctrl();
				break;
			case '-':
				this->ptzzoomout();
				this->ptzzoomctrl();
				usleep(PTZ_INTERVAL_MS*1000);
				this->ptzsetonoff(false);
				this->ptzzoomctrl();
				break;
			case 'b':
				this->ptzsetonoff(true);
				this->ptzzoomctrl();
				break;
			case 'e':
				this->ptzsetonoff(false);
				this->ptzzoomctrl();
				break;
			case 'q':
				goto finish;
				break;
			default:
				printf("unsupported key!\n");
				break;
		}
	}
	this->ptzsetonoff(true);
	goto wait;
	this->ptzptzctrl();
finish:	return 0;
}

void *display_pthread(void *context){
#ifdef DEBUG
	std::cout << "video address: " << ((ptzcam *)context)->getvideosource() << std::endl;
#endif
	((ptzcam *)context)->test_cvdisplay();
	return NULL;
}

void *ptz_pthread(void *context){
#ifdef DEBUG
	std::cout << "video address: " << ((ptzcam *)context)->getptzsource() << std::endl;
#endif
	((ptzcam *)context)->ptzkeyctrl();
	return NULL;
}
