//
// Created by tomas on 23.6.2024.
//

#include "fsa_api.h"

const uint8_t functions_num_params[NUM_FSA_API_FUNCTIONS] = {
//        "100" |  ; read()                          - read one char from BT console and return it as string of len 1
        0,
//        "101" |  ; read_line()                     - read one line from BT console and return it as string
        0,
//        "102" |  ; angle(number dir)               - return inclination of the hub (0 - yaw, 1 - pitch, 2 - roll), returns number
        1,
//        "103" |  ; motor_angle(number port_var)    - return the current position of motor specified with port-type variable in degrees 0-359
        1,
//        "104" |  ; motor_speed(number port_var)    - return the current speed of motor specified with port-type variable in percentage
        1,
//        "105" |  ; left_button()                   - return the state of left button pressed  (0 - not pressed, 1 - pressed)
        0,
//        "106" |  ; right_button()                  - return the state of right button pressed  (0 - not pressed, 1 - pressed)
        0,
//        "107" |  ; bt_button()                     - return the state of bt button pressed  (0 - not pressed, 1 - pressed)
        0,
//        "108" |  ; distance(number port_var)       - return the distance measured by US sensor on port specified with port-type variable
        1,
//        "109" |  ; force(number port_var)          - return the force measured by force sensor on port specified with port-type variable
        1,
//        "110" |  ; color(number port_var)          - return the color number measured by color sensor on port specified with port-type variable
        1,
//        "111" |  ; reflect(number port_var)        - return the percentage of reflected light in active mode measured by color sensor on port specified with port-type variable
        1,
//        "112" |  ; ambient(number port_var)        - return the percentage of ambient light in passive mode measured by color sensor on port specified with port-type variable
        1,
//        "113" |  ; concat(string s1, string s2)    - return a new string that is created by concatenating the two specified strings
        2,
//        "114" |  ; substr(string s, number i, number len)  - returns a new string containing a substring of the supplied string, starting at a specified index of a specified length
        3,
//        "115" |  ; eqstr(string s1, string s2)     - returns true, if the strings are equal, otherwise returns false
        2,
//        "116" |  ; setchar(string s, string c, number i)   - modifies the specified string by changing its i-th char to the first char in the specified string c
        3,
//        "117" |  ; ascii(string s)                 - returns a number representing ASCII value of the first char of string s
        1,
//        "118" |  ; chr(number ascii)               - returns a one-char long string with a character with the specified ASCII value
        1,
//        "119" |  ; eq(number a, number b)          - return true, if a, and b are the same numbers (wrt. a small allowed epsilon difference), otherwise returns false
        2,
//        "120" |  ; less(number a, number b)        - returns true, if a < b, otherwise returns false
        2,
//        "121" |  ; more(number a, number b)        - returns true, if a > b, otherwise returns false
        2,
//        "122" |  ; between(number x, number bottom, number top)  - returns true, if x >= bottom and x <= top, otherwise returns false
        3,
//        "123" |  ; plus(number a, number b)        - returns a number with value a + b
        2,
//        "124" |  ; minus(number a, number b)       - returns a number with value a - b
        2,
//        "125" |  ; times(number a, number b)       - returns a number with value a * b
        2,
//       "126" |  ; divide(number a, number b)      - returns a number with value a / b
        2,
//        "127" |  ; mod(number a, number b)         - returns a number with value a % b
        2,
//        "128" |  ; sqrt(number x)                  - returns a number with value square root of x
        1,
//        "129" |  ; abs(number x)                   - returns a number with value abs(x)
        1,
//        "130" |  ; sgn(number x)                   - returns a number with value sign of x: -1, 0 or 1
        1,
//        "131" |  ; sin(number x)                   - returns a number with value sin(x)
        1,
//        "132" |  ; cos(number x)                   - returns a number with value cos(x)
        1,
//        "133" |  ; atan2(number y, number x)       - returns a number with value atan2(y, x)
        2,
//        "134" |  ; ceil(number x)                  - returns a number with value ceil(x)
        1,
//        "135" |  ; floor(number x)                 - returns a number with value floor(x)
        1,
//        "136" |  ; and(boolean a, boolean b)       - logical and of two boolean values
        2,
//        "137" |  ; or(boolean a, boolean b)        - logical or of two boolean values
        2,
//        "138" |  ; xor(boolean a, boolean b)       - logical xor of two boolean values
        2,
//        "139" |  ; not(boolean x)                  - logical not of a boolean value
        1
};


