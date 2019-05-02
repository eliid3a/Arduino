/*******************
  By eliid3a@gmail.com
  23-04-2019  v.2.1
  Contador de Piezas buenas, malas y activadores en caja, Maquina Jimmy
  Si hay una pieza mala ignora el conteo de pieza buena y cuenta la pieza mala y activador si cae en caja, despues acompleta su ciclo
  -Pantalla
  A4 = SDA
  A5 = SCL
********************/
////////////////////////  Libreria para pantalla OLED ////////////////////////////
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
Adafruit_SSD1306 display;  // Create display
#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font
////////////////////////  Libreria para pantalla OLED ////////////////////////////

//GIRO DE ENCODER
const int S_GIRO =  2;  //REVISA SI LA MESA ESTA GIRANDO
const int LED_A = 3;
int state_giro = 0;  //int state_3 = 0;


//INPUT SENSOR PIEZAS MALAS
const int S_RECHAZO = 4; //INPUT Sensor de rechazo
const int LED_R = 5;
const int ANTIreb = 10;


//INPUT SENSOR PIEZAS BUENAS
const int S_BUENAS = 6;  //INPUT Sensor de piezas buenas
const int LED_AM = 7;
int state_buenas = 0;  //int state_1 = 0;
int LED_AC = 8; // led de ACTIVADORES MALOS


//ESTADO ANTERIOR PIEZAS MALAS
int estado_ma = 0;
int estadoAnterior_ma = 1; //int estadoAnterior = 0;
int salida_ma = 0;

//CONTADOR DE PIEZAS MALAS
//const int led_13 = 13;
unsigned long contador_pz_ma = 0;  //int contador_pz = 0;
//int estadoAnteriorBoton_ma = 1; //int estadoAnteriorBoton_ma = 0;
//int valorBoton_ma = 0;


//CONTADOR DE PIEZAS BUENAS
//const int led_24 = 12;
unsigned long contador_pz_bu = 0; //int contador_pz_bu = 0;
int estadoAnteriorBoton_bu = 0; //int estadoAnteriorBoton_bu = 0;
int valorBoton_bu = 0;


//CONTADOR DE PIEZAS ACTIVADOR
//const int led_24 = 12;
unsigned long contador_pz_ac = 0; //int contador_pz_bu = 0;
int estadoAnteriorBoton_ac = 0; //int estadoAnteriorBoton_bu = 0;
int valorBoton_ac = 0;



int prueba_bbb =0;
int salida_mama = 0;
int pru= 0 ;
bool prub= 0 ;


void setup() {  
  Serial.begin(9600);   //Inicia comunicación serie
  pinMode(S_GIRO, INPUT_PULLUP);
  pinMode(LED_A, OUTPUT);
  pinMode(S_BUENAS, INPUT_PULLUP);
  pinMode(LED_AM, OUTPUT);
  pinMode(S_RECHAZO, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_AC, OUTPUT);
//////////////////////// pantalla OLED ////////////////////////////
  delay(100);  // This delay is needed to let the display to initialize delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C 
  display.clearDisplay();  // Clear the buffer
  display.setTextColor(WHITE);  // Set color of the text WHITE
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                              //false = las lineas siguen y no salen    true = las lineas continuan
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).
  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)
//////////////////////// pantalla OLED ////////////////////////////
  inicio_oled();
}




void loop() {

 state_giro = digitalRead (S_GIRO); // Se mantiene un pulso cuando jira la mesa

    if (state_giro == HIGH) { // Mientras este en movimiento la mesa y este en HIGH
      
      digitalWrite(LED_A, HIGH); // se activa LED AZUL mesa girando
      rechazo();   
    }
        else  { // Mientras este en movimiento la mesa y este en HIGH   =    else
                salida_ma = 0;
                estado_ma = 0;
                estadoAnterior_ma = 0;                
                digitalWrite(LED_A, LOW); //apaga led azul
                oled();
                Serial.println("imprime");
                Serial.println(contador_pz_bu);                               
      }     
} //fin void loop




void rechazo(){

  estado_ma = digitalRead(S_RECHAZO);  // Lee si hay una entrada en el sensor de pz malas

          if ((estado_ma == LOW) && (estadoAnterior_ma == HIGH)) { // if((estado == HIGH) && (estadoAnterior == LOW))
              salida_ma = 1 - salida_ma;
              contador_pz_ma++; //contador de pz malas              
              delay(ANTIreb);
              //oled(); //imprime en pantalla
          }
            estadoAnterior_ma = estado_ma; 

          if (salida_ma == 1) {
            digitalWrite(LED_R, HIGH); //hay pieza mala  
            //************************ CONTADOR PZ ACTIVADOR
              valorBoton_ac = digitalRead(S_BUENAS);

              if (valorBoton_ac != estadoAnteriorBoton_ac) { //Si hay un cambio entra if
                  if (valorBoton_ac == 0) { //if (valorBoton_bu == 1) {
                  contador_pz_ac++; //Aumentamos en una unidad la cuenta
                  //Serial.print("BUENAS = ");
                  //Serial.println(contador_pz_bu);
                  digitalWrite(LED_AC, HIGH);
                  //oled();
                  }
              if (valorBoton_ac == 1) { // if (valorBoton_bu == 0) {
                  digitalWrite(LED_AC, LOW);
                }
            }
            estadoAnteriorBoton_ac = valorBoton_ac; //PIEZAS ACTIVADOR
                  
          }
            else {
              digitalWrite(LED_R, LOW);  //apaga led rojo
              buenas();
            }
}


void buenas(){
  // Sino hay pieza mala, cuenta si hay pieza buena             

    valorBoton_bu = digitalRead(S_BUENAS);

      if (valorBoton_bu != estadoAnteriorBoton_bu) { //Si hay un cambio entra if
                  if (valorBoton_bu == 0) { //if (valorBoton_bu == 1) {
                  contador_pz_bu++; //Aumentamos en una unidad la cuenta
                  digitalWrite(LED_AM, HIGH);
                  //oled();
                  }
              if (valorBoton_bu == 1) { // if (valorBoton_bu == 0) {
                  digitalWrite(LED_AM, LOW);
              }
       }
            estadoAnteriorBoton_bu = valorBoton_bu; //PIEZAS BUENAS CONTADOR
  
}


void oled(){
/*////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
/////////////////////////////////////  screen OLED /////////////////////////
*/ 
  display.setCursor(0, 10);  // (x,y)
  display.println("Pz Ok:");
  display.setCursor(70, 10);  // (x,y)
  display.println(contador_pz_bu);
        //LCD
  display.setCursor(0, 35);  // (x,y)
  display.println("Malas:");
  display.setCursor(70, 35);  // (x,y)
  display.println(contador_pz_ma);

  display.setCursor(0,60);
  display.println("Activ:");
  display.setCursor(70,60);
  display.println(contador_pz_ac);  
  display.display();  // Print everything we set previously   
  display.clearDisplay();    
}
 
void inicio_oled(){
  ////////////////// SE INICIA PANTALLA PARA MOSTRAR TEXTO //////////////////////////////////
  //display.clearDisplay();  // Borrar la pantalla para que podamos actualizar
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // El tamaño debe ser 0

  display.setCursor(0, 10);  // (x,y)
  display.println("Bienvenido...");

  display.setCursor(30, 35);  // (x,y)
  display.println("Maquina");
  
  display.setCursor(70, 60);  // (x,y)
  display.println("Jimmy");
  
  display.display();  // Imprime todo lo que configuramos previamente
  display.clearDisplay();  // Borrar la pantalla para que podamos actualizar 
}
