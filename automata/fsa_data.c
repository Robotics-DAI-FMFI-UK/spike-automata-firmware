#include "fsa_data.h"
#include "fsa_api.h"

//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "MemoryLeak"

uint8_t memory[MEMORY_SIZE] __attribute__ ((aligned (4)));
uint32_t pointer = 0;

uint16_t fsa_malloc(uint32_t size) {
    if (size + pointer > MEMORY_SIZE)
        return 0;
    if (size & 3)
        size += 4 - (size & 3);
    uint16_t output = (pointer >> 2);
    pointer += size;
    return output;   // real pointer is at memory + (retval << 2);
}

void fsa_free() {
    pointer = 0;
}

typedef uint16_t fsaptr;

uint8_t *fsaptr2ptr8(fsaptr ptr) {
    return memory + (((uint32_t) ptr) << 2);
}

fsaptr *fsaptr2ptrfsaptr(fsaptr ptr) {
    return (fsaptr *) (memory + (((uint32_t) ptr) << 2));
}

float *fsaptr2ptrfloat(fsaptr ptr) {
    return (float *) (memory + (((uint32_t) ptr) << 2));
}


fsaptr ptr2fsaptr(uint8_t *ptr) {
    return (fsaptr) (((uint32_t) ptr) >> 2);
}

uint8_t automata_count;
uint8_t top_level_automata_count;
uint8_t global_variables_count;

fsaptr global_variable_names;
fsaptr global_variable_types;
fsaptr global_variable_init_values;

fsaptr numbers_of_states;
fsaptr numbers_of_final_states;
fsaptr numbers_of_events;
fsaptr automata_names;
fsaptr final_states_numbers;

fsaptr local_variables_counts;
fsaptr local_variable_names;
fsaptr local_variables_types;
fsaptr local_variables_init_values;

fsaptr automata_states;
fsaptr automata_events;

void program_init(uint8_t automata_cnt, uint8_t top_level_automata_cnt, uint8_t global_variables_cnt) {
    fsa_free();
    automata_count = automata_cnt;
    top_level_automata_count = top_level_automata_cnt;
    global_variables_count = global_variables_cnt;
    global_variable_names = fsa_malloc(sizeof(fsaptr) * global_variables_count);
    global_variable_types = fsa_malloc(sizeof(uint8_t) * global_variables_count);
    global_variable_init_values = fsa_malloc(sizeof(fsaptr) * global_variables_count);
    numbers_of_states = fsa_malloc(sizeof(uint8_t) * automata_count);
    numbers_of_final_states = fsa_malloc(sizeof(uint8_t) * automata_count);
    numbers_of_events = fsa_malloc(sizeof(uint8_t) * automata_count);
    automata_names = fsa_malloc(sizeof(uint8_t) * automata_count);
    final_states_numbers = fsa_malloc(sizeof(fsaptr) * automata_count);
    local_variables_counts = fsa_malloc(sizeof(uint8_t) * automata_count);
    local_variable_names = fsa_malloc(sizeof(fsaptr) * automata_count);
    local_variables_types = fsa_malloc(sizeof(fsaptr) * automata_count);
    local_variables_init_values = fsa_malloc(sizeof(fsaptr) * automata_count);
    automata_states = fsa_malloc(sizeof(fsaptr) * automata_count);
    automata_events = fsa_malloc(sizeof(fsaptr) * automata_count);
}

fsaptr store_str_copy(char *str) {
    uint8_t string_len = strlen(str) + 1;
    fsaptr str_in_memory = fsa_malloc(string_len);
    memcpy(fsaptr2ptr8(str_in_memory), str, string_len);
    return str_in_memory;
}

void setup_var_name_and_type(uint8_t id, char *name, uint8_t type, fsaptr var_names, fsaptr var_types) {
    fsaptr name_in_memory = store_str_copy(name);
    fsaptr2ptrfsaptr(var_names)[id] = name_in_memory;
    fsaptr2ptr8(var_types)[id] = type;
}

