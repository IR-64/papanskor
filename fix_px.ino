#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <Arial_Black_16_ISO_8859_1.h>
#include <Arial20.h>
#include <font20.h>


#define ACROSS 11
#define DOWN 1

char teamA[50] = "SMAN 1 Kraksaan";
char teamB[50] = "SMAN 1 Probolinggo";
int roundNumber = 1;

unsigned long startMillis;
unsigned long previousMillisTimer = 0;
int elapsedMinutes = 0;
int elapsedSeconds = 0;
bool isCounting = false;

unsigned long previousMillisGilir = 0;  // Waktu untuk pergantian
int gilirState = 0;  // Mulai dengan Team A
int gilirIntervalA_B = 2000;  // Interval untuk Team A dan Team B (2 detik)
int gilirIntervalVS = 1000;  
int posX_A = 161; // Posisi awal Team A
int posX_B = 161; // Posisi awal Team B

unsigned long previousMillisCountdown = 0;  // Variabel untuk melacak waktu sebelumnya pada countdown
bool isCountdownRunning = false;

int setA = 0;
int setB = 0;

int TA1 = 0;
int TA2 = 0;
int TB1 = 0;
int TB2 = 0;

int timeout = 0;

const int latchPin = A2;
const int dataPin = A0;
const int clockPin = A1;

const byte angka[10] = {129, 207, 146, 134, 204, 164, 160, 143, 128, 132}; 
byte buffer[8]; 

DMD dmd(ACROSS, DOWN);

void ScanDMD() {
    dmd.scanDisplayBySPI();
}

void setup() {
    Serial.begin(9600);
    Timer1.initialize(1500);
    Timer1.attachInterrupt(ScanDMD);

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

  buffer[0] = 255; 
  buffer[1] = 255; 
  buffer[2] = 255; 
  buffer[3] = 255; 
  buffer[4] = 255; 
  buffer[5] = 255; 
  buffer[6] = 255; 
  buffer[7] = 255;

    
  
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
}

void updateGilir() {
    unsigned long currentMillis = millis();
    unsigned long gilirInterval;

    if (gilirState == 0) {
        gilirInterval = gilirIntervalA_B;
    } else {
        gilirInterval = gilirIntervalVS;
    }

    if (currentMillis - previousMillisGilir >= gilirInterval) {
        previousMillisGilir = currentMillis;
        gilirState++;

        if (gilirState > 3) {
            dmd.clearScreen(true);
            gilirState = 0;
        }
    }
}


void displayGilir() {
    if (gilirState == 0) {
        displayPart31();  // Tampilkan Team A
    } else if (gilirState == 1) {
        displayPart33();  // Tampilkan "VS"
    } else if (gilirState == 2) {
        displayPart32();  // Tampilkan Team B
    }

}

void handleSerialInput() {
    String dataInput = Serial.readStringUntil('\n');
    dataInput.trim();

    if (dataInput.startsWith("start:")) {
        String startValue = dataInput.substring(6);
        if (startValue == "1") {
            isCounting = true;
            startMillis = millis();
            Serial.println("Timer started.");
        }
    } else if (dataInput.startsWith("pause:")) {
        String pauseValue = dataInput.substring(6);
        if (pauseValue == "1") {
            isCounting = false;
            Serial.println("Timer paused.");
        }
    } else if (dataInput.startsWith("reset:")) {
        elapsedMinutes = 0;
        elapsedSeconds = 0;
        isCounting = false; // Timer berhenti setelah di-reset
        Serial.println("Timer reset.");
    } else if (dataInput.startsWith("teamA:")) {
        String newTeamA = dataInput.substring(6);
        if (newTeamA.length() < sizeof(teamA)) {
            strcpy(teamA, newTeamA.c_str());
            dmd.clearScreen(true);
            Serial.println("Team A updated.");
        }
    } else if (dataInput.startsWith("teamB:")) {
        String newTeamB = dataInput.substring(6);
        if (newTeamB.length() < sizeof(teamB)) {
            strcpy(teamB, newTeamB.c_str());
            dmd.clearScreen(true);
            Serial.println("Team B updated.");
        }
    } else if (dataInput.startsWith("round:")) {
        String newRoundStr = dataInput.substring(6);
        roundNumber = newRoundStr.toInt();
        dmd.clearScreen(true);
        Serial.println("Round updated.");
    } else if (dataInput.startsWith("setA:")) {
        String newSetA = dataInput.substring(5);
        setA = newSetA.toInt();
        dmd.clearScreen(true);
        Serial.println("Set A updated.");
    } else if (dataInput.startsWith("setB:")) {
    String newSetB = dataInput.substring(5);
    setB = newSetB.toInt();  // Pastikan data masuk ke setB
    dmd.clearScreen(true);
    Serial.println("Set B updated: " + String(setB));


    }else if (dataInput.startsWith("menit:")) {
    String newelapseMinutes = dataInput.substring(6);  // Mengubah `elapsedMinutes`
    elapsedMinutes = newelapseMinutes.toInt();  // Update nilai menit
    dmd.clearScreen(true);
    Serial.println("Set menit.");
    }else if (dataInput.startsWith("detik:")) {
    String newelapseSeconds = dataInput.substring(6);  // Mengubah `elapsedSeconds`
    elapsedSeconds = newelapseSeconds.toInt();  // Update nilai detik
    dmd.clearScreen(true);
    Serial.println("Set detik.");
}
 else if (dataInput.startsWith("TA1:")) {
        String newTA1 = dataInput.substring(4);
        TA1 = newTA1.toInt();
        dmd.clearScreen(true);
        Serial.println("TA1 updated.");
    } else if (dataInput.startsWith("TA2:")) {
        String newTA2 = dataInput.substring(4);
        TA2 = newTA2.toInt();
        dmd.clearScreen(true);
        Serial.println("TA2 updated.");
    } else if (dataInput.startsWith("TB1:")) {
        String newTB1 = dataInput.substring(4);
        TB1 = newTB1.toInt();
        dmd.clearScreen(true);
        Serial.println("TB1 updated.");
    } else if (dataInput.startsWith("TB2:")) {
        String newTB2 = dataInput.substring(4);
        TB2 = newTB2.toInt();
        dmd.clearScreen(true);
        Serial.println("TB2 updated.");
    }else if (dataInput.startsWith("round:")) {
        String newRoundStr = dataInput.substring(6);
        roundNumber = newRoundStr.toInt();
        dmd.clearScreen(true);
        Serial.println("Round updated.");
    } else if (dataInput.startsWith("timeout:")) {
    String newTimeout = dataInput.substring(8);
    timeout = newTimeout.toInt();  // Update the timeout value
    Serial.print("Timeout updated: ");
    Serial.println(timeout);
    dmd.clearScreen(true);
    }else if (dataInput.startsWith("mulai:")) {
        String mulaiValue = dataInput.substring(6);
        if (mulaiValue == "1") {
            isCountdownRunning = true;
            Serial.println("Timer started.");
        }else if (dataInput.startsWith("round:")) {
        String newRoundStr = dataInput.substring(6);
        roundNumber = newRoundStr.toInt();
        dmd.clearScreen(true);
        Serial.println("Round updated.");
    }
}
}

