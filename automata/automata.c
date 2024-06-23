#include "automata.h"
#include "serial_reader.h"
#include "fsa_parse.h"

//  predefine:
uint32_t pbdrv_clock_get_ms(void);

void pb_color_map_rgb_to_hsv(const pbio_color_rgb_t *rgb, pbio_color_hsv_t *hsv);

// implemented:
void do_events(void) {
    int count = process_run();
    while (count > 0) {
        count = process_run();
    }
}

void delay(int milliseconds) {
    uint32_t arrived_at = pbdrv_clock_get_ms();
    while (arrived_at + milliseconds > pbdrv_clock_get_ms()) {
        do_events();
    }
}

bool end() {
    if (pbsys_status_test(PBIO_PYBRICKS_STATUS_POWER_BUTTON_PRESSED)
        || pbsys_status_test(PBIO_PYBRICKS_STATUS_SHUTDOWN_REQUEST)
        || *(pbio_error_t *) parameters[0] != PBIO_SUCCESS)
        return true;
    return false;
}

// used in code
//    pbsys_hub_light_matrix; // pointer to matrix

int debug_mode = 0;

uint8_t received[100000];
uint32_t recvptr = 0;

void echo_lines(){
    uint32_t started_waiting = 0;
    uint8_t waiting = 0;
    recvptr = 0;

    do {
        do_events();
        uint8_t data[10];
        uint32_t size = 10;
        pbio_error_t err = pbsys_bluetooth_rx(data, &size);
        if (err == PBIO_ERROR_AGAIN)
        {
            if (!waiting)
            {
                started_waiting = pbdrv_clock_get_ms();
                waiting = 1;
            }
            else
            {
                if (pbdrv_clock_get_ms() - started_waiting > 500) break;
            }
        }
        else
        {
            uint8_t copydata[20];
            uint32_t j = 0;
            for (uint32_t i = 0; i < size; i++)
            {
                if (data[i] == '\r') copydata[j++] = '\n';
                copydata[j++] = data[i];
            }
            waiting = 0;
            memcpy(received + recvptr, copydata, j);
            recvptr += j;
            if (recvptr > 100000) recvptr = 0;
        }
    } while (1);
    uint32_t size = 21;

    uint32_t i = 0;
    for ( ; i < recvptr / 10; i++) {
        size = 10;
        pbsys_bluetooth_tx(received + i * 10, &size);
        delay(100);
    }

    size = recvptr - i * 10;
    pbsys_bluetooth_tx(received + i * 10, &size);
    delay(10);

    size = 7;
    pbsys_bluetooth_tx((const uint8_t *)"\r\nEOT\r\n", &size);
}

int start_automata(void) {
    pbio_error_t err = PBIO_SUCCESS;
    parameters[0] = &err;
    do_events();

    while (!end()) {
        delay(200);
        uint8_t data[10];
        uint32_t size = 10;
        pbsys_bluetooth_rx(data, &size);
        if (size > 0) {
            if (size < 16) {
                char message[size + 1];
                strcpy(message, (char *) data);
                message[1] = '\0';
                parameters[10] = message;
                print_message();
                switch (message[0]) {
                    case '0':
                        parameters[10] = "Starting follow automata...";
                        print_message();
                        follow();
                        break;
                    case '1':
                        parameters[10] = "Starting discover automata...";
                        print_message();
                        discover();
                        break;
                    case '2':
                        parameters[10] = "Starting tilt automata...";
                        print_message();
                        tilt();
                        break;
                    case '7':
                        //echo_lines();
                        fsa_parse();
                        break;
                    case 'd':
                        if (debug_mode == 0) {
                            parameters[10] = "Debug mode on.";
                            debug_mode++;
                        } else if (debug_mode == 1) {
                            parameters[10] = "Debug mode off.";
                            debug_mode--;
                        }
                        print_message();
                        break;
//                case 'm':
//                    memory_test();
//                    break;
                    default:
                        parameters[10] = "Unspecified code...";
                        print_message();
                }
            }
//            else {
//                parse_automata(data, size);
//            }
        }
    }

    return 0;
}

//void parse_automata(uint8_t message, uint32_t length) {
//    uint8_t automata_text[2000] = message;
//    uint32_t position = length;
//    while (true) {
//        uint8_t data[200];
//        uint32_t size = 200;
//        pbsys_bluetooth_rx(data, &size);
//        if (size == 0)
//            break;
//        if (position += size > 2000){
//            parameters[10] = "Too big automata!";
//            print_message();
//            return;
//        }
//        automata_text[length] = data;
//        position += size;
//    }
//    return;
//}

