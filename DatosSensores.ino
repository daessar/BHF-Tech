void dataSensor(){
    int valorLumex = Lumex.readLightLevel();  //Variable que almacena los datos arrojados por el sensor de luminosidad
    int t = dht.readTemperature();  //Variable que almacena los datos arrojados por el sensor de temperatura 
    int h = dht.readHumidity();     //Variable que almacena los datos arrojados por el sensor de humedad
    //TempAqua.requestTemperatures(); //Funcion del sensor de temperatura del agua
    //int valorTempAqua= TempAqua.getTempCByIndex(0);   //Variable que almacena los datos arrojados por el sensor de temperatura del agua
    
    HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
    
    segundo=HoraFecha.second();
    minuto=HoraFecha.minute();
    hora=HoraFecha.hour();
    dia=HoraFecha.day();
    mes=HoraFecha.month();
    anio=HoraFecha.year();
    diaDeLaSemana=HoraFecha.dayOfTheWeek();
    boolean activacionLumex;        //Variable de dos valores para hacer la activacion o desactivacion de sensor de luminosidad    
    
     if (time-tr > tiempo1){
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
       // pantalla.print(valorTempAqua);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);
        

     //   Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
      //  Serial.print("                 Ambiente Sensor                           "); Serial.println("                      Aqua Sensor                          ");
       // Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
        
        Serial.print("Temperatura = "); Serial.print(t); Serial.print(" | "); 
        Serial.print("Humedad = "); Serial.print(h); Serial.print(" | ");  
        Serial.print("Luminosidad = "); Serial.print(valorLumex); Serial.println(" |         "); //Serial.println("Temperatura del aqua = "); 
        //Serial.println(valorTempAqua); Serial.print(" | ");

        
        Serial.print(hora);
        Serial.print(":");
        Serial.print(minuto);
        Serial.print(":");
        Serial.print(segundo);
        Serial.print(" , ");
        Serial.print(nombreDia[diaDeLaSemana]);
        Serial.print(" ");
        Serial.print(dia);
        Serial.print(" de ");
        Serial.print(nombreMes[mes-1]);
        Serial.print(" del ");
        Serial.print(anio);
        Serial.println();


            pantalla.print("Mes.txt=");
            pantalla.print(mes);
            pantalla.print(".""");
            
            pantalla.write(0xff);
            pantalla.write(0xff);
            pantalla.write(0xff);

            pantalla.print("Dia.val=");
            pantalla.print(dia);
            pantalla.write(0xff);
            pantalla.write(0xff);
            pantalla.write(0xff);
   
   }
}



    /*
 
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
     */ 
       