void setup_global_numeric_variable(uint8_t id, char *name, uint8_t type, float number) {
    setup_var_name_and_type(id, name, type, global_variable_names, global_variable_types);

    fsaptr number_in_memory = fsa_malloc(sizeof(float));
    *fsaptr2ptrfloat(number_in_memory) = number;
    fsaptr2ptrfsaptr(global_variable_init_values)[id] = number_in_memory;
}

void setup_global_string_variable(uint8_t id, char *name, uint8_t type, char *str) {
    setup_var_name_and_type(id, name, type, global_variable_names, global_variable_types);

    fsaptr str_in_memory = store_str_copy(str);
    fsaptr2ptrfsaptr(global_variable_init_values)[id] = str_in_memory;
}

void setup_global_boolean_variable(uint8_t id, char *name, uint8_t type, uint8_t val) {
    setup_var_name_and_type(id, name, type, global_variable_names, global_variable_types);

    fsaptr2ptrfsaptr(global_variable_init_values)[id] = (fsaptr) val;
}

void setup_global_port_variable(uint8_t id, char *name, uint8_t type) {
    setup_var_name_and_type(id, name, type, global_variable_names, global_variable_types);

    fsaptr2ptrfsaptr(global_variable_init_values)[id] = 0;
}

void setup_automaton(uint8_t id, char *name, uint8_t num_states, uint8_t num_final_states, uint8_t num_events) {
    fsaptr name_in_memory = store_str_copy(name);

    fsaptr2ptrfsaptr(automata_names)[id] = name_in_memory;
    fsaptr2ptr8(numbers_of_states)[id] = num_states;
    fsaptr2ptr8(numbers_of_final_states)[id] = num_final_states;
    fsaptr2ptr8(numbers_of_events)[id] = num_events;
    fsaptr2ptrfsaptr(final_states_numbers)[id] = fsa_malloc(sizeof(uint8_t) * num_final_states);
    fsaptr2ptrfsaptr(automata_states)[id] = fsa_malloc(sizeof(fsaptr) * num_states);
    fsaptr2ptrfsaptr(automata_events)[id] = fsa_malloc(sizeof(fsaptr) * num_events);
}

void setup_one_final_state_number_of_automaton(uint8_t id_automaton, uint8_t index_final_state, uint8_t final_state_number) {
    fsaptr2ptr8(fsaptr2ptrfsaptr(final_states_numbers)[id_automaton])[index_final_state] = final_state_number;
}

void setup_local_var_structures_for_automaton(uint8_t id_automaton, uint8_t local_var_count) {
    fsaptr2ptr8(local_variables_counts)[id_automaton] = local_var_count;
    fsaptr2ptrfsaptr(local_variable_names)[id_automaton] = fsa_malloc(sizeof(fsaptr) * local_var_count);
    fsaptr2ptrfsaptr(local_variables_types)[id_automaton] = fsa_malloc(sizeof(uint8_t) * local_var_count);
    fsaptr2ptrfsaptr(local_variables_init_values)[id_automaton] = fsa_malloc(sizeof(fsaptr) * local_var_count);
}

void setup_local_var_name_and_type(uint8_t automaton_id, uint8_t id, char *name, uint8_t type) {
    fsaptr var_names = fsaptr2ptrfsaptr(local_variable_names)[automaton_id];
    fsaptr var_types = fsaptr2ptrfsaptr(local_variables_types)[automaton_id];
    setup_var_name_and_type(id, name, type, var_names, var_types);
}

void setup_local_numeric_variable(uint8_t automaton_id, uint8_t id, char *name, uint8_t type, float number) {
    setup_local_var_name_and_type(automaton_id, id, name, type);

    fsaptr number_in_memory = fsa_malloc(sizeof(float));
    *fsaptr2ptrfloat(number_in_memory) = number;
    fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(local_variables_init_values)[automaton_id])[id] = number_in_memory;
}

void setup_local_string_variable(uint8_t automaton_id, uint8_t id, char *name, uint8_t type, char *str) {
    setup_local_var_name_and_type(automaton_id, id, name, type);

    fsaptr str_in_memory = store_str_copy(str);
    fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(local_variables_init_values)[automaton_id])[id] = str_in_memory;
}

