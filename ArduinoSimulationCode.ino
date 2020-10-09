/*
ECE3872 Project Software Assignment
Group 6B: Austin Pitts, Emily Buchanan, Matthew Liu, Pavan Bharadwaj
Fall 2020 Semester


*/

#include <Servo.h>
//Declare servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


//Switch Variables
bool isRecord = false;
bool isPlayLive = false;
bool isPlayRecording = false;
//Permission Variables
bool canRecord = false;
bool canPlayRecording = false;
bool canPlayLive = false;

//Pin Number Assignments
const int speakerPin = 3;
const int recordSwitch = 14;
const int playLiveSwitch = 15;
const int playRecordingSwitch = 16;
const int actionButton = 17;
const int resetButton = 18;
const int servo1Pin = 5;
const int servo2Pin = 6;
const int servo3Pin = 9;
const int servo4Pin = 10;
//Keypad Pin Assignments
const int pinA = 8;
const int pinB = 2;
const int pinC = 4;
const int pinD = 19;
const int pin1 = 11;
const int pin2 = 12;
const int pin3 = 13;
//Note Frequencies
const unsigned int A = 110;
const unsigned int B2 = 123;
const unsigned int C3 = 131;
const unsigned int D3 = 147;
const unsigned int E3 = 165;
const unsigned int F3 = 175;
const unsigned int G3 = 196;
const unsigned int Gsharp3 = 208;

//Keypad Matrix
const int rowPins[]={pinA,pinB,pinC};
const int columnPins[]={pin1,pin2,pin3};
const int keyPadNotes[3][3]= {{A,B2,C3},{D3,E3,F3},{G3,Gsharp3,A}};
int keyPadInput[3][3]={{0,0,0},{0,0,0},{0,0,0}};



//Prerecorded Note Array
int RecordingLength = 40;
int Recording[] = {A,B2,C3,D3,E3,F3,G3,Gsharp3,G3,F3,E3,D3,C3,B2,A,B2,C3,D3,E3,F3,G3,Gsharp3,G3,F3,E3,D3,C3,B2,A,B2,C3,D3,E3,F3,G3,Gsharp3,G3,F3,E3,D3};
//Unique Servo positions for different notes in order from A-Gsharp3
int servo1Pos[] = {45,90,-45,-90,45,90,-45,-90};
int servo2Pos[] = {90,-45,-90,45,-90,45,90,-45};
int servo3Pos[] = {-45,-90,45,90,90,-45,-90,45};
int servo4Pos[] = {-90,45,90,-45,-45,-90,45,90};

//Array that the notes input is stored in.  Initialized to all zeros in setup.
int inputRecording[40];
//Function that reads keypad input and returns note
int readKeypad(){

  for(int i = 0;i<3;i++){
    for(int j=0;j<3;j++){
      keyPadInput[i][j] = 0;
      }
    }

int rowInput=0;
int colInput=0;

  for(int i = 0;i<3;i++){
    digitalWrite(rowPins[i],HIGH);
    for(int j=0;j<3;j++){
       keyPadInput[i][j] = digitalRead(columnPins[j]);
    }
    digitalWrite(rowPins[i],LOW);
  }

  for(int row = 0;row<3;row++){
    for(int col = 0;col<3;col++){
      if(keyPadInput[row][col] == 1){
        rowInput = row;
        colInput = col;
        break;
        }
      else{}
      
      }
    }

  return keyPadNotes[rowInput][colInput];
    
  }
//Takes a note as input and sets servos to unique positions based on the note
void driveServos(int note){
  switch(note){
    case A:
    servo1.write(servo1Pos[0]);
    servo2.write(servo2Pos[0]);
    servo3.write(servo3Pos[0]);
    servo4.write(servo4Pos[0]);
    break;
    case B2:
    servo1.write(servo1Pos[1]);
    servo2.write(servo2Pos[1]);
    servo3.write(servo3Pos[1]);
    servo4.write(servo4Pos[1]);
    break;
    case C3:
    servo1.write(servo1Pos[2]);
    servo2.write(servo2Pos[2]);
    servo3.write(servo3Pos[2]);
    servo4.write(servo4Pos[2]);
    break;
    case D3:
    servo1.write(servo1Pos[3]);
    servo2.write(servo2Pos[3]);
    servo3.write(servo3Pos[3]);
    servo4.write(servo4Pos[3]);
    break;
    case E3:
    servo1.write(servo1Pos[4]);
    servo2.write(servo2Pos[4]);
    servo3.write(servo3Pos[4]);
    servo4.write(servo4Pos[4]);
    break;
    case F3:
    servo1.write(servo1Pos[5]);
    servo2.write(servo2Pos[5]);
    servo3.write(servo3Pos[5]);
    servo4.write(servo4Pos[5]);
    break;
    case G3:
    servo1.write(servo1Pos[6]);
    servo2.write(servo2Pos[6]);
    servo3.write(servo3Pos[6]);
    servo4.write(servo4Pos[6]);
    break;
    case Gsharp3:
    servo1.write(servo1Pos[7]);
    servo2.write(servo2Pos[7]);
    servo3.write(servo3Pos[7]);
    servo4.write(servo4Pos[7]);
    break;
    }
  }

