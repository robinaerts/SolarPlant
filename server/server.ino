int VOCHTIGHEIDPIN = 0; // Bodemvochtigheidssensor (analoge input A0)
int vochtigheid = 0; 

void setup() { 
 Serial.begin(9600); 
} 

void loop() { 
  test_vochtigheid()
  delay(1000); 
} 

void test_vochtigheid() {
  value= analogRead(SENSE); 
  value= value/10; 
  Serial.println(value); 
  if(value<50) // experimenteren met waarden
  { 
    // DOE IETS
  }
}