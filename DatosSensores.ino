void dataSensor(){
    wdt_reset();           //Funcion del perro guardian
    int valorLumex = Lumex.readLightLevel();  //Variable que almacena los datos arrojados por el sensor de luminosidad
    int t = dht.readTemperature();  //Variable que almacena los datos arrojados por el sensor de temperatura 
    int h = dht.readHumidity();     //Variable que almacena los datos arrojados por el sensor de humedad
    TempAqua.requestTemperatures(); //Funcion del sensor de temperatura del agua
    int valorTempAqua= TempAqua.getTempCByIndex(0);   //Variable que almacena los datos arrojados por el sensor de temperatura del agua
    
    HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
    segundo=HoraFecha.second();
    minuto=HoraFecha.minute();
    hora=HoraFecha.hour();
    dia=HoraFecha.day();
    mes=HoraFecha.month();
    anio=HoraFecha.year();
    diaDeLaSemana=HoraFecha.dayOfTheWeek();
    time = millis();

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
        pantalla.print(valorTempAqua);
        pantalla.write(0xff);
        pantalla.write(0xff);
        pantalla.write(0xff);
        

     //   Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
      //  Serial.print("                 Ambiente Sensor                           "); Serial.println("                      Aqua Sensor                          ");
       // Serial.print("___________________________________________________________  "); Serial.println("  ___________________________________________________________");
        
        Serial.print(hora);
        Serial.print(":");
        Serial.print(minuto);
        Serial.print(":");
        Serial.println(segundo);   

        Serial.print("Temperatura = "); Serial.print(t); Serial.print(" | "); 
        Serial.print("Humedad = "); Serial.print(h); Serial.print(" | ");  
        Serial.print("Luminosidad = "); Serial.print(valorLumex); Serial.print(" |  "); Serial.print("Temperatura del aqua = "); 
        Serial.print(valorTempAqua); Serial.print(" | "); 
        Serial.print("Nivel del agua = "); Serial.print(media);Serial.println(" cm");
        Serial.print("Estado de la Luz = "); Serial.println(EstadoLuz);

        

       





   
   }
}



