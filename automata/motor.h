#pragma once

#include <unistd.h>
#include <contiki.h>

#include <pbio/observer.h>
#include <pbio/parent.h>
#include <pbio/servo.h>
#include <pbio/error.h>
#include <pbio/drivebase.h>
#include <pbio/int_math.h>
#include <pbio/imu.h>

#include <pbdrv/clock.h>
#include <pbdrv/legodev.h>

#include "print.h"
#include "parameters.h"

/**
 * Getting instance of motor.
 * @param port_id is hub port with plugged motor.
 * @param [out] device is pointer, where the motor will be initialize.
 */
pbio_error_t get_large_motor(pbio_port_id_t port_id, pbio_servo_t **device);
pbio_error_t get_medium_motor(pbio_port_id_t port_id, pbio_servo_t **device);
pbio_error_t get_small_motor(pbio_port_id_t port_id, pbio_servo_t **device);

pbio_error_t get_motor2();

/**
 * Getting status about motor.
 * @param [out] angle is pointer, where the motor angle will be initialize.
 * @param [out] speed is pointer, where the motor speed will be initialize.
 */
pbio_error_t motor_get_status(pbio_servo_t *device, int32_t *angle, int32_t *speed); //TODO ME: need to be tested

pbio_error_t motor_run_time(pbio_servo_t *device, int32_t speed, int32_t milliseconds);

pbio_error_t motor_run_forever(pbio_servo_t *device, int32_t speed);

pbio_error_t motor_stop(pbio_servo_t *device);

/**
 * @param speed in deg/s.
 * @param angle is target.
 */
pbio_error_t motor_run_angle(pbio_servo_t *device, int32_t speed, int32_t angle);

/**
 * Getting instance of robot with two motors.
 * @param [out] base is pointer, where the robot will be initialize.
 * @param left is left motor.
 * @param right is right motor.
*/
pbio_error_t get_base(pbio_drivebase_t **base, pbio_servo_t *left, pbio_servo_t *right);

bool base_is_done(pbio_drivebase_t *drive);

/**
 * @param speed in mm/s.
 * @param angle in deg/s.
 */
pbio_error_t base_run_forever(pbio_drivebase_t *base, int32_t speed, int32_t angle);

pbio_error_t base_stop(pbio_drivebase_t *base);

/**
 * @param distance in mm is target.
 */
pbio_error_t base_run_distance(pbio_drivebase_t *base, int32_t distance);

/**
 * @param radius in mm is target.
 * @param angle in deg is speed of turning.
 */
pbio_error_t base_run_angle(pbio_drivebase_t *base, int32_t radius, int32_t angle);  //TODO ME: test it if it run angle

/**
 * @param left_speed in deg/s.
 * @param right_speed in deg/s.
 */
pbio_error_t base_run_forever_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed);

/**
 * @param left_speed in deg/s.
 * @param right_speed in deg/s.
 * @param duration in ms.
 */
pbio_error_t base_run_time_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed, int32_t duration);

/**
 * @param left_speed in deg/s.
 * @param right_speed in deg/s.
 * @param angle in deg, that the fast motor should travel.
 */
pbio_error_t base_run_angle_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed, int32_t angle);