// Generated by gencpp from file apriltags/AprilTagDetection.msg
// DO NOT EDIT!


#ifndef APRILTAGS_MESSAGE_APRILTAGDETECTION_H
#define APRILTAGS_MESSAGE_APRILTAGDETECTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Pose.h>

namespace apriltags
{
template <class ContainerAllocator>
struct AprilTagDetection_
{
  typedef AprilTagDetection_<ContainerAllocator> Type;

  AprilTagDetection_()
    : header()
    , id(0)
    , corners2d()
    , tag_size(0.0)
    , pose()  {
    }
  AprilTagDetection_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , id(0)
    , corners2d()
    , tag_size(0.0)
    , pose(_alloc)  {
  (void)_alloc;
      corners2d.assign( ::geometry_msgs::Point32_<ContainerAllocator> (_alloc));
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint32_t _id_type;
  _id_type id;

   typedef boost::array< ::geometry_msgs::Point32_<ContainerAllocator> , 4>  _corners2d_type;
  _corners2d_type corners2d;

   typedef float _tag_size_type;
  _tag_size_type tag_size;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _pose_type;
  _pose_type pose;




  typedef boost::shared_ptr< ::apriltags::AprilTagDetection_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::apriltags::AprilTagDetection_<ContainerAllocator> const> ConstPtr;

}; // struct AprilTagDetection_

typedef ::apriltags::AprilTagDetection_<std::allocator<void> > AprilTagDetection;

typedef boost::shared_ptr< ::apriltags::AprilTagDetection > AprilTagDetectionPtr;
typedef boost::shared_ptr< ::apriltags::AprilTagDetection const> AprilTagDetectionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::apriltags::AprilTagDetection_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::apriltags::AprilTagDetection_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace apriltags

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'apriltags': ['/home/fregu856/TSRT10/catkin_ws/src/apriltags/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::apriltags::AprilTagDetection_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::apriltags::AprilTagDetection_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::apriltags::AprilTagDetection_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::apriltags::AprilTagDetection_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::apriltags::AprilTagDetection_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::apriltags::AprilTagDetection_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::apriltags::AprilTagDetection_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cbbc500741705b6142a546b4696bb7f5";
  }

  static const char* value(const ::apriltags::AprilTagDetection_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcbbc500741705b61ULL;
  static const uint64_t static_value2 = 0x42a546b4696bb7f5ULL;
};

template<class ContainerAllocator>
struct DataType< ::apriltags::AprilTagDetection_<ContainerAllocator> >
{
  static const char* value()
  {
    return "apriltags/AprilTagDetection";
  }

  static const char* value(const ::apriltags::AprilTagDetection_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::apriltags::AprilTagDetection_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Message storing raw 2D and 3D information about a single AprilTag detection.\n\
Header header\n\
uint32 id  # id of AprilTag (not necessarily unique)\n\
geometry_msgs/Point32[4] corners2d  # AprilTag corners in image\n\
float32 tag_size  # tag size in m\n\
geometry_msgs/Pose pose  # pose of the marker in the camera frame\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point32\n\
# This contains the position of a point in free space(with 32 bits of precision).\n\
# It is recommeded to use Point wherever possible instead of Point32.  \n\
# \n\
# This recommendation is to promote interoperability.  \n\
#\n\
# This message is designed to take up less space when sending\n\
# lots of points at once, as in the case of a PointCloud.  \n\
\n\
float32 x\n\
float32 y\n\
float32 z\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::apriltags::AprilTagDetection_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::apriltags::AprilTagDetection_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.id);
      stream.next(m.corners2d);
      stream.next(m.tag_size);
      stream.next(m.pose);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct AprilTagDetection_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::apriltags::AprilTagDetection_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::apriltags::AprilTagDetection_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.id);
    s << indent << "corners2d[]" << std::endl;
    for (size_t i = 0; i < v.corners2d.size(); ++i)
    {
      s << indent << "  corners2d[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Point32_<ContainerAllocator> >::stream(s, indent + "    ", v.corners2d[i]);
    }
    s << indent << "tag_size: ";
    Printer<float>::stream(s, indent + "  ", v.tag_size);
    s << indent << "pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.pose);
  }
};

} // namespace message_operations
} // namespace ros

#endif // APRILTAGS_MESSAGE_APRILTAGDETECTION_H
