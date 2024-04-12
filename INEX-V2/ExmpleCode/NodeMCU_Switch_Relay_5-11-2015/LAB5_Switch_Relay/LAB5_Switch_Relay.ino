const int sw1 =  D1;
const int sw2 =  D2;
const int Rel1 =  D4;
const int Rel2 =  D5;
int st_sw1=0;
int st_sw2=0;
int st_1=0;
int st_2=0;
int last_st_sw1=1;
int last_st_sw2=0;
void setup() {
 pinMode(Rel1, OUTPUT);
 pinMode(Rel2, OUTPUT);
 pinMode(sw1, INPUT);
 pinMode(sw2, INPUT);
}
void loop() {
 
 st_sw1=digitalRead(sw1);
 if((st_sw1==0)&&(last_st_sw1==1)){
    st_1=~st_1;
    digitalWrite(Rel1,st_1);
    delay(250);
  }
  last_st_sw1 = st_sw1;
  
 st_sw2=digitalRead(sw2);
 if((st_sw2==1)&&(last_st_sw2==0)){
    st_2=~st_2;
    digitalWrite(Rel2,st_2);
    delay(250);
  }
  last_st_sw2 = st_sw2;
}

