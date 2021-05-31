/* Thank You For Source Code Reference : https://github.com/mandulaj/PZEM-004T-v30/blob/master/PZEM004Tv30.cpp */
/* Thank You For Source Code Reference CRC_16 Modbus : https://github.com/LacobusVentura/MODBUS-CRC16 */
/* Update 31 May 2021 */

#ifndef __PZEM_004T_100A_103CB
#define __PZEM_004T_100A_103CB

#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"
#include "main.h"

class PZM_UART {
private:

	UART_HandleTypeDef _huart;
	uint8_t rxBuff[50];

	typedef struct PZE {

		uint8_t slave_addr ;
		uint8_t cmd ;
		uint8_t H_raddr;
		uint8_t L_raddr;
		uint8_t H_val;
		uint8_t L_val;

	}PZE_T ;

	typedef struct PZE_CRC {

		uint8_t slave_addr;
		uint8_t cmd ;
		uint8_t H_raddr;
		uint8_t L_raddr;
		uint8_t H_val;
		uint8_t L_val;
		uint8_t H_CRC;
		uint8_t L_CRC;

	}PZE_T_CRC ;

	typedef struct PZE_RAW {
		uint16_t Voltage_val ;
		uint32_t Current_val ;
		uint32_t Power_val ;
		uint32_t Energy_val ;
		uint16_t Frequency_val;
		uint16_t PowerFector_val;
	}PZE_RAW_T;

	typedef struct PZE_DATA {
		float Voltage_val ;
		float Current_val ;
		float Power_val ;
		int Energy_val ;
		float Frequency_val;
		float PowerFector_val;
	}PZE_DATA_T;

	PZE_RAW_T pzm_raw;
	PZE_DATA_T pzm_data;

	static uint16_t MODBUS_CRC16_v3( const unsigned char *buf, unsigned int len )
	{
		static const uint16_t table[256] = {
		0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
		0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
		0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
		0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
		0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
		0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
		0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
		0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
		0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
		0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
		0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
		0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
		0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
		0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
		0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
		0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
		0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
		0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
		0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
		0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
		0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
		0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
		0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
		0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
		0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
		0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
		0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
		0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
		0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
		0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
		0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
		0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };

		uint8_t xor_ = 0;
		uint16_t crc = 0xFFFF;

		while( len-- )
		{
			xor_ = (*buf++) ^ crc;
			crc >>= 8;
			crc ^= table[xor_];
		}

		return crc;
	}

	 void sendCMD ( uint8_t cmd , uint16_t rAddr, uint16_t slave_addr , uint16_t val) {

		PZE_T pze ;
		PZE_T_CRC pze_crc;
		uint16_t crc;

		pze.slave_addr = 0xF8;
		pze.cmd = cmd;
		pze.H_raddr = (rAddr >> 8) & 0xFF ;
		pze.L_raddr = rAddr & 0xFF ;
		pze.H_val = (val >> 8) & 0xFF ;
		pze.L_val = val & 0xFF ;

		crc = MODBUS_CRC16_v3((const unsigned char *)&pze, sizeof(pze));

		pze_crc.slave_addr = 0xF8;
		pze_crc.cmd = cmd;
		pze_crc.H_raddr = (rAddr >> 8) & 0xFF ;
		pze_crc.L_raddr = rAddr & 0xFF ;
		pze_crc.H_val = (val >> 8) & 0xFF ;
		pze_crc.L_val = val & 0xFF ;
		pze_crc.H_CRC = (crc >> 8) & 0xFF ;
		pze_crc.L_CRC = crc & 0xFF ;

		HAL_UART_Transmit(&_huart, (uint8_t *)&pze_crc, 8 ,1000);
	}

public:
	int num;

	PZM_UART(UART_HandleTypeDef *_huart , USART_TypeDef *uart_Instance) {


		_huart->Instance = uart_Instance;
		_huart->Init.BaudRate = 9600;
		_huart->Init.WordLength = UART_WORDLENGTH_8B;
		_huart->Init.StopBits = UART_STOPBITS_1;
		_huart->Init.Parity = UART_PARITY_NONE;
		_huart->Init.Mode = UART_MODE_TX_RX;
		_huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		_huart->Init.OverSampling = UART_OVERSAMPLING_16;

		  if (HAL_UART_Init(_huart) != HAL_OK)
		  {
		    Error_Handler();
		  }

	}


	void testprint( )
	{
		HAL_UART_Transmit(&_huart, (uint8_t *)"Hello UART \r\n", sizeof("Hello UART \r\n"), 1000);
	}

	void updateValue() ;
	float voltageValue();
	float currentValue();
	int energyValue();
	float frequencyvalue();
	float powerValue();
	float powerFector();



};



#endif