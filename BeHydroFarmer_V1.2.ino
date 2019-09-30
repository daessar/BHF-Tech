/*_________________________________________________________________________________

-------------------------------- Be Hydro Farmer ----------------------------------
_____________________________________V1.0__________________________________________
Este programa esta hecho para controlar un cualtivo hidroponico - acuaponico
___________________________________________________________________________________
*/


//--------------------------------- LIBRERIAS -------------------------------------
#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <BH1750.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <avr/wdt.h>

//------------------------------ DEFINICION DE PINES ------------------------------
//-------------------------------- LUCES RGB  -------------------------------------
#define T1green 7
#define T1red 6
#define T1blue 5
#define T2green 24
#define T2red 23
#define T2blue 22
#define T3green 25
#define T3red 26
#define T3blue 27
#define T4green 28
#define T4red 29
#define T4blue 30 
//-------------------------------- ACTUADORES ----------------------------------------
#define motoBomba 31
#define ResCalefactora 32
#define trece 13
//---------------------------- SENSOR ULTRASONICO---------------------------------
#define Trigger 4                       //Sensor ultrasonico destinado a medir el nivel de agua en el tanque         
#define Echo 3

//---------------------------- VARIABLES DEL SISTEMA ----------------------------------
const unsigned char RGB[4][3] =
{
 {T1green, T1red, T1blue},                  
 {T2green, T2red, T2blue},         
 {T3green, T3red, T3blue},              //Arreglo para optimizar las variables de los colores RGB
 {motoBomba, ResCalefactora, trece}     //Incluidos los actuadores y pin 13 para hacer pruebas de funcionamiento
};
//---------------- VARIABLES PARA EL MANEJO DE ACTIVACION DE LAS LUCES RGB DESDE LA PANTALLA----------------------
char r=0;                                //Variable para hacer el for y asi asignar los pines de salida
int contadorRGB = 0;

int contadorActivacionNivel1 = 0;

int contadorTira1FullSpectre = 0;
int contadorTira1Rojo = 0;
int contadorTira1Azul = 0;

int contadorActivacionNivel2 = 0;

int contadorTira2FullSpectre = 0;
int contadorTira2Rojo = 0;
int contadorTira2Azul = 0;

int contadorActivacionNivel3 = 0;

int contadorTira3FullSpectre = 0;
int contadorTira3Rojo = 0;
int contadorTira3Azul = 0;

int contadorActivacionNivel4 = 0;

int contadorTira4FullSpectre = 0;
int contadorTira4Rojo = 0;
int contadorTira4Azul = 0;
//------------------------------ TIEMPO EN MILLIS --------------------------------
unsigned long time;
unsigned long tr = 0;
int tiempo = 1000;                  //Tiempo de espera para mandar los datos por monitor serial

//------------------------------ PANTALLA TOUCH -----------------------------------
int Data;                           //Variable para recibir los datos desde la pantalla
SoftwareSerial pantalla(10, 9);     // 10=RX - 9=TX Asignacion de pines para abrir otro puerto serial y asi tener un solo puerto de comunicacion con la pantalla


//---------------------------- SENSOR DE LUMINOSIDAD -----------------------------------
BH1750 Lumex(0x23);                //Sensor de luminosidad, comunicacion I2C por eso no se le asigna pin digital


//------------------------ DTH11 HUMEDAD Y TEMPERATURA ----------------------------
DHT dht(2, DHT11);                 //Sensor de humedad y temperatura relativa asignado al pin digital 2

//------------------------------ VARIABLES ACTUADORES ------------------------------
int contadorMotoBomba = 0;
int contadorResCalefactora = 0;

//------------------------------- RTH TIEMPO ----------------------------------------
RTC_DS3231 rtc;                   // Modulo del tiempo, comunicacion I2C, nos diferenciara entre el dia y la noche


//---------------------------SENSOR DE TEMPERATURA DEL AGUA---------------------------
OneWire ourWire(11);              //Sensor de temperatura del agua
DallasTemperature TempAqua(&ourWire); //Libreria utilizada para controlar el sensor de temperatura del agua


