#include <string.h>
#include "serial_reader.h"
#include "automata.h"

#define SERIAL_MAX_LINE_LENGTH  300
#define SERIAL_ONE_TIME_READ 20
#define SERIAL_LINE_TIMEOUT_MS 3000

uint8_t current_line[SERIAL_MAX_LINE_LENGTH];
uint16_t line_length;
uint8_t remains[SERIAL_ONE_TIME_READ];
uint8_t amount_remaining = 0;


uint8_t read_line(uint8_t **destination_pointer)
{
    *destination_pointer = current_line;

    do_events();
    if (amount_remaining)
    {
        uint8_t how_much_to_take_from_remaining = 0;
        while ((how_much_to_take_from_remaining < amount_remaining) &&
               (remains[how_much_to_take_from_remaining] != '\r')) how_much_to_take_from_remaining++;

        if (how_much_to_take_from_remaining < amount_remaining)
        {
            memcpy(current_line, remains, how_much_to_take_from_remaining);
            memcpy(remains, remains + (how_much_to_take_from_remaining + 1), amount_remaining - how_much_to_take_from_remaining - 1);
            amount_remaining -= how_much_to_take_from_remaining + 1;
            current_line[how_much_to_take_from_remaining] = 0;
            return 1;
        }
        else
        {
            memcpy(current_line, remains, amount_remaining);
            line_length = amount_remaining;
            amount_remaining = 0;
        }
    }
    else line_length = 0;

    uint8_t waiting = 0;
    uint32_t started_waiting = 0;
    do {
        do_events();
        uint32_t size = SERIAL_ONE_TIME_READ;
        pbio_error_t err = pbsys_bluetooth_rx(current_line + line_length, &size);
        if (err == PBIO_ERROR_AGAIN) {
            if (!waiting) {
                started_waiting = pbdrv_clock_get_ms();
                waiting = 1;
            } else {
                if (pbdrv_clock_get_ms() - started_waiting > SERIAL_LINE_TIMEOUT_MS) break;
            }
            delay(4);
            continue;
        }
        waiting = 0;

        uint8_t *p = current_line + line_length;
        for (uint32_t i = 0; i < size; i++)
            if (*(p + i) == '\r') {
                *(p + i) = 0;
                if (i < size - 1) {
                    amount_remaining = size - i - 1;
                    memcpy(remains, p + i + 1, amount_remaining);
                }
                return 1;
            }
        line_length += size;
    } while (1);
    // line was not terminated by \n until timeout, but we return it anyway
    current_line[line_length] = 0;
    if (line_length)
        return 1;

    const char *terminated = "Empty read with timeout.\r\n";
    uint32_t length = strlen(terminated);
    pbsys_bluetooth_tx((uint8_t *)terminated, &length);

    return 0;
}