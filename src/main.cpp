#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <DS3231.h>
DS3231  rtc(SDA, SCL);
Time  t;

int len = 6; int gtlen;  // Lên là trừ
int xuong = 5; int gtxuong; // Xuống là cộng
int menu = 7; int gtmenu; 
int macdinh = 1;
int relay1 = 9; int relay2 = 10;

int contro = 0; int contro_dk = 5; int hang = 0;

int congtru_tong = 0; int congtru_menudk = 0;
int demtong = 0;

int ngay = 1; int thang = 1; int namng = 0; int namtr = 0; int namch = 0; int namdv = 0; int namtong = 0; //SETUP DATE
int gio = 0; int phut = 0; int giay = 0; //SETUP TIME

int ton1 = 0; int pon1 = 0; int tof1 = 0; int pof1 = 0; //LỆNH 1
int ton2 = 0; int pon2 = 0; int tof2 = 0; int pof2 = 0; //LỆNH 2
int ton3 = 0; int pon3 = 0; int tof3 = 0; int pof3 = 0; //LỆNH 3
int ton4 = 0; int pon4 = 0; int tof4 = 0; int pof4 = 0; //LỆNH 4
int ton5 = 0; int pon5 = 0; int tof5 = 0; int pof5 = 0; //LỆNH 5
int re1 = 1; int re2 = 1; int re3 = 1; int re4 = 1; int re5 = 1; //RELAY

