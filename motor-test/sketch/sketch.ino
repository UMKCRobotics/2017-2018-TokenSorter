#include "ScrapController.h"

#define ENCODER_LEFT_INT 4
#define ENCODER_LEFT_DIG 5
#define ENCODER_RIGHT_INT 6
#define ENCODER_RIGHT_DIG 7
#define MOTOR_LEFT_D 8
#define MOTOR_LEFT_PWM 9
#define MOTOR_RIGHT_D 10
#define MOTOR_RIGHT_PWM 11



ScrapEncoder encoderL = ScrapEncoder(ENCODER_LEFT_INT,ENCODER_LEFT_DIG);
ScrapEncoder encoderR = ScrapEncoder(ENCODER_RIGHT_INT,ENCODER_RIGHT_DIG);

ScrapMotorSinglePin motorL = ScrapMotorSinglePin(MOTOR_LEFT_D,MOTOR_LEFT_PWM);
ScrapMotorSinglePin motorR = ScrapMotorSinglePin(MOTOR_RIGHT_D,MOTOR_RIGHT_PWM);

ScrapMotorControl motorControlL = ScrapMotorControl(motorL, encoderL);
ScrapMotorControl motorControlR = ScrapMotorControl(motorR, encoderR);

ScrapController singleControl = ScrapController(motorControlL);
ScrapDualController controller = ScrapDualController(motorControlL,motorControlR);


void setup() {

}
void loop() {

}
