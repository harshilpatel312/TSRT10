#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64MultiArray
from std_msgs.msg import String
from nav_msgs.msg import OccupancyGrid

import numpy as np

def frontier_func(slamMap, currentPosition):
    rows, cols = slamMap.shape
    frontierMap = np.zeros(shape=(rows,cols))
    #print slamMap
    slamMapNoObstacles = slamMap
    slamMapNoObstacles[slamMapNoObstacles == -2] = 0    #Covered
    slamMapNoObstacles[slamMapNoObstacles == 100] = 0   #Obstacle]
    #print slamMapNoObstacles
    tempMapA = np.vstack( [ np.zeros(shape=(1,rows)), slamMapNoObstacles ] )
    #print tempMapA
    tempMap1 = np.column_stack( [ np.zeros(shape=(cols+1,1)), tempMapA ] )
    #print tempMap1
    tempMapB = np.vstack( [ slamMapNoObstacles, np.zeros(shape=(1,rows)) ] )
    tempMap2 = np.column_stack( [ tempMapB, np.zeros(shape=(cols+1,1)) ] )
    #print tempMapB
    #print tempMap2
    frontierNodes = tempMap2 - tempMap1 ## 16x16
    #print frontierNodes
    FirstMap = frontierNodes[0:-1,0:-1]
    #print FirstMap
    SecondMap = frontierNodes[1:,1:]
    #print SecondMap

    frontierMap[FirstMap == -1] = 1
    frontierMap[SecondMap == 1] = 1
    #print frontierMap
    tempMapC = np.vstack( [ slamMapNoObstacles, np.zeros(shape=(1,cols)) ] )
    tempMap3 = np.column_stack( [ np.zeros(shape=(cols+1,1)), tempMapC ] )
    tempMapD = np.column_stack( [ slamMapNoObstacles, np.zeros(shape=(rows,1)) ] )
    tempMap4 = np.vstack( [ np.zeros(shape=(1,cols+1)), tempMapD  ] )
    frontierNodes = tempMap3 - tempMap4
    #print frontierNodes

    FirstMap = frontierNodes[:-1,1:]
    SecondMap = frontierNodes[1:,0:-1]
    frontierMap[FirstMap == -1] = 1
    frontierMap[SecondMap == 1] = 1
    #print frontierMap
    # Remove covered area and obstacles as frontier candidates
    frontierMap[slamMap == 100] = 0
    frontierMap[slamMap == -2] = 0
    #print frontierMap
    x = np.nonzero(frontierMap)
    goalNode = np.argmin(((x[0]-currentPosition[0])**2 + (x[1]-currentPosition[1])**2)**0.5)

    return [x[0][goalNode],x[1][goalNode]]

def map_index_2_pos(map_msg, pos_index):
    map_origin_obj = map_msg.info.origin
    map_origin = [map_origin_obj.position.x, map_origin_obj.position.y]

    map_resolution = map_msg.info.resolution

    x_map_ind = pos_index[0]
    y_map_ind = pos_index[1]

    x_map = x_map_ind*map_resolution
    y_map = y_map_ind*map_resolution

    x = x_map + map_origin[0]
    y = y_map + map_origin[1]

    pos = [x, y]

    return pos

def pos_2_map_index(map_msg, pos):
    map_origin_obj = map_msg.info.origin
    map_origin = [map_origin_obj.position.x, map_origin_obj.position.y]

    map_resolution = map_msg.info.resolution

    x = pos[0]
    y = pos[1]

    x_map = x - map_origin[0]
    y_map = y - map_origin[1]

    x_map_ind = int(x_map/map_resolution) # (col)
    y_map_ind = int(y_map/map_resolution) # (row)

    pos_index = [x_map_ind, y_map_ind]

    return pos_index

def map_msg_2_matrix(map_msg):
    map_data = map_msg.data
    map_height = map_msg.info.height

    # convert the map data from a list into a numpy array:
    map_matrix = np.array(map_data)
    # split the array into a list of map_height arrays (each list element is a row):
    map_matrix = np.split(map_matrix, map_height)
    # convert the list of arrays into a 2D array:
    map_matrix = np.array(map_matrix)

    return map_matrix

class Frontier:
    def __init__(self):
        # initialize this code as a ROS node named nav_frontier_node:
        rospy.init_node("nav_frontier_node", anonymous=True)

        rospy.Subscriber("/map", OccupancyGrid, self.map_callback)

        rospy.Subscriber("/estimated_pose", Float64MultiArray, self.est_pose_callback)

        # subscribe to the topic onto which the controller publishes data once
        # it has reached a goal position:
        rospy.Subscriber("/controller_status", String, self.controller_callback)

        # create a publisher for publishing goal positions to the controller:
        self.goal_pos_pub = rospy.Publisher("/goal_pos", Float64MultiArray, queue_size=10)

        self.map_msg = None
        self.x = None
        self.y = None
        self.theta = None

        msg = Float64MultiArray()
        msg.data = [0, 0]
        self.goal_pos_pub.publish(msg)

        # keep python from exiting until this ROS node is stopped:
        rospy.spin()

    # define the callback function for the /map subscriber:
    def map_callback(self, msg_obj):
        self.map_msg = msg_obj

        print "map_callback"

    # define the callback function for the /estimated_pose subscriber:
    def est_pose_callback(self, msg_obj):
        pose = msg_obj.data

        self.x = pose[0]
        self.y = pose[1]
        self.theta = pose[2]

        print "est_pose_callback"

    # define the callback function for the /controller_status subscriber:
    def controller_callback(self, msg_obj):
        # get the recived string:
        msg_string = msg_obj.data

        if msg_string == "reached target position":
            goal_pos = self.get_goal_pos()
            if goal_pos is not None:
                # publish the goal position:
                msg = Float64MultiArray()
                msg.data = goal_pos
                self.goal_pos_pub.publish(msg)

    def get_goal_pos(self):
        if self.map_msg is not None and self.x is not None and self.y is not None:
            map_msg = self.map_msg
            x = self.x
            y = self.y
            pos = [x, y]

            map_matrix = map_msg_2_matrix(map_msg)
            print map_matrix
            print map_matrix.shape

            pos_index = pos_2_map_index(map_msg, pos)
            print pos
            print pos_index
            print map_index_2_pos(map_msg, pos_index)

            goal_pos_index = frontier_func(map_matrix, pos_index)
            print goal_pos_index

            goal_pos = map_index_2_pos(map_msg, goal_pos_index)
            print goal_pos

            return goal_pos
        else:
            return None

    # def run(self):
    #     rate = rospy.Rate(1) # (1 Hz)
    #     while not rospy.is_shutdown():
    #         goal_pos = self.get_goal_pos()
    #         rate.sleep() # (to get it to loop with 1 Hz)

if __name__ == "__main__":
    # create a Frontier object (this will run its __init__ function):
    frontier = Frontier()

    #frontier.run()
