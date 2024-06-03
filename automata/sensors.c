#include "sensors.h"

void get_distance_sensor() {
    pbdrv_legodev_type_id_t id_ultra = PBDRV_LEGODEV_TYPE_ID_SPIKE_ULTRASONIC_SENSOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_ultra,
                    (pbdrv_legodev_dev_t * *) & parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_distance_sensor: ";
        print_error();
    }
}

void get_low_distance_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__DISTL,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_low_distance_data: ";
        print_error();
    }
}

void get_high_distance_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__DISTS,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_high_distance_data: ";
        print_error();
    }
}

void get_single_distance_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__SINGL,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_single_distance_data: ";
        print_error();
    }
}

void get_force_sensor() {
    pbdrv_legodev_type_id_t id_force = PBDRV_LEGODEV_TYPE_ID_SPIKE_FORCE_SENSOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_force,
                    (pbdrv_legodev_dev_t **)(&parameters[1]));
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_force_sensor: ";
        print_error();
    }
}

void get_raw_force_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_FORCE_SENSOR__FRAW,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_raw_force_data: ";
        print_error();
    }
}

void get_color_sensor() {
    pbdrv_legodev_type_id_t id_color = PBDRV_LEGODEV_TYPE_ID_SPIKE_COLOR_SENSOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_color,
                    (pbdrv_legodev_dev_t * *) & parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_color_sensor: ";
        print_error();
    }
}

void get_color_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__COLOR,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_color_data: ";
        print_error();
    }
}

void get_reflection_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__REFLT,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_reflection_data: ";
        print_error();
    }
}

void get_ambient_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__AMBI,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_ambient_data: ";
        print_error();
    }
}

void get_rgb_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__RGB_I,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_rgb_data: ";
        print_error();
    }
}

void get_hsv_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__HSV,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_hsv_data: ";
        print_error();
    }
}

void get_scaled_hsv_data() {
    pbio_error_t err =
            pbdrv_legodev_get_data(
                    (pbdrv_legodev_dev_t *) parameters[3],
                    PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__SHSV,
                    &parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_scaled_hsv_data: ";
        print_error();
    }
}