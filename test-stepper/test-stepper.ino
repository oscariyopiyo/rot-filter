#include <AccelStepper.h>

// Configuración de los pines del CNC Shield para el eje X
#define STEP_PIN 2   // Pin de STEP del eje X en el CNC Shield
#define DIR_PIN 9    // Pin de DIR del eje X en el CNC Shield
#define ENABLE_PIN 10 // Pin de ENABLE en el CNC Shield (controla todos los motores)

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
int step_value = 0;  // Valor de pasos recibido por serial

void setup() {
  Serial.begin(9600);  // Inicializa la comunicación serial a 9600 baudios
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);  // Habilita los motores

  stepper.setMaxSpeed(200);    // Velocidad máxima en pasos por segundo
  stepper.setAcceleration(2000); // Aceleración en pasos por segundo al cuadrado

  Serial.println("Ingrese la cantidad de pasos:");  // Mensaje de inicio
}

void loop() {
  if (Serial.available() > 0) {  // Si hay datos disponibles en el puerto serial
    step_value = Serial.parseInt();  // Lee un valor entero desde el serial
    delay(10);
    if (step_value != 0) {  // Verifica que el valor no sea cero
      Serial.print("Moviendo motor a: ");
      Serial.println(step_value);
      digitalWrite(ENABLE_PIN, LOW);
      stepper.moveTo(step_value);  // Mueve el motor a la posición recibida
      stepper.runToPosition();  // Ejecuta el movimiento hasta la posición
      digitalWrite(ENABLE_PIN, HIGH);
    }

    // Envía un nuevo mensaje para pedir más pasos
    Serial.println("Ingrese la cantidad de pasos:");
  }
}
