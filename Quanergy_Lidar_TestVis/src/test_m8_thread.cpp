/*
 * test_m8_thread.cpp
 *
 *  Created on: 26 Sep 2018
 *      Author: Yun Wu
 */

#include "test_m8_thread.hpp"

void *data_print_thread(void *p){

    std::string input;
    std::getline(std::cin, input);

    int datasize;
    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy;
    float *fdatacpy = NULL;

    {
    	quanergym8 *context = (quanergym8*) p;
		std::cout << "get data" << std::endl;
		pcl::PointCloud<quanergy::PointXYZIR> rawdata = context->getm8pointcloud();
		char *fdata = context->getm8data();
		std::cout << "get data size: " << context->getm8datasize() << std::endl;
		datasize = context->getm8datasize();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy.push_back(rawdata.at(i));
		}
		fdatacpy = (float*) realloc(fdatacpy, datasize);
		memcpy(fdatacpy,fdata,datasize);
    }

	std::cout << "raw data size: " << rawdatacpy.size() << std::endl;
	std::cout << "char data size: " << datasize << std::endl;

    std::cout << "save data" << std::endl;
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen("rawdata.txt", "w+");
	fp2 = fopen("chardata.txt", "w+");
	uint i=0;
	for(i=0;i<rawdatacpy.size();i++)
		fprintf(fp1, "%f\t%f\t%f\t%f\t%f\n", rawdatacpy.at(i).x,
				rawdatacpy.at(i).y, rawdatacpy.at(i).z, rawdatacpy.at(i).intensity,
				(float)rawdatacpy.at(i).ring );
	for(i=0;i<(uint)datasize/20;i++)
		fprintf(fp2, "%f\t%f\t%f\t%f\t%f\n", fdatacpy[5*i],fdatacpy[5*i+1],fdatacpy[5*i+2],fdatacpy[5*i+3],fdatacpy[5*i+4]);
	fclose(fp1);
	fclose(fp2);

	pcl::io::savePCDFileASCII ("test_pcd.pcd", rawdatacpy);

	return NULL;

}

void *data_update_thread(void *p){
	quanergym8 *context = (quanergym8*) p;
    std::cout << "start data receiver" << std::endl;
    context->setm8visonffflag(0);
    context->m8datareveiver();
	return NULL;
}

void *control_thread(void *p){

	quanergym8 *context = (quanergym8*) p;

    std::cout << "wait for 10s" << std::endl;
	usleep(1000*1000*10);

    std::cout << "turn on the sensor" << std::endl;
    context->setm8onoffflag(2);

    std::cout << "wait for 120s" << std::endl;
	usleep(1000*1000*120);

    std::cout << "turn off the sensor" << std::endl;
    context->setm8onoffflag(1);

    std::cout << "exit the thread" << std::endl;
    context->setm8onoffflag(0);
	return NULL;
}

void *vis_m8_thread(void *p){


    std::string input;
    std::getline(std::cin, input);

#ifdef XYZ

    int datasize;
    float *fdatacpy = NULL;
    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy;
	quanergym8 *context = (quanergym8*) p;
	std::cout << "get data" << std::endl;
	pcl::PointCloud<quanergy::PointXYZIR> rawdata = context->getm8pointcloud();
	char *fdata = context->getm8data();
	std::cout << "get data size: " << context->getm8datasize() << std::endl;
	datasize = context->getm8datasize();
	for(uint i=0;i<(uint)rawdata.size();i++){
		rawdatacpy.push_back(rawdata.at(i));
	}
	fdatacpy = (float*) realloc(fdatacpy, datasize);
	memcpy(fdatacpy,fdata,datasize);
	std::cout << "data recorded" << std::endl;

	pcl::PointCloud<pcl::PointXYZ> cloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudptr;
	for(uint i=0;i<(uint)rawdatacpy.size();i++){
		//std::cout << i << "th point" << std::endl;
		pcl::PointXYZ pc;
		pc.x = rawdatacpy.points[i].x;
		pc.y = rawdatacpy.points[i].y;
		pc.z = rawdatacpy.points[i].z;
		//pc.intensity = rawdatacpy.points[i].intensity;
		cloud.push_back(pc);
	}
	cloudptr = cloud.makeShared();

#ifdef CLOUDVIEWER

	pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
	viewer.showCloud (cloudptr, "Sample Cloud");
	while (!viewer.wasStopped ())
	{
	    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy1;
		rawdata = context->getm8pointcloud();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy1.push_back(rawdata.at(i));
		}
		pcl::PointCloud<pcl::PointXYZ> cloud1;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloudptr1;
		for(uint i=0;i<(uint)rawdatacpy1.size();i++){
			//std::cout << i << "th point" << std::endl;
			pcl::PointXYZ pc;
			pc.x = rawdatacpy1.points[i].x;
			pc.y = rawdatacpy1.points[i].y;
			pc.z = rawdatacpy1.points[i].z;
			//pc.intensity = rawdatacpy.points[i].intensity;
			cloud1.push_back(pc);
		}
		cloudptr1 = cloud1.makeShared();
		viewer.showCloud (cloudptr1, "Sample Cloud");
	}
