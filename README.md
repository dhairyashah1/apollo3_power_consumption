# Apollo3 Power Consumption
Code for evaluating power consumption at different frequencies and modes for Ambiq Apollo3 on Redboard Artemis ATP Board

## Pre-requisites
1. Install [Apollo Ambiq SDK](https://github.com/sparkfun/AmbiqSuiteSDK) with a `recursive clone` to fetch `boards_sfe` alongwith the dependencies and toolchains. A step-by-step guide for development using Ambiq SDK is given [here](https://learn.sparkfun.com/tutorials/using-sparkfun-edge-board-with-ambiq-apollo3-sdk/installing-the-sdk-and-board-support-files).
2. Install [Board Support Packages](https://github.com/sparkfun/SparkFun_Apollo3_AmbiqSuite_BSPs) (BSPs) according to the target platform, eg. `Redboard Artemis ATP`
3. For easier testing and initial Ambiq development using Arduino refer [this guide](https://learn.sparkfun.com/tutorials/artemis-development-with-arduino/all)

## Hardware & Software setup
1. Connect your target platform i.e. `Redboard Artemis ATP` in this case to the setup PC. Also connect the relevant power profiler i.e. `Nordic Power Profiler Kit (PPK) 2` in this case for current measurement in ammeter mode. Ensure that there is common ground between the devices.
2. Clone this repository in this path -> `<path_to_ambiq_sdk>/boards_sfe/common/examples/`. This example can be built elsewhere by specifying the path changes in the [`Makefile`](https://github.com/dhairyashah1/apollo3_power_consumption/blob/main/example_blank/gcc/Makefile)
3. Connect power supply to the power profiler and the Ambiq board
4. In [`main.c`](https://github.com/dhairyashah1/apollo3_power_consumption/blob/main/example_blank/main.c#L14C1-L18C74), select the desired mode by uncommenting it and commenting rest of the modes.
5. Compile and upload code to the Ambiq board using the below commands:
```
cd example_blank/gcc
make bootload_svl BOARD=redboard_artemis_atp COM_PORT=/dev/ttyUSB0 PYTHON=python3 SVL_UPLOAD_BAUD=921600
```
Generically,
```
make <make_target> BOARD=<board_target> COM_PORT=<port> PYTHON=<python> SVL_UPLOAD_BAUD=<baud_rate>
```
a. It uses the [`Sparkfun Variable Loader`](https://learn.sparkfun.com/tutorials/artemis-development-with-arduino/bootloader-options) (SVL) Bootloader. If needed, the `Ambiq Secure Bootloader` (ASB) can also be used. 
b. Specify and replace the corresponding fields in the make command as required.
c. `<make_target>` = `clean`, `bootload_svl` and `bootload_asb`
d. `<board_target` = `edge`, `edge2`, `artemis_devkit`, `redboard_artemis_atp`, etc
e. `<port>` = `COMxx` on Windows, `/dev/ttyUSBx` on Linux
