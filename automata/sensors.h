#pragma once

#include <unistd.h>

#include <pbdrv/legodev.h>

#include "automata.h"

/**
 * Getting instance of the distance sensor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbdrv_legodev_dev_t *sensor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_distance_sensor();

/**
 * Getting low data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_low_distance_data();

/**
 * Getting high data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_high_distance_data();

/**
 * Getting single data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_single_distance_data();

/**
 * Getting instance of the force sensor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbdrv_legodev_dev_t *sensor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_force_sensor();

/**
 * Getting raw data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_raw_force_data();

/**
 * Getting instance of the color sensor.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to pbdrv_legodev_dev_t *sensor.
 * <br><br> [in] parameters_3 is pointer to pbio_port_id_t *port_id.
 */
void get_color_sensor();

/**
 * Getting color data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint8_t] (color enum is in SPIKE Prime documentations).
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_color_data();

/**
 * Getting reflection data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint8_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_reflection_data();

/**
 * Getting ambient data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [1xint8_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_ambient_data();

/**
 * Getting rgb data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [4xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_rgb_data();

/**
 * Getting hsv data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [3xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_hsv_data();

/**
 * Getting scaled hsv data of the distance.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to void *data [4xint16_t].
 * <br><br> [in] parameters_3 is pointer to pbdrv_legodev_dev_t *sensor.
 */
void get_scaled_hsv_data();