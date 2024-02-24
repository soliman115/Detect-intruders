#include <WiFi.h>
#include <HTTPClient.h>   
#include <UrlEncode.h>

const char* ssid     = "dux";
const char* password = "1234solo";

String apiKey = "5834042";        
String phone_number = "+201066473089";

const int trigPin = 2;
const int echoPin = 5;
const int buzzerPIN = 18;

long duration;
int distance;
String url;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
  pinMode(trigPin, OUTPUT);      
  pinMode(echoPin, INPUT);       
  pinMode(buzzerPIN, OUTPUT); 
  Serial.println();
}
void loop() 
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034/2;
  Serial.print("Distance : ");
  Serial.println(distance);
  
  if (distance >=5 && distance <=50) 
  {
    digitalWrite(buzzerPIN,HIGH);
    message_to_whatsapp("Alert!!! Someone Opened Your Door."); 
    delay(800);
  }

  else 
   {
    Serial.println(" No Warning ");
    digitalWrite(buzzerPIN,LOW);
   }

   delay(800);
}

void message_to_whatsapp(String message) 
{
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  postData(); 
}
//HTTPS post method
void postData() 
{
  int httpResponseCode ;     
  HTTPClient http;  
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  httpResponseCode = http.POST(url); 
  if (httpResponseCode  == 200)     
  {
    Serial.println("Message sent successfully"); 
  }
  else                     
  {
    Serial.println("Error sending the message"); 
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();       
}
