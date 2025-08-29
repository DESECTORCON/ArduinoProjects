#define CO2PWM 2

volatile unsigned long rosetime = 0;
volatile unsigned long falltime = 0;

volatile unsigned long co2			 = 0;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(1);
	pinMode(CO2PWM, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(CO2PWM), getwave, CHANGE);
}

void loop() {
	while (!Serial.available()) {}
	Serial.read();
	Serial.println(co2);
}

void getwave(){
	int state = digitalRead(CO2PWM);
	if (state == 1) {
		rosetime = millis();
	} else {
		falltime = millis();
		co2 = (falltime - rosetime - 2) * 5;
	}	
}
