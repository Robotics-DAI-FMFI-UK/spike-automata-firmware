//#include <automata/hub/buildInDrivers.c>
//#include <automata/motor/motor.c>
#include <unistd.h>
//#include <lib/pbio/drv/legodev/legodev_nxt.c>
#include <pbdrv/counter.h>
#include <pbdrv/legodev.h>
#include <pbdrv/bluetooth.h>

#include <pbio/angle.h>
#include <pbio/int_math.h>
#include <pbio/observer.h>
#include <pbio/parent.h>
#include <pbio/servo.h>
#include <pbio/light_matrix.h>

#include <pbsys/light.h>
#include <pbsys/bluetooth.h>

#include "contiki.h"

#include <unistd.h>
#include <time.h>
#include "string.h"

/*
pbsys_hub_light_matrix

uint8_t pbio_light_matrix_get_size(pbio_light_matrix_t *light_matrix);
void pbio_light_matrix_set_orientation(pbio_light_matrix_t *light_matrix, pbio_geometry_side_t up_side);
pbio_error_t pbio_light_matrix_clear(pbio_light_matrix_t *light_matrix);
pbio_error_t pbio_light_matrix_set_rows(pbio_light_matrix_t *light_matrix, const uint8_t *rows);
pbio_error_t pbio_light_matrix_set_pixel(pbio_light_matrix_t *light_matrix, uint8_t row, uint8_t col, uint8_t brightness);
pbio_error_t pbio_light_matrix_set_image(pbio_light_matrix_t *light_matrix, const uint8_t *image);
void pbio_light_matrix_start_animation(pbio_light_matrix_t *light_matrix, const uint8_t *cells, uint8_t num_cells, uint16_t interval);
void pbio_light_matrix_stop_animation(pbio_light_matrix_t *light_matrix);
*/

uint32_t pbdrv_clock_get_ms(void);

void delay(int msec)
{
    uint32_t arrived_at = pbdrv_clock_get_ms();
    uint32_t last_events_done = arrived_at;
    while (arrived_at + msec > pbdrv_clock_get_ms())
    {
          process_run();
	  last_events_done++;
	/* if (pbdrv_clock_get_ms() - last_events_done > 2)
	{
	  last_events_done = pbdrv_clock_get_ms();
	} */
    }

}

void logmsgnl(const char *msg)
{
    char *newline = "\r\n";
    uint32_t size = strlen(msg);
    pbsys_bluetooth_tx((unsigned char *)msg, &size);
    size = 2;
    pbsys_bluetooth_tx((unsigned char *)newline, &size);
}

void logmsg(const char *msg)
{
    uint32_t size = strlen(msg);
    pbsys_bluetooth_tx((unsigned char *)msg, &size);
}

void int2str(long a, char *s)
{
  long b = a;
  int cifier = 1;
  long k = 1;

  while (b /= 10) { cifier++; k *= 10; }

  if (a < 0) { *(s++) = '-'; a = -a; }
  while (k > 0)
  {
    *(s++) = '0' + a / k;
    a = a % k;
    k /= 10;
  }
  *s = 0;
}


void logmsgvalnl(const char *msg, int value)
{
    char *newline = "\r\n";
    uint32_t size = strlen(msg);
    pbsys_bluetooth_tx((unsigned char *)msg, &size);

    char str[23];
    int2str(value, str);

    size = strlen(str);
    pbsys_bluetooth_tx((unsigned char *)str, &size);

    size = 2;
    pbsys_bluetooth_tx((unsigned char *)newline, &size);
}


int start_automata()
{
    static int initialized = 0;
    static pbdrv_legodev_dev_t *legodev_motor;
    static pbdrv_legodev_dev_t *legodev_ultra;
    static pbio_servo_t *srv;
    static pbdrv_legodev_type_id_t id = PBDRV_LEGODEV_TYPE_ID_SPIKE_M_MOTOR;
    static pbdrv_legodev_type_id_t id_ultra = PBDRV_LEGODEV_TYPE_ID_SPIKE_ULTRASONIC_SENSOR;

    pbio_error_t err;

    if (!initialized)
    {
      
      err = pbdrv_legodev_get_device(PBIO_PORT_ID_E, &id_ultra, &legodev_ultra);
      if (err == PBIO_SUCCESS){

      } else logmsgvalnl("err get ultra device: ", err);


      err = pbdrv_legodev_get_device(PBIO_PORT_ID_A, &id, &legodev_motor);

      if (err == PBIO_SUCCESS){
	err = pbio_servo_get_servo(legodev_motor, &srv);
	if (err == PBIO_SUCCESS)
	{
	    if (PBIO_SUCCESS != (err = pbio_servo_setup(srv, id, PBIO_DIRECTION_CLOCKWISE, 1000, true, 0)))
            {
               logmsgvalnl("err servo setup: ", err);
            }
	    else initialized = 1;
	}
	else logmsgvalnl("err get servo: ", err);
      }
      else logmsgvalnl("err get device: ", err);

      pbio_error_t errm = pbio_light_matrix_clear(pbsys_hub_light_matrix);
      logmsgvalnl("matrix clear=", errm);

    }

    pbio_error_t errm;

    void *data_distance;
    errm = pbdrv_legodev_get_data(legodev_ultra, PBDRV_LEGODEV_MODE_PUP_ULTRASONIC_SENSOR__DISTL, &data_distance);
    if (errm != PBIO_SUCCESS)
    {
	    logmsg("err ultra");
    }
    else 
    {
	    uint16_t dist = *((uint16_t *)data_distance);
	    logmsgvalnl("dist: ", dist);
    }

    uint32_t current_time = pbdrv_clock_get_ms();
    logmsgvalnl("time: ", current_time);
	
    errm = pbio_light_matrix_set_pixel(pbsys_hub_light_matrix, 3, 3, 100);
    logmsgvalnl("matrix setpx=", errm);

	
    if (PBIO_SUCCESS != (err = pbio_servo_run_time(srv, 500, 4000, PBIO_CONTROL_ON_COMPLETION_BRAKE)))
    {
       logmsgvalnl("err run: ", err);
    }

    delay(4000);

    errm = pbio_light_matrix_set_pixel(pbsys_hub_light_matrix, 3, 3, 0);
    logmsgvalnl("matrix clrpx=", errm);

    delay(1000);

    if (pbio_control_is_done(&srv->control))
	    logmsg("is done");
    else 
	    logmsg("is not done");

    if (pbio_control_is_done(&srv->control))
        logmsg("t");
    else
	logmsg("f");


    return 0;
}

