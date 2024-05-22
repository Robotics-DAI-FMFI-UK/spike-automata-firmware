#include "sensors.h"

pbio_error_t get_distance_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device) {
    pbdrv_legodev_type_id_t id_ultra = PBDRV_LEGODEV_TYPE_ID_SPIKE_ULTRASONIC_SENSOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_ultra, device);
    if (PBIO_SUCCESS != err)
        print_value("Err get_distance_sensor: ", err);
    return err;
}

pbio_error_t get_low_distance_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__DISTL, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_low_distance_data: ", err);
    return err;
}

pbio_error_t get_high_distance_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__DISTS, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_high_distance_data: ", err);
    return err;
}

pbio_error_t get_single_distance_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__SINGL, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_single_distance_data: ", err);
    return err;
}

pbio_error_t get_force_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device) {
    pbdrv_legodev_type_id_t id_force = PBDRV_LEGODEV_TYPE_ID_SPIKE_FORCE_SENSOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_force, device);
    if (PBIO_SUCCESS != err)
        print_value("Err get_force_sensor: ", err);
    return err;
}

pbio_error_t get_raw_force_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_FORCE_SENSOR__FRAW, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_raw_force_data: ", err);
    return err;
}

pbio_error_t get_color_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device) {
    pbdrv_legodev_type_id_t id_color = PBDRV_LEGODEV_TYPE_ID_SPIKE_COLOR_SENSOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_color, device);
    if (PBIO_SUCCESS != err)
        print_value("Err get_color_sensor: ", err);
    return err;
}

pbio_error_t get_color_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__COLOR, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_color_data: ", err);
    return err;
}

pbio_error_t get_reflection_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__REFLT, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_reflection_data: ", err);
    return err;
}

pbio_error_t get_ambient_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__AMBI, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_ambient_data: ", err);
    return err;
}

pbio_error_t get_rgb_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__RGB_I, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_rgb_data: ", err);
    return err;
}

pbio_error_t get_hsv_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__HSV, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_hsv_data: ", err);
    return err;
}

pbio_error_t get_scaled_hsv_data(pbdrv_legodev_dev_t *device, void **data) {
    pbio_error_t err = pbdrv_legodev_get_data(device, PBDRV_LEGODEV_MODE_PUP_COLOR_SENSOR__SHSV, data);
    if (PBIO_SUCCESS != err)
        print_value("Err get_scaled_hsv_data: ", err);
    return err;
}