
#include <FastLED.h>
#include "Ticker.h"
#include "ascii.h"
#include "position.h"
#include "charImage.h"
#include "textRoller.h"
#include "constant.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>




//------------------------------------------VARIABLE DECLARATION----------------------------------------------//
CRGB leds[TOTAL_MATRIX_LEDS];
TextRoller textRoller;


void textRollerHandler();
Ticker textRollerTicker(textRollerHandler, textRoller.interval);

void printMessage();
Ticker printTicker(printMessage, 1000);

//------------ web server variable -----------------//
// const char* ssid = "huawei";
// const char* password = "12345678";

const char* ssid = "SpectrumSetup-2D";
const char* password = "bluecrown668";
const char* MESSAGE_PARAMETER = "message";
const char* COLOR_PARAMETER = "color";
const char* BRIGHTNESS_PARAMETER = "brightnessFactor";





ESP8266WebServer server(80);

IPAddress ip(192, 168, 1, 133);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);




//------------------------------------------FUNCTION DECLARATION----------------------------------------------//
int positionToNumber(int rowIndex, int colIndex);
String mainPage();

void handleRoot();

void handleNotFound() {

  server.send(404, "text/html", "not found page");
}






void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, TOTAL_MATRIX_LEDS);  // GRB ordering is assumed
  Serial.begin(115200);
  //----------------------web server configuration here--------------------------//
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");


  FastLED.clear();
  // configure the image
  textRollerTicker.start();
  printTicker.start();
}



void loop() {
  textRollerTicker.update();

  // printTicker.update();

  server.handleClient();
}



//------------------------------------------FUNCTION DEFINITION----------------------------------------------//




int positionToNumber(int rowIndex, int colIndex) {
  int matrixBlockOffset = colIndex / SINGLE_MATRIX_COLS;
  rowIndex = rowIndex % SINGLE_MATRIX_ROWS;
  colIndex = colIndex % SINGLE_MATRIX_COLS;
  int ledNum = 0;

  if (rowIndex % 2 == 0) {
    ledNum = (SINGLE_MATRIX_ROWS - rowIndex - 1) * SINGLE_MATRIX_ROWS + (SINGLE_MATRIX_COLS - colIndex - 1);
    ledNum += matrixBlockOffset * SINGLE_MATRIX_LEDS;
  } else {
    ledNum = (SINGLE_MATRIX_ROWS - rowIndex - 1) * SINGLE_MATRIX_ROWS + colIndex;
    ledNum += matrixBlockOffset * SINGLE_MATRIX_LEDS;
  }
  return ledNum;
}

// function convert one dimension char array index to a 2 dimension position
Position indexToPosition(int arraySize, int index) {

  int cols = arraySize / ASCII_ROWS;


  int r = index / cols;
  int c = index % cols;

  Position pos;
  pos.row = r;
  pos.col = c;

  return pos;
}

int calcLedNumFromCharBinaryIndex(int binaryCharArraySize, int index) {

  Position pos = indexToPosition(binaryCharArraySize, index);

  return positionToNumber(pos.row, pos.col);
}


void textRollerHandler() {


  if (textRoller.step >= textRoller.totalOffsetCols) {
    textRoller.setStep(0);
    if (textRoller.isRandomColor == true) {
      textRoller.setRedValue(random(0, 10));
      textRoller.setGreenValue(random(0, 10));
      textRoller.setBlueValue(random(0, 10));
    }
  }

  // saving time purpose, direct adding 1 to step
  textRoller.step++;

  // Serial.println(textRoller.step);

  FastLED.clear();
  renderFrame();
  FastLED.show();
}

void renderFrame() {
  for (int i = 0; i < textRoller.message.length(); i++) {  // looping each image
    CharImage* image = textRoller.charImagesList.get(i);
    for (int j = 0; j < image->size; j++) {
      if (image->imagePtr[j] == true) continue;

      Position pos = indexToPosition(image->size, j);

      int newRow = pos.row + textRoller.verticalOffset;
      int newCol = pos.col + SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX + (image->offset) - textRoller.step;

      if (newRow < 0 || newRow >= TOTAL_MATRIX_ROWS) continue;
      if (newCol < 0 || newCol >= TOTAL_MATRIX_COLS) continue;

      int ledNum = positionToNumber(newRow, newCol);
      leds[ledNum] = CRGB(textRoller.redValue * textRoller.brightnessFactor, textRoller.greenValue* textRoller.brightnessFactor, textRoller.blueValue* textRoller.brightnessFactor);

    }
  }
}
// FastLED.show();
// delay(textRoller.interval);
// FastLED.clear();


String mainPage() {
  String page = "<!DOCTYPE HTML><html><head>";
  page += "<title>ESP Input Form</title>";
  page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  page += "</head><body>";


  // Message Form to update message
  page += "<form  action = \"/\"  method=\"get\">";
  page += "Message: <input type=\"text\" name=\"";
  page += MESSAGE_PARAMETER;
  page += "\">";
  page += "<input type=\"submit\" value=\"Submit\">";
  page += "&nbsp current message: &nbsp";
  page += textRoller.message;
  page += "</form><br>";

  // Colof Form to update color
  page += "<form  action = \"/\"  method=\"get\">";
  page += "Color: <input type=\"text\" name=\"";
  page += COLOR_PARAMETER;
  page += "\">";
  page += "<input type=\"submit\" value=\"Submit\">";
  page += "&nbsp current Color: &nbsp";
  page += "Color Place holder";
  page += "</form><br>";
  page += "</form><br>";



  page += "<form  action = \"/\"  method=\"get\">";
  page += "Brightness: <input type=\"text\" name=\"";
  page += BRIGHTNESS_PARAMETER;
  page += "\">";
  page += "<input type=\"submit\" value=\"Submit\">";
  page += "&nbsp current brightness: &nbsp";
  page += textRoller.brightnessFactor;
  page += "</form><br>";
  page += "</form><br>";

  // page += "<form  action = \"/\"  method=\"get\">";
  // page += "input3: <input type=\"text\" name=\"input3\">";
  // page += "<input type=\"submit\" value=\"Submit\">";
  // page += "</form>";
  // page += "</body></html>";

  return page;
}

void handleRoot() {

  String msg = server.arg(MESSAGE_PARAMETER);

  if (msg.length() != 0) {
    textRoller.setMessage(msg);
  }

  String color = server.arg(COLOR_PARAMETER);
  if (color.length() != 0) {

    color.toLowerCase();
    color.trim();
    textRoller.isRandomColor = false;

    if (color.equals("red")) {
      textRoller.setRedValue(10);
      textRoller.setGreenValue(0);
      textRoller.setBlueValue(0);
    } else if (color.equals("green")) {
      textRoller.setRedValue(0);
      textRoller.setGreenValue(10);
      textRoller.setBlueValue(0);
    } else if (color.equals("blue")) {
      textRoller.setRedValue(0);
      textRoller.setGreenValue(0);
      textRoller.setBlueValue(10);
    } else {
      textRoller.isRandomColor = true;
    }
  }

  String brightness = server.arg(BRIGHTNESS_PARAMETER);
  brightness.trim();


  if(brightness.length() != 0){
      bool isStringNumber = true;
      for(int i = 0 ;i < brightness.length(); i++){
         if (!isDigit(brightness.charAt(i))){
           isStringNumber = false;
           break;
         }
      }

      if(isStringNumber){
        textRoller.setBrightnessFactor(brightness.toInt());
      }
      
  }


  server.send(200, "text/html", mainPage());  //Send web page
}

void printMessage() {
  textRoller.print();
}
