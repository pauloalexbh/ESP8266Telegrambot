#include <ESP8266WiFi.h>
#include <ESP8266TelegramBOT.h>


// Initialize Wifi connection to the router
const char* ssid = "WiFI Name here";
const char* password = "WiFi password here";
int status = WL_IDLE_STATUS;
WiFiClient  client;


// Initialize Telegram BOT

#define BOTtoken "TelegramBottoken here"  //token of FlashledBOT
#define BOTname "BOTname here"
#define BOTusername "Botusername here"

TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;



void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println(" ");
  Serial.println("Iniciando programa Telegram3.");

  // prepare GPIOs
  pinMode(14, OUTPUT); //Spot
  digitalWrite(14, 0);
  delay(100);
  pinMode(5, OUTPUT); //Luz indireta
  digitalWrite(5, 0);
  delay(100);


  // Connect to WiFi network
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

  bot.begin();
}



void loop() {
  String dado = "";
  int dadon = 0;
  
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_lasttime = millis();
    
    Serial.println ("Mensagem recebida de: ");
    Serial.println (bot.message[1][2]);
    Serial.println (" ");
    Serial.println (bot.message[1][3]);
    Serial.println ("-----------");
  
  if ( bot.message[1][5].equals("/ligaindireta")) {
  digitalWrite(5, HIGH);
  Serial.println ("Iluminação indireta ligada.");
  bot.sendMessage(bot.message[1][1], "Iluminação indireta ligada.", "");
  }
  else if ( bot.message[1][5].equals("/desligaindireta")) {
  digitalWrite(5, LOW);
  Serial.println ("Iluminação indireta desligada.");
  bot.sendMessage(bot.message[1][1], "Iluminação indireta desligada.", "");
  }
  else if ( bot.message[1][5].equals("/ligaspot")) {
  digitalWrite(14, HIGH);
  Serial.println ("Spot indireta ligado.");
  bot.sendMessage(bot.message[1][1], "Spot ligado.", "");
  }
  else if ( bot.message[1][5].equals("/desligaspot")) {
  digitalWrite(14, LOW);
  Serial.println ("Spot indireta deligado.");
  bot.sendMessage(bot.message[1][1], "Spot desligado.", "");
  }
  else if ( bot.message[1][5].equals("/temperatura")) {
  Serial.println ("Temperatura solicitada.");
  bot.sendMessage(bot.message[1][1], "Temperatura solicitada.", "");
  }
  else if ( bot.message[1][5].startsWith("/Dado")) {
  dado = bot.message[1][5].substring(6);
  dadon = dado.toInt();
    if (dadon == 0){
      dadon = 6;
      }
  dado = String(dadon);
  Serial.println ("Girou um dado de " + dado + " lados.");
  bot.sendMessage(bot.message[1][1], "Girou um dado de " + dado + " lados" , "");
  dadon = random(1, 1+dadon);
  dado = String(dadon);
  Serial.println ("O resultado foi " + dado);
  delay(100);
  bot.sendMessage(bot.message[1][1], "O resultado foi " + dado, "");
  }
  
    bot.message[0][0] = "";   // All messages have been replied - reset new messages
    bot.message[1][5] = "";
  }
  }
