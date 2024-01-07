# Scorpions - A robot solving 3x3 Rubik's cubes

* We implement the data structures and algorithms for solving the cubes based on the [CFOP](https://en.wikipedia.org/wiki/CFOP_method) method, the implementation is stored in the [RubikAlgorithm](https://github.com/phamvannhatvu/Scorpions/tree/main/CLI/RubikAlgorithm) folder.
* We use STMF32F103C8T6 microcontroller to rotate the robot arms to exact degrees, recognize the color of the cube's cells, and transmit data between the MCU and a PC for solving algorithm, the STM32 project is stored in the [RubikSolver_STM32](https://github.com/phamvannhatvu/Scorpions/tree/main/RubikSolver_STM32) folder:
  * To rotate the robot arms, we generated PWM signals at the GPIO pins using a timer interrupt. The duty cycle of generated signals depend on the desired rotation degrees.
  * To recognize the color of the cells, we use [TCS34725](https://www.waveshare.com/wiki/TCS34725_Color_Sensor) color sensors and read the sensory data by I2C communication, based on the code example on the manufacturer's website.
  * To send data from the MCU to a PC, we use the built-in USB communication of STM32CubeIDE projects.
* We read the data transmitted from the MCU to a PC by [LibUSB](https://libusb.info/) C library, and after the solving algorithm is done, we send the data back to the MCU to rotate the cube from the algorithm's result. The code for this mechanism is stored in the [USBCommunication](https://github.com/phamvannhatvu/Scorpions/tree/main/CLI/USBCommunication) folder.
