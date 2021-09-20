#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const int whiteButton = 9;
const int yellowButton = 10;
const int greenButton = 11;
const int redButton = 12;
const int blueButton = 13;
const int onOffButton = 2;
const int whiteLED = 3;
const int yellowLED = 4;
const int greenLED = 5;
const int redLED = 6;
const int blueLED = 7;

int* target = 0;
bool fail = false;
bool playing = false;
int level = 0;
int notes[] = {261, 293, 329, 349, 391};
int highscore = 0;
int currentMode = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(whiteButton,INPUT);
  pinMode(yellowButton,INPUT);
  pinMode(greenButton,INPUT);
  pinMode(redButton,INPUT);
  pinMode(blueButton,INPUT);

  pinMode(whiteLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(blueLED,OUTPUT);

  pinMode(onOffButton,INPUT);

  randomSeed(analogRead(0));

  lcd.begin(16,2);

  printtoLCD(0);

}

void loop() {
  // put your main code here, to run repeatedly:
   if(fail){
    if (level > highscore){
      highscore = level;
    }
      turnOnLEDs();
      playing = false;
      
   }
   else if(playing){
     delay(500);
     printtoLCD(1);
     generatePattern();
     printtoLCD(2);
     checkPattern();
   }
   if(!playing && digitalRead(onOffButton)){
    level = 0;
    turnOffLEDs();
    printtoLCD(0);
    playing = true;
    fail = false;
   }
   
}

void checkPattern() {
  for (int i = 0; i < level + 3; ++i){
    int pressed = 0;
    int released = 1;
    while(true){

      if(digitalRead(whiteButton)){
        pressed = whiteLED;
        digitalWrite(whiteLED, HIGH);
        tone(8, notes[0]);
      }
      else{
        if(pressed == whiteLED){
          released = whiteLED;
          digitalWrite(whiteLED, LOW);
        }
      }

      if(digitalRead(yellowButton)){
        pressed = yellowLED;
        digitalWrite(yellowLED, HIGH);
        tone(8, notes[1]);
      }
      else{
        if(pressed == yellowLED){
           released = yellowLED;
           digitalWrite(yellowLED, LOW); 
        }
      }
      
      if(digitalRead(greenButton)){
        pressed = greenLED;
        digitalWrite(greenLED, HIGH);
        tone(8, notes[2]);
      }
      else{
        if(pressed == greenLED){
          released = greenLED;
          digitalWrite(greenLED, LOW); 
        }
      }
      
      if(digitalRead(redButton)){
        pressed = redLED;
        digitalWrite(redLED, HIGH);
        tone(8, notes[3]);
      }
      else{
        if(pressed == redLED){
          released = redLED;
          digitalWrite(redLED, LOW); 
        }
      }

      if(digitalRead(blueButton)){
        pressed = blueLED;
        digitalWrite(blueLED, HIGH);
        tone(8, notes[4]);
      }
      else{
        if(pressed == blueLED){
          released = blueLED;
          digitalWrite(blueLED, LOW);
        }
      }
     
      if (released == pressed){
        noTone(8);
        if(released != target[i]){
          fail = true;
          printtoLCD(3);
          delay(1000);
        }
        break;
      }
      
    }
  if(fail){
    break;
    
  }
    
  }
  
  if(!fail){
    ++level;
    flash();
    delay(250);
    flash();
  }
    
}

void generatePattern() {
  if(target){
    delete[] target;
    target = 0;
  }

  target = new int[level+3];
  
  for(int i = 0; i < level+3; ++i){
    target[i] = random(3,8);
    delay(10);
  }
  for(int i = 0; i < level+3; ++i){
    digitalWrite(target[i], HIGH);
    tone(8, notes[target[i]-3]);
    delay(500);
    noTone(8); 
    digitalWrite(target[i], LOW);
    delay(500); 
  }
  flash();
  delay(100);
}

void flash(){
    delay(250); 
    digitalWrite(whiteLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    delay(500);
    digitalWrite(whiteLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    delay(250);
}

void printtoLCD (int mode){
  if (mode != currentMode){
    lcd.clear();
    if(mode == 0){
      lcd.print("Welcome to");
      lcd.setCursor(0,1);
      lcd.print("Simon's game");
    }
    if(mode == 1){
      lcd.print("Watch closely!");
      lcd.setCursor(0,1);
      lcd.print("S:");
      lcd.print(level);
      lcd.print(" HS:");
      lcd.print(highscore);
    }
    if(mode == 2){
      lcd.print("Remember?");
      lcd.setCursor(0,1);
      lcd.print("S:");
      lcd.print(level);
      lcd.print(" HS:");
      lcd.print(highscore);
    }
    if(mode == 3){
      lcd.print("You lost :(");
      lcd.setCursor(0,1);
      lcd.print("S:");
      lcd.print(level);
      lcd.print(" HS:");
      lcd.print(highscore);
    }
  }

  currentMode = mode;
}

void turnOffLEDs(){
    digitalWrite(whiteLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
}

void turnOnLEDs(){
    digitalWrite(whiteLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
}
