#include <unistd.h>
#pragma once

#include <pbdrv/legodev.h>
#include <pbdrv/sound.h>
#include <pbdrv/button.h>

#include <pbio/geometry.h>
#include <pbio/light_matrix.h>
#include <pbio/imu.h>

#include "print.h"
#include "parameters.h"

pbio_error_t matrix_clear(pbio_light_matrix_t *light_matrix);

uint8_t matrix_get_size(pbio_light_matrix_t *light_matrix);

/**
 * Function will invert light of each point in matrix in selected rows.
 * Default is rows from up to down, but with changing orientation it will be columns from left to right.
 * @param rows is array of size bytes. Each byte is one row.
 */
pbio_error_t matrix_set_row(pbio_light_matrix_t *light_matrix, const uint8_t *rows);

/**
 * up_side enum is in geometry.h
 */
void matrix_orientation(pbio_light_matrix_t * light_matrix, pbio_geometry_side_t up_side);

pbio_error_t matrix_set_pixel(pbio_light_matrix_t *light_matrix, uint8_t row, uint8_t col, uint8_t brightness);

pbio_error_t matrix_set_image(pbio_light_matrix_t *light_matrix, const uint8_t *image);

/**
 * @param cells is array x array of animated pixels.
 * @param num_cells is number of cells.
 */
void matrix_animation_start(pbio_light_matrix_t *light_matrix, const uint8_t *cells, uint8_t num_cells, uint16_t interval);

void matrix_animation_stop(pbio_light_matrix_t *light_matrix);

/**
 * @param data the PCM data of the sound to play. (PCM is method to translate sound from analog to digital representation.)
 * @param length number of samples.
 * @param sample_rate is sample rate of @p data in HZ.
 */
void sound_play(const uint16_t *data, uint32_t length, uint32_t sample_rate);

void sound_stop(void);

/**
 * side enum is in geometry.h
 * @param side is requested side of the box.
 * @param [out] index is the index 0 (x), 1 (y), or 2 (z) of the axis.
 * @param [out] sign is the sign of the axis: 1 or -1.
 */
void gyro_get_geometry_axis(pbio_geometry_side_t side, uint8_t *index, int8_t *sign);

/**
 * @param geo x,y,z is linked with output
 * @param [out] input is pointer on float
 */
void gyro_get_axis_rotation(pbio_geometry_xyz_t *geo, float *input);

void gyro_init(void);

bool gyro_is_ready(void);

pbio_error_t button_pressed(pbio_button_flags_t *pressed);