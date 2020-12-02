#include <IRremote.h>
#include <toneAC.h>
int IR_RECEIVE_PIN = 11;
IRrecv IrReceiver(IR_RECEIVE_PIN);
IRsend IrSender;
decode_results results;
int lives = 9;
int button = 2;
unsigned long tData = 0xa90;
int frequency = 1000;
int buzzer = 13;
void shootSound(){
  for( int i = 1500 ; i > 1000 ; i-=5){
    toneAC(i);
    delay(1);
}
  toneAC(0);
}
void startSound(){
  for( int i = 0 ; i < 1000 ; i+=1){
    toneAC(i);
    delay(1);
  }
  toneAC(0);
}
void trigger(){
  if(lives >1){
    if(digitalRead(button) == LOW){
      IrSender.sendSony(tData, 12);
      IrReceiver.enableIRIn();
      shootSound();
      delay(150);
    }
  }else if(lives == 0){
    if(digitalRead(button) == LOW){
      lives = 9;
    }
  }
}

void hp(int num)
{
  if(num == 0)
  {
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    digitalWrite(12, 0);
  } else if(num == 1) {
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 0);
    digitalWrite(A4, 0);
    digitalWrite(12, 0);
  } else if(num == 2) {
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 0);
    digitalWrite(12, 1);
  } else if(num == 3) {
    digitalWrite(5, 0);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 0);
    digitalWrite(12, 1);
  } else if(num == 4) {
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 0);
    digitalWrite(A4, 1);
    digitalWrite(12, 1);
  } else if(num == 5) {
    digitalWrite(5, 0);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    digitalWrite(12, 1);
  } else if(num == 6) {
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    digitalWrite(12, 1);
  } else if(num == 7) {
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 0);
    digitalWrite(12, 0);
  } else if(num == 8) {
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    digitalWrite(12, 1);
  } else if(num == 9) {
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    digitalWrite(12, 1);
  }else {
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(A5, 0);
    digitalWrite(A4, 0);
    digitalWrite(11, 0);
  }
}

#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(button,INPUT_PULLUP);
    Serial.begin(9600);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));

    // In case the interrupt driver crashes on setup, give a clue
    // to the user what's going on.
    Serial.println("Enabling IRin");
    IrReceiver.enableIRIn();  // Start the receiver

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    startSound();

    
}

void loop() {
    hp(lives);
    if (IrReceiver.decode(&results)) {
        if(results.decode_type == SONY & (lives > 0)){
          lives--;
          Serial.println("received");
        }
        IrReceiver.printResultShort(&Serial);
        Serial.println();
        IrReceiver.resume(); // Receive the next value
    }
    delay(100);
    trigger();
    
    

    
}
