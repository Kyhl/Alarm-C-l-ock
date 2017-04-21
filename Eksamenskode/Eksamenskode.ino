#include<SoftwareSerial.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int bluetoothRx = 7;
int bluetoothTx = 6;
int Vibrator = 8;
int data;   
char data1='a';
char timer;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx
int counter = 0;
int interval = 15;
int countered;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(115200);//standard bluetooth mate
  pinMode(Vibrator,OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
}

void loop() {
  bluetooth.listen();
  timercontrol();
  delay(1000);
  counter++;
  while(interval < counter){
    bluetoothAction();
    delay(5000);
    counter=0;
    lcd.clear(); 
  }
  bluetooth.println(data1);
  Serial.println(counter);
  Serial.println(interval);
  lcd.setCursor(0, 0);
  lcd.print("Interval:");
  lcd.print(interval);
  lcd.setCursor(0, 1);
  lcd.print(interval-counter);
  lcd.print(" sek. tilbage");
  data=' ';
  //countered=counter/60;
 /* lcd.print("Send ");
  lcd.print(millis()/1000);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
    lcd.print(" nudes plz :)");*/
    
}
void bluetoothAction(){  
 // Serial.println("BluetoothAction");
   data= random(1,6);
   Serial.println(data);
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
    delay(10000);
    counter=0;
}
void timercontrol(){  
 // Serial.println("BluetoothAction");
  
 if(bluetooth.available()){ 
    timer= (char)bluetooth.read();
    if(timer=='y'){
      interval=15;
    }else if(timer=='u'){
      interval=20;
    }else if(timer=='i'){
      interval=30;
   }else if(timer=='o'){
      interval=45;
   }else if(timer=='p'){
      interval=60;
}
 }
 timer=' ';
}
       

