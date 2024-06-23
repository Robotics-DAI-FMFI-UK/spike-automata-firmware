#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <contiki.h>
#include <lib/memb.h>

#include <pbdrv/counter.h>
#include <pbdrv/legodev.h>
#include <pbdrv/sound.h>

#include <pbio/angle.h>
#include <pbio/int_math.h>
#include <pbio/observer.h>
#include <pbio/parent.h>
#include <pbio/servo.h>
#include <pbio/light_matrix.h>
#include <pbio/geometry.h>
#include <pbio/imu.h>
#include <pbio/protocol.h>

#include <pbsys/light.h>
#include <pbsys/status.h>

#include "print.h"
#include "sensors.h"
#include "motor.h"
#include "modules.h"
#include "parameters.h"

// sprintf for conversion numbers to string

/*
 * #include <stdio.h>
 *
 * void int_to_string(int value, char *buffer, size_t buffer_size) {
 *     snprintf(buffer, buffer_size, "%d", value);
 * }
 */

//#define MAX_NAME_LENGTH 50
//#define DEFAULT_DELAY 250
//
//typedef enum {
//    STRING,
//    BOOLEAN,
//    INTEGER,
//    PORT
//} type;
//
//typedef struct variable{
//    char[MAX_NAME_LENGTH] name;
//
//} variable;
//
//typedef struct condition {
//
//} condition;
//
//typedef struct task {
//
//} task;
//
//typedef struct {
//    char[MAX_NAME_LENGTH] to_state;
//    condition *conditions;
//    task *task;
//} transition;
//
//typedef struct {
//    char[MAX_NAME_LENGTH] name;
//    transition *transition;
//    int transition_count;
//
//    // task maintain
//    bool have_task = false;
//    task *tasks;
//    int delay_between_task = DEFAULT_DELAY;
//
//    // sub automata maintain
//    bool have_sub_automata = false;
//    char *sub_automata_name;
//} state;

void do_events(void);

void delay(int milliseconds);

int start_automata(void);

void follow();

void discover();

void tilt();

//void parse_automata(uint8_t message, uint32_t length);