/**
 * states:<br>
 * 0 => middle<br>
 * 1 => right<br>
 * -1 => left<br>
 * 2 => up<br>
 * -2 => down
 */
void tilt() {
    /**
     * 0 => middle<br>
     * 1 => right<br>
     * -1 => left<br>
     * 2 => up<br>
     * -2 => down
     */
    int state = 0;
    int32_t x = 2;
    int32_t y = 2;
    int32_t bright = 100;
    uint32_t last_print = 0;
    parameters[3] = pbsys_hub_light_matrix;
    matrix_clear();
    if (end()) {
        parameters[10] = "Exit tilt because matrix_clear: ";
        print_error();
        return;
    }
    do_events();

    parameters[4] = &x;
    parameters[5] = &y;
    parameters[6] = &bright;
    matrix_set_pixel();
    if (end()) {
        parameters[10] = "Exit tilt because matrix_set_pixel: ";
        print_error();
        return;
    }
    do_events();

    gyro_init();
    if (end()) {
        parameters[10] = "Exit tilt because gyro_init: ";
        print_error();
        return;
    }
    bool ready = false;
    parameters[1] = &ready;
    gyro_is_ready();
    if (!ready || end()) {
        parameters[10] = "Exit tilt because gyro_init: ";
        print_error();
        return;
    }

    while (!end()) {
        do_events();

        float angle_x = 0.0;
        pbio_geometry_xyz_t geo;
        geo.x = 1;
        geo.y = 0;
        geo.z = 0;
        parameters[1] = &angle_x;
        parameters[3] = &geo;
        gyro_get_axis_rotation();
        angle_x = *(float *) parameters[1];
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;

        float angle_y = 0.0;
        geo.x = 0;
        geo.y = 1;
        geo.z = 0;
        parameters[1] = &angle_y;
        gyro_get_axis_rotation();
        angle_y = *(float *) parameters[1];
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;

        float angle_z = 0.0;
        geo.x = 0;
        geo.y = 0;
        geo.z = 1;
        parameters[1] = &angle_z;
        gyro_get_axis_rotation();
        angle_z = *(float *) parameters[1];
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;

        if (debug_mode == 1 && pbdrv_clock_get_ms() - last_print > 200) {
            parameters[10] = "Angle X: ";
            parameters[11] = &angle_x;
            print_float();
            parameters[10] = "Angle Y: ";
            parameters[11] = &angle_y;
            print_float();
            parameters[10] = "Angle Z: ";
            parameters[11] = &angle_z;
            print_float();
            parameters[10] = "State: ";
            parameters[11] = &state;
            print_value();
            last_print = pbdrv_clock_get_ms();
        }

        parameters[3] = pbsys_hub_light_matrix;
        parameters[4] = &x;
        parameters[5] = &y;
        parameters[6] = &bright;

        if (state == 0) {
            if (angle_y >= 35.0) {
                state = 1;
                matrix_clear();
                x = 0;
                matrix_set_pixel();
            } else if (angle_y <= -35.0) {
                state = -1;
                matrix_clear();
                x = 4;
                matrix_set_pixel();
            } else if (angle_x >= 35.0) {
                state = 2;
                matrix_clear();
                y = 4;
                matrix_set_pixel();
            } else if (angle_x <= -35.0) {
                state = -2;
                matrix_clear();
                y = 0;
                matrix_set_pixel();
            }
        } else {
            if (angle_x > -25.0 && angle_x < 25.0 &&
                angle_y > -25.0 && angle_y < 25.0)
                state = 0;
        }

        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;
    }

    parameters[10] = "Ending tilt automata with exit code ";
    print_error();
    parameters[3] = pbsys_hub_light_matrix;
    matrix_clear();
}

