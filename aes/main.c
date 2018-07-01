
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>

#define CBC 1
#define CTR 1
#define ECB 1
#include "aes.h"

static const char* optString = "i:k:h?";

static const char* helpmsg = "$ aes -i input_file -k key_file\r\n";

#define AES_KEY_LEN  16

static uint8_t key[AES_KEY_LEN] = {0x00};

#define AES_BLOCKLEN 16
#define PACKET_LEN   128
static uint8_t buffer[PACKET_LEN] = {0x00};

int main(int argc, char *argv[])
{
    int opt = 0;
    char *input_file = NULL;
    char *key_file = NULL;

    do
    {
        opt = getopt(argc, argv, optString);

        switch(opt)
        {
        case 'i':
            input_file = optarg;
            break;
        case 'k':
            key_file = optarg;
            break;
        case 'h':
        case '?':
            printf("%s", helpmsg);
            break;
        default:
            break;
        }
    }while(-1 != opt);

    if(NULL == input_file || NULL == key_file)
    {
        printf("%s", helpmsg);
        return -1;
    }

    /* read key *************************************************/
    int fd = open(key_file, O_RDONLY);

    if(fd < 0)
    {
        printf("open key file error!!!\r\n");
        return -1;
    }

    int count = read(fd, key, AES_KEY_LEN);

    if(count < AES_KEY_LEN)
    {
       printf("warning, the key length less %d\r\n", AES_KEY_LEN); 
    }

    printf("key: %s\r\n", key);

    close(fd);

    /* padding input file, padding 0x1A *****************************************/
    fd = open(input_file, O_RDONLY);

    if(fd < 0)
    {
        printf("open input file error!!!\r\n");
        return -1;
    }

    int tmp_fd = open("tmp.bin", O_WRONLY | O_CREAT | O_TRUNC);

    if(tmp_fd < 0)
    {
        printf("creat tmp.bin error!!!\r\n");
        return -1;
    }

    while(1)
    {
        int count = read(fd, buffer, PACKET_LEN);

        if(PACKET_LEN == count)
        {
            write(tmp_fd, buffer, count);
        }
        else if(count > 0x00)
        {
            for(int i = count; i != PACKET_LEN; i++)
            {
                buffer[i] = 0x1A;
            }

            write(tmp_fd, buffer, PACKET_LEN);
        }
        else
        {
            close(fd);
            close(tmp_fd);
            break;
        }
    }

    /* encrypt file out enc.bin************************************************/
    fd = open("tmp.bin", O_RDONLY);

    if(fd < 0)
    {
        printf("open tmp.bin error!!!\r\n");
        return -1;
    }

    int enc_fd = open("enc.bin", O_WRONLY | O_CREAT | O_TRUNC);

    if(enc_fd < 0)
    {
        printf("creat enc.bin error!!!\r\n");
        return -1;
    }

    struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);

    while(1)
    {
        int count = read(fd, buffer, AES_BLOCKLEN);

        if(count > 0)
        {
            AES_ECB_encrypt(&ctx, buffer);

            write(enc_fd, buffer, count);
        }
        else
        {
            close(fd);
            close(enc_fd);
            break;
        }
    }

    printf("encrypt %s finish!!!\r\n", input_file);

    return 0x00;
}

