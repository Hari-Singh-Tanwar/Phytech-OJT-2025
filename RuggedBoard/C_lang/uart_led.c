#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define GPIO_EN  "/sys/class/gpio/export"

#define LED1_DIR "/sys/class/gpio/PC13/direction"
#define LED1_VAL "/sys/class/gpio/PC13/value"

int  led1_fd;
char gpio_buf[30];
int  led1_num = 77;

void led_init()
{
        //led1 export
        led1_fd = open(GPIO_EN,O_WRONLY);
        if(led1_fd < 0)
        {
                printf("Unable to open the file  %s\n",GPIO_EN);
                exit(0);
        }
        printf("Enable LED1\n");
        sprintf(gpio_buf,"%d",led1_num);
        write(led1_fd,gpio_buf,strlen(gpio_buf));
        close(led1_fd);
        
         //led1 direction
        printf("Configuring LED1 direction  \n");
        led1_fd = open(LED1_DIR,O_WRONLY);
        if(led1_fd < 0)
        {
                printf("Unable to open the file   %s",LED1_DIR);
                exit(0);
        }

        write(led1_fd,"out",3);
        close(led1_fd);
        
        //LED1 value
        printf("Set the value into LED1_Val \n");

        led1_fd = open( LED1_VAL,O_WRONLY);
        if(led1_fd < 0)
        {
                printf("Unable to open the file   %s",LED1_VAL);
                exit(0);
        }
 }

int set_interface_attribs(int fd, int speed) {
  struct termios tty;
  if (tcgetattr(fd, &tty) < 0) {
    printf("Error from tcgetattr: %s\n", strerror(errno));
    return -1;
  }
  cfsetispeed(&tty, (speed_t)speed);
  cfsetospeed(&tty, (speed_t)speed);
  tty.c_cflag |= (CLOCAL | CREAD); /* ignore modem controls */
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;      /* 8-bit characters */
  tty.c_cflag &= ~PARENB;  /* no parity bit */
  tty.c_cflag &= ~CSTOPB;  /* only need 1 stop bit */
  tty.c_cflag &= ~CRTSCTS; /* no hardware flowcontrol */
  tty.c_iflag = IGNPAR;
  tty.c_lflag = 0;    /* no signaling chars, no echo, no canonical processing */
  tty.c_oflag = 0;    /* no remapping, no delays */
  tty.c_cc[VMIN] = 0; /* non-blocking read */
  tty.c_cc[VTIME] = 10; /* 1 second read timeout */
  if (tcsetattr(fd, TCSANOW, &tty) != 0) {
    printf("Error from tcsetattr: %s\n", strerror(errno));
    return -1;
  }
  return 0;
}

int main() {
  led_init();
  printf("Toggling the LEDs! \n");
  
  char *portname = "/dev/ttyS3";
  int fd;
  ssize_t wlen, rdlen;
  unsigned char buf[100];
  char input[100];
  fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    printf("Error opening %s: %s\n", portname, strerror(errno));
    return -1;
  }
  if (set_interface_attribs(fd, B9600) < 0) {
    close(fd);
    return -1;
  }
  printf(
      "Enter text to send via serial (press ENTER to send, Ctrl+D to quit):\n");
  while (fgets(input, sizeof(input), stdin) != NULL) {
    size_t len = strlen(input);
    // Remove newline character from input if present
    if (len > 0 && input[len - 1] == '\n') {
      input[len - 1] = '\0';
      len--;
    }
    if (len == 0) {
      printf("Empty input, please enter something.\n");
      continue;
    }
    // Write input to serial port
    wlen = write(fd, input, len);
    if (wlen != len) {
      printf("Error from write: %ld, %s\n", wlen, strerror(errno));
    }
    // Try reading response from serial port (non-blocking)
    rdlen = read(fd, buf, sizeof(buf) - 1);
    if (rdlen > 0) {
      buf[rdlen] = '\0'; // Null-terminate
      printf("Received: %s\n", buf);
    } else if (rdlen < 0) {
      printf("Error from read: %s\n", strerror(errno));
    }
    
    if(strcmp(buf, "OFF") == 0)
    {
      printf("Led = OFF\n");
    write(led1_fd,"1" ,1);
    }
    else if (strcmp(buf, "ON") == 0)
    {
      printf("Led = ON\n");
    write(led1_fd,"0" ,1);
    }
  }
  printf("Exiting...\n");
  close(fd);
  return 0;
}