#endif

#ifdef PCLVISULIZER

	pcl::visualization::PCLVisualizer::Ptr pclviewer (
			new pcl::visualization::PCLVisualizer ("Simple Cloud Viewer"));
	pclviewer->setBackgroundColor (0, 0, 0);
	pclviewer->addPointCloud<pcl::PointXYZ> (cloudptr, cloudptr->header.frame_id);
	pclviewer->setPointCloudRenderingProperties (
			pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
	pclviewer->addCoordinateSystem (1.0, "global");
	pclviewer->initCameraParameters ();
	pclviewer->setCameraPosition (0.0, 0.0, 30.0, 0.0, 1.0, 0.0, 0);
	pclviewer->setCameraClipDistances (0.0, 50.0);
	while (!pclviewer->wasStopped ())
	{
		pclviewer->spinOnce(10);
	    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy1;
		rawdata = context->getm8pointcloud();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy1.push_back(rawdata.at(i));
		}
		pcl::PointCloud<pcl::PointXYZ> cloud1;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloudptr1;
		for(uint i=0;i<(uint)rawdatacpy1.size();i++){
			//std::cout << i << "th point" << std::endl;
			pcl::PointXYZ pc;
			pc.x = rawdatacpy1.points[i].x;
			pc.y = rawdatacpy1.points[i].y;
			pc.z = rawdatacpy1.points[i].z;
			//pc.intensity = rawdatacpy.points[i].intensity;
			cloud1.push_back(pc);
		}
		cloudptr1 = cloud1.makeShared();
		if(!pclviewer->addPointCloud<pcl::PointXYZ> (cloudptr1, cloudptr1->header.frame_id))
			pclviewer->updatePointCloud(cloudptr1, cloudptr1->header.frame_id);
	    usleep(100*1000);
	}

#endif

#endif



#ifdef XYZI

    int datasize;
    float *fdatacpy = NULL;
    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy;
	quanergym8 *context = (quanergym8*) p;
	std::cout << "get data" << std::endl;
	pcl::PointCloud<quanergy::PointXYZIR> rawdata = context->getm8pointcloud();
	char *fdata = context->getm8data();
	std::cout << "get data size: " << context->getm8datasize() << std::endl;
	datasize = context->getm8datasize();
	for(uint i=0;i<(uint)rawdata.size();i++){
		rawdatacpy.push_back(rawdata.at(i));
	}
	fdatacpy = (float*) realloc(fdatacpy, datasize);
	memcpy(fdatacpy,fdata,datasize);
	std::cout << "data recorded" << std::endl;

	pcl::PointCloud<pcl::PointXYZI> cloud;
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloudptr;
	for(uint i=0;i<(uint)rawdatacpy.size();i++){
		//std::cout << i << "th point" << std::endl;
		pcl::PointXYZI pc;
		pc.x = rawdatacpy.points[i].x;
		pc.y = rawdatacpy.points[i].y;
		pc.z = rawdatacpy.points[i].z;
		pc.intensity = rawdatacpy.points[i].intensity;
		cloud.push_back(pc);
	}
	cloudptr = cloud.makeShared();

