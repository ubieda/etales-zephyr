# Copyright (c) 2024 Croxel, Inc.
# SPDX-License-Identifier: Apache-2.0

zephyr_sources_ifdef(
  CONFIG_SHELL_BACKEND_BT
  shell_bt.c
)
