#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "SMPH_4G";
const char* password = "Maan@2021";

// Create web server on port 80
WebServer server(80);

// LED states
bool led1State = false;
bool led2State = false;
bool led3State = false;

// UART2 pins
#define RXD2 16
#define TXD2 17

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  
  // Initialize UART2 for LED control
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Define server routes
  server.on("/", handleRoot);
  server.on("/led1/on", handleLED1On);
  server.on("/led1/off", handleLED1Off);
  server.on("/led2/on", handleLED2On);
  server.on("/led2/off", handleLED2Off);
  server.on("/led3/on", handleLED3On);
  server.on("/led3/off", handleLED3Off);
  
  // Start server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

// Main page HTML
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Led control panel</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    
    body {
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Roboto', 'Helvetica', 'Arial', sans-serif;
      background: #f5f5f7;
      min-height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      padding: 20px;
    }
    
    .container {
      background: white;
      border-radius: 16px;
      box-shadow: 0 4px 24px rgba(0,0,0,0.06);
      padding: 48px 40px;
      max-width: 420px;
      width: 100%;
    }
    
    h1 {
      text-align: center;
      color: #1d1d1f;
      margin-bottom: 48px;
      font-size: 32px;
      font-weight: 600;
      letter-spacing: -0.5px;
    }
    
    .led-control {
      margin: 0 0 24px 0;
      padding: 20px 0;
      border-bottom: 1px solid #e5e5e7;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    
    .led-control:last-child {
      border-bottom: none;
      margin-bottom: 0;
    }
    
    .led-info {
      display: flex;
      flex-direction: column;
      gap: 4px;
    }
    
    .led-label {
      font-size: 17px;
      font-weight: 500;
      color: #1d1d1f;
      letter-spacing: -0.2px;
    }
    
    .led-status {
      font-size: 14px;
      color: #86868b;
    }
    
    /* iOS Toggle Switch */
    .switch {
      position: relative;
      display: inline-block;
      width: 51px;
      height: 31px;
      flex-shrink: 0;
    }
    
    .switch input {
      opacity: 0;
      width: 0;
      height: 0;
    }
    
    .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: #e5e5e7;
      transition: 0.4s;
      border-radius: 31px;
    }
    
    .slider:before {
      position: absolute;
      content: "";
      height: 27px;
      width: 27px;
      left: 2px;
      bottom: 2px;
      background-color: white;
      transition: 0.4s;
      border-radius: 50%;
      box-shadow: 0 2px 4px rgba(0,0,0,0.2);
    }
    
    input:checked + .slider {
      background-color: #34c759;
    }
    
    input:checked + .slider:before {
      transform: translateX(20px);
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Led control panel</h1>
    
    <div class="led-control">
      <div class="led-info">
        <span class="led-label">LED 1</span>
        <span class="led-status">)rawliteral" + String(led1State ? "ON" : "OFF") + R"rawliteral(</span>
      </div>
      <label class="switch">
        <input type="checkbox" id="led1" )rawliteral" + String(led1State ? "checked" : "") + R"rawliteral( onchange="toggleLED(1, this.checked)">
        <span class="slider"></span>
      </label>
    </div>
    
    <div class="led-control">
      <div class="led-info">
        <span class="led-label">LED 2</span>
        <span class="led-status">)rawliteral" + String(led2State ? "ON" : "OFF") + R"rawliteral(</span>
      </div>
      <label class="switch">
        <input type="checkbox" id="led2" )rawliteral" + String(led2State ? "checked" : "") + R"rawliteral( onchange="toggleLED(2, this.checked)">
        <span class="slider"></span>
      </label>
    </div>
    
    <div class="led-control">
      <div class="led-info">
        <span class="led-label">LED 3</span>
        <span class="led-status">)rawliteral" + String(led3State ? "ON" : "OFF") + R"rawliteral(</span>
      </div>
      <label class="switch">
        <input type="checkbox" id="led3" )rawliteral" + String(led3State ? "checked" : "") + R"rawliteral( onchange="toggleLED(3, this.checked)">
        <span class="slider"></span>
      </label>
    </div>
  </div>
  
  <script>
    function toggleLED(ledNum, isChecked) {
      const state = isChecked ? 'on' : 'off';
      fetch('/led' + ledNum + '/' + state)
        .then(response => response.text())
        .then(data => {
          console.log('LED ' + ledNum + ' ' + state);
          document.querySelector('#led' + ledNum).parentElement.parentElement.querySelector('.led-status').textContent = isChecked ? 'ON' : 'OFF';
        })
        .catch(error => console.error('Error:', error));
    }
  </script>
</body>
</html>
)rawliteral";
  
  server.send(200, "text/html", html);
}

// LED 1 ON
void handleLED1On() {
  led1State = true;
  Serial2.println("LED1:ON");
  Serial.println("Sent via UART2: LED1:ON");
  server.send(200, "text/plain", "OK");
}

// LED 1 OFF
void handleLED1Off() {
  led1State = false;
  Serial2.println("LED1:OFF");
  Serial.println("Sent via UART2: LED1:OFF");
  server.send(200, "text/plain", "OK");
}

// LED 2 ON
void handleLED2On() {
  led2State = true;
  Serial2.println("LED2:ON");
  Serial.println("Sent via UART2: LED2:ON");
  server.send(200, "text/plain", "OK");
}

// LED 2 OFF
void handleLED2Off() {
  led2State = false;
  Serial2.println("LED2:OFF");
  Serial.println("Sent via UART2: LED2:OFF");
  server.send(200, "text/plain", "OK");
}

// LED 3 ON
void handleLED3On() {
  led3State = true;
  Serial2.println("LED3:ON");
  Serial.println("Sent via UART2: LED3:ON");
  server.send(200, "text/plain", "OK");
}

// LED 3 OFF
void handleLED3Off() {
  led3State = false;
  Serial2.println("LED3:OFF");
  Serial.println("Sent via UART2: LED3:OFF");
  server.send(200, "text/plain", "OK");
}