void setup_local_boolean_variable(uint8_t automaton_id, uint8_t id, char *name, uint8_t type, uint8_t val) {
    setup_local_var_name_and_type(automaton_id, id, name, type);

    fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(local_variables_init_values)[automaton_id])[id] = (fsaptr) val;
}

uint32_t size_of_state(uint8_t num_script_lines, uint8_t num_transitions) {
    return sizeof(fsaptr) +  // name
           3 * sizeof(uint8_t) + // #script lines, subautomaton, num_trans
           sizeof(int16_t) +     // period
           sizeof(fsaptr) * num_script_lines +
           sizeof(fsaptr) * num_transitions +
           1;   // alignment
}

#define AUTOMATON_PROPERTY_NAME_OFFSET 0
#define AUTOMATON_PROPERTY_SCRIPT_LINES_OFFSET 2
#define AUTOMATON_PROPERTY_SUBAUTOMATON_OFFSET 3
#define AUTOMATON_PROPERTY_PERIOD_LINES_OFFSET 4
#define AUTOMATON_PROPERTY_NUM_TRANSITIONS_OFFSET 6
#define AUTOMATON_PROPERTY_TRANSITIONS_OFFSET 8
#define AUTOMATON_PROPERTY_SCRIPT_OFFSET(num_transitions) (8 + (num_transitions * 2))

void set_automaton_name(fsaptr state_in_memory, fsaptr name_in_memory) {
    *fsaptr2ptrfsaptr(state_in_memory) = name_in_memory;
}

void set_structure_property8(fsaptr structure_in_memory, uint8_t property_offset, uint8_t value) {
    *(fsaptr2ptr8(structure_in_memory) + property_offset) = value;
}

void set_structure_property16(fsaptr structure_in_memory, uint8_t property_offset, uint16_t value) {
    *((uint16_t * )(fsaptr2ptr8(structure_in_memory) + property_offset)) = value;
}

uint8_t get_structure_property8(fsaptr structure_in_memory, uint8_t property_offset) {
    return *(fsaptr2ptr8(structure_in_memory) + property_offset);
}

uint16_t get_structure_property16(fsaptr structure_in_memory, uint8_t property_offset) {
    return (uint16_t)(*(fsaptr2ptr8(structure_in_memory) + property_offset));
}

void set_automaton_script_lines(fsaptr state_in_memory, uint8_t num_script_lines) {
    set_structure_property8(state_in_memory, AUTOMATON_PROPERTY_SCRIPT_LINES_OFFSET, num_script_lines);
}

void set_automaton_period(fsaptr state_in_memory, int16_t period) {
    set_structure_property16(state_in_memory, AUTOMATON_PROPERTY_PERIOD_LINES_OFFSET, (uint16_t) period);
}

void set_automaton_subautomaton(fsaptr state_in_memory, int8_t subautomaton) {
    set_structure_property8(state_in_memory, AUTOMATON_PROPERTY_SUBAUTOMATON_OFFSET, (uint8_t) subautomaton);
}

void set_automaton_num_transitions(fsaptr state_in_memory, uint8_t num_transitions) {
    set_structure_property8(state_in_memory, AUTOMATON_PROPERTY_NUM_TRANSITIONS_OFFSET, num_transitions);
}

uint8_t get_automaton_num_transitions(fsaptr structure_in_memory) {
    return get_structure_property8(structure_in_memory, AUTOMATON_PROPERTY_NUM_TRANSITIONS_OFFSET);
}

void setup_state_structures_for_automaton(uint8_t automaton_id, uint8_t state_id, char *state_name, uint8_t num_script_lines,
                                          int16_t period, int8_t subautomaton, uint8_t num_transitions) {
    fsaptr state_in_memory = fsa_malloc(size_of_state(num_script_lines, num_transitions));
    fsaptr name_in_memory = store_str_copy(state_name);
    set_automaton_name(state_in_memory, name_in_memory);
    set_automaton_script_lines(state_in_memory, num_script_lines);
    set_automaton_period(state_in_memory, period);
    set_automaton_subautomaton(state_in_memory, subautomaton);
    set_automaton_num_transitions(state_in_memory, num_transitions);
    fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(automata_states)[automaton_id])[state_id] = state_in_memory;
}

