/*
 * spi_eflash.c
 *
 *  Author: 
 */ 


#include "hsf.h"
#include "spi_eflash.h"
#include <hf_debug.h>


void hf_spi_TH25D_40HB_demo(void)
{
    HF_Debug(DEBUG_WARN,"start hfspi demo .....\r\n");
    uint8_t spi_send_8bits_data[10]={0x05,0x00,0x35,0x00,0x44,0x55,0x66,0x77,0xEE,0xFF};        //低8  高8
    uint8_t spi_recv_8bits_data[10]={0x11,0x19,0x33,0x55,0x77,0x11,0x13,0x17,0xFE,0xFF};
    uint8_t spi_send_8bits_read[1024+512]={0};
    uint8_t spi_recv_8bits_read[1024+512]={0};
    uint8_t readen = 0x06;

    uint16_t i = 0;

    //SPI_Int_Callback_Install(SPI_ID_0, SPI_INT_END, spi_end_callback);		//注册SPI异步回调

    if(hfspi_master_init(0, 200000) == HF_SUCCESS)    //初始化  模式0 时钟200khz
    {
        HF_Debug(DEBUG_WARN,"hfspi init success .....\r\n");

        hfspi_master_send_data(&readen, 1);        //擦除/写使能

        hfspi_master_send_and_recv_data(spi_send_8bits_data, spi_recv_8bits_data, 2);           //读取状态寄存器低8位
        u_printf("TH25D_40HB state_L:0x%02X---\r\n",spi_recv_8bits_data[1]);

        hfspi_master_send_and_recv_data(spi_send_8bits_data+2,spi_recv_8bits_data+2, 2);        //读取状态寄存器高8位
        u_printf("TH25D_40HB state_H:0x%02X---\r\n",spi_recv_8bits_data[3]);

        bzero(spi_send_8bits_data,10);
        spi_send_8bits_data[0] = 0x90;
        hfspi_master_send_and_recv_data(spi_send_8bits_data,spi_recv_8bits_data, 6);        //读取制造商ID与设备ID
        u_printf("TH25D_40HB Manufacture ID:0x%02X---\r\n",spi_recv_8bits_data[4]);         //制造商
        u_printf("TH25D_40HB Device ID:0x%02X---\r\n",spi_recv_8bits_data[5]);              //设备ID


        bzero(spi_send_8bits_data,10);
        spi_send_8bits_data[0] = 0x9F;
        hfspi_master_send_and_recv_data(spi_send_8bits_data,spi_recv_8bits_data, 4);        //读取制造商ID,存储器类型ID,容量ID
        u_printf("TH25D_40HB Manufacture ID:0x%02X---\r\n",spi_recv_8bits_data[1]);         //制造商
        u_printf("TH25D_40HB Memory Type ID:0x%02X---\r\n",spi_recv_8bits_data[2]);         //存储器类型
        u_printf("TH25D_40HB Capacity ID:0x%02X---\r\n",spi_recv_8bits_data[3]);            //容量




        spi_send_8bits_read[0] = 0x03;      //读数据命令
        spi_send_8bits_read[1] = 0x00;      //起始地址H
        spi_send_8bits_read[2] = 0x0D;      //起始地址M
        spi_send_8bits_read[3] = 0x40;      //起始地址L

        hfspi_master_send_and_recv_data(spi_send_8bits_read,spi_recv_8bits_read,4+1024+512);          //发&收  发1B直接3B地址  接收(1024+512)B数据
        
        for(i=0;i<1024+512;i++)
        {
            if((i%32) == 0)
                u_printf("flash[%05d]:",i);

            u_printf("%02X ",spi_recv_8bits_read[i+4]);

            if(((i+1)%32) == 0)
                u_printf("---\r\n");
        }
                u_printf("flash[%05d]: ---\r\n\r\n",i);

    }else{
        HF_Debug(DEBUG_WARN,"hfspi init error .....\r\n");
    }

    HF_Debug(DEBUG_WARN,"hfspi demo the end .....\r\n");
}
