#ifndef __LPC31xx_GPIO_H
#define __LPC31xx_GPIO_H
#include <stdint.h>



#define IOCONF_BASE               0x13003000
#define IOCONF_LENGTH             0x00001000


/***********************************************************************
 * GPIO register definitions
 **********************************************************************/
#define GPIO_STATE(port)     *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x00))
#define GPIO_STATE_M0(port)  *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x10))
#define GPIO_M0_SET(port)    *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x14))
#define GPIO_M0_RESET(port)  *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x18))
#define GPIO_STATE_M1(port)  *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x20))
#define GPIO_M1_SET(port)    *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x24))
#define GPIO_M1_RESET(port)  *((uint32_t*) (IOCONF_MAPPED_ADDR + (port) + 0x28))

#define GPIO_OUT_LOW(port, pin)  do { GPIO_M1_SET(port) = pin; GPIO_M0_RESET(port) = pin;} while(0)
#define GPIO_OUT_HIGH(port, pin) do { GPIO_M1_SET(port) = pin; GPIO_M0_SET(port) = pin;} while(0)
#define GPIO_IN(port, pin)       do { GPIO_M1_RESET(port) = pin; GPIO_M0_RESET(port) = pin;} while(0)
#define GPIO_DRV_IP(port, pin)   do { GPIO_M1_RESET(port) = pin; GPIO_M0_SET(port) = pin;} while(0)

#define IOCONF_EBI_MCI       (0x000)
#define IOCONF_EBI_I2STX_0   (0x040)
#define IOCONF_CGU           (0x080)
#define IOCONF_I2SRX_0       (0x0c0)
#define IOCONF_I2SRX_1       (0x100)
#define IOCONF_I2STX_1       (0x140)
#define IOCONF_EBI           (0x180)
#define IOCONF_GPIO          (0x1c0)
#define IOCONF_I2C1          (0x200)
#define IOCONF_SPI           (0x240)
#define IOCONF_NAND_CTRL     (0x280)
#define IOCONF_PWM           (0x2c0)
#define IOCONF_UART          (0x300)


#define GPIO_PORT_MASK  0x0FE0
#define GPIO_PIN_MASK   0x001F


#define GPIO_MGPIO9           (IOCONF_EBI_MCI | 0)  
#define GPIO_MGPIO6           (IOCONF_EBI_MCI | 1)  
#define GPIO_MLCD_DB_7        (IOCONF_EBI_MCI | 2)  
#define GPIO_MLCD_DB_4        (IOCONF_EBI_MCI | 3)  
#define GPIO_MLCD_DB_2        (IOCONF_EBI_MCI | 4)  
#define GPIO_MNAND_RYBN0      (IOCONF_EBI_MCI | 5)  
#define GPIO_MI2STX_CLK0      (IOCONF_EBI_MCI | 6)  
#define GPIO_MI2STX_BCK0      (IOCONF_EBI_MCI | 7)  
#define GPIO_EBI_A_1_CLE      (IOCONF_EBI_MCI | 8)  
#define GPIO_EBI_NCAS_BLOUT   (IOCONF_EBI_MCI | 9)  
#define GPIO_MLCD_DB_0        (IOCONF_EBI_MCI | 10) 
#define GPIO_EBI_DQM_0_NOE    (IOCONF_EBI_MCI | 11) 
#define GPIO_MLCD_CSB         (IOCONF_EBI_MCI | 12) 
#define GPIO_MLCD_DB_1        (IOCONF_EBI_MCI | 13) 
#define GPIO_MLCD_E_RD        (IOCONF_EBI_MCI | 14) 
#define GPIO_MLCD_RS          (IOCONF_EBI_MCI | 15) 
#define GPIO_MLCD_RW_WR       (IOCONF_EBI_MCI | 16) 
#define GPIO_MLCD_DB_3        (IOCONF_EBI_MCI | 17) 
#define GPIO_MLCD_DB_5        (IOCONF_EBI_MCI | 18) 
#define GPIO_MLCD_DB_6        (IOCONF_EBI_MCI | 19) 
#define GPIO_MLCD_DB_8        (IOCONF_EBI_MCI | 20) 
#define GPIO_MLCD_DB_9        (IOCONF_EBI_MCI | 21) 
#define GPIO_MLCD_DB_10       (IOCONF_EBI_MCI | 22) 
#define GPIO_MLCD_DB_11       (IOCONF_EBI_MCI | 23) 
#define GPIO_MLCD_DB_12       (IOCONF_EBI_MCI | 24) 
#define GPIO_MLCD_DB_13       (IOCONF_EBI_MCI | 25) 
#define GPIO_MLCD_DB_14       (IOCONF_EBI_MCI | 26) 
#define GPIO_MLCD_DB_15       (IOCONF_EBI_MCI | 27) 
#define GPIO_MGPIO5           (IOCONF_EBI_MCI | 28) 
#define GPIO_MGPIO7           (IOCONF_EBI_MCI | 29) 
#define GPIO_MGPIO8           (IOCONF_EBI_MCI | 30) 
#define GPIO_MGPIO10          (IOCONF_EBI_MCI | 31) 
                
