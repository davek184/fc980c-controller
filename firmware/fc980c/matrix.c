// Copyright 2022 Wilhelm Schuster
// Copyright 2019 Evy Dekkers
// Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"
#include "util.h"
#include "wait.h"

static const pin_t row_pins[] = MATRIX_MUX_ROW_PINS;
static const pin_t col_pins[] = MATRIX_MUX_COL_PINS;

static inline void KEY_ENABLE_on(void) { writePinLow(MATRIX_KEY_ENABLE_PIN); }
static inline void KEY_ENABLE_off(void) { writePinHigh(MATRIX_KEY_ENABLE_PIN); }
static inline void KEY_HYS_on(void) { writePinHigh(MATRIX_KEY_HYS_PIN); }
static inline void KEY_HYS_off(void) { writePinLow(MATRIX_KEY_HYS_PIN); }

static void set_row(int row) {
    writePin(row_pins[0], row & 0b00000001);
    writePin(row_pins[1], row & 0b00000010);
    writePin(row_pins[2], row & 0b00000100);
}

static void set_col(int col) {
    writePin(col_pins[0], col & 0b00000001);
    writePin(col_pins[1], col & 0b00000010);
    writePin(col_pins[2], col & 0b00000100);
    writePin(col_pins[3], col & 0b00001000);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], int current_col) {
    bool matrix_changed = false;

    set_col(current_col);

    for (int row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        set_row(row_index);

        if (last_row_value & (1 << current_col)) {
            KEY_HYS_on();
        }
        matrix_output_select_delay();

        KEY_ENABLE_on();
        wait_us(2);

        // KEY_STATE is only valid for 20us after KEY_ENABLE
        if (!readPin(MATRIX_KEY_STATE_PIN)) {
            // pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        KEY_HYS_off();
        KEY_ENABLE_off();

        // KEY_STATE keeps its state for 20us after KEY_ENABLE. Wait for 25us or
        // more to make sure KEY_STATE returns to idle state.
        wait_us(25);

        // determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    return matrix_changed;
}


#if !defined(IS_ARRAY)
/**
 * @brief Returns true if the value is an array, false if it's a pointer.
 *
 * This macro is ill-formed for scalars, which is OK for its intended use in
 * ARRAY_SIZE.
 */
#    define IS_ARRAY(value) (!__builtin_types_compatible_p(typeof((value)), typeof(&(value)[0])))
#endif

#if !defined(ARRAY_SIZE)
/**
 * @brief Computes the number of elements of the given array at compile time.
 *
 * This Macro can only be used for statically allocated arrays that have not
 * been decayed into a pointer. This is detected at compile time, though the
 * error message for scalar values is poor.
 */
#    define ARRAY_SIZE(array) (__builtin_choose_expr(IS_ARRAY((array)), sizeof((array)) / sizeof((array)[0]), (void)0))
#endif
 
void matrix_init_custom(void) {
    setPinInput(MATRIX_KEY_STATE_PIN); // uses external pullup
    setPinOutput(MATRIX_KEY_HYS_PIN);
    setPinOutput(MATRIX_KEY_ENABLE_PIN);

    for (int i = 0; i < ARRAY_SIZE(row_pins); i++) {
        setPinOutput(row_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(col_pins); i++) {
        setPinOutput(col_pins[i]);
    }

    KEY_ENABLE_off();
    KEY_HYS_off();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}

