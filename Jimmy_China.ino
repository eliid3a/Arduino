/*******************
  By eliid3a@gmail.com
  23-04-2019  v.1.3
  Contador de Piezas buenas y malas, Maquina Jimmy
  Si hay una pieza mala ignora la pieza buena hasta que acompleta su ciclo
  A4 = SDA
  A5 = SCL
********************/
////////////////////////  screen OLED ////////////////////////////
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display


Adafruit_SSD1306 display;  // Create display


#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

/////////////////////////  screen OLED //////////////////////////

/*
//lcd//
#include <LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);   // original UNO  0x3F  OTRO  0x27
//lcd//
*/

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


//ESTADO ANTERIOR PIEZAS MALAS
int estado_ma = 0;
int estadoAnterior_ma = 1; //int estadoAnterior = 0;
int salida_ma = 0;

//CONTADOR DE PIEZAS MALAS
//const int led_13 = 13;
unsigned long contador_pz_ma = 0;  //int contador_pz = 0;
int estadoAnteriorBoton_ma = 1; //int estadoAnteriorBoton_ma = 0;
int valorBoton_ma = 0;


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

int S_ACTIVADOR = 10;
int LED_AC = 11;



void setup() {

  
  //Serial.begin(9600);   //Inicia comunicación serie
  pinMode(S_GIRO, INPUT_PULLUP);
  pinMode(LED_A, OUTPUT);
  pinMode(S_BUENAS, INPUT_PULLUP);
  pinMode(LED_AM, OUTPUT);
  pinMode(S_RECHAZO, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT);
  pinMode(S_ACTIVADOR, INPUT_PULLUP);
  pinMode(LED_AC, OUTPUT);

          /////////////////////////////////////  screen OLED //////////////////////////
  delay(100);  // This delay is needed to let the display to initialize delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C 
  display.clearDisplay();  // Clear the buffer
  display.setTextColor(WHITE);  // Set color of the text WHITE
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).
  display.dim(1);  //Set brightness (0 is maximun and 1 is a little dim)
  /////////////////////////////////////  screen OLED //////////////////////////
/*      //lcd//
  lcd.init();
  lcd.backlight();
  //lcd//
 */ 









        /////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
/*  // Print text:
  display.setCursor(0, 10);  // (x,y)
  display.println("Esperando...");  // Text or value to print
*/
/////////////////////////////////////  screen OLED //////////////////////////

 //LCD
  display.setCursor(0, 10);  // (x,y)
  display.println("Bienvenido...");
  //display.setCursor(90, 15);  // (x,y)
  //display.println(contador_pz_bu);
        //LCD
  display.setCursor(30, 35);  // (x,y)
  display.println("Maquina");
  display.setCursor(65, 60);  // (x,y)
  display.println("Jimmy");
  //display.setCursor(90, 40);  // (x,y)
  //display.println(contador_pz_ma);
  
  display.display();  // Print everything we set previously   

  //display.clearDisplay();  






 
}

void loop() {

 state_giro = digitalRead (S_GIRO); // Se mantiene un pulso cuando jira la mesa

    if (state_giro == LOW) { // Mientras este en movimiento la mesa y este en HIGH
    
        digitalWrite(LED_A, HIGH); // se activa led azul

    estado_ma = digitalRead(S_RECHAZO);  // Lee si hay una entrada en el sensor de pz malas

       /////////////CONTADOR PZ MALAS
       valorBoton_ma = digitalRead(S_RECHAZO);

              if (valorBoton_ma != estadoAnteriorBoton_ma) { //Si hay un cambio entra if
                 if (valorBoton_ma == 0) {  //if (valorBoton_ma == 1) {
                      contador_pz_ma++; //Aumentamos en una unidad la cuenta
                      //Serial.print("PIEZAS MALAS = ");
                      //Serial.println(contador_pz_ma);
                     //digitalWrite(led_13, HIGH);
                     oled();
                  }
                /*if (valorBoton == 0) {
                    digitalWrite(led_13, LOW);
                  }*/
            }
             estadoAnteriorBoton_ma = valorBoton_ma; //PIEZAS MALAS guardamos el estado actual del pulsador para la siguiente iteración
         /////////////////CONTADOR PZ MALAS
    

          if ((estado_ma == LOW) && (estadoAnterior_ma == HIGH)) { // if((estado == HIGH) && (estadoAnterior == LOW))
              salida_ma = 1 - salida_ma;
              delay(ANTIreb);
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
                  oled();
                  }
              if (valorBoton_ac == 1) { // if (valorBoton_bu == 0) {
                  digitalWrite(LED_AC, LOW);
                }
            }
            estadoAnteriorBoton_ac = valorBoton_ac; //PIEZAS BUENAS CONTADOR guardamos el estado actual del pulsador para la siguiente iteración

/////////////////////////////////////////////////


                   
          }





          
       
                
             else {  // Sino hay pieza mala, cuenta si hay pieza buena
              
                      digitalWrite(LED_R, LOW);  //apaga led rojo
                   //******* CONTADOR PZ BUENAS
                    valorBoton_bu = digitalRead(S_BUENAS);

              if (valorBoton_bu != estadoAnteriorBoton_bu) { //Si hay un cambio entra if
                  if (valorBoton_bu == 0) { //if (valorBoton_bu == 1) {
                  contador_pz_bu++; //Aumentamos en una unidad la cuenta
                  //Serial.print("BUENAS = ");
                  //Serial.println(contador_pz_bu);
                  digitalWrite(LED_AM, HIGH);
                  oled();
                  }
              if (valorBoton_bu == 1) { // if (valorBoton_bu == 0) {
                  digitalWrite(LED_AM, LOW);
                }
            }
            estadoAnteriorBoton_bu = valorBoton_bu; //PIEZAS BUENAS CONTADOR guardamos el estado actual del pulsador para la siguiente iteración
            
    } // Cierra ELSE- Sino hay pieza mala, cuenta si hay pieza buena 





                      
    
  } // Se cierra Primer IF
          else { // Mientras este en movimiento la mesa y este en HIGH   =    else
                salida_ma = 0;
                estado_ma = 0;
                estadoAnterior_ma = 0;
                digitalWrite(LED_A, LOW); //apaga led azul
          }

  //oled();
