/**
  ******************************************************************************
  * @file    module_ccr16xx.h
  * @brief   A software crc16 calculation header file
  * @author  AresChai           
  * @version V0.1.0
  ******************************************************************************  
  * @date  09/02/2021
  * @note  First time build
  * @note  It provides several popular crc16 calc ways.
  *         like CRC16_MODBUS, CRC16_CCITT, CRC16_X25 etc.

  * @date  xx/xx/xx
  * @note  xxxxxxxx
  ******************************************************************************
  */
#ifndef __MODULE_CRC16XX_H_
#define __MODULE_CRC16XX_H_
#include <stdint.h>
/************************************************************
*                    User Header Include 
************************************************************/


/************************************************************
*                       Macro Define
************************************************************/
/**
 * Since this lib create a static table,enable each crc mode 
 *  will need extra 256*sizeof(width_t) byte memory
 */
#define CRC16_X25_ENABLE            1
#define CRC16_CCITT_ENABLE          1
#define CRC16_CCITT_FLASE_ENABLE    1
#define CRC16_MODBUS_ENABLE         1
#define CRC16_USB_ENABLE            1
#define CRC16_XMODEM_ENABLE         1
#define CRC16_IBM_ENABLE            1
#define CRC16_MAXIM_ENABLE          1

/* CRC16 Mode Declare */
typedef enum {
#if CRC16_X25_ENABLE    
    MODULE_CRC16_MODE_X25,
#endif
#if CRC16_CCITT_ENABLE    
    MODULE_CRC16_MODE_CCITT,
#endif
#if CRC16_CCITT_FLASE_ENABLE    
    MODULE_CRC16_MODE_CCITT_FLASE,
#endif
#if CRC16_MODBUS_ENABLE    
    MODULE_CRC16_MODE_MODBUS,
#endif
#if CRC16_USB_ENABLE    
    MODULE_CRC16_MODE_USB,
#endif
#if CRC16_XMODEM_ENABLE    
    MODULE_CRC16_MODE_XMODEM,
#endif
#if CRC16_IBM_ENABLE    
    MODULE_CRC16_MODE_IBM,
#endif
#if CRC16_MAXIM_ENABLE    
    MODULE_CRC16_MODE_MAXIM,
#endif    
} MODULE_CRC16_MODE_e;

/************************************************************
*                   Data Structure Define
************************************************************/
typedef uint16_t  width_t;

typedef struct {    
    width_t     poly;   // Polynomial
    width_t     init;   // Initialize value
    uint8_t     refin;  // Reverse bit sequence input flag
    uint8_t     refout; // Reverse bit sequence output flag
    width_t     xor;    // Final result = ^xor 
} module_crc_cfg_t;

/************************************************************
*                 External Variable Declare
************************************************************/


/************************************************************
*                   External Fxn Declare 
************************************************************/
/* CRC Table Init */
void module_crc16_init(void);

/* CRC Calc */
width_t module_crc16_calc(MODULE_CRC16_MODE_e mode, 
    const uint8_t *ptr, uint32_t size);




#endif /* __MODULE_CRC16XX_H_ */