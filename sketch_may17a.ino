#include <SPI.h>

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#include <Servo.h>

#include "RTClib.h"


RTC_DS3231 rtc;


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


#define SCREEN_WIDTH 128 // OLED display width, in pixels

#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

// The pins for I2C are defined by the Wire-library.

// On an arduino UNO:       A4(SDA), A5(SCL)

// On an arduino MEGA 2560: 20(SDA), 21(SCL)

// On an arduino LEONARDO:   2(SDA),  3(SCL), ...

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards


int home = 20;    // variable to store the servo position

int fire = 160;

int min = 0;

int hour = 0;


void setup() {

  Serial.begin(9600);

  pinMode(2,OUTPUT);


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {

    Serial.println(F("SSD1306 allocation failed"));

    for(;;); // Don't proceed, loop forever

  }


  // Show initial display buffer contents on the screen --

  // the library initializes this with an Adafruit splash screen.

  display.display();

  delay(2000); // Pause for 2 seconds


  // Clear the buffer

  display.clearDisplay();


  // Draw a single pixel in white

  display.drawPixel(10, 10, SSD1306_WHITE);


  // Show the display buffer on the screen. You MUST call display() after

  // drawing commands to make them visible on screen!

  display.display();

  delay(2000);



  myservo.attach(5);  // attaches the servo on pin 9 to the servo object


  #ifndef ESP8266

  while (!Serial); // wait for serial port to connect. Needed for native USB

#endif


  if (! rtc.begin()) {

    Serial.println("Couldn't find RTC");

    Serial.flush();

    while (1) delay(10);

  }


  if (rtc.lostPower()) {

    Serial.println("RTC lost power, let's set the time!");

    // When time needs to be set on a new device, or after a power loss, the

    // following line sets the RTC to the date & time this sketch was compiled

    rtc.adjust(DateTime(F(_DATE), F(TIME_)));

    // This line sets the RTC with an explicit date & time, for example to set

    // January 21, 2014 at 3am you would call:

    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }


}


void loop() {

  digitalWrite(2,1);

  DateTime now = rtc.now();

  Serial.print(now.hour(), DEC);

  Serial.print(':');

  Serial.print(now.minute(), DEC);

  Serial.print(':');

  min = now.minute();

  hour = now.hour();

  Serial.print(now.second(), DEC);

  Serial.println();


  display.clearDisplay();


  display.setTextSize(1); // Draw 2X-scale text

  display.setTextColor(SSD1306_WHITE);

  display.setCursor(20, 0);

  display.println("Waktu Sekarang:");

  display.setCursor(29, 35);

  display.println("Waktu Sahur:");

  display.setTextSize(2);

  display.setCursor(20, 12);

  display.print(now.hour());

  display.print(':');

  display.print(now.minute());

  display.print(':');

  display.print(now.second());

  display.setCursor(30, 47);

  display.print("13:10");

  display.display();      // Show initial text

  delay(100);

  //display.print(min);

 

                        // waits 15 ms for the servo to reach the positionlllllllll

   if(min==10&&hour==13){

 

    digitalWrite(2,0);

    delay(100);

    display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text

  display.setTextColor(SSD1306_WHITE);

  display.setCursor(20, 0);

  display.println("Sahur!!");

 

  display.display();      // Show initial text

    myservo.write(fire);              // tell servo to go to position in variable 'pos'

    delay(1000);        

    myservo.write(home);              // tell servo to go to position in variable 'pos'

    delay(1000);

    }

   

    else{myservo.write(home);              // tell servo to go to position in variable 'pos'

    delay(100); }             // waits 15 ms for the servo to reach the position

 

}
