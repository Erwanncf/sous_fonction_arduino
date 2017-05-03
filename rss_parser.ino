/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "Livebox-1ffd";
const char* password = "0123456789";

const char* host = "www.france24.com";
// We now create a URI for the request
String url = "http://www.france24.com/fr/france/rss";

String RssTiltle[100];
String RssDescrption[100];

String RssTiltleClear[100];

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               
  delay(5000);
                 
  String line= "";
bool TitleLock = false;
int cptTitle= 0;
int cptDescription = 0;
String compar = "Server";

  while(client.available())
  {
     line = client.readStringUntil('\n');
    // Serial.println("test");
     
     int lineLength = line.length();
          
      if (lineLength > 2000)
      {
        lineLength =2000;
      }
      
     char lineAray[lineLength];
     memset(lineAray,'\0',lineLength);
     
     Serial.print("nb line: ");
     Serial.println(lineLength);

       line.toCharArray(lineAray, lineLength) ;


       if (strstr(lineAray, "<title>")) 
       {
        Serial.println("title match");
        RssTiltle[cptTitle] = line;
        cptTitle = cptTitle+1;
       }
       
        if (strstr(lineAray, "<description>")) 
       {
        Serial.println("description match");
        RssDescrption[cptDescription] = line;
        cptDescription = cptDescription+1;
       }
       //Serial.println(line);
       
  }

Serial.println("closing connection");


//Fonction pour enlever les balises titre
for(int i=0 ; i<cptTitle ; i++)
{
 RssTiltle[i].replace("<title>", "\0");
 RssTiltle[i].replace("</title>", "\0");
 RssTiltle[i].replace("é", "e");
 RssTiltle[i].replace("ç", "c");
 RssTiltle[i].replace("è", "e");
 RssTiltle[i].replace("ç", "c");
 RssTiltle[i].replace("l'", "l");
 RssTiltle[i].replace("ê", "e");
 RssTiltle[i].replace("à", "a");
 RssTiltle[i].replace("ô", "o");
 RssTiltle[i].replace("L'", "L");
 RssTiltle[i].replace("À", "A");
 RssTiltle[i].replace("’", " ");
 RssTiltle[i].replace("–", "-");
 RssTiltle[i].replace("É", "E");

}

//Fonction pour enlever les balises description
for(int i=0 ; i<cptDescription ; i++)
{
 RssDescrption[i].replace("<description>", "\0");
 RssDescrption[i].replace("</description>", "\0");
 RssDescrption[i].replace("é", "e");
 RssDescrption[i].replace("è", "e");
 RssDescrption[i].replace("ç", "c");
 RssDescrption[i].replace("l'", "l");
 RssDescrption[i].replace("ê", "e");
 RssDescrption[i].replace("à", "a");
 RssDescrption[i].replace("ô", "o");
 RssDescrption[i].replace("L'", "L");
 RssDescrption[i].replace("À", "A");
 RssDescrption[i].replace("’", " ");
 RssDescrption[i].replace("–", "-");
 RssDescrption[i].replace("É", "E");

  
}

Serial.print("nb Title: ");
Serial.println(cptTitle);

Serial.print("nb Description: ");
Serial.println(cptDescription);

//Fonction pour montrer les données rss

for(int i=0 ; i<cptDescription ; i++)
{
Serial.print("T ");
Serial.print(i);
Serial.print(" :");
Serial.println(RssTiltle[i]);

Serial.print("D ");
Serial.print(i);
Serial.print(" :");
Serial.println(RssDescrption[i]);
Serial.println();
Serial.println();
}

}

