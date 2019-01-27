
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TLOG_LEVEL  TLOG_LEVEL_DEBUG
#define TLOG_TAG    "tlog_test"
#include "src/tlog.h"

int main(int argc, char *argv[])
{
    tlog_d("hello world!");
    tlog_i("hello world!");
    tlog_w("hello world!");
    tlog_e("hello world!");

    return 0;
}


