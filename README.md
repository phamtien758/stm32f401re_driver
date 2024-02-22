# Driver for STM32F401RE microcontroller
### Target board for development and testing: [NUCLEO-F401RE](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
<br></br>
:heavy_check_mark: Folder structure:
* **common**
     - **from_ST** : Contains resources from ST (linker file, startup file, system-call functions, system-memory functions)
     - **template** : The template for source files and header files
* **driver**
     - **inc** : Header files
     - **src** : Source files
* **test**
     - ****<**module**>**** : Contains test cases of module
* **Makefile** : Commands to compile, create object files, debug, ...
* **ozone_config.jdebug** : Configuration for Ozone debugger

<br></br>
:heavy_check_mark: Development tools:
* **Arm Gnu toolchain** : [Detail](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain)
* **Cygwin64** (install Makefile package) : [Detail](https://www.cygwin.com)
* **Ozone** : [Detail](https://www.segger.com/products/development-tools/ozone-j-link-debugger)
  - How to use ST-Link as a J-Link ? : [Detail](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board)
