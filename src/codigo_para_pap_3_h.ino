#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>
const int HORA = 12;
const int MINUTO = 49;
const int SEGUNDO = 3;
const int HORA2 = 12;
const int MINUTO2 = 50;
const int SEGUNDO2 = 3;
const int HORA3 = 12;        
const int MINUTO3 = 51;
const int SEGUNDO3 = 3;
int estado_chave;
Servo porta1;
Servo porta2;
Servo porta3;

RTC_DS1307 rtc;

char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"}; //Dias da semana


int echo1 =5;
int trig1 =2;
int echo2 =6;
int trig2 =3;
int echo3 =7;
int trig3 =4;
bool vazio1=false;
bool tamp_aberta1=false;
bool carregado1=false; 
bool vazio2=false;
bool tamp_aberta2=false;
bool carregado2=false; 
bool vazio3=false;
bool tamp_aberta3=false;
bool carregado3=false; 
int teste=0;
int posicao1=0;
int posicao2=0;
int posicao3=0;

void setup(){
  Serial.begin(9600);
  porta1.write(0);
  porta2.write(0);
  porta3.write(0);
  pinMode(echo1,INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo3,INPUT);
  pinMode(trig3, OUTPUT);
  Serial.println("INICIO");
  porta1.attach(11);
  porta2.attach(10);
  porta3.attach(9);
  pinMode(8, INPUT);

   if (!rtc.begin()) {                          
      Serial.println("RTC NAO INICIALIZADO"); 
      while (1);                                 
  }
  rtc.adjust(DateTime(2020, 11, 16, 12, 48, 45)); 
  delay(100);                           
}
  
void loop()
  {
     DateTime agora = rtc.now();            
  Serial.print("Data: ");
  Serial.print(agora.day(), DEC);        
  Serial.print('/');                     
  Serial.print(agora.month(), DEC);      
  Serial.print('/');                     
  Serial.print(agora.year(), DEC);       
  Serial.print(" / Dia da semana: ");                       
  Serial.print(diasDaSemana[agora.dayOfTheWeek()]);         
  Serial.print(" / Horas: ");                               
  Serial.print(agora.hour(), DEC);                          
  Serial.print(':');                                        
  Serial.print(agora.minute(), DEC);                        
  Serial.print(':');                                        
  Serial.print(agora.second(), DEC);                        
  Serial.println();                                         
  delay(1000);          

       
   estado_chave=digitalRead(8);
   if(estado_chave==HIGH)
   {
      levanta_todos();
      caixa();
   }
   else
   {  
       fechartodos();
        Serial.println("Pronto");
       horas();
   }

 }
 
     
     
     
     
void caixa()
{
     
     if(verificasensor(trig1, echo1)<10)
       
     {
         carregado1=true;
         Serial.print(teste);
       //Serial.print("caixa1");
       Serial.print(verificasensor(trig1, echo1));
     }
  else
    {
    carregado1=false;
    }
    
   if(verificasensor(trig2, echo2)<10)
       
     {
         carregado2=true;
         Serial.print(teste);
       //Serial.print("caixa2");
       Serial.print(verificasensor(trig2, echo2));
     }
  else
    {
    carregado2=false;
    }

    if(verificasensor(trig3, echo3)<10)
       
     {
         carregado3=true;
         Serial.print(teste);
       //Serial.print("caixa3");
       Serial.print(verificasensor(trig3, echo3));
     }
  else
    {
    carregado3=false;
    }
   
}


   void horas()
{
        DateTime agora = rtc.now();
        //estado_hora1=digitalRead(A0);
         if(carregado1==true && (agora.hour() == HORA) && (agora.minute() == MINUTO) && (agora.second() == SEGUNDO) )  // verificar com dupla cond
         { 
           Serial.println("aaaaaaaaaaaaaaaaaaaaa");
           levanta_porta1();
           Serial.println("ativar hora 1");
         }
         
      else
      {
       Serial.println("desativar hora 1");
      }



if(carregado2==true && (agora.hour() == HORA2) && (agora.minute() == MINUTO2) && (agora.second() == SEGUNDO2) )  // verificar com dupla cond
         { 
           levanta_porta2();
           Serial.println("ativar hora 2");
         }
         
      else
      {
       Serial.println("desativar hora 2");
      }

      
      if(carregado3==true && (agora.hour() == HORA3) && (agora.minute() == MINUTO3) && (agora.second() == SEGUNDO3) )  // verificar com dupla cond
         { 
           levanta_porta3();
           Serial.println("ativar hora 3");
         }
         
      else
      {
       Serial.println("desativar hora 3");
      }






      
}  
  
     
 long verificasensor(int trig, int echo)
 {
 long duration, dista;
   digitalWrite(trig, LOW);
   delayMicroseconds(2);
   digitalWrite(trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig, LOW);
   duration = pulseIn(echo, HIGH);
   dista = duration / 29.1 /2; 
   Serial.println (dista);
   dista == teste;
   delay(10);
   return dista; 
  }


