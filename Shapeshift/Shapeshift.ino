#define DAC 25
#define SELECT 12
#define POT 13
#define IN1 34
#define IN2 35

int select_var;
double vca_pot;
int osc_delay;
int lfo_value;
bool lfo_up;

void setup() {
  pinMode(DAC, OUTPUT);
}

void loop()
{
  select_var = analogRead(SELECT);
  if (select_var < 1024)
  {
    // VCO Mode
    /*
    osc_delay = 500000.0 / (130.8 * pow(2, analogRead(IN2) / 4096.0 * 3.3) + analogRead(POT) / 4.0 + analogRead(IN1) / 4.0);
    for (int i = 0; i < 32; i++){
      //dacWrite(DAC, 0);
      digitalWrite(DAC, LOW);
      delayMicroseconds(osc_delay);
      //dacWrite(DAC, 255);
      digitalWrite(DAC, HIGH);
      delayMicroseconds(osc_delay);
    }
    */
    osc_delay = 500000.0 / (130.8 * pow(2, analogRead(IN2) / 4096.0 * 3.3) + analogRead(POT) / 4.0 + analogRead(IN1) / 4.0);
    digitalWrite(DAC, LOW);
    delayMicroseconds(osc_delay);
    digitalWrite(DAC, HIGH);
    delayMicroseconds(osc_delay); 
  }
  else if (select_var < 2048)
  {
    // VCA Mode
    vca_pot = static_cast<double>(analogRead(POT));
    for (int i = 0; i < 10; i++)
    {
      dacWrite(DAC, static_cast<double>(analogRead(IN1) - 1489) * static_cast<double>(analogRead(IN2)) * vca_pot / 268435456.0 + 93);
    }
  }
  else if (select_var < 3072)
  {
    // LFO Mode
    dacWrite(DAC, lfo_value);
    if (lfo_value == 255) lfo_up = false;
    else if (lfo_value == 0) lfo_up = true;
    if (lfo_up) lfo_value ++;
    else lfo_value --;
    delayMicroseconds(pow(2, 5 + (analogRead(IN2) + analogRead(POT)) / 300.0));
  }
  else
  {
    // Noise Mode
    dacWrite(DAC, random(255));
    delayMicroseconds(pow(2, (1 + analogRead(POT)) / 200.0));
  }
}
