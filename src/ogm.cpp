
#include <iostream>
#include <fstream>
//#include <iomanip>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

//#include <Eigen/Core>
//#include <Eigen/Geometry>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <octomap_ros/conversions.h>
#include <octomap/octomap.h>



//std::ofstream ofs("/home/hzx/data/time_stamp.txt");
//std::string pointCloudPath = "/home/hzx/data/point_cloud/";

void velodyneHandler(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    
    double timestamp = msg->header.stamp.toSec();
    //std::cout <<"time stamps:  " <<  timestamp << std::endl;
    pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl_conversions::toPCL(*msg, *cloud);

    ros::NodeHandle nh;
    ros::Publisher octo_pub = nh.advertise<octomap_msgs::Octomap>("/octomap", 10);

    octomap::Pointcloud octo_cloud;
//    octomap::pointCloud2ToOctomap(*msg, octo_cloud);
    octomap::pointCloud2ToOctomap(*msg, octo_cloud);

    std::stringstream ssTime;
    ssTime << std::setprecision(16) << timestamp;
    std::string strTime = ssTime.str(); 
    //std::cout << strTime << std::endl;

//    std::cout << cloud->points.size() <<std::endl;
//    pcl::io::savePCDFileASCII("1.pcd", *cloud);
//    pcl::io::savePCDFileASCII (pointCloudPath + strTime + ".pcd", *cloud);

//    ofs << std::setprecision(16) << timestamp << std::endl;
 //   std::cout << pointCloudPath + strTime + ".pcd" << std::endl;


    // Perform the actual filtering
//    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
//    sor.setInputCloud (cloudPtr);
//    sor.setLeafSize (0.1, 0.1, 0.1);
//    sor.filter (cloud_filtered);

    // Convert to ROS data type
//    sensor_msgs::PointCloud2 output;
//    pcl_conversions::fromPCL(cloud_filtered, output);

    // Publish the data
//    pub.publish (output);
    
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "ogm_node");
    ros::NodeHandle nh;

    ros::Subscriber velodyne_sub;
    velodyne_sub = nh.subscribe("/point_cloud", 100, velodyneHandler);
//    ofs << "name,latitude,longitude" << std::endl;
//    ofs << setiosflags(std::ios::fixed);
//    imu_pub = nh.advertise<sensor_msgs::Imu>("/imu_retime", 1);
//    pandora_sub = nh.subscribe("/pandora/sensor/pandora/hesai40/PointCloud2", 1, pandoraHandler);
//    imu_sub = nh.subscribe("/imu/data", 1, imuHandler);
//    gps_sub = nh.subscribe("/gps", 1, gpsHandler);
//    gps_pub = nh.advertise<nav_msgs::Odometry> ("odom_gps", 5);
//    natfix_sub = nh.subscribe("/gnss", 1, natfixHandler);

    ros::spin();
}
