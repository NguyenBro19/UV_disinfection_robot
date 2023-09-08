#define BRAKE  40
#define CW     41
#define CCW    42
#define LEFT   43
#define RIGHT  44


//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6


#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

#define CBTrai  A2 //cam bien trai
#define CBGiua  A3 //cam bien giua
#define CBPhai  A4 //cam bien phai

#define encoder 2

int a = 0, b= 0;
int dem = 0;
float tocdo = 0;

int timecho = 1000;
unsigned long thoigian;
unsigned long hientai;

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;
 
void setup()                         
{
  Serial.begin(9600);
//Motor
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);
 
  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

//Cảm biến
  pinMode(CBTrai, INPUT);
  pinMode(CBGiua, INPUT);
  pinMode(CBPhai, INPUT);

//Đèn UV
  pinMode(51, OUTPUT); 
  digitalWrite(51, LOW);
  pinMode(52, OUTPUT); 
  digitalWrite(52, LOW);
  pinMode(53, OUTPUT); 
  digitalWrite(53, LOW);
           
  pinMode(encoder, INPUT);
  attachInterrupt(0, dem_xung, RISING); //Ngắt ngoài
}

void loop() 
{
  thoigian = millis();
  if (Serial.available())
  {
  char data_rcvd = Serial.read();
    if(data_rcvd == '1')
    {
     Auto();
    }
    if(data_rcvd == '2')
    {
      TurnON();
    }   
    if(data_rcvd == '3')
    {
      TurnOFF();
    }
    if(data_rcvd == '4')
    {
      Forward();
    }
    if(data_rcvd == '5')
    {
      Stop();
    }
    if(data_rcvd == '6')
    {
      Reverse();
    } 
    if(data_rcvd == '7')
    {
      Turnleft();
    } 
    if(data_rcvd == '8')
    {    
       Turnright();
    }   
    if(data_rcvd == '+')
    {
      IncreaseSpeed();
    } 
    if(data_rcvd == '-')
    {
      DecreaseSpeed();
    }     
    Serial.println(data_rcvd);//Kiểm tra dữ liệu đã nhận từ ESP32
  }
 dotocdo();
}

void dotocdo()
{
 if (thoigian - hientai >= timecho)
  {
    hientai = thoigian;
    tocdo = float(dem/20)*float(0.025*3.14); // m/s
//     * dem/20 là số vòng/s
//     * 0.025 là đường kính vòng tròn (đơn vị: m)
//     * 3.14 là số pi
    dem = 0;
    Serial.print("   "); Serial.print("M/s: "); 
    Serial.println(tocdo); //kiểm tra tốc độ qua monitor
  }
}
void dem_xung()
{
  dem++; //đếm xung
}

void Stop()
{
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
  Serial.println("XE DUNG");
}

void Forward()
{
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  Serial.println("XE DI TOI");
}

void Reverse()
{
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  Serial.println("XE DI LUI");
}

void Turnleft()
{
  usMotor_Status = LEFT;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  Serial.println("XE QUEO TRAI");
}
void Turnright()
{
  usMotor_Status = RIGHT;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  Serial.println("XE  QUEO PHAI");
}

void TurnON()  //Bật đèn UV
{
  digitalWrite(51, HIGH); 
  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH); 
}
void TurnOFF() //Tắt đèn UV
{
  digitalWrite(51, LOW);
  digitalWrite(52, LOW);
  digitalWrite(53, LOW);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
       Serial.println("BANH 1 DI TOI");
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);
      Serial.println("BANH 1 DI LUI");      
    }
     else if(direct == LEFT)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW); 
    }
    else if(direct == RIGHT)
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);    
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    } 
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
      Serial.println("BANH 2 DI TOI");
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);  
          Serial.println("BANH 2 DI LUI");
    }
    else if(direct == LEFT)
    {
       digitalWrite(MOTOR_A2_PIN, LOW);
       digitalWrite(MOTOR_B2_PIN, LOW);     
    }
    else if(direct == RIGHT)
    {   
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);   
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    analogWrite(PWM_MOTOR_1, pwm);
    analogWrite(PWM_MOTOR_2, pwm);
  }
}
void Auto()
{
  if (digitalRead(CBGiua) == LOW) 
  {
    Forward();
  }
  else 
  {
    Stop();
    a = 1;
  }
  if (a == 1 && digitalRead(CBTrai) == HIGH && digitalRead(CBPhai) == LOW )
  {
    Turnright();
    delay(3000);
    Stop();
    delay(500);
    Forward();
    a=0; 
  }
  else if (a == 1 && digitalRead(CBTrai) == LOW && digitalRead(CBPhai) == HIGH )
  {
    Turnleft();
    delay(3000);
    Stop();
    delay(500);
    Forward();
    a=0; 
  }
 if( tocdo < 0.1)
 {
  Reverse();
  delay(2000);
  Turnleft();
  delay(2000);
  Auto();
 } 
}
