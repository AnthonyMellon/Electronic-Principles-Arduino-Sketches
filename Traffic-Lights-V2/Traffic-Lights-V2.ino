const int ORANGETIME = 2500; //How long an orange light is help for (in milliseconds)
const int BUTTONGRACE = 250; //Grace period to let go of button (in milliseconds)

class trafficLight
{
    public:
        int redLED;   
        int orngLED;
        int grnLED;
        int onTime; //How long a green light is held for (in milliseconds)

        void off() //Switch all LEDs off
        {
            digitalWrite(redLED, LOW);
            digitalWrite(orngLED, LOW);
            digitalWrite(grnLED, LOW);
        }

        void GreenLight()
        {
            off();
            digitalWrite(grnLED, HIGH);
        }

        void OrangeLight()
        {
            off();
            digitalWrite(orngLED, HIGH);
        }

        void RedLight()
        {
            off();
            digitalWrite(redLED, HIGH);
        }

        void setup(int RLED, int OLED, int GLED, int time)
        {
            onTime = time; 

            grnLED = GLED;
            orngLED = OLED;
            redLED = RLED;           

            pinMode(grnLED, OUTPUT);
            pinMode(orngLED, OUTPUT);
            pinMode(redLED, OUTPUT);
        }
};

enum time
{
    day,
    night
};

trafficLight mainLights;
trafficLight secondaryLights;

time timeOfDay = day; //Is it day time?
bool secondaryCross = 0; //are the secondary lights allowed to cross (only used at night time)

int dayButton = 7;
int secondaryButton = 8;

void mainLightsGreen()
{
    secondaryLights.RedLight();
    mainLights.GreenLight();
    delay(mainLights.onTime);
}

void mainLightsOrange()
{
    mainLights.OrangeLight();
    delay(ORANGETIME);
}

void secondaryLightsGreen()
{
    mainLights.RedLight();
    secondaryLights.GreenLight();
    delay(secondaryLights.onTime);
}

void secondaryLightsOrange()
{
    secondaryLights.OrangeLight();
    delay(ORANGETIME);
}

void daySequence()
{
    Serial.println("Day Sequence");
    
    mainLightsGreen();
    mainLightsOrange();

    secondaryLightsGreen();
    secondaryLightsOrange();
    
    mainLightsGreen();
}

void nightSequence()
{
    Serial.println("Night Sequence");

    //Check to allow secondary crossing
    secondaryCross = !digitalRead(secondaryButton);

    //Secondary Lights right of way
    if(secondaryCross)
    {
        //Main lights orange
        mainLights.OrangeLight();
        delay(ORANGETIME);

        //Secondary lights green
        mainLights.RedLight();
        secondaryLights.GreenLight();
        delay(secondaryLights.onTime);

        while(secondaryCross)
        {
            secondaryCross = !digitalRead(secondaryButton);
        }

        //Seconday lights orange
        secondaryLights.OrangeLight();
        delay(ORANGETIME);

        //Main lights green
        secondaryLights.RedLight();
        mainLights.GreenLight();
        delay(mainLights.onTime);
    }    
}

void setup()
{
    mainLights.setup(9, 2, 3, 2500);
    secondaryLights.setup(4, 5, 6, 2500);

    pinMode(dayButton, INPUT);
    pinMode(secondaryButton, INPUT);
    
    Serial.begin(9600);
}

void loop()
{
    //Set the time of day
    if (digitalRead(dayButton))
    {
        timeOfDay = day;
        delay(BUTTONGRACE);
    }   
    else
    {
        timeOfDay = night;
    }

    //Act on weather its day or night time
    if(timeOfDay == day)
    {
        daySequence();
    }
    else if (timeOfDay == night)
    {
        nightSequence();
    }
}
