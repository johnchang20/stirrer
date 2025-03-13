#include "rpmToCLK.h"
#include <stdio.h>
#include <QString>
#include <string>
#include <iostream>

void motor1_control(int rpm1,int rmp2,int rpm3)
{
    /* relatinship :
     * rpm
     * CLK frequence HZ (motor driver IC)
     * step_operation(motor driver IC full 1/2 1/4 1/8 1/16 1/32)
     * step_angle(step motor 0.9° 1.8° )
     */
    int CLK1 = 0;
    int CLK2 = 0;
    int CLK3 = 0;
    float step_operation = 32;
    float step_angle = 0.9;
    /*base on this formula
     *
     *                 Pulse Frequency×60
     * Speed(rmp) = ------------------------
     *                 Steps per Revolution
     *
     *                             360
     * Steps per Revolution = -------------
     *                          step_angle
     *
     *         Pulse Frequency*step_angle
     * rmp = -----------------------------
     *             6*step_operation
     */
    CLK1 = (int)((6*rpm1*step_operation)/step_angle);
    CLK2 = (int)((6*rmp2*step_operation)/step_angle);
    CLK3 = (int)((6*rpm3*step_operation)/step_angle);
    printf("CLK1 = %d, CLK2 = %d,CLK3 = %d\n",CLK1,CLK2,CLK3);

    int period1 = 1000000000/CLK1;
    int dutycycle1 = period1/2;

    std::string period= std::to_string(period1);
    std::string dutycycle= std::to_string(dutycycle1);
    std::string periodpath = "/sys/class/pwm/pwmchip1/pwm0/period";
    std::string dutycyclepath = "/sys/class/pwm/pwmchip1/pwm0/duty_cycle";

    system("echo 0 > /sys/class/pwm/pwmchip1/export");

    std::string commandperiod = "echo " + period + " > " + periodpath;
    system(commandperiod.c_str());
    std::string commanddutycycle = "echo " + dutycycle + " > " + dutycyclepath;
    system(commanddutycycle.c_str());
    system("echo 1 > /sys/class/pwm/pwmchip1/pwm0/enable");

}
