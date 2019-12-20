void EncedidoHoras(){

    
    if (HoraFecha.hour()==15 && HoraFecha.minute()== 24 && HoraFecha.second() == 00) //Prender
    {
        EstadoLuz = "Prendida";
        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        EEPROM.write(0, 1);

    }
    if (HoraFecha.hour()==17 && HoraFecha.minute()==00 && HoraFecha.second() == 00)//Apagar
    {
        EstadoLuz = "Apagada";
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        EEPROM.write(0, 0);
    }
    if (HoraFecha.hour()==18 && HoraFecha.minute()== 00 && HoraFecha.second() == 00)//Prender
    {
        EstadoLuz = "Prendida";
       // EstadoLuzMemoria = 1;

        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        EEPROM.write(0, 1);



    }
    if (HoraFecha.hour()==21 && HoraFecha.minute()==00 && HoraFecha.second() == 00)//Apagar
    {
        EstadoLuz = "Apagada";
       // EstadoLuzMemoria = 0;
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        EEPROM.write(0, 0);
    }
    if (HoraFecha.hour()==24 && HoraFecha.minute()== 00 && HoraFecha.second() == 00)//Prender
    {
        EstadoLuz = "Prendida";
       // EstadoLuzMemoria = 1;

        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        EEPROM.write(0, 1);



    }
    if (HoraFecha.hour()==05 && HoraFecha.minute()==00 && HoraFecha.second() == 00)//Apagar
    {
        EstadoLuz = "Apagada";
       // EstadoLuzMemoria = 0;
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        EEPROM.write(0, 0);
    }
    if (HoraFecha.hour()== 8 && HoraFecha.minute()== 00 && HoraFecha.second() == 00)//Prender
    {
        EstadoLuz = "Prendida";
       // EstadoLuzMemoria = 1;

        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
        EEPROM.write(0, 1);



    }
    if (HoraFecha.hour()==13 && HoraFecha.minute()==00 && HoraFecha.second() == 00)//Apagar
    {
        EstadoLuz = "Apagada";
       // EstadoLuzMemoria = 0;
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
        EEPROM.write(0, 0);
    }
    /*
    if (HoraFecha.hour()==24){
        ContadorHoras++; 
        Serial.print("Los dias completado son  ");
        Serial.println(ContadorHoras);

            pantalla.print("Total.val=");
            pantalla.print(ContadorHoras);
            pantalla.write(0xff);
            pantalla.write(0xff);
            pantalla.write(0xff);  
    }
*/
   // EEPROM.write(addr1,ContadorHoras);
   // EEPROM.write(addr2,EstadoLuzMemoria);
}