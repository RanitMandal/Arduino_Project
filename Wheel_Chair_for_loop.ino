
const int echoPin[] = {5,7,9,11,13,A5};
const int trigPin[] = {4,6,8,10,12,A4};
int sens[6];
int LimDis = 21;

int m1a= A0;
int m1b= A1;
int m2a= A2;
int m2b= A3;

int EN = 3;                 // Pin 1 of L293D IC                 // Pin 9 of L293D IC
int val, save;

void setup()
{
  pinMode(trigPin[0], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[0], INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin[1], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[1], INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin[2], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[2], INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin[3], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[3], INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin[4], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[4], INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin[5], OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin[5], INPUT); // Sets the echoPin as an INPUT 
 pinMode(m1a, OUTPUT); //Digital pin 10 set as output Pin
 pinMode(m1b, OUTPUT);//Digital pin 11 set as output Pin
 pinMode(m2a, OUTPUT);//Digital pin 12 set as output Pin
 pinMode(m2b, OUTPUT); //Digital pin 13. set as output Pin
 pinMode(EN, OUTPUT);   // where the motor is connected to
 Serial.begin(9600);
 Serial.println("Enter values between 0 - 255");
}


void loop(){
    
  sens[0] = Calculate(trigPin[0],echoPin[0]);
  sens[1] = Calculate(trigPin[1],echoPin[1]);
  sens[2] = Calculate(trigPin[2],echoPin[2]);
  sens[3] = Calculate(trigPin[3],echoPin[3]);
  sens[4] = Calculate(trigPin[4],echoPin[4]);
  sens[5] = Calculate(trigPin[5],echoPin[5]);
  
  
 while (Serial.available() > 0){
  
      val = Serial.read();
      Serial.println(val);
 }
 
 if(val >= 49 && val <= 57)         
    { 
        save=val;
        analogWrite(EN, val*25);      //sets the motors speed
    }
   
 if(sens[0] >= LimDis && sens[1] >= 30
    && sens[2] >= 9 && sens[3] >= 9
    && sens[4] == 5 && sens[5] >= LimDis){ 
       // Serial.println("Enter 1st Condition pass senser ");
     
        if(val== 70){
            Forward();
        }
    
        else if(val==66){
            Backward();
        }
      
        else if(val== 76){
        Left();
        } 
        
        else if(val== 82){
        Right();
        }
     
        else if(val == 83){
        Stop();
        }

        else if(val== 73){
        Forward_Right();
        }
     
        else if(val== 74){
        Backward_Right();
        }

        else if(val == 71) {
        Forward_Left();
        }
      
        else if(val== 72){
        Backward_Left();
        }
      
    }else if(sens[0] <= 20){
        if(val== 70){
            Forward();
        }else if(val== 73){
        Forward_Right();
        }

        else if(val == 71) {
        Forward_Left();
        }else{
        Stop();
        }
    }else if(sens[1]<=31){
        Backward();
        delay(300);
        Stop();
    }else if(sens[2]<=10 && sens[4] ==5 ){
        Forward_Right();
        delay(700);
        Forward_Left();
        delay(700);
        Stop();
    }else if(sens[3]<=10 && sens[4] == 5 ){
        Forward_Left();
        delay(700);
        Forward_Right();
        delay(700);
        Stop();
    }else if(sens[4] > 5 ){
        if(val==66){
            Backward();
        
        }else{
            Stop();
        }
        

    }else if(sens[4] < 5){
        if(val==66){
            Backward();
        
        }else{
            Stop();
        }
        

    }else if(sens[5] <= 20){
        if(val==66){
            Backward();
        }else{
            Stop();
        }
    }
 
 }//End Void loop



int Calculate(int tig, int eco){
  
  digitalWrite(tig, LOW);
  //delayMicroseconds(1); // wait for 2 ms to avoid 
            // collision in serial monitor
  digitalWrite(tig,HIGH); // turn on the Trigger to generate pulse
  //delayMicroseconds(1); // keep the trigger "ON" for 10 ms to generate   // pulse for 10 ms.
  digitalWrite(tig,LOW); // Turn off the pulse trigger to stop      // pulse generation
  long duration = pulseIn(eco, HIGH); // Variable to store time taken to the pulse
  int distance = duration * 0.0344 / 2; // Expression to calculate    // distance using time // Variable to store distance calculated using
 return distance;
}



void Forward(){
   digitalWrite(m1a, HIGH);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, HIGH);
   digitalWrite(m2b, LOW);  
}

void Backward(){
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}


void Left(){
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

void Right(){
   digitalWrite(m1a, HIGH);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, LOW);
   digitalWrite(m2b, HIGH);
}

void Stop(){
   digitalWrite(m1a, LOW);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, LOW);
   digitalWrite(m2b, LOW);
  }
void Forward_Right(){
   digitalWrite(m1a, HIGH);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, LOW);
   digitalWrite(m2b, LOW);
}

void Backward_Right(){
   digitalWrite(m1a, LOW);
   digitalWrite(m1b, HIGH);
   digitalWrite(m2a, LOW);
   digitalWrite(m2b, LOW);
}

void Forward_Left(){
   digitalWrite(m1a, LOW);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, HIGH);
   digitalWrite(m2b, LOW);  
}

void Backward_Left(){
   digitalWrite(m1a, LOW);
   digitalWrite(m1b, LOW);
   digitalWrite(m2a, LOW);
   digitalWrite(m2b, HIGH);
}
