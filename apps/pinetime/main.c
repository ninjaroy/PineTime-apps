/*
 * Copyright (C) 2018 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "log.h"
#include "xtimer.h"
#include "lvgl.h"

#include "xtimer.h"

#include "shell.h"
#include "msg.h"

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern lv_disp_t *hal_init(void);
extern int lvgl_thread_create(lv_disp_t *display);

int main(void)
{
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    LOG_DEBUG("Starting PineTime application");
    lv_init();

    lv_disp_t * disp = hal_init();
    if (disp == NULL) {
        return 0;
    }
    lvgl_thread_create(disp);

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    while (1) {
        xtimer_sleep(10);
    }

    return 0;
}