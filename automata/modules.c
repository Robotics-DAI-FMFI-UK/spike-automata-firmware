#include "modules.h"

void matrix_clear() {
    pbio_error_t err =
            pbio_light_matrix_clear(
                    (pbio_light_matrix_t *) parameters[3]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err matrix_clear: ";
        print_error();
    }
}

void matrix_get_size() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    uint8_t result =
            pbio_light_matrix_get_size(
                    (pbio_light_matrix_t *) parameters[3]);
    *(uint8_t *) parameters[1] = result;
}

void matrix_set_row() {
    pbio_error_t err =
            pbio_light_matrix_set_rows(
                    (pbio_light_matrix_t *) parameters[3],
                    (const uint8_t *) parameters[4]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err matrix_set_row: ";
        print_error();
    }
}

void matrix_orientation() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_light_matrix_set_orientation(
            (pbio_light_matrix_t *) parameters[3],
            *((pbio_geometry_side_t *) parameters[4]));
}

void matrix_set_pixel() {
    pbio_error_t err =
            pbio_light_matrix_set_pixel(
                    (pbio_light_matrix_t *) parameters[3],
                    *((uint8_t *) parameters[4]),
                    *((uint8_t *) parameters[5]),
                    *((uint8_t *) parameters[6]));
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err matrix_set_pixel: ";
        print_error();
    }
}

void matrix_set_image() {
    pbio_error_t err =
            pbio_light_matrix_set_image(
                    (pbio_light_matrix_t *) parameters[3],
                    (uint8_t *) parameters[4]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err matrix_set_image: ";
        print_error();
    }
}

void matrix_animation_start() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_light_matrix_start_animation(
            (pbio_light_matrix_t *) parameters[3],
            (uint8_t *) parameters[4],
            *((uint8_t *) parameters[5]),
            *((uint16_t *) parameters[6]));
}

void matrix_animation_stop() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_light_matrix_stop_animation(
            (pbio_light_matrix_t *) parameters[3]);
}

void sound_play() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbdrv_sound_start(
            (uint16_t *) parameters[3],
            *((uint32_t *) parameters[4]),
            *((uint32_t *) parameters[5]));
}

void sound_stop() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbdrv_sound_stop();
}

void gyro_get_geometry_axis() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_geometry_side_get_axis(
            *((pbio_geometry_side_t *) parameters[3]),
            (uint8_t *) parameters[1],
            (int8_t *) parameters[2]);
}

void gyro_get_axis_rotation() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_imu_get_single_axis_rotation(
            (pbio_geometry_xyz_t *) parameters[3],
            (float *) parameters[1]);
}

void gyro_init() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    pbio_imu_init();
}

void gyro_is_ready() {
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
    bool ready = pbio_imu_is_ready();
    *(bool *) parameters[1] = ready;
}

void button_pressed() {
    pbio_error_t err =
            pbdrv_button_is_pressed(
                    (pbio_button_flags_t *) parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err button_pressed: ";
        print_error();
    }
}