// 最後編輯 2021-9-18 by ShinWei Chiou
// 初版

// 最後編輯 2021-10-05 by ShinWei Chiou
// 增加 P0 按鍵測試
// 增加 LED 亮度控制(調暗)

// 最後編輯 2021-11-29 by ShinWei Chiou
// 修正 P4 亮度不足
// 修正 P1,P3 誤動作

/*
  ESP32-CAM Motor Shield V3.0
  L9110_A_1 = 15;
  L9110_A_2 = 14;
  L9110_B_1 = 13;
  L9110_B_2 = 12;
  BUZZER = 2;
  LED = 4;

  Board: ESP32 Wrover Module
  Upload Speed: 115200
  Flash Frequency: 80MHz
  Flash Mode: QIO
  Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)
  Core Debug Level: None
*/

int Counter = 0;

// variable for reading the pushbutton status
int buttonState = 0;

// setting PWM properties
const int freq = 3000;
const int resolution = 8;
const int ledChannel = 0;
const int BuzzerChannel = 1;


void setup()
{
  pinMode(0, INPUT); // Button

  pinMode(1, OUTPUT);  //I2C,GPIO
  pinMode(2, OUTPUT);  //BUZZER,GPIO
  pinMode(3, OUTPUT);  //I2C,GPIO
  pinMode(12, OUTPUT); //MotorB,Servo
  pinMode(13, OUTPUT); //MotorB,Servo
  pinMode(14, OUTPUT); //MotorA,Servo
  pinMode(15, OUTPUT); //MotorA,Servo

  //宣告Channel特性
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(BuzzerChannel, freq, resolution);

  //將上述Channel附加到Pin腳位上
  ledcAttachPin(4, ledChannel);
  ledcAttachPin(2, BuzzerChannel);
}


void loop()
{
  // Push Button
  buttonState = digitalRead(0);
  if (buttonState == LOW)
  {
    // turn LED on:
    ledcWrite(ledChannel, 64);
    ledcWrite(BuzzerChannel, 0);

    // GPIO
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
  }
  else
  {
    // GPIO
    digitalWrite(1, LOW);
    digitalWrite(3, LOW);

    // turn LED off:
    ledcWrite(ledChannel, 0);
    ledcWrite(BuzzerChannel, 128);
  }

  // Motor
  if (Counter == 0 && buttonState == HIGH)
  {
    Counter++;
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(15, LOW);
  }
  else if (Counter == 30 && buttonState == HIGH)
  {
    Counter++;
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);
  }
  else if (Counter >= 60)
  {
    Counter = 0;
  }
  else
  {
    Counter++;
  }

  delay(50);
}
