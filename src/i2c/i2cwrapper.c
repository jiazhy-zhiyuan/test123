#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include "i2cwrapper.h"

static int __open_i2c_dev(int i2cbus)
{
	int file;
	char filename[32] = "";

	sprintf(filename, "/dev/i2c/%d", i2cbus);
	file = open(filename, O_RDWR);

	if (file < 0 && (errno == ENOENT || errno == ENOTDIR)) {
		sprintf(filename, "/dev/i2c-%d", i2cbus);
		file = open(filename, O_RDWR);
	}

	return file;
}

static int i2c_bus_fd1 = -1;
static int i2c_bus_fd2 = -1;

int __open_i2c(I2C_BUS_NR bus)
{
	int fd = -1;

	if(I2C_BUS_1 == bus) {
		if(i2c_bus_fd1 < 0)
			i2c_bus_fd1 = __open_i2c_dev(1);
		fd = i2c_bus_fd1;
	} else if(I2C_BUS_2 == bus) {
		if(i2c_bus_fd2 < 0)
			i2c_bus_fd2 = __open_i2c_dev(2);
		fd = i2c_bus_fd2;
	}

	if(fd >= 0) {
		ioctl(fd, I2C_TIMEOUT, 2);	// ���ó�ʱʱ��
		ioctl(fd, I2C_RETRIES, 1);	// �����ط�����
	}

	return fd;
}

unsigned char read_i2c_byte8(I2C_BUS_NR bus, int chipaddr, int regaddr)
{
	unsigned char regvalue;
	unsigned char temp[2];
	struct i2c_msg msg[2];

	int fd = __open_i2c(bus);
	if(fd < 0)
		return 0xff;

	struct i2c_rdwr_ioctl_data e2prom_data;
	e2prom_data.nmsgs = 2;			//��ʱ��Ҫ���ι��̣�Ҫ������I2C��Ϣ
	e2prom_data.msgs = msg;
	e2prom_data.msgs[0].len = 1;		//��Ϣ����Ϊ1����һ��ֻдҪ����eeprom�д洢��Ԫ�ĵ�ַ
	e2prom_data.msgs[0].addr = chipaddr;
	e2prom_data.msgs[0].flags = 0;		//д�������ʱ�����
	e2prom_data.msgs[0].buf = temp;
	e2prom_data.msgs[0].buf[0] = regaddr;	//��Ϣֵ

	e2prom_data.msgs[1].len = 1;
	e2prom_data.msgs[1].addr = chipaddr;
	e2prom_data.msgs[1].flags = I2C_M_RD;	//������
	e2prom_data.msgs[1].buf = &regvalue;
	e2prom_data.msgs[1].buf[0] = 0;		//�����Ҫ���Ļ�����
	ioctl (fd, I2C_RDWR, (unsigned long)&e2prom_data);

	return regvalue;
}

void write_i2c_byte8(I2C_BUS_NR bus, int chipaddr, int regaddr, unsigned char regvalue)
{
	int fd = __open_i2c(bus);
	if(fd < 0)
		return;

	ioctl(fd, I2C_SLAVE_FORCE, chipaddr);
	unsigned char data[2];
	data[0] = regaddr;
	data[1] = regvalue;
	write(fd, &data, 2);
}

