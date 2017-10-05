/**********************ETUDE 2 CART 360 2017*******************************
 * 
 * Michelle Samson
 * 27037600
 * CART 360
 * Etude Two
 * 
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK. 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)
 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 5 // R PIN
#define LED_PIN_G 9 // G PIN
#define LED_PIN_B 6 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration =200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 
int mode = 0; // start at off

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  Serial.begin(9600);    //
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
  // IMPLEMENT
  
  boolean buttonState = false;      //declare local boolean variables for this function only
  boolean prevButtonState = true;       //boolean variable for previous button state

   if (digitalRead(BUTTON_MODE_PIN) == HIGH)
  {
    delay(200);   //process time for arduino board to delay time
    if (buttonState != prevButtonState) {

     buttonState = !buttonState;    //flip the current button state
     
      prevButtonState = buttonState;      //this will assign value of the button state in the previous button state
    }
  } else {
    prevButtonState = !buttonState;   //assign opposite states of button
  }

 if (buttonState) {
    if (mode < 4) {
               
      mode++;         //increment mode
    } else {
      
      mode = 0;       //reset the mode
    }
  }
  Serial.println(mode);
    
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  //IMPLEMENT
  switch (mode) {
    case 0:
    {
      //light off 
      analogWrite(LED_PIN_R, LOW);
      analogWrite(LED_PIN_G, LOW);
      analogWrite(LED_PIN_B, LOW);
    }break;
      
    case 1:
     {
      //blue light
      analogWrite(LED_PIN_R, LOW);
      analogWrite(LED_PIN_G, LOW);
      analogWrite(LED_PIN_B, HIGH);
      }
       break;

    case 2:
      {
       //red light 
       analogWrite(LED_PIN_R, HIGH);
      analogWrite(LED_PIN_G, LOW);
      analogWrite(LED_PIN_B, LOW);
      }
      break;   
    
    case 3:
      {
        //green light
        analogWrite(LED_PIN_R, LOW);
        analogWrite(LED_PIN_G, HIGH);
        analogWrite(LED_PIN_B, LOW);
      }
      break;

    case 4:
    {
      //red light purple light does not work
      analogWrite(LED_PIN_R, HIGH);
      analogWrite(LED_PIN_G, LOW);
      analogWrite(LED_PIN_B, HIGH);
    }
    break;
    
    }  
  }
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode ==0) { 
    reset();
  }
  else if(mode ==1) {
    live();
  }
  else if(mode ==2) {
    record();
  }
  
  else if(mode ==3) {
    play();
  }
   
   else if(mode ==4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // IMPLEMENT

  //to shut off any tone playing
  noTone(BUZZER_PIN);

  //for loop to cycle through the notes array and assign 0s in every element
  for(int i = 0; i < MAX_NOTES; i++) {

    //assign 0 for each increment
    notes[i] = 0;
    
  }

  //reset the countNotes
  countNotes = 0;
  
}

/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
    //IMPLEMENT
    //use tone function to play the sounds from the buttons
    tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);
    
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // IMPLEMENT

  //instantiate initial button state
  boolean buttonState = false;

  //implement previous button state
  boolean prevButtonState = true;

  //need to store the analog values and convert them into frequency
  int frequencyConv = analogRead(NOTE_IN_PIN);

  //play tone that is triggered by user by using the tone function
  tone(BUZZER_PIN, frequencyConv, duration);

  //check if the frequency exceeds 0
  if(frequencyConv > 0){

    //delay loop processing to insure proper input is displayed
    delay(duration);

    //also check for button state is equal to previous state to avoid a dupe
    if(buttonState != prevButtonState)  {

      //flip the value of the button state
      buttonState = !buttonState;

      //assign button state value to previous button state value
      prevButtonState = buttonState;
    } 
  
  } else {

      //assign opposite value button state to prev state
      prevButtonState = !buttonState;
    }

    //check the true or false value of the button state
    if(buttonState) {

      //also check the counter of notes is less than max notes or else the world crashes
      if(countNotes < MAX_NOTES){

        //assign value of the frequency into an array input
        notes[countNotes] = frequencyConv;

        //increment countNotes to continue the process
        countNotes++;
      }
    }
  }

/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // IMPLEMENT
  //need to ensure the countnotes is less than max notes to allow iteration of notes in the array
  if(countNotes < MAX_NOTES) {

    //delay the processing
    delay(duration);

    //play the tones from the frequency specs in the array box depending on their position in countNotes
    tone(BUZZER_PIN, notes[countNotes]); 

    //increment
    countNotes++;
    
  } else { 

    //reset counter of notes
    countNotes = 0;
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode() 
{
  //IMPLEMENT
  //delay process to ensure correct input and output is displayed
  delay(duration);

  //generate random order of integers which ranges from 0 to 15 inclusively
  int randomNum = random(0, MAX_NOTES);

  //play the tones randomly
  tone(BUZZER_PIN, notes[randomNum]);
}

/**************************************************************************/

/*analysis of the etude's setup
 * 
 * The resistors throughout the breadboard are in series, while the resistors set up for the push buttons
 * are positioned as parallel resistors.  this parallel setup allows the tone frequency to circulate and to 
 * provide different sound tones.  
 * There are 5V of power circulating through the arduino board and the breadboard, which provides a slower processing  
 * time for the code to be circulated and to send an output.  
 * The input becomes audible via the analogRead function which detects the push buttons input and converts them into 
 * output and their frequency gets tranfered into a tonal sound.
 * Pushing the buttons activates the resistor's ohms and provides frequency.
 * With the different mode selector, the user is able to access the resistors of the buttons to allow various recordings and functions to occur.
 */


