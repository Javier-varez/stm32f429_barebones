
#include <stdint.h>

#define GPIOA_BASE		0x40020000
#define GPIOG_BASE 		0x40021800
#define GPIO_MODER_OFFSET	0x00
#define GPIO_OTYPER_OFFSET	0x04
#define GPIO_OSPEEDR_OFFSET	0x08
#define GPIO_PUPDR_OFFSET	0x0C
#define GPIO_IDR_OFFSET		0x10
#define GPIO_ODR_OFFSET		0x14
#define GPIO_BSRR_OFFSET	0x18
#define GPIO_LCKR_OFFSET	0x1C
#define GPIO_AFRL_OFFSET	0x20
#define GPIO_AFRH_OFFSET	0x24

#define RCC_BASE   0x40023800
#define RCC_AHB1ENR_OFFSET 0x30

void button_test() {
	*(uint32_t*)(RCC_BASE + RCC_AHB1ENR_OFFSET) = (1<<6) | (1<<0); // EN CLK FOR GPIO G and A
	*(uint32_t*)(GPIOG_BASE + GPIO_MODER_OFFSET) = (0x01<<26) | (0x01<<28); // OUTs
	*(uint32_t*)(GPIOG_BASE + GPIO_BSRR_OFFSET) = (0x01<<13) | (0x01<<14); // Turn on LED's

	while(1) {
		uint32_t data = *(uint32_t*)(GPIOA_BASE + GPIO_IDR_OFFSET);
		*(uint32_t*)(GPIOG_BASE + GPIO_ODR_OFFSET) = (data & 0x00000001) << 13 | 1<<14;
	}
}

void led_flash() {
	*(uint32_t*)(RCC_BASE + RCC_AHB1ENR_OFFSET) = (1<<6) | (1<<0); // EN CLK FOR GPIO G and A
	*(uint32_t*)(GPIOG_BASE + GPIO_MODER_OFFSET) = (0x01<<26) | (0x01<<28); // OUTs
	*(uint32_t*)(GPIOG_BASE + GPIO_BSRR_OFFSET) = (0x01<<13) | (0x01<<14); // Turn on LED's

	while(1) {
		for(int i = 0; i < 1000000; i++);
		*(uint32_t*)(GPIOG_BASE + GPIO_BSRR_OFFSET) = (0x01<<13) | (0x01<<30); // Turn off LED's
		for(int i = 0; i < 1000000; i++);
		*(uint32_t*)(GPIOG_BASE + GPIO_BSRR_OFFSET) = (0x01<<29) | (0x01<<14); // Turn on LED's
	}
}

void main()
{
	//button_test();	
	led_flash();
}
