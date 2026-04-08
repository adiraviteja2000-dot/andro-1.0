#include &lt;WiFi.h&gt;
#include &lt;HTTPClient.h&gt;

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Pins
#define MIC_PIN 34
#define SPEAKER_PIN 25

void setup() {
  Serial.begin(115200);

  pinMode(MIC_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void loop() {
  int micValue = analogRead(MIC_PIN);

  // Simple voice detection
  if (micValue > 2000) {
    Serial.println("Voice Detected!");

    String response = askServer("Hello Andro");
    Serial.println(response);

    speak();
    delay(3000);
  }
}

// Send request to server
String askServer(String question) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin("http://api.example.com/ask?q=" + question);
    int httpCode = http.GET();

    if (httpCode &gt; 0) {
      String payload = http.getString();
      http.end();
      return payload;
    }
  }
  return "No response";
}

// Simple speaker output
void speak() {
  tone(SPEAKER_PIN, 1000);
  delay(300);
  noTone(SPEAKER_PIN);
}