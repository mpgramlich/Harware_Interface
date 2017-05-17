#include <robot_control/initialize.h>

bool Initialize::runProc()
{
    switch(state)
    {
    case _init_:
        procsBeingExecuted[procType] = true;
        procsToExecute[procType] = false;
        procsToResume[procType] = false;
        computeDriveSpeeds();
        state = _exec_;
        stage = _initialRaiseArm;
        sendRaiseArm();
        initComplete = false;
        rotateDeltaAngle = 25.0; // deg
        resetQueueEmptyCondition();
        break;
    case _exec_:
        procsBeingExecuted[procType] = true;
        procsToExecute[procType] = false;
        procsToResume[procType] = false;
        computeDriveSpeeds();
        switch(stage)
        {
        case _startTimer:
            startupTime = ros::Time::now().toSec();
            performFullPoseUpdate = true;
            stage = _checkFullPose;
            break;
        case _checkFullPose:
            if(robotStatus.initialFullPoseFound)
            {

            }
            else if((ros::Time::now().toSec() - startupTime) > waitForFullPoseTime)
            {
                sendDriveRel(0.0, rotateDeltaAngle, false, 0.0, false, false);
                stage = _rotate;
            }
            else stage = _checkFullPose;
            break;
        case _rotate:
            if((execLastProcType == procType && execLastSerialNum == serialNum) || queueEmptyTimedOut) stage = _startTimer;
            else stage = _rotate;
            break;
        case _backUp:

            break;
        case _initialRaiseArm:
            if((execLastProcType == procType && execLastSerialNum == serialNum) || queueEmptyTimedOut)
            {
                initComplete = true;
            }
            else stage = _initialRaiseArm;
            break;
        }
        if(initComplete) state = _finish_;
        else state = _exec_;
        serviceQueueEmptyCondition();
        break;
    case _interrupt_:
        procsBeingExecuted[procType] = false;
        procsToInterrupt[procType] = false;
        state = _exec_;
        break;
    case _finish_:
        initialized = true;
        procsBeingExecuted[procType] = false;
        procsToExecute[procType] = false;
        procsToResume[procType] = false;
        state = _finish_;
        break;
    }
}
