#include<stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "../include/SPIOpen.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;

void ByteTranslation(unsigned char x_separated[5],int x)
{
	const unsigned int char_size = 8;
	unsigned int hash = 0;
	for (int i = 0; i < 4; i++)
	{
		x_separated[i] = ((x >> char_size * i) & 0xFF);
		hash += x_separated[i];
	}
	x_separated[4] = (unsigned char)(hash % 256);
}

void transfer(int fd,int angle, unsigned char order)
{
	int ret;
	unsigned char angle_transe[5];
	ByteTranslation(angle_transe, angle);

	uint8_t tx[] = {
		angle_transe[0], angle_transe[1], angle_transe[2], angle_transe[3], angle_transe[4],
		order,order,
		0x0A};
	uint8_t rx[ARRAY_SIZE(tx)] = {
		0,
	};
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = ARRAY_SIZE(tx),
		.speed_hz = speed,
		.delay_usecs = delay,
		.bits_per_word = bits
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		pabort("can't send spi message");
}


void TransferValuesToArduino(int angle, unsigned char order)
{
	int fd = SPIOpen();

	transfer(fd,angle, order);

	close(fd);
}
