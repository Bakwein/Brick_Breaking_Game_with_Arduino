#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define width 128
#define height 64

//KARDESIM CALMA KODU KAPA EKRANI

Adafruit_SSD1306 display(width, height, &Wire, -1);

static byte menu = 0;
byte up, down, select;

static int can = 3;
static int score = -1;
//int top_kenar = 2;

//int tugla_genislik;
//int tugla_yukseklik;

int asagi_buton_kontrol = 0;
int yukari_buton_kontrol = 0;
int select_kontrol = 0;
int mode = 1;

class Top 
{
  public:
   int topX;
   int topY;
   int dirX;
   int dirY;
   int top_kenar;

   Top()
   {
    topX = 0;
    topY = 0;
    dirX = 0;
    dirY = 0;
    top_kenar = 2;
   }

   Top(int topX_, int topY_, int dirX_, int dirY_)
   {
    topX = topX_;
    topY = topY_;
    dirX = dirX_;
    dirY = dirY_;
    top_kenar = 2;
   }

   int getTopX()
   {
     return topX;
   }

   void setTopX(int topX_)
   {
    topX = topX_;
   }
  
   int getTopY()
   {
    return topY;
   }

   void setTopY(int topY_)
   {
    topY = topY_;
   }

   int getDirX()
   {
    return dirX;
   }

   void setDirX(int dirX_)
   {
    dirX = dirX_;
   }

   int getDirY()
   {
    return dirY;
   }

   void setDirY(int dirY_)
   {
    dirY = dirY_;
   }

   int getTopKenar()
   {
    return top_kenar;
   }

   void setTopKenar(int top_kenar_)
   {
      top_kenar = top_kenar_;
   }
};

Top top = Top(0,0,0,0);

const byte digits[10][7] =
{
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

const unsigned char bitmap_kalp [] PROGMEM = {
  0x50, 0xf8, 0x70, 0x20
};

void setup()
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A14, OUTPUT);
  pinMode(A15, OUTPUT);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

  randomSeed(analogRead(A2));

  display.setRotation(3);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  
}

void loop()
{
  //delay(100);
  display.display();

  //up = digitalRead(10);
  
  //down = digitalRead(8);
  //select = digitalRead(9);

  int ldr = analogRead(A0);
  if (ldr > 500) display.invertDisplay(true);
  else display.invertDisplay(false);

  
  if ((digitalRead(8) == LOW) && (asagi_buton_kontrol == 0)) //assa
  {
    asagi_buton_kontrol = 1;
    if(menu == 0)
    {
      menu = 1;
    } 
    else if(menu == 1)
    {
      menu = 41;
    }
    else if(menu == 41)
    {
      menu = 0;
    }
    else if(menu == 42)
    {
      menu = 43;
    }
    else if(menu == 43)
    {
      menu = 42;
    }
  }
  else if ((digitalRead(10) == LOW) && (yukari_buton_kontrol == 0)) //yukar
  {
    yukari_buton_kontrol = 1;
    if (menu == 1)
    {
      menu = 0;
    }
    else if(menu == 0)
    {
      menu = 41;
    }
    else if(menu == 41)
    {
      menu = 1;
    }
    else if(menu == 42)
    {
      menu = 43;
    }
    else if(menu == 43)
    {
      menu = 42;
    }
  }
  else if ((digitalRead(9) == LOW) && (select_kontrol == 0)) //selectttt
  {
    select_kontrol = 1;
    if (menu == 0)
    {
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, HIGH);
      can = 3;
      score = -1;
      scoreUpdate();
      menu = 3;
      Start();
    }
    else if (menu == 1)
    {
      menu = 2;
    }
    else if(menu == 41) //cikinca cikis yapilan ekran gelsin
    {
      if(mode == 1)
      {
        menu = 42;
      }
      else if(mode == 0)
      {
        menu = 43;
      }
    }
    else if(menu == 42 || menu == 43)
    {
      menu = 0;
    }
  }

  if((digitalRead(8) == HIGH) && (asagi_buton_kontrol == 1))
  {
    asagi_buton_kontrol = 0;
  }
  if((digitalRead(10) == HIGH) && (yukari_buton_kontrol == 1))
  {
    yukari_buton_kontrol = 0;
  }
  if(digitalRead(9) == HIGH && (select_kontrol == 1))
  {
    select_kontrol = 0;
  }

  

  // GIRIS EKRANI AYARLARI BASLIYOR
  display.clearDisplay();
  display.setCursor(6, 30);
  display.print("SEFA GAME");
  display.drawLine(0, 39, 65, 39, SSD1306_WHITE);

  if (menu == 0)
  {
    display.setCursor(0, 60); display.print("> START");
    display.setCursor(0, 80); display.print("  QUIT");
    display.setCursor(0, 100); display.print("  SETTINGS");
  }
  else if (menu == 1)
  {
    display.setCursor(0, 60); display.print("  START");
    display.setCursor(0, 80); display.print("> QUIT");
    display.setCursor(0, 100); display.print("  SETTINGS");
  }
  
  else if (menu == 2)
  {
    display.setCursor(0, 55); display.print("THANK  YOU\n FOR YOUR\n INTEREST\n  IN OUR\n   GAME");
  }
  else if (menu == 8)
  {
    display.setCursor(0, 50); display.print(" GAME OVER");
    display.setCursor(0, 75); display.print(" Score:");
    display.setCursor(45, 75); display.print(score);
    display.display();
    delay(3500);
    menu = 0;
  }
  else if (menu==9)
  {
    display.setCursor(0, 50); display.print(" WELL DONE");
    display.setCursor(0, 75); display.print(" Score:");
    display.setCursor(45, 75); display.print(score);
    display.display();
    delay(3500);
    menu = 0;
  }
  else if(menu == 41)
  {
    display.setCursor(0, 60); display.print("  START");
    display.setCursor(0, 80); display.print("  QUIT");
    display.setCursor(0, 100); display.print("> SETTINGS");
  }
  else if(menu == 42)
  {
    display.clearDisplay();
    display.setCursor(0, 5);
    display.print("RETURN:\nYELLOW\n\nSWAP MODE:\nGREEN OR\nBLUE");
    display.setCursor(0, 75); display.print("> MODE:ON");
    mode = 1;
  }
  else if(menu == 43)
  {
    display.clearDisplay();
    display.setCursor(0, 5);
    display.print("RETURN:\nYELLOW\n\nSWAP MODE:\nGREEN OR\nBLUE");
    display.setCursor(0, 75); display.print("> MODE:OFF");
    mode = 0;
  }
  // GIRIS EKRANI AYARLARI BITIYOR
}