#define GPIO_MNAND_RYBN1      (IOCONF_EBI_I2STX_0 | 0) 
#define GPIO_MNAND_RYBN2      (IOCONF_EBI_I2STX_0 | 1) 
#define GPIO_MNAND_RYBN3      (IOCONF_EBI_I2STX_0 | 2) 
#define GPIO_MUART_CTS_N      (IOCONF_EBI_I2STX_0 | 3) 
#define GPIO_MUART_RTS_N      (IOCONF_EBI_I2STX_0 | 4) 
#define GPIO_MI2STX_DATA0     (IOCONF_EBI_I2STX_0 | 5) 
#define GPIO_MI2STX_WS0       (IOCONF_EBI_I2STX_0 | 6) 
#define GPIO_EBI_NRAS_BLOUT   (IOCONF_EBI_I2STX_0 | 7) 
#define GPIO_EBI_A_0_ALE      (IOCONF_EBI_I2STX_0 | 8) 
#define GPIO_EBI_NWE          (IOCONF_EBI_I2STX_0 | 9) 
                 
#define GPIO_CGU_SYSCLK_O     (IOCONF_CGU | 0) 

#define GPIO_I2SRX_BCK0       (IOCONF_I2SRX_0 | 0) 
#define GPIO_I2SRX_DATA0      (IOCONF_I2SRX_0 | 1) 
#define GPIO_I2SRX_WS0        (IOCONF_I2SRX_0 | 2) 
                  
#define GPIO_I2SRX_DATA1      (IOCONF_I2SRX_1 | 0) 
#define GPIO_I2SRX_BCK1       (IOCONF_I2SRX_1 | 1) 
#define GPIO_I2SRX_WS1        (IOCONF_I2SRX_1 | 2) 
                  
#define GPIO_I2STX_DATA1      (IOCONF_I2STX_1 | 0) 
#define GPIO_I2STX_BCK1       (IOCONF_I2STX_1 | 1) 
#define GPIO_I2STX_WS1        (IOCONF_I2STX_1 | 2) 
#define GPIO_I2STX_256FS_O    (IOCONF_I2STX_1 | 3) 
 
#define GPIO_EBI_D_9          (IOCONF_EBI | 0)  
#define GPIO_EBI_D_10         (IOCONF_EBI | 1)  
#define GPIO_EBI_D_11         (IOCONF_EBI | 2)  
#define GPIO_EBI_D_12         (IOCONF_EBI | 3)  
#define GPIO_EBI_D_13         (IOCONF_EBI | 4)  
#define GPIO_EBI_D_14         (IOCONF_EBI | 5)  
#define GPIO_EBI_D_4          (IOCONF_EBI | 6)  
#define GPIO_EBI_D_0          (IOCONF_EBI | 7)  
#define GPIO_EBI_D_1          (IOCONF_EBI | 8)  
#define GPIO_EBI_D_2          (IOCONF_EBI | 9)  
#define GPIO_EBI_D_3          (IOCONF_EBI | 10) 
#define GPIO_EBI_D_5          (IOCONF_EBI | 11) 
#define GPIO_EBI_D_6          (IOCONF_EBI | 12) 
#define GPIO_EBI_D_7          (IOCONF_EBI | 13) 
#define GPIO_EBI_D_8          (IOCONF_EBI | 14) 
#define GPIO_EBI_D_15         (IOCONF_EBI | 15) 
                  

#define GPIO_GPIO1            (IOCONF_GPIO | 0)  
#define GPIO_GPIO0            (IOCONF_GPIO | 1)  
#define GPIO_GPIO2            (IOCONF_GPIO | 2)  
#define GPIO_GPIO3            (IOCONF_GPIO | 3)  
#define GPIO_GPIO4            (IOCONF_GPIO | 4)  
#define GPIO_GPIO11           (IOCONF_GPIO | 5)  
#define GPIO_GPIO12           (IOCONF_GPIO | 6)  
#define GPIO_GPIO13           (IOCONF_GPIO | 7)  
#define GPIO_GPIO14           (IOCONF_GPIO | 8)  
#define GPIO_GPIO15           (IOCONF_GPIO | 9)  
#define GPIO_GPIO16           (IOCONF_GPIO | 10) 
#define GPIO_GPIO17           (IOCONF_GPIO | 11) 
#define GPIO_GPIO18           (IOCONF_GPIO | 12) 
#define GPIO_GPIO19           (IOCONF_GPIO | 13) 
#define GPIO_GPIO20           (IOCONF_GPIO | 14) 
                
#define GPIO_I2C_SDA1         (IOCONF_I2C1 | 0) 
#define GPIO_I2C_SCL1         (IOCONF_I2C1 | 1) 
                          
#define GPIO_SPI_MISO         (IOCONF_SPI | 0) 
#define GPIO_SPI_MOSI         (IOCONF_SPI | 1) 
#define GPIO_SPI_CS_IN        (IOCONF_SPI | 2) 
#define GPIO_SPI_SCK          (IOCONF_SPI | 3) 
#define GPIO_SPI_CS_OUT0      (IOCONF_SPI | 4) 
                 
#define GPIO_NAND_NCS_3       (IOCONF_NAND_CTRL | 0)
#define GPIO_NAND_NCS_0       (IOCONF_NAND_CTRL | 1)
#define GPIO_NAND_NCS_1       (IOCONF_NAND_CTRL | 2)
#define GPIO_NAND_NCS_2       (IOCONF_NAND_CTRL | 3)
                 
#define GPIO_PWM_DATA         (IOCONF_PWM | 0)
                  
#define GPIO_UART_RXD         (IOCONF_UART | 0)
#define GPIO_UART_TXD         (IOCONF_UART | 1)

#endif
