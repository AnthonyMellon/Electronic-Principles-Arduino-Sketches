const int ORANGETIME = 2000; //How long an orange light runs for in seconds

class trafficLight
{
    public:
        int RedLed;
        int OrngLed;
        int GrnLed;
        float onTime; //How long the light is green, in seconds

        void GreenLight()
        { 
            refresh();           
            digitalWrite(GrnLed, HIGH);
        }

        void RedLight()
        {
            //Run an orange light first
            refresh();
            digitalWrite(OrngLed, HIGH);
            delay(ORANGETIME);

            refresh();
            digitalWrite(RedLed, HIGH);
        }

        void setupPins()
        {
            pinMode(RedLed, OUTPUT);
            pinMode(OrngLed, OUTPUT);
            pinMode(GrnLed, OUTPUT);
        }

    private:
        void refresh()
        {
            digitalWrite(GrnLed, LOW);
            digitalWrite(OrngLed, LOW);
            digitalWrite(RedLed, LOW);
        }
};

bool day; //TRUE if day time, FALSE if night time

int daySwitch = 7; //Switch to control day/night
int secondarySwitch = 8; //Switch to activate secondary lights at night

trafficLight MainLight;
trafficLight SecondaryLight;

void setup()
{
    //Main Light Setup
    MainLight.RedLed = 1;
    MainLight.OrngLed = 2;
    MainLight.GrnLed = 3;
    MainLight.onTime = 5000;

    //Secondary Light Setup
    SecondaryLight.RedLed = 4;
    SecondaryLight.OrngLed = 5;
    SecondaryLight.RedLed = 6;
    SecondaryLight.onTime = 2500;

    //Pin setups
    pinMode(daySwitch, INPUT);
    pinMode(secondarySwitch, INPUT);
    MainLight.setupPins();
    SecondaryLight.setupPins();

    Serial.begin(9600);
}

void loop()
{
    day = digitalRead(daySwitch);

    if(day)
    {
        runLight(MainLight);
        runLight(SecondaryLight);
    }
    else
    {
      Serial.println("not day");
        if(digitalRead(secondarySwitch))
        {
            //Turn off the main light
            MainLight.RedLight();

            runLight(SecondaryLight);
        }
        MainLight.GreenLight();
    }
}

void runLight(trafficLight tLight)
{
    tLight.GreenLight();
    delay(tLight.onTime);

    tLight.RedLight();
}
