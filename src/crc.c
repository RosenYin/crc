/************************************************************************
 * @file: Do not edit
 * @author: xxx
 * @brief: xxx
 * @version: 1.0.0
 * @copyright: Copyright (c) tuya.inc 2021
 * @LastEditTime: 2022-03-22 11:09:29
 *************************************************************************/
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

static uint8_t __invert_uint8(const uint8_t data)
{
    uint8_t i,result = 0;
    for ( i = 0; i < 8; i++){
        if (data & (1 << i)){
            result |= 1 << (7-i);
        }
    }
    return result;
}

static uint16_t __invert_uint16(const uint16_t data)
{
    uint16_t i,result = 0;
    for ( i = 0; i < 16; i++){
        if (data & (1 << i)){
            result |= 1 << (15-i);
        }
    }
    return result;
}

static uint32_t __invert_uint32(const uint32_t data)
{
    uint32_t i,result = 0;
    for ( i = 0; i < 32; i++){
        if (data & (1 << i)){
            result |= 1 << (31-i);
        }
    }
    return result;
}

/*****************************************************************
 * @Function: iot_calc_crc32
 * @Description: 计算CRC32值的算法实现，适配所有CRC32的协议
 * @Return: uint32_t
 *****************************************************************/
uint32_t iot_calc_crc32(const uint8_t *data, uint32_t size, uint32_t crc_poly, uint32_t init_value, uint8_t ref_flag, uint32_t xorout){  
    uint32_t crc_reg = init_value, tmp;
    
    while (size--)
    {
        uint8_t byte = *(data++);
        if (ref_flag)
        {
            byte = __invert_uint8(byte);
        }
        crc_reg ^= byte << 24;
        for ( uint8_t j = 0; j < 8; j++)
        {
            tmp = crc_reg & 0x80000000;
            crc_reg <<= 1;
            if (tmp)
                crc_reg ^= crc_poly;
        }
    }
    
    if (ref_flag)
    {
        crc_reg = __invert_uint32(crc_reg);
    }
    crc_reg = crc_reg ^ xorout;
    
    return crc_reg;
}

uint16_t iot_calc_crc16(const uint8_t *data, uint32_t size, uint16_t crc_poly, uint16_t init_value, uint8_t ref_flag, uint16_t xorout)
{   
    uint16_t crc_reg = init_value , tmp;
    
    while (size--)
    {
        uint8_t byte = *(data++);
        if (ref_flag)
        {
            byte = __invert_uint8(byte);
        }
        crc_reg ^= byte << 8;
        for (uint8_t j = 0; j < 8; j++)
        {
            tmp = crc_reg & 0x8000;
            crc_reg <<= 1;
            if (tmp)
                crc_reg ^= crc_poly;
        }
    }
    
    if (ref_flag)
    {
        crc_reg = __invert_uint16(crc_reg);
    }
    crc_reg = crc_reg ^ xorout;
    
    return crc_reg;
}

uint8_t iot_calc_crc8(const uint8_t *data, uint32_t size, uint8_t crc_poly, uint8_t init_value, uint8_t ref_flag, uint8_t xorout)
{
    uint8_t crc_reg = init_value, tmp;
    
    while (size--)
    {
        uint8_t byte = *(data++);
        if (ref_flag)
        {
            byte = __invert_uint8(byte);
        }
        crc_reg ^= byte;
        for ( uint8_t j = 0; j < 8; j++)
        {
            tmp = crc_reg & 0x80;
            crc_reg <<= 1;
            if (tmp)
                crc_reg ^= crc_poly;
        }
    }
    
    if (ref_flag)
    {
        crc_reg = __invert_uint8(crc_reg);
    }
    crc_reg = crc_reg ^ xorout;
    
    return crc_reg;
}

void generate_crc8_table(uint8_t poly)
{
    for (int index = 0; index < 256; index++)
    {
        uint8_t crc=0xff;//定义余数初值
        crc = (uint8_t)(__invert_uint8(index));//注意这里不管是8,16,32,对输入数据反转都是8bit
        // printf("0x%02x, ", crc);
        // if((index+1)%16 == 0)
        // {
        //     printf("\n");
        // }
        for (int i = 0; i < 8; i++)
        {
            if ((crc & 0x80) != 0)
            {
                crc = (uint8_t)((crc << 1) ^ poly);
            }
            else
            {
                crc = (uint8_t)(crc << 1);
            }
        }
        crc = __invert_uint8(crc);
        printf("0x%02x, ", crc);
        if((index+1)%16 == 0)
        {
            printf("\n");
        }
    }
}

void generate_crc16_table(uint16_t poly)
{
    for (int index = 0; index < 256; index++)
    {
        uint16_t crc=0x0000;//定义余数初值
        crc = (uint8_t)(__invert_uint8(index));//注意这里不管是8,16,32,对输入数据反转都是8bit
        // crc = index;
        // printf("0x%02x, ", crc);
        // if((index+1)%16 == 0)
        // {
        //     printf("\n");
        // }
        for (int i = 0; i < 16; i++)
        {
            if ((crc & 0x8000) != 0)
            {
                crc = (uint16_t)((crc << 1) ^ poly);
            }
            else
            {
                crc = (uint16_t)(crc << 1);
            }
        }
        crc = __invert_uint16(crc);
        // crc = crc ^ 0x0000;
        printf("0x%04x, ", crc);
        if((index+1)%16 == 0)
        {
            printf("\n");
        }
    }
}