//Takes an array pointer as input and instructs the arduino to play the notes and call driveServos() to set motor positions
void playRecordedNotes(int *sequence,int Length){

  for(int i = 0; i<(Length); i++){
    checkInputs();
    if(!isPlayRecording){
      break;
      }
    if (checkButton(resetButton)) {
      resetPermissions();
      break;}
    else{
      if(sequence[i] != 0){
      tone(speakerPin,sequence[i]);
      driveServos(sequence[i]);
      delay(500);
      noTone(speakerPin);
      delay(50);}
      else if(sequence[i] == 0){
        break;
        }
        }
      }
    }

//Function that updates the current state of rotary switch
void checkInputs() {
  isRecord = digitalRead(recordSwitch);
  isPlayLive = digitalRead(playLiveSwitch);
  isPlayRecording = digitalRead(playRecordingSwitch);
}

/*
  Resets permission variables in order to only allow transitions to states that are available from the idle state.

*/
void resetPermissions() {
  canRecord = false;
  canPlayRecording = false;
  canPlayLive = false;
}

//returns boolean value to indicate whether a button has been pressed.
bool checkButton(int button) {
  return digitalRead(button);
}

/*
 * Idle state that indicates the rotary switch is set to Record mode
 * State machine can only transition to Record mode once it has passed through readyToRecord
 * and canRecord has been set to true
 */
void readyToRecord() {
  while (isRecord) {
    digitalWrite(7,HIGH);
    checkInputs();
    resetPermissions();
    canRecord = true;
    if (checkButton(actionButton)) {
      break;
    }
    if (checkButton(resetButton)) {
      resetPermissions();
      break;
    }
  }
  digitalWrite(7,LOW);
}

/*
 * Idle state that indicates the rotary switch is set to Play Recording mode
 * State machine must pass through this state before it can play the recording
*/
void readyToPlayRecording() {
  while (isPlayRecording) {
    checkInputs();
    resetPermissions();
    canPlayRecording = true;
    if (checkButton(actionButton)) {
      break;
    }
    if (checkButton(resetButton)) {
      resetPermissions();
      break;
    }
  }
}

/*
 * Idle state that indicates the rotary switch is set to the Play Live mode
 * State machine must pass through this state before it can play Live
 */

void readyToPlayLive() {
  while (isPlayLive) {
    
    checkInputs();
    resetPermissions();
    canPlayLive = true;
    if (checkButton(actionButton)) {
      break;
    }
    if (checkButton(resetButton)) {
      resetPermissions();
      break;
    }
  }
}

/*
 * State that executes the necessary functions to play a recorded sequence of notes
 */

void playRecording() {

  while (canPlayRecording && isPlayRecording) {

    checkInputs();
    playRecordedNotes(inputRecording,RecordingLength);
    if (checkButton(resetButton)) {
      resetPermissions();
      break;
    }
  }
}
/*
 * State that plays notes in real time in response to user input
 */
void playLive() {
  while (canPlayLive && isPlayLive) {

    checkInputs();
    if (checkButton(resetButton)) {
      resetPermissions();
      break;
    }
    int note = readKeypad();
    tone(speakerPin,note);
    driveServos(note);
    delay(50);
    noTone(speakerPin);
    delay(10);
  }
}

/*
 * State that records user input and stores the sequence of notes in memory
 */

void record() {
  while (canRecord && isRecord) {
    int startingIndex = 0;
    bool isFull = false;
    checkInputs();
    if (checkButton(resetButton)) {
      resetPermissions();
      break;}

    for(int i=0;i<RecordingLength;i++){
      if(inputRecording[i] == 0){
        startingIndex = i;
        isFull = false;
        break;
        }
        isFull = true;
      }
      if(isFull){
        readyToRecord();
        }
      

    if(!isFull){
      for(int i=startingIndex; i<RecordingLength;i++){
        checkInputs();
        if (checkButton(resetButton)) {
          resetPermissions();
          break;
          }
        int note = readKeypad();
        inputRecording[i] = note;
        tone(speakerPin,note);
        delay(500);
        noTone(speakerPin);
        delay(10);
        startingIndex = i;
      }
    }
  }
}

//State that checks for a 3 second reset button press and deletes recording
void EraseLoop(){
  int counter = 0;
  while(checkButton(resetButton)){
    delay(500);
    counter++;
    if(counter == 6){
      for (int i =0;i<RecordingLength;i++){
        inputRecording[i] = 0;
        }
        break;
      }
    
    }
  
  }

