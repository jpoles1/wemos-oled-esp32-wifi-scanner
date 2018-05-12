#include "WiFi.h"

#include <Wire.h>
#include "SSD1306.h"
#include <bits/stdc++.h>

SSD1306  display(0x3c, 5, 4);

void setup(){
    display.init();
    // display.flipScreenVertically();
    display.setContrast(255);
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}
void displayStringVector(std::vector <std::string> display_data){
  display.setLogBuffer(5, 30);
  for (std::vector<std::string>::iterator it = display_data.begin() ; it != display_data.end(); ++it){
    display.clear();
    // Print to the screen
    std::string str = *it;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    Serial.println(cstr);
    display.println(cstr);
    delete [] cstr;
    // Draw it to the internal screen buffer
    display.drawLogBuffer(0, 0);
    // Display it on the screen
    display.display();
    delay(500);
  }
}
void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
        display.setLogBuffer(5, 30);
        for (int i = 0; i < n; ++i) {
          display.clear();
          // Print to the screen
          display.print(i + 1);
          display.print(": ");
          display.print(WiFi.SSID(i));
          display.print(" (");
          display.print(WiFi.RSSI(i));
          display.print(")");
          display.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          // Draw it to the internal screen buffer
          display.drawLogBuffer(0, 0);
          // Display it on the screen
          display.display();
          delay(500);
        }
    }
    std::vector <std::string> display_data;
    display_data.push_back("Blue");
    display_data.push_back("Red");
    display_data.push_back("Orange");
    display_data.push_back("Yellow");
    displayStringVector(display_data);
    // Wait a bit before scanning again
    delay(5000);
}