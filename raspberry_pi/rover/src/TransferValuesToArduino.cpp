#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "../include/TransferValuesToArduino.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

static const char *device = "/dev/spidev1.2";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;

void ByteTranslation(unsigned char x_separated[5], int x)
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

int transfer(int fd, int angle, unsigned char order)
{
	int ret;
	unsigned char angle_transe[5];
	ByteTranslation(angle_transe, angle);

	uint8_t tx[] = {
		angle_transe[0], angle_transe[1], angle_transe[2], angle_transe[3], angle_transe[4],
		order, order,
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
		.bits_per_word = bits};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		cerr << "can't send spi message" << endl;
		return ret;
	}
}

int OpenSPI()
{
	int fd = open(device, O_RDWR);
	if (fd < 0)
	{
		cerr << "can't open device" << endl;
		return -1;
	}

	/*
	 * spi mode
	 */
	int ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
	{
		cerr << "can't set spi mode" << endl;
		return -1;
	}

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
	{
		cerr << "can't get spi mode" << endl;
		return -1;
	}

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		cerr << "can't set bits per word" << endl;
		return -1;
	}

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		cerr << "can't get bits per word" << endl;
		return -1;
	}

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		cerr << "can't set max speed hz" << endl;
		return -1;
	}

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		cerr << "can't get max speed hz" << endl;
		return -1;
	}

	return fd;
}

void TransferValuesToArduino(int angle, unsigned char order)
{
	int fd = OpenSPI();
	if (fd < 0)
	{
		return;
	}
	else
	{
		transfer(fd, angle, order);

		close(fd);
	}
}
