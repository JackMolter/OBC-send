#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/i2c.h"

#include "IMU.h"

uint8_t imu[6]; // stores accel data
static int addr = BMI088_ID; //0x18 when pin pulled to ground, accelerometer 
// static int addr = 0x69 gyroscope 


// Initialize IMU 
void imu_init(void){
    stdio_init_all();  

    // configure the I2C Communication
    i2c_init(I2C_PORT, BMI088_BAUD);
    gpio_set_function(BMI088_SDA, GPIO_FUNC_I2C);
    gpio_set_function(BMI088_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(BMI088_SDA);
    gpio_pull_up(BMI088_SCL);

    uint8_t data[2];

    // Reset IMU
    data[0] = ACC_SOFTRESET;
    data[1] = ACC_RESET;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(10);

    // turn accelerometer on
    data[0] = ACC_PWR_CTRL;
    data[1] = ACC_ON;  // normal mode 
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(10);

    // set range 
    data[0] = ACC_RANGE;
    data[1] = ACC_RANGE_3G;  // +- 3g 
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(10);

    // turn gyro off
    //data[0] = GYRO_LMP1;  // GYRO_LPM1 register
    //data[1] = GYRO_SUSPEND; // suspend mode 
    //i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    //sleep_ms(30);

}

void get_accel() {
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;

    uint8_t val = 0x12; // variable to hold data 

    i2c_write_blocking(I2C_PORT, addr, &val, 1, true);
    i2c_read_blocking(I2C_PORT, addr, imu, 6, false);

    accelX = (int16_t)((imu[1]<<8) | imu[0]);   // puts in MSB-LSB order 
    accelY = (int16_t)((imu[3]<<8) | imu[2]);
    accelZ = (int16_t)((imu[5]<<8) | imu[4]);
    //TODO: convert this to m/s and ouput those values instread of MSB/LSB 

    
}


/*
int main(void){
    stdio_init_all(); 

    // configure the I2C Communication
    i2c_init(I2C_PORT, BMI088_BAUD);
    gpio_set_function(BMI088_SDA, GPIO_FUNC_I2C);
    gpio_set_function(BMI088_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(BMI088_SDA);
    gpio_pull_up(BMI088_SCL);

    // 
    imu_init();

    uint8_t imu[6]; // stores data
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;

    int16_t x;
    int16_t y;
    int16_t z;
    int16_t xx;
    int16_t yy;
    int16_t zz;

    double X;
    double Y;
    double Z;
    //float f_accelX, f_accelY, f_accelZ;
    uint8_t val = 0x12;

    while(1){
        i2c_write_blocking(I2C_PORT, addr, &val, 1, true);
        i2c_read_blocking(I2C_PORT, addr, imu, 6, false);

        accelX = (int16_t)((imu[1]<<8) | imu[0]);
        accelY = (int16_t)((imu[3]<<8) | imu[2]);
        accelZ = (int16_t)((imu[5]<<8) | imu[4]);        

        x = imu[1]*256 + imu[0];
        y = imu[3]*256 + imu[2];
        z = imu[5]*256 + imu[4];
        //X = x / 32768 * 1000 * 2^(4);
        //Y = y / 32768 * 1000 * 2^(4);
        //Z = z / 32768 * 1000 * 2^(4);

        //X = (imu[1]*256 + imu[0]) / 32768 * 1000 * 2^(1);
        //Y = (imu[3]*256 + imu[2]) / 32768 * 1000 * 2^(1);
        //Z = (imu[5]*256 + imu[4]) / 32768 * 1000 * 2^(1);
        X = accelX ;
        Y = accelY ;
        Z = accelZ ;
        

        //int imu[1];
        // Print to serial monitor
        //printf("X: %.2f | Y: %.2f | Z: %.2f\r\n", X, Y, Z);
        //sleep_ms(300); 

        // temp stuff
        double temperature;
        int16_t temp_lsb;
        int16_t temp_msb;

        uint8_t tem = 0x22;
        uint8_t temp[2];

        i2c_write_blocking(I2C_PORT, addr, &tem, 1, true);
        i2c_read_blocking(I2C_PORT, addr, temp, 2, false);
        
        temperature = temp[1]*8 + temp[0] / 32;
        printf("Temperature: %.2f\n", temperature);
        sleep_ms(1500);
        

    }
}
*/