void updateTimer() {
    if (isCounting) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillisTimer >= 1000) {
            previousMillisTimer = currentMillis;
            elapsedSeconds++;
            if (elapsedSeconds >= 60) {
                elapsedSeconds = 0;
                elapsedMinutes++;
            }
            Serial.print("Timer: ");
            Serial.print(elapsedMinutes);
            Serial.print(":");
            Serial.println(elapsedSeconds);
        }
    }
}

void updateCountdown() {
    if (isCountdownRunning && timeout > 0) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillisCountdown >= 1000) {
            previousMillisCountdown = currentMillis;
            timeout--;  // Mengurangi nilai timeout setiap detik
            Serial.print("Countdown: ");
            Serial.println(timeout);
        }
    } else if (timeout == 0) {
        isCountdownRunning = false;  // Hentikan countdown ketika mencapai 0
        Serial.println("Countdown ended.");
    }
}

void displayPart31() {
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
    dmd.drawString(posX_A, 0, teamA, strlen(teamA), GRAPHICS_NORMAL);
}

void displayPart32() {
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
    dmd.drawString(posX_B, 0, teamB, strlen(teamB), GRAPHICS_NORMAL);
}


void displayPart33() {
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
    dmd.drawString(161, 0, "          VS          ", 50, GRAPHICS_NORMAL);
}

void displayPart4() {
    char buffer[3];
    sprintf(buffer, "%d", roundNumber);
    dmd.selectFont(Arial20);
    dmd.drawString(140, 0, buffer, strlen(buffer), GRAPHICS_NORMAL);
}

void displayPart5() {
    char buffer[10];
    sprintf(buffer, "%02d:%02d", elapsedMinutes, elapsedSeconds);
    dmd.selectFont(font20);
    dmd.drawString(11, 0, buffer, strlen(buffer), GRAPHICS_NORMAL);
}

void displayPart6() {
    char buffer[4];
    sprintf(buffer, "%02d", timeout);
    dmd.selectFont(font20);
    dmd.drawString(88, 0, buffer, strlen(buffer), GRAPHICS_NORMAL);
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
}


void poin(){
  buffer[0] = angka[setB]; 

  buffer[1] = angka[TB1]; 
  buffer[2] = angka[TB2]; 
  buffer[3] = angka[0]; 

  
  buffer[4] = angka[TA1]; 
  buffer[5] = angka[TA2]; 
  buffer[6] = angka[0];

  buffer[7] = angka[setA]; 

  digitalWrite(latchPin, LOW);
  for (int i = 7; i >= 0; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, buffer[i]);
  }
  digitalWrite(latchPin, HIGH);

  delay(1000);
}


void loop() {
    if (Serial.available() > 0) {
        handleSerialInput();
    }

    if (isCounting) {
        updateTimer();
    }

       if (isCountdownRunning) {
        updateCountdown();
    }

    Serial.println(setB);

      updateGilir();
    displayGilir();
    displayPart4();
    displayPart5();
    displayPart6();
    poin();
}
