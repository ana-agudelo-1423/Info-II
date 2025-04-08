int sumaDivisores(int num) {
  int suma = 0;
  for (int i = 1; i <= num / 2; i++) {
    if (num % i == 0) {
      suma += i;
    }
  }
  return suma;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ingrese un número:");
}

void loop() {
  if (Serial.available() > 0) {
    int limite = Serial.parseInt();
    int sumaAmigables = 0;

    for (int a = 2; a < limite; a++) {
      int b = sumaDivisores(a);
      if (b != a && b < limite) {
        if (sumaDivisores(b) == a && a < b) {
          sumaAmigables += a + b;
          Serial.print("Par amigable: ");
          Serial.print(a);
          Serial.print(" y ");
          Serial.println(b);
        }
      }
    }

    Serial.print("El resultado de la suma es: ");
    Serial.println(sumaAmigables);
    Serial.println("Ingrese otro número:");
  }
}