/*
struct Tugla {
  int x;
  int y;
  bool aktif_mi;
  String renk;
};
*/

class Tugla
{
  public:
    int x;
    int y;
    bool aktif_mi;
    String renk;
    int tugla_genislik;
    int tugla_yukseklik;

    Tugla()
    {
      x = 0;
      y = 0;
      aktif_mi = false;
      renk = "arda";
      tugla_genislik = 0;
      tugla_yukseklik = 0;
    }

    Tugla(int x_, int y_, bool aktif_mi_, String renk_, int tugla_genislik_, int tugla_yukseklik_ )
    {
      x = x_;
      y = y_;
      aktif_mi = aktif_mi_;
      renk = renk_;
      tugla_genislik = tugla_genislik_;
      tugla_yukseklik = tugla_yukseklik_;
    }

    int getX() {
      return x;
    }

    void setX(int x_) {
      x = x_;
    }

    int getY() {
      return y;
    }

    void setY(int y_) {
      y = y_;
    }

    bool getAktifMi() {
      return aktif_mi;
    }

    void setAktifMi(bool aktif_mi_) {
      aktif_mi = aktif_mi_;
    }

    String getRenk() {
      return renk;
    }

    void setRenk(String renk_) {
      renk = renk_;
    }

    int getTuglaGenislik() {
      return tugla_genislik;
    }

    void setTuglaGenislik(int tugla_genislik_) {
      tugla_genislik = tugla_genislik_;
    }

    int getTuglaYukseklik() {
      return tugla_yukseklik;
    }

    void setTuglaYukseklik(int tugla_yukseklik_) {
      tugla_yukseklik = tugla_yukseklik_;
    }
};


