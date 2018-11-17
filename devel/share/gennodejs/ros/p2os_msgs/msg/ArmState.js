// Auto-generated. Do not edit!

// (in-package p2os_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ArmState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.arm_power = null;
    }
    else {
      if (initObj.hasOwnProperty('arm_power')) {
        this.arm_power = initObj.arm_power
      }
      else {
        this.arm_power = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ArmState
    // Serialize message field [arm_power]
    bufferOffset = _serializer.bool(obj.arm_power, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ArmState
    let len;
    let data = new ArmState(null);
    // Deserialize message field [arm_power]
    data.arm_power = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'p2os_msgs/ArmState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f78f2c49a110ba43464d5c16d2a19027';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool arm_power
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ArmState(null);
    if (msg.arm_power !== undefined) {
      resolved.arm_power = msg.arm_power;
    }
    else {
      resolved.arm_power = false
    }

    return resolved;
    }
};

module.exports = ArmState;