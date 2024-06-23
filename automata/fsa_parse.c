#include <stdlib.h>
#include <string.h>

#include "automata.h"
#include "serial_reader.h"
#include "fsa_parse.h"


uint8_t received2[100000];
uint32_t recvptr2 = 0;

void fsa_parse() {
    int line_number = 0;
    do {
        uint8_t *line;
        uint8_t line_arrived = read_line(&line);
        if (line_arrived == 0) break;
        uint32_t len = strlen((char *)line);
        memcpy(received2 + recvptr2, line, len);
        recvptr2 += len;
        received2[recvptr2++] = '\r';
        received2[recvptr2++] = '\n';
        //pbsys_bluetooth_tx(line, &len);
        //len = 2;
        //pbsys_bluetooth_tx((uint8_t *)"\r\n", &len);

        line_number++;
    } while (1);

    uint32_t i = 0;
    uint32_t size = 0;
    for ( ; i < recvptr2 / 10; i++) {
        size = 10;
        pbsys_bluetooth_tx(received2 + i * 10, &size);
        delay(100);
    }

    size = recvptr2 - i * 10;
    pbsys_bluetooth_tx(received2 + i * 10, &size);
    delay(10);


    size = 17;
    pbsys_bluetooth_tx((uint8_t *)"number of lines: ", &size);
    delay(20);
    char nlines[15];
    snprintf(nlines, 10, "\r\n%d\r\n", line_number);
    size = strlen(nlines);
    pbsys_bluetooth_tx((uint8_t *)nlines, &size);
    delay(20);
}