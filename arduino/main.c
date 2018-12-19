volatile int count_h = 0;
volatile int count_m = 0;
int sw[4] = {3,4,5,6};
int start_sw = 0;
int stage = 0;


int value[4];
int d_value[4];

long start_time = 0;
long set_time = 0;
long long second(int ,int );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(2,func_a,FALLING);
  attachInterrupt(3,func_b,FALLING);
  attachInterrupt(4,func_c,FALLING);
  attachInterrupt(5,func_d,FALLING);
  attachInterrupt(0,func_e,FALLING);
  
}
void loop() {
    
    Serial.print(abs(count_h%25));
    Serial.print(":");
    Serial.println(count_m%60);
    second(abs(count_h%25),count_m%60);

    while(stage == 2)
    {
      start_time = millis()/1000;//stage2に入った時間を秒に直して入力する
      stage = 3; 
    }

    while(stage == 3){
      set_time = second(count_h%25,count_m%61);
      Serial.println(set_time - millis()/1000 - start_time); 
    }
    
    
  }


void func_a(){ count_h ++;}
void func_b(){ count_h --;}
void func_c(){ count_m ++;}
void func_d(){ count_m --;}
void func_e(){ stage = 2;}



//何時何分かを入力するとそれが何秒か表示
long long second(int hour,int minitue){
  return minitue*60+hour*3600;
}

//時間を秒単位で入力すると、h,m,sの部分だけを抽出する
long hour(long long second){
  return second/3600;
}

long mini(long long second){
  return (second-hour(second)*3600)/60;
}

long sec(long long second){
  return second-hour(second)*3600-mini(second)*60;
}


 
