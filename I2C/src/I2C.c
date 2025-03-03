#include "stm32f4xx.h"

#define GPIOBEN (1U<<1)
#define OT8 (1U<<8)
#define OT9 (1U<<9)

#define I2C1EN (1U<<21) // Corrected I2C1 Enable bit in RCC->APB1ENR
#define SWRST  (1U<<15)
#define PE     (1U<<0)

#define STANDARD_MODE_100KHZ 80

#define BUSY (1U<<1)
#define START (1U<<8)
#define SB (1U<<0)
#define ADDR (1U<<1)
#define TXE (1U<<7)
#define ACK (1U<<10)
#define STOP (1U<<9)
#define RXNE (1U<<6) // Corrected Receive Data Register Not Empty
#define BTF (1U<<2)

void i2c_gpio_init(void) {
    /* Enable clock for GPIOB */
    RCC->AHB1ENR |= GPIOBEN;

    /* Set PB8 & PB9 to Alternate Function Mode */
    GPIOB->MODER &= ~(1U << 16); // Clear bit 16
    GPIOB->MODER |= (1U << 17);  // Set bit 17 for PB8 (AF mode)

    GPIOB->MODER &= ~(1U << 18); // Clear bit 18
    GPIOB->MODER |= (1U << 19);  // Set bit 19 for PB9 (AF mode)

    /* Configure PB8 & PB9 as Open Drain */
    GPIOB->OTYPER |= OT8;
    GPIOB->OTYPER |= OT9;

    /* Enable Pull-Up resistors for PB8 and PB9 */
    GPIOB->PUPDR &= ~(3U << 16); // Clear both bits (PB8)
    GPIOB->PUPDR |= (1U << 16);  // Set bit 16 (Pull-Up for PB8)

    GPIOB->PUPDR &= ~(3U << 18); // Clear both bits (PB9)
    GPIOB->PUPDR |= (1U << 18);  // Set bit 18 (Pull-Up for PB9)

    /* Configure PB8 & PB9 as I2C (AF4) */
    GPIOB->AFR[1] &= ~(0xF << 0); // Clear PB8 AF
    GPIOB->AFR[1] |= (4U << 0);   // Set AF4 for PB8

    GPIOB->AFR[1] &= ~(0xF << 4); // Clear PB9 AF
    GPIOB->AFR[1] |= (4U << 4);   // Set AF4 for PB9
}

void i2c_config(void) {
    /* Initialize I2C GPIO */
    i2c_gpio_init();

    /* Enable clock for I2C1 */
    RCC->APB1ENR |= I2C1EN;

    /* Enter and exit software reset */
    I2C1->CR1 |= SWRST;
    I2C1->CR1 &= ~SWRST;

    /* Set clock frequency for 16MHz PCLK1 */
    I2C1->CR2 = 16U; // Directly setting value instead of bitwise operations

    /* Set I2C speed (Standard Mode) */
    I2C1->CCR = STANDARD_MODE_100KHZ;

    /* Set rise time (max 1000ns for Standard Mode) */
    I2C1->TRISE = 17;

    /* Enable I2C1 Peripheral */
    I2C1->CR1 |= PE;
}

void i2c_burstWrite(char saddr, char maddr, int n, char *data) {
    volatile int temp;

    /* Wait for bus to become free */
    while (I2C1->SR2 & BUSY);

    /* Generate START condition */
    I2C1->CR1 |= START;

    /* Wait for START condition to be generated */
    while (!(I2C1->SR1 & SB));

    /* Send slave address with Write (LSB = 0) */
    I2C1->DR = saddr << 1;

    /* Wait for address transmission */
    while (!(I2C1->SR1 & ADDR));

    /* Clear ADDR flag */
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    /* Send memory/register address */
    I2C1->DR = maddr;

    /* Transmit data */
    while (n > 0) {
        while (!(I2C1->SR1 & TXE)); // Wait until TXE is set
        I2C1->DR = *data++;
        n--;
    }

    /* Wait for data transfer completion */
    while (!(I2C1->SR1 & BTF));

    /* Generate STOP condition */
    I2C1->CR1 |= STOP;
}

void i2c_burstRead(char saddr, char maddr, int n, char *data) {
    volatile int temp;

    while (I2C1->SR2 & BUSY);
    I2C1->CR1 |= START;
    while (!(I2C1->SR1 & SB));

    I2C1->DR = saddr << 1;
    while (!(I2C1->SR1 & ADDR));
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    I2C1->DR = maddr;
    while (!(I2C1->SR1 & TXE));

    I2C1->CR1 |= START;
    while (!(I2C1->SR1 & SB));

    I2C1->DR = saddr | 1;
    while (!(I2C1->SR1 & ADDR));

    I2C1->CR1 |= ACK;
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    while (n > 0) {
        if (n == 1U) {
            I2C1->CR1 &= ~ACK;
            I2C1->CR1 |= STOP;
            while (!(I2C1->SR1 & RXNE));
            *data++ = I2C1->DR;
            break;
        } else {
            while (!(I2C1->SR1 & RXNE));
            *data++ = I2C1->DR;
            n--;
        }
    }
}

void i2c_byteRead(char saddr, char maddr, char *data) {
    volatile int temp;

    while (I2C1->SR2 & BUSY);
    I2C1->CR1 |= START;
    while (!(I2C1->SR1 & SB));

    I2C1->DR = saddr << 1;
    while (!(I2C1->SR1 & ADDR));

    temp = I2C1->SR1;
    temp = I2C1->SR2;

    I2C1->DR = maddr;
    while (!(I2C1->SR1 & TXE));

    I2C1->CR1 |= START;
    while (!(I2C1->SR1 & SB));

    I2C1->DR = saddr | 1;
    while (!(I2C1->SR1 & ADDR));

    I2C1->CR1 &= ~ACK;
    temp = I2C1->SR1;
    temp = I2C1->SR2;

    I2C1->CR1 |= STOP;
    while (!(I2C1->SR1 & RXNE));

    *data = I2C1->DR;
}
