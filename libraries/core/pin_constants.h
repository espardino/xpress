#ifndef __PIN_CONSTANTS_H
#define __PIN_CONSTANTS_H


#define MAX_PIN 100


#define	INVALID_PIN -1
	/* FPGA - core dependent pins */
	
#define	F27    3	//  3	 F27/LED2	FPGA pin (IO27RSB0) and/or LED2 pin	 FPGA
#define	F36    4	//  4	 F36/LED1	FPGA pin (IO36RSB0) and/or LED1 pin	 FPGA
#define	F39    5	//  5	 F39/LED3	FPGA pin (IO39RSB0) and/or LED3 pin	 FPGA
#define	F44    6	//  6	 F44		FPGA pin (IO44RSB0) 	 FPGA
#define	F45    7	//  7	 F45	 	FPGA pin (IO45RSB0)	 FPGA
#define	F46    8	//  8	 F46	 	FPGA pin (IO46RSB0)	 FPGA
#define	F49    9	//  9	 F49	 	FPGA pin (IO49RSB0)	 FPGA
#define	F51    93	//  93	 F51	 	FPGA pin (IO51RSB1)	 FPGA
#define	F52    94	//  94	 F52	 	FPGA pin (IO52RSB1)	 FPGA
#define	F53    91	//  91	 F53	 	FPGA pin (IO53RSB1)	 FPGA
#define	F54    19 	//  19	 F54	 	FPGA pin (IO54RSB1)	 FPGA
#define	F55    20 	//  20	 F55	 	FPGA pin (IO55RSB1)	 FPGA
#define	F56    21 	//  21	 F56	 	FPGA pin (IO56RSB1)	 FPGA
#define	F57    22 	//  22	 F57	 	FPGA pin (IO57RSB1)	 FPGA
#define	F58    23 	//  23	 F58	 	FPGA pin (IO58RSB1)	 FPGA
#define	F59    24 	//  24	 F59	 	FPGA pin (IO59RSB1)	 FPGA
#define	F60    16 	//  16	 F60	 	FPGA pin (IO60RSB1)	 FPGA
#define	F61    67	//  67	 F61	 	FPGA pin (IO61RSB1)	 FPGA
#define	F62    68	//  68	 F62	 	FPGA pin (IO62RSB1)	 FPGA
#define	F63    69	//  69	 F63	 	FPGA pin (IO63RSB1)	 FPGA
#define	F64    70	//  70	 F64	 	FPGA pin (IO64RSB1)	 FPGA
#define	F65    71	//  71	 F65	 	FPGA pin (IO65RSB1)	 FPGA
#define	F66    72	//  72	 F66	 	FPGA pin (IO66RSB1)	 FPGA
#define	F67    73	//  73	 F67	 	FPGA pin (IO67RSB1)	 FPGA
#define	F68    74	//  74	 F68	 	FPGA pin (IO68RSB1)	 FPGA
#define	F69    75	//  75	 F69	 	FPGA pin (IO69RSB1)	 FPGA
#define	F70    76	//  76	 F70	 	FPGA pin (IO70RSB1)	 FPGA
#define	F71    77	//  77	 F71	 	FPGA pin (IO71RSB1)	 FPGA
#define	F72    78	//  78	 F72	 	FPGA pin (IO72RSB1)	 FPGA
#define	F73    79	//  79	 F73	 	FPGA pin (IO73RSB1)	 FPGA
#define	F74    80	//  80	 F74	 	FPGA pin (IO74RSB1)	 FPGA
#define	F75    81	//  81	 F75	 	FPGA pin (IO75RSB1)	 FPGA
#define	F77    82	//  82	 F77	 	FPGA pin (IO77RSB1)	 FPGA
#define	F83    83	//  83	 F83	 	FPGA pin (IO83RSB1)	 FPGA
#define	F84    84	//  84	 F84	 	FPGA pin (IO84RSB1)	 FPGA
#define	F85    85	//  85	 F85	 	FPGA pin (IO85RSB1)	 FPGA
#define	F86    86	//  86	 F86	 	FPGA pin (IO86RSB1)	 FPGA
#define	F87    87	//  87	 F87	 	FPGA pin (IO87RSB1)	 FPGA
#define	F92    88	//  88	 F92	 	FPGA pin (IO92RSB1)	 FPGA
#define	F93    89	//  89	 F93	 	FPGA pin (IO93RSB1)	 FPGA
#define	F94    90	//  90	 F94	 	FPGA pin (IO94RSB1)	 FPGA
#define	F95    92	//  92	 F95	 	FPGA pin (IO95RSB1)	 FPGA

	/* Special function pins that could act as gpio if needed */
	