//Setup runs once and sets proper pin modes
void setup() {
  //Input Switches and buttons
  for (int i = 14; i <= 18; i++) {
    pinMode(i, INPUT);
  }
  //Speaker and Servo pin modes
  pinMode(speakerPin,OUTPUT);
  pinMode(servo1Pin,OUTPUT);
  pinMode(servo2Pin,OUTPUT);
  pinMode(servo3Pin,OUTPUT);
  pinMode(servo4Pin,OUTPUT);
  //Keypad Pin modes
  pinMode(pinA,OUTPUT);
  pinMode(pinB,OUTPUT);
  pinMode(pinC,OUTPUT);
  pinMode(pinD,OUTPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  pinMode(7,OUTPUT);

  //Initialize Switches
  isRecord = false;
  isPlayLive = false;
  isPlayRecording = false;
  //Initialize Permission Variables
  canRecord = false;
  canPlayRecording = false;
  canPlayLive = false;
  
//Attach Servo Motor Objects to pins
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

//Set input recording array to empty (all zeros)
for(int i = 0;i<RecordingLength;i++){
  inputRecording[i] = 0;
  }

}



//Main loop that allows transitions between the states

void loop() {

  checkInputs();
  EraseLoop();
  readyToRecord();
  record();
  readyToPlayRecording();
  playRecording();
  readyToPlayLive();
  playLive();

}






/*// Generated by Proteus Visual Designer for Arduino

  // Peripheral Configuration Code (Do Not Edit)
  //---CONFIG_BEGIN---
  #pragma GCC push_options
  #pragma GCC optimize ("Os")

  #include <core.h> // Required by cpu
  #include <cpu.h>
  #include <TimerOne.h>
  #include <spi.h> // Required by SD1
  #include <WaveStore.h>
  #include <Generic.h>
  #include <WavePlayer.h>

  #pragma GCC pop_options

  // Peripheral Constructors
  CPU &cpu = Cpu;
  TimerOne &timer1 = Timer1;
  GenericSwitch SW1 = GenericSwitch (14);
  GenericButton BTN1 = GenericButton (17);
  GenericSwitch SW2 = GenericSwitch (15);
  GenericSwitch SW3 = GenericSwitch (16);
  GenericButton BTN2 = GenericButton (18);
  WavePlayer &AUDIO1 = WP;
  WaveStore &SD1 = WS;

  void peripheral_setup () {
  AUDIO1.begin (2, 3, 4, 5);
  SD1.begin (10);
  }

  void peripheral_loop() {
  }
  //---CONFIG_END---

  // Flowchart Variables
  bool var_Record;
  bool var_playLive;
  bool var_playRecording;
  bool var_canRecord;
  bool var_canPlayRecording;
  bool var_canPlayLive;
  String var_fileName;

  // Flowchart Routines
  void chart_SETUP() {
  var_Record=false,var_playLive=false,var_playRecording=false,var_canRecord=false,var_canPlayLive=false,var_canPlayRecording=false;

  }

  void chart_LOOP() {
  chart_CheckInputs();
  chart_ReadyToRecord();
  chart_Record();
  chart_ReadyToPlayRecording();
  chart_PlayRecording();
  chart_ReadyToPlayLive();
  chart_PlayLive();
  }

  void chart_ReadyToRecord() {
  while (var_Record) {
  chart_CheckInputs();
  chart_ResetPermissions();
  var_canRecord=true;
  if (!(!BTN1())) goto l10;
  if (!(!BTN2())) goto l9;
  }
  l9:;
  chart_ResetPermissions();
  l10:;
  }

  void chart_CheckInputs() {
  var_Record=SW1(),var_playLive=SW2(),var_playRecording=SW3();
  }

  void chart_ReadyToPlayRecording() {
  while (var_playRecording) {
  chart_CheckInputs();
  chart_ResetPermissions();
  var_canPlayRecording=true;
  if (!(!BTN1())) goto l10;
  if (!(!BTN2())) goto l9;
  }
  l9:;
  chart_ResetPermissions();
  l10:;
  }

  void chart_ResetPermissions() {
  var_canRecord=false,var_canPlayRecording=false,var_canPlayLive=false;
  }

  void chart_ReadyToPlayLive() {
  while (var_playLive) {
  chart_CheckInputs();
  chart_ResetPermissions();
  var_canPlayLive=true;
  if (!(!BTN1())) goto l10;
  if (!(!BTN2())) goto l9;
  }
  l9:;
  chart_ResetPermissions();
  l10:;
  }

  void chart_PlayRecording() {
  while (var_canPlayRecording&&var_playRecording) {
  chart_CheckInputs();
  AUDIO1.play("DO.WAV",true);
  delay(100);
  }
  }

  void chart_Record() {
  while (var_Record&&var_canRecord) {
  chart_CheckInputs();
  }
  }

  void chart_PlayLive() {
  while (var_playLive&&var_canPlayLive) {
  chart_CheckInputs();
  AUDIO1.play("RE.WAV",true);
  delay(100);
  }
  }

  // Entry Points and Interrupt Handlers
  void setup () { peripheral_setup();  chart_SETUP(); }
  void loop () { peripheral_loop();  chart_LOOP(); }*/
