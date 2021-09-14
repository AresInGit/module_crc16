/**
  ******************************************************************************
  * @file    module_ccr16xx.c
  * @brief   A software crc16 calculation source file
  * @author  AresChai           
  * @version V0.1.0
  ******************************************************************************  
  * @date  09/02/2021
  * @note  First time build
  
  * @date  xx/xx/xx
  * @note  xxxxxxxx
  ******************************************************************************
  */
#include "module_crc16xx.h"
/************************************************************
*                      Varlables Define
************************************************************/
#if CRC16_X25_ENABLE
static width_t _x25_table[256] = {0};
static const module_crc_cfg_t _x25_cfg = {
    .poly   = 0x1021,
    .init   = 0xFFFF,
    .refin  = 1,
    .refout = 1,
    .xor    = 0xFFFF
};
#endif 

#if CRC16_CCITT_ENABLE
static width_t _ccitt_table[256] = {0};
static const module_crc_cfg_t _ccitt_cfg = {
    .poly   = 0x1021,
    .init   = 0x0000,
    .refin  = 1,
    .refout = 1,
    .xor    = 0x0000
};
#endif 

#if CRC16_CCITT_FLASE_ENABLE
static width_t _ccitt_false_table[256] = {0};
static const module_crc_cfg_t _ccitt_false_cfg = {
    .poly   = 0x1021,
    .init   = 0xFFFF,
    .refin  = 0,
    .refout = 0,
    .xor    = 0x0000
};
#endif 

#if CRC16_MODBUS_ENABLE
static width_t _modbus_table[256] = {0};
static const module_crc_cfg_t _modbus_cfg = {
    .poly   = 0x8005,
    .init   = 0xFFFF,
    .refin  = 1,
    .refout = 1,
    .xor    = 0x0000
};
#endif 

#if CRC16_USB_ENABLE
static width_t _usb_table[256] = {0};
static const module_crc_cfg_t _usb_cfg = {
    .poly   = 0x8005,
    .init   = 0xFFFF,
    .refin  = 1,
    .refout = 1,
    .xor    = 0xFFFF
};
#endif 

#if CRC16_XMODEM_ENABLE
static width_t _xmodem_table[256] = {0};
static const module_crc_cfg_t _xmodem_cfg = {
    .poly   = 0x1021,
    .init   = 0x0000,
    .refin  = 0,
    .refout = 0,
    .xor    = 0x0000
};
#endif 

#if CRC16_IBM_ENABLE
static width_t _ibm_table[256] = {0};
static const module_crc_cfg_t _ibm_cfg = {
    .poly   = 0x8005,
    .init   = 0x0000,
    .refin  = 1,
    .refout = 1,
    .xor    = 0x0000
};
#endif 

#if CRC16_MAXIM_ENABLE
static width_t _maxim_table[256] = {0};
static const module_crc_cfg_t _maxim_cfg = {
    .poly   = 0x8005,
    .init   = 0x0000,
    .refin  = 1,
    .refout = 1,
    .xor    = 0xFFFF
};
#endif 

/************************************************************
*                      Local Fxn Declare
************************************************************/
static width_t bitReverse(width_t input);
static void crc16_table_init(const module_crc_cfg_t *pCfg, 
	width_t *pTable);
static width_t crc16_calc(const module_crc_cfg_t *pCfg, 
    const width_t *pTable, const uint8_t *ptr, uint32_t size);

/************************************************************
*                      External Fxn Define
************************************************************/

/**
  * @brief  Init all enabled crc16 mode table
  * @param  None
  * @retval None
  */
void module_crc16_init(void)
{
#if CRC16_X25_ENABLE
    crc16_table_init(&_x25_cfg, _x25_table);
#endif     
#if CRC16_CCITT_ENABLE
    crc16_table_init(&_ccitt_cfg, _ccitt_table);
#endif
#if CRC16_CCITT_FLASE_ENABLE
    crc16_table_init(&_ccitt_false_cfg, _ccitt_false_table);
#endif
#if CRC16_MODBUS_ENABLE
    crc16_table_init(&_modbus_cfg, _modbus_table);
#endif
#if CRC16_USB_ENABLE
    crc16_table_init(&_usb_cfg, _usb_table);
#endif
#if CRC16_XMODEM_ENABLE
    crc16_table_init(&_xmodem_cfg, _xmodem_table);
#endif
#if CRC16_IBM_ENABLE
    crc16_table_init(&_ibm_cfg, _ibm_table);
#endif
#if CRC16_MAXIM_ENABLE
    crc16_table_init(&_maxim_cfg, _maxim_table);
#endif    
}

/**
  * @brief  Calc input datas crc by given crc mode
  * @param  mode: see MODULE_CRC16_MODE_e
  * @param  ptr: pointer of input data
  * @param  size: sizeof(data)
  * @retval crc16 value
  * @note   if retval=0xFFFF, shall check input mode enable macro   
  */
