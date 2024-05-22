#include <unistd.h>
#include <time.h>
#include <string.h>
#include <contiki.h>

#include <pbdrv/counter.h>
#include <pbdrv/legodev.h>
#include <pbdrv/sound.h>

#include <pbio/angle.h>
#include <pbio/int_math.h>
#include <pbio/observer.h>
#include <pbio/parent.h>
#include <pbio/servo.h>
#include <pbio/light_matrix.h>
#include <pbio/geometry.h>
#include <pbio/imu.h>

#include <pbsys/light.h>

#include "automata.h"

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

int start_automata(void) {
    static int initialized = 0;

//     importatnt with initialization
//    pbsys_hub_light_matrix; // exposed internal pointer
//    pbio_imu_init(); // void
//    pbio_imu_is_ready() // bool

//    static pbdrv_legodev_dev_t *legodev_ultra;
//    static pbdrv_legodev_dev_t *legodev_color;
//    static pbdrv_legodev_dev_t *legodev_force;
//    static pbio_servo_t *srv;
//    pbio_error_t err;

    if (!initialized) {
        initialized = 1;
    }
    do_events();

    uint32_t current_time = pbdrv_clock_get_ms();
    print_value("time: ", current_time);

    do_events();
    return 0;
}

//#include <glib.h>
//
//int main() {
//    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
//
//    g_hash_table_insert(hash, "key1", "value1");
//    g_hash_table_insert(hash, "key2", "value2");
//
//    char *value = g_hash_table_lookup(hash, "key1");
//    printf("Key1: %s\n", value);
//
//    g_hash_table_destroy(hash);
//    return 0;
//}
