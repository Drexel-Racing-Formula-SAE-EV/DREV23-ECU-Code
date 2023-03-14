/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void   MX_GPIO_Init(void);
void   MX_USART3_UART_Init(void);
void   MX_USB_OTG_FS_PCD_Init(void);
void   MX_ADC1_Init(void);
void   MX_CAN1_Init(void);
void   MX_SPI4_Init(void);
void   MX_ADC2_Init(void);
void   MX_ADC3_Init(void);
void   MX_I2C2_Init(void);
void   MX_RTC_Init(void);
void   MX_SPI6_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define Pressure_Transducer_2_Analog_Pin GPIO_PIN_3
#define Pressure_Transducer_2_Analog_GPIO_Port GPIOF
#define Misc_IO2_Pin GPIO_PIN_5
#define Misc_IO2_GPIO_Port GPIOF
#define BAMOCAR_RDY_State_Pin GPIO_PIN_10
#define BAMOCAR_RDY_State_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define APPS_2_Analog_Pin GPIO_PIN_0
#define APPS_2_Analog_GPIO_Port GPIOC
#define Pressure_Transducer_1_Analog_Pin GPIO_PIN_3
#define Pressure_Transducer_1_Analog_GPIO_Port GPIOC
#define APPS1_Analog_Pin GPIO_PIN_3
#define APPS1_Analog_GPIO_Port GPIOA
#define Misc_IO3_Pin GPIO_PIN_4
#define Misc_IO3_GPIO_Port GPIOA
#define Misc_IO4_Pin GPIO_PIN_5
#define Misc_IO4_GPIO_Port GPIOA
#define Firmware_Ok_Pin GPIO_PIN_7
#define Firmware_Ok_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define MISC_IO1_Pin GPIO_PIN_1
#define MISC_IO1_GPIO_Port GPIOB
#define BAMOCAR_FRG_RUN_Activate_Pin GPIO_PIN_12
#define BAMOCAR_FRG_RUN_Activate_GPIO_Port GPIOF
#define Buzzer_CRTL_Pin GPIO_PIN_13
#define Buzzer_CRTL_GPIO_Port GPIOF
#define IMD_Fail_Pin GPIO_PIN_14
#define IMD_Fail_GPIO_Port GPIOF
#define BMS_Fail_Pin GPIO_PIN_15
#define BMS_Fail_GPIO_Port GPIOF
#define BAMOCAR_RTD_Go_Pin GPIO_PIN_9
#define BAMOCAR_RTD_Go_GPIO_Port GPIOE
#define Firmware_Fail_Pin GPIO_PIN_11
#define Firmware_Fail_GPIO_Port GPIOE
#define BSPD_Fail_Pin GPIO_PIN_13
#define BSPD_Fail_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define Brake_Light_Control_Pin GPIO_PIN_14
#define Brake_Light_Control_GPIO_Port GPIOD
#define BAMOCAR_RFE_Activate_Pin GPIO_PIN_15
#define BAMOCAR_RFE_Activate_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define TSAL_HV_signal_Pin GPIO_PIN_9
#define TSAL_HV_signal_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
