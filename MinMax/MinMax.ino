//motor 1
const int pin11 =5; //control motor1
const int pin21 = 6; //control direccio contraria
//moto2
const int pin12 = 2;//control motor2
const int pin22 = 3;//control direccio contraria
 
const int vel_pin1 = 7; // pin de la velocitat
const int vel_pin2 = 4; // pin de la velocitat

/****Geometria****/
const float distancia_rodes = 0.39;
const float radi_rodes = 0.85;


float velocitat_lineal = 0; //insertar valor
float velocitat_angular = 0; //insertar valor

float w1, w2; //velocitat angular de les rodes

const int pwm1 = 9;
const int pwm2 = 8;

volatile float va,vl;

float vel_ang,vel_lin;
float minim_a = 2000;
float maxim_a = 0;
float minim_l = 2000;
float maxim_l = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pin11,OUTPUT);
  pinMode(pin21,OUTPUT);
  
  pinMode(pin12,OUTPUT);
  pinMode(pin22,OUTPUT);
  
  pinMode(vel_pin1,OUTPUT);
  pinMode(vel_pin2,OUTPUT);

  pinMode(pwm1, INPUT);
  pinMode(pwm2, INPUT);

  while (millis() < 10000) {
   vel_lin = pulseIn(pwm1, HIGH);
   vel_ang = pulseIn(pwm2, HIGH);
    if(vel_ang < minim_a) {
    minim_a = vel_ang;
  } else if(vel_ang > maxim_a){
    maxim_a = vel_ang;
  }
  if(vel_lin < minim_l) {
    minim_l = vel_ang;
  } else if(vel_lin > maxim_l){
    maxim_l = vel_lin;
  }
  }
  Serial.println(minim_a);
  Serial.println(maxim_a);
  Serial.println(minim_l);
  Serial.println(maxim_l);
}

void loop() {
  // put your main code here, to run repeatedly:

  vl = pulseIn(pwm1, HIGH); //entrada velocitat lineal mando
  va = pulseIn(pwm2, HIGH); //entrada velocitat angular mand

  velocitat_lineal = map(vl,1911,1060,-255,255); //Rescala velocitat
  velocitat_angular = map(va,1911,1060,-255,255);

  if(velocitat_lineal > 255) {
    velocitat_lineal = 255;
  } else if(velocitat_lineal < -255) {
    velocitat_lineal = -255;
  }
  if(velocitat_angular > 255) {
    velocitat_angular = 255;
  } else if(velocitat_angular < -255) {
    velocitat_angular = -255;
  }

  if(velocitat_lineal < 10 & velocitat_lineal > -10) {
    velocitat_lineal = 0;
  }
  if(velocitat_angular < 10 & velocitat_angular > -10) {
    velocitat_angular = 0;
  }
  
  calcular_velocitats();
  accionar_motor(pin11, pin21, vel_pin1, w1);
  accionar_motor(pin12, pin22, vel_pin2, w2);

  delay(5);
  
}

void calcular_velocitats(){
  w1 = (velocitat_lineal/radi_rodes) + (distancia_rodes*velocitat_angular / (2*radi_rodes));
  w2 = (velocitat_lineal/radi_rodes) - (distancia_rodes*velocitat_angular / (2*radi_rodes));

}

void accionar_motor(int pin1, int pin2, int vel, float velocitat){
  if(velocitat > 0){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
  analogWrite(vel,abs(velocitat*100));
  
}
