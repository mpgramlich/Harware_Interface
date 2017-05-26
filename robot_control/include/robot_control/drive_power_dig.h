#ifndef DRIVE_POWER_DIG_H
#define DRIVE_POWER_DIG_H
#include "task.h"

class DrivePowerDig : public Task
{
public:
	void init();
	int run();
private:
    float initX_;
    float initY_;
	float initHeading_;
	int driveSign_;
	int pivotSign_;
	float desiredDistance_;
	float remainingDistance_;
	float traversedDistance_;
	float deltaHeading_;
	float vMax_;
	float vDesRaw_;
	float vDesCoerc_;
	float rDes_;
	float errorR_;
	float yawRatePrev_;
	int leftSpeed_;
	int rightSpeed_;
	float headingErrorSpeedT_;
	float headingErrorSpeedP_;
	float headingErrorSpeedI_;
	unsigned int timeoutValue_;
	unsigned int timeoutCounter_;
    unsigned int timeoutMinValue_;
	int taskEnded_;
	const float vMin_ = 0.2; // m/s
	const float kpV_ = 2.0; // m/(s*m)
	const float kVOutput_ = 900/1.2; // 90% of max speed at 1.2 m/s
	const float kpR_ = 1.5; // deg/(s*deg)
	const float kiR_ = 0.1;
	const float kROutput_ = 450/45.0; // 45% of max speed at 45 deg/s
	const float rMax_ = 30.0; // deg/s
	const float maxHeadingErrorSpeed_ = 50.0;
	const float maxHeadingErrorSpeedI_ = 30.0;
};

#endif // DRIVE_POWER_DIG_H
