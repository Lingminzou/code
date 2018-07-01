
## aes 示例 加密一个 bin 文件

key 写在 key.txt 文件中

特殊的要求 bin 文件的大小是 128 的倍数，不足的要填充 0x1A

使用：./aes -i input.bin -k key.txt

程序思路：

1、先读取 16 位的 key
2、对原文件按 128 的倍数进行填充到已个临时文件 tmp.bin
3、对 tmp.bin 进行加密生成 enc.bin


注：aes lib 来自于：https://github.com/kokke/tiny-AES-c
