#include "motor.h"

void motor_large_setup() {
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_L_MOTOR;
    pbio_error_t err =
            pbio_servo_setup(
                    (pbio_servo_t *) parameters[3],
                    id_motor,
                    *(pbio_direction_t *) parameters[4],
                    1000,
                    true,
                    0);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_large_setup: ";
        print_error();
    }
}

void motor_medium_setup() {
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_M_MOTOR;
    pbio_error_t err =
            pbio_servo_setup(
                    (pbio_servo_t *) parameters[3],
                    id_motor,
                    *(pbio_direction_t *) parameters[4],
                    1000,
                    true,
                    0);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_medium_setup: ";
        print_error();
    }
}

void motor_small_setup() {
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_S_MOTOR;
    pbio_error_t err =
            pbio_servo_setup(
                    (pbio_servo_t *) parameters[3],
                    id_motor,
                    *(pbio_direction_t *) parameters[4],
                    1000,
                    true,
                    0);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_small_setup: ";
        print_error();
    }
}

void get_large_motor() {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_L_MOTOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_motor,
                    &lego_device);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_large_motor/device: ";
        print_error();
        return;
    }
    err =
            pbio_servo_get_servo(
                    lego_device,
                    (pbio_servo_t * *) & parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_large_motor/servo: ";
        print_error();
    }
}

void get_medium_motor() {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_M_MOTOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_motor,
                    &lego_device);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_medium_motor/device: ";
        print_error();
        return;
    }
    err =
            pbio_servo_get_servo(
                    lego_device,
                    (pbio_servo_t * *) & parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_medium_motor/servo: ";
        print_error();
    }
}

void get_small_motor() {
    pbdrv_legodev_dev_t *lego_device;
    pbdrv_legodev_type_id_t id_motor = PBDRV_LEGODEV_TYPE_ID_SPIKE_S_MOTOR;
    pbio_error_t err =
            pbdrv_legodev_get_device(
                    *((pbio_port_id_t *) parameters[3]),
                    &id_motor,
                    &lego_device);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_small_motor/device: ";
        print_error();
        return;
    }
    err =
            pbio_servo_get_servo(
                    lego_device,
                    (pbio_servo_t * *) & parameters[1]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_small_motor/servo: ";
        print_error();
    }
}

void motor_get_status() {
    pbio_error_t err =
            pbio_servo_get_state_user(
                    (pbio_servo_t *) parameters[3],
                    (int32_t *) parameters[1],
                    (int32_t *) parameters[2]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_get_status: ";
        print_error();
    }
}

void motor_run_time() {
    pbio_error_t err =
            pbio_servo_run_time(
                    (pbio_servo_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_run_time: ";
        print_error();
    }
}

void motor_run_forever() {
    pbio_error_t err =
            pbio_servo_run_forever(
                    (pbio_servo_t *) parameters[3],
                    *((int32_t *) parameters[4]));
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_run_forever: ";
        print_error();
    }
}

void motor_run_angle() {
    pbio_error_t err =
            pbio_servo_run_angle(
                    (pbio_servo_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_run_angle: ";
        print_error();
    }
}

void motor_stop() {
    pbio_error_t err =
            pbio_servo_stop(
                    (pbio_servo_t *) parameters[3],
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err motor_stop: ";
        print_error();
    }
}

void get_base() {
    pbio_error_t err =
            pbio_drivebase_get_drivebase_spike(
                    (pbio_drivebase_t * *) & parameters[1],
                    (pbio_servo_t *) parameters[3],
                    (pbio_servo_t *) parameters[4]);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err get_base: ";
        print_error();
    }
}

void base_is_done() {
    bool done =
            pbio_drivebase_is_done(
                    (pbio_drivebase_t *) parameters[3]);
    *(bool *) parameters[1] = done;
    *(pbio_error_t *) parameters[0] = PBIO_SUCCESS;
}

void base_run_forever() {
    pbio_error_t err =
            pbio_drivebase_drive_forever(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]));
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_forever: ";
        print_error();
    }
}

void base_stop() {
    pbio_error_t err =
            pbio_drivebase_stop(
                    (pbio_drivebase_t *) parameters[3],
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_stop: ";
        print_error();
    }
}

void base_run_distance() {
    pbio_error_t err =
            pbio_drivebase_drive_straight(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_distance: ";
        print_error();
    }
}

void base_run_angle() {
    pbio_error_t err =
            pbio_drivebase_drive_curve(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_angle: ";
        print_error();
    }
}

void base_run_forever_different() {
    pbio_error_t err =
            pbio_drivebase_spike_drive_forever(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5])); //is light because of Define
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_forever_different: ";
        print_error();
    }
}

void base_run_time_different() {
    pbio_error_t err =
            pbio_drivebase_spike_drive_time(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]),
                    *((int32_t *) parameters[6]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE);  //is light because of Define
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_time_different: ";
        print_error();
    }
}

void base_run_angle_different() {
    pbio_error_t err =
            pbio_drivebase_spike_drive_angle(
                    (pbio_drivebase_t *) parameters[3],
                    *((int32_t *) parameters[4]),
                    *((int32_t *) parameters[5]),
                    *((int32_t *) parameters[6]),
                    PBIO_CONTROL_ON_COMPLETION_BRAKE); //is light because of Define
    *(pbio_error_t *) parameters[0] = err;
    if (PBIO_SUCCESS != err) {
        parameters[10] = "Err base_run_angle_different: ";
        print_error();
    }
}