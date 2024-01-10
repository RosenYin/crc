/************************************************************************
 * @file: Do not edit
 * @author: xxx
 * @brief: xxx
 * @version: 1.0.0
 * @copyright: Copyright (c) tuya.inc 2021
 * @LastEditTime: 2022-03-22 11:36:22
 * https://seedeer.github.io/2022/03/20/crc/
 *************************************************************************/
#include <stdio.h>
#include "crc.h"
#include "CRC_Check.h"

int main()
{
    uint8_t data[5] = {0x5A,0x13,0x01};

    uint8_t data1[10] = {0xFE, 0x0F, 0x00, 00, 00, 01, 01, 00, 0xA0, 53};

    //uint8_t data[] = {0x5A,0x13,0x00,0xCF,0x2F};

    uint32_t crc = 0;
    crc = IOT_CRC16_XMODEM(&data[0], 3);
    printf("crc16-xmodem:%x\n", crc);

    uint32_t crc1 = 0;
    crc1 = IOT_CRC16_MODBUS(&data1[0], 8);
    printf("crc16-xmodem1:%x\n", crc1);

    data[3] = crc >> 8;
    data[4] = crc & 0xff;
    crc = IOT_CRC16_XMODEM(&data[0], 5);
    printf("crc16-xmodem:%x\n", crc);

    // 认为制造错误帧验证通过
    data[2] = 0x00;
    data[3] = 0xCF;
    data[4] = 0x2F;
    crc = IOT_CRC16_XMODEM(&data[0], 5);
    printf("crc16-xmodem:%x\n", crc);
    
    generate_crc8_table((uint8_t)0x31);
    generate_crc16_table((uint16_t)0x1021);
    
    uint8_t pcTxBuf[4];
	pcTxBuf[0] = 0x00;
	pcTxBuf[1] = 0x00;
	pcTxBuf[2] = 0x00;
	Append_CRC8_Check_Sum(pcTxBuf,4);
    uint8_t verify_flag;
    verify_flag = Verify_CRC8_Check_Sum(pcTxBuf,4);
    printf("%02x\n",verify_flag);
    return 0;
}


