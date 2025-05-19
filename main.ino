#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7      // Define the pin to which the DHT11 is connected
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the button pin
const int buttonPin = 6;

// Define state variable to track the current function
int currentState = 0;

// celcius icon
byte degreeC[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.createChar(1, degreeC);
  lcd.backlight();
  
//Welcome
  lcd.setCursor(4, 0);
    lcd.print("WELCOME!");
    lcd.setCursor(2, 1);
    //lcd.print("------------");
    //delay(2000);
    for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print("-");
    delay(100);
  }
  delay(500);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(32));
    
    delay(100);
  }
    
//Team Robo Yogies
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("by team");
    lcd.setCursor(2, 1);
    lcd.print("Robo Yogies");
    delay(2000);
   // lcd.clear();
    //delay(50);

//Transition animation
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(255));
    lcd.setCursor(i, 1);
    lcd.write(byte(255));
    delay(100);
  }
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(32));
    lcd.setCursor(i, 1);
    lcd.write(byte(32));
    
    delay(100);
  }
  // Set up the button pin as INPUT
  pinMode(buttonPin, INPUT);
}


void loop() 
{

  
  
  // Read the state of the button
  int buttonState = digitalRead(buttonPin);
  // Check button press and update state
  if (buttonState == HIGH) {
    delay(50); // Debounce delay
    currentState = (currentState + 1) % 3;// Cycle between 0, 1, and 2
  }

  // Execute the appropriate function based on the current state
  switch (currentState) {
    case 0:
      displayTempHum();
      break;
    case 1:
      displayTemp();
      break;
    case 2:
      displayHum();
      break;
  }
}


  
  
void displayTempHum() {

// Reading humidity and temperature values
  int hum = dht.readHumidity();
  int temp = dht.readTemperature(); 
  int t = temp;
  int h = hum;
  
  // Check if the readings are valid
  if (!isnan(hum) && !isnan(temp)) {
    // Display humidity and temperature on the LCD
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.print("% ");

    lcd.setCursor(0, 1);
    lcd.print("Temp    : ");
    lcd.print(temp);
    lcd.write(1);
    lcd.print("C");

    // Print values to the Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%, Temperature: ");
    Serial.print(temp);
    Serial.println("C");
     delay(200);
     
  }
        else {
        Serial.println("Failed to read from DHT11 sensor!");
        lcd.setCursor(5,1);
        lcd.print("sensor");
        lcd.setCursor(2,1);
        lcd.print("not detected");
        delay(10000);
       }
       if (hum =! h){
        lcd.clear();
        h = hum;
       }
       if (hum = 0){
        lcd.setCursor(5,1);
        lcd.print("sensor");
        lcd.setCursor(2,1);
        lcd.print("not detected");
        delay(10000);
       }
}

      
void displayTemp() {
  float temp = dht.readTemperature();
  float t=temp;
  lcd.setCursor(0, 0);
  lcd.print("TEMP  :");
  lcd.print(temp);
  lcd.write(1);
  lcd.print("C    ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(10);
  
       if (temp =! t){
        lcd.clear();
        t = temp;
       }
}


void displayHum() {
  float hum = dht.readHumidity();
  float h=hum;
  lcd.setCursor(0, 0);
  lcd.print("HUMIDITY: ");
  lcd.print(hum);
  lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(10);
  
       if (hum =! h){
        lcd.clear();
        h = hum;
       }
}
