// C++ code
//
int pot;
float y;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
 pot=analogRead(A0); //lectura analógica
 y=map(pot,0,1023,0,500); //función map para escalamiento
 y=y/100; //arreglo para generar decimales
  analogWrute(3,pot);
 Serial.print(pot); //primera variable a mostrar
 Serial.print("\t"); //genera un tab, con el separamos el print
 Serial.println(y); //segunda variable a mostrar y nueva línea
 delay(250); //delay para evitar lecturas erróneas
}