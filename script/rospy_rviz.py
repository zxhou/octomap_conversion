#!/usr/bin/env python
# coding=utf-8
 
import os
import numpy as np
import rospy
 
 
from visualization_msgs.msg import *
from sensor_msgs.msg import PointCloud2
from sensor_msgs import point_cloud2 as pc2
#import pcl.pcl_visualization
 
 
def get_data():
    file_name = list()
 
    file_path = rospy.get_param('file_path', "")  # 获取一个全局参数
 
    for filename in os.listdir(file_path):
        filename = os.path.join(file_path, filename)
        if filename.split('.')[-1] == "bin":
            # print(filename.split('/')[-1])
            file_name.append(filename.split('/')[-1])
    # print(file_name)
    return file_name
 
 
def main():
    rospy.init_node("point_cloud", anonymous=True)
 
    rate = rospy.Rate(10)
 
    pub_cloud = rospy.Publisher("/point_cloud", PointCloud2, queue_size=100)
 
    point_cloud2 = PointCloud2()
    point_cloud2.header.frame_id = "robotcar"
 
    file_path = rospy.get_param('file_path', "")  # 获取一个全局参数
    file_name = get_data()
    for file in file_name:
        #print(file)
        point_data = np.fromfile((file_path + file), dtype=np.float64, count=-1).reshape([-1, 3])

        point_cloud2.header.stamp = rospy.Time(int(file.split('.')[0][:10]), int(file.split('.')[0][10:]+'000'))
        cloud = pc2.create_cloud_xyz32(point_cloud2.header, point_data[:, :3])
 
        pub_cloud.publish(cloud)
 
        # 控制发布频率
        rate.sleep()
 
if __name__ == "__main__":    
    main()    