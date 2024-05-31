#include "modules.h"

pbio_error_t matrix_clear(pbio_light_matrix_t *light_matrix) {
    pbio_error_t err = pbio_light_matrix_clear(light_matrix);
    if (err != PBIO_SUCCESS)
        print_value("Err matrix_clear: ", err);
    return err;
}

uint8_t matrix_get_size(pbio_light_matrix_t *light_matrix) {
    return pbio_light_matrix_get_size(light_matrix);
}

pbio_error_t matrix_set_row(pbio_light_matrix_t *light_matrix, const uint8_t *rows) {
    pbio_error_t err = pbio_light_matrix_set_rows(light_matrix, rows);
    if (err != PBIO_SUCCESS)
        print_value("Err matrix_set_row: ", err);
    return err;
}

void matrix_orientation(pbio_light_matrix_t *light_matrix, pbio_geometry_side_t up_side) {
    pbio_light_matrix_set_orientation(light_matrix, up_side);
}

pbio_error_t matrix_set_pixel(pbio_light_matrix_t *light_matrix, uint8_t row, uint8_t col, uint8_t brightness) {
    pbio_error_t err = pbio_light_matrix_set_pixel(light_matrix, row, col, brightness);
    if (err != PBIO_SUCCESS)
        print_value("Err matrix_set_pixel: ", err);
    return err;
}

pbio_error_t matrix_set_image(pbio_light_matrix_t *light_matrix, const uint8_t *image) {
    pbio_error_t err = pbio_light_matrix_set_image(light_matrix, image);
    if (err != PBIO_SUCCESS)
        print_value("Err matrix_set_image: ", err);
    return err;
}

void
matrix_animation_start(pbio_light_matrix_t *light_matrix, const uint8_t *cells, uint8_t num_cells, uint16_t interval) {
    pbio_light_matrix_start_animation(light_matrix, cells, num_cells, interval);
}

void matrix_animation_stop(pbio_light_matrix_t *light_matrix) {
    pbio_light_matrix_stop_animation(light_matrix);
}

void sound_play(const uint16_t *data, uint32_t length, uint32_t sample_rate) {
    pbdrv_sound_start(data, length, sample_rate);
}

void sound_stop(void) {
    pbdrv_sound_stop();
}

void gyro_get_geometry_axis(pbio_geometry_side_t side, uint8_t *index, int8_t *sign) {
    pbio_geometry_side_get_axis(side, index, sign);
}

void gyro_get_axis_rotation(pbio_geometry_xyz_t *geo, float *input) {
    pbio_imu_get_single_axis_rotation(geo, input);
}

void gyro_init(void) {
    pbio_imu_init();
}

bool gyro_is_ready(void) {
    return pbio_imu_is_ready();
}

pbio_error_t button_pressed(pbio_button_flags_t *pressed){ //L16,M32,R64,Bluetooth512
    pbio_error_t err = pbdrv_button_is_pressed(pressed);
    if (err != PBIO_SUCCESS)
        print_value("Err button_pressed: ", err);
    return err;
}