const uint8_t procedures_num_params[NUM_FSA_API_PROCEDURES] = {
//        "0" |   ; print_message(string msg)            - sends string to console
        1,
//        "1" |   ; print_value(string msg, number n)    - sends string followed by number to console
        2,
//        "2" |   ; matrix_clear()                       - turns off all 25 pixels
        0,
//        "3" |   ; matric_orientation(number o)         - sets orientation for showing letters/numbers
        1,
//        "4" |   ; matrix_set_pixel(number row, number col, number brightness_percentage)   - ; controls single LED of the display
        3,
//        "5" |   ; matrix_set_image(number image_id)    - shows one of the predefined images on display
        1,
//        "6" |   ; matrix_letter(string msg)            - displays one letter character on display
        1,
//        "7" |   ; matrix_digit(number digit)           - displays one digit on display on display
        1,
//        "8" |   ; play_tone(number freq, number dur_ms)  - plays tone of the specified frequency for the specified time
        2,
//        "9" |   ; stop_play()                          - turn off playing tone now
        0,
//        "10" |   ; set_local_number(number var, number value)  - set a specified local variable to specified numeric value, automatically inferred from user's set(string var, any value)
        2,
//        "11" |   ; set_local_string(number var, string value)  - set a specified local variable to specified string value, automatically inferred from user's set(string var, any value)
        2,
//        "12" |   ; set_local_boolean(number var, boolean value) - set a specified local variable to specified string value, automatically inferred from user's set(string var, any value)
        2,
//        "13" |   ; set_global_number(number var, number value)  - set a specified global variable to specified numeric value, automatically inferred from user's set(string var, any value)
        2,
//        "14" |   ; set_global_string(number var, string value)  - set a specified global variable to specified string value, automatically inferred from user's set(string var, any value)
        2,
//        "15" |   ; set_global_boolean(number var, boolean value) - set a specified global variable to specified string value, automatically inferred from user's set(string var, any value)
        2,
//        "16" |   ; motor_on(number port_var, number speed)      - starts motor on a port specified using id of variable of type port to specified speed (positive or negative)
        2,
//        "17" |   ; motor_on_for(number port_var, number speed, number time_ms)
        3,
//        "18" |   ; motor_turn(number port_var, number speed, number angle_deg)
        3,
//        "19" |   ; motor_off(number port_var)           - turn off motor on port specified using port variable instantly
        1,
//        "20" |   ; base_speed(number port_var, number speed) - configure speed for robot base movements
        2,
//        "21" |   ; base_fwd(number port_var, number dist_deg)
        2,
//        "22" |   ; base_on(number port_var)             - start moving the robot base using configured speed
        1,
//        "23" |   ; base_off(number port_var)            - stop moving the base instantly
        1,
//        "24" |   ; base_turn(number port_var, number radius, number angle)
        3,
//        "25" |   ; base_tank(number port_var, number left_speed, number right_speed)
        3,
//        "26" |   ; base_tank_for(number port_var, number left_speed, number right_speed, number time_ms)
        4,
//        "27" |   ; base_tank_turn(number port_var, number left_speed, number right_speed, number angle_deg)
        4,
//        "28" |   ; delay(ms)                            - pause execution of script for the specified time
        1,
//        "29" |   ; while(number boolean_var)            - beginning of while loop - it is not really a procedure, but a statement for the interpreter to mark the start of the loop
        1,
//        "30" |   ; wend()                               - end of while loop - not really a procedure, but a statement for the interpreter to jump to the start of the loop, if variable still true
        0,
//        "31" |   ; if(number boolean_var)               - beginning of if branching - not a procedure, marks start of the then part of the if block
        1,
//        "32" |   ; else()                               - end of then-part of the if-block and start of else-part (optional) - always pairs with the last if encountered
        0,
//        "33" |   ; endif()                              - end of if branching - not a procedure, marks end of then-part of else-part of the if-block
        0,
//        "34" |   ; lock()
        0,
//        "35"     ; unlock()
        0
};
