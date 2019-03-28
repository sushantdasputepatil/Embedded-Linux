static int init_serial(void)
{	
	int fd;
	
	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (fd == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
	return fd;
}
