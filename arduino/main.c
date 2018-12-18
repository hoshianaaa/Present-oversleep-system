void setup() {
  // put your setup code here, to run once:
  attachiInterrupt(1,timerstop(),FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (stage == 0) { servo_up();stage = 1;}
  while (stage == 1) { Serial.println("00:00");stage = 2; }
  while (stage == 2) { 
    if(sw_start == LOW || set_time != 0)stage = 3;
    set_h = set_count(sw1,sw2);
    set_m = set_count(sw3,sw4);
    Serial.print(set_h);
    Serial.print(":");
    Serial.print(set_m);
  }
  while (stage == 3){
    if((set_h - now_h) == 0)stage = 4;
    Serial.print(set_h - nowh);
    Serial.print(":");
    Serial.print(set_m - now_m);
    Serial.print(":");
    Serial.println(set_s - now_s);
  }
  while (stage == 4){
    if((set_m - now_m) == 0)stage = 5;
    Serial.print("00:");
    Serial.print(set_m - now_m);
    Serial.print(":");
    Serial.println(set_s - now_s);
  }
  while (stage == 5){
    if((set_s < now_s)servo_down();stage = 0;
      Serial.print("00:00:");
      Serial.println(set_s - now_s);
  }
  
  
}