width_t module_crc16_calc(MODULE_CRC16_MODE_e mode, 
    const uint8_t *ptr, uint32_t size) 
{
    switch (mode) {
    #if CRC16_X25_ENABLE      
        case MODULE_CRC16_MODE_X25:
            return crc16_calc(&_x25_cfg, _x25_table, ptr, size);
            //break;
    #endif 
    #if CRC16_CCITT_ENABLE         
	case MODULE_CRC16_MODE_CCITT:
            return crc16_calc(&_ccitt_cfg, _ccitt_table, ptr, size);
            //break;
    #endif
    #if CRC16_CCITT_FLASE_ENABLE       
	case MODULE_CRC16_MODE_CCITT_FLASE:
            return crc16_calc(&_ccitt_false_cfg, _ccitt_false_table, ptr, size);
            //break;    
    #endif 
    #if CRC16_MODBUS_ENABLE         
        case MODULE_CRC16_MODE_MODBUS:
            return crc16_calc(&_modbus_cfg, _modbus_table, ptr, size);
            //break;  
    #endif 
    #if CRC16_USB_ENABLE              
        case MODULE_CRC16_MODE_USB:
            return crc16_calc(&_usb_cfg, _usb_table, ptr, size);
            //break;
    #endif 
    #if CRC16_XMODEM_ENABLE            
        case MODULE_CRC16_MODE_XMODEM:
            return crc16_calc(&_xmodem_cfg, _xmodem_table, ptr, size);
            //break;
    #endif
    #if CRC16_IBM_ENABLE            
        case MODULE_CRC16_MODE_IBM:
            return crc16_calc(&_ibm_cfg, _ibm_table, ptr, size);
            //break; 
    #endif 
    #if CRC16_MAXIM_ENABLE           
        case MODULE_CRC16_MODE_MAXIM:
            return crc16_calc(&_maxim_cfg, _maxim_table, ptr, size);
            //break; 
    #endif                                  
    }
    return 0xFFFF;
}

/************************************************************
*                       Local Fxn Define
************************************************************/

/**
  * @brief  Reverse input data bit by bit
  * @param  input: data to be reversed
  * @retval reversed value
  */
static width_t bitReverse(width_t input)
{
    uint16_t val = 0;
    uint16_t bits = sizeof(width_t)*8;
    while (bits--) {
        val <<= 1;
        val |= input & 0x1;
        input >>= 1;
    }
    return val;
}

/**
  * @brief  Init crc16 table by input cfg
  * @param  pCfg: pointer of module_crc_cfg_t
  * @param  pTable: pointer of crcTable container  
  * @retval reverse value
  */
static void crc16_table_init(const module_crc_cfg_t *pCfg, width_t *pTable)
{
    uint16_t            i,j;
    width_t             poly;
    width_t             value; 

    /*  Reverse bit sequence input */
    if (pCfg->refin) {
        poly = bitReverse(pCfg->poly);  
        for (i = 0; i < 256; i++) {
            value = i;
            for (j = 0; j < 8; j++){
                value = (value & 0x1) ? (value >> 1) ^ poly : \
                    (value >> 1);
            }
            pTable[i] = value;
        }   
    }

    /* Normal bit sequence Input */
    else {
        poly = pCfg->poly;
        for (i = 0; i < 256; i++) {
            value = i << 8;
            for (j = 0; j < 8; j++) {
                value = (value & 0x8000) ? (value << 1) ^ poly : \
                    (value << 1);
            }
            pTable[i] = value;
        }
    }
}

/**
  * @brief  Calc input datas crc by given crc_cfg and table
  * @param  pCfg: pointer of module_crc_cfg_t
  * @param  pTable: pointer of crcTable container
  * @param  ptr: pointer of input data
  * @param  size: sizeof(data)
  * @retval crc16 value
  */
static width_t crc16_calc(const module_crc_cfg_t *pCfg, 
    const width_t *pTable, const uint8_t *ptr, uint32_t size)
{
    width_t value;
    
    /* Reverse bit sequence input */
    if (pCfg->refin) {
        value = bitReverse(pCfg->init);
        while (size--) {
            value = (value >> 8) ^ pTable[(value & 0xff) ^ *ptr++];
        }
    }
    /* Normal bit sequence Input */
    else {
        value = pCfg->init;
        while (size--) {
            value = (value << 8) ^ pTable[(value >> 8) ^ *ptr++];
        }
    }

    /* Reverse bit sequence output */
    if (pCfg->refout != pCfg->refin) {
        value = bitReverse(value);
    }

    /* Xor & return */
    return (width_t)(value ^ pCfg->xor);
}