void manhinh()  // HIỂN THỊ MÀN HÌNH CHÍNH
{
  lcd.setCursor(0,0);
  lcd.print("DATE: ");
  lcd.setCursor(0,1);
  lcd.print("TIME: ");
  lcd.setCursor(6,0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(6,1);
  lcd.print(rtc.getTimeStr());  
}

void menu_tong() // HIỂN THỊ MENU TỔNG
{
  if (congtru_tong == 0)
  {
    lcd.clear();
    lcd.print(">BACK");
    lcd.setCursor(0, 1);
    lcd.print(" DATE");  
  }
  else if (congtru_tong == 1)
  {
    lcd.clear();
    lcd.print(" BACK");
    lcd.setCursor(0, 1);
    lcd.print(">DATE");    
  }
  else if (congtru_tong == 2)
  {
    lcd.clear();
    lcd.print(">TIME");
    lcd.setCursor(0, 1);
    lcd.print(" DIEU KHIEN");   
  }
  else if (congtru_tong == 3)
  {
    lcd.clear();
    lcd.print(" TIME");
    lcd.setCursor(0, 1);
    lcd.print(">DIEU KHIEN");    
  }
}

void chonmenu_tong() // CHỌN MENU TỔNG
{
  switch (congtru_tong) 
  {
    case 0:
      //BACK
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SETUP DATE");
      lcd.setCursor(12,1);
      lcd.print("BACK");      
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SETUP TIME");
      lcd.setCursor(12,1);
      lcd.print("BACK");       
      break;
    case 3:
      // LỆNH ĐIỀU KHIỂN
      break;                       
  }
}

void menu_dieukhien() // HIỂN THỊ MENU ĐIỀU KHIỂN
{
  if (congtru_menudk == 0)
  {
    lcd.clear();
    lcd.print(">BACK");
    lcd.setCursor(0, 1);
    lcd.print(" LENH 1");  
  }
  else if (congtru_menudk == 1)
  {
    lcd.clear();
    lcd.print(" BACK");
    lcd.setCursor(0, 1);
    lcd.print(">LENH 1");    
  }
  else if (congtru_menudk == 2)
  {
    lcd.clear();
    lcd.print(">LENH 2");
    lcd.setCursor(0, 1);
    lcd.print(" LENH 3");    
  } 
  else if (congtru_menudk == 3)
  {
    lcd.clear();
    lcd.print(" LENH 2");
    lcd.setCursor(0, 1);
    lcd.print(">LENH 3");    
  } 
  else if (congtru_menudk == 4)
  {
    lcd.clear();
    lcd.print(">LENH 4");
    lcd.setCursor(0, 1);
    lcd.print(" LENH 5");    
  } 
  else if (congtru_menudk == 5)
  {
    lcd.clear();
    lcd.print(" LENH 4");
    lcd.setCursor(0, 1);
    lcd.print(">LENH 5");    
  }        
}

void chonmenu_dieukhien() // CHỌN MENU ĐIỀU KHIỂN
{
  switch (congtru_menudk) 
  {
    case 0:
      //BACK
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TON: ");
      lcd.setCursor(11,0);
      lcd.print("RE: ");      
      lcd.setCursor(0,1);
      lcd.print("TOF: ");
      lcd.setCursor(12,1);
      lcd.print("BACK");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TON: ");
      lcd.setCursor(11,0);
      lcd.print("RE: ");      
      lcd.setCursor(0,1);
      lcd.print("TOF: ");
      lcd.setCursor(12,1);
      lcd.print("BACK");     
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TON: ");
      lcd.setCursor(11,0);
      lcd.print("RE: ");      
      lcd.setCursor(0,1);
      lcd.print("TOF: ");
      lcd.setCursor(12,1);
      lcd.print("BACK");     
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TON: ");
      lcd.setCursor(11,0);
      lcd.print("RE: ");      
      lcd.setCursor(0,1);
      lcd.print("TOF: ");
      lcd.setCursor(12,1);
      lcd.print("BACK");       
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TON: ");
      lcd.setCursor(11,0);
      lcd.print("RE: ");      
      lcd.setCursor(0,1);
      lcd.print("TOF: ");
      lcd.setCursor(12,1);
      lcd.print("BACK");       
      break;                             
  }
}

void HTset(int &ton, int &pon, int &tof, int &pof, int &re) //Hiển thị Setup ON/OFF
{
  if (ton < 10){
    lcd.setCursor(5,0); lcd.print("0");
    lcd.setCursor(6,0); lcd.print(ton);} 
  else
    {lcd.setCursor(5,0); lcd.print(ton);}

  lcd.setCursor(7,0); lcd.print(":");

  if (pon < 10){
    lcd.setCursor(8,0); lcd.print("0"); 
    lcd.setCursor(9,0); lcd.print(pon);} 
  else
    {lcd.setCursor(8,0); lcd.print(pon);}    

  lcd.setCursor(14,0); lcd.print(re); //relay 

  if (tof < 10){
    lcd.setCursor(5,1); lcd.print("0");
    lcd.setCursor(6,1); lcd.print(tof);}
  else
    {lcd.setCursor(5,1); lcd.print(tof);}

  lcd.setCursor(7,1); lcd.print(":");

  if (pof < 10){
    lcd.setCursor(8,1); lcd.print("0"); 
    lcd.setCursor(9,1); lcd.print(pof);}
  else
    {lcd.setCursor(8,1); lcd.print(pof);}    

  lcd.setCursor(contro_dk, hang); 
  lcd.cursor();
  delay(50);   
}

void on(int &relay) //Lệnh Bật
{
    if(relay == 1){
      if (digitalRead(relay1) == LOW)
        digitalWrite(relay1, HIGH);
      else digitalWrite(relay1, HIGH);  }

    else if(relay == 2){
      if (digitalRead(relay2) == LOW)
        digitalWrite(relay2, HIGH);
      else digitalWrite(relay2, HIGH);  }

    else if(relay == 3){
      if (digitalRead(relay1) == LOW)
        digitalWrite(relay1, HIGH);
      else digitalWrite(relay1, HIGH);
      if (digitalRead(relay2) == LOW)
        digitalWrite(relay2, HIGH);
      else digitalWrite(relay2, HIGH); }  
}
void off(int &relay) //Lệnh TẮT
{
    if(relay == 1){
      if (digitalRead(relay1) == HIGH)
        digitalWrite(relay1, LOW);
      else digitalWrite(relay1, LOW); }
    
    else if(relay == 2){
      if (digitalRead(relay2) == HIGH)
        digitalWrite(relay2, LOW);
      else digitalWrite(relay2, LOW); }    
    
    else if(relay == 3){
      if (digitalRead(relay1) == HIGH)
        digitalWrite(relay1, LOW);
      else digitalWrite(relay1, LOW);
      if (digitalRead(relay2) == HIGH)
        digitalWrite(relay2, LOW);
      else digitalWrite(relay2, LOW); }          
}

void CongRelay(int &relay) //Cộng relay
{
  relay ++;
  if (relay > 3)
    relay = 1;
}
void TruRelay(int &relay) //Trừ Relay
{
  relay --;
  if (relay < 1)
    relay = 3;
}

void CongGio(int &ton, int &tof) //+ Giờ ON/OFF
{
  if (hang == 0){ //GIỜ ON 
    ton ++;
    if (ton > 23)
      ton = 0; } 
  else if (hang == 1){ //GIỜ OFF
    tof ++;
    if (tof > 23)
      tof = 0; }
}
void CongPhut(int &pon, int &pof) //+ Phút ON/OFF
{
  if (hang == 0){ //PHÚT ON
    pon ++;
    if (pon > 59)
      pon = 0; } 
  else if (hang == 1){ //PHÚT OFF
    pof ++;
    if (pof > 59)
      pof = 0; }
}
void TruGio(int &ton, int &tof) //- Giờ ON/OFF
{
  if (hang == 0){ //GIỜ ON 
    ton --;
    if (ton < 0)
      ton = 23; } 
  else if (hang == 1){ //GIỜ OFF
    tof --;
    if (tof < 0)
      tof = 23; }
}
void TruPhut(int &pon, int &pof) //- Phút ON/OFF
{
  if (hang == 0){ //PHÚT ON
    pon --;
    if (pon < 0)
      pon = 59; } 
  else if (hang == 1){ //PHÚT OFF
    pof --;
    if (pof < 0)
      pof = 59; }
}

void setup() 
{
  Serial.begin(9600);
  rtc.begin();
  
  lcd.init();
  lcd.backlight();
  
  pinMode(len, INPUT_PULLUP);
  pinMode(xuong, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() 
{
  t = rtc.getTime();
  
  gtlen = digitalRead(len);  
  gtxuong = digitalRead(xuong);  
  gtmenu = digitalRead(menu);
  // Serial.print("LÊN: "); Serial.print(gtlen); Serial.print("    ");
  // Serial.print("XUỐNG: "); Serial.print(gtxuong); Serial.print("    ");
  // Serial.print("Menu: "); Serial.println(gtmenu);

if (gtlen != macdinh)  // NÚT LÊN
{
  if (gtlen == 0) // Khi nhấn nút lên
  {
    if (demtong == 1)   // LÊN Ở MENU TỔNG  
    {
      if (congtru_tong >= 3)
      { 
        congtru_tong = 0;  
      }
      else
      { 
        congtru_tong++;  
      }   
      menu_tong();
    }
    
    else if (demtong == 2)    //+ Con trỏ Set Date/Time và lên Menu Điều khiển
    {
      if(congtru_tong == 1 or congtru_tong == 2) // + CON TRỎ ở SET DATE và TIME
      {
        contro ++;
        if (contro > 15)
          contro = 0;
      }
      else if(congtru_tong == 3) //Lên ở MENU ĐIỀU KHIỂN
      {
        congtru_menudk ++;
        if (congtru_menudk > 5)
          congtru_menudk = 0;
        menu_dieukhien();
      }
    }

    else if (demtong == 3)   
    {
      if(congtru_tong == 1) // - ở NGÀY, THÁNG, NĂM
      {
        if ((contro == 0 or contro == 1)){ //NGÀY
          ngay --;
          if (ngay < 1)
            ngay = 31;}
        else if ((contro == 3 or contro == 4)){ //THÁNG
          thang --;
          if (thang < 1)
            thang = 12;}

          else if (contro == 6){ //NĂM NGHÌN
            namng --;
            if (namng < 0)
              namng = 9;}
          else if (contro == 7){ //NĂM TRĂM
            namtr --;
            if (namtr < 0)
              namtr = 9;}
          else if (contro == 8){ //NĂM CHỤC
            namch --;
            if (namch < 0)
              namch = 9;}
          else if (contro == 9){ //NĂM ĐƠN VỊ
            namdv --;
            if (namdv < 0)
              namdv = 9;}
      }

      else if(congtru_tong == 2) // - ở GIỜ : PHÚT : GIÂY
      {
        if ((contro == 0 or contro == 1)){ //GIỜ
          gio --;
          if (gio < 0)
            gio = 23;}
        else if ((contro == 3 or contro == 4)){ //PHÚT
          phut --;
          if (phut < 0)
            phut = 59;}
        else if ((contro == 6 or contro == 7)){ //GIÂY
          giay --;
          if (giay < 0)
            giay = 59;}
      }

      else if(congtru_tong == 3) // + CON TRỎ ở ĐIỀU KHIỂN
      {
        contro_dk ++;
        if (hang == 0){
          if (contro_dk > 15)
          { contro_dk = 5;
            hang = 1;}
        } else {
          if (contro_dk > 15)
          { contro_dk = 5;
            hang = 0;}       
        }
      }
    }
    
    else if (demtong == 4 && congtru_tong == 3) // - ĐIỀU KHIỂN | GIỜ ON - OFF, RELAY
    {
      if(contro_dk == 5 or contro_dk == 6) //- Giờ ON/OFF
      {
        if(congtru_menudk == 1) //Giờ 1
          TruGio(ton1, tof1);
        else if(congtru_menudk == 2) //Giờ 2
          TruGio(ton2, tof2);
        else if(congtru_menudk == 3) //Giờ 3
          TruGio(ton3, tof3);
        else if(congtru_menudk == 4) //Giờ 4
          TruGio(ton4, tof4);
        else if(congtru_menudk == 5) //Giờ 5
          TruGio(ton5, tof5);                              
      }
      else if(contro_dk == 8 or contro_dk == 9) //- Phút ON/OFF
      {
        if(congtru_menudk == 1) //Phút 1
          TruPhut(pon1, pof1);
        else if(congtru_menudk == 2) //Phút 2
          TruPhut(pon2, pof2);
        else if(congtru_menudk == 3) //Phút 3
          TruPhut(pon3, pof3);
        else if(congtru_menudk == 4) //Phút 4
          TruPhut(pon4, pof4);
        else if(congtru_menudk == 5) //Phút 5
          TruPhut(pon5, pof5);                              
      }                               

      else if(hang == 0 && contro_dk == 14) // - RELAY (chọn relay on/off)
      {
        if(congtru_menudk == 1) //Lệnh 1
          TruRelay(re1);
        else if (congtru_menudk == 2) //Lệnh 2
          TruRelay(re2);
        else if (congtru_menudk == 3) //Lệnh 3
          TruRelay(re3);
        else if (congtru_menudk == 4) //Lệnh 4
          TruRelay(re4);     
        else if (congtru_menudk == 5) //Lệnh 5
          TruRelay(re5);                       
      }                         
    }                                         

    delay(200);
  }
  macdinh = gtlen;
}

if (gtxuong != macdinh) // NÚT XUỐNG
{
  if (gtxuong == 0) //Khi nhấn nút xuống
  {
    if (demtong == 1)   // XUỐNG Ở MENU TỔNG
    {
      if (congtru_tong <= 0)
      { 
        congtru_tong = 3;  
      }
      else
      { 
        congtru_tong--;  
      }
      menu_tong();
    }
    
    else if (demtong == 2)   //- Con trỏ Set Date/Time và Xuống Menu Điều khiển
    {
      if(congtru_tong == 1 or congtru_tong == 2) // - CON TRỎ ở SET DATE và TIME
      {
        contro --;
        if (contro < 0)
          contro = 15;
      }
      else if(congtru_tong == 3)  //Xuống ở MENU ĐIỀU KHIỂN
      {
        congtru_menudk --;
        if (congtru_menudk < 0)
          congtru_menudk = 5;
        menu_dieukhien();
      }
    }

    else if (demtong == 3)
    {
      if(congtru_tong == 1)  // + ở NGÀY, THÁNG, NĂM
      {
        if (contro == 0 or contro == 1){ // + NGÀY ở DATE
          ngay ++;
          if (ngay > 31)
            ngay = 1;}
        else if (contro == 3 or contro == 4){ // + THÁNG ở DATE
          thang ++;
          if (thang > 12)
            thang = 1;}
        else if (contro == 6){ // + NĂM NGHÌN
          namng ++;
          if (namng > 9)
            namng = 0;}
        else if (contro == 7){// + NĂM TRĂM
          namtr ++;
          if (namtr > 9)
            namtr = 0;}
        else if (contro == 8){// + NĂM CHỤC
          namch ++;
          if (namch > 9)
            namch = 0;}
        else if (contro == 9){// + NĂM ĐƠN VỊ
          namdv ++;
          if (namdv > 9)
            namdv = 0;}
      }

      else if(congtru_tong == 2) //+ ở GIỜ : PHÚT :GIÂY
      {
        if (contro == 0 or contro == 1){ //GIỜ
          gio ++;
          if (gio > 23)
            gio = 0;}
        else if (contro == 3 or contro == 4){ //PHÚT
          phut ++;
          if (phut > 59)
            phut = 0;}
        else if (contro == 6 or contro == 7){ //GIÂY
          giay ++;
          if (giay > 59)
            giay = 0;}
      }

      else if(congtru_tong == 3) // - CON TRỎ ở ĐIỀU KHIỂN
      {
        contro_dk --;
        if (hang == 0){
          if (contro_dk < 5)
          { contro_dk = 15;
            hang = 1;}
        } else {
          if (contro_dk < 5)
          { contro_dk = 15;
            hang = 0;}        
        } 
      }
    } 

    else if (demtong == 4 && congtru_tong == 3) //+ ĐIỀU KHIỂN | GIỜ ON - OFF, RELAY
    {
      if(contro_dk == 5 or contro_dk == 6) //+ Giờ ON/OFF
      {
        if(congtru_menudk == 1) //Giờ 1
          CongGio(ton1, tof1);
        else if(congtru_menudk == 2) //Giờ 2
          CongGio(ton2, tof2);
        else if(congtru_menudk == 3) //Giờ 3
          CongGio(ton3, tof3);
        else if(congtru_menudk == 4) //Giờ 4
          CongGio(ton4, tof4);
        else if(congtru_menudk == 5) //Giờ 5
          CongGio(ton5, tof5);                              
      }
      else if(contro_dk == 8 or contro_dk == 9) //+ Phút ON/OFF
      {
        if(congtru_menudk == 1) //Phút 1
          CongPhut(pon1, pof1);
        else if(congtru_menudk == 2) //Phút 2
          CongPhut(pon2, pof2);
        else if(congtru_menudk == 3) //Phút 3
          CongPhut(pon3, pof3);
        else if(congtru_menudk == 4) //Phút 4
          CongPhut(pon4, pof4);
        else if(congtru_menudk == 5) //Phút 5
          CongPhut(pon5, pof5);                              
      }                        

      else if(hang == 0 && contro_dk == 14) // + RELAY (chọn relay on/off)
      {
        if(congtru_menudk == 1) //Lệnh 1
          CongRelay(re1);
        else if (congtru_menudk == 2) //Lệnh 2
          CongRelay(re2);
        else if (congtru_menudk == 3) //Lệnh 3
          CongRelay(re3);
        else if (congtru_menudk == 4) //Lệnh 4
          CongRelay(re4);      
        else if (congtru_menudk == 5) //Lệnh 5
          CongRelay(re5);                        
      }                    
    }                                                  

    delay(200);
  }
  macdinh = gtxuong;
}

if (gtmenu != macdinh)    // NÚT MENU
{  
  if (gtmenu == 0) //Khi nhấn nút
  {  
    demtong ++;

    if (demtong == 1) //Ở menu tổng
    { 
      menu_tong(); 
    }
    else if (demtong == 2) 
    {
      if(congtru_tong == 0) //Nhấn BACK từ Menu tổng về màn hình
      {
        demtong = 0;
        manhinh(); 
      }
      else if(congtru_tong == 1 or congtru_tong == 2) // chọn menu tổng DATE or TIME
      {
        chonmenu_tong();
      }
      else if(congtru_tong == 3) //Menu ĐIỀU KHIỂN
      {
        menu_dieukhien();
      }
    }                                           

    else if (demtong == 4) //Thoát CON TRỎ
    {
      if(congtru_tong == 1) //Thoát CON TRỎ từ SET DATE ra
      {
        demtong = 2;
        chonmenu_tong();
      }
      else if(congtru_tong == 2) //Thoát CON TRỎ từ SET TIME ra
      {
        demtong = 2;
        chonmenu_tong(); 
      }
      else if (congtru_tong == 3) //Thoát từ SET BT ra menu báo thức
      {
        if((contro_dk == 12 or contro_dk == 13 or contro_dk == 14 or contro_dk == 15) && hang == 1)
        {
          menu_dieukhien();
          demtong = 2;
          congtru_tong = 3;
          contro_dk = 5;
          hang = 0;
          lcd.noCursor();
        }
      }
    }       
    
    else if (demtong == 3) 
    {
      if((congtru_tong == 2 or congtru_tong == 1) && 
          (contro == 12 or contro == 13 or contro == 14 or contro == 15)) // Thoát từ SET DATE or TIME ra
      {
        demtong = 1;
        congtru_tong = 0;
        contro = 0;
        menu_tong();
        lcd.noCursor();
      }
      else if(congtru_tong == 3 && congtru_menudk == 0) //từ Menu ĐIỀU KHIỂN về Menu TỔNG
      {
        demtong = 1;
        congtru_menudk = 0;
        menu_tong();
      }
      else if(congtru_tong == 3 && (congtru_menudk == 1 or congtru_menudk == 2 
              or congtru_menudk == 3 or congtru_menudk == 4 or congtru_menudk == 5)) //chọn menu ĐK
      {
        chonmenu_dieukhien();
      }
    }      

    else if (demtong == 5 && congtru_tong == 3 && (congtru_menudk == 1 or congtru_menudk == 2
            or congtru_menudk == 3 or congtru_menudk == 4 or congtru_menudk == 5))  //Từ CON TRỎ ĐK chức năng SET ra
      {
        chonmenu_dieukhien();
        demtong = 3;
      }

    delay(100);
  }
  macdinh = gtmenu;
}

if (demtong == 0 && congtru_tong == 0) // MÀN HÌNH
{
  manhinh();
  lcd.noCursor();

// re1 = 1; re2 = 3; re3 = 2; re4 = 3; re5 = 1; //RELAY

// ton1 = 4; pon1 = 10; tof1 = 4; pof1 = 11; // 1 
// ton2 = 4; pon2 = 11; tof2 = 4; pof2 = 12; // 1, 2
// ton3 = 4; pon3 = 12; tof3 = 4; pof3 = 13; // 2
// ton4 = 4; pon4 = 13; tof4 = 4; pof4 = 14; // 1, 2
// ton5 = 4; pon5 = 14; tof5 = 4; pof5 = 15; // 1

  if(t.sec == 2) //ON
  {
    if(t.hour == ton1 && t.min == pon1) //LỆNH 1
      on(re1);
    else if(t.hour == ton2 && t.min == pon2) //LỆNH 2
      on(re2);
    else if(t.hour == ton3 && t.min == pon3) //LỆNH 3
      on(re3);
    else if(t.hour == ton4 && t.min == pon4) //LỆNH 4
      on(re4);
    else if(t.hour == ton5 && t.min == pon5) //LỆNH 5
      on(re5);                  
  }
  if(t.sec == 1) //OFF
  {
    if(t.hour == tof1 && t.min == pof1) //LỆNH 1
      off(re1);
    else if(t.hour == tof2 && t.min == pof2) //LỆNH 2
      off(re2);
    else if(t.hour == tof3 && t.min == pof3) //LỆNH 3
      off(re3);
    else if(t.hour == tof4 && t.min == pof4) //LỆNH 4
      off(re4);
    else if(t.hour == tof5 && t.min == pof5) //LỆNH 5
      off(re5);    
  }      
}

else if ((demtong == 2 or demtong == 3) && congtru_tong != 3) //SETUP DATE / TIME
{
  if(congtru_tong == 1) //DATE
  {
    if (ngay < 10){
      lcd.setCursor(0,1); lcd.print("0");
      lcd.setCursor(1,1); lcd.print(ngay);
    } else {
      lcd.setCursor(0,1); lcd.print(ngay);    
    }
    lcd.setCursor(2,1); lcd.print("/");
    if (thang < 10){
      lcd.setCursor(3,1); lcd.print("0"); 
      lcd.setCursor(4,1); lcd.print(thang);
    } else {
      lcd.setCursor(3,1); lcd.print(thang);    
    }
    lcd.setCursor(5,1); lcd.print("/"); 
    lcd.setCursor(6,1); lcd.print(namng); lcd.setCursor(7,1); lcd.print(namtr);
    lcd.setCursor(8,1); lcd.print(namch); lcd.setCursor(9,1); lcd.print(namdv);  
    namtong = (namng * 1000) + (namtr * 100) + (namch * 10) + namdv;

    lcd.setCursor(contro, 1); 
    lcd.cursor();
    delay(50);  

    rtc.setDate(ngay, thang, namtong);
  }
  else if (congtru_tong == 2) //TIME
  {
    if (gio < 10){
      lcd.setCursor(0,1); lcd.print("0");
      lcd.setCursor(1,1); lcd.print(gio);
    } else {
      lcd.setCursor(0,1); lcd.print(gio);
    }
    lcd.setCursor(2,1); lcd.print(":");
    if (phut < 10){
      lcd.setCursor(3,1); lcd.print("0"); 
      lcd.setCursor(4,1); lcd.print(phut);
    } else {
      lcd.setCursor(3,1); lcd.print(phut);    
    }  
    lcd.setCursor(5,1); lcd.print(":");
    if (giay < 10){
      lcd.setCursor(6,1); lcd.print("0"); 
      lcd.setCursor(7,1); lcd.print(giay);
    } else {
      lcd.setCursor(6,1); lcd.print(giay);    
    }

    lcd.setCursor(contro, 1); 
    lcd.cursor();
    delay(50);

    rtc.setTime(gio, phut, giay); 
  }
}

else if ((demtong == 3 or demtong == 4) && congtru_tong == 3) //Hiển thị SETUP ON/OFF
{ 
  if(congtru_menudk == 1) //Lệnh 1
    HTset(ton1, pon1, tof1, pof1, re1);     
  else if(congtru_menudk == 2) //Lệnh 2
    HTset(ton2, pon2, tof2, pof2, re2);  
  else if(congtru_menudk == 3) //Lệnh 3
    HTset(ton3, pon3, tof3, pof3, re3); 
  else if(congtru_menudk == 4) //Lệnh 4
    HTset(ton4, pon4, tof4, pof4, re4); 
  else if(congtru_menudk == 5) //Lệnh 5
    HTset(ton5, pon5, tof5, pof5, re5);              
}

  Serial.print("Đếm tổng: "); Serial.print(demtong); Serial.print("    ");
  Serial.print("+/- tổng: "); Serial.print(congtru_tong); Serial.print("    ");
  Serial.print("CT Điều khiển: "); Serial.print(contro_dk); Serial.print("    ");
  Serial.print("Hàng: "); Serial.print(hang); Serial.print("    ");   
  Serial.print("+/- menu báo thức: "); Serial.print(congtru_menudk); Serial.print("    ");
  Serial.print("Con trỏ: "); Serial.println(contro);

} //Kết loop
