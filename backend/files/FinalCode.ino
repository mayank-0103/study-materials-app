#include <WiFi.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Mayank's A15";
const char* password = "1234567890";

// LED GPIOs
const int ledPins[] = {12, 13, 14};

// Create web server on port 80
WebServer server(80);

// LED states
bool ledStates[] = {false, false, false};

String generateHTML() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta charset='utf-8'>
      <title>ESP32 LED Control</title>
      <style>
        body {
          background: linear-gradient(135deg, #74ebd5 0%, #ACB6E5 100%);
          font-family: 'Segoe UI', Arial, sans-serif;
          color: #222;
          text-align: center;
          margin: 0;
          padding: 0;
        }
        h2 {
          margin-top: 40px;
          color: #333;
          letter-spacing: 2px;
        }
        .led-container {
          display: flex;
          justify-content: center;
          gap: 40px;
          margin-top: 40px;
        }
        .led-card {
          background: #fff;
          border-radius: 20px;
          box-shadow: 0 4px 16px rgba(0,0,0,0.12);
          padding: 30px 40px;
          min-width: 200px;
          transition: transform 0.2s;
        }
        .led-card:hover {
          transform: translateY(-8px) scale(1.03);
        }
        .led-status {
          font-size: 1.3em;
          margin-bottom: 18px;
        }
        .led-on {
          color: #27ae60;
          font-weight: bold;
        }
        .led-off {
          color: #c0392b;
          font-weight: bold;
        }
        button {
          font-size: 22px;
          padding: 12px 28px;
          border: none;
          border-radius: 8px;
          background: linear-gradient(90deg, #36d1c4 0%, #5b86e5 100%);
          color: #fff;
          cursor: pointer;
          box-shadow: 0 2px 8px rgba(44,62,80,0.12);
          transition: background 0.2s, transform 0.2s;
        }
        button:hover {
          background: linear-gradient(90deg, #5b86e5 0%, #36d1c4 100%);
          transform: scale(1.07);
        }
      </style>
      <script>
        function toggleLED(idx) {
          let url = '/led' + (idx+1);
          if(idx === 1) url = '/doorlock';
          fetch(url)
            .then(response => response.text())
            .then(html => {
              document.open();
              document.write(html);
              document.close();
            });
        }
      </script>
    </head>
    <body>
      <h2>ESP32 LED Control Panel</h2>
      <div class='led-container'>
  )rawliteral";

  for (int i = 0; i < 3; i++) {
    html += "<div class='led-card'>";
    html += "<div class='led-status ";
    if (i == 1) {
      // Door lock status
      html += ledStates[i] ? "led-on'>LOCKED" : "led-off'>UNLOCKED";
    } else {
      html += ledStates[i] ? "led-on'>ON" : "led-off'>OFF";
    }
    html += "</div>";
    if (i == 1) {
      html += "<div style='margin-bottom:12px;font-weight:bold;font-size:1.1em;'>DOOR LOCK</div>";
      html += "<button style='background:linear-gradient(90deg,#ff512f 0%,#dd2476 100%);font-size:24px;' onclick='toggleLED(" + String(i) + ")'>";
      html += ledStates[i] ? "Unlock Door" : "Lock Door";
      html += "</button>";
    } else {
      html += "<div style='margin-bottom:12px;'>LED " + String(i+1) + "</div>";
      html += "<button onclick='toggleLED(" + String(i) + ")'>Toggle LED " + String(i+1) + "</button>";
    }
    html += "</div>";
  }

  html += R"rawliteral(
      </div>
      <div style='margin-top:40px;color:#888;font-size:0.95em;'>ESP32 Web Server &copy; 2025</div>
    </body>
    </html>
  )rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", generateHTML());
}
void toggleLED(int index) {
  ledStates[index] = !ledStates[index];
  digitalWrite(ledPins[index], ledStates[index] ? HIGH : LOW);
  server.send(200, "text/html", generateHTML());
}
void setup() {
  Serial.begin(115200);

  // Set LED pins as output
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());
  // Set up server routes
  server.on("/", handleRoot);
  server.on("/led1", []() { toggleLED(0); });      // LED 1
  server.on("/doorlock", []() { toggleLED(1); });  // Door Lock (was led2)
  server.on("/led3", []() { toggleLED(2); });      // LED 3

  server.begin();
  Serial.println("Server started");
}
void loop() {
  server.handleClient();
}