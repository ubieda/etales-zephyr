/*
 * Copyright (c) 2024 Croxel, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/shell/shell.h>
#include <zephyr/kernel.h>

extern int bt_app_init(void);

/** @NOTE: Simple Custom command added to demo how to add your own  */
int handler_bluetooth_name(const struct shell *sh, size_t argc, char **argv)
{
        shell_print(sh, "Bluetooth Name: %s", CONFIG_BT_DEVICE_NAME);

        return 0;
}

SHELL_CMD_REGISTER(device_name, NULL, "Get Bluetooth Name", handler_bluetooth_name);

int main(void)
{
	int err = -1;

	err = bt_app_init();
	if (err) {
		printk("Bluetooth failed to initialize: %d\n", err);
		return err;
	}

	printk("Shell over Bluetooth Sample started!\n");

	return 0;
}
