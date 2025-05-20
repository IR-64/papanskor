#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <font9.h>

// Konfigurasi panel secara keseluruhan
#define ACROSS 1
#define DOWN 11

// Inisialisasi DMD untuk seluruh panel
DMD dmd(ACROSS, DOWN);

char FA1[12] ="04";
char FA2[12] = "05";
char FA3[12] = "06";
char FA4[12] = "07";
char FA5[12] = "08";
char FA6[12] = "09";
char FA7[12] = "10";
char FA8[12] = "11";
char FA9[12] = "12";
char FA10[12] = "13";
char FA11[12] = "14";
char FA12[12] = "15";

char Ap1[12]=  "" ;
char Ap2[12]=  "" ;
char Ap3[12]=  "" ;
char Ap4[12]=  "" ;
char Ap5[12]=  "" ;
char Ap6[12]=  "" ;
char Ap7[12]=  ""  ;
char Ap8[12]=  "" ;
char Ap9[12]=  "" ;
char Ap10[12] = "" ;
char Ap11[12] = "" ;
char Ap12[12] = "" ;


void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  // Setup DMD
  delay(1000);
  Serial.begin(9600);
  Timer1.initialize(1500);
  Timer1.attachInterrupt(ScanDMD);

  // Bersihkan layar

  // Pilih font untuk seluruh panel
  dmd.selectFont(font9);
}


void TimA1() {
  dmd.drawString(1, 1, FA1, strlen(FA1), GRAPHICS_NORMAL);
}

void TimA2() {
  dmd.drawString(1, 9, FA2, strlen(FA2), GRAPHICS_NORMAL);
}
void TimA3() {
  dmd.drawString(1, 17, FA3, strlen(FA3), GRAPHICS_NORMAL);
}
void TimA4() {
  dmd.drawString(1, 25, FA4, strlen(FA4), GRAPHICS_NORMAL);
}

void TimA5() {
  dmd.drawString(1, 33, FA5, strlen(FA5), GRAPHICS_NORMAL);
}

void TimA6() {
  dmd.drawString(1, 41, FA6, strlen(FA6), GRAPHICS_NORMAL);
}



void TimAp1() {
  dmd.drawString(12, 1, Ap1, strlen(Ap1), GRAPHICS_NORMAL);
}

void TimAp2() {
  dmd.drawString(12, 9, Ap2, strlen(Ap2), GRAPHICS_NORMAL);
}

void TimAp3() {
  dmd.drawString(12, 17, Ap3, strlen(Ap3), GRAPHICS_NORMAL);
}

void TimAp4() {
  dmd.drawString(12, 25, Ap4, strlen(Ap4), GRAPHICS_NORMAL);
}

void TimAp5() {
  dmd.drawString(12, 33, Ap5, strlen(Ap5), GRAPHICS_NORMAL);
}

void TimAp6() {
  dmd.drawString(12, 41, Ap6, strlen(Ap6), GRAPHICS_NORMAL);
}


void TimA13() {
  dmd.drawString(1, 97, FA7, strlen(FA7), GRAPHICS_NORMAL);
}

void TimA14() {
  dmd.drawString(1, 105, FA8, strlen(FA8), GRAPHICS_NORMAL);  
}

void TimA15() {
  dmd.drawString(1, 113, FA9, strlen(FA9), GRAPHICS_NORMAL);
}

void TimA16() {
  dmd.drawString(1, 121, FA10, strlen(FA10), GRAPHICS_NORMAL);
}

void TimA17() {
  dmd.drawString(1, 129, FA11, strlen(FA11), GRAPHICS_NORMAL);
}

void TimA18() {
  dmd.drawString(1, 137, FA12, strlen(FA12), GRAPHICS_NORMAL);
}


void TimAp13() {
  dmd.drawString(12, 97, Ap7, strlen(Ap7), GRAPHICS_NORMAL);
}

void TimAp14() {
  dmd.drawString(12, 105, Ap8, strlen(Ap8), GRAPHICS_NORMAL);
}

void TimAp15() {
  dmd.drawString(12, 113, Ap9, strlen(Ap9), GRAPHICS_NORMAL);
}

void TimAp16() {
  dmd.drawString(12, 121, Ap10, strlen(Ap10), GRAPHICS_NORMAL);
}

void TimAp17() {
  dmd.drawString(12, 129, Ap11, strlen(Ap11), GRAPHICS_NORMAL);
}

void TimAp18() {
  dmd.drawString(12, 137, Ap12, strlen(Ap12), GRAPHICS_NORMAL);
}


void loop() {
  // Bersihkan layar
  // dmd.clearScreen(true);

  if (Serial.available() > 0) {
    String receivedData = Serial.readString(); // Baca data yang diterima
    
    // Periksa dan update nilai-nilai FA berdasarkan data yang diterima
    if (receivedData.startsWith("FA1=")) {
      strcpy(FA1, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA2=")) {
      strcpy(FA2, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA3=")) {
      strcpy(FA3, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA4=")) {
      strcpy(FA4, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA5=")) {
      strcpy(FA5, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA6=")) {
      strcpy(FA6, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA7=")) {
      strcpy(FA7, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA8=")) {
      strcpy(FA8, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA9=")) {
      strcpy(FA9, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("FA10=")) {
      strcpy(FA10, receivedData.substring(5).c_str());
    } else if (receivedData.startsWith("FA11=")) {
      strcpy(FA11, receivedData.substring(5).c_str());
    } else if (receivedData.startsWith("FA12=")) {
      strcpy(FA12, receivedData.substring(5).c_str());
    } else if (receivedData.startsWith("AP1=")) {
      strcpy(Ap1, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP2=")) {
      strcpy(Ap2, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP3=")) {
      strcpy(Ap3, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP4=")) {
      strcpy(Ap4, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP5=")) {
      strcpy(Ap5, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP6=")) {
      strcpy(Ap6, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP7=")) {
      strcpy(Ap7, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP8=")) {
      strcpy(Ap8, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP9=")) {
      strcpy(Ap9, receivedData.substring(4).c_str());
    } else if (receivedData.startsWith("AP10=")) {
      strcpy(Ap10, receivedData.substring(5).c_str());
    } else if (receivedData.startsWith("AP11=")) {
      strcpy(Ap11, receivedData.substring(5).c_str());
    }else if (receivedData.startsWith("AP12=")) {
      strcpy(Ap12, receivedData.substring(5).c_str());
    }
    dmd.clearScreen(true);
  }

  // Nomor pemain // pelanggaran TIM A
  TimA1();  TimAp1();
  TimA2();  TimAp2();
  TimA3();  TimAp3();
  TimA4();  TimAp4();
  TimA5();  TimAp5();
  TimA6();  TimAp6();
  

  // Nomor pemain // pelanggaran TIM B
  TimA13();  TimAp13();
  TimA14();  TimAp14();
  TimA15();  TimAp15();
  TimA16();  TimAp16();
  TimA17();  TimAp17();
  TimA18();  TimAp18();
  
Serial.println(FA1);
Serial.println(Ap1);
}