void setup() {

    wdt_disable();                //Inicializamos el perro guardian para que cuanto el sistema se bloquee este se reinicie y vuelva a ejecutar el code
    pantalla.begin(9600);         //Inicializamos la conexion serial de la pantalla
    Serial.begin(9600);           //Inicializamos el puerto serial para poder visualizar los sensores en un monitor serial
    dht.begin();                  //Inicializamos el sensor de temperatura y humedad
    Wire.begin();                 //Inicializamos la libreria Wire para la comunicacion I2C
    Lumex.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);  //Inicializamos el sensor de luminosidad con su modo en HIGH
    rtc.begin();                  //Inicializamos el modulo de reloj 
    TempAqua.begin();             //Inicializamos el sensor de temperatura del agua

   
//-----------------------------------------------------------------------------------  
    pinMode(Trigger, OUTPUT);     //pin como salida
    pinMode(Echo, INPUT);         //pin como entrada
    digitalWrite(Trigger, LOW);   //Inicializamos el pin con 0
//-----------------------------------------------------------------------------------  

    for (r=0; r<12; r++) pinMode(RGB[r], OUTPUT);  //Contador para barrer el arreglo de RGB y asignarlos con salidas

//-----------------------------------------------------------------------------------
      
    wdt_enable(WDTO_4S);          //Tiempo de espera del perro guardian para hacer un resect del codigo si se queda en un bucle infinito
   Tira1LucesOff();
  Tira2LucesOff();
  Tira3LucesOff();
  Tira4LucesOff();
     delay(100);                  //Tiempo de retardo para estabilizar el void setup
}





