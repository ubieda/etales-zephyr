# Embedded Tales - Zephyr

Contains source code (libraries and examples) referenced on https://embeddedtales.blog specific to the Zephyr Project. This repository can be used as an external module to leverage the existing codebase and speed-up development-process on Applications compatible with the Zephyr Project (as well as nRF Connect SDK).

## Getting Started

The best place to start using this repository is by following Zephyr's Getting Started Guide and getting familiar with the Zephyr Project.


This repository assumes you have installed all of the dependencies listed on the [Getting Started guide by Zephyr](https://docs.zephyrproject.org/3.5.0/develop/getting_started/index.html#getting-started-guide).

Please note this repository has been developed and tested against [Zephyr Release 3.5.0](https://github.com/zephyrproject-rtos/zephyr/releases/tag/v3.5.0).

### Set Development Environment

#### Option 1 - Setup using West Manifest
This option is useful to evaluate and try the libraries and examples available.

```console
mkdir -p ~/zephyrproject
cd ~/zephyrproject
west init -m https://github.com/ubieda/etales-zephyr
west update
```

#### Option 2 - Setup including as an External Module
This option is useful when integrating the codebase as an external module. This approach assumes the Manifest is in the application, and works by adding it as a module dependency:

```yaml
- name: etales-zephyr
  path: modules/lib/etales-zephyr
  revision: master
  url: https://github.com/ubieda/etales-zephyr.git
```

### Build Sample Code - Hello World

```console
cd ~/zephyrproject/modules/lib/etales-zephyr
source ~/zephyrproject/zephyr/zephyr-env.sh

west build -b nrf52840dk_nrf52840 samples/hello_world
```