void discover() {
    pbdrv_legodev_dev_t *legodev_ultra;
    pbdrv_legodev_dev_t *legodev_color;
    pbio_servo_t *srv1;
    pbio_servo_t *srv2;
    pbio_drivebase_t *base;
    pbio_port_id_t port;
    pbio_direction_t direction;

    port = PBIO_PORT_ID_B;
    parameters[3] = &port;
    get_medium_motor();
    srv1 = parameters[1];
    if (end()) {
        parameters[10] = "Exit discover because srv1: ";
        print_error();
        return;
    }
    do_events();

    port = PBIO_PORT_ID_D;
    parameters[3] = &port;
    get_medium_motor();
    srv2 = parameters[1];
    if (end()) {
        parameters[10] = "Exit discover because srv2: ";
        print_error();
        return;
    }
    do_events();

    direction = PBIO_DIRECTION_CLOCKWISE;
    parameters[3] = srv1;
    parameters[4] = &direction;
    motor_medium_setup();
    if (end()) {
        parameters[10] = "Exit discover because setup srv1: ";
        print_error();
        return;
    }
    do_events();

    direction = PBIO_DIRECTION_COUNTERCLOCKWISE;
    parameters[3] = srv2;
    parameters[4] = &direction;
    motor_medium_setup();
    if (end()) {
        parameters[10] = "Exit discover because setup srv2: ";
        print_error();
        return;
    }
    do_events();

    parameters[4] = srv1;
    parameters[5] = srv2;
    get_base();
    base = parameters[1];
    if (end()) {
        parameters[10] = "Exit discover because base: ";
        print_error();
    }
    do_events();

    port = PBIO_PORT_ID_C;
    parameters[3] = &port;
    parameters[1] = legodev_ultra;
    get_distance_sensor();
    legodev_ultra = parameters[1];
    if (end()) {
        parameters[10] = "Exit discover because legodev_ultra: ";
        print_error();
        return;
    }
    do_events();

    port = PBIO_PORT_ID_F;
    parameters[3] = &port;
    parameters[1] = legodev_color;
    get_color_sensor();
    legodev_color = parameters[1];
    if (end()) {
        parameters[10] = "Exit discover because legodev_color: ";
        print_error();
        return;
    }
    do_events();

    /**
     * 1 = run<br>
     * 2 = stop<br>
     * 3 = start_turn<br>
     * 4 = end_turn<br>
     */
    int state = 4;
    int32_t radius = 0;
    int32_t speed = -200;
    int32_t angle = 0;
    uint32_t last_print = 0;

    while (!end()) {
        do_events();

        parameters[3] = legodev_ultra;
        get_low_distance_data();
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;
        int distance = *(int16_t *) parameters[1];
        if (distance < 0) distance = 2000;

        parameters[3] = legodev_color;
        get_color_data();
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;
        int color = *(int8_t *) parameters[1];

        if (debug_mode == 1 && pbdrv_clock_get_ms() - last_print > 200) {
            parameters[10] = "Distance: ";
            parameters[11] = &distance;
            print_value();
            parameters[10] = "Color: ";
            parameters[11] = &color;
            print_value();
            parameters[10] = "State: ";
            parameters[11] = &state;
            print_value();
            last_print = pbdrv_clock_get_ms();
        }

        parameters[3] = base;

        if (state == 1) {
            if (distance < 140) {
                base_stop();
                state = 2;
            }
        } else if (state == 2) {
            if (color == -1) continue;
            parameters[4] = &radius;
            if (color == 0) angle = 300; //black
            if (color == 10) angle = 150; //white
            if (color == 7) angle = -150; //yellow
            if (color == 3) angle = -300; //blue
            if (color == 5) angle = -450; //turquoise
            if (color == 9) angle = 450; //red
            parameters[5] = &angle;
            base_run_angle();
            state = 3;
        } else if (state == 3) {
            bool done = false;
            parameters[1] = &done;
            base_is_done();
            if (done) {
                state = 4;
            }
        } else if (state == 4) {
            if (distance > 150) {
                angle = 0;
                parameters[4] = &speed;
                parameters[5] = &angle;
                base_run_forever();
                state = 1;
            } else {
                state = 2;
            }
        }

        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;

    }
    parameters[10] = "Ending discover automata with exit code ";
    print_error();
    parameters[3] = base;
    base_stop();
}

/**
 * states:<br>
 * -1 => back<br>
 * 0 => stop<br>
 * 1 => forward
 */
