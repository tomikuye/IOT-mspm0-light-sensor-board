#include "ti_msp_dl_config.h"

#define I2C_TARGET_ADDRESS (0x29) // 7-bit address for BH1750

uint8_t cmd = 0x10; // Continuous H-Resolution Mode
uint8_t on_cmd = 0x01;
volatile uint8_t gRxPacket[2];
uint16_t raw;
float lux;
int int_lux;

void delay_ms(uint32_t ms) {
    // crude delay at 16MHz, ~16000 cycles per ms
    for (volatile uint32_t i = 0; i < (16000 * ms); i++);
}

/*
 * Number of bytes for UART packet size
 * The packet will be transmitted by the UART.
 * This example uses FIFOs with polling, and the maximum FIFO size is 4.
 * Refer to interrupt examples to handle larger packets.
 */
#define UART_PACKET_SIZE (18)

/* Delay for 5ms to ensure UART TX is idle before starting transmission */
#define UART_TX_DELAY (160000)

/* Data for UART to transmit */
uint8_t txPacket[UART_PACKET_SIZE] = {};

int main(void)
{
    SYSCFG_DL_init();

    // Turn on LED to indicate start
    for(int i = 0; i < 4; i++){
            DL_GPIO_togglePins(GPIO_LEDS_PORT,
                GPIO_LEDS_USER_LED_1_PIN | GPIO_LEDS_USER_TEST_PIN);
            delay_cycles(16000000);
    }

    // Send 0x10 command to BH1750
    DL_I2C_fillControllerTXFIFO(I2C_INST, &on_cmd, 1);
    while (!(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(I2C_INST, I2C_TARGET_ADDRESS,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    while (DL_I2C_getControllerStatus(I2C_INST) &
             DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
      if (DL_I2C_getControllerStatus(I2C_INST) &
          DL_I2C_CONTROLLER_STATUS_ERROR) {
          // Sensor didn't ACK the command
          while (1);
      }

    DL_I2C_fillControllerTXFIFO(I2C_INST, &cmd, 1);
    while (!(DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(I2C_INST, I2C_TARGET_ADDRESS,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    while (DL_I2C_getControllerStatus(I2C_INST) &
           DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    if (DL_I2C_getControllerStatus(I2C_INST) &
        DL_I2C_CONTROLLER_STATUS_ERROR) {
        // Sensor didn't ACK the command
        while (1);
    }

    // Wait ~180ms for first measurement
    delay_ms(800);

    /* Wait for I2C to be Idle */
    while (!(DL_I2C_getControllerStatus(I2C_INST) &
             DL_I2C_CONTROLLER_STATUS_IDLE))
        ;


    // Loop: read every 10s and blink LED if I2C read and UART TX successful
    while (1) {
        DL_I2C_startControllerTransfer(I2C_INST, I2C_TARGET_ADDRESS,
                                       DL_I2C_CONTROLLER_DIRECTION_RX, 2);

        // Wait for and read both bytes
        for (uint8_t i = 0; i < 2; i++) {
            while (DL_I2C_isControllerRXFIFOEmpty(I2C_INST)){
            gRxPacket[i] = DL_I2C_receiveControllerData(I2C_INST);
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
            }
        }



        raw = ((uint16_t)gRxPacket[0] << 8) | gRxPacket[1];
        lux = (float)raw / 1.2f;    /* Convert per datasheet */
        uint8_t line[18];
        int_lux = snprintf(line, sizeof(line),
                           "Lux=%.0f\r\n",
                           lux);


        /* Fills TX FIFO with data and transmits the data */
        DL_UART_Main_fillTXFIFO(UART_0_INST, &line, int_lux);

        /* Wait until all bytes have been transmitted and the TX FIFO is empty */
        while (DL_UART_Main_isBusy(UART_0_INST))
            ;


        //Once successful blink the led
        for(int i = 0; i < 4; i++){
                DL_GPIO_togglePins(GPIO_LEDS_PORT,
                    GPIO_LEDS_USER_LED_1_PIN | GPIO_LEDS_USER_TEST_PIN);
                delay_cycles(16000000);
        }


        delay_ms(10000);



}
}
