#define PINS 3        //number of used pins
#define CAL_ROUNDS 30 //number of calibration reads at setup

int pins[]       = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int thresholds[] = {0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0};
boolean states[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};


void setup(){
  Serial.begin(9600);  //Begin serial communcation
  pinMode(13, OUTPUT);
  for(int pin = 0; pin < PINS;pin++) {
    pinMode(pins[pin], INPUT);
  }

  //read a good couple of values to check existing ambient light
  Serial.print("calibrating photodiodes ... ");
  for(int i = 0; i < CAL_ROUNDS; i++){
    for(int pin = 0; pin < PINS;pin++) {
      int temp = analogRead(pins[pin]);
      if(temp > thresholds[pin]){
        thresholds[pin] = temp;
      }
    }
    delay(10);
  }
  Serial.println("done"); 

  for(int pin = 0; pin < PINS;pin++) {
    thresholds[pin] += 5; //decrease by five for good measure
    Serial.print("# ");
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(thresholds[pin]);
  }

  Serial.println("BEGIN TRANSMISSION"); 
}

void loop(){
  //read each pin and transmit state changes
  for(int pin = 0; pin < PINS;pin++) {
    int temp = analogRead(pins[pin]);
    if(temp > thresholds[pin]){
      if(!states[pin]){
        states[pin] = true;
        Serial.print(pin);
        Serial.println(":on");
      }
    } else {
      if(states[pin]){
        states[pin] = false;
        Serial.print(pin);
        Serial.println(":off");
      }
    }
  }
  delay(100);
}

