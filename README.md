STM32 External and USART Interrupt Control
This embedded C project showcases how to implement external interrupts (EXTI) and USART software-triggered interrupts on the STM32F446RE microcontroller using bare-metal (register-level) programming.

🔧 Key Features:
System Clock Configuration:

Uses HSI as the system clock source.

Initializes SysTick for precise timing.

GPIO Setup:

PA5 configured as an output pin to drive an LED.

PC13 configured as an input pin with an internal pull-up resistor (connected to a push button).

Interrupt Configuration:

EXTI13 (connected to PC13) is configured to trigger on both rising and falling edges.

NVIC priorities are set to ensure correct handling of EXTI and USART interrupts.

⚙️ Functional Behavior:
When the button is pressed (logic LOW), the LED is turned OFF.

When the button is released (logic HIGH), the code sets the USART3 pending interrupt flag, which triggers the interrupt handler that turns the LED ON.

This project is ideal for learning interrupt-driven development, understanding NVIC priority configuration, and practicing low-level control on STM32 microcontrollers — without using STM32 HAL or Cube libraries.

