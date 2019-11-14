#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

//button 
int bst = 3;
int bup = 4;
int bdw = 5;
int bsx = 6;
int bdx = 7;

bool start = false;

byte divisorio[8] = {
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
};

void printlcd(int c1, int c2, String text){
  lcd.setCursor(c1,c2);
  lcd.print(text);
}

void printbyte(int c1, int c2, int c3){
    lcd.setCursor(c1,c2);
    lcd.write(byte(c3));
}

void TopStructure(String text){
  int cursore = ((20/2) - (text.length()/2));
  printlcd(cursore,0,text);
}

void setup() {
  lcd.begin (20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.createChar(0, divisorio);
  pinMode(bst, INPUT);
  pinMode(bup, INPUT);
  pinMode(bdw, INPUT);
  pinMode(bsx, INPUT);
  pinMode(bdx, INPUT);
  TopStructure("Premi Start");
  randomSeed(analogRead(0));
}

int matrix[4][4]= {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12},
  {13, 14, 15, 0}
};

int x = 3; 
int y = 3;
int ponte;
int mosse = 0;

void loop() {
  if(digitalRead(bst) == HIGH){
    lcd.clear();
    if(start){
      TopStructure("Premi Start");
      start = false;
    }else{
      genMatrix();
      mosse = 0;
      printMatrix();
      start = true;
    }
    delay(200);
  }
  if(digitalRead(bup) == HIGH && start){
    up();
    printMatrix();
    delay(200);
  }
  if(digitalRead(bdx) == HIGH && start){
    dx();
    printMatrix();
    delay(200);
  }
  if(digitalRead(bdw) == HIGH && start){
    dw();
    printMatrix();
    delay(200);
  }
  if(digitalRead(bsx) == HIGH && start){
    sx();
    printMatrix();
    delay(200);
  }
}

void grafica(){
  printlcd(14,0, "Mosse");
  printlcd(16,2, String(mosse));
  printbyte(12, 0, 0);
  printbyte(12, 1, 0);
  printbyte(12, 2, 0);
  printbyte(12, 3, 0);
}

void printMatrix(){
  lcd.clear();
  int c = 0;
  grafica();
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(matrix[i][j] == 0){
        printlcd(c + j, i, " ");
      }else{
        printlcd(c + j, i, String(matrix[i][j]));        
      }
      c += 2;
    }
    c = 0;
  }
}

void resetMatrix(){
  int c = 1;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      matrix[i][j] = c;
      c++;
    }
  }
}

void genMatrix(){
  resetMatrix();
  int ponte;
  int rnd = random(1, 5);
  for(int i = 0; i < 200; i++){
    switch(rnd){
      case 1:
        up();
        break;
      case 2:
        dx();
        break;
      case 3:
        dw();
        break;
      case 4:
        sx();
        break;
    }
    rnd = random(1, 5);
  }
}

void up(){
  if(y <= 3 && y > 0){
    ponte = matrix[y-1][x];
    matrix[y-1][x] = 0;
    matrix[y][x] = ponte;
    y--;
    mosse++;
  } 
}
void dx(){
  if(x < 3 && x >= 0){
    ponte = matrix[y][x+1];
    matrix[y][x+1] = 0;
    matrix[y][x] = ponte;
    x++;
    mosse++;
  }
}
void dw(){
  if(y < 3 && y >= 0){
    ponte = matrix[y+1][x];
    matrix[y+1][x] = 0;
    matrix[y][x] = ponte;
    y++;
    mosse++;
  }
}
void sx(){
  if(x <= 3 && x > 0){
    ponte = matrix[y][x-1];
    matrix[y][x-1] = 0;
    matrix[y][x] = ponte;
    x--;
    mosse++;
  }
}
