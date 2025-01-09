/**!
 * @file pollMeasurement.ino
 * @brief Measures absolute range from 0 to above 10 cm 
 * @n Measurement of ambient light data
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-02-08
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_VL6180X
 */
#include <DFRobot_VL6180X.h>

I2C i2c(D12, A6);
//When the IIC address is changed, the address should be passed in when the class is instantiated. And it will be saved after its changing. 
//But if the sensor is restarted by using the CE pin, the IIC address will change back to the default address 0x29
//DFRobot_VL6180X VL6180X(/* iicAddr */0x29,/* TwoWire * */&Wire);
DFRobot_VL6180X VL6180X(VL6180X_IIC_ADDRESS, &i2c);

void setup() {
  while(!(VL6180X.begin())){
    printf("Please check that the IIC device is properly connected!\n");
    ThisThread::sleep_for(1000ms);
  }
  /*Change IIC address*/
  //VL6180X.setIICAddr(0×29);
}


void loop() {
  /*Poll measurement of ambient light data*/
  float lux = VL6180X.alsPoLLMeasurement();
  int mlux = (int)(lux*1000);
  printf("ALS: %i mlux, ", mlux);
  ThisThread::sleep_for(1000ms);
  /*Poll measurement of distance*/
  uint8_t range = VL6180X.rangePollMeasurement();
  /*Get the judgment of the range value*/
  uint8_t status = VL6180X.getRangeResult();
  switch(status){
  case VL6180X_NO_ERR:
    printf("Range: %i mm\n", range);
    break;
  case VL6180X_EARLY_CONV_ERR:
    printf("RANGE ERR: ECE check failed !\n");
    break;
  case VL6180X_MAX_CONV_ERR:
    printf("RANGE ERR: System did not converge before the specified max!\n");
    break;
  case VL6180X_IGNORE_ERR:
    printf("RANGE ERR: Ignore threshold check failed !\n");
    break;
  case VL6180X_MAX_S_N_ERR:
    printf("RANGE ERR: Measurement invalidated!\n");
    break;
  case VL6180X_RAW_Range_UNDERFLOW_ERR:
    printf("RANGE ERR: RESULT_RANGE_RAW < 0!\n");
    break;
  case VL6180X_RAW_Range_OVERFLOW_ERR:
    printf("RESULT_RANGE_RAW is out of range !\n");
    break;
  case VL6180X_Range_UNDERFLOW_ERR:
    printf("RANGE ERR: RESULT__RANGE_VAL < 0 !\n");
    break;
  case VL6180X_Range_OVERFLOW_ERR:
    printf("RANGE ERR: RESULT__RANGE_VAL is out of range !\n");
    break;
  default:
    printf("RANGE ERR: Systerm err! Error code %x\n", status);
    break;
  }

  ThisThread::sleep_for(1000ms);
  loop();
}

int main()
{
    setup();
    loop();
}