#include"MyLock.h"
void init()
{
     wiringPiSetup() ;
     //步
     pinMode (25, OUTPUT) ;
     //方向
     pinMode (24, OUTPUT) ;

     pinMode (23, OUTPUT) ;

     //正极
     pinMode (22, OUTPUT) ;

     //蜂鸣器信号
     pinMode (21, OUTPUT) ;

}

int openLock(void)
{

    int i = 0;
   digitalWrite(21, HIGH) ;
   digitalWrite(24, LOW) ;
  for(i=0;i<100;i++)
  {
    digitalWrite(25, HIGH) ;
   delay(1);

   digitalWrite(25,LOW);
   delay(1);

  }
 digitalWrite(21, LOW) ;


 for(i=0;i<7;i++)
 {
       delay(200);
      digitalWrite(21, HIGH) ;
      delay(200);
      digitalWrite(21, LOW) ;
 }
 return 0;
}
int closeLock(void)
{

    int i = 0;
digitalWrite(24, HIGH) ;
  for(i=0;i<100;i++)
  {
    digitalWrite(25, HIGH) ;
   delay(1);

   digitalWrite(25,LOW);
   delay(1);

  }

  return 0;
}
void setPowerPin23(){

    digitalWrite(23, HIGH) ;
    digitalWrite(22, HIGH) ;
}
