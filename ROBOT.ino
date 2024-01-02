#include <LiquidCrystal.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);
// Crée un objet de la classe Adafruit_LiquidCrystal nommé "lcd_1" en utilisant le constructeur qui 
//prend un argument de type entier (dans ce cas, la valeur 0).

#define BROCHE_TRIGGER_AVANT A0
#define BROCHE_ECHO_AVANT A1
#define BROCHE_TRIGGER_ARRIERE 4
#define BROCHE_ECHO_ARRIERE 5
#define BROCHE_TRIGGER_GAUCHE A3
#define BROCHE_ECHO_GAUCHE A2
#define BROCHE_TRIGGER_DROITE 7
#define BROCHE_ECHO_DROITE 8



#define DISTANCE_OBSTACLE 15

#define PIN_MOTEUR1_1 9
#define PIN_MOTEUR1_2 6
#define PIN_MOTEUR2_1 10
#define PIN_MOTEUR2_2 11


int enMouvement;

void setup() {
  pinMode(PIN_MOTEUR1_1, OUTPUT);
  pinMode(PIN_MOTEUR1_2, OUTPUT);
  pinMode(PIN_MOTEUR2_1, OUTPUT);
  pinMode(PIN_MOTEUR2_2, OUTPUT);
  

  pinMode(BROCHE_TRIGGER_AVANT, OUTPUT);
  pinMode(BROCHE_ECHO_AVANT, INPUT);
  pinMode(BROCHE_TRIGGER_ARRIERE, OUTPUT);
  pinMode(BROCHE_ECHO_ARRIERE, INPUT);
  pinMode(BROCHE_TRIGGER_GAUCHE, OUTPUT);
  pinMode(BROCHE_ECHO_GAUCHE, INPUT);
  pinMode(BROCHE_TRIGGER_DROITE, OUTPUT);
  pinMode(BROCHE_ECHO_DROITE, INPUT);

  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2); // Initialiser l'écran LCD avec 16 colonnes et 2 lignes
  lcd.print("Robot Eviteur");
  lcd.setCursor(0, 1);
  lcd.print("d'Obstacles");
  delay(2000);
  lcd.clear();
}

