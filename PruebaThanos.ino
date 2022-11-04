#include <LiquidCrystal.h>

  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long powerAvenger;
char * Heros[6] = { "Gamora", "Loki", "El coleccionista", "Star lord", "Dr Strange", "Vision" };
char * Gema[6] = { "Alma", "Espacio", "Realidad", "Poder", "Tiempo", "Mente" };
char * GemaThanos[6];
int LEDS[6] = { 6, 7, 8, 9, 10, 13};
long powerThanos;  
long valuePowerThanos;
int posHero = 0;
int posThanos = 0;
int gemasPendientes[6];
int gemasObtenidas = 0;
int btnReady;

void setup() {
  Serial.begin(9600);
  powerOff(6,13,1);
  pinMode(15, INPUT);
  lcd.begin(16, 2);
}

void powerOff(int min, int max,int state){
  char *stateOf = "LOW";
  if( state== 0){
    stateOf = "HIGH";
  }
  for(int i = min ; i <= max ; i ++){
    pinMode(i, *stateOf);
  }
}


void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Pulse el boton");
  lcd.setCursor(0, 1);
  lcd.print("para pelear");
  
  if(digitalRead(15) != 1) {
    lcd.clear();
    powerAvenger = random(100, 200);
    powerThanos = analogRead(A0);
    powerOff(6,14,0);
    valuePowerThanos = map(powerThanos, 0, 1023, 90, 190);
    
    if(gemasObtenidas == 6) {
      for (int i = 6; i < 14  ; i++) {
        digitalWrite(i, HIGH);
      }
      digitalWrite(6, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("No me quiero ir sr stark.");
    }
    
    for (int i = 0; i < 6 ; i++) {
      if (strcmp(GemaThanos[i], NULL) == 0) {
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Iniciando pelea");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(Heros[i]);
        lcd.setCursor(0, 1);
        lcd.print(Gema[i]);
        delay(1000);
        if (valuePowerThanos > powerAvenger) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Gema obtenida");
          lcd.setCursor(0, 1);
          lcd.print(Gema[i]);
          GemaThanos[posThanos] = Gema[i];
          posThanos++;
          gemasObtenidas++;
          break;
        }
        else {
          lcd.clear();
          gemasPendientes[i] = posHero;
          lcd.setCursor(0, 0);
          lcd.print("Le partieron la");
          lcd.setCursor(0, 1);
          lcd.print("Madre a thanos.");
          break;
        }
      }
    }
    posHero++;
    delay(1000);
    lcd.clear();
  }
}
