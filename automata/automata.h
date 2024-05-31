#pragma once

#include "print.h"
#include "sensors.h"
#include "motor.h"
#include "modules.h"
#include "parameters.h"

// implemented:
void do_events(void);

void delay(int milliseconds);

int start_automata(void);

int follow(void);

//TODO ME: check all high all low number