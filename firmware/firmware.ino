#include <util/delay.h>

#define M1_PIN            3
#define M2_PIN            4
#define M3_PIN            0
#define M4_PIN            1
#define M5_PIN            2


const uint8_t LED_CONFIGS[5] = {
  M1_PIN,
  M2_PIN,
  M3_PIN,
  M4_PIN,
  M5_PIN
};


void turn_on_leds(uint8_t count) {
  if (count == 0) {
    DDRB &= ~0x1f;
    PORTB &= ~0x1f;
    return;
  }

  for (uint8_t i = 0; i < count; i++) {
    DDRB |= 1 << LED_CONFIGS[i];
    PORTB |= 1 << LED_CONFIGS[i];
  }
  for (uint8_t i = count; i < 5; i++) {
    DDRB &= ~(1 << LED_CONFIGS[i]);
    PORTB &= ~(1 << LED_CONFIGS[i]);
  }
}

int main() {
  // Set ADC Multiplexer to use VCC as voltage reference and use the internal bandagap sa input
  ADMUX = (0 << REFS0) | (0 << REFS1) | (1 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0);
  ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
  float vcc_volts = 0.0;
  _delay_ms(2);

  while (true) {
    // Enable the ADC and start conversion
    ADCSRA |= 1 << ADSC;
    // Wait for conversion to complete
    while (((ADCSRA & (1 << ADSC)) != 0));

    vcc_volts = 1126.4f / (float) ADC;
    if (vcc_volts < 2) {
      turn_on_leds(0);
    } else if (vcc_volts < 2.1) {
      turn_on_leds(1);
    } else if (vcc_volts < 2.2) {
      turn_on_leds(2);
    } else if (vcc_volts < 2.3) {
      turn_on_leds(3);
    } else if (vcc_volts < 2.4) {
      turn_on_leds(4);
    } else {
      turn_on_leds(5);
    }

    _delay_ms(1);
  }

  return 0;
}
