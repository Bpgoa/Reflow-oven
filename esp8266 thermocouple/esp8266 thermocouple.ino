#include <SerialESP8266wifi.h>
#include <Adafruit_ESP8266.h>
#include <max6675.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <ESP_Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Our HTML webpage contents

#define OLED_RESET 4

int ktcSO = 12;
int ktcCS = 13;
int ktcCLK = 14;

//SSID and Password of your WiFi router
const char* ssid = "pi";
const char* password = "RockRock";

ESP8266WebServer server(80); //Server on port 80


MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
Adafruit_SSD1306 display(OLED_RESET);

//===============================================================
// This routine is executed when you open main webpage in browser
//===============================================================

void handleRoot() {
	String s = MAIN_page; //Read HTML contents
	
	server.send(200, "text/html", s); //Send web page
}


//===============================================================
// This routine is executed when you request data for Temp in C
//===============================================================

void handleOvenTempC() {
	float a = ktc.readCelsius();
	String tempValue = String(a);
	server.send(200, "text/plane", tempValue); //Send web page
}


//==============================================================
//                  SETUP
//==============================================================

void setup() {

	// Starting Serial debugger code

	Serial.begin(9600);
	delay(500);
	Serial.println("Setup Started");


	// starting OLED server

	display.begin(SSD1306_SWITCHCAPVCC, 0x78 >> 1);
	display.display();
	delay(2000);
	display.clearDisplay();	


	// Setup text and size on oled

	display.setTextSize(1);
	display.setCursor(5, 1);
	display.setTextColor(WHITE);



	// Attempt to connect to your WiFi router
	
	WiFi.begin(ssid, password);     
	Serial.println("WiFi Connecting");
	display.print("WiFi connecting");
	display.display();

	// Wait for connection

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
		display.print(".");
		display.display();
	}


	// If connection successful show IP address

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());  //IP address assigned to your ESP

	display.clearDisplay();
	display.setTextSize(1);

	display.setCursor(5, 1);
	display.print("The SSID is ");

	display.setCursor(5, 10);
	display.print(ssid);

	display.setCursor(5, 20);
	display.print("The IP is ");

	display.setCursor(5, 30);
	display.print(WiFi.localIP());

	display.display();
	delay(10000);
	display.clearDisplay();

	// Start Web server

	server.on("/", handleRoot);      //Which routine to handle at root location
	server.on("/readOvenTempC", handleOvenTempC); //routine to sent temp back to server
	server.begin();                  //Start server
	Serial.println("HTTP server started");
}


//==============================================================
//                     LOOP
//==============================================================

void loop() {


	// Handle client requests
	
	server.handleClient();          


	// Read the temprature probe data

	float DC = ktc.readCelsius();
	float DF = ktc.readFahrenheit();


	// Write to serial monitor

	Serial.print("C = ");
	Serial.print(ktc.readCelsius());
	Serial.print("\t F = ");
	Serial.println(ktc.readFahrenheit());
	

	// Write to Oled display
	
	displayData();


	// wait a sec before doing it all again 

	delay(1000);
}

void displayData() {
	display.setTextSize(1);
	display.setCursor(15, 1);
	display.println("Ade's Reflow Oven");

	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(18, 20);
	display.print((char)248);
	display.print("C:");
	display.print(ktc.readCelsius());


	display.setCursor(18, 40);
	display.print((char)248);
	display.print("F:");
	display.println(ktc.readFahrenheit());
	display.display();
	display.clearDisplay();
}