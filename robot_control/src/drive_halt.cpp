#include <robot_control/drive_halt.h>

void DriveHalt::init()
{
	robotOutputs.flMotorSpeed = 0;
	robotOutputs.blMotorSpeed = 0;
	robotOutputs.frMotorSpeed = 0;
	robotOutputs.brMotorSpeed = 0;
    robotOutputs.stopFlag = false;
    robotOutputs.turnFlag = false;
}

int DriveHalt::run()
{
	robotOutputs.flMotorSpeed = 0;
	robotOutputs.mlMotorSpeed = 0;
	robotOutputs.blMotorSpeed = 0;
	robotOutputs.frMotorSpeed = 0;
	robotOutputs.mrMotorSpeed = 0;
	robotOutputs.brMotorSpeed = 0;
	robotOutputs.stopFlag = true;
	robotOutputs.turnFlag = false;
	state_ = _noHold;
	return 1;
}
