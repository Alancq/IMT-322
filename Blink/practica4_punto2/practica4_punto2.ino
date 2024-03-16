#define     CONTBTN     2
#define     VELBTN      3
#define     LED         13
#define     BAUDRATE    115200
/*declaracion de variables*/
volatile uint16_t cont =0;
volatile unsigned long lasttime=0;
volatile unsigned long debounceDelay=100;
volatile bool btnflag=false;
volatile bool btnflag2=false;
/*declaracion de funciones*/
void contadorRST();
void vel();
typedef enum{
  v1=500,
  v2=1000,
  v3=1500
}velocidad;
velocidad velocidadActual=v1;//velocidad inicial 500

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  pinMode(CONTBTN,INPUT_PULLUP);
  pinMode(VELBTN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(CONTBTN),contadorRST,FALLING);
  attachInterrupt(digitalPinToInterrupt(VELBTN),vel,FALLING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,1);
  delay(velocidadActual);
  digitalWrite(LED,0);
  delay(velocidadActual);

  if(btnflag){
    
    if(digitalRead(CONTBTN)==0){
      if(millis()-lasttime>=3000){
        cont=0;
        Serial.println("Contador Reiniciado");
        btnflag=false;
      }
    }
  }
  if(btnflag2){
    
    if(digitalRead(VELBTN)==0){
      if(millis()-lasttime>=3000){
        switch (velocidadActual){
          case v1:
          velocidadActual=v2;
          break;
          case v2:
          velocidadActual=v3;
          break;
          case v3:
          velocidadActual=v1;
          break;
        }
        Serial.print("Velocidad actual cambiada a: ");
        Serial.println(velocidadActual);
        btnflag2=false;
      }
    }
  }

}

/*funciones de interrupcion*/
void contadorRST(){
  
  if(millis()-lasttime>debounceDelay){
    if(digitalRead(CONTBTN)==0){
      cont++;
      btnflag=true;
      lasttime=millis();
      Serial.println(cont);
    }
    
  }
}
void vel(){
  if(millis()-lasttime>debounceDelay){
    if(digitalRead(VELBTN)==0){
      cont--;
      btnflag2=true;
      lasttime=millis();
      Serial.println(cont);
    }  
  }
}