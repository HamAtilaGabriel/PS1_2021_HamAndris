#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 #define btnRIGHT 0
 #define btnUP 1
 #define btnDOWN 2
 #define btnLEFT 3
 #define btnSELECT 4
 #define btnNONE 5
 #define btnUNKNOWN 6
 int volatile a;
int readkeypad(){
      int adc_key_in = analogRead(0); //
      int ret = btnUNKNOWN;

      if (adc_key_in < 50) ret = btnRIGHT;
      if ((adc_key_in > 500) && (adc_key_in < 1150)) ret = btnNONE;
      if ( (adc_key_in > 120) && (adc_key_in < 150) ) ret = btnUP;
      if ( (adc_key_in > 250) && (adc_key_in < 350) ) ret = btnDOWN;
      if ( (adc_key_in > 450) && (adc_key_in < 500) ) ret = btnLEFT;
      if ( (adc_key_in > 700) && (adc_key_in < 750) ) ret = btnSELECT;

      return ret;
 }
int volatile temp_q;
void setup() {
      lcd.begin(16, 2);
      adc_init();  
      sei();
      //OCR1A = 62500;

 /*TCCR1B |= (1 << WGM12) | (1 << CS12);
 TIMSK1 |= (1 << OCIE1A);*/    
 }
void adc_init(){
  ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));//set division factor between
//system clock frequency and the input clock to the ADC- 128
ADMUX |= (1<<REFS0);//AVcc with external capacitor at Aref pin
ADCSRA |= (1<<ADEN);//enable ADC

//ADCSRA|= 1<<ADIE;
ADCSRA |= (1<<ADSC);//ADC
}
uint16_t read_adc(uint8_t channel)
{

ADMUX &= 0xF0;//set input AO to A5
ADMUX |= channel;//select chanel AO to A5
ADCSRA |= (1<<ADSC);//start conversion
while(ADCSRA & (1<<ADSC));//wait wile adc conversion are not updated
return ADCL;//read and return voltage
}
float read_temp()//read and return temperature
{
float voltage=0;
float Temperature=0;
float temperatureCelsius=0; int reading;
reading=read_adc(1);
voltage=reading*5.0; voltage/=1024.0;
temperatureCelsius=(voltage-0.5)*100;
ADCSRA|=1<<ADSC;
return temperatureCelsius;
}

ISR(ADC_vect)
{ 
  ADCSRA|=1<<ADSC;
  
}
void loop() {     
      
       lcd.setCursor(0,0);
       lcd.print(read_temp());
       
       
       
      
}
