#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

int VOCHTIGHEIDSPIN = 34;  // Bodemvochtigheidssensor (analoge input GPIO34)
int WATERNIVEAUPIN = 35;     // Waterniveausensor (analoge input GPIO35)

int MOTORPIN1 = 27; 
int MOTORPIN2 = 26; 
int MOTORACTIVATIE = 14; 

int vochtigheid = 0; 
int waterniveau = 0;

int teller = 0;

// Netwerk setup (makkelijkst met hotspot)
const char* ssid = "solarplant";
const char* password = "solarplant";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
String phoneNumber = "TEL";
String apiKey = "API"; // Instructies: https://www.callmebot.com/blog/free-api-whatsapp-messages/

void setup() {
  pinMode(MOTORPIN1, OUTPUT);
  pinMode(MOTORPIN2, OUTPUT);
  pinMode(MOTORACTIVATIE, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.begin(9600); 
} 

void loop() { 
  test_vochtigheid();
  test_waterniveau();
  delay(5000);
} 

void test_vochtigheid() {
  vochtigheid = analogRead(VOCHTIGHEIDSPIN); 
  vochtigheid = vochtigheid/10; 
  Serial.println(vochtigheid); 
  if(vochtigheid<180) // TODO nog experimenteren met waarden
  { 
    motor_open();
    delay(10000); // Aantal seconden dat het buisje open staat
    motor_toe();
    teller = teller + 1;
  }
}

void test_waterniveau() {
  if (teller > 1) {
    stuur_melding("Het water is bijna op!");
    teller = 0;
  }
}

void motor_open() {
  digitalWrite(MOTORPIN1, LOW);
  digitalWrite(MOTORPIN2, HIGH); 
}

void motor_toe() {
  digitalWrite(MOTORPIN1, LOW);
  digitalWrite(MOTORPIN2, LOW); 
}

void stuur_melding(String bericht) {
  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(bericht);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
