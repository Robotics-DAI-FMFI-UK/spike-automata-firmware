#include "print.h"
#include "string.h"

void print_message(const char *message) {
    uint32_t message_size = strlen(message);
    pbsys_bluetooth_tx((unsigned char *) message, &message_size);

    char *new_line = "\r\n";
    message_size = 2;
    pbsys_bluetooth_tx((unsigned char *) new_line, &message_size);
}

void int_to_str(long number, char *string) {
    long number_copy = number;
    int digits = 1;
    long constant = 1;

    while (number_copy /= 10) {
        digits++;
        constant *= 10;
    }

    if (number < 0) {
        *(string++) = '-';
        number = -number;
    }
    while (constant > 0) {
        *(string++) = '0' + number / constant;
        number = number % constant;
        constant /= 10;
    }
    *string = 0;
}


void print_value(const char *message, int value) {
    uint32_t message_size = strlen(message);
    pbsys_bluetooth_tx((unsigned char *) message, &message_size);

    char string_value[23];
    int_to_str(value, string_value);

    message_size = strlen(string_value);
    pbsys_bluetooth_tx((unsigned char *) string_value, &message_size);

    char *new_line = "\r\n";
    message_size = 2;
    pbsys_bluetooth_tx((unsigned char *) new_line, &message_size);
}