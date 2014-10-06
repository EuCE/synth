// The maximum PWM output value
#define MAX_PWM 0xFF
#define OUTPUT_PIN 9
// Fast PWM, 8 bit (datasheet page 136)
#define PWM_MODE 0b0101

unsigned int hzToMicros(unsigned int freq) {
	return 1000000 / freq;
}

byte sawWave(unsigned int period /* in us */) {
	unsigned long time = micros() % period;
	return time * MAX_PWM / period;
}

void setup() {
	pinMode(OUTPUT_PIN, OUTPUT);

	// Apply PWM_MODE
	TCCR1A = (TCCR1A & 0b11111100) | (PWM_MODE & 0b11);
	TCCR1B = (TCCR1B & 0b11100111) | (PWM_MODE & 0b1100 << 1);

	// Turn on PWM output A on pin 9
	TCCR1A |= (1 << COM1A1);

	// No prescaling
	TCCR1B &= 0b11111001;
}

unsigned int notes[] = { 262, 328, 392, 523 };

void loop() {
	OCR1A = sawWave(hzToMicros(notes[(millis() % 3000) / 750]));
}
