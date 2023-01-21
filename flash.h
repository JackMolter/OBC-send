// values
#define FLASH_BAUD 1000 * 1000 // for test 
#define FLASH_PAGE_SIZE 256
#define FLASH_SECTOR_SIZE 4096
#define RANDOM_DATA_SIZE 256
#define FLASH_CS_DELAY 100 // us

// vars
uint8_t dat[6];

// pins
#define FLASH_SPI spi0
#define FLASH_MOSI 3
#define FLASH_MISO 0
#define FLASH_SCK 2 
#define FLASH_CS 1

// commands
#define FLASH_DUMMY_BYTE 0x00
#define FLASH_READ_ID 0x4B
#define FLASH_WRITE_ENABLE 0x06
#define FLASH_READ_DATA 0x03
#define FLASH_WRITE_DATA 0x02
#define FLASH_ERASE_4 0x20
#define FLASH_ERASE_32 0x52
#define FLASH_ERASE_64 0xD8
#define FLASH_ERASE_CHIP 0xC7

#define FLASH_READ_REGISTER1 0x05 // probably the only useful one
#define FLASH_READ_REGISTER2 0x35
#define FLASH_READ_REGISTER3 0x15



// initialize functions 

// setup
void __not_in_flash_func(flash_setup)();

// write enable 
void __not_in_flash_func(flash_write_enable)(); 

// read status registers
void __not_in_flash_func(flash_read_register)();

// read data
// needs address of data to read, length of data
void __not_in_flash_func(flash_read_data)(uint32_t addr, uint8_t *buf, size_t len);

// write data
void __not_in_flash_func(flash_write_data)(uint32_t addr, uint8_t *buf, size_t len);

// 4k Erase
//  addr is start of 4k block address 
// Reases 4k-bytes of data, the erased state is all 1s.
void __not_in_flash_func(flash_erase_4k)(uint32_t addr);

// 32k erase
void __not_in_flash_func(flash_erase_32k)(uint32_t addr);

// 64k erase
void __not_in_flash_func(flash_erase_64k)(uint32_t addr);

// chip erase
void __not_in_flash_func(flash_erase_chip)();

// check if busy
int __not_in_flash_func(check_busy)();

// DMA
static inline void __not_in_flash_func(dma_done_handle)();
int64_t __not_in_flash_func(cs_alarm)();

void __not_in_flash_func(dma_do_stuff)();

// accelerometer stuff
void __not_in_flash_func(handle_accel)(uint32_t addr, uint8_t *buf, size_t len);