Tugla *tuglalar;
void Start()
{
  int kontrol_edilecek_sayi = 4;
  int size = 0;

  if (menu == 3) {
    tuglalar = new Tugla[6];
    size = 6;
    int idx = 0;
    for (int i = 3; i < 54; i = i + 30)
    {
      for (int j = 0; j < 25 - 4; j = j + 7)
      {
        /*
        tuglalar[idx].x = i;
        tuglalar[idx].y = j;
        tuglalar[idx].aktif_mi = true;
        tuglalar[idx].renk = "beyaz";
        */
        tuglalar[idx] = Tugla(i,j,true,"beyaz",-1,-1);
        idx++;
      }
    }
  }

  else if (menu == 4) {
    tuglalar = new Tugla[18];
    size = 18;
    int idx = 0;
    for (int i = 3; i < 64 - 7; i = i + 10)
    {
      for (int j = 0; j < 25 - 4; j = j + 7)
      {
        /*
        tuglalar[idx].x = i;
        tuglalar[idx].y = j;
        tuglalar[idx].aktif_mi = true;
        tuglalar[idx].renk = "beyaz";
        */
        tuglalar[idx] = Tugla(i,j,true,"beyaz",-1,-1);
        idx++;
      }
    }
  }

  else if (menu == 5) {
    //struct Tugla tuglalar[40];
    tuglalar = new Tugla[18];
    size = 18;
    int idx = 0;
    for (int i = 3; i < 64 - 7; i = i + 10)
    {
      for (int j = 0; j < 25 - 4; j = j + 7)
      {
        /*
        tuglalar[idx].x = i;
        tuglalar[idx].y = j;
        tuglalar[idx].aktif_mi = true;
        tuglalar[idx].renk = "beyaz";
        */
        tuglalar[idx] = Tugla(i,j,true,"beyaz",-1,-1);
        idx++;
      }
    }
  }

  else if (menu == 6) {
    //struct Tugla tuglalar[40];
    tuglalar = new Tugla[18];
    size = 18;
    int idx = 0;
    for (int i = 3; i < 64 - 7; i = i + 10)
    {
      for (int j = 0; j < 25 - 4; j = j + 7)
      {
        /*
        tuglalar[idx].x = i;
        tuglalar[idx].y = j;
        tuglalar[idx].aktif_mi = true;
        tuglalar[idx].renk = "siyah";
        */
        tuglalar[idx] = Tugla(i,j,true,"siyah",-1,-1);
        idx++;
      }
    }
  }

  else if (menu == 7) {
    //struct Tugla tuglalar[40];
    tuglalar = new Tugla[1];
    size = 1;
    /*
    tuglalar[0].x = 28;
    tuglalar[0].y = 0;
    tuglalar[0].aktif_mi = true;
    tuglalar[0].renk = "beyaz";
    */
    tuglalar[0] = Tugla(28,0,true,"beyaz",-1,-1);
  }

  int drop_y[size] = {0};
  int drop_x[size] = {0};
  //diger kisimlar devamina
  display.clearDisplay();

  if (menu == 3)
  {
    display.setCursor(0, 55); display.print("  LEVEL 1");
    display.drawLine(0, 63, 65, 63, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
  else if (menu == 4)
  {
    delay(500);
    display.setCursor(0, 55); display.print("  LEVEL 2");
    display.drawLine(0, 63, 65, 63, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
  else if (menu == 5)
  {
    delay(500);
    display.setCursor(0, 55); display.print("  LEVEL 3");
    display.drawLine(0, 63, 65, 63, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
  else if (menu == 6)
  {
    delay(500);
    display.setCursor(0, 55); display.print("  LEVEL 4");
    display.drawLine(0, 63, 65, 63, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
  else if (menu == 7)
  {
    delay(500);
    display.setCursor(0, 55); display.print("  LEVEL 5");
    display.drawLine(0, 63, 65, 63, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
  display.clearDisplay();
  top.setTopX(32);
  top.setTopY(120);
  top.setDirX(2);
  top.setDirY(-2);

  //int topX = 32;
  //int topY = 120;
  //int dirX = 2;
  //int dirY = -2;
  //Serial.println("while oncesi");
  //Serial.println(tuglalar[0].x);
  //Serial.println(tuglalar[1].x);
  while (true)
  {
    if (menu == 8 || menu == 9) break;

    int konum = analogRead(A1);
    int xPos = map(konum, 0, 1023, 0, 43);

    display.clearDisplay();
    display.fillRect(xPos, 126, 20, 2, SSD1306_WHITE);

    //deneme(tuglalar,size);
    //tuglalari bastirma


    for (int j = 0; j < size; j++) {
      if (menu == 3)
      {
        if (score == 6)
        {
          display.display();
          menu = 4;
          Start();
        }

        if (tuglalar[j].getAktifMi()) {
          display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 25, 4, SSD1306_WHITE);
          tuglalar[j].setTuglaGenislik(25);
          tuglalar[j].setTuglaYukseklik(4);
          //tugla_genislik = 25;
          //tugla_yukseklik = 4;
        }
      }

      else if (menu == 4)
      {
        if (tuglalar[j].getAktifMi()) {
          display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 7, 4, SSD1306_WHITE);
          tuglalar[j].setTuglaGenislik(7);
          tuglalar[j].setTuglaYukseklik(4);
        }
        if (score == 24)
        {
          menu = 5;
          Start();
        }
      }

      else if (menu == 5)
      {
        display.drawLine(0, 20, 22, 20, SSD1306_WHITE);
        display.drawLine(40, 20, 63, 20, SSD1306_WHITE);
        if (tuglalar[j].getAktifMi()) {
          display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 7, 4, SSD1306_WHITE);
          tuglalar[j].setTuglaGenislik(7);
          tuglalar[j].setTuglaYukseklik(4);
        }
        if (score == 42)
        {
          menu = 6;
          Start();
        }
      }

      else if (menu == 6)
      {
        if (tuglalar[j].getAktifMi()) {
          if (tuglalar[j].renk == "siyah") display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 7, 4, SSD1306_BLACK);
          else if (tuglalar[j].renk == "beyaz") display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 7, 4, SSD1306_WHITE);
          tuglalar[j].setTuglaGenislik(7);
          tuglalar[j].setTuglaYukseklik(4);
        }
        if (score == 60)
        {
          menu = 7;
          Start();
        }
      }

      else if (menu == 7)
      {
        display.drawLine(0, 20, 30, 20, SSD1306_WHITE);
        display.drawLine(34, 20, 63, 20, SSD1306_WHITE);
        if (tuglalar[j].getAktifMi()) {
          display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 8, 4, SSD1306_WHITE);
          tuglalar[j].setTuglaGenislik(8);
          tuglalar[j].setTuglaYukseklik(4);
        }
        if (score == 61)
        {
          menu = 9;
          Start();
        }
      }

    }

    /*
    top.setTopX(top.getTopX()+top.getDirX());
    //topY += dirY;
    top.setTopY(top.getTopY()+top.getDirY());
    */
    if(menu==3) delay(25);
    else if(menu==4) delay(17);
    else if(menu==5) delay(10);
    else if(menu==6) delay(5);
    else if(menu==7) delay(1);


    for (int s = 0; s < size; s++)
    {
      if (tuglalar[s].getAktifMi() && tuglalar[s].getRenk() == "beyaz")
      {
        if (top.getTopX() < tuglalar[s].getX() + tuglalar[s].getTuglaGenislik()  &&
            top.getTopX() + top.getTopKenar() > tuglalar[s].getX() &&
            top.getTopY() <= tuglalar[s].getY() + tuglalar[s].getTuglaYukseklik() &&
            top.getTopY() + top.getTopKenar() > tuglalar[s].getY()) //carpisma var mi
        {
          tuglalar[s].setAktifMi(false);
          //score güncellendi
          scoreUpdate();

          //drop
          //randomSeed(42);
          int rastgele_sayi = random(0, 10);
          if (rastgele_sayi == kontrol_edilecek_sayi) // drop zamani
          {
            drop_y[s] = top.getTopY() + 1;
            drop_x[s] = top.getTopX();
          }


          if ((top.getTopY() + top.getTopKenar() >= tuglalar[s].getY()) || (tuglalar[s].getY() + tuglalar[s].getTuglaYukseklik() >= top.getTopY())) //ust alt
          {

            top.setDirY(-top.getDirY());
          }
          else if ((top.getTopX() + top.getTopKenar() >= tuglalar[s].getX()) || (tuglalar[s].getX() + tuglalar[s].getTuglaGenislik()  >= top.getTopX())) //sol sag
          {
            top.setDirX(-top.getDirX());
            //dirX = -dirX;
          }
        }
      }
      else if (tuglalar[s].getAktifMi() && tuglalar[s].renk == "siyah")
      {
        if (top.getTopX() < tuglalar[s].getX() + tuglalar[s].getTuglaGenislik()  &&
            top.getTopX() + top.getTopKenar() > tuglalar[s].getX() &&
            top.getTopY() <= tuglalar[s].getY() + tuglalar[s].getTuglaYukseklik() &&
            top.getTopY() + top.getTopKenar() > tuglalar[s].getY()) //carpisma var mi
        {
          tuglalar[s].setRenk("beyaz");

          if ((top.getTopY() + top.getTopKenar() >= tuglalar[s].getY()) || (tuglalar[s].getY() + tuglalar[s].getTuglaYukseklik() >= top.getTopY())) //ust alt
          {
            top.setDirY(-top.getDirY());
          }
          else if ((top.getTopX() + top.getTopKenar() >= tuglalar[s].getX()) || (tuglalar[s].getX() + tuglalar[s].getTuglaGenislik()  >= top.getTopX())) //sol sag
          {
           top.setDirX(-top.getDirX());
          }
        }
      }
    }


    //SOL-SAG KONTROL
    //if (top.getTopX() <= -1 || top.getTopX() + top.getTopKenar() >= height - 2) {
    /*
    if(top.getTopX() > height - top.getTopKenar() || top.getTopX() < 0 + top.getTopKenar()){
      //Serial.println(("sol sag kenar problem!"));
      //Serial.println(topX);
      top.setDirX(-top.getDirX());
    }
    */

    if(top.getTopX() <= 0)
    {
      top.setTopX(0);
      top.setDirX(-top.getDirX());
    }
    else if(top.getTopX() >= height - top.getTopKenar())
    {
      top.setTopX(height-1);
      top.setDirX(-top.getDirX());
    }

    /*  display.drawLine(0,20,30,20,SSD1306_WHITE);
      display.drawLine(34,20,63,20,SSD1306_WHITE);*/

    if (menu == 5)
    {
      if (top.getTopX() <= 22  &&
          top.getTopX() + top.getTopKenar() >= 0 &&
          top.getTopY() <= 21 &&
          top.getTopY() + top.getTopKenar() > 20)
      {
        top.setDirY(-top.getDirY());
      }
      if (top.getTopX() <= 63  &&
          top.getTopX() + top.getTopKenar() >= 40 &&
          top.getTopY() <= 21 &&
          top.getTopY() + top.getTopKenar() > 20)
      {
        top.setDirY(-top.getDirY());
      }
    }
    else if (menu == 7)
    {
      if (top.getTopX() <= 30  &&
          top.getTopX() + top.getTopKenar() >= 0 &&
          top.getTopY() <= 21 &&
          top.getTopY() + top.getTopKenar() > 20)
      {
        top.setDirY(-top.getDirY());
      }
      if (top.getTopX() <= 63  &&
          top.getTopX() + top.getTopKenar() >= 34 &&
          top.getTopY() <= 21 &&
          top.getTopY() + top.getTopKenar() > 20)
      {
       top.setDirY(-top.getDirY());
      }
    }


    //YUKARI KONTROL!!!!
    //if (top.getTopY() <= -1) {
    //
    //if (top.getTopY() <= 1 /*+ top.getTopKenar()*/) {
    //  //Serial.println("ust kenar sorunu");
    //  //Serial.println(top.getTopY());
    //  top.setDirY(-top.getDirY());
    //}

    if(top.getTopY() <= 0)
    {
      top.setTopY(0);
      top.setDirY(-top.getDirY());

    }
    

    top.setTopX(top.getTopX()+top.getDirX());
    //topY += dirY;
    top.setTopY(top.getTopY()+top.getDirY());
    

    if (top.getTopY() + 2 >= 126)
    {

      if(top.getTopX() < 0 + top.getTopKenar())
      {
        top.setTopX(0);
        top.setDirX(-top.getDirX());
      }
      else if(top.getTopX() > height - top.getTopKenar() )
      {
        top.setTopX(height-1);
        top.setDirX(-top.getDirX());
      }
      bool icinde_mi = false;
      int min_cubuk_x = xPos;
      int max_cubuk_x = xPos + 20;
      if (top.getTopX() < xPos + 20  &&
          top.getTopX() + top.getTopKenar() > xPos &&
          top.getTopY() + top.getTopKenar() >= 126 )
      {
        if (menu == 6)
        {
          for (int j = 0; j < size; j++) {
            if (tuglalar[j].getAktifMi()) {
              display.fillRect(tuglalar[j].getX(), tuglalar[j].getY(), 7, 4, SSD1306_WHITE);
              tuglalar[j].setTuglaGenislik(7);
              tuglalar[j].setTuglaYukseklik(4);
            }
          }
          delay(200);
        }
        icinde_mi = true;
        //Serial.println("haraketli");
        //Serial.println(topX);
        top.setDirY(-top.getDirY());
        //x olayı carpma konumuna gore degisecek

        int neredeyim = top.getTopX() - min_cubuk_x;
        if(mode == 1)
        {
            if (neredeyim < 3) {
            top.setDirX(-4);
          }
          else if (neredeyim < 6) {
            top.setDirX(-3);
          }
          else if (neredeyim < 10) {
            top.setDirX(-2);
          }
          //saglar
          else if (neredeyim < 14) {
            top.setDirX(2);
          }
          else if (neredeyim < 17) {
            top.setDirX(3);
          }
          else if (neredeyim < 20) {
            top.setDirX(4);
          }
        }
        
      }
      
      
      int baslangic_kontrol;
      if (!icinde_mi)
      {
        //burada sonraki frame'i de atarlamamız gerekir

        display.fillCircle(top.getTopX()+top.getDirX(), top.getTopY()+top.getDirY(), 1, SSD1306_WHITE);
        display.display();
        if (can == 3)
        {
          baslangic_kontrol = xPos;
          can--;
          digitalWrite(13, LOW);
          //top.getTopX() = min_cubuk_x + 10;
          top.setTopX(min_cubuk_x + 10);
          top.setDirY(-top.getDirY());
          while (baslangic_kontrol == xPos)
          {
            konum = analogRead(A1);
            xPos = map(konum, 0, 1023, 0, 43);
          }
        }
        else if (can == 2)
        {
          baslangic_kontrol = xPos;
          can--;
          digitalWrite(12, LOW);
          //top.getTopX() = min_cubuk_x + 10;
          top.setTopX(min_cubuk_x + 10);
          top.setDirY(-top.getDirY());
          while (baslangic_kontrol == xPos)
          {
            konum = analogRead(A1);
            xPos = map(konum, 0, 1023, 0, 43);
          }
        }
        else if (can == 1)
        {
          can--;
          digitalWrite(11, LOW);
          //SKOR EKRANI EKLENCEK
          delay(1000);
          display.clearDisplay();
          menu = 8;
          display.display();
          //break;
        }
      }
    }
    //Serial.println(topX);
    //Serial.println(topY);
    
    display.fillCircle(top.getTopX(), top.getTopY(), 1, SSD1306_WHITE);

    for (int s = 0; s < size; s++) {
      if (drop_y[s] != 0 && drop_y[s] + 4 != 126)
      {
        display.drawBitmap(drop_x[s], drop_y[s], bitmap_kalp, 5, 4, SSD1306_WHITE);
        drop_y[s] += 1;
      }
      else if (drop_y[s] + 4 == 126)
      {
         drop_y[s] = 0;
        /*
          bool icinde_mi = false;
          int min_cubuk_x = xPos;
          int max_cubuk_x = xPos+20;
          if(topX < max_cubuk_x && topX+1 >= min_cubuk_x)
          {
          icinde_mi =true;
        */
        int min_cubuk_x = xPos;
        int max_cubuk_x = xPos + 20;
        if (drop_x[s] < max_cubuk_x && drop_x[s] + 4 >= min_cubuk_x) //toplandi
        {
          if (can == 1)
          {
            can++;
            
            if (can == 2)
            {
              digitalWrite(12, HIGH);
              continue;
            }

          }
          else if (can == 2)
          {
            can++;
            if (can == 3)
            {
              digitalWrite(13, HIGH);
              continue;
            }
          }
        }

      }

    }

    display.display();

  }
  display.display();
}

void displayDigit(int digit, int basamak)
{
  byte *segment = (byte *)digits[digit];

  if (basamak == 10)
  {
    digitalWrite(7, segment[0]);
    digitalWrite(A3, segment[1]);
    digitalWrite(A4, segment[2]);
    digitalWrite(A5, segment[3]);
    digitalWrite(A6, segment[4]);
    digitalWrite(A7, segment[5]);
    digitalWrite(A8, segment[6]);
  }
  else if (basamak == 1)
  {
    digitalWrite(A9, segment[0]);
    digitalWrite(A10, segment[1]);
    digitalWrite(A11, segment[2]);
    digitalWrite(A12, segment[3]);
    digitalWrite(A13, segment[4]);
    digitalWrite(A14, segment[5]);
    digitalWrite(A15, segment[6]);
  }
}

void scoreUpdate()
{
  score++;
  for (int i = 0; i < 2; i++)
  {
    int digit;
    if (i == 0)
    {
      digit = score / 10;
      displayDigit(digit, 10);
    }
    else if (i == 1)
    {
      digit = score % 10;
      displayDigit(digit, 1);
    }
  }
}