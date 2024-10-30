//Declarations

#include <Arduino.h>                        // needed for PlatformIO\

//This segment invokes the NeoPixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//This line ivnvokes the Ramp library, found in the libraries tab
//The full documentation can be found below
//https://github.com/siteswapjuggler/RAMP
#include <Ramp.h>                           

//-------------------------------------------------------------------

//Variables

//This line sets which pin the NeoPixel object is plugged into
#define PUDDLEPIN        10 // On Trinket or Gemma, suggest changing this to 1
#define STRIPPIN        11 // On Trinket or Gemma, suggest changing this to 1


//This sets how many NeoPixels are on the object
#define NUMPIXELS 60

//This line defines the time (in milliseconds) to pause between pixels (basically the speed of the animation)
//Note: in this script, it affects where the pixels start on the script, need to fix this
#define DELAYVAL 30

//These are the two ramps which control the fade of the LEDs
//The first ramp controls the brightness.
ramp myRamp;
//The Second ramp controls slight the Fade-in of the blue value.
ramp myRamp2;
//In the Void Setup they are defined, and in the Pixelfall Function they are utilized.
ramp myRamp3;


//This line sets a variable for the NeoPixel object.
//The first argument uses the NUMPIXELS variable to define how many pixels
//The second argument uses the PIN variable to define the pin
Adafruit_NeoPixel puddlepixels(NUMPIXELS, PUDDLEPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip(NUMPIXELS, STRIPPIN, NEO_GRB + NEO_KHZ800);


//-------------------------------------------------------------------

void setup() {

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

//This line initializes the NeoPixel object (REQUIRED)
  puddlepixels.begin(); 
  strip.begin();

  //This segment sets variables for the ramp functions
  //The first argument sets the max value of the ramp, while the second sets the speed
  //The third argument sets the interpolation mode and the fourth sets the direction (see the documentation link above for these) 
  //The first line sets the brightness fade
  //Some Math To calculate so that the pixels start at the same place each time
  myRamp.go(255, DELAYVAL*(NUMPIXELS+1), LINEAR, LOOPBACKWARD);    
    myRamp3.go(255, DELAYVAL*(NUMPIXELS+1), LINEAR, LOOPBACKWARD);    

  //The second line sets the blue value fade
  myRamp2.go(200, 1000, LINEAR, LOOPFORWARD);    

}

//-------------------------------------------------------------------

void loop() {

PuddlePixels();

//delay(200);

//Invokes the Pixelfall animation
Pixelfall();

}

//-------------------------------------------------------------------

//Custom Functions

void PuddlePixels(){

  puddlepixels.clear(); // Set all pixel colors to 'off'


  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<1; i++) { // For each pixel...

     for( int i = 0; i<NUMPIXELS; i++){
        puddlepixels.setPixelColor(i, puddlepixels.Color(0, 0, 25));

            puddlepixels.setBrightness(myRamp3.update());

        puddlepixels.show();



    //pixels.setBrightness(100);

    //puddlepixels.show();   // Send the updated pixel colors to the hardware.

    //delay(200); // Pause before next pass through loop
    }   

        //delay(10);
    
  }
        delay(10);

}

void Pixelfall(){

  strip.clear(); // Set all pixel colors to 'off'


  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    //This line makes the blue get slightly deeper as the Brightness of the strip fades
    strip.setPixelColor(i, strip.Color(10, 10, myRamp2.update()+50));
    //pixels.setPixelColor(i, pixels.Color(10, 10, 150));

    //pixels.setBrightness(100);

    strip.setBrightness(myRamp.update());



    strip.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL);
  }

}