#ifdef CLOUDVIEWER

	pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
	viewer.showCloud (cloudptr, "Sample Cloud");
	while (!viewer.wasStopped ())
	{
	    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy1;
		rawdata = context->getm8pointcloud();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy1.push_back(rawdata.at(i));
		}
		pcl::PointCloud<pcl::PointXYZI> cloud1;
		pcl::PointCloud<pcl::PointXYZI>::Ptr cloudptr1;
		for(uint i=0;i<(uint)rawdatacpy1.size();i++){
			//std::cout << i << "th point" << std::endl;
			pcl::PointXYZI pc;
			pc.x = rawdatacpy1.points[i].x;
			pc.y = rawdatacpy1.points[i].y;
			pc.z = rawdatacpy1.points[i].z;
			//pc.intensity = rawdatacpy.points[i].intensity;
			cloud1.push_back(pc);
		}
		cloudptr1 = cloud1.makeShared();
		viewer.showCloud (cloudptr1, "Sample Cloud");
	}
#endif

#ifdef PCLVISULIZER

	pcl::visualization::PCLVisualizer::Ptr pclviewer (
			new pcl::visualization::PCLVisualizer ("Simple Cloud Viewer"));
	pclviewer->setBackgroundColor (0, 0, 0);
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(cloudptr, "intensity");
	pclviewer->addPointCloud<pcl::PointXYZI> (cloudptr, color_handler, cloudptr->header.frame_id);
	pclviewer->setPointCloudRenderingProperties (
			pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
	pclviewer->addCoordinateSystem (1.0, "global");
	pclviewer->initCameraParameters ();
	pclviewer->setCameraPosition (0.0, 0.0, 30.0, 0.0, 1.0, 0.0, 0);
	pclviewer->setCameraClipDistances (0.0, 50.0);
	while (!pclviewer->wasStopped ())
	{
		pclviewer->spinOnce();
	    pcl::PointCloud<quanergy::PointXYZIR> rawdatacpy1;
		rawdata = context->getm8pointcloud();
		for(uint i=0;i<(uint)rawdata.size();i++){
			rawdatacpy1.push_back(rawdata.at(i));
		}
		pcl::PointCloud<pcl::PointXYZRGB> cloud1;
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudptr1;
		for(uint i=0;i<(uint)rawdatacpy1.size();i++){
			//std::cout << i << "th point" << std::endl;
			pcl::PointXYZRGB pc;
			pc.x = rawdatacpy1.points[i].x;
			pc.y = rawdatacpy1.points[i].y;
			pc.z = rawdatacpy1.points[i].z;
			pc.rgb = rawdatacpy1.points[i].intensity*pc.x*pc.y*pc.z;
			uint32_t rgb = *reinterpret_cast<int*>(&pc.rgb);
			uint8_t r = (rgb >> 16) & 0x0000ff;
			uint8_t g = (rgb >> 8)  & 0x0000ff;
			uint8_t b = (rgb)       & 0x0000ff;
			pc.r = r; pc.g = g; pc.b = b;
			cloud1.push_back(pc);
		}
		cloudptr1 = cloud1.makeShared();
		pclviewer->updatePointCloud(cloudptr1, cloudptr1->header.frame_id);
	    usleep(100*1000);
	}

#endif

#endif
	return NULL;

}