void follow() {
    pbdrv_legodev_dev_t *legodev_ultra;
    pbio_servo_t *srv1;
    pbio_servo_t *srv2;
    pbio_drivebase_t *base;
    pbio_port_id_t port;
    pbio_direction_t direction;

    port = PBIO_PORT_ID_B;
    parameters[3] = &port;
    get_medium_motor();
    srv1 = parameters[1];
    if (end()) {
        parameters[10] = "Exit follow because srv1: ";
        print_error();
        return;
    }
    do_events();

    port = PBIO_PORT_ID_D;
    parameters[3] = &port;
    get_medium_motor();
    srv2 = parameters[1];
    if (end()) {
        parameters[10] = "Exit follow because srv2: ";
        print_error();
        return;
    }
    do_events();

    direction = PBIO_DIRECTION_CLOCKWISE;
    parameters[3] = srv1;
    parameters[4] = &direction;
    motor_medium_setup();
    if (end()) {
        parameters[10] = "Exit follow because setup srv1: ";
        print_error();
        return;
    }
    do_events();

    direction = PBIO_DIRECTION_COUNTERCLOCKWISE;
    parameters[3] = srv2;
    parameters[4] = &direction;
    motor_medium_setup();
    if (end()) {
        parameters[10] = "Exit follow because setup srv2: ";
        print_error();
        return;
    }
    do_events();

    parameters[4] = srv1;
    parameters[5] = srv2;
    get_base();
    base = parameters[1];
    if (end()) {
        parameters[10] = "Exit follow because base: ";
        print_error();
    }
    do_events();

    port = PBIO_PORT_ID_C;
    parameters[3] = &port;
    parameters[1] = legodev_ultra;
    get_distance_sensor();
    legodev_ultra = parameters[1];
    if (end()) {
        parameters[10] = "Exit follow because legodev_ultra: ";
        print_error();
        return;
    }
    do_events();

    /**
     * -1 => back<br>
     * 0 => stop<br>
     * 1 => forward
     */
    int state = 0;
    int32_t speed = 250;
    int32_t angle = 0;
    uint32_t last_print = 0;

    while (!end()) {
        do_events();

        parameters[3] = legodev_ultra;
        get_low_distance_data();
        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;
        int distance = *(int16_t *) parameters[1];
        if (distance < 0) distance = 2000;

        if (debug_mode == 1 && pbdrv_clock_get_ms() - last_print > 200) {
            parameters[10] = "Distance: ";
            parameters[11] = &distance;
            print_value();
            parameters[10] = "State: ";
            parameters[11] = &state;
            print_value();
            last_print = pbdrv_clock_get_ms();
        }

        parameters[3] = base;
        parameters[4] = &speed;
        parameters[5] = &angle;

        if (state == -1) {
            if (distance > 150) {
                base_stop();
                state = 0;
            }
        } else if (state == 1) {
            if (distance < 300) {
                base_stop();
                state = 0;
            }
        } else if (state == 0) {
            if (distance < 140) {
                if (speed < 0) speed *= -1;
                base_run_forever();
                state = -1;
            } else if (distance > 310) {
                if (speed > 0) speed *= -1;
                base_run_forever();
                state = 1;
            }
        }

        if (*(pbio_error_t *) parameters[0] != PBIO_SUCCESS) break;
    }

    parameters[10] = "Ending follow automata with exit code ";
    print_error();
    parameters[3] = base;
    base_stop();
}

//JSON parser: https://zserge.com/jsmn/

//pointer to function example:
//    #include <stdio.h>
//
//    void f1() {
//        printf("this is f1\n");
//    }
//
//    void f2() {
//        printf("and this is f2\n");
//    }
//
//    void (*fun_ptr[2])();
//
//    int main() {
//        fun_ptr[0] = f1;
//        fun_ptr[1] = f2;
//
//        void (*fn)() = fun_ptr[0];
//        fn();
//        fn = fun_ptr[1];
//        fn();
//
//        fun_ptr[0]();
//        fun_ptr[1]();
//
//    // f1, f2, f1, f2
//    }

//dynamic allocation memory:
//    MEMB(bee, char, 10);
//
//    char *ch = memb_alloc(&bee);
//    if (ch != NULL) {
//        strcpy(ch, "bee");
//        memb_free(&bee, ch);
//    }
//    else
//        ch = "flee";

//dynamic structure (lists, linked lists, dictionary,..): https://sourceware.org/glibc/wiki/HomePage
//    #include <glib.h>
//
//    int main() {
//        GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
//
//        g_hash_table_insert(hash, "key1", "value1");
//        g_hash_table_insert(hash, "key2", "value2");
//
//        char *value = g_hash_table_lookup(hash, "key1");
//        printf("Key1: %s\n", value);
//
//        g_hash_table_destroy(hash);
//        return 0;
//    }