/*//## abrir tampa 1 ##
 void abrirtampa1()
 {
  // porta1.write(90);  // tampa aberta
   int posicao=0;
   for(int i=0;i<90;i++)
   {posicao=posicao+10;
    delay(200);
    porta1.write(posicao);
   }  
   tamp_aberta1=true;
   while(verificasensor(trig1, echo1)<13){
        vazio1=false;
   }
   vazio1=true;
   delay(4000);
   while(verificasensor(trig1, echo1)>13){
   
   }
   vazio1=false;
  fechartampa1();
   
}

//##fechar tampa 1 ##
  void fechartampa1()
  { 
    delay(4000);
    porta1.write(0);
    
  }

*/
 


void levanta_todos() 

{
  while(posicao1<90)
 {
    porta1.write(posicao1);
    porta2.write(posicao1); 
    porta3.write(posicao1);
  
    posicao1=posicao1+10;
     delay(150);
  }
}

 void fechartodos()
  {
   while(posicao1>0){

    porta1.write(posicao1);
    porta2.write(posicao1);
    porta3.write(posicao1);
  
    posicao1=posicao1-10;
     delay(150);
  }
  }


void levanta_porta1() {
  
 
  while(posicao1<90)
  {
    posicao1=posicao1+10;
     delay(150);

    porta1.write(posicao1); 
   }  
   tamp_aberta1=true;
   while(verificasensor(trig1, echo1)<10){
        vazio1=false;
        delay(4000);
   }
   vazio1=true;
   delay(4000);
   while(verificasensor(trig1, echo1)>10){
   
   }
   vazio1=false;
 
  delay(4000);
  fecha_porta1();
  }

  void fecha_porta1() {
  
  while (posicao1>0){
    porta1.write(posicao1); 
    posicao1=posicao1-10;
    delay(150);
  }

}

void levanta_porta2() {
  
 
  while(posicao1<90)
  {
    posicao1=posicao1+10;
     delay(150);

    porta2.write(posicao1); 
   }  
   tamp_aberta2=true;
   while(verificasensor(trig2, echo2)<10){
        vazio2=false;
        delay(4000);
   }
   vazio2=true;
   delay(4000);
   while(verificasensor(trig2, echo2)>10){
   
   }
   vazio2=false;
 
  delay(4000);
  fecha_porta2();
  }

  void fecha_porta2() {
  
  while (posicao1>0){
    porta2.write(posicao1); 
    posicao1=posicao1-10;
    delay(150);
  }

}

void levanta_porta3() {
  
 
  while(posicao1<90)
  {
    posicao1=posicao1+10;
     delay(150);

    porta3.write(posicao1); 
   }  
   tamp_aberta3=true;
   while(verificasensor(trig3, echo3)<10){
        vazio3=false;
        delay(4000);
   }
   vazio3=true;
   delay(4000);
   while(verificasensor(trig3, echo3)>10){
   
   }
   vazio3=false;
 
  delay(4000);
  fecha_porta3();
  }

  void fecha_porta3() {
  
  while (posicao1>0){
    porta3.write(posicao1); 
    posicao1=posicao1-10;
    delay(150);
  }

}
