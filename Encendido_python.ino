void EncedidoPython(){

    if (Serial.available()) { //Si está disponible
    char D = Serial.read();
    
    if (D == 'F'){
        Serial.println("RGB Encendida Full");
        EstadoLuz = "Prendida";
        EEPROM.write(0, 1); 
        Tira1LucesFullSpectre();
        Tira2LucesFullSpectre();
        Tira3LucesFullSpectre();
        Tira4LucesFullSpectre();
       
    }
    if (D == 'R'){

        Serial.println("RGB Encendida Rojo ");
        EstadoLuz = "Prendida";
        EEPROM.write(0, 1);
        Tira1LucesRojo();
        Tira2LucesRojo();
        Tira3LucesRojo();
        Tira4LucesRojo();
    } 
    if (D == 'A'){

        Serial.println("RGB Encendida Azul");
        EstadoLuz = "Prendida";
        EEPROM.write(0, 1);
        Tira1LucesAzul();
        Tira2LucesAzul();
        Tira3LucesAzul();
        Tira4LucesAzul();
    } 
        if (D == 'O'){

        Serial.println("RGB Apagada");
        EstadoLuz = "Apagada";
        EEPROM.write(0, 0);
        Tira1LucesOff();
        Tira2LucesOff();
        Tira3LucesOff();
        Tira4LucesOff();
    } 
    }
}

    
