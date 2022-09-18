#include <LiquidCrystal.h>

#define ECHO_PIN 2
#define TRIG_PIN 15
#define pinAmount 4
#define NULL ((void *)0)

LiquidCrystal lcd(12, 13, 14, 27, 26, 25);

struct Node{
  int index;
  int pin;
  int distance;
  struct Node *next;
};

int arrayLed[4][2] = {{21,50},
                      {19,100},
                      {18,200},
                      {5,300}};

int arr =sizeof(arrayLed[0]);
struct Node *head;   

void insertArray(int index,int pin, int distance ){
  struct Node* lP = (struct Node*) malloc(sizeof(struct Node));  
   lP->index = index+1; 
   lP->pin = pin;
   lP->distance = distance;
   lP->next = head; 
   head =lP;
   pinMode(arrayLed[index][0], OUTPUT);
  }
 
 void setHighLow(int param,int delayTime,int highLow){
  digitalWrite(param, highLow);
  delayMicroseconds(delayTime);
}

float readDistance(){
  setHighLow(TRIG_PIN,2,LOW);
  setHighLow(TRIG_PIN,10,HIGH);
  setHighLow(TRIG_PIN,0,LOW);
  int duration = pulseIn(ECHO_PIN,HIGH);
  return duration *0.034/2;
}

void setup() {
  for (int i=0;i<pinAmount;i++){
  insertArray(i,arrayLed[i][0],arrayLed[i][1]);
  }
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void display(float distance, int ledamount){ 
    lcd.clear();
    lcd.print("distance = "); 
    lcd.print(distance,5);
    lcd.setCursor(0, 1);
    ledamount>0?lcd.print("led on "):lcd.print("led off ");
}

void loop() {
   float distance = readDistance();
   struct Node* ptr;
   ptr = head;
   
   while (ptr != NULL) { 
      int idx = distance>ptr->distance?ptr->index:0;
      display(distance,idx);
      if (idx==pinAmount){
        setHighLow(ECHO_PIN,10,HIGH);
      }
      for(int j=0; j<idx;j++){
       setHighLow(ptr->pin,100,HIGH);
      }
      setHighLow(ptr->pin,10,LOW);
      ptr = ptr->next; 
    
   } 
}
 
