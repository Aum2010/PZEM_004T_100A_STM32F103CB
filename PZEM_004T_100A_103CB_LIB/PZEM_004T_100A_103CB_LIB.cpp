
#include "PZEM_004T_100A_103CB_LIB.h"

#define CMD_RHR         0x03
#define CMD_RIR         0X04
#define CMD_WSR         0x06
#define CMD_CAL         0x41
#define CMD_REST        0x42

#define PZEM_DEFAULT_ADDR    0xF8

void PZM_UART::updateValue( void ) {
	 sendCMD(CMD_RIR, 0x00, PZEM_DEFAULT_ADDR, 0x0A);

	 HAL_UART_Receive(&_huart, rxBuff, 25, 2000);

	//		  memcpy(&pzm_raw.Voltage_val , &rxBuff[3] , 2);
		 	  pzm_raw.Voltage_val = (uint16_t)rxBuff[3] << 8 | (uint16_t)rxBuff[4] ;
	//		  memcpy(&pzm_raw.Current_val , &rxBuff[5] , 4);
			  pzm_raw.Current_val = (uint32_t)rxBuff[5] << 8 | (uint32_t)rxBuff[6] | (uint32_t)rxBuff[7] << 24 | (uint32_t)rxBuff[8] << 16 ;
	//		  memcpy(&pzm_raw.Power_val , &rxBuff[9] , 4);
			  pzm_raw.Power_val = (uint32_t)rxBuff[9] << 8 | (uint32_t)rxBuff[10] | (uint32_t)rxBuff[11] << 24 | (uint32_t)rxBuff[12] << 16 ;
	//		  memcpy(&pzm_raw.Energy_val , &rxBuff[13] , 4);
			  pzm_raw.Energy_val = (uint32_t)rxBuff[13] << 8 | (uint32_t)rxBuff[14] | (uint32_t)rxBuff[15] << 24 | (uint32_t)rxBuff[16] << 16 ;
	//		  memcpy(&pzm_raw.Frequency_val , &rxBuff[17] , 2);
			  pzm_raw.Frequency_val = (uint16_t)rxBuff[17] << 8 | (uint16_t)rxBuff[18] ;
	//		  memcpy(&pzm_raw.PowerFector_val , &rxBuff[19] , 2);
			  pzm_raw.PowerFector_val = (uint16_t)rxBuff[19] << 8 | (uint16_t)rxBuff[20] ;

	//		  pzm_raw.Current_val = (uint32_t) pzm_raw.Current_val << 16 ;

	//		  pzm_raw.Voltage_val = __REV16(pzm_raw.Voltage_val);
	//		  pzm_raw.Current_val = __REV(pzm_raw.Current_val);
	//		  pzm_raw.Energy_val = __REV(pzm_raw.Energy_val);
	//		  pzm_raw.Frequency_val = __REV(pzm_raw.Frequency_val);
	//		  pzm_raw.Power_val = __REV16(pzm_raw.Power_val);
	//		  pzm_raw.PowerFector_val = __REV16(pzm_raw.PowerFector_val);

			  pzm_data.Voltage_val = pzm_raw.Voltage_val * 0.1f;
			  pzm_data.Current_val = pzm_raw.Current_val * 0.001f;
			  pzm_data.Energy_val = pzm_raw.Energy_val ;
			  pzm_data.Frequency_val = pzm_raw.Frequency_val * 0.1f;
			  pzm_data.Power_val = pzm_raw.Power_val * 0.1f;
			  pzm_data.PowerFector_val = pzm_raw.PowerFector_val * 0.01f;
}

float PZM_UART::voltageValue( void ) {
	return pzm_data.Voltage_val;
}
float PZM_UART::currentValue( void ){
	return pzm_data.Current_val;
}
int PZM_UART::energyValue( void ){
	return pzm_data.Energy_val;
}
float PZM_UART::frequencyvalue(void){
	return pzm_data.Frequency_val;
}
float PZM_UART::powerValue(void){
	return pzm_data.Power_val;
}
float PZM_UART::powerFector(void){
	return pzm_data.PowerFector_val;
}


