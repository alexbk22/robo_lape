// Generated by gencpp from file tf2_msgs/LookupTransformActionGoal.msg
// DO NOT EDIT!


#ifndef TF2_MSGS_MESSAGE_LOOKUPTRANSFORMACTIONGOAL_H
#define TF2_MSGS_MESSAGE_LOOKUPTRANSFORMACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <tf2_msgs/LookupTransformGoal.h>

namespace tf2_msgs
{
template <class ContainerAllocator>
struct LookupTransformActionGoal_
{
  typedef LookupTransformActionGoal_<ContainerAllocator> Type;

  LookupTransformActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  LookupTransformActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::tf2_msgs::LookupTransformGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct LookupTransformActionGoal_

typedef ::tf2_msgs::LookupTransformActionGoal_<std::allocator<void> > LookupTransformActionGoal;

typedef boost::shared_ptr< ::tf2_msgs::LookupTransformActionGoal > LookupTransformActionGoalPtr;
typedef boost::shared_ptr< ::tf2_msgs::LookupTransformActionGoal const> LookupTransformActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace tf2_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geometry_msgs': ['/home/pi/git/robo_lape/src/common_msgs/geometry_msgs/msg'], 'actionlib_msgs': ['/home/pi/git/robo_lape/src/common_msgs/actionlib_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'tf2_msgs': ['/home/pi/git/robo_lape/src/geometry2/tf2_msgs/msg', '/home/pi/git/robo_lape/devel/share/tf2_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f2e7bcdb75c847978d0351a13e699da5";
  }

  static const char* value(const ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf2e7bcdb75c84797ULL;
  static const uint64_t static_value2 = 0x8d0351a13e699da5ULL;
};

template<class ContainerAllocator>
struct DataType< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tf2_msgs/LookupTransformActionGoal";
  }

  static const char* value(const ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
LookupTransformGoal goal\n\
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
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: tf2_msgs/LookupTransformGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
#Simple API\n\
string target_frame\n\
string source_frame\n\
time source_time\n\
duration timeout\n\
\n\
#Advanced API\n\
time target_time\n\
string fixed_frame\n\
\n\
#Whether or not to use the advanced API\n\
bool advanced\n\
\n\
";
  }

  static const char* value(const ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LookupTransformActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tf2_msgs::LookupTransformActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::tf2_msgs::LookupTransformGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TF2_MSGS_MESSAGE_LOOKUPTRANSFORMACTIONGOAL_H