void *test_m8_thread(void *p){

	// port number; queue number, return number, ip address
	quanergym8 dev_m8(4141, 100, 2, "192.168.57.162");
	//quanergym8 dev_m8(4141, 100, 2, "192.168.57.180");

	pthread_t tid1;
	pthread_t tid2;
	//pthread_t tid3;
	pthread_t tid4;

	int err1 = pthread_create(&tid1, NULL, data_update_thread, &dev_m8);
	if(err1){
		std::cout << "failed to create thread to test the M8 data acquiring" << std::endl;
	}
	int err2 = pthread_create(&tid2, NULL, control_thread, &dev_m8);
	if(err2){
		std::cout << "failed to create thread to test the M8 control" << std::endl;
	}
	/*int err3 = pthread_create(&tid3, NULL, data_print_thread, &dev_m8);
	if(err3){
		std::cout << "failed to create thread to test the M8 data print" << std::endl;
	}*/
	int err4 = pthread_create(&tid4, NULL, vis_m8_thread, &dev_m8);
	if(err4){
		std::cout << "failed to create thread to test the M8 visualization" << std::endl;
	}
	pthread_join(tid4, NULL);
	//pthread_join(tid3, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid1, NULL);


#if 0

	pcl::PointCloud<quanergy::PointXYZIR>::Ptr cloud_tx (new pcl::PointCloud<quanergy::PointXYZIR>);
	pcl::PointCloud<quanergy::PointXYZIR>::Ptr cloud_rx (new pcl::PointCloud<quanergy::PointXYZIR>);

	if (pcl::io::loadPCDFile<quanergy::PointXYZIR> ("test_pcd.pcd", *cloud_tx) == -1) //* load the file
	{
		PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
	}else{
		std::cout << "read pcd file successfully !"
				  << std::endl;
		std::cout << "pcl width: "
				  << cloud_tx->width
				  << std::endl;
		std::cout << "pcl height: "
				  << cloud_tx->height
				  << std::endl;
		std::cout << "Loaded "
				  << cloud_tx->points.size()
				  << " data points from test_pcd.pcd"
				  << std::endl;
		std::cout << "Loaded "
				  << cloud_tx->points.size()*5*sizeof(float)
				  << " data from test_pcd.pcd"
				  << std::endl;
	}

	std::thread rx_thread([&cloud_rx]{

		float *data_rx_f = NULL;
		char *data_rx = NULL;
		udp *udp_obj_rx = new udp(9527, (char*)"192.168.57.1");
		udp_obj_rx->setTxIP((char*)"192.168.57.1");
		udp_obj_rx->setRxIP((char*)"192.168.57.1");

		udp_obj_rx->setRxDataSize(sizeof(int));
		udp_obj_rx->rx2();
		udp_obj_rx->setRxDataR();
		char *datasize = udp_obj_rx->getRxData();
		int size = byte2int(datasize);
		std::cout << "rx data size value: " << size << std::endl;
		udp_obj_rx->setRxDataSize(size);
		udp_obj_rx->rx2();
		udp_obj_rx->setRxDataR();

		data_rx = (char*) udp_obj_rx->getRxData();
		// data_rx_f = (float*) data_rx;
		data_rx_f = (float*) realloc(data_rx_f, size);
		memcpy(data_rx_f, data_rx, size);
		uint size_f = size/5/sizeof(float);
		for(uint j=0;j<size_f;j++){
			quanergy::PointXYZIR pcl_point;
			pcl_point.x = data_rx_f[j*5];
			pcl_point.y = data_rx_f[j*5+1];
			pcl_point.z = data_rx_f[j*5+2];
			pcl_point.intensity = data_rx_f[j*5+3];
			pcl_point.ring = (uint16_t)data_rx_f[j*5+4];
			cloud_rx.get()->push_back(pcl_point);
		}
		pcl::io::savePCDFileASCII ("test_pcd_rx.pcd", *cloud_rx);
		std::cout << "rx done!" << std::endl;

	});

	std::thread tx_thread([&cloud_tx]{

		float *data_tx_f = NULL;
		char *data_tx = NULL;
		udp *udp_obj_tx = new udp(9527, (char*)"192.168.57.1");
		udp_obj_tx->setTxIP((char*)"192.168.57.1");
		udp_obj_tx->setRxIP((char*)"192.168.57.1");

		data_tx = (char*) realloc(data_tx, cloud_tx->points.size()*5*sizeof(float));
		data_tx_f = (float*) realloc(data_tx_f, cloud_tx->points.size()*5*sizeof(float));
		for(uint j=0;j<cloud_tx->points.size();j++){
			data_tx_f[j*5] = (float)cloud_tx->at(j).x;
			data_tx_f[j*5+1] = (float)cloud_tx->at(j).y;
			data_tx_f[j*5+2] = (float)cloud_tx->at(j).z;
			data_tx_f[j*5+3] = (float)cloud_tx->at(j).intensity;
			data_tx_f[j*5+4] = (float)cloud_tx->at(j).ring;
		}
		data_tx = (char*) data_tx_f;

		int size = cloud_tx->points.size()*5*sizeof(float);
		char *datasize = (char*) malloc(sizeof(unsigned int)*sizeof(char));
		int2byte(size, datasize);
		std::cout << "tx data size value: " << size << std::endl;
		udp_obj_tx->setTxDataSize(sizeof(unsigned int));
		udp_obj_tx->setTxDataW(datasize);
		udp_obj_tx->setTxDataR();
		udp_obj_tx->tx2();
		udp_obj_tx->setTxDataSize(size);
		udp_obj_tx->setTxDataW(data_tx);
		udp_obj_tx->setTxDataR();
		udp_obj_tx->tx2();
		std::cout << "tx done!" << std::endl;

	});


	tx_thread.join();
	rx_thread.join();
#endif

	return NULL;
}
