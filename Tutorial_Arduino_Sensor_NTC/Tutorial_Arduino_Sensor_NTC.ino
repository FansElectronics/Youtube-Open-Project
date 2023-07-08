//------------------------------------------------------------------------------
#define NTC_PIN A13

void setup() {
  Serial.begin(9600);  // Debug ke PC
}
//------------------------------------------------------------------------------

void loop() {
  float celcius = getTemperature(NTC_PIN, 'C');
  float farenheit = getTemperature(NTC_PIN, 'F');
  float kelvin = getTemperature(NTC_PIN, 'K');
  Serial.print("TEMP: \t");
  Serial.print(celcius);
  Serial.print("C \t");
  Serial.print(farenheit);
  Serial.print("F \t");
  Serial.print(kelvin);
  Serial.println("K \t");
}

//------------------------------------------------------------------------------
float getTemperature(uint8_t pin, char unit) {
  const float R1 = 10000;  // Nilai Resistor ke GND 10K / 10000 ohm
  const float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  int adc = analogRead(pin);
  float R2 = R1 * (1023.0 / (float)adc - 1.0);
  float logR2 = log(R2);
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // KElvin
  float Tc = T - 273.15;                                             // CELCIUS
  float Tf = (Tc * 9.0) / 5.0 + 32.0;                                // FARENHEIT
  if (unit == 'K') return T;
  else if (unit == 'F') return Tf;
  else return Tc;
}