void loop() {

  wdt_reset();                    //Funcion del perro guardian
  TempAqua.requestTemperatures(); //Funcion del sensor de temperatura del agua
  int valorTempAqua= TempAqua.getTempCByIndex(0);   //Variable que almacena los datos arrojados por el sensor de temperatura del agua
  int valorLumex = Lumex.readLightLevel();  //Variable que almacena los datos arrojados por el sensor de luminosidad
  DateTime now = rtc.now();       //Funcion que toma el valor del tiempo entrado por el modulo RTC
  int t = dht.readTemperature();  //Variable que almacena los datos arrojados por el sensor de temperatura 
  int h = dht.readHumidity();     //Variable que almacena los datos arrojados por el sensor de humedad
  time = millis();                //Funcion del tiempo en millis
  boolean activacionLumex;        //Variable de dos valores para hacer la activacion o desactivacion de sensor de luminosidad
   

  if (pantalla.available()){      //Condicional que asigna los datos de la comunicacion serial a la variable data
        Data = pantalla.read();
  }
  switch (Data)                   //Condicional para evaluar los datos entregados por la comunicacion serial
  {
      case 1:                     //Boton para activar el contador de la motobomba
       contadorMotoBomba++;
        switch (contadorMotoBomba)
            {
            case 1:               //Activacion de la motobomba
              Serial.println("motoBomba Encendida"); 
              digitalWrite(motoBomba,HIGH);
              digitalWrite(trece,HIGH);
              break;

            case 2:               //Desactivacion de la motobomba
              
              digitalWrite(trece,LOW);
              digitalWrite(motoBomba,LOW);
              Serial.println("motoBomba Apagada");
              contadorMotoBomba = 0;   //Se reinicia la variable contador para la motobomba
              
              break;  
            }
            break;
      case 2:
      contadorRGB++;              //Activacion de la variable contador para las luces RGB
        switch (contadorRGB)
            {
            case 1:               //Encendido de todos los niveles de las luces RGB en fullSpectre (1,2,3,4)
              Serial.println("RGB Encendida"); 
              Tira1LucesFullSpectre();
              Tira2LucesFullSpectre();
              Tira3LucesFullSpectre();
              Tira4LucesFullSpectre();
              digitalWrite(trece,HIGH);
              break;

            case 2:               //Apagado de todos los niveles de las luces RGB en fullSpectre (1,2,3,4)
              Serial.println("RGB Apagada");
              Tira1LucesOff();
              Tira2LucesOff();
              Tira3LucesOff();
              Tira4LucesOff();
              digitalWrite(trece,LOW);          
              contadorRGB = 0;    //Se reinicia la variable contador de las luces RGB
              break;  
            }
            break;
  
  
  
      case 3:                     //Activacion de la variable contador para la resistencia electrica
         contadorResCalefactora++;
         switch (contadorResCalefactora)
            {
            case 1:               //Encedido de la resistencia calefactora
              Serial.println("ResCalefactora Encendida"); 
              digitalWrite(ResCalefactora,HIGH);
              digitalWrite(trece,HIGH);
              break;

            case 2:               //Apagado de la resistencia calefactora
              digitalWrite(ResCalefactora,LOW);
              digitalWrite(trece,LOW);
              Serial.println("ResCalefactora Apagada");
              contadorResCalefactora = 0;
              
              break;  
            }

  


           
//------------------------------------- ENCEDIDO DE LUCES POR NIVELES------------------------------------
      case 4:                     //Confirmacion de encendido del nivel 1 de las luces RGB                
        contadorActivacionNivel1++;
          switch (contadorActivacionNivel1)
            {
            case 1:
               Serial.println("Boton Nivel 1 Luces Encendido");
               break; 
            

            case 2:
               Serial.println("Boton Nivel 1 Luces Apagado"); 
               contadorActivacionNivel1 = 0;
               break;
            }
               break;



      case 5:                   //Confirmacion de encendido del nivel 2 de las luces RGB 
      contadorActivacionNivel2++;
          switch (contadorActivacionNivel2)
            {
            case 1:
               Serial.println("Boton Nivel 2 Luces Encendido");
               break; 
            

            case 2:
               Serial.println("Boton Nivel 2 Luces Apagado"); 
               contadorActivacionNivel2 = 0;
               break;
            }
               break;


      case 6:                   //Confirmacion de encendido del nivel 3 de las luces RGB 
       contadorActivacionNivel3++;
          switch (contadorActivacionNivel3)
            {
            case 1:
               Serial.println("Boton Nivel 3 Luces Encendido");
               break; 
            

            case 2:
               Serial.println("Boton Nivel 3 Luces Apagado"); 
               contadorActivacionNivel3 = 0;
               break;
            }
               break;


      case 7:                   //Confirmacion de encendido del nivel 4 de las luces RGB 
       contadorActivacionNivel4++;
          switch (contadorActivacionNivel4)
            {
            case 1:
               Serial.println("Boton Nivel 4 Luces Encendido");
               break; 
            

            case 2:
               Serial.println("Boton Nivel 4 Luces Apagado"); 
               contadorActivacionNivel4 = 0;
               break;
            }
               break;



              
//------------- ENCEDIDO DE LUCES ESPECIFICADO EL COLOR EN EL PRIMER NIVEL DE LUCES RGB --------------------------------

      case 8:                   //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color full Spectre
        contadorTira1FullSpectre++;
          switch (contadorTira1FullSpectre)
            {
            case 1:
              if(contadorActivacionNivel1==1 && contadorTira1FullSpectre==1)
                  {
                    Tira1LucesFullSpectre();
                    Serial.println("Luz nivel 1 Full Spectre activada");
                  }
                break;


            case 2:             
              Tira1LucesOff();
              contadorTira1FullSpectre = 0;
              Serial.println("Luz nivel 1 Full Spectre Apagada");

            }

      case 9:                   //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color Rojo 
        contadorTira1Rojo++;
          switch (contadorTira1Rojo)
            {
            case 1:
              if(contadorActivacionNivel1==1 && contadorTira1Rojo==1)
                  {
                    Tira1LucesRojo();
                    Serial.println("Luz nivel 1 Rojo activada");
                  }
                break;


            case 2:
              Tira1LucesOff();
              contadorTira1Rojo = 0;
              Serial.println("Luz nivel 1 Rojo Apagada");

            }

      case 10:                  //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color Azul
        contadorTira1Azul++;
          switch (contadorTira1Azul)
            {
            case 1:
              if(contadorActivacionNivel1==1 && contadorTira1Azul==1)
                  {
                    Tira1LucesAzul();
                    Serial.println("Luz nivel 1 Azul activada");
                  }
                break;


            case 2:
              Tira1LucesOff();
              contadorTira1Azul = 0;
              Serial.println("Luz nivel 1 Azul Apagada");

            }
  }

  
   switch(now.hour())
   {
      case 18:
        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        activacionLumex = false;
        break;

      case 21:
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        break;
      
      case 04:
        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
       break;

      case 06:
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        activacionLumex = true;
        break;
   }   
      
        
      while (activacionLumex == true){
        if (valorLumex <= 30){
          Tira1LucesFullSpectre();
          Tira2LucesFullSpectre();
          Tira3LucesFullSpectre();
          Tira4LucesFullSpectre();
      }
      }
      
        if (time-tr > tiempo){
        tr = time;      
  
        pantalla.print("Temperatura.val=");
        pantalla.print(t);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);
 

        pantalla.print("Humedad.val=");
        pantalla.print(h);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);

        pantalla.print("Luminosidad.val=");
        pantalla.print(valorLumex);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);

        pantalla.print("TempAq.val=");
        pantalla.print(valorTempAqua);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);

        Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
        Serial.print("                 Ambiente Sensor                           "); Serial.println("                      Aqua Sensor                          ");
        Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
        Serial.print("Temperatura = "); Serial.print(t); Serial.print(" | "); 
        Serial.print("Humedad = "); Serial.print(h); Serial.print(" | ");  
        Serial.print("Luminosidad = "); Serial.print(valorLumex); Serial.print(" |         "); 
        Serial.print("Temperatura del aqua = "); Serial.println(valorTempAqua); Serial.print(" | ");
   
        }
   
    }
   
   
   
       
 


