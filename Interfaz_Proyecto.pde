import controlP5.*;
import processing.serial.*;
import meter.*;
Serial puerto;
ControlP5 cp5;//constructor 
PImage fondo1;
PFont f,aut; //fuente
int i=0;
float valores[] = {0,0};
float valor1=0;
float valor2=0;
float valor3; //prediccion
String dato;
Meter m;
int value;
int medida;

void setup(){
background(255);
size(1000, 700);

//*************fondo*******************
fondo1=loadImage("fondo1.jpg");
fondo1.resize(1000, 700);
image(fondo1,0,0);

//***********************medidor ************************
m=new Meter(this,15,475);
m.setFrameThickness(10);
m.setMeterWidth(300);
m.setTitle("Estado del ambiente Puro/Contaminado");
String[] scaleLabels = {"1","A. fresco","P. conta","2","P. conta","A. Conta","3"};
m.setScaleLabels(scaleLabels);
m.setTitleFontSize(15);
m.setTitleFontName("Times new Roman bold");
m.setDisplayDigitalMeterValue(true);
 
//**********texto titulo***************

f = createFont("Impact",26,true);
textFont(f,30);
fill(222,53,42);
text("SISTEMA DE CALIDAD DEL AIRE",350,60);

//*************autores*********************
aut=createFont("Garamond bold",35,true);
textFont(aut,24);
fill(0);
text("Autores: Gustavo Pillajo",25,105);
text("Lizeth Cardenas",115,125);
textFont(aut,44);
fill(0,45,246);
text("CITEL",100,200);

//*****************Botones****************
cp5 = new ControlP5(this);
  cp5.addButton("CONECTAR")
    .setPosition(450, 200)//posicion
    .setSize(100, 50) //tamaño
    .setCaptionLabel("DESCONECTADO")// cambiar el nombre del boton
    .setColorBackground(color(200, 0, 0))
    ;
//*****************indicadores********************
  cp5.addSlider("CO")
    .setPosition(290, 275)//elegir posicion
    .setSize(400, 45) //elegir tamaño
    .setRange(0, 100) //pm10
    .setValue(0)
    .setColorActive(color(255, 70, 51))
    .setColorBackground(color(33, 232, 2))
    .setColorForeground(color(144, 62, 80)) 
    ;
  cp5.addSlider("NOX")
    .setPosition(290, 350)//elegir posicion
    .setSize(400, 45) //elegir tamaño
    .setRange(0, 100) //pm2.5
    .setValue(0)
    .setColorActive(color(255, 221, 51 ))
    .setColorBackground(color(56, 119, 245))
    .setColorForeground(color(200, 106, 107)) 
    ;
}
void draw(){
  m.updateMeter(int(valor1)+10 );
  
  interpretacion();
  
  if(i==1){
  leer();
 }
}
public void CONECTAR() { //conectar al arduino
  i=1-i;
  if (i==1) {
    puerto= new Serial(this, "COM3", 9600);
    cp5.getController("CONECTAR").setCaptionLabel("CONECTADO");
    cp5.getController("CONECTAR").setColorBackground(color(0, 200, 0));//boton activado
    cp5.getController("NOX").setValue(0);
    cp5.getController("CO").setValue(0);
 


  } else {
    puerto.stop();
    cp5.getController("CONECTAR").setCaptionLabel("DESCONECTADO");
    cp5.getController("CONECTAR").setColorBackground(color(200, 0, 0));
  }
  //i++;
}
void leer(){
if(puerto.available()>0){
String trama=puerto.readStringUntil('\n');
if (trama != null){
  trama=trim(trama);
   valores= float (split(trama,','));
    valor1=valores[0];
     println(valor1);
    valor2=valores[1];
    println(valor2);

    //*********CO*************

    cp5.getController("CO").setValue(valor1);
    if(valor1>0 && valor1<100){
      cp5.getController("CO").setColorForeground(color(255,39,0));}
    //***********NOX*************
    cp5.getController("NOX").setValue(valor2);
    if(valor2>0 && valor2<100){
      cp5.getController("NOX").setColorForeground(color(119,92,25));}
 
  }
}
}
//***********color y advertencia del medido***********
void interpretacion(){
 
   m.setLowSensorWarningActive(false);
  m.setLowSensorWarningValue((float)1.0);
  m.setHighSensorWarningActive(true);
  m.setHighSensorWarningValue((float)4.0);

}
