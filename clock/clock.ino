#include "Wire.h"

#define DS3231_I2C_ADDRESS 0x68

#define MINUTES 51
#define HOURS 20

#define A 11
#define B 12
#define C 5
#define D 3
#define E 2
#define EF 10
#define G 4

#define N1 6
#define N2 7
#define N3 8
#define N4 9

int flag = 0;

//*********************************DISPLAY**********************************************
void setup_display()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(EF, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
}

void display_none()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(EF, HIGH);
  digitalWrite(G, HIGH);
}

void display_zero()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(EF, LOW);
  digitalWrite(G, HIGH);
}

void display_one()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(EF, HIGH);
  digitalWrite(G, HIGH);
}

void display_two()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(EF, HIGH);
  digitalWrite(G, LOW);
}

void display_three()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(EF, HIGH);
  digitalWrite(G, LOW);
}

void display_four()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(EF, LOW);
  digitalWrite(G, LOW);
}

void display_five()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(EF, LOW);
  digitalWrite(G, LOW);
}

void display_six()
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(EF, LOW);
  digitalWrite(G, LOW);
}

void display_seven()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(EF, HIGH);
  digitalWrite(G, HIGH);
}

void display_eight()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(EF, LOW);
  digitalWrite(G, LOW);
}

void display_nine()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(EF, LOW);
  digitalWrite(G, LOW);
}

void display_digit(int digit)
{
  switch(digit)
  {
    case 0:
    {
      display_zero();
      break;
    }
    case 1:
    {
      display_one();
      break;
    }
    case 2:
    {
      display_two();
      break;
    }
    case 3:
    {
      display_three();
      break;
    }
    case 4:
    {
      display_four();
      break;
    }
    case 5:
    {
      display_five();
      break;
    }
    case 6:
    {
      display_six();
      break;
    }
    case 7:
    {
      display_seven();
      break;
    }
    case 8:
    {
      display_eight();
      break;
    }
    case 9:
    {
      display_nine();
      break;
    }
    default:
    {
      display_none();
      break;
    }
  }
}

void set_disp_off()
{
  digitalWrite(N1, HIGH);
  digitalWrite(N2, HIGH);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, HIGH);
}

void set_n1()
{
  digitalWrite(N1, LOW);
  digitalWrite(N2, HIGH);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, HIGH);
}

void set_n2()
{
  digitalWrite(N1, HIGH);
  digitalWrite(N2, LOW);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, HIGH);
}

void set_n3()
{
  digitalWrite(N1, HIGH);
  digitalWrite(N2, HIGH);
  digitalWrite(N3, LOW);
  digitalWrite(N4, HIGH);
}

void set_n4()
{
  digitalWrite(N1, HIGH);
  digitalWrite(N2, HIGH);
  digitalWrite(N3, HIGH);
  digitalWrite(N4, LOW);
}

int display_time(int h, int m)
{
  if(flag < 1)
    set_disp_off();
  else if(flag < 5)
  {
    display_digit((h-h%10)/10);
    set_n1();
  }
  else if(flag < 6)
    set_disp_off();
  else if(flag < 10)
  {
    display_digit(h%10);
    set_n2();
  }
  else if(flag < 11)
    set_disp_off();
  else if(flag < 15)
  {
    display_digit((m-m%10)/10);
    set_n3();
  }
  else if(flag < 16)
    set_disp_off();
  else if(flag < 20)
  {
    display_digit(m%10);
    set_n4();
  }
  else if(flag == 21)
    flag=0;
  else
    set_disp_off();
  
  flag++;
}


//*****************************COMMUNICATION I2C*****************************************
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  setup_display();
  
  // DS3231 seconds, minutes, hours, day, date, month, year
  setDS3231time(0,MINUTES,HOURS,7,25,10,15);
}

void loop()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  
  display_time(hour, minute);
  //displayTime(); // display the real-time clock data on the Serial Monitor,
  //delay(1000); // every second
}

