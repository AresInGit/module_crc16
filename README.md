# Module CRC16

## What

- This is a C source lib for calculating crc16.

- It provides several crc16 calc ways, as

  | X25  | CCITT  | CCITT_FALSE | MODBUS |
  | :--: | :----: | :---------: | :----: |
  | USB  | XMODEM |     IBM     | MAXIM  |

  

## How

1.  Add the source file in your project, make sure you add the correct path in your compile environment.

2. Modify the enable macro in `module_crc16xx.h`, which likes

   ```c
   #define CRC16_X25_ENABLE            1
   #define CRC16_CCITT_ENABLE          1
   ```

   > Each enable needs about(more not less) 256*2 			bytes memory. 

3.  Call  `module_crc16_init()` fxn once first, before use the  `module_crc16_calc()`.

4. Call  `module_crc16_calc()` fxn to calculate crc16 value.

   ```C
   /* Here's an example for use this crc16 lib */
   int main() 
   {
   	/* Declare some variables */
   	char testbuf[] = "Hello World.";
   	uint16_t crc16 = 0;
   	
   	/* Init module_crc16 first */
   	module_crc16_init();
   	
   	/* Call crc16_calc fxn */
   	crc16 = module_crc16_calc(MODULE_CRC16_MODE_X25, \
           (uint8_t*)testbuf, strlen(testbuf));
   	
   	/* Print result */
   	printf("%s crc16= 0x%04x\n",testbuf, crc16);
   		
   	return 0;
   }
   ```

## End

- Thanks for your attention.

![](images/appendix.gif)

---









