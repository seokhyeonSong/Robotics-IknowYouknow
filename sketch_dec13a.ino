#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int frequency = 0;
int r_led[12]={1,2,4,8,16,32,64,1,2,4,8,16};
int g_led[12]={1,2,4,8,16,32,64,1,2,4,8,16};
int b_led[12]={1,2,4,8,16,32,64,1,2,4,8,16};
const int latch1 = 40;//빨간색 1~64
const int clock1 = 39;
const int data1 = 41;
const int latch2 = 43;//빨간색 1~16
const int clock2 = 42;
const int data2 = 44;
const int latch3 =46; //파란색 1~64
const int clock3 = 45;
const int data3 = 47; 
const int latch4 = 31; //파란색 1~16
const int clock4 = 30;
const int data4 = 32;
const int latch5 = 34; //초록색 1~64
const int clock5 = 33;
const int data5 = 35;
const int latch6 =37; //초록색 1~16
const int clock6 = 36;
const int data6 = 38;
int color=0;

int r=0;
int g=0;
int b=0;
int r_pre = 0;
int g_pre = 0;
int b_pre = 0;
int motor=20;
int i=0;
int r_island=0;
int g_island=0;
int b_island=0;

char *board[12];

int start_button = 2;
int go_button = 3;
int TX =4;
int RX =5;
SoftwareSerial mySerial(TX, RX);
int S0 = 7, S1 = 8, S2 = 9, S3 = 10;
int out = 11;
int flag =0;
int start_count=0;
int bluetooth=0;

int RS = 14;//lcd
int EN = 15;
int D4 = 16;
int D5 = 17;
int D6 = 18;
int D7 = 19;//lcd

int r_num=0;
int g_num=0;
int b_num=0;

int ran=0;


LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

char *random_key[6]; //랜덤열쇠 
char *user[5]; //블루투스로 받는 array

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(latch1, OUTPUT);
  pinMode(clock1, OUTPUT);
  pinMode(data1, OUTPUT);
  pinMode(latch2, OUTPUT);
  pinMode(clock2, OUTPUT);
  pinMode(data2, OUTPUT);
  pinMode(latch3, OUTPUT);
  pinMode(clock3, OUTPUT);
  pinMode(data3, OUTPUT);
  pinMode(latch4, OUTPUT);
  pinMode(clock4, OUTPUT);
  pinMode(data4, OUTPUT);
  pinMode(latch5, OUTPUT);
  pinMode(clock5, OUTPUT);
  pinMode(data5, OUTPUT);
  pinMode(latch6, OUTPUT);
  pinMode(clock6, OUTPUT);
  pinMode(data6, OUTPUT);

  Serial.begin(9600);
 
  lcd.begin(16, 2);

random_key[0]="go to island";
random_key[1]="go to start";
random_key[2]="go two forward";
random_key[3]="go one forward";
random_key[4]="go two backward";
random_key[5]="go one backward";
board[0]="start!";
board[6]="island...";
Serial.printf("type what you want to do : ");
while(1){
if(user[i]=Serial.read())
  {
    i++;
    if(i==5)
      break;
    Serial.printf("type what you want to do : ");
    
  }
}
i=0;
while(1)
 {
  Serial.print(start_count);
   delay(300);

  if (digitalRead(start_button) == HIGH)
  {
   if (start_count <3&&flag==0) {
      start_count++;
   } // close if
  
   if (flag == 1)
   {
      start_count--;
      
   } //close if
  }
   if (start_count == 3)
      flag = 1;
   if (start_count == 0)
         flag == 0;
    if(start_count==1)
    {
     //첫번째 red on
      digitalWrite(latch1, LOW);
      digitalWrite(latch2, LOW);
      digitalWrite(latch3, LOW);

      shiftOut(data1, clock1, MSBFIRST, 1);
      shiftOut(data2, clock2, MSBFIRST, 0);
      shiftOut(data3, clock3, MSBFIRST, 0); 

      digitalWrite(latch1, HIGH);
      digitalWrite(latch2, HIGH);
      digitalWrite(latch3, HIGH);
       lcd.clear();
       lcd.print("1P");  
      } //close if
    else if(start_count==2)
    {
      //첫번째 red, 첫번째 green on
      digitalWrite(latch1, LOW);
      digitalWrite(latch2, LOW);
      digitalWrite(latch3, LOW);

      shiftOut(data1, clock1, MSBFIRST, 1);
      shiftOut(data2, clock2, MSBFIRST, 1);
      shiftOut(data3, clock3, MSBFIRST, 0); 

      digitalWrite(latch1, HIGH);
      digitalWrite(latch2, HIGH);
      digitalWrite(latch3, HIGH);
       lcd.clear();
       lcd.print("2P");
      } //close else if
    else if(start_count==3)
    {
      //첫번째 red, 첫번째 green , 첫번째 blue on
      digitalWrite(latch1, LOW);
      digitalWrite(latch2, LOW);
      digitalWrite(latch3, LOW);

      shiftOut(data1, clock1, MSBFIRST, 1);
      shiftOut(data2, clock2, MSBFIRST, 1);
      shiftOut(data3, clock3, MSBFIRST, 1); 

      digitalWrite(latch1, HIGH);
      digitalWrite(latch2, HIGH);
      digitalWrite(latch3, HIGH);
       lcd.clear();
       lcd.print("3P");
      } // close else
   if(digitalRead(go_button)==HIGH)
   {
    
            lcd.clear();
            String str(board[0]);
            lcd.print(str); 
            delay(1000);
      break;
   }//close if
   //close if
 } //close while

} //close setup

