#define black 0
#define white 1

#define FORWORD 1
#define BACK 2
#define LEFT 3
#define RIGHT 4


#define PIN_P0_IN1 46
#define PIN_P0_IN2 47
#define PIN_P0_IN3 48
#define PIN_P0_IN4 49
#define PIN_P0_ENA 3
#define PIN_P0_ENB 2

#define PIN_P1_IN1 37
#define PIN_P1_IN2 36
#define PIN_P1_IN3 35
#define PIN_P1_IN4 34
#define PIN_P1_ENA 4
#define PIN_P1_ENB 5

#define PIN_F_IN1 PIN_P0_IN1
#define PIN_F_IN2 PIN_P0_IN2
#define PIN_F_PWM PIN_P0_ENA
 
#define PIN_B_IN1 PIN_P1_IN1
#define PIN_B_IN2 PIN_P1_IN2
#define PIN_B_PWM PIN_P1_ENA

#define PIN_R_IN1 PIN_P1_IN3
#define PIN_R_IN2 PIN_P1_IN4
#define PIN_R_PWM PIN_P1_ENB

#define PIN_L_IN1 PIN_P0_IN3
#define PIN_L_IN2 PIN_P0_IN4
#define PIN_L_PWM PIN_P0_ENB

//left->right
#define PIN_SEN_F_1 17
#define PIN_SEN_F_2 16
#define PIN_SEN_F_3 15
#define PIN_SEN_F_4 14

//front->back
#define PIN_SEN_R_1 18
#define PIN_SEN_R_2 19
#define PIN_SEN_R_3 20
#define PIN_SEN_R_4 21

//front->back
#define PIN_SEN_L_1 25
#define PIN_SEN_L_2 24
#define PIN_SEN_L_3 23
#define PIN_SEN_L_4 22

class Car{
  int F1,F2,F3,F4,R1,R2,R3,R4,L1,L2,L3,L4;
  int Speed;
  int task;
  int count;
  int adjust_time;
  int adjust_speed;
public:
  Car(){
  Speed = 80;
  task = 1;
  count = 0;
  adjust_time = 2;
  adjust_speed = 80;
  }
  
  void car_setup()
  {
    pinMode(PIN_P0_IN1,OUTPUT);
    pinMode(PIN_P0_IN2,OUTPUT);
    pinMode(PIN_P0_IN3,OUTPUT);
    pinMode(PIN_P0_IN4,OUTPUT);
    pinMode(PIN_P0_ENA,OUTPUT);
    pinMode(PIN_P0_ENB,OUTPUT);

    pinMode(PIN_P1_IN1,OUTPUT);
    pinMode(PIN_P1_IN2,OUTPUT);
    pinMode(PIN_P1_IN3,OUTPUT);
    pinMode(PIN_P1_IN4,OUTPUT);
    pinMode(PIN_P1_ENA,OUTPUT);
    pinMode(PIN_P1_ENB,OUTPUT);

    pinMode(PIN_SEN_F_1,INPUT);
    pinMode(PIN_SEN_F_2,INPUT);
    pinMode(PIN_SEN_F_3,INPUT);
    pinMode(PIN_SEN_F_4,INPUT);
  
    pinMode(PIN_SEN_R_1,INPUT);
    pinMode(PIN_SEN_R_2,INPUT);
    pinMode(PIN_SEN_R_3,INPUT);
    pinMode(PIN_SEN_R_4,INPUT);

    pinMode(PIN_SEN_L_1,INPUT);
    pinMode(PIN_SEN_L_2,INPUT);
    pinMode(PIN_SEN_L_3,INPUT);
    pinMode(PIN_SEN_L_4,INPUT);
  }

