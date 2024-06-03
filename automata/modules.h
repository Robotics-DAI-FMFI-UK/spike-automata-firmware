#pragma once

#include <unistd.h>

#include <pbdrv/legodev.h>
#include <pbdrv/sound.h>
#include <pbdrv/button.h>

#include <pbio/geometry.h>
#include <pbio/light_matrix.h>
#include <pbio/imu.h>

#include "print.h"
#include "parameters.h"

/**
 * Clear matrix.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 */
void matrix_clear();

/**
 * Get matrix size.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in,out] parameters_1 is pointer to uint8_t *size.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 */
void matrix_get_size();

/**
 * Function will invert light of each point in matrix in selected rows.
 * Default is rows from up to down, but with changing orientation it will be columns from left to right.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 * <br><br> [in] parameters_4 is pointer to uint8_t *rows.
 */
void matrix_set_row();

/**
 * Set matrix orientation.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in,out] parameters_1 is pointer to pbio_geometry_side_t *up_side. up_side enum is in geometry.h.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 */
void matrix_orientation();

/**
 * Set matrix pixel.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 * <br><br> [in] parameters_4 is pointer to uint8_t *row.
 * <br><br> [in] parameters_5 is pointer to uint8_t *col.
 * <br><br> [in] parameters_6 is pointer to uint8_t *brightness.
 */
void matrix_set_pixel();

/**
 * Set matrix image.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 * <br><br> [in] parameters_4 is pointer to uint8_t *image.
 */
void matrix_set_image();

/**
 * Set matrix animation.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 * <br><br> [in] parameters_4 is pointer to uint8_t *cells. It is array x array of animated pixels.
 * <br><br> [in] parameters_5 is pointer to uint8_t *num_cells. It is number of cells.
 * <br><br> [in] parameters_6 is pointer to uint16_t *interval.
*/
void matrix_animation_start();

/**
 * Stop matrix animation.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to pbio_light_matrix_t *matrix.
 */
void matrix_animation_stop();

/**
 * Play sound.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in] parameters_3 is pointer to uint16_t *data. It is he PCM data of the sound to play. (PCM is method to translate sound from analog to digital representation.)
 * <br><br> [in] parameters_4 is pointer to uint32_t *length. It is number of samples.
 * <br><br> [in] parameters_5 is pointer to uint32_t *sample_rate. It is sample rate of @p data in HZ.
 */
void sound_play();

/**
 * Stop sound.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 */
void sound_stop();

/**
 * Get gyro axis.
 * <br><br> [out] parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in,out] parameters_1 is pointer to uint8_t *index. It is the index 0 (x), 1 (y), or 2 (z) of the axis.
 * <br><br> [in,out] parameters_2 is pointer to int8_t *sign. It is the sign of the axis: 1 or -1.
 * <br><br> [in] parameters_3 is pointer to pbio_geometry_side_t *side. It is requested side of the box. side enum is in geometry.h
 */void gyro_get_geometry_axis();

/**
 * Get gyro rotation.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in, out] parameters_1 is pointer to float *angle [deg].
 * <br><br> [in] parameters_3 is pointer to pbio_geometry_xyz_t *geo. X,y,z is linked with output
 */
void gyro_get_axis_rotation();

/**
 * Init of gyro.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 */
void gyro_init();

/**
 * Gyro is ready to use.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [out] parameters_1 is pointer to bool *ready.
 */
void gyro_is_ready();

/**
 *  LeftButton = 16, MiddleButton = 32,RightButton = 64,Bluetooth = 512
 * Button pressed.
 * <br><br> parameters_0 is pointer to pbio_error_t *error_code.
 * <br><br> [in,out] parameters_1 is pointer to pbio_button_flags_t *button_flag.
 */
void button_pressed();