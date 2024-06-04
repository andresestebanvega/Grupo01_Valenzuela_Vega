#include <Arduino.h>
#include "libreria.h"

// Inicialización de objetos y variables
Servo myServo;                   // Crea un objeto Servo
DHT dht(DHT_PIN, DHT_TYPE);      // Inicializa el objeto DHT con el pin y tipo definidos
int pote = 0;
int gasValue = 0;                // Variable para almacenar la lectura del sensor MQ2                    // Variable para almacenar el valor discretizado del potenciómetro

void setup() {
    Serial.begin(9600);          // Inicia la comunicación serial a 9600 bps
    setupPins();                 // Configura los pines
    dht.begin();                 // Inicia la comunicación con el sensor DHT
}

void loop() {
    readPotentiometer();         // Lee el valor del potenciómetro
    readDHTSensor();             // Lee los valores del sensor DHT
    readPhotoresistor();         // Lee el valor del fotorresistor
    readMQ2Sensor();             // Lee el valor del sensor MQ2
    controlServo();              // Controla el servo motor basado en las lecturas de los sensores
    delay(2000);                 // Espera 2 segundos antes de la siguiente iteración del loop
}

void setupPins() {
    myServo.attach(SERVO_PIN);   // Asigna el pin del servo al objeto Servo
}

void readPotentiometer() {
    int potValue = analogRead(POT_PIN);       // Lee el valor analógico del potenciómetro
    pote = map(potValue, 0, 1023, 0, 36);     // Mapea el valor de 0-1023 a 0-36
    Serial.print("Potenciometro: ");          // Imprime el valor del potenciómetro en el monitor serial
    Serial.println(pote);
}

void readDHTSensor() {
    float h = dht.readHumidity();             // Lee la humedad del sensor DHT
    float t = dht.readTemperature();          // Lee la temperatura del sensor DHT

    // Verifica si alguna lectura falló y, de ser así, imprime un mensaje de error
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Error al leer del sensor DHT!"));
        return;
    }

    // Imprime las lecturas de humedad y temperatura en el monitor serial
    Serial.print(F("Humedad: "));
    Serial.print(h);
    Serial.print(F("%  Temperatura: "));
    Serial.print(t);
    Serial.println(F("°C "));
}

void readPhotoresistor() {
    int photoValue = analogRead(PHOTORESISTOR_PIN);    // Lee el valor analógico del fotorresistor
    Serial.print("Fotoresistor: ");                    // Imprime el valor del fotorresistor en el monitor serial
    Serial.println(photoValue);
}

void readMQ2Sensor() {
    gasValue = analogRead(MQ2_PIN);                    // Lee el valor analógico del sensor MQ2
    Serial.print("MQ2 Gas Sensor: ");                  // Imprime el valor del sensor MQ2 en el monitor serial
    Serial.println(gasValue);
}

void controlServo() {
    int photoValue = analogRead(PHOTORESISTOR_PIN);    // Lee el valor del fotorresistor
    float temperature = dht.readTemperature();         // Lee la temperatura del sensor DHT

    delay(1000);
    if (gasValue<430)
    {
      
        if ((photoValue < 300) && (temperature > pote)) {// mayor a 300 es de noche
            myServo.write(90);
                Serial.println("Temperatura > pote, Servo a 90 grados.");
                Serial.println("ESTA DE DIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                delay(1000);
        }
        else {
            myServo.write(0);
            Serial.println("cierro!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            delay(1000);
        }
        
    }
    else{
        myServo.write(90);
        Serial.println("hay GAAAAAAAAAAAAAAAAAAAAAASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
        delay(1000);
    }


 /*   delay(1000);

        // Independientemente de las condiciones de luz y temperatura, si se detecta gas
    if (gasValue > 511) {                              // Si la lectura del sensor de gas es mayor a la mitad del rango
        myServo.write(90);                             // Mueve el servo a 90 grados
        Serial.println("Detección de gas alta, Servo a 90 grados.");
    }
        else {
      myServo.write(0);
    }
    */
}
