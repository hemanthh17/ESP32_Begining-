const int ledPin = 2; 

// setting PWM properties
const int freq = 5000; //for LED we set the PWM freq as 5000Hz
const int led_Channel = 0; // the channel can range from 0 to 15
const int resolution = 8; // 8 bit resolution
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(led_Channel, freq, resolution); 
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, led_Channel);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(led_Channel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(led_Channel, dutyCycle);   
    delay(15);
  }
}
 
