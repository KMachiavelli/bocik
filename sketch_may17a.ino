#include <ESP8266WiFi.h>
#include "ESP8266WebServer.h"

const char* ssid = "ERYK_GDZIE_JESTES";
const char* password = "ujck1234";
// WiFiServer server(80);  // Set port to 80
ESP8266WebServer server;
String header;  // This storees the HTTP request

const char* myHTML = "<!DOCTYPE HTML><!DOCTYPE html><html><script> const order = (type) => {\
            fetch(`http://192.168.244.98/${type}`);\
        };\
    </script>\
    <body>\
        <button onclick=\"order('forward')\">FORWARD</button>\
        <button onclick=\"order('left')\">LEFT</button>\
        <button onclick=\"order('right')\">RIGHT</button>\
        <button onclick=\"order('back')\">BACK</button>\
        <button onclick=\"order('stop')\">STOP</button>\
    </body>\
</html>";

int d5in1 = 14;
int d6in2 = 12;
int d7in3 = 13;
int d8in4 = 15;

void forward() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, LOW);
}

void back() {
  digitalWrite(d5in1, 0);
  digitalWrite(d6in2, 1);
  digitalWrite(d7in3, 0);
  digitalWrite(d8in4, 1);
}

void left() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  digitalWrite(d7in3, 0);
  digitalWrite(d8in4, 1);
}

void right() {
  digitalWrite(d5in1, 0);
  digitalWrite(d6in2, 1);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, LOW);
}

void stop() {
  digitalWrite(d5in1, 1);
  digitalWrite(d6in2, 1);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, 1);
}

void setup() {
  Serial.begin(9600);
  pinMode(d5in1, OUTPUT);
  pinMode(d6in2, OUTPUT);
  pinMode(d7in3, OUTPUT);
  pinMode(d8in4, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");

  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", myHTML);
  });
  server.on("/forward", forward);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/back", back);
  server.on("/stop", stop);
  server.begin();
}

// digitalWrite(d5in1, 1);
// digitalWrite(d6in2, LOW);
// digitalWrite(d7in3, 1);
// digitalWrite(d8in4, LOW);

// delay(1000);



// delay(1000);

// digitalWrite(d5in1, LOW);
// digitalWrite(d6in2, HIGH);
// digitalWrite(d7in3, HIGH);
// digitalWrite(d8in4, LOW);

// delay(1000);

void loop() {
  server.handleClient();
}
