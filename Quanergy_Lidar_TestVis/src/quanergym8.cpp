/*
 * quanergy.cpp
 *
 *  Created on: 25 Sep 2018
 *      Author: Yun Wu
 */

#include "quanergym8.hpp"
#include "visualizer_module.hpp"

// convenient typedefs
// SensorClient connects to any quanergy sensor; it pulls TCP packets off the stream, queues them, and then signals them on a separate thread
typedef quanergy::client::SensorClient ClientType;
// VariadicPacketParser produces a polar point cloud; it uses information in the packet to find the correct parser from the ones supplied
typedef quanergy::client::VariadicPacketParser<quanergy::PointCloudHVDIRPtr,                      // return type
                                               quanergy::client::DataPacketParser00,              // PARSER_00_INDEX
                                               quanergy::client::DataPacketParser01,              // PARSER_01_INDEX
                                               quanergy::client::DataPacketParser04> ParserType;  // PARSER_04_INDEX

// enum to make indexing into the VariadicPacketParser easier
enum
{
  PARSER_00_INDEX = 0,
  PARSER_01_INDEX = 1,
  PARSER_04_INDEX = 2
};

// more typedefs
// PacketParserModule wraps the parser with signal/slot functionality
typedef quanergy::client::PacketParserModule<ParserType> ParserModuleType;
// EncoderAngleCalibration provides some calibration functionality for M8
typedef quanergy::calibration::EncoderAngleCalibration CalibrationType;
// PolarToCartConverter converts the polar point cloud to Cartesian
typedef quanergy::client::PolarToCartConverter ConverterType;

quanergym8::quanergym8(){
	  this->dataportnum = 4141;
	  this->queuenum = 100;
	  this->returnnum = 0;
	  this->ipaddress = "192.168.57.131";
	  this->m8datasize = 0;
	  this->m8xyzirdata = NULL;
	  this->m8onoffflag = 1;

}

quanergym8::quanergym8(int portnum, std::string ipaddr){
	  this->dataportnum = portnum;
	  this->queuenum = 100;
	  this->returnnum = 0;
	  this->ipaddress = ipaddr;
	  this->m8datasize = 0;
	  this->m8xyzirdata = NULL;
	  this->m8onoffflag = 1;
}

quanergym8::quanergym8(int portnum, int qnum, std::string ipaddr){
	  this->dataportnum = portnum;
	  this->queuenum = qnum;
	  this->returnnum = 0;
	  this->ipaddress = ipaddr;
	  this->m8datasize = 0;
	  this->m8xyzirdata = NULL;
	  this->m8onoffflag = false;
}

quanergym8::quanergym8(int portnum, int qnum,
					int rnum, std::string ipaddr){
	  this->dataportnum = portnum;
	  this->queuenum = qnum;
	  this->returnnum = rnum;
	  this->ipaddress = ipaddr;
	  this->m8datasize = 0;
	  this->m8xyzirdata = NULL;
	  this->m8onoffflag = 1;
}

quanergym8::~quanergym8(){

}

void quanergym8::setpoitnumber(int pn){
	this->dataportnum = pn;
}

void quanergym8::setipaddress(std::string ip){
	this->ipaddress = ip;
}

int quanergym8::getportnumber(){
	return this->dataportnum;
}

int quanergym8::getqueuenumber(){
	return this->queuenum;
}

int quanergym8::getm8datasize(){
	return this->m8datasize;
}

void quanergym8::setm8datasize(int size){
	this->m8datasize = size;
}

std::string quanergym8::getipaddress(){
	return this->ipaddress;
}

void quanergym8::setm8onoffflag(unsigned short flag){
	std::lock_guard<std::mutex> onofflk(this->m8_onoff_mutex);
	this->m8onoffflag = flag;
}

void quanergym8::setm8visonffflag(unsigned short flag){
	this->m8visonoffflag = flag;
}

