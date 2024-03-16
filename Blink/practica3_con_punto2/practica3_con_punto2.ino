#define     CONTBTN     2
#define     VELBTN      3
#define     LED         13
#define     BAUDRATE    115200
/*declaracion de variables*/
volatile uint16_t cont =0;
volatile unsigned long lasttime=0;
volatile unsigned long debounceDelay=100;
/*declaracion de funciones*/
void contador();
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

  attachInterrupt(digitalPinToInterrupt(CONTBTN),contador,RISING);
  attachInterrupt(digitalPinToInterrupt(VELBTN),vel,RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,1);
  delay(velocidadActual);
  digitalWrite(LED,0);
  delay(velocidadActual);

}

/*funciones de interrupcion*/
void contador(){
  if(millis()-lasttime>debounceDelay){
    cont++;
    lasttime=millis();
    Serial.println(cont);
  }
}
void vel(){
  if(millis()-lasttime>debounceDelay){
    lasttime=millis();
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
  }
}