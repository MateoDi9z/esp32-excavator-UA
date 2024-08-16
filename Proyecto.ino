  #include <Servo.h>

  // Definición de los pines de los servos
  #define SERVO_BASE_PIN 6
  #define SERVO_BRAZO_1_PIN 10
  #define SERVO_BRAZO_2_PIN 11
  #define SERVO_PALA_PIN 3

  // Definiciones para la dirección del movimiento
  #define R true
  #define L false

  // Estructura para representar un servo con su ángulo
  struct ServoConAngle {
    Servo instance; // Objeto Servo para controlar el servo motor
    int angle;      // Ángulo actual del servo

    // Constructor para inicializar el ángulo
    ServoConAngle() {
      angle = 0;
      instance.write(0);
    }
  };

  // Estructura que contiene todos los servos
  struct Servos {
    ServoConAngle servo_base;
    ServoConAngle servo_brazo1;
    ServoConAngle servo_brazo2;
    ServoConAngle servo_pala;
  };

  // Instancia global de servos
  Servos globalServos;

  // Prototipos de funciones
  ServoConAngle* getServo(int servoPin);
  void moverServo(int servoPin, bool direction);

  // Función para obtener un puntero al servo específico
  ServoConAngle* getServo(int servoPin) {
    switch (servoPin) {
      case SERVO_BASE_PIN: return &globalServos.servo_base;
      case SERVO_BRAZO_1_PIN: return &globalServos.servo_brazo1;
      case SERVO_BRAZO_2_PIN: return &globalServos.servo_brazo2;
      case SERVO_PALA_PIN: return &globalServos.servo_pala;
      default: return nullptr; // Retorna nullptr si el pin no coincide
    }
  }

  ServoConAngle* servoEnMovimiento;
  int servoEnMovimientoPin = -1;

  // Función para mover un servo en una dirección específica
  void moverServo(int servoPin, bool direction) {
    if (servoEnMovimientoPin != servoPin) {
      servoEnMovimiento = getServo(servoPin);
      servoEnMovimientoPin = servoPin;
    }

    if (servoEnMovimiento == nullptr) return; // Verifica si el servo es válido

    if (direction == R) { // Movimiento hacia la derecha
      if (servoEnMovimiento->angle < 180) servoEnMovimiento->angle += 1;
    } else if (direction == L) { // Movimiento hacia la izquierda
      if (servoEnMovimiento->angle > 0) servoEnMovimiento->angle -= 1;
    }

    servoEnMovimiento->instance.write(servoEnMovimiento->angle); // Mueve el servo al ángulo deseado
    delay(30); // Espera para permitir el movimiento del servo
  }

  void setup() {
    // Adjuntar cada servo a su pin correspondiente
    globalServos.servo_base.instance.attach(SERVO_BASE_PIN);
    globalServos.servo_brazo1.instance.attach(SERVO_BRAZO_1_PIN);
    globalServos.servo_brazo2.instance.attach(SERVO_BRAZO_2_PIN);
    globalServos.servo_pala.instance.attach(SERVO_PALA_PIN);

    // Configurar el pin del botón como entrada con pull-up interno
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
  }

  void loop() {
    // Leer el estado del botón
    bool buttonR = digitalRead(12) == LOW; // Botón presionado
    bool buttonL = digitalRead(13) == LOW; // Botón presionado

    if (buttonR) {
      // Si el botón está presionado, mover el servo base a la derecha
      moverServo(SERVO_BASE_PIN, R);
    } else if (buttonL) {
      // Si el botón está presionado, mover el servo base a la izquierda
      moverServo(SERVO_BASE_PIN, L);
    }

    delay(10);
  }

  /**
  * Esta funcion deberia mover los 4 servos si esta todo
  * conectado correctamente.
  */
  void testServos() {
    // Mueve el servo base de 0 a 180 grados
    for (int i = 0; i <= 50; i++) {
      moverServo(SERVO_BASE_PIN, R); // Mueve a la derecha
    }
    
    // Mueve el servo base de 180 a 0 grados
    for (int j = 50; j >= 0; j--) {
      moverServo(SERVO_BASE_PIN, L); // Mueve a la izquierda
    }

    // Mueve el servo base de 0 a 180 grados
    for (int i = 0; i <= 50; i++) {
      moverServo(SERVO_BRAZO_1_PIN, R); // Mueve a la derecha
    }
    
    // Mueve el servo base de 180 a 0 grados
    for (int j = 50; j >= 0; j--) {
      moverServo(SERVO_BRAZO_1_PIN, L); // Mueve a la izquierda
    }

    // Mueve el servo base de 0 a 180 grados
    for (int i = 0; i <= 50; i++) {
      moverServo(SERVO_BRAZO_2_PIN, R); // Mueve a la derecha
    }
    
    // Mueve el servo base de 180 a 0 grados
    for (int j = 50; j >= 0; j--) {
      moverServo(SERVO_BRAZO_2_PIN, L); // Mueve a la izquierda
    }

    // Mueve el servo base de 0 a 180 grados
    for (int i = 0; i <= 50; i++) {
      moverServo(SERVO_PALA_PIN, R); // Mueve a la derecha
    }
    
    // Mueve el servo base de 180 a 0 grados
    for (int j = 50; j >= 0; j--) {
      moverServo(SERVO_PALA_PIN, L); // Mueve a la izquierda
    }
  }
