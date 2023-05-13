int encoderReadingPin=2; //Pin lectura señal del encoder

long m1,m2; //Tiempos para el cálculo de interrupciones
long up_times[3]={0,0,0}; //tiempos interrupciones
long t_min = 0; //duración media interrupciones
int index = 0; //indice para interrupciones

//interrupcion, aqui almacenaremos el tiempo de la señal del encoder
void int0(){
  m1=micros(); //asignamos m1 al tiempo de ahora
  up_times[index]=m1-m2; //calculamos la duración con la diferencia entre el momento presente y la última interrupción
  index=(index+1)%3; //actualizamos el índice de la lista de tiempos
  m2=m1; //actualizamos m2 para el siguiente ciclo
}

void setup() {
  pinMode(encoderReadingPin, INPUT);
  digitalWrite(encoderReadingPin, HIGH); //turn on pullup resistors
  attachInterrupt(digitalPinToInterrupt(encoderReadingPin),int0,RISING);
  Serial.begin(115200);
  while(!Serial){
    ; //wait for serial port to connect
  }
}

void loop() {
  t_min=up_times[0]+up_times[1]+up_times[2]; // tiempo medio entre interrupciones
  double motor_f=3E6/(t_min*7); //calculamos la frecuencia
  Serial.println(motor_f);
}