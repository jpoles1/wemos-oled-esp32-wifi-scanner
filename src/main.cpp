#include "WiFi.h"
#include <esp_wifi.h>

#include <Wire.h>
#include "SSD1306.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>

SSD1306  display(0x3c, 5, 4);

void setup(){
    display.init();
    // display.flipScreenVertically();
    display.setContrast(255);
    display.setLogBuffer(5, 30);

    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}
void displayString(std::string display_data, bool clearScreen = false){
  if(clearScreen == true){
    display.setLogBuffer(5, 30);
  }
  display.clear();
  // Print to the screen
  char *cstr = new char[display_data.length() + 1];
  strcpy(cstr, display_data.c_str());
  Serial.println(cstr);
  display.println(cstr);
  delete [] cstr;
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
  delay(250);
}
void displayStringVector(std::vector <std::string> display_data, bool clearScreen = false){
  if(clearScreen == true){
    display.setLogBuffer(5, 30);
  }
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
    displayString("Scan started...", true);

    // WiFi.scanNetworks will return the number of networks found
    int num_aps = WiFi.scanNetworks();
    displayString("Scan complete!");
    displayString("--------------------");
    if (num_aps == 0) {
        displayString("No networks found");
    } else {
        std::ostringstream ss;
        ss << num_aps << " networks found:";
        displayString(ss.str());
        ss.str("");
        ss << WiFi.SSID(0);
        displayString(ss.str());
        std::vector <std::string> display_data;
        for (int i = 0; i < num_aps; i++) {
          String ssid = WiFi.SSID(i);
          std::ostringstream stringStream;
          stringStream.str("");
          stringStream << i+1 << ": ";
          stringStream << ssid << " ";
          stringStream << "(" << WiFi.RSSI(i) << " db)" ;
          stringStream << (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*";
          display_data.push_back(stringStream.str());
        }
        displayStringVector(display_data);
    }
    // Wait a bit before scanning again
    delay(5000);
}