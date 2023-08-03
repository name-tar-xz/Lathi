#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "F13";  //ENTER YOUR WIFI SETTINGS
const char *password = "DeezFuckingNuts";  //ENTER YOUR WIFI PASSWORD


const char *host = "aeapi.bumblebee13.repl.co";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "B4 36 2A 5B 51 D2 7C F2 E0 AA B2 55 BF 14 48 9A 41 1E 46 06";

void setup() {

    Serial.begin(115200);
    WiFi.mode(WIFI_OFF);//Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA);//Only Station No AP, This line hides the viewing of ESP as wifi hotspot
    WiFi.begin(ssid, password);//Connect to your WiFi router
    Serial.println("");
    //
    Serial.print("Connecting");
// Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
//If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void loop() {
    WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
    Serial.println(host);
    Serial.printf("Using fingerprint '%s'\n", fingerprint);
    httpsClient.setFingerprint(fingerprint);
    httpsClient.setTimeout(15000); // 15 Seconds
    delay(1000);
    Serial.print("HTTPS Connecting");
    int r=0; //retry counter
    while((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
        delay(100);
        Serial.print(".");
        r++;
    }
    if(r==30) {
        Serial.println("\nConnection failed");
    }
    else {
        Serial.println("\nConnected to web");
    }
    String Link;
    Link = "/api/setData/00000000\\n1111111111111111\\n0000000000000000\\n1111111111111111";
    Serial.print("requesting URL: ");
    Serial.println(host+Link);
    httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n");
    Serial.println("request sent");
    while (httpsClient.connected()) {
        String line = httpsClient.readStringUntil('\n');
        if (line == "\r") {
            Serial.println("Headers received");
            break;
        }
    }

}
