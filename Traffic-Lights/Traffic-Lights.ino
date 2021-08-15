class trafficLight
{
    public:
        int RedLed;
        int OrngLed;
        int GrnLed;
        float onTime;

        void TurnOn()
        {

            TurnOff();
        }

        void TurnOff()
        {

        }
};


void setup()
{
    trafficLight MainLight;
    MainLight.RedLed = 1;
    MainLight.OrngLed = 2;
    MainLight.GrnLed = 3;
}

void loop()
{

}