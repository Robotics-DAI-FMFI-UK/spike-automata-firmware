#include <unistd.h>

#include <pbdrv/legodev.h>

#include "print.h"

/**
 * Getting instance of distance sensor.
 * @param port_id is hub port with plugged sensor.
 * @param [out] device is pointer, where the sensor will be initialize.
 */
pbio_error_t get_distance_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device);

/**
 * @param [out] data is pointer on 1x int16_t data.
 */
pbio_error_t get_low_distance_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 1x int16_t data.
 */
pbio_error_t get_high_distance_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 1x int16_t data.
 */
pbio_error_t get_single_distance_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * Getting instance of force sensor.
 * @param port_id is hub port with plugged sensor.
 * @param [out] device is pointer, where the sensor will be initialize.
 */
pbio_error_t get_force_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device);

/**
 * @param [out] data is pointer on 1x int16_t data.
 */
pbio_error_t get_raw_force_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * Getting instance of color sensor.
 * @param port_id is hub port with plugged sensor.
 * @param [out] device is pointer, where the sensor will be initialize.
 */
pbio_error_t get_color_sensor(pbio_port_id_t port_id, pbdrv_legodev_dev_t **device);

/**
 * color enum is in SPIKE Prime documentations
 * @param [out] data is pointer on 1x int8_t data.
 */
pbio_error_t get_color_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 1x int8_t data.
 */
pbio_error_t get_reflection_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 1x int8_t data.
 */
pbio_error_t get_ambient_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 4x int16_t data.
 */
pbio_error_t get_rgb_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 3x int16_t data.
 */
pbio_error_t get_hsv_data(pbdrv_legodev_dev_t *device, void **data);

/**
 * @param [out] data is pointer on 4x int16_t data.
 */
pbio_error_t get_scaled_hsv_data(pbdrv_legodev_dev_t *device, void **data);