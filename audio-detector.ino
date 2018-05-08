
const long maxIdleMinutes = 1;
const int ON_TIMEOUT = 10000;
const int OFF_TIMEOUT = 1000;

int sampleSleepTime = OFF_TIMEOUT;


const int playingPin = 2;
const int playingPin2 = LED_BUILTIN; 


const int leftInput = A0;
const int rightInput = A1;

#define ANALOG_SAMPLES 20
const int analogThreashold = 2; // Less than this is noise
long lastPlayingTimestamp = 0;

bool IsMusicPlaying()
{
  int maxRead = 0;
  int samples[ANALOG_SAMPLES];
  int i;
  

  // Take samples on right channel
  for(i=0; i < (sizeof(samples)/sizeof(samples[0])); i++)
  {
    samples[i] = analogRead(leftInput);
    delay(2 * i);
  }
  for(i=0; i < (sizeof(samples)/sizeof(samples[0])); i++)
    if (samples[i] > maxRead)
      maxRead = samples[i];
  

  // Take samples on left channel
  for(i=0; i < (sizeof(samples)/sizeof(samples[0])); i++)
  {
    samples[i] = analogRead(leftInput);
    delay(2 * i);
  }
  for(i=0; i < (sizeof(samples)/sizeof(samples[0])); i++)
    if (samples[i] > maxRead)
      maxRead = samples[i];
  
  return (maxRead > analogThreashold);
}


void setup()
{
  
  pinMode(playingPin, OUTPUT);
  pinMode(playingPin2, OUTPUT);
  
}



void loop()
{
  if (IsMusicPlaying()) {
      digitalWrite(playingPin, HIGH); 
      digitalWrite(playingPin2, HIGH); 

      lastPlayingTimestamp = millis();
      sampleSleepTime = ON_TIMEOUT;
  } else {
      if (millis() - lastPlayingTimestamp > maxIdleMinutes * 1000 * 60) {
        digitalWrite(playingPin, LOW); 
        digitalWrite(playingPin2, LOW); 
        sampleSleepTime = OFF_TIMEOUT;
      }
  }
  delay(sampleSleepTime);
}
