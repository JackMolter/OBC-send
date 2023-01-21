
// values 
#define I2C_PORT i2c0
#define BMI088_BAUD 400000 // ? from video example
#define ACCEL_DATA_LEN 6
#define BMI088_ID 0x19

// pins
#define BMI088_SDA 8
#define BMI088_SCL 9

// vars 
// Accelerometer 
#define ACC_SOFTRESET 0x7E  // reset
#define ACC_RESET 0xB6

#define ACC_PWR_CTRL 0x7D   // power on or off
#define ACC_ON 0x04
#define ACC_OFF 

#define ACC_RANGE 0x41  // set the max ranges 
#define ACC_RANGE_3G 0x00
#define ACC_RANGE_6G 0x01
#define ACC_RANGE_12G 0x02
#define ACC_RANGE_24G 0x03

// Gyroscope 
#define GYRO_LMP1 0x11  // turn gyro on or suspend 
#define GYRO_NORMAL 0x00
#define GYRO_SUSPEND 0x80

#define GYRO_RANGE 0x0F     // range rate 
#define GYRO_RANGE_2000 0x00
#define GYRO_RANGE_1000 0x01
#define GYRO_RANGE_500 0x02
#define GYRO_RANGE_250 0x3
#define GYRO_RANGE_125 0x04

#define GYRO_BANDWIDTH 0x10     // Bandwidth and output data rate 
#define GYRO_BANDWIDTH_532 0x00
#define GYRO_BANDWIDTH_230 0x01
#define GYRO_BANDWIDTH_116 0x02
#define GYRO_BANDWIDTH_47 0x03
#define GYRO_BANDWIDTH_23 0x04
#define GYRO_BANDWIDTH_12 0x05  // ODR = 100
#define GYRO_BANDWIDTH_64 0x06  // ODR = 200
#define GYRO_BANDWIDTH_32 0x07  // ODR = 100

// functions
// initilizations 
void imu_init();

// get accelerometer data
void get_accel();
