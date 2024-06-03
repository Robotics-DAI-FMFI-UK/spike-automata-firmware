#include "print.h"
#include "string.h"

void print_message() {
    char *message_raw = (char *) parameters[10];
    char *new_line = "\r\n";
    size_t new_message_size = strlen(message_raw) + strlen(new_line) + 1;
    char new_message[new_message_size];
    strcpy(new_message, message_raw);
    strcat(new_message, new_line);

    const char *message = new_message;
    uint32_t message_size = strlen(message);
    uint32_t already_written = 0;
    uint32_t send = message_size;
    pbio_error_t err = PBIO_ERROR_INVALID_ARG;

    while (send != 0) {
        err = pbsys_bluetooth_tx((unsigned char *) message + already_written, &send);
        if (err == PBIO_ERROR_AGAIN)
            continue;
        if (err == PBIO_ERROR_INVALID_OP || err == PBIO_ERROR_NOT_SUPPORTED)
            break;
        already_written += send;
        send = message_size - already_written;
        delay(10);

    }
    if (err != PBIO_SUCCESS) {
        *(pbio_error_t *) parameters[0] = err;
    }
}

void int_to_str(long *number_raw, char *string) {
    long number = *number_raw;
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


void print_value() {
    char string_value[23];
    int_to_str((long *) parameters[11], string_value);

    char *message_raw = parameters[10];
    size_t new_message_size = strlen(message_raw) + strlen(string_value) + 1;
    char new_message[new_message_size];

    strcpy(new_message, message_raw);
    strcat(new_message, string_value);
    parameters[10] = new_message;
    print_message();
}

void print_float() {
    char string_value[23];
    long x = *(float *) parameters[11];
    int_to_str(&x, string_value);

    char *message_raw = parameters[10];
    size_t new_message_size = strlen(message_raw) + strlen(string_value) + 1;
    char new_message[new_message_size];

    strcpy(new_message, message_raw);
    strcat(new_message, string_value);
    parameters[10] = new_message;
    print_message();
}



void print_error() {
    char string_value[23];
    long error = *(pbio_error_t *) parameters[0];
    int_to_str(&error, string_value);

    char *message_raw = parameters[10];
    size_t new_message_size = strlen(message_raw) + strlen(string_value) + 1;
    char new_message[new_message_size];

    strcpy(new_message, message_raw);
    strcat(new_message, string_value);
    parameters[10] = new_message;
    print_message();
}