#include <DHT11.h>
#include <SPI.h>
#include <SD.h>

// Pin definitions
#define DHTPIN 2
#define SD_CS 10   // Chip select pin for SD card

DHT11 dht11(DHTPIN);


File myFile;

void setup() {
  Serial.begin(9600);

  // Wait for Serial (needed for some boards like Leonardo)
  while (!Serial) {
    ;
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed!");
    while (1);  // Stop here if SD fails
  }

  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    Serial.println("Writing to test.txt...");

    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");

    for (int i = 0; i < 20; i++) {
      myFile.println(i);
    }

    myFile.close();
    Serial.println("done.");
  } else {
    // If the file didn't open, print an error
    Serial.println("error opening test.txt");
  }
}

void loop() {
  int temperature = 0;
  int humidity = 0;

  // Read DHT11 data
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {  // Successful read
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read from DHT11");
  }

  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {

    myFile.println("Starting Humidity readings");
    myFile.println("Temp: ");
    myFile.print(temperature);
    Serial.println(" C\tHumidity: ");
    Serial.print(humidity);
    Serial.print(" %");

    myFile.close();


  delay(1000);
}