void setup_state_transition(uint8_t automaton_id, uint8_t state_id, uint8_t transition_index, fsaptr transition) {
    set_structure_property16(
            fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(automata_states)[automaton_id])[state_id],
            AUTOMATON_PROPERTY_TRANSITIONS_OFFSET + transition_index * 2,
            transition);
}

void setup_state_script_statement(uint8_t automaton_id, uint8_t state_id, uint8_t statement_index, fsaptr statement) {
    fsaptr state_in_memory = fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(automata_states)[automaton_id])[state_id];
    uint8_t num_transitions = get_automaton_num_transitions(state_in_memory);
    set_structure_property16(state_in_memory,
                             AUTOMATON_PROPERTY_SCRIPT_OFFSET(num_transitions) + statement_index * 2,
                             statement);
}

uint32_t size_of_transition(uint8_t num_script_lines) {
    return sizeof(uint8_t) +  // dest state
           sizeof(uint8_t) +  // cond value type
           sizeof(uint16_t) + // value parameter
           sizeof(uint8_t) + // num script lines
           sizeof(fsaptr) * num_script_lines +   // script lines pointers
           1;   // alignment
}

#define TRANSITION_PROPERTY_DEST_STATE_OFFSET 0
#define TRANSITION_PROPERTY_COND_VAL_TYPE_OFFSET 1
#define TRANSITION_PROPERTY_COND_VAL_PARAM_OFFSET 2
#define TRANSITION_PROPERTY_NUM_SCRIPT_LINES_OFFSET 4
#define TRANSITION_PROPERTY_SCRIPT_LINES_OFFSET 6

void new_transition(uint8_t dest_state_id, uint8_t cond_value_type, uint16_t value_parameter, uint8_t num_script_lines) {
    fsaptr transition_in_memory = fsa_malloc(size_of_transition(num_script_lines));
    set_structure_property8(transition_in_memory, TRANSITION_PROPERTY_DEST_STATE_OFFSET, dest_state_id);
    set_structure_property8(transition_in_memory, TRANSITION_PROPERTY_COND_VAL_TYPE_OFFSET, cond_value_type);
    set_structure_property16(transition_in_memory, TRANSITION_PROPERTY_COND_VAL_PARAM_OFFSET, value_parameter);
    set_structure_property8(transition_in_memory, TRANSITION_PROPERTY_NUM_SCRIPT_LINES_OFFSET, num_script_lines);
}

void set_transition_script_line(fsaptr transition_in_memory, uint8_t script_line_index, fsaptr script_line) {
    set_structure_property16(transition_in_memory, TRANSITION_PROPERTY_SCRIPT_LINES_OFFSET + 2 * script_line_index,
                             script_line);
}

fsaptr new_call(uint8_t call_id) {
    uint8_t num_params = 0;
    if (call_id >= 100) // function call
        num_params = functions_num_params[call_id - 100];
    else
        num_params = procedures_num_params[call_id - 100];
    fsaptr call_in_memory = fsa_malloc(1 + 3 * num_params);
    *fsaptr2ptr8(call_in_memory) = call_id;

    return call_in_memory;
}

void set_call_param(fsaptr call_in_memory, uint8_t param_index, uint8_t value_type, fsaptr value_param) {
    set_structure_property8(call_in_memory, 1 + 3 * param_index, value_type);
    set_structure_property16(call_in_memory, 2 + 3 * param_index, value_param);
}

void set_automaton_event(uint8_t automaton_id, uint8_t event_id, fsaptr event_transition)
{
    fsaptr2ptrfsaptr(fsaptr2ptrfsaptr(automata_events)[automaton_id])[event_id] = event_transition;
}

//#pragma clang diagnostic pop