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
 * Setup large motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to pbio_direction_t *direction.
 */
void motor_large_setup();

/**
 * Setup medium motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to pbio_direction_t *direction.

 */
void motor_medium_setup();

/**
 * Setup small motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to pbio_direction_t *direction.
 */
void motor_small_setup();

/**
 * Getting instance of large motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_large_motor();

/**
 * Getting instance of medium motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_medium_motor();

/**
 * Getting instance of small motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_small_motor();

/**
 * Getting status about motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in, out] parameters_1 is pointer to int32_t *angle [deg].
 * <br><br> [in, out] parameters_2 is pointer to int32_t *speed [deg/s].
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 */
void motor_get_status();

/**
 * Run the motor for the time.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to int32_t *speed [deg/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *time [ms].
 */
void motor_run_time();

/**
 * Run the motor forever.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to int32_t *speed [deg/s].
 */
void motor_run_forever();

/**
 * Run the motor for the angle.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 * <br><br> [in] parameters_4 is pointer to int32_t *speed [deg/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *angle [deg].
 */
void motor_run_angle();

/**
 * Stop motor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *motor.
 */
void motor_stop();

/**
 * Getting instance of drive base.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbio_drivebase_t *drive.
 * <br><br> [in] parameters_3 is pointer to pbio_servo_t *left_motor.
 * <br><br> [in] parameters_4 is pointer to pbio_servo_t *right_motor.
 */
void get_base();

/**
 * Getting bool if drive base is done.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_1 is pointer to bool *done.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 */
void base_is_done();

/**
 * Run the drive base forever.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *speed [mm/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *turn_rate_angle [deg/s].
 */
void base_run_forever();

/**
 * Stop the drive base.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 */
void base_stop();

/**
 * Run the drive base for the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *distance [mm].
 */
void base_run_distance();

/**
 * Run the drive base for the angle.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *radius [mm].
 * <br><br> [in] parameters_5 is pointer to int32_t *angle [deg].
 */
void base_run_angle();

/**
 * Run the drive base forever with different speed.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *left_speed [deg/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *right_speed [deg/s].
 */
void base_run_forever_different();

/**
 * Run the drive base time with different speed.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *left_speed [deg/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *right_speed [deg/s].
 * <br><br> [in] parameters_6 is pointer to int32_t *time [ms].
 */
void base_run_time_different();

/**
 * Run the drive base with different speed until faster motor travel angle.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_drivebase_t *drive_base.
 * <br><br> [in] parameters_4 is pointer to int32_t *left_speed [deg/s].
 * <br><br> [in] parameters_5 is pointer to int32_t *right_speed [deg/s].
 * <br><br> [in] parameters_6 is pointer to int32_t *angle_of_faster_motor [deg].
 */
void base_run_angle_different();