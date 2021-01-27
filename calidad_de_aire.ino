/*
 *                             UNIVERSIDAD TÉCNICA DEL NORTE               
 *                                        CITEL                               
 *                                  SISTEMAS EMBEBIDOS                    
 *                               PROYECTO CALIDAD DEL AIRE       
 *               
 * Las pruebas se reaizo en el interior y exterior de una vivienda del estudiante.
 * 
 * Cada etiqueta contiene datos CO ppm/ CO2 ppm
 * LA EVALUACION DE DATOS DE ENTRADA SE REALIZO CON KNN DEBIDO A LA BUENA EFICIENCIA DE PREDICCION 
 */
 //variables para toma de datos
#include "datosPrueba.h"
#include<avr/wdt.h>
#include<MsTimer2.h>
float datos_entrada [3] = {23.1,6.64,3}; //Datos usados para realizar pruebas
int dato;
int on;
int valor;
float limite;
float mq135;
String datos;
String resp;
int aire=4;//LEDS INDICADORES 
int diox=5;
int butano=6;
int monox=7;

void(* resetFunc)(void)=0;//para haer un reset sin un perro guardian 

void setup() {
  wdt_disable();
  Serial.begin(9600); // Inicializamos comunicación serie.
  
  pinMode(2,INPUT); //entrada digital MQ7
  pinMode(3,INPUT); //entrada digital MQ135
  pinMode(aire,OUTPUT); //leds indicadores
  pinMode(diox,OUTPUT);
  pinMode(butano,OUTPUT);
  pinMode(monox,OUTPUT);
  //Serial.println("CONDICIONES DEL AIRE");
  //delay(50);
  
  wdt_enable(WDTO_4S);
}

void loop() {
  wdt_reset();
  on=knn(100,3,3,3);
   //MQ7***********************/
   limite=analogRead(A0);
   valor=digitalRead(2);
   float CO = limite/1024*100; //medicion porcentaje
   //datos+=","+String(CO); //pm10
   
     //MQ135*******************/
   mq135=analogRead(A1);
   float CO2 =(mq135/1024*100)-2; //medicion porcentaje
   //datos+=","+String(CO2); //pm2.5
   /****Interpretacion de datos en LEDS indicadores ******/
    if(CO2>0 && CO2<55){ //aire normal
    digitalWrite(aire,HIGH);
    digitalWrite(diox,LOW);
    digitalWrite(butano,LOW);  
    delay(100);  
    }else if(CO2>56 && CO2<150){// aire con co2
    digitalWrite(aire,LOW);
    digitalWrite(diox,HIGH);
    digitalWrite(butano,LOW); 
    delay(100);  
      }else if(CO2>151 && CO2<399){//diox de carbono
    digitalWrite(aire,LOW);
    digitalWrite(diox,HIGH);
    digitalWrite(butano,LOW);
    delay(100);
          }else if(CO2>400){//presencia de gas propano butano 
    digitalWrite(aire,LOW);
    digitalWrite(diox,LOW);
    digitalWrite(butano,HIGH); 
    delay(100); 
          }else if(CO>400 && CO<800){//presencia de gas propano butano 
    digitalWrite(monox,HIGH);
          }
 
  datos = "";
  datos += CO;;
  datos += ",";
  datos += CO2;
Serial.println(datos);
 delay(1000);
}


//***********KNN****************************

int knn (int fil, int columna, int vecinos, int etiquetas) {
int col; //Para recorrer las columnas
int fila = 0; //Para recorrer las filas
float promedio = 0; //Para almacenar el promedio de las distancias
float distancia; //Para almacenar la raíz de la distancia
const int k = vecinos; //Número de vecinos
float dist_menores [2][k]; //Matriz para distancias y etiquetas. 
int i = 0; //Contador
int j = 0; //Contador

float aux; //Auxiliar para almacenar Distancia
float aux1; //Auxiliar para almacenar Etiqueta
int x=0;
float num_etiquetas [2][etiquetas];
float respuesta;  //imprimir la etiqueta ganadora
float mayor=0;

for (; i < k; i++) { //Primero almacena valores de las distancias altas
    dist_menores[0][i] = 4000 + i;//Escoger un valor alto para entrar a la condición
    dist_menores[1][i] = 0; // Valor para cualquier etiqueta
  }
  i=0; //Reseteo de la variable para volver a ser usada
  for(;i<etiquetas;i++) {
    num_etiquetas[0][i]=i+1;   
     num_etiquetas[1][i]=0;   
  }
  i=0;//reseteo de la variable 
for (; fila < fil; fila++) { //Para recorrer todas las filas de la matriz
    for (col = 0; col < columna-1; col++) { //Para recorrer las columnas de la matriz
      promedio = promedio + (pow(datos_entrada[col] - matriz[fila][col], 2)); //Fórmula para Potencia.  
    }
    distancia = sqrt(promedio); //Fórmula para la raíz del promedio 
    promedio = 0; //Reinicio de la variable para la siguiente lectura
    
    if (distancia < dist_menores[0][k - 1]) { //Inicio de comparación. Valor de k de los vecinos
      dist_menores[0][k - 1] = distancia; //Almacena la distancia después de ser comparada
      dist_menores[1][k - 1] = matriz[fila][columna-1]; //Almacena la etiqueta
    }  

    //Para ordenar las distancias de menor a mayor
    for (; i < k; i++) { //Para recorrer las filas
      for (j = i + 1; j < k; j++) { //Para recorrer las columnas
        if (num_etiquetas[0][i] > dist_menores[0][j]) { //Compara las distancias de dos en dos siempre
          aux = dist_menores[0][i]; //Primero ordena la fila de la distancia
          dist_menores[0][i] = dist_menores[0][j];
          dist_menores[0][j] = aux;

          // etiquetas
          aux1 = dist_menores[1][i]; //Para ordenar la fila de las etiquetas
          dist_menores[1][i] = dist_menores[1][j];
          dist_menores[1][j] = aux1;
        }
      }
    }  
  }
  //Determinar el número de cada etiqueta
  for(i=0;i<etiquetas;i++){
    for(j=0;j<k;j++) {
      if(num_etiquetas[0][i]==dist_menores[1][j]) {
        num_etiquetas[1][i]=1+num_etiquetas[1][i];
      }
    }
  }
 for(;x<etiquetas;x++) {
  if(num_etiquetas[1][x]>mayor){
    mayor=num_etiquetas[1][x];
    respuesta=num_etiquetas[0][x];
   
   // Serial.println(String("La etiqueta es:")+ String(respuesta)); 
  //datos += respuesta;
  }
 }
  return respuesta;
 }
 
