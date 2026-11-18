# FiberCards NFC Business Card

A battery-free PCB business card that shares a link with an NFC-enabled phone and lights up its LEDs using power harvested from the phone.
The copper spiral on the board acts as an inductor and NFC antenna. The phone's changing magnetic field induces a voltage in the coil, and the NFC chip harvests this energy to power the microcontroller and LEDs.

The hardware design is in [`cad/`](cad/), and the firmware is in [`firmware/`](firmware/).
