// Bibliotekerene som koden skal anvende bliver opgjort
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>

// De pins som skal anvende LiquidCrystal biblioteket, hvilket er det der styrer displayet, bestemmes.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Variablerne bliver tildelt en Pin på Arduinoen
int bluetoothRx = 7;
int bluetoothTx = 6;
int Vibrator = 9;
int data;   
char timer;
//Det opgøres hvilke pins der skal sende og modtage bluetoothdataen
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx
//Vores timer bliver sat til at starte på 0, og intervallet bliver sat til 15 som standard
int counter = 0;
int interval = 15;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(115200);//standard bluetooth mate
  //Vibratorpin'en bliver sat til output, da den skal sende strøm
  pinMode(Vibrator,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
}

void loop() {
  //Vibratorpin'en bliver sat i analog tilstand
  analogWrite(Vibrator,0);
  //Bluetooth bliver opdateret med den nyeste information
  bluetooth.listen();
  //Funktion til kontrol af timer
  timercontrol();
  // Et sekundt delay så vores timer tæller op 1 gang i sekundet
  delay(1000);
  //Timeren tæller op
  counter++;
  //While funktion der bestemmer hvornår en øvelse skal vises
  while(interval < counter){
    //Funktion der bestemmer hvilken øvelser der vises
    bluetoothAction();
    //5 sekunders forsinkelse så man kan nå at set øvelsen
    delay(15000);
    //Timeren nulstilles
    counter=0;
    //Displayet bliver nulstillet
    lcd.clear(); 
  }
  //Sætter vores teoretisk mousecursor til 1. blok øverst i venstre hjørne af displayet
  lcd.setCursor(0, 0);
  //Printer tekst til displayet
  lcd.print("Interval:");
  //Printer det bestemte interval til displayet
  lcd.print(interval);
  lcd.print(" sek.");
  //Sætter vores cursor til 1 blok på nederste række
  lcd.setCursor(0, 1);
  //Udregner og printer tiden til næste øvelse 
  lcd.print(interval-counter);
  lcd.print(" sek. tilbage");
  //Data variablen bliver nulstillet så timeren ikke bliver ændret
  data=' ';    
}
void bluetoothAction(){  
   //Et tilfældigt tal mellem 1 og 5 bliver udregnet
   data= random(1,6);
  //If funktion der printer en forskellig øvelse afhængigt af tallet fra "data" 
  if(data==1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lav Oevelse 1");
      lcd.setCursor(0, 1);
      lcd.print("Gentag 8 Gange");
    }else if(data==2){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Lav Oevelse 2");
      lcd.setCursor(0, 1);
      lcd.print("Gentag 5 Gange");
    }else if(data==3){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Lav Oevelse 3");
      lcd.setCursor(0, 1);
      lcd.print("Gentag 5 Gange");
    }else if(data==4){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Lav Oevelse 4");
      lcd.setCursor(0, 1);
      lcd.print("Gentag 5 Gange");
    }else if(data==5){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Lav Oevelse 5");
      lcd.setCursor(0, 1);
      lcd.print("Gentag 10 Gange");
    }else{
      lcd.print("Ingen data");
      lcd.setCursor(0, 1);
      lcd.print("modtaget");
    }
    //Sender dataen tilbage til appen
    bluetooth.println(data);
    //Tænder for vibrationsmotoren
    analogWrite(Vibrator, 150);
}
void timercontrol(){  
 //If funktion der kun tænder hvis en bluetoothforbindelse er til stede
 if(bluetooth.available()){ 
    //timer variablet bliver sat til det tegn der bliver modtaget via. bluetooth
    timer= (char)bluetooth.read();
    //if funktion der ændre interval variablet afhængigt af modtaget bogstav 
   if(timer=='a'){
      interval=15;
    }else if(timer=='b'){
      interval=20;
    }else if(timer=='c'){
      interval=30;
   }else if(timer=='d'){
      interval=45;
   }else if(timer=='e'){
      interval=60;
   }
 }
 timer=' ';
}
       

