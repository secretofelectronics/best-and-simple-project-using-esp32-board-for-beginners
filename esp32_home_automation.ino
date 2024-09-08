#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "enter your ssid";
const char* password = "enter your password";

// Define LED pins
const int led1Pin = 2;   // LED 1 on GPIO 2
const int led2Pin = 4;   // LED 2 on GPIO 4
const int led3Pin = 16;  // LED 3 on GPIO 16
const int led4Pin = 17;  // LED 4 on GPIO 17

// HTML page to control the LEDs
String htmlPage = "<html>\
<head>\
<title>ESP32 LED Control</title>\
</head>\
<body>\
<h1>Control LEDs</h1>\
<p><a href=\"/led1/on\">Turn ON LED 1</a></p>\
<p><a href=\"/led1/off\">Turn OFF LED 1</a></p>\
<p><a href=\"/led2/on\">Turn ON LED 2</a></p>\
<p><a href=\"/led2/off\">Turn OFF LED 2</a></p>\
<p><a href=\"/led3/on\">Turn ON LED 3</a></p>\
<p><a href=\"/led3/off\">Turn OFF LED 3</a></p>\
<p><a href=\"/led4/on\">Turn ON LED 4</a></p>\
<p><a href=\"/led4/off\">Turn OFF LED 4</a></p>\
</body>\
</html>";

WiFiServer server(80); // Create a server that listens on port 80

void setup() {
  // Initialize the LED pins as outputs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);

  // Start with all LEDs off
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led3Pin, HIGH);
  digitalWrite(led4Pin, HIGH);

  // Start the serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Wait until the ESP32 is connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print the ESP32 IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected");
    String request = client.readStringUntil('\r'); // Read the HTTP request
    Serial.println(request);
    client.flush();

    // Send the HTML page to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println(htmlPage);

    // Control LED 1
    if (request.indexOf("/led1/on") != -1) {
      digitalWrite(led1Pin, LOW); // Turn LED 1 on
      Serial.println("LED 1 ON");
    } else if (request.indexOf("/led1/off") != -1) {
      digitalWrite(led1Pin, HIGH);  // Turn LED 1 off
      Serial.println("LED 1 OFF");
    }

    // Control LED 2
    if (request.indexOf("/led2/on") != -1) {
      digitalWrite(led2Pin, LOW); // Turn LED 2 on
      Serial.println("LED 2 ON");
    } else if (request.indexOf("/led2/off") != -1) {
      digitalWrite(led2Pin, HIGH);  // Turn LED 2 off
      Serial.println("LED 2 OFF");
    }

    // Control LED 3
    if (request.indexOf("/led3/on") != -1) {
      digitalWrite(led3Pin, LOW); // Turn LED 3 on
      Serial.println("LED 3 ON");
    } else if (request.indexOf("/led3/off") != -1) {
      digitalWrite(led3Pin, HIGH);  // Turn LED 3 off
      Serial.println("LED 3 OFF");
    }

    // Control LED 4
    if (request.indexOf("/led4/on") != -1) {
      digitalWrite(led4Pin, LOW); // Turn LED 4 on
      Serial.println("LED 4 ON");
    } else if (request.indexOf("/led4/off") != -1) {
      digitalWrite(led4Pin, HIGH);  // Turn LED 4 off
      Serial.println("LED 4 OFF");
    }

    delay(1);
    client.stop(); // Close the connection
    Serial.println("Client Disconnected");
  }
}
