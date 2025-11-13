#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Read ADC value from given channel
int read_adc(int channel) {
  char path[64];
  char value_str[8];
  int fd;
  // Construct sysfs path
  snprintf(path, sizeof(path),
           "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", channel);
  // Open ADC sysfs file
  fd = open(path, O_RDONLY);
  if (fd < 0) {
    perror("Failed to open ADC file");
    return -1;
  }
  // Read the value
  if (read(fd, value_str, sizeof(value_str)) < 0) {
    perror("Failed to read ADC value");
    close(fd);
    return -1;
  }
  close(fd);
  return atoi(value_str); // Convert string to integer
}
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <adc_channel>\n", argv[0]);
    return 1;
  }
  int channel = atoi(argv[1]);
  while (1) {
    int value = read_adc(channel);
    if (value >= 0) {
      printf("ADC Channel %d Value: %d\n", channel, value);
    }
    usleep(500000); // 0.5 second delay
  }
  return 0;
}