  void brake(int t) {
    analogWrite(PIN_F_PWM,255);
    digitalWrite(PIN_F_IN1,HIGH);
    digitalWrite(PIN_F_IN2,HIGH);
    analogWrite(PIN_B_PWM,255);
    digitalWrite(PIN_B_IN1,HIGH);
    digitalWrite(PIN_B_IN2,HIGH);
    analogWrite(PIN_L_PWM,255);
    digitalWrite(PIN_L_IN1,HIGH);
    digitalWrite(PIN_L_IN2,HIGH);
    analogWrite(PIN_R_PWM,255);
    digitalWrite(PIN_R_IN1,HIGH);
    digitalWrite(PIN_R_IN2,HIGH);
    delay(t);
  }

   void move_forword()
  {
 //   delay(100);
    analogWrite(PIN_F_PWM,0);
    digitalWrite(PIN_F_IN1,LOW);
    digitalWrite(PIN_F_IN2,LOW);
    analogWrite(PIN_B_PWM,0);
    digitalWrite(PIN_B_IN1,LOW);
    digitalWrite(PIN_B_IN2,LOW);
  
    analogWrite(PIN_L_PWM,Speed);
    digitalWrite(PIN_L_IN1,LOW);
    digitalWrite(PIN_L_IN2,HIGH);
    analogWrite(PIN_R_PWM,Speed);
    digitalWrite(PIN_R_IN1,HIGH);
    digitalWrite(PIN_R_IN2,LOW);  

    if(F4 == black || (F1 == white && F2 == white))//向右调整
    {
      analogWrite(PIN_F_PWM,adjust_speed);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,HIGH);

      analogWrite(PIN_B_PWM,adjust_speed);
      digitalWrite(PIN_B_IN1,HIGH);
      digitalWrite(PIN_B_IN2,LOW);
      delay(adjust_time);
      
      analogWrite(PIN_F_PWM,0);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,LOW);
      analogWrite(PIN_B_PWM,0);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,LOW);
    }
  
    if(F1 == black || (F3 == white && F4 == white))//向左调整
    {
      analogWrite(PIN_F_PWM,adjust_speed);
      digitalWrite(PIN_F_IN1,HIGH);
      digitalWrite(PIN_F_IN2,LOW);

      analogWrite(PIN_B_PWM,adjust_speed);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,HIGH);
      delay(adjust_time);
      
      analogWrite(PIN_F_PWM,0);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,LOW);
      analogWrite(PIN_B_PWM,0);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,LOW);
    } 
  }

  void move_left()
  {
    analogWrite(PIN_L_PWM,0);
    digitalWrite(PIN_L_IN1,LOW);
    digitalWrite(PIN_L_IN2,LOW);
    analogWrite(PIN_R_PWM,0);
    digitalWrite(PIN_R_IN1,LOW);
    digitalWrite(PIN_R_IN2,LOW);
    
    analogWrite(PIN_F_PWM,Speed);
    digitalWrite(PIN_F_IN1,HIGH);
    digitalWrite(PIN_F_IN2,LOW);

    analogWrite(PIN_B_PWM,Speed);
    digitalWrite(PIN_B_IN1,LOW);
    digitalWrite(PIN_B_IN2,HIGH);

     if((L1 == black && R4 == black) || 
        (L1 == black && R2 == white))
    {
      analogWrite(PIN_B_PWM,Speed+30);
      analogWrite(PIN_F_PWM,Speed-30);
      delay(adjust_time); 
    }
    if((L4 == black && R1 == black) ||
       (L4 == black && R3 == white))//向下调整
    {
      analogWrite(PIN_B_PWM,Speed-30);
      analogWrite(PIN_F_PWM,Speed+30);
      delay(adjust_time);
    }
    analogWrite(PIN_F_PWM,Speed);
    analogWrite(PIN_B_PWM,Speed);
  }

  void move_back()
  {
 //   delay(100);
    analogWrite(PIN_F_PWM,0);
    digitalWrite(PIN_F_IN1,LOW);
    digitalWrite(PIN_F_IN2,LOW);
    analogWrite(PIN_B_PWM,0);
    digitalWrite(PIN_B_IN1,LOW);
    digitalWrite(PIN_B_IN2,LOW);
    
    analogWrite(PIN_L_PWM,Speed);
    digitalWrite(PIN_L_IN1,HIGH);
    digitalWrite(PIN_L_IN2,LOW);
    analogWrite(PIN_R_PWM,Speed);
    digitalWrite(PIN_R_IN1,LOW);
    digitalWrite(PIN_R_IN2,HIGH);

    if(F4 == black || (F1 == white && F2 == white))//向右调整
    {
      analogWrite(PIN_F_PWM,adjust_speed);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,HIGH);

      analogWrite(PIN_B_PWM,adjust_speed);
      digitalWrite(PIN_B_IN1,HIGH);
      digitalWrite(PIN_B_IN2,LOW);
      delay(adjust_time);
      
      analogWrite(PIN_F_PWM,0);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,LOW);
      analogWrite(PIN_B_PWM,0);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,LOW);
    }
  
    if(F1 == black || (F3 == white && F4 == white))//向左调整
    {
      analogWrite(PIN_F_PWM,adjust_speed);
      digitalWrite(PIN_F_IN1,HIGH);
      digitalWrite(PIN_F_IN2,LOW);

      analogWrite(PIN_B_PWM,adjust_speed);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,HIGH);
      delay(adjust_time);
      
      analogWrite(PIN_F_PWM,0);
      digitalWrite(PIN_F_IN1,LOW);
      digitalWrite(PIN_F_IN2,LOW);
      analogWrite(PIN_B_PWM,0);
      digitalWrite(PIN_B_IN1,LOW);
      digitalWrite(PIN_B_IN2,LOW);
    } 
  }

  void move_right()
  {
 //   delay(100);
    analogWrite(PIN_L_PWM,0);
    digitalWrite(PIN_L_IN1,LOW);
    digitalWrite(PIN_L_IN2,LOW);
    analogWrite(PIN_R_PWM,0);
    digitalWrite(PIN_R_IN1,LOW);
    digitalWrite(PIN_R_IN2,LOW);
  
    analogWrite(PIN_F_PWM,Speed);
    digitalWrite(PIN_F_IN1,LOW);
    digitalWrite(PIN_F_IN2,HIGH);

    analogWrite(PIN_B_PWM,Speed);
    digitalWrite(PIN_B_IN1,HIGH);
    digitalWrite(PIN_B_IN2,LOW);

     if((L1 == black && R4 == black) || 
        (L1 == black && R2 == white))
    {
      analogWrite(PIN_B_PWM,Speed-30);
      analogWrite(PIN_F_PWM,Speed+30);
      delay(adjust_time); 
    }
    if((L4 == black && R1 == black) ||
       (L4 == black && R3 == white))
    {
      analogWrite(PIN_B_PWM,Speed+30);
      analogWrite(PIN_F_PWM,Speed-30);
      delay(adjust_time);
    }
    analogWrite(PIN_F_PWM,Speed);
    analogWrite(PIN_B_PWM,Speed);
  }
  
  void updata()
  {
    F1 = digitalRead(PIN_SEN_F_1);
    F2 = digitalRead(PIN_SEN_F_2);
    F3 = digitalRead(PIN_SEN_F_3);
    F4 = digitalRead(PIN_SEN_F_4);
    
    R1 = digitalRead(PIN_SEN_R_1);
    R2 = digitalRead(PIN_SEN_R_2);
    R3 = digitalRead(PIN_SEN_R_3);
    R4 = digitalRead(PIN_SEN_R_4);

    L1 = digitalRead(PIN_SEN_L_1);
    L2 = digitalRead(PIN_SEN_L_2);
    L3 = digitalRead(PIN_SEN_L_3);
    L4 = digitalRead(PIN_SEN_L_4);  
  }
  
  void speed_contorl(int a)
  {
    Speed = a;
  }

  void move_contorl(int a)
  {
    switch(a)
    {
    case FORWORD: move_forword();break;
    case BACK:  move_back();break;
    case RIGHT: move_right();break;
    case LEFT:  move_left();break;
    }
  }
