# Copyright (c) 2024 Luis Ubieda.
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(shell)
add_subdirectory_ifdef(CONFIG_MOTION_DETECTION motion_detection)
