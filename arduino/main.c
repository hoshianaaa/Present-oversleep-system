  #include <Servo.h>

#include <I2CLiquidCrystal.h>
#include <Wire.h>
I2CLiquidCrystal lcd(20, (bool)true); 

Servo servo;

int sw[6] = {2,3,4,5};//sw[0]:60分 sw[1]:-60分 sw[2]:1分 sw[3]:-1分
int stop_sw = 7;
int start_sw = 6;
static int stage=1;
static int flag[4],count;
long set_h,set_m,all_m,all_s;
int val[4];
static int a;
static int start_time;
static int i;


int hour(long);
int mini(long);
int sec(long);



void setup() {

  servo.attach(9);
  // put your setup code here, to run once:
  for(int i=0;i<4;i++)pinMode(sw[i],INPUT_PULLUP);
  pinMode(stop_sw,INPUT_PULLUP);
  pinMode(start_sw,INPUT_PULLUP);
  
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //初期コードを入力,
   while(stage == 1){
    count = 0;a = 0;
    i = 0;
    servo.write(0);
    stage = 2;   
   }

   //タイマーのセット(何時間何分か)
  while(stage == 2){
   /* Serial.print("count:");
    Serial.print(count);
    Serial.print("  all_m:");
    Serial.print(all_m);
    Serial.print("  set_h:");
    Serial.print(set_h);
    Serial.print("  set_m:");
    Serial.println(set_m);
    lcd.setCursor(0,0);*/
    lcd.print("TIMER SETTING");
   // Serial.println(digitalRead(stop_sw));
    //delay(1000);
    
    val[0] = digitalRead(sw[0]);
    if(val[0] == LOW && flag[0] == 0){flag[0] = 1;count += 60;}
    if(flag[0] == 1 && val[0] == HIGH){flag[0] = 0;}
   

    val[1] = digitalRead(sw[1]);
    if(val[1] == LOW && flag[1] == 0){flag[1] = 1;count -= 60;}
    if(flag[1] == 1 && val[1] == HIGH){flag[1] = 0;}

    val[2] = digitalRead(sw[2]);
    if(val[2] == LOW && flag[2] == 0){flag[2] = 1;count += 1;}
    if(flag[2] == 1 && val[2] == HIGH){flag[2] = 0;}
    
    val[3] = digitalRead(sw[3]);
    if(val[3] == LOW && flag[3] == 0){flag[3] = 1;count -= 1;}
    if(flag[3] == 1 && val[3] == HIGH){flag[3] = 0;}
    

    

    //0:0 - 23:59 mの桁0-59　60通り、hの桁 0-23 の 24通り 60*24 = 1200+240=1440　
    //1440個パターンがある
    //0-1339をこれに対応させる
    //-1になったら766にもどるようにする
    //767になったら0に戻るようにする
    // %演算子を使うことになるのかな？

    if(count >= 0)all_m = count % 1440;else {all_m = 1440 + (count % 1440);/*Serial.print(count%1440);*/}
    set_h = all_m / 60;
    set_m = all_m % 60;
    
    lcd.setCursor(0, 1);
    lcd.print(set_h);
    lcd.print(":");
    lcd.print(set_m);
    delay(10);
    lcd.clear();
    delay(1);


    val[4] = digitalRead(start_sw);
   // Serial.print(stop_sw);
   // Serial.print(digitalRead(4));
    if(val[4] == LOW && all_m != 0){stage = 3;}

    
    

   /* lcd.setCursor(0, 0);
    for(int i=0;i<6;i++){
      lcd.print(count[i]);
      lcd.print(" ");
    }*/
  }

//カウントダウン
  while(stage == 3){
     Serial.print("stage:");
     Serial.print(stage);
    
    
    if(a == 0){
     // lcd.print("stage 3");
     // delay(10);
     // lcd.clear();
      start_time = millis()/1000;
      all_s = set_h * 3600 + set_m * 60;
      //Serial.println(all_s);
      a = 1;
    }

    if(a == 1){
      lcd.setCursor(0, 0);
      //lcd.print(start_time);
      lcd.print("COUNT DOWN");
     // delay(10);
      //lcd.print(all_s - start_time);
      lcd.setCursor(0, 1);
      lcd.print(hour(all_s + start_time - millis()/1000) );
      
      lcd.print(":");
      lcd.print(mini(all_s + start_time - millis()/1000) );
      lcd.print(":");
      lcd.print(sec(all_s + start_time - millis()/1000));
     // Serial.println((all_s-millis()/1000+start_time)/60);
      delay(10);
      lcd.clear();
     
    }
    /*
    Serial.print("  hour:");
    Serial.print((all_s + start_time - millis()/1000)/60);
    Serial.print("  mini:");
    Serial.print(mini(all_s + start_time - millis()/1000));
    Serial.print("  sec");
    Serial.print(sec(all_s + start_time - millis()/1000));
    Serial.print("  0に近づくやつ:");
    Serial.println(all_s + start_time - millis()/1000);*/
    if(all_s + start_time - millis()/1000 <= 60)stage = 4;
    if(digitalRead(stop_sw) == LOW){lcd.print("TIMER STOP");delay(1000);count = 0;a = 0;stage = 1;}
    }
  
//タイマーが60秒以下になった時の動作
  while(stage == 4){
    if(all_s + start_time - millis()/1000 <= 60)stage = 5;
    if(digitalRead(stop_sw) == LOW){lcd.print("TIMER STOP");delay(1000);count = 0;a = 0;stage = 1;}
    tone(13,262,100);
     
     
  }
//タイマーが0になったときの行動を記入する
  while(stage == 5){
    
    lcd.println("WARNNIG");
    servo.write(i++);
    delay(30);
    if(i >= 150)stage = 1;
    
    
  }






  
}
