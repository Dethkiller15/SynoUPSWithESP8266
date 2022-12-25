#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#include <WiFiUdp.h>
WiFiUDP UDP;

#include <WakeOnLan.h>
WakeOnLan WOL(UDP); // Pass WiFiUDP class

// Set WiFi Ccredentials
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASS "YourWiFiPassword"


// Set your Static IP address
IPAddress local_IP(192, 168, 2, 254);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(1, 1, 1, 1);   //optional
IPAddress secondaryDNS(1, 0, 0, 1); //optional


// Set the MAC address of the device you want to use for wake on lan.
const char *WOLMACAddr = "00:00:00:00:00:00"; // Put the MAC Address for the WOL port here.
// Set its IP to check if it is online or not
IPAddress WOLIPAddr(192, 168, 1, 125); // This is the IP for my NAS's eth0 port that has WOL enabled change it so that yours is here instead.




// Do not edit below this line


bool DeviceOnline = "0";

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Starts up WiFi connection
  WiFi_Setup();
  
  // Blink Setup for output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Will see if device attached to mac address is 
  DetectIfDeviceOnlineAndWakeOnLan();
}

void WiFi_Setup() {
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // WiFi Connected
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
  // MAC Address info
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void DetectIfDeviceOnlineAndWakeOnLan() {
  WOL.setRepeat(5, 100);
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
  bool DeviceOnline = Ping.ping(WOLIPAddr, 5);
  if (DeviceOnline) {
    Serial.println("WOL Device shows to be online. Not sending magic packets.");
  } else {
    Serial.println("WOL Device shows to be offline. Sending magic packets.");
    WOL.sendMagicPacket(WOLMACAddr, 7);
    WOL.sendMagicPacket(WOLMACAddr);
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  
  // for blink. Also for this device the voltage is reversed for some reason.
  // 100% just to indicate that the device has power. Nothing else. I may change this later idk.
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (LOW is the voltage level)
  delay(500);                      // wait for half a second
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage HIGH
  delay(1500);                      // wait for a second
}
