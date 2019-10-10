void botones (){


 time = millis();  
               //Funcion del tiempo en millis
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

              
//------------- ENCEDIDO DE LUCES ESPECIFICADO EL COLOR EN EL PRIMER NIVEL DE LUCES RGB --------------------------------

      case 8:                   //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color full Spectre
        contadorTira1FullSpectre++;
          switch (contadorTira1FullSpectre)
            {
            case 1:
              Serial.println("boton luces fullSpectre Activado");
              Tira1LucesFullSpectre();
                break;


            case 2:             
              
              contadorTira1FullSpectre = 0;
              Serial.println("boton luces fullSpectre desactivado");
              Tira1LucesOff();
              break;
            }
              break;

      case 9:                   //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color Rojo 
        contadorTira1Rojo++;
          switch (contadorTira1Rojo)
            {
            case 1:
              Serial.println("boton luces Rojo activado");
                Tira1LucesRojo();
                break;


            case 2:
              
              contadorTira1Rojo = 0;
              Serial.println("boton luces Rojo desactivado");
              Tira1LucesOff();
              break;
            }
              break;

      case 10:                  //Condicional para evalular si el nivel 1 esta encendido y si se encendio el color Azul
        contadorTira1Azul++;
          switch (contadorTira1Azul)
            {
            case 1:
              Serial.println("boton luces Azul activado");
              Tira1LucesAzul();
                  
                break;


            case 2:
              
              contadorTira1Azul = 0;
              Serial.println("Luz nivel 1 Azul Apagada");
              Tira1LucesOff();
                break;

            }
                break;

      case 11:                   //Condicional para evalular si el nivel 2 esta encendido y si se encendio el color full Spectre
        contadorTira2FullSpectre++;
          switch (contadorTira2FullSpectre)
            {
            case 1:
              Serial.println("boton luces fullSpectre nivel 2 Activado");
              Tira2LucesFullSpectre();
                break;


            case 2:             
              
              contadorTira2FullSpectre = 0;
              Serial.println("boton luces fullSpectre nivel 2 desactivado");
              Tira2LucesOff();
              break;
            }
              break;

      case 12:                   //Condicional para evalular si el nivel 2 esta encendido y si se encendio el color Rojo 
        contadorTira2Rojo++;
          switch (contadorTira2Rojo)
            {
            case 1:
              Serial.println("boton luces Rojo nivel 2 activado");
              Tira2LucesRojo();
                break;


            case 2:
              
              contadorTira2Rojo = 0;
              Serial.println("boton luces Rojo nivel 2 desactivado");
              Tira2LucesOff();
              break;
            }
              break;

      case 13:                  //Condicional para evalular si el nivel 2 esta encendido y si se encendio el color Azul
        contadorTira2Azul++;
          switch (contadorTira2Azul)
            {
            case 1:
              Serial.println("boton luces Azul nivel 2 activado");
              Tira2LucesAzul();
                  
                break;


            case 2:
              
              contadorTira2Azul = 0;
              Serial.println("Boton luces Azul nivel 2 Apagada");
              Tira2LucesOff();
                break;

            }
                break;

       case 14:                   //Condicional para evalular si el nivel 3 esta encendido y si se encendio el color full Spectre
        contadorTira3FullSpectre++;
          switch (contadorTira3FullSpectre)
            {
            case 1:
              Serial.println("boton luces fullSpectre nivel 3 Activado");
              Tira3LucesFullSpectre();
                break;


            case 2:             
              
              contadorTira3FullSpectre = 0;
              Serial.println("boton luces fullSpectre nivel 3 desactivado");
              Tira3LucesOff();
              break;
            }
              break;

       case 15:                   //Condicional para evalular si el nivel 3 esta encendido y si se encendio el color Rojo 
        contadorTira3Rojo++;
          switch (contadorTira3Rojo)
            {
            case 1:
              Serial.println("boton luces Rojo nivel 3 activado");
              Tira3LucesRojo();
                break;


            case 2:
              
              contadorTira3Rojo = 0;
              Serial.println("boton luces Rojo nivel 3 desactivado");
              Tira3LucesOff();
              break;
            }
              break;

        case 16:                  //Condicional para evalular si el nivel 3 esta encendido y si se encendio el color Azul
        contadorTira3Azul++;
          switch (contadorTira3Azul)
            {
            case 1:
              Serial.println("boton luces Azul nivel 23 activado");
              Tira3LucesAzul();
                  
                break;


            case 2:
              
              contadorTira3Azul = 0;
              Serial.println("Boton luces Azul nivel 3 Apagada");
              Tira3LucesOff();
                break;

            }
                break;
  }
}