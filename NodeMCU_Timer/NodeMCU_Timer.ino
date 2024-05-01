#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "testnetwork";
const char *pass = "testnetwork";
ESP8266WebServer server(80);

void serveIndex() {
server.send(200, "text/html",
"<!DOCTYPE html>"
"<html lang=\"en\">"
  "<head>"
    "<meta charset=\"UTF-8\" />"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />"
    "<title>Node MCU</title>"
    "<style>"
      "body {"
        "background-color: silver;"
        "font-size: larger;"
      "}"
      "form {"
        "border-radius: 0.4rem;"
        "padding: 2rem 4rem 0 4rem;"
        "display: inline-block;"
        "position: absolute;"
        "top: 40%;"
        "left: 50%;"
        "transform: translate(-50%, -50%);"
        "background-color: white;"
      "}"
      "h1 {"
        "margin: 0;"
        "text-align: center;"
      "}"
      "section {"
        "margin-top: 1rem;"
        "border-top: 2px dashed silver;"
        "border-bottom: 2px dashed silver;"
        "padding-top: 2rem;"
      "}"
      "input {"
        "padding: 0.5rem;"
        "width: 12rem;"
        "border: 1px solid black;"
        "border-radius: 0.2rem;"
        "font-size: 1rem;"
        "text-align: center;"
      "}"
      "button {"
        "margin: 2rem auto;"
        "border: 0;"
        "border-radius: 0.2rem;"
        "padding: 0.6rem 1.2rem;"
        "font-size: 0.9rem;"
        "color: white;"
        "background-color: #4caf50;"
      "}"
      "button:active,"
      "button:hover {"
        "background-color: lightcoral;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<form>"
      "<h1>Timer</h1>"
      "<section>"
        "<label>Minutes:&emsp;</label"
        "><input id=\"minutesInput\" type=\"number\" value=\"0\" min=\"0\" max=\"7\" /> <br /><br />"
        "<label>Seconds:&emsp;</label"
        "><input id=\"secondsInput\" type=\"number\" value=\"0\" min=\"0\" max=\"60\" /> <br /><br />"
      "</section>"
      "<button onclick=\"timer()\">Start</button>"
    "</form>"
    "<script>"
      "function timer() {"
        "var minutesInput = parseInt("
          "document.getElementById(\"minutesInput\").value"
        ");"
        "var secondsInput = parseInt("
          "document.getElementById(\"secondsInput\").value"
        ");"
        "var totalSeconds = minutesInput * 60 + secondsInput;"
        "sendToNodeMCU(totalSeconds);"
      "}"
      "function sendToNodeMCU(seconds) {"
        "var xhr = new XMLHttpRequest();"
        "xhr.open(\"POST\", \"/setTimer\", true);"
        "xhr.setRequestHeader("
          "\"Content-Type\","
          "\"application/x-www-form-urlencoded\""
        ");"
        "xhr.onreadystatechange = function () {"
          "if (xhr.readyState === 4 && xhr.status === 200) {"
            "console.log(\"Data sent successfully\");"
          "}"
        "};"
        "xhr.send(seconds);"
      "}"
    "</script>"
  "</body>"
"</html>"
);
}

const int ledPins[9] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};
void start() {
  for(int j = 0; j < 3; j++) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < 9; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(500);
  }
}
void blinkLEDs(int number) {
  for (int i = 0; i < 9; i++) {
    digitalWrite(ledPins[i], (number >> i) & 0x01);
  }
}
void end() {
  for(int j = 0; j < 6; j++) {
    for (int i = 0; i < 9; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < 9; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(500);
  }
}

void handleSetTimer() {
  if (server.hasArg("plain")) {
    String plainData = server.arg("plain");
    int seconds = atoi(plainData.c_str()); 
    Serial.println("Received: " + String(seconds) + "sec");

    start();
    while (seconds >= 0) {
      blinkLEDs(seconds);
      delay(1000);
      seconds--;
    }
    end();
    
    server.send(200, "text/plain", "OK");
  }
}

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

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

  server.on("/", serveIndex);
  server.on("/setTimer", HTTP_POST, handleSetTimer);
  server.begin();
}

void loop() {
  server.handleClient();
}