void loop() {
while(1){
   while (1) {
      if (start_count>=1)//1p
      {

          r=0;
          r_pre = r_num;     
       if(r_island==0)
       {
      if (digitalRead(go_button) == HIGH)
             { 
              color=0;
              color=random(6)+1;
            } //close if(roll dice)
             r = r + color;
          
            lcd.clear();
            lcd.print(r);
            lcd.print(" move forward");
            delay(1000);
         digitalWrite(r_led[r_num],LOW);
           r_num = r_num + color;
        
         for(r_pre; r_pre<=r_num;r_pre++){
              digitalWrite(r_led[r_pre-1],LOW);
              delay(300);
                if(r_pre == 12){
                digitalWrite(r_led[0],HIGH);
                lcd.clear();
                lcd.print("red win!!");  
                delay(3000);
                exit(1);}  //close if(win and exit)
              digitalWrite(r_led[r_pre],HIGH);} //close for (turn on led)
            } //close if island
       else
       {
        r_island--;
         lcd.clear();
            String str(board[r_num]);
            lcd.print(str);   
            lcd.setCursor(0,1);
            lcd.print(r_island);
            lcd.print(" time rest");
       } //close else island
         if(r_num==0)
         {
            lcd.clear();
            String str(board[r_num]);
            lcd.print(str);   
         }//close if 0
         else if(r_num==6)
         { 
          if(r_island==0)
         {
           r_island=2; 
            lcd.clear();
            String str(board[r_num]);
            lcd.print(str); 
            lcd.setCursor(0,1);
            lcd.print("2 time rest");   
         } //close if

         } //close else if 6
         else if(r_num==1||r_num==3||r_num==5||r_num==8||r_num==10)
         {
            ran=0;       
         
             lcd.clear();
             ran=random(5);
             String str(user[ran]);
            lcd.print(str); 
           
         } //close else if 1,3,5,8,10
         else
         {
          ran=0;       
         
             lcd.clear();
             ran=random(6);
             String str(random_key[ran]);
             lcd.print("Random key!");
             lcd.setCursor(0,1);
            lcd.print(str);
            if(ran==0)
            {
              r_island=2;
              digitalWrite(r_led[r_num],LOW);
              r_num=6;
              digitalWrite(r_led[r_num],HIGH); 
              break;
            } //close if ran0
            else if(ran==1)
            {
               digitalWrite(r_led[r_num],LOW);
              r_num=0;
              digitalWrite(r_led[r_num],HIGH); 
              break;
            } //close else if ran1
            else if(ran==2)
            {
              digitalWrite(r_led[r_num],LOW);
              r_pre = r_num;
              r_num = r_num + 2;
              for(r_pre; r_pre<=r_num;r_pre++){
                  digitalWrite(r_led[r_pre-1],LOW);
                  delay(300);
                  digitalWrite(r_led[r_pre],HIGH);} //close for(go 2 blocks)
                break;
            } //close else if ran2
            else if(ran==3)
            {
               digitalWrite(r_led[r_num],LOW);
              r_pre = r_num;
              r_num = r_num + 1;
              for(r_pre; r_pre<=r_num;r_pre++){
                  digitalWrite(r_led[r_pre-1],LOW);
                  delay(300);
                  digitalWrite(r_led[r_pre],HIGH);} //close for(go 1 block)
                break;
            } //close else if ran3
            else if(ran==4)
            {
                digitalWrite(r_led[r_num],LOW);
              r_pre = r_num;
              r_num = r_num - 2;
              for(r_pre; r_pre>=r_num;r_pre--){
                  digitalWrite(r_led[r_pre+1],LOW);
                  delay(300);
                  digitalWrite(r_led[r_pre],HIGH);} //close for(go back 2 blocks)
                break;
            } //close else if ran4
            else
            {
              digitalWrite(r_led[r_num],LOW);
              r_pre = r_num;
              r_num = r_num - 1;
              for(r_pre; r_pre>=r_num;r_pre--){
                  digitalWrite(r_led[r_pre+1],LOW);
                  delay(300);
                  digitalWrite(r_led[r_pre],HIGH);} //close for(go back 1 block)
                break;
             } //close else ran5
         } // close else 2,4,7,9,11
        }//close if
      } //close 1P(red)
   
     while (1)
        {
          if (start_count>=2)//2p
         {
           g=0; 
           g_pre = g_num;
           if(r_island==0)
           { 
              if (digitalRead(go_button) == HIGH)
               {
                color=0;
                 color=random(6)+1;
               } //close if(roll dice)
               g = g + color;
               lcd.clear();
               lcd.print(g);
               lcd.print(" move forward");
               delay(1000);
               digitalWrite(g_led[g_num],LOW);
               g_num = g_num + color;
          
               for(g_pre; g_pre<=g_num;g_pre++){
                  digitalWrite(g_led[g_pre-1],LOW);
                  delay(300);
                  if(g_pre == 12){
                  digitalWrite(g_led[0],HIGH);
                  lcd.clear();
                  lcd.print("green win!!");  
                  delay(3000);
                  exit(1);}  //close if(win and exit)
              digitalWrite(g_led[g_pre],HIGH);
              } //close for(turn up led)
            } //close if island
            else
            {
               g_island--;
               lcd.clear();
               String str(board[g_num]);
               lcd.print(str);   
               lcd.setCursor(0,1);
               lcd.print(g_island);
               lcd.print(" time rest");
               break;
            } //close else island
          if(g_num==0)
           {
             lcd.clear();
             String str(board[g_num]);
            lcd.print(str); 
           } //close if 0
          else if(g_num==6)
           {  
            if(g_island==0)
              {
               g_island=2; 
               lcd.clear();
               String str(board[g_num]);
               lcd.print(str); 
               lcd.setCursor(0,1);
               lcd.print("2 time rest");   
            } //close if
          } // close else if 6
         else if(g_num==1||g_num==3||g_num==5||g_num==8||g_num==10)
         {
            ran=0;       
         
             lcd.clear();
             ran=random(5);
              String str(user[ran]);
            lcd.print(str); 
          
         } //close else if 1,3,5,8,10
         else
         {
          ran=0;       
         
             lcd.clear();
             ran=random(6);
             String str(random_key[ran]);
             lcd.print("Random key!");
             lcd.setCursor(0,1);
             lcd.print(str);
            if(ran==0)
            {
              g_island=2;
              digitalWrite(g_led[g_num],LOW);
              g_num=6;
              digitalWrite(g_led[g_num],HIGH); 
              break;
            }  //close else if ran0
            else if(ran==1)
            {
               digitalWrite(g_led[g_num],LOW);
              g_num=0;
              digitalWrite(g_led[g_num],HIGH); 
              break;
            }  //close else if ran1
            else if(ran==2)
            {
              digitalWrite(g_led[g_num],LOW);
              g_pre = g_num;
              g_num = g_num + 2;
              for(g_pre; g_pre<=g_num;g_pre++){
                  digitalWrite(g_led[g_pre-1],LOW);
                  delay(300);
                  digitalWrite(g_led[g_pre],HIGH);} //close for(go 2 blocks)
                break;
            } //close else if ran2
            else if(ran==3)
            {
               digitalWrite(g_led[g_num],LOW);
              g_pre = g_num;
              g_num = g_num + 1;
              for(g_pre; g_pre<=g_num;g_pre++){
                  digitalWrite(g_led[g_pre-1],LOW);
                  delay(300);
                  digitalWrite(g_led[g_pre],HIGH);} //close for(go 1 block)
                break;
            } //close else if ran3
            else if(ran==4)
            {
               digitalWrite(g_led[g_num],LOW);
              g_pre = g_num;
              g_num = g_num - 2;
              for(g_pre; g_pre>=g_num;g_pre--){
                  digitalWrite(g_led[g_pre+1],LOW);
                  delay(300);
                  digitalWrite(g_led[g_pre],HIGH);} //close for(go back 2 blocks)
                break;
            } //close else if ran4
            else
            {
              digitalWrite(g_led[g_num],LOW);
              g_pre = g_num;
              g_num = g_num - 1;
              for(g_pre; g_pre>=g_num;g_pre--){
                  digitalWrite(g_led[g_pre+1],LOW);
                  delay(300);
                  digitalWrite(g_led[g_pre],HIGH);} //close for(go back 1 block)
                break;
            } //close else ran5
         } // close else 2,4,7,9,11
        }//close if
      } //close 2P(green)
         
      while (1)
       {  
        if (start_count>=3)//3p
         { 
          b=0;
          b_pre = b_num;
          if(b_island==0)
          { 
            if (digitalRead(go_button) == HIGH)
               {
                  color = 0;
                  color = random(6)+1;
               }//close if(roll dice)
               b = b + color;
            lcd.clear();
            lcd.print(b);
            lcd.print(" move forward");
            delay(1000);
                digitalWrite(b_led[b_num],LOW);
                  b_num = b_num + color;
             for(b_pre; b_pre<=b_num;b_pre++){
              digitalWrite(b_led[b_pre-1],LOW);
              delay(300);
              if(b_pre == 12){
                digitalWrite(b_led[0],HIGH);
                lcd.clear();
                lcd.print("blue win!!");  
                delay(3000);
                exit(1);
                } // close if(win and exit)
              digitalWrite(b_led[b_pre],HIGH);
              } //close for(turn up led)
            } //close if (island)
        else
        {
           b_island--;
           lcd.clear();
           String str(board[b_num]);
           lcd.print(str);   
           lcd.setCursor(0,1);
           lcd.print(b_island);
           lcd.print(" time rest");
         }  //close else(island)
         if(b_num==0)
         {
            lcd.clear();
             String str(board[b_num]);
            lcd.print(str); 
         } //close if 0
         else if(b_num==6)
         {
             if(b_island==0)
            {
                b_island=2; 
                lcd.clear();
                String str(board[b_num]);
                lcd.print(str);
                lcd.setCursor(0,1);
                lcd.print("2 time rest");   
             } //close if
         } //close else if 6
         else if(b_num==1||b_num==3||b_num==5||b_num==8||b_num==10)
         {
            ran=0;       
            lcd.clear();
            ran=random(5);
            String str(user[ran]);
            lcd.print(str);
         } //close else if 1,3,5,8,10
         else
         {
           ran=0;       
           lcd.clear();
           ran=random(6);
           String str(random_key[ran]);
           lcd.print("Random key!");
           lcd.setCursor(0,1);
           lcd.print(str);
           if(ran==0)
            {
              b_island=2;
              digitalWrite(b_led[b_num],LOW);
              b_num=6;
              digitalWrite(b_led[b_num],HIGH); 
              break;
            } //close if ran0
            else if(ran==1)
            {
               digitalWrite(b_led[b_num],LOW);
              b_num=0;
              digitalWrite(b_led[b_num],HIGH); 
              break;
            } //close else if ran1
            else if(ran==2)
            {
              digitalWrite(b_led[b_num],LOW);
              b_pre = b_num;
              b_num = b_num + 2;
              for(b_pre; b_pre<=b_num;b_pre++){
                  digitalWrite(b_led[b_pre-1],LOW);
                  delay(300);
                  digitalWrite(b_led[b_pre],HIGH);} //close for(go 2 blocks)
                break;
            } //close else if ran2
            else if(ran==3)
            {
              digitalWrite(b_led[b_num],LOW);
              b_pre = b_num;
              b_num = b_num + 1;
              for(b_pre; b_pre<=b_num;b_pre++){
                  digitalWrite(b_led[b_pre-1],LOW);
                  delay(300);
                  digitalWrite(b_led[b_pre],HIGH);} //close for(go back 1 block)
                break;
            } //close else if ran3
            else if(ran==4)
            {
              digitalWrite(b_led[b_num],LOW);
              b_pre = b_num;
              b_num = b_num - 2;
              for(b_pre; b_pre>=b_num;b_pre--){
                  digitalWrite(b_led[b_pre+1],LOW);
                  delay(300);
                  digitalWrite(b_led[b_pre],HIGH);} //close for(go back 2 blocks)
                break;
            } //close else if ran4
            else
            {
              digitalWrite(b_led[b_num],LOW);
              b_pre = b_num;
              b_num = b_num - 1;
              for(b_pre; b_pre>=b_num;b_pre--){
                  digitalWrite(b_led[b_pre+1],LOW);
                  delay(300);
                  digitalWrite(b_led[r_pre],HIGH);} //close for(go back 1 block)
                break;
            } //close else ran5
         } // close else 2,4,7,9,11
         } //close if
       } //close 3P(blue)  
    } //close all while
   } //close loop
