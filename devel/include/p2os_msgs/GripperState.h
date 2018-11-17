// Generated by gencpp from file p2os_msgs/GripperState.msg
// DO NOT EDIT!


#ifndef P2OS_MSGS_MESSAGE_GRIPPERSTATE_H
#define P2OS_MSGS_MESSAGE_GRIPPERSTATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <p2os_msgs/GripState.h>
#include <p2os_msgs/LiftState.h>

namespace p2os_msgs
{
template <class ContainerAllocator>
struct GripperState_
{
  typedef GripperState_<ContainerAllocator> Type;

  GripperState_()
    : grip()
    , lift()  {
    }
  GripperState_(const ContainerAllocator& _alloc)
    : grip(_alloc)
    , lift(_alloc)  {
  (void)_alloc;
    }



   typedef  ::p2os_msgs::GripState_<ContainerAllocator>  _grip_type;
  _grip_type grip;

   typedef  ::p2os_msgs::LiftState_<ContainerAllocator>  _lift_type;
  _lift_type lift;





  typedef boost::shared_ptr< ::p2os_msgs::GripperState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::p2os_msgs::GripperState_<ContainerAllocator> const> ConstPtr;

}; // struct GripperState_

typedef ::p2os_msgs::GripperState_<std::allocator<void> > GripperState;

typedef boost::shared_ptr< ::p2os_msgs::GripperState > GripperStatePtr;
typedef boost::shared_ptr< ::p2os_msgs::GripperState const> GripperStateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::p2os_msgs::GripperState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::p2os_msgs::GripperState_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace p2os_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'p2os_msgs': ['/home/dannyel/catkin_ws/src/p2os/p2os_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::p2os_msgs::GripperState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::p2os_msgs::GripperState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::p2os_msgs::GripperState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::p2os_msgs::GripperState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::p2os_msgs::GripperState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::p2os_msgs::GripperState_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::p2os_msgs::GripperState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "300b38b2a4173deb725df02fa70fc70b";
  }

  static const char* value(const ::p2os_msgs::GripperState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x300b38b2a4173debULL;
  static const uint64_t static_value2 = 0x725df02fa70fc70bULL;
};

template<class ContainerAllocator>
struct DataType< ::p2os_msgs::GripperState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "p2os_msgs/GripperState";
  }

  static const char* value(const ::p2os_msgs::GripperState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::p2os_msgs::GripperState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "GripState grip\n\
LiftState lift\n\
\n\
================================================================================\n\
MSG: p2os_msgs/GripState\n\
# direction -1 is inward, +1 is outward, 0 is stationary\n\
uint32 state\n\
int32 dir\n\
bool inner_beam\n\
bool outer_beam\n\
bool left_contact\n\
bool right_contact\n\
\n\
================================================================================\n\
MSG: p2os_msgs/LiftState\n\
# direction -1 is downard, +1 is upward, 0 is stationary\n\
int32 state\n\
int32 dir\n\
float32 position\n\
";
  }

  static const char* value(const ::p2os_msgs::GripperState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::p2os_msgs::GripperState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.grip);
      stream.next(m.lift);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GripperState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::p2os_msgs::GripperState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::p2os_msgs::GripperState_<ContainerAllocator>& v)
  {
    s << indent << "grip: ";
    s << std::endl;
    Printer< ::p2os_msgs::GripState_<ContainerAllocator> >::stream(s, indent + "  ", v.grip);
    s << indent << "lift: ";
    s << std::endl;
    Printer< ::p2os_msgs::LiftState_<ContainerAllocator> >::stream(s, indent + "  ", v.lift);
  }
};

} // namespace message_operations
} // namespace ros

#endif // P2OS_MSGS_MESSAGE_GRIPPERSTATE_H