//function
  void grabCircle(){};
  void grabSquare(){};
  void grabHex(){};
  void pushCircle(){};
  void pushSquare(){};
  void pushHex(){};
  
  void Run(int& a)
  {
      switch(a)
      {
        case 1:
            //到出生地
            move_forword();  
/*            Serial.print(L1);
            Serial.print(L2);
            Serial.print(L3);
            Serial.print(L4);
            Serial.print("\n");
*/
            if((L1 == black || L2  == black || L3 == black || L4 == black))//已到达目的地
            {
              brake(500);
              a = 2;
            }
            break;
        case 2:
          //抓物体并放到容器里
          //抓物体
          switch(task)
          {
            case 1: grabCircle(); break;
            case 2: grabSquare(); break;
            case 3: grabHex(); break;
          }
          //到容器处
          //先到左方分叉口
          move_left();
          if(F1 == black || F2 == black || F3 == black || F4 == black)
          {
            brake(500);
            if(task == 1) a = 21;
            if(task == 2) a = 22;
            if(task == 3) a = 23; 
          }
          break;
        case 21:
          //完成第一个物块的放置
          //先到达第一个物块对应位置
          move_forword();
          delay(50);  
          if(F1 == white && F2  == white && F3 == white && F4 == white)//已到达目的地
          {
            brake(500);
            Speed = 100;
            a = 212;
            //放置第一个物块
            pushCircle();
          }
          break;                
        case 212:
          move_back();
          if( R4 == black || R3 == black || R2 == black || R1 == black )
          {
            brake(500);
            task = 2;
            a = 3;
          }
          break;
        case 22:
          pushSquare();
          a = 3;
          task = 3;
          break;
        case 23:
           //第三个
           //先到达第三个物块对应位置  
           move_back();
           delay(50);
           if(L4 == black || L3 == black)//已到达目的地
           {
              brake(500);
              a = 232;
           }
           //放置第一个物块
           pushCircle();
           break;
        case 232:      
            //返回三岔口
            move_forword();  
            delay(50);
            if(R1 == black || R2 == black)
            {
              brake(500);
              task = 4;
              a = 3; 
            }
            break;
        case 3:
          //返回出生地
          move_right();
          if(R1 == white && R2 == white && R3 == white && R4 == white)
          {
            count++;
          }
          if(count == 3)
          {
            brake(500);
            if(task != 4)
            {
              a = 2;
            }
            else 
            {
              a = 4;
            }
          }
          break;
        case 4:
          //返回出发点
          move_back();  
          if(F1 == white && F2 == white && F3 == white && F4 == white)//减速停止
          {
            delay(1000);
            brake(500);
          }
          break;
      }             
  }

  void test()
  {
   Serial.print(F1);
   Serial.print(F2);
   Serial.print(F3);
   Serial.print(F4);
   Serial.print(' ');
   Serial.print(R1);
   Serial.print(R2);
   Serial.print(R3);
   Serial.print(R4);
   Serial.print(' ');
   Serial.print(L1);
   Serial.print(L2);
   Serial.print(L3);
   Serial.print(L4);
   Serial.println();
   delay(1000);
  }  
};

Car my_Car; 
int mode = 1;

void setup() { 
  my_Car.car_setup();
 // my_Car.move_forword();
 // delay(500);
  Serial.begin(9600);
/*  analogWrite(PIN_L_PWM,0);
  digitalWrite(PIN_L_IN1,LOW);
  digitalWrite(PIN_L_IN2,LOW);
  analogWrite(PIN_R_PWM,0);
  digitalWrite(PIN_R_IN1,LOW);
  digitalWrite(PIN_R_IN2,LOW);
*/
}

void loop() {
  // put your main code here, to run repeatedly:
  my_Car.updata();
  my_Car.Run(mode);
//  my_Car.test();
}