void quanergym8::updatedata(boost::shared_ptr<pcl::PointCloud<quanergy::PointXYZIR>>& pc)
{
    pcl::PointCloud<quanergy::PointXYZIR> *pc1;
    pcl::PointCloud<quanergy::PointXYZIR> pc2;
    quanergy::PointXYZIR pc3;
	pc1 = (pcl::PointCloud<quanergy::PointXYZIR> *) pc.get();
	pc2 = pc1[0];
	{
		std::lock_guard<std::mutex> rdlk(this->m8_dataread_mutex);
		this->m8pcldata.clear();
		for(uint j=0;j<pc2.size();j++){
			// std::cout << j << "th point cloud" << std::endl;
			pc3 = pc2.at(j);
			if(pc3.x==pc3.x){
				this->m8pcldata.push_back(pc3);
			}
		}
		/*uint size = this->m8rawdata.size();
		std::cout << "point cloud number: " << size << std::endl;
		this->m8datasize = size * 5 * sizeof(float);
		this->m8xyzirdata = NULL;
		this->m8xyzirdata = (char*) realloc(this->m8xyzirdata, size*5*sizeof(float));
		float *data = (float *) malloc(size*5*sizeof(float));
		for(uint j=0;j<size;j++){
			data[j*5] = (float)this->m8rawdata.at(j).x;
			data[j*5+1] = (float)this->m8rawdata.at(j).y;
			data[j*5+2] = (float)this->m8rawdata.at(j).z;
			data[j*5+3] = (float)this->m8rawdata.at(j).intensity;
			data[j*5+4] = (float)this->m8rawdata.at(j).ring;
		}
		memcpy(this->m8xyzirdata,data,size*5*sizeof(float));*/
	}
}