float calculerDistance(int brocheTrigger, int brocheEcho) {
  digitalWrite(brocheTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(brocheTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(brocheTrigger, LOW);

  float duree = pulseIn(brocheEcho, HIGH);
  float distance = duree * 0.034 / 2;  // Convertir la durée du signal en distance en centimètres
  return distance;
}

void avancer(int enMouvement) {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  analogWrite(PIN_MOTEUR1_1, 255);
  analogWrite(PIN_MOTEUR1_2, 0);
  analogWrite(PIN_MOTEUR2_1, 255);
  analogWrite(PIN_MOTEUR2_2, 0);
  delay(enMouvement);
  return;
}

void reculer(int enMouvement) {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  analogWrite(PIN_MOTEUR1_1, 0);
  analogWrite(PIN_MOTEUR1_2, 255);
  analogWrite(PIN_MOTEUR2_1, 0);
  analogWrite(PIN_MOTEUR2_2, 255);
  delay(enMouvement);
  return;
}

void tournerAGauche(int enMouvement) {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  analogWrite(PIN_MOTEUR1_1, 255);
  analogWrite(PIN_MOTEUR1_2, 0);
  analogWrite(PIN_MOTEUR2_1, 80);
  analogWrite(PIN_MOTEUR2_2, 0);
  delay(enMouvement);
  return;
}

void tournerADroite(int enMouvement) {
  analogWrite(PIN_MOTEUR1_1, 80);
  analogWrite(PIN_MOTEUR1_2, 0);
  analogWrite(PIN_MOTEUR2_1, 255);
  analogWrite(PIN_MOTEUR2_2, 0);
  delay(enMouvement);
  return;
}

void arreterMouvement(int enMouvement) {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  analogWrite(PIN_MOTEUR1_1, 0);
  analogWrite(PIN_MOTEUR1_2, 0);
  analogWrite(PIN_MOTEUR2_1, 0);
  analogWrite(PIN_MOTEUR2_2, 0);
  delay(enMouvement);
  return;
}

void loop() {
  Serial.print("Distance avant : ");
  Serial.print(calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT));
  Serial.println(" cm");
  float distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);

  while (distanceAvant > DISTANCE_OBSTACLE) { //pas 'obstacle devant  
    
    avancer(600);
    lcd.clear();
    lcd.print("Avancer");
    distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);
  }

  if (distanceAvant < DISTANCE_OBSTACLE) { // obstacle devant 
    arreterMouvement(300);
    lcd.clear();
    lcd.print("Arret");
    float distanceDroite = calculerDistance(BROCHE_TRIGGER_DROITE, BROCHE_ECHO_DROITE);
    float distanceGauche = calculerDistance(BROCHE_TRIGGER_GAUCHE, BROCHE_ECHO_GAUCHE);
    float distanceArriere = calculerDistance(BROCHE_TRIGGER_ARRIERE, BROCHE_ECHO_ARRIERE);
    Serial.print("Distance droite : ");
    Serial.println(calculerDistance(BROCHE_TRIGGER_DROITE, BROCHE_ECHO_DROITE));
    Serial.print("Distance gauche : ");
    Serial.println(calculerDistance(BROCHE_TRIGGER_GAUCHE, BROCHE_ECHO_GAUCHE));

    if (distanceDroite > DISTANCE_OBSTACLE ) { // pas d'obstacle a droite et un obstacle devant
      tournerADroite(1600);
      lcd.clear();
      lcd.print("Tourner a droite");
      distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);

      while (distanceAvant > DISTANCE_OBSTACLE) {  
        avancer(600);
        lcd.clear();
        lcd.print("Avancer");
        distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);
      }
    } else if (distanceGauche > DISTANCE_OBSTACLE ) { // pas d'obstacle a gauche et un obstacle devant ,et a droite 
      tournerAGauche(1600);
      lcd.clear();
      lcd.print("Tourner a gauche");
      distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);

      while (distanceAvant > DISTANCE_OBSTACLE) {
        avancer(600);
        lcd.clear();
        lcd.print("Avancer");
        distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);
      }
    } else if (distanceArriere > DISTANCE_OBSTACLE) { //pas d'obstacle derrière et un obstacle devant , a droite et a gauche
      reculer(2000);
      lcd.clear();
      lcd.print("Reculer");
      distanceDroite = calculerDistance(BROCHE_TRIGGER_DROITE, BROCHE_ECHO_DROITE);
      distanceGauche = calculerDistance(BROCHE_TRIGGER_GAUCHE, BROCHE_ECHO_GAUCHE);

      if (distanceDroite > DISTANCE_OBSTACLE) { //pas d'obstacle derrière et pas d'obstacle a droite
        tournerADroite(1600);
        lcd.clear();
        lcd.print("Tourner a droite");
        distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);

        while (distanceAvant > DISTANCE_OBSTACLE) {
          avancer(600);
          lcd.clear();
          lcd.print("Avancer");
          distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);
        }
      } else if (distanceGauche > DISTANCE_OBSTACLE) { //pas d'obstacle derrière et pas d'obstacle a gauche
        tournerAGauche(1600);
        lcd.clear();
        lcd.print("Tourner a gauche");
        distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);

        while (distanceAvant > DISTANCE_OBSTACLE) {
          avancer(600);
          lcd.clear();
          lcd.print("Avancer");
          distanceAvant = calculerDistance(BROCHE_TRIGGER_AVANT, BROCHE_ECHO_AVANT);
        }
      }
    } else { //obstacles entouraient le robot
      arreterMouvement(3000);
      lcd.clear();
      lcd.print("Arret");
    }
  } else { //Arret pour recommencer 
    arreterMouvement(3000);
    lcd.clear();
    lcd.print("Arret");
  }
}
