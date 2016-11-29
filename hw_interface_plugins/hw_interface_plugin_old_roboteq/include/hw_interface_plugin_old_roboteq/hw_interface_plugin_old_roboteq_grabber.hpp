#ifndef HW_INTERFACE_PLUGIN_OLD_ROBOTEQ_GRABBER_HPP__
#define HW_INTERFACE_PLUGIN_OLD_ROBOTEQ_GRABBER_HPP__

#include <ros/ros.h>

#include <pluginlib/class_list_macros.h>

#include <hw_interface/bit_utils.h>
#include <hw_interface_plugin_old_roboteq/hw_interface_plugin_old_roboteq.hpp>

#include <messages/ActuatorOut.h>
#include <messages/encoder_data.h>

namespace hw_interface_plugin_old_roboteq {


    class roboteq_grabber : public hw_interface_plugin_old_roboteq::roboteq_serial
    {
        public:
            roboteq_grabber(){
                if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
                       ros::console::notifyLoggerLevelsChanged();
                    }
            }

            void rosMsgCallback(const messages::ActuatorOut::ConstPtr &msgIn);

        protected:
            messages::encoder_data lastMsgPub;

            bool implInit();
            bool implStart();
            bool implStop();
            bool implDataHandler(const long &length, int arrayStartPos);

            bool implChecksum();
    };


}

PLUGINLIB_EXPORT_CLASS(hw_interface_plugin_old_roboteq::roboteq_grabber, base_classes::base_interface)

#endif //HW_INTERFACE_PLUGIN_OLD_ROBOTEQ_GRABBER_HPP__