void Tira1LucesFullSpectre(){
    analogWrite (T1green,0);
    analogWrite (T1red,255);
    analogWrite (T1blue,130);
}
void Tira1LucesRojo(){
    analogWrite (T1green,0);
    analogWrite (T1red,255);
    analogWrite (T1blue,0);
}
void Tira1LucesAzul(){
    analogWrite (T1green,0);
    analogWrite (T1red,0);
    analogWrite (T1blue,255);
}
 void Tira1LucesOff(){
    analogWrite (T1green,0);
    analogWrite (T1red,0);
    analogWrite (T1blue,0);   
}


void Tira2LucesFullSpectre(){
    analogWrite (T2green,0);
    analogWrite (T2red,255);
    analogWrite (T2blue,130);
}
void Tira2LucesRojo(){
    analogWrite (T2green,0);
    analogWrite (T2red,255);
    analogWrite (T2blue,0);
}
void Tira2LucesAzul(){
    analogWrite (T2green,0);
    analogWrite (T2red,0);
    analogWrite (T2blue,255);
}
void Tira2LucesOff(){
    analogWrite (T2green,0);
    analogWrite (T2red,0);
    analogWrite (T2blue,0);
}


void Tira3LucesFullSpectre(){
    analogWrite (T3green,0);
    analogWrite (T3red,255);
    analogWrite (T3blue,130);
}
void Tira3LucesRojo(){
    analogWrite (T3green,0);
    analogWrite (T3red,255);
    analogWrite (T3blue,0);
}
void Tira3LucesAzul(){
    analogWrite (T3green,0);
    analogWrite (T3red,0);
    analogWrite (T3blue,255);
}
void Tira3LucesOff(){
    analogWrite (T3green,0);
    analogWrite (T3red,0);
    analogWrite (T3blue,0);
}



void Tira4LucesFullSpectre(){
    analogWrite (T4green,255);
    analogWrite (T4red,150);
    analogWrite (T4blue,0);
}
void Tira4LucesRojo(){
    analogWrite (T4green,0);
    analogWrite (T4red,255);
    analogWrite (T4blue,0);
}
void Tira4LucesAzul(){
    analogWrite (T4green,0);
    analogWrite (T4red,0);
    analogWrite (T4blue,255);
}
void Tira4LucesOff(){
    analogWrite (T4green,0);
    analogWrite (T4red,0);
    analogWrite (T4blue,0);
    
}

