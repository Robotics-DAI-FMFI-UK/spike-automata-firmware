#include "motor.h"

pbio_error_t get_large_motor(pbio_port_id_t port_id, pbio_servo_t **device) {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_L_MOTOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_motor, &lego_device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get lego device: ", err);
        return err;
    }
    err = pbio_servo_get_servo(lego_device, device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get servo: ", err);
        return err;
    }
    err = pbio_servo_setup(*device, id_motor, PBIO_DIRECTION_CLOCKWISE, 1000, true, 0);
    if (PBIO_SUCCESS != err) {
        print_value("Err servo setup: ", err);
    }
    return err;
}

pbio_error_t get_medium_motor(pbio_port_id_t port_id, pbio_servo_t **device) {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_M_MOTOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_motor, &lego_device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get lego device: ", err);
        return err;
    }
    err = pbio_servo_get_servo(lego_device, device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get servo: ", err);
        return err;
    }
    err = pbio_servo_setup(*device, id_motor, PBIO_DIRECTION_CLOCKWISE, 1000, true, 0);
    if (PBIO_SUCCESS != err) {
        print_value("Err servo setup: ", err);
    }
    return err;
}

pbio_error_t get_small_motor(pbio_port_id_t port_id, pbio_servo_t **device) {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_S_MOTOR;
    pbio_error_t err = pbdrv_legodev_get_device(port_id, &id_motor, &lego_device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get lego device: ", err);
        return err;
    }
    err = pbio_servo_get_servo(lego_device, device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get servo: ", err);
        return err;
    }
    err = pbio_servo_setup(*device, id_motor, PBIO_DIRECTION_CLOCKWISE, 1000, true, 0);
    if (PBIO_SUCCESS != err) {
        print_value("Err servo setup: ", err);
    }
    return err;
}

pbio_error_t get_motor2() {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_M_MOTOR;
    pbio_error_t err = pbdrv_legodev_get_device(*((pbio_port_id_t *) parameters[1]), &id_motor, &lego_device);
    if (PBIO_SUCCESS != err) {
        print_value("Err get lego device: ", err);
        return err;
    }
    err = pbio_servo_get_servo(lego_device, (pbio_servo_t **) &parameters[0]);
    if (PBIO_SUCCESS != err) {
        print_value("Err get servo: ", err);
        return err;
    }
    err = pbio_servo_setup((pbio_servo_t *) parameters[0], id_motor, PBIO_DIRECTION_CLOCKWISE, 1000, true, 0);
    if (PBIO_SUCCESS != err) {
        print_value("Err servo setup: ", err);
    }
    return err;
}

pbio_error_t motor_get_status(pbio_servo_t *device, int32_t *angle, int32_t *speed) {
    pbio_error_t err = pbio_servo_get_state_user(device, angle, speed);
    if (PBIO_SUCCESS != err) {
        print_value("Err motor_get_status: ", err);
    }
    return err;
}

pbio_error_t motor_run_time(pbio_servo_t *device, int32_t speed, int32_t milliseconds) {
    pbio_error_t err = pbio_servo_run_time(device, speed, milliseconds, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err motor_run_time: ", err);
    return err;
}

pbio_error_t motor_run_forever(pbio_servo_t *device, int32_t speed) {
    pbio_error_t err = pbio_servo_run_forever(device, speed);
    if (PBIO_SUCCESS != err)
        print_value("Err motor_run_forever: ", err);
    return err;
}

pbio_error_t motor_stop(pbio_servo_t *device) {
    pbio_error_t err = pbio_servo_stop(device, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err motor_stop: ", err);
    return err;
}

pbio_error_t motor_run_angle(pbio_servo_t *device, int32_t speed, int32_t angle) {
    pbio_error_t err = pbio_servo_run_angle(device, speed, angle, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err motor_run_angle: ", err);
    return err;
}

pbio_error_t get_base(pbio_drivebase_t **base, pbio_servo_t *left, pbio_servo_t *right) {
    pbio_error_t err = pbio_drivebase_get_drivebase_spike(base, left, right); //is light because of Define
    if (PBIO_SUCCESS != err)
        print_value("Err get_base: ", err);
    return err;
}

bool base_is_done(pbio_drivebase_t *base) {
    return pbio_drivebase_is_done(base);
}

pbio_error_t base_run_forever(pbio_drivebase_t *base, int32_t speed, int32_t angle) {
    pbio_error_t err = pbio_drivebase_drive_forever(base, speed, angle);
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_forever: ", err);
    return err;
}

pbio_error_t base_stop(pbio_drivebase_t *base) {
    pbio_error_t err = pbio_drivebase_stop(base, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err base_stop: ", err);
    return err;
}

pbio_error_t base_run_distance(pbio_drivebase_t *base, int32_t distance) {
    pbio_error_t err = pbio_drivebase_drive_straight(base, distance, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_distance: ", err);
    return err;
}

pbio_error_t base_run_angle(pbio_drivebase_t *base, int32_t radius, int32_t angle) {
    pbio_error_t err = pbio_drivebase_drive_curve(base, radius, angle, PBIO_CONTROL_ON_COMPLETION_BRAKE);
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_angle: ", err);
    return err;
}

pbio_error_t base_run_forever_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed) {
    pbio_error_t err = pbio_drivebase_spike_drive_forever(base, left_speed, right_speed); //is light because of Define
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_forever_different: ", err);
    return err;
}

pbio_error_t
base_run_time_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed, int32_t duration) {
    pbio_error_t err = pbio_drivebase_spike_drive_time(base, left_speed, right_speed, duration,
                                                       PBIO_CONTROL_ON_COMPLETION_BRAKE);  //is light because of Define
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_time_different: ", err);
    return err;
}

pbio_error_t base_run_angle_different(pbio_drivebase_t *base, int32_t left_speed, int32_t right_speed, int32_t angle) {
    pbio_error_t err = pbio_drivebase_spike_drive_angle(base, left_speed, right_speed, angle,
                                                        PBIO_CONTROL_ON_COMPLETION_BRAKE); //is light because of Define
    if (PBIO_SUCCESS != err)
        print_value("Err base_run_angle_different: ", err);
    return err;
}