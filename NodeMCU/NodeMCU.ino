#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "homenetwork";
const char *pass = "homenetwork";

ESP8266WebServer server(80);
const int reverseRelay = D2;

void homePage() {
  server.send(200, "text/html",
"<!DOCTYPE html>"
"<html>"
  "<head>"
    "<title>LED Controller</title>"
    "<style>"
      "div {"
        "display: inline-block;"
        "width: 80vw;"
        "position: absolute;"
        "top: 25%;"
        "left: 50%;"
        "transform: translate(-50%, -50%);"
      "}"
      "h1 {"
        "font-size: 3.6rem;"
      "}"
      "button {"
        "margin: 0 1.8rem;"
        "border: 0;"
        "border-radius: 0.3rem;"
        "padding: 1rem;"
        "font-size: 1rem;"
        "font-weight: bolder;"
        "color: white;"
        "background-color: #4caf50;"
      "}"
      "button:active,"
      "button:hover {"
        "background-color: lightcoral;"
      "}"
      "button:disabled {"
        "color: black;"
        "background-color: silver;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<div>"
      "<h1>Press a button</h1>"
      "<button onclick=\"window.location.href='/on'\">Turn ON</button>"
      "<button onclick=\"window.location.href='/off'\">Turn OFF</button>"
    "</div>"
  "</body>"
"</html>"
);
}

void handleOn() {
  digitalWrite(reverseRelay, LOW);
  server.send(200, "text/html",
"<!DOCTYPE html>"
"<html>"
  "<head>"
    "<title>LED Controller</title>"
    "<style>"
      "div {"
        "display: inline-block;"
        "width: 80vw;"
        "position: absolute;"
        "top: 25%;"
        "left: 50%;"
        "transform: translate(-50%, -50%);"
      "}"
      "h1 {"
        "font-size: 3.6rem;"
      "}"
      "button {"
        "margin: 0 1.8rem;"
        "border: 0;"
        "border-radius: 0.3rem;"
        "padding: 1rem;"
        "font-size: 1rem;"
        "font-weight: bolder;"
        "color: white;"
        "background-color: #4caf50;"
      "}"
      "button:active,"
      "button:hover {"
        "background-color: lightcoral;"
      "}"
      "button:disabled {"
        "color: black;"
        "background-color: silver;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<div>"
      "<h1>Press a button</h1>"
      "<button onclick=\"window.location.href='/on'\" disabled>Turn ON</button>"
      "<button onclick=\"window.location.href='/off'\">Turn OFF</button>"
    "</div>"
  "</body>"
"</html>"
  );
}

void handleOff() {
  digitalWrite(reverseRelay, HIGH);
  server.send(200, "text/html",
"<!DOCTYPE html>"
"<html>"
  "<head>"
    "<title>LED Controller</title>"
    "<style>"
      "div {"
        "display: inline-block;"
        "width: 80vw;"
        "position: absolute;"
        "top: 25%;"
        "left: 50%;"
        "transform: translate(-50%, -50%);"
      "}"
      "h1 {"
        "font-size: 3.6rem;"
      "}"
      "button {"
        "margin: 0 1.8rem;"
        "border: 0;"
        "border-radius: 0.3rem;"
        "padding: 1rem;"
        "font-size: 1rem;"
        "font-weight: bolder;"
        "color: white;"
        "background-color: #4caf50;"
      "}"
      "button:active,"
      "button:hover {"
        "background-color: lightcoral;"
      "}"
      "button:disabled {"
        "color: black;"
        "background-color: silver;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<div>"
      "<h1>Press a button</h1>"
      "<button onclick=\"window.location.href='/on'\">Turn ON</button>"
      "<button onclick=\"window.location.href='/off'\" disabled>Turn OFF</button>"
    "</div>"
  "</body>"
"</html>"
  );
}

void setup() {
  pinMode(reverseRelay, OUTPUT);
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected sucessfully!");
  IPAddress localIP = WiFi.localIP();
  Serial.print("Node MCU IP: "); Serial.println(localIP);

  server.on("/", homePage);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
