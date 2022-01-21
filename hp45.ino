#include <TimerOne.h> //https://www.pjrc.com/teensy/td_libs_TimerOne.html
unsigned char toWork=0;
unsigned long punkteerTimer = 100000;//полупериод пунктира в микросекундах
  unsigned char a = 0;
void callback(){ 
  if(toWork==1)
    toWork=0;
  else
    toWork=1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);//Primitive
  pinMode(3, OUTPUT);//Address
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  Timer1.initialize(punkteerTimer); // инициализировать timer1, и установить период в мкс - период пунктиров!
  Timer1.attachInterrupt(callback);
}
// nop = 62.5 ns




void delay1125(){
asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
asm("nop");asm("nop");asm("nop");asm("nop");
}

void delay1250(){
delay1125();
asm("nop");asm("nop");  
}

void delayAPA(){ //176 - 3.1 ms - можно немного уменьшить, чтобы рисовал жирнее
  for(unsigned char i=0; i<176; i++){ //ре
    delay1250();    
    delay1250();   
    delay1250();   
  }
}

void loop() {

  a = PIND & 0B110000;
  if(a == 48) { //оба упр. пина установлены
    cli();  
    toWork = 1;
  } else {
    sei();     
  }
  if (a == 32) { //уст. D5
      punkteerTimer = 100000;  
      Timer1.setPeriod(punkteerTimer);
    }
    if (a == 16) { //уст. D4
      punkteerTimer = 80000;  
       Timer1.setPeriod(punkteerTimer);
  }  

    
  
  // put your main code here, to run repeatedly:
  if(toWork){  
  PORTD = 0B0000100; //1   //задержка между периодами A-P-A
  delayAPA();
  PORTD = 0B0001100; //2 
  delay1125(); // задержка между A и P
  
  PORTD = 0B0001000; //3
  delay1125(); //длительность P
  
  PORTD = 0B0001100; //от выключения P до выключения A
  
  delay1250();
  PORTD = 0B0000100;
  }
  else
    PORTD = 0B0000100; //P - off, A - off
}
