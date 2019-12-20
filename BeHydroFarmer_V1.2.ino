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
#include <BH1750.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <avr/wdt.h>
#include <EEPROM.h>

//------------------------------ DEFINICION DE PINES ------------------------------
//-------------------------------- LUCES RGB  -------------------------------------
#define T1green 6
#define T1red 7
#define T1blue 8
#define T2green 22
#define T2red 23
#define T2blue 24
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
#define PinTrig 3                       //Sensor ultrasonico destinado a medir el nivel de agua en el tanque         
#define PinEcho 4
// Constante velocidad sonido en cm/s
const float VelSon = 34000.0;
float distancia;
// Número de muestras
const int numLecturas = 50;
 
float lecturas[numLecturas]; // Array para almacenar lecturas
int lecturaActual = 0; // Lectura por la que vamos
float total = 0; // Total de las que llevamos
float media = 0; // Media de las medidas
bool primeraMedia = false; // Para saber que ya hemos calculado por lo menos una
//---------------------------- VARIABLES DEL SISTEMA ----------------------------------
char RGB[4][3] =
{
 {T1green, T1red, T1blue},                  
 {T2green, T2red, T2blue},         
 {T3green, T3red, T3blue},              //Arreglo para optimizar las variables de los colores RGB
 {motoBomba, ResCalefactora, trece}     //Incluidos los actuadores y pin 13 para hacer pruebas de funcionamiento
};
//---------------- VARIABLES PARA EL MANEJO DE ACTIVACION DE LAS LUCES RGB DESDE LA PANTALLA----------------------
int r=0;                                //Variable para hacer el for y asi asignar los pines de salida
int contadorRGB = 0;

int contadorTira1FullSpectre = 0;
int contadorTira1Rojo = 0;
int contadorTira1Azul = 0;

int contadorTira2FullSpectre = 0;
int contadorTira2Rojo = 0;
int contadorTira2Azul = 0;

int contadorTira3FullSpectre = 0;
int contadorTira3Rojo = 0;
int contadorTira3Azul = 0;

int contadorTira4FullSpectre = 0;
int contadorTira4Rojo = 0;
int contadorTira4Azul = 0;
//------------------------------ TIEMPO EN MILLIS --------------------------------
unsigned long time;
unsigned long tr = 0;
int tiempo1 = 1000;                  //Tiempo de espera para mandar los datos por monitor serial
int tiempo2 = 1000;                  //Tiempo de espera para mandar los datos por monitor serial

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
char nombreDia[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
char nombreMes[12][12]= {"Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
int segundo,minuto,hora,dia,mes,diaDeLaSemana;
long anio; //variable año

DateTime HoraFecha;


//---------------------------SENSOR DE TEMPERATURA DEL AGUA---------------------------
OneWire ourWire(11);              //Sensor de temperatura del agua
DallasTemperature TempAqua(&ourWire); //Libreria utilizada para controlar el sensor de temperatura del agua

//----------------------------SENSOR DE CONDUCTIVIDAD ELECTRICA--------------------------
// CONSTANTS / SETTINGS

const byte    POWER_PIN       = 35;        // Digital pin to use for powering pulse circuit
const byte    EC_PIN          = A0;       // Analog pin used to read EC Meter volage 

const int     READ_DURATION   = 100;      // Amount of time to take reading for (ms)
const int     READ_INTERVAL   = 6000;     // Amount of time between readings (ms)

const String  SERIAL_OUTPUT_DELIMITER   = "  Voltaje  ";    // Cordoba expects a comma-delimited string
const int     SERIAL_OUTPUT_INTERVAL    = 175;    // Amount of time between serial outputs

// TIMESTAMPS

unsigned long currentTime     = 0;
unsigned long readStartTime   = 0;        // Time that the EC Meter read process starts
unsigned long lastOutputTime  = 0;        // Time of last serial output

// SENSORS

float ecMeterReading = 0;
float ecMeterVoltage = 0;
int PPM = 0;

//------------------------------------------------EEPROM MEMORY --------------------------------------------------

String EstadoLuz;

int ContadorHoras;
byte EstadoLuzMemoria;




void setup() {

    delay(100);                //Tiempo de retardo para estabilizar el void setup
    wdt_disable();                //Inicializamos el perro guardian para que cuanto el sistema se bloquee este se reinicie y vuelva a ejecutar el code
    pantalla.begin(9600);         //Inicializamos la conexion serial de la pantalla
    Serial.begin(9600);           //Inicializamos el puerto serial para poder visualizar los sensores en un monitor serial
    dht.begin();                  //Inicializamos el sensor de temperatura y humedad
    Wire.begin();                 //Inicializamos la libreria Wire para la comunicacion I2C
    Lumex.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);  //Inicializamos el sensor de luminosidad con su modo en HIGH
    rtc.begin();                  //Inicializamos el modulo de reloj 
    TempAqua.begin();             //Inicializamos el sensor de temperatura del agua
   // rtc.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)

//------------------------------------------------------------------------------------
    EstadoLuzMemoria = EEPROM.read(0);

//-----------------------------------------------------------------------------------  

    for (r=0; r<12; r++) pinMode(RGB[r], OUTPUT);  //Contador para barrer el arreglo de RGB y asignarlos con salidas

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------  
    pinMode(PinTrig, OUTPUT);     //pin como salida
    pinMode(PinEcho, INPUT);         //pin como entrada
    

//------------------------------------------------------------------------------------
    pinMode( POWER_PIN , OUTPUT );

//------------------------------------------------------------------------------------

    wdt_enable(WDTO_4S);          //Tiempo de espera del perro guardian para hacer un resect del codigo si se queda en un bucle infinito

//-------------------------------------------------------------------------------------

    if(EstadoLuzMemoria == 1){

        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        EstadoLuz = "ON";
    }
    else{

        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        EstadoLuz = "OFF";
    }
    Serial.println("Sistema encendido");
    //Serial.print(nombreDia[diaDeLaSemana]);Serial.print(" "); Serial.print(dia); Serial.print(" de "); Serial.print(nombreMes[mes-1]); Serial.print(" del "); Serial.print(anio);
    //Serial.println();
  
}





void loop() 
{

  botones();
  dataSensor();
  EncedidoHoras();
  SensorNivelAqua();
  EncedidoPython();
  
  
  //SensorEC();
 
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
   
       
 



