// values 
#define I2C_PORT i2c0
#define BMI088_BAUD 112800 // ? from video example

// pins
#define BMI088_SDA 8
#define BMI088_SCL 9

// functions

// initilizations 
void imu_init();

// get accelerometer data
void get_accel();
