
#include <Servo.h>

#define SERVO 9
Servo s; // Variável Servo
int pos; // Posição Servo

// Pinos dos led
int brancos = 8;
int vermelhos = 7;
int verdes = 6;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
//fim servo config

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



void setup() {
// setup servo

  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
  // fim setup

  pinMode(brancos, OUTPUT);
  pinMode(vermelhos, OUTPUT);
  pinMode(verdes, OUTPUT);
  

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
 
}

void loop() {
 //configuração para ativar leds



  char entrada = Serial.read();



if(entrada == 'f'){
  digitalWrite(verdes, HIGH);
}if(entrada == 'g' ){
  digitalWrite(verdes, LOW);
}


if(entrada == 'h'){
  digitalWrite(vermelhos, HIGH);
}if(entrada == 'i' ){
  digitalWrite(vermelhos, LOW);
}


//servo motor
  if(entrada == 'd'){
  for(pos = 0; pos < 180; pos++)
  {
    s.write(pos);
  delay(15);
  }
  }else if(entrada == 'e'){
delay(1000);
  for(pos = 180; pos >= 0; pos--)
  {
    s.write(pos);
    delay(15);
  }
  }

//servo fim


//led sala, balada
  if(entrada == 'b'){
  corFixa(strip.Color(0,   0,   0),brancos);
  digitalWrite(brancos, LOW);
  }
  
  if(entrada == 'a'){
  corFixa(strip.Color(255,   255,   255),brancos);
  
  }else if(entrada == 'c'){
delay(1000);
  // Fill along the length of the strip in various colors...


      // Do a theater marquee effect in various colors...
      theaterChase(strip.Color(127, 127, 127), 50
      ); // White, half brightness
      theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
      theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

      rainbow(10);             // Flowing rainbow cycle along the whole strip
      theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
 
  }

//fiiim


 
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void corFixa(uint32_t color,int pin) {
  digitalWrite(pin,HIGH);
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
                        //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
