# Scorpions - A Robot for Solving 3x3 Rubik's Cubes

* We implement data structures and algorithms for solving cubes based on the [CFOP](https://en.wikipedia.org/wiki/CFOP_method) method. The implementation is stored in the [RubikAlgorithm](https://github.com/phamvannhatvu/Scorpions/tree/main/CLI/RubikAlgorithm) folder.

* We use the STM32F103C8T6 microcontroller to rotate the robot arms to exact degrees, recognize the color of the cube's cells, and transmit data between the MCU and a PC for solving algorithms. The STM32 project is stored in the [RubikSolver_STM32](https://github.com/phamvannhatvu/Scorpions/tree/main/RubikSolver_STM32) folder:
  * To rotate the robot arms, we generate PWM signals at the GPIO pins using a timer interrupt. The duty cycle of generated signal depends on the desired rotation degrees.
  * To recognize the color of the cells, we use [TCS34725](https://www.waveshare.com/wiki/TCS34725_Color_Sensor) color sensors and read the sensory data via I2C communication, based on the code example on the manufacturer's website.
  * To send data from the MCU to a PC, we use the built-in USB communication of STM32CubeIDE projects.

* We read the sensory data transmitted from the MCU to a PC using the [LibUSB](https://libusb.info/) C library. After the solving algorithm is completed, we send the algorithm's result back to the MCU to control the robot arms and physically solve the cube. The code for this mechanism is stored in the [USBCommunication](https://github.com/phamvannhatvu/Scorpions/tree/main/CLI/USBCommunication) folder.
