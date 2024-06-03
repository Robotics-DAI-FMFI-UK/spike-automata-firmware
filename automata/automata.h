#pragma once

#include <unistd.h>
#include <stdlib.h>
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

void do_events(void);

void delay(int milliseconds);

int start_automata(void);

void follow();

void discover();

void tilt();