void quanergym8::m8datareveiver(){

	ClientType m8client(this->ipaddress, std::to_string(this->dataportnum), this->queuenum);
	ParserModuleType parser;
	ConverterType converter;
#if(WITH_VIS==1)
	VisualizerModule visualizer;
#endif

	// setup modules
	// setFrameId sets the frame id in the PCL point clouds
	parser.get<PARSER_00_INDEX>().setFrameId("quanergy");
	// setReturnSelection allows choosing between the 3 returns (Packet00, only)
	parser.get<PARSER_00_INDEX>().setReturnSelection(this->returnnum);
	// setDegreesOfSweepPerCloud allows breaking the point clouds into smaller pieces (M8 only)
	parser.get<PARSER_00_INDEX>().setDegreesOfSweepPerCloud(360.0);
	parser.get<PARSER_01_INDEX>().setFrameId("quanergy");
	parser.get<PARSER_04_INDEX>().setFrameId("quanergy");

	// connect the packets from the client to the parser
	this->connections.push_back(m8client.connect([&parser]
						  (const ClientType::ResultType& pc)
						  { parser.slot(pc); }));
    // connect the parser to the converter
	this->connections.push_back(parser.connect([&converter]
						  (const ParserModuleType::ResultType& pc)
						  { converter.slot(pc); }));
    // connect customised function
	unsigned int cloud_count = 0;
#if(WITH_VIS==1)
    this->connections.push_back(converter.connect([&visualizer, &cloud_count, this](const ConverterType::ResultType& pc)
#else
	this->connections.push_back(converter.connect([&cloud_count, this](const ConverterType::ResultType& pc)
	{

#endif
#if(WITH_VIS==1)
    		if(this->m8visonoffflag==1){
				visualizer.slot(pc);
    		}
#endif
			this->updatedata((boost::shared_ptr<pcl::PointCloud<quanergy::PointXYZIR>>&)pc);
		}));

    std::mutex state_mutex;
    std::condition_variable state_condition;
    enum struct State {ON, OFF, EXIT};
    State state(State::OFF);


	// run the client in a separate thread
#if(WITH_VIS==1)
	std::thread m8client_thread([&m8client, &visualizer, this, &state, &state_condition, &state_mutex]
#else
	std::thread m8client_thread([&m8client, this, &state, &state_condition, &state_mutex]
#endif
	{
		while (true)
		{
			//std::cout << "in loop1" << std::endl;
			try
			{
		        {
					// wait for state to be change from STOP; this is scoped for the lock
					std::unique_lock<std::mutex> lk(state_mutex);
					state_condition.wait(lk, [&state]{return state != State::OFF;});

					if (state == State::EXIT)
					{
						break; // exit while loop
					}
		        }

		        m8client.run();
		    }
			catch (std::exception& e)
			{
				std::cerr << "Caught exception (" << e.what() << "); stopping" << std::endl;
		        std::lock_guard<std::mutex> lk(state_mutex);
		        state = State::OFF;
		        this->m8onoffflag = 0;
#if(WITH_VIS==1)
		        visualizer.stop();
#endif
			}
		}
		//std::cout << "out loop1" << std::endl;
	});

	std::thread control_thread([&state_mutex, &state, &m8client, &state_condition, this]{
		while (state != State::EXIT)
		{
			//std::cout << "in loop2" << std::endl;
			{
				std::lock_guard<std::mutex> onofflk(this->m8_onoff_mutex);
				// set the state and take appropriate action; this is scoped for the lock
				if (this->m8onoffflag == 2)
				{
					std::lock_guard<std::mutex> lk(state_mutex);
					state = State::ON;
				}
				else if (this->m8onoffflag == 1)
				{
					std::lock_guard<std::mutex> lk(state_mutex);
					state = State::OFF;
					m8client.stop();
				}
				else if (this->m8onoffflag == 0)
				{
					std::lock_guard<std::mutex> lk(state_mutex);
					state = State::EXIT;
					m8client.stop();
				}
				else
				{
					std::cout << "Exceptional Flag" << std::endl;
				}
			}

			// notify the condition variable to stop waiting
			state_condition.notify_one();
		}
	});

#if(WITH_VIS==1)
	if(this->m8visonoffflag==1)
		visualizer.run();
#endif


	// clean up
	m8client.stop();
	this->connections.clear();
	control_thread.join();
	m8client_thread.join();

}


void quanergym8::m8pcldisplay(){

}

void quanergym8::setm8rawdata(pcl::PointCloud<quanergy::PointXYZIR> data){
	this->m8pcldata.clear();
	for(uint i=0;i<data.size();i++){
		this->m8pcldata.push_back(data.at(i));
	}
}

void quanergym8::setm8data(char* data){
	this->m8xyzirdata = (char*) realloc(this->m8xyzirdata, this->m8datasize*sizeof(char));
	memcpy(this->m8xyzirdata, data, this->m8datasize*sizeof(char));
}

pcl::PointCloud<quanergy::PointXYZIR> quanergym8::getm8pointcloud(){
	std::lock_guard<std::mutex> rdlk(this->m8_dataread_mutex);
	pcl::PointCloud<quanergy::PointXYZIR> data;
	uint size = this->m8pcldata.size();
	for(uint i=0;i<size;i++){
		data.push_back(this->m8pcldata.at(i));
	}
	return data;
}

char* quanergym8::getm8data(){
	std::lock_guard<std::mutex> rdlk(this->m8_dataread_mutex);
	uint size = this->m8pcldata.size();
	this->m8datasize = size * 5 * 4;
	this->m8xyzirdata = NULL;
	this->m8xyzirdata = (char*) realloc(this->m8xyzirdata, size*5*sizeof(float));
	float *data = (float*) this->m8xyzirdata;
	for(uint j=0;j<size;j++){
		data[j*5] = this->m8pcldata.at(j).x;
		data[j*5+1] = this->m8pcldata.at(j).y;
		data[j*5+2] = this->m8pcldata.at(j).z;
		data[j*5+3] = this->m8pcldata.at(j).intensity;
		data[j*5+4] = this->m8pcldata.at(j).ring;
	}
	return this->m8xyzirdata;
}

