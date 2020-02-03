//motor 1
const int pin11 = 5; //control motor1
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

volatile float va, vl;

void setup() {
  Serial.begin(9600);

  pinMode(pin11, OUTPUT);
  pinMode(pin21, OUTPUT);

  pinMode(pin12, OUTPUT);
  pinMode(pin22, OUTPUT);

  pinMode(vel_pin1, OUTPUT);
  pinMode(vel_pin2, OUTPUT);

  pinMode(pwm1, INPUT);
  pinMode(pwm2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  vl = pulseIn(pwm1, HIGH); //entrada velocitat lineal mando
  va = pulseIn(pwm2, HIGH); //entrada velocitat angular mand

  velocitat_lineal = map(vl, 1911, 1065, -255, 255); //Rescala velocitat
  velocitat_angular = map(va, 1058, 1912, -255, 255);

  if (velocitat_lineal > 255) {
    velocitat_lineal = 255;
  } else if (velocitat_lineal < -255) {
    velocitat_lineal = -255;
  }
  if (velocitat_angular > 255) {
    velocitat_angular = 255;
  } else if (velocitat_angular < -255) {
    velocitat_angular = -255;
  }

  if (velocitat_lineal < 10 & velocitat_lineal > -10) {
    velocitat_lineal = 0;
  }
  if (velocitat_angular < 10 & velocitat_angular > -10) {
    velocitat_angular = 0;
  }

  calcular_velocitats();
  accionar_motor(pin11, pin21, vel_pin1, w1);
  accionar_motor(pin12, pin22, vel_pin2, w2);

  delay(5);

}

void calcular_velocitats() {
  w1 = (velocitat_lineal / radi_rodes) + (distancia_rodes * velocitat_angular / (2 * radi_rodes));
  w2 = (velocitat_lineal / radi_rodes) - (distancia_rodes * velocitat_angular / (2 * radi_rodes));

  Serial.print(w1);
  Serial.println(w2);
}

void accionar_motor(int pin1, int pin2, int vel, float velocitat) {
  if (velocitat > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  Serial.println(velocitat);
  analogWrite(vel, abs(velocitat * 100));

}
