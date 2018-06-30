#include <stdio.h>
#include <stdint.h>

union sys_bit_data
{
    uint8_t  byte;
    struct
    {
        uint8_t  bit0:1;
        uint8_t  bit1:1;
        uint8_t  bit2:1;
        uint8_t  bit3:1;
        uint8_t  bit4:1;
        uint8_t  bit5:1;
        uint8_t  bit6:1;
        uint8_t  bit7:1;
    } bit;
};

union sys_bit_data sys_flg[2];

#define g_sys_init_flg            (sys_flg[0].bit.bit0)
#define g_sys_led_flash_flg       (sys_flg[0].bit.bit1)

typedef struct
{
    uint8_t sys_init_flg:1;
    uint8_t sys_led_flash_flg:1;
    uint8_t bit2:1;
    uint8_t bit3:1;
    uint8_t bit4:1;
    uint8_t bit5:1;
    uint8_t bit6:1;
    uint8_t bit7:1;
} sys_status_st_flg;

sys_status_st_flg sys_status_flg;

int main(int argc, char *argv[])
{
    printf("hello world, the union sample...\r\n");
    
    g_sys_init_flg = 1;
    g_sys_led_flash_flg = 0;

    sys_status_flg.sys_init_flg = 1;
    sys_status_flg.sys_led_flash_flg = 0;

    printf("g_sys_init_flag: %d, g_sys_led_flash_flg: %d \r\n", g_sys_init_flg, g_sys_led_flash_flg);

    return 0x00;
}

