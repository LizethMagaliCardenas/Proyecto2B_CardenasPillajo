/*
 * MATRIZ DE CONFUSIÓN
 */
  #include <ListLib.h>
  #import "datosAlgoritmos.h"
  #import "datosPrueba.h"
  int fil=100;
  int col=3;
  
  int Vpositivo=0;
  int Vnegativo=0;
  int Fpositivo=0;
  int Fnegativo=0;
 
  List <int> list;
  
  void setup() {
    Serial.begin(9600);
  }
  
  void loop() {
    matriz_Confusion();
  }

  void matriz_Confusion() {

   for (int i = 0; i <= fil; i++) {
    for(int j=0;j<col;j++){
      
  if (matriz[i][j] == matrizkNN[i][j] &&  matriz[i][j] == 1) {
      Vpositivo++;
    }
  if (matriz[i][j] == matrizkNN[i][j] && matriz[i][j] == 2) {
      Vnegativo++;
    }
  if (matriz[i][j] ==matrizkNN[i][j] &&  matriz[i][j] == 3) {
    Vpositivo++;
    }
  if (matriz[i][j] == matrizkNN[i][2] && matriz[i][j] == 4) {
        Vnegativo++;
    }
      
    if (matriz[i][j] != matrizkNN[i][j] == 1) {
      Fnegativo++;
    }
    if (matriz[i][j] !=matrizkNN[i][j] == 2) {
      Fpositivo++;
    }
    if (matriz[i][j] != matrizkNN[i][j] == 3) {
      Fnegativo++;
    }
    if (matriz[i][j] != matrizkNN[i][j] == 4) {
       Fpositivo++;
    } 
  }
  }
  Serial.println("Algoritmo kNN");
  Serial.println(String(" Verdadero Positivo = ") + String(Vpositivo) + String("\n Verdadero Negativo = ") + String(Vnegativo) + String("\n Falso Positivo = ") + String(Fpositivo) + String("\n Falso negativo = ") + String(Fnegativo));
  Vpositivo=0;
  Vnegativo=0;
  Fpositivo=0;
  Fnegativo=0;
  delay(1000);
  
  for (int i = 0; i <= fil; i++) {
    for(int j=0;j<col;j++){
      
  if (matriz[i][j] == matrizBayes[i][j] &&  matriz[i][j] == 1) {
  Vpositivo++;
    }
  if (matriz[i][j] == matrizBayes[i][j] && matriz[i][j] == 2) {
    Vnegativo++;
    }
  if (matriz[i][j] == matrizBayes[i][j] &&  matriz[i][j] == 3) {
     Vpositivo++;
    }
   if (matriz[i][j] == matrizBayes[i][2] && matriz[i][j] == 4) {
        Vnegativo++;
    }
    
    if (matriz[i][j] != matrizBayes[i][j] == 1) {
       Fnegativo++;
    }
    if (matriz[i][j] != matrizBayes[i][j] == 2) {
     Fpositivo++;
    }
    if (matriz[i][j] != matrizBayes[i][j] == 3) {
       Fnegativo++;
    }
    if (matriz[i][j] != matrizBayes[i][j] == 4) {
       Fpositivo++;
    }
    
  }
  }
  Serial.println("Algoritmo de Bayes");
  Serial.println(String(" Verdadero Positivo = ") + String(Vpositivo) + String("\n Verdadero Negativo = ") + String(Vnegativo) + String("\n Falso Positivo = ") + String(Fpositivo) + String("\n Falso negativo = ") + String(Fnegativo));
  
  Vpositivo=0;
  Vnegativo=0;
  Fpositivo=0;
  Fnegativo=0;
  delay(1000);
  }
