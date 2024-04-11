#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int received_data[] = {0x2A,
                      0x54, 0x01, 0x00, 0x00,
                      0xFF, 0x00, 0x00, 0x00,
                      0x01, 0x00, 0x00, 0x00, 
                      0x02, 0x00, 0x00, 0x00,
                      0x03, 0x00, 0x00, 0x00};
//---pitch---
    int num1 = received_data[4];
    int num2 = received_data[3];
    int num3 = received_data[2];
    int num4 = received_data[1];
    // 将数字转换为字符串
    char str_num1[3];
    char str_num2[3];
    char str_num3[3];
    char str_num4[3];
    sprintf(str_num1, "%X", num1);
    sprintf(str_num2, "%X", num2);
    sprintf(str_num3, "%X", num3);
    sprintf(str_num4, "%X", num4);
    // 拼接字符串
    char result[12];
    strcpy(result, str_num1);
    strcat(result, str_num2);
    strcat(result, str_num3);
    strcat(result, str_num4);
    long int result_1_decimal = strtol(result, NULL, 16);    // 将十六进制字符串转换为十进制整数
//---yaw---
    num1 = received_data[8];
    num2 = received_data[7];
    num3 = received_data[6];
    num4 = received_data[5];
    sprintf(str_num1, "%X", num1);
    sprintf(str_num2, "%X", num2);
    sprintf(str_num3, "%X", num3);
    sprintf(str_num4, "%X", num4);

    // 拼接字符串
    strcpy(result, str_num1);
    strcat(result, str_num2);
    strcat(result, str_num3);
    strcat(result, str_num4);

    int result_2_decimal = strtol(result, NULL, 16);    // 将十六进制字符串转换为十进制整数

    float pitch = (float)(result_1_decimal)/100;
    float yaw = (float)(result_2_decimal)/100;
    printf("pitch: %f\n", pitch);
    printf("yaw: %f\n", yaw);
    printf("%d",received_data[4]);
    return 0;
}
