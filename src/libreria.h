#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <Servo.h>
#include <DHT.h>

// Definiciones de pines
#define POT_PIN A2               // Pin del potenciómetro
#define DHT_PIN 2                // Pin del sensor DHT
#define DHT_TYPE DHT11           // Tipo de sensor DHT (DHT11 en este caso)
#define PHOTORESISTOR_PIN A1     // Pin del fotorresistor
#define SERVO_PIN A0              // Pin del servo motor
#define MQ2_PIN A7               // Pin del sensor MQ2

// Variables globales
extern Servo myServo;            // Objeto Servo global
extern DHT dht;                  // Objeto DHT global
extern int pote;                 // Variable global para el valor discretizado del potenciómetro

// Declaración de funciones
void setupPins();                // Configura los pines
void readPotentiometer();        // Lee el valor del potenciómetro
void readDHTSensor();            // Lee los valores del sensor DHT (temperatura y humedad)
void readPhotoresistor();        // Lee el valor del fotorresistor
void readMQ2Sensor();            // Lee el valor del sensor MQ2
void controlServo();             // Controla el servo motor basado en las lecturas de los sensores

#endif // LIBRERIA_H