#define	SCL0  19	//  19	SCL0	 	I2C Clock line	 NB31XX                        
#define	SDA0  20	//  20	SDA0	 	I2C Data Line	 NB31XX                          
#define	SCL1  21	//  21	SCL1	 	I2C Clock line	 NB31XX                        
#define	SDA1  22	//  22	SDA1	 	I2C Data Line	 NB31XX                          
#define	RXD   23	//  23	RXD	 	UART Serial Input	 NB31XX                      
#define	TXD   24	//  24	TXD	 	UART Serial Output	 NB31XX                    
#define	PWM   38	//  38  PWM	 	PWM Output	 NB31XX
#define	SCK   51	//  51	SCK	 	SPI Clock Input (Slave) / Clock Output (Master)	 NB31XX                     			
#define	MISO  53 	//  53	MISO 		SPI Data Input (Master) / Data Output (Slave)	 NB31XX                           			
#define	MOSI  54 	//  54	MOSI 		SPI Data Output (Master) / Data Input (Slave)	 NB31XX                           			 
#define	nCSIN 55	//  55	nCSIN 		SPI Chip Select Input (Slave) (active low)	 NB31XX                         			 
#define	nCS0  56	//  56	nCS0	 	SPI Chip Select Output (Master) (active low)	 NB31XX                       			         
#define	nCS1  57 	//  57	nCS1 		SPI chip select out for slave 1 (used in master mode) (active low)	 NB31XX 			
#define	nCS2  58 	//  58	nCS2 		SPI chip select out for slave 2 (used in master mode) (active low)	 NB31XX 			

	/* Standard GPIO ports */

#define	GB0    25 	//  25	GB0	 	General Purpose I/O Pin 0 (Mode pin 0)	 POWER
#define	GB1    26 	//  26	GB1		General Purpose I/O Pin 1 (Mode pin 1)	 POWER	
#define	GB2    27 	//  27	GB2	 	General Purpose I/O Pin 2 (Mode pin 2)	 POWER	
	      
#define	G14   31  	//  31	G14	 	General Purpose I/O Pin 14 NB31XX             		                                                                                                      	
#define	G15   32  	//  32	G15	 	General Purpose I/O Pin 15 NB31XX
#define	G16   33  	//  33	G16	 	General Purpose I/O Pin 16 NB31XX
#define	G17   34  	//  34	G17	 	General Purpose I/O Pin 17 NB31XX
#define	G18   35  	//  35	G18	 	General Purpose I/O Pin 18 NB31XX
#define	G19   36  	//  36	G19	 	General Purpose I/O Pin 19 NB31XX
#define	G20   37  	//  37	G20	 	General Purpose I/O Pin 20 NB31XX
	
	/* Analog input pins */
	
#define	ADC3  60	 //  60	 ADC3 		10-bit ADC Analog Input	 NB31XX
#define	ADC2  62  	 //  62  ADC2		10-bit ADC Analog Input	 NB31XX
#define	ADC1  64	 //  64	 ADC1 		10-bit ADC Analog Input	 NB31XX
#define	ADC0  66  	 //  66  ADC0 		10-bit ADC Analog Input	 NB31XX



#endif