/*

        /////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0

/////////////////////////////////////  screen OLED //////////////////////////
  
        //LCD
  display.setCursor(0, 15);  // (x,y)
  display.println("Buenas:");
  display.setCursor(90, 15);  // (x,y)
  display.println(contador_pz_bu);
  display.setCursor(0, 40);  // (x,y)
  display.println("Malas:");
  display.setCursor(90, 40);  // (x,y)
  display.println(contador_pz);

  display.display();  // Print everything we set previously   

  //display.clearDisplay();  
/////////////////////////////////////  screen OLED //////////////////////////

*/
  
 // pantalla();

  
  //lcd

} //fin void loop

void oled_clear(){

   
}





void oled(){
        /////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
/*  // Print text:
  display.setCursor(0, 10);  // (x,y)
  display.println("Esperando...");  // Text or value to print
*/
/////////////////////////////////////  screen OLED //////////////////////////

 //LCD
  display.setCursor(0, 15);  // (x,y)
  display.println("Pz Ok:");
  display.setCursor(90, 15);  // (x,y)
  display.println(contador_pz_bu);
        //LCD
  display.setCursor(0, 40);  // (x,y)
  display.println("Malas:");
  display.setCursor(75, 40);  // (x,y)
  display.println(contador_pz_ma);

  display.setCursor(0,60);
  display.println("Acti:");
  display.setCursor(90,60);
  display.println(contador_pz_ac);
  
  display.display();  // Print everything we set previously   

  //display.clearDisplay();    
}



void oled_bu(){
      /////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
/*  // Print text:
  display.setCursor(0, 10);  // (x,y)
  display.println("Esperando...");  // Text or value to print
*/
/////////////////////////////////////  screen OLED //////////////////////////
  
        //LCD
  display.setCursor(0, 15);  // (x,y)
  display.println("Buenas:");
  display.setCursor(90, 15);  // (x,y)
  display.println(contador_pz_bu);
  display.display();  // Print everything we set previously   

  display.clearDisplay();  
/////////////////////////////////////  screen OLED //////////////////////////
}




void oled_ma(){
      /////////////////////////////////////  screen  OLED //////////////////////////
  display.clearDisplay();  // Clear the display so we can refresh
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0
/*  // Print text:
  display.setCursor(0, 10);  // (x,y)
  display.println("Esperando...");  // Text or value to print
*/
/////////////////////////////////////  screen OLED //////////////////////////
  
        //LCD
  display.setCursor(0, 40);  // (x,y)
  display.println("Malas:");
  display.setCursor(90, 40);  // (x,y)
  display.println(contador_pz_ma);
  display.display();  // Print everything we set previously   

  display.clearDisplay();  
/////////////////////////////////////  screen OLED //////////////////////////
}




/***
void pantalla(){
     //LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Buenas: ");
  lcd.print(contador_pz_bu); 
  //lcd.print(" pz"); 
  lcd.setCursor(0,1);
  lcd.print("Malas: ");
  lcd.print(contador_pz);
  //lcd.print(" pz");
  //lcd.clear();


  //delay(400);  //LCD

  
}
**/
