#pragma once
#define USBD_PRODUCT_STRING     "FahmyF722"
#define USBD_MANUFACTURER_STRING "Fahmy"
#define TARGET_BOARD_IDENTIFIER "F7YA"

#define LED0_PIN                PB01
#define LED1_PIN                PB02
#define LED2_PIN                PB00

#define SPI1_SCK_PIN            PA05
#define SPI1_MISO_PIN           PA06
#define SPI1_MOSI_PIN           PA07

#define SPI3_SCK_PIN            PC10
#define SPI3_MISO_PIN           PC11
#define SPI3_MOSI_PIN           PC12

#define IMU_SPI_INSTANCE        SPI3
#define IMU_CS_PIN              PD02
#define IMU_INT_PIN             PC13

#define BARO_I2C_INSTANCE       I2C1
#define BARO_SCL_PIN            PB08
#define BARO_SDA_PIN            PB09

#define USB_DETECT_PIN          NONE
#define USB_DM_PIN              PA11
#define USB_DP_PIN              PA12

#define BEEPER_PIN              NONE
#define BATTERY_VOLTAGE_PIN     PC02
#define BATTERY_VOLTAGE_DIVIDER 11.0f

#define MOTOR1_PIN              PA00
#define MOTOR2_PIN              PA01
#define MOTOR3_PIN              PB05
#define MOTOR4_PIN              PC08

#define SERIAL_PORT_COUNT       1
#define SERIAL_PORT_USART1      NONE

#define DEFAULT_RX_TYPE         RX_TYPE_NONE