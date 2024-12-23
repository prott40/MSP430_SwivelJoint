#include <msp430.h> 
#include <math.h>
void config_ADC_JOYSTICK()
{
    // Enable Pins
    // Horizontal: P9.2 --> A10 to Digital
    P9SEL1 |= BIT2;
    P9SEL0 |= BIT2;
    // Vertical: P8.7 --> A4 to Digital
    P8SEL1 |= BIT7;
    P8SEL0 |= BIT7;
    ADC12CTL0 |= ADC12ON; //ADC enable
    ADC12CTL0 &= ~ADC12ENC; //Turn-off ENC
    //Setup ADC12CTL0
    //ADC12SHT0: control the number of cycles
    ADC12CTL0 |= ADC12ON | ADC12SHT1_10;
    //Setup ADC12CTL1
    // ADC12SHS: configure ADC12SC bit as the trigger signal
    // ADC12SHP ADC12 Sample/Hold Pulse Mode
    // ADC12DIV ADC12 Clock Divider Select: 7
    // ADC12SSEL ADC12 Clock Source Select: 0
    ADC12CTL1 = ADC12SHS_0 | ADC12SHP | ADC12DIV_7 | ADC12SSEL_0;
    ADC12CTL1 |= ADC12CONSEQ_1;
    //Setup ADC12CTL2
    // ADC12RES: 12-bit resolution
    // ADC12DF: unsigned bin-format
    ADC12CTL2 |= ADC12ENC;
    //Setup ADC12MCTL0
    // ADC12VRSEL: VR+=AVCC, VR-=AVSS
    // ADC12INCH: Channel A10
    ADC12MCTL0 |= ADC12INCH_10 | ADC12VRSEL_0;
    // ADC12INCH: Channel A4
    ADC12MCTL1 |= ADC12INCH_4 | ADC12VRSEL_0 | ADC12EOS;
    ADC12CTL0 |= ADC12ENC; //Turn-on ENC at the end
    return;
}

#define Move  0;
#define FreezeX 1;
#define FreezeY 2;
#define FreezeAll 3;
volatile unsigned int state = Move;

volatile unsigned int stepv=0;
volatile double calcv = 0.00;
volatile unsigned int saveX=0;
volatile unsigned int saveY = 0;

void push1and2()
{
    P3DIR &= ~BIT1;
    P3REN |= BIT1;
    P3OUT |= BIT1;
    P3IES |= BIT1;
    P3IE |= BIT1;
    P3IFG &= ~BIT1;


   P3DIR &= ~BIT0;
    P3REN |= BIT0;
    P3OUT |= BIT0;
    P3IES |= BIT0;
    P3IE |= BIT0;
    P3IFG &= ~BIT0;


   }


/**
 * main.c
 */
const int maxpulse = 3000;

void pulsewidthmodulation() {

    TB0CTL |= TBCLR;          // Clears clock value
    TB0CTL |= TBSSEL__SMCLK;   // Sets clock to 1MHz
    TB0CTL |= MC__UP;          // Sets to a pullup

    //TB0CCR0 &= ~0x0000;
    TB0CCR0 = maxpulse;
    //TB0CCR1 &= ~0x0000;// sets the period time 655 or 20 ms
    TB0CCR1 = 0;           // sets the time active
    //TB0CCR2 &= 0xFFFF;
    TB0CCR2 = 0;

    TB0CCTL0 |= CCIE;// enables interrupt flags
    TB0CCTL1 |= CCIE;
    TB0CCTL2 |= CCIE;


    TB0CCTL0 &= ~CCIFG;// clears interrupt flag
    TB0CCTL1 &= ~CCIFG;
    TB0CCTL2 &= ~CCIFG;


    //__enable_interrupt(); //Enable maskable IRQs
}

int readx(int hor){
    if (hor > 2200)
    {
       hor = hor + 90;
       if(hor > 4061)
       {
          TB0CCR1 = (0);
          saveX = TB0CCR1;
       }
       else if(hor > 4000)
       {
           TB0CCR1 = (50);
           saveX = TB0CCR1;
       }
       else if(hor > 3939)
       {
        TB0CCR1 = (100);
         saveX = TB0CCR1;
          }
       else if(hor > 3878)
       {
          TB0CCR1 = (150);
          saveX = TB0CCR1;
       }
       else if(hor > 3817)
       {
         TB0CCR1 = (200);
         saveX = TB0CCR1;
       }
       else if(hor > 3756)
       {
         TB0CCR1 = (250);
         saveX = TB0CCR1;
       }
       else if(hor > 3695)
        {
          TB0CCR1 = (300);
          saveX = TB0CCR1;
        }
                                 else if(hor > 3634)
                                 {
                                  TB0CCR1 = (350);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3573)
                                 {
                                  TB0CCR1 = (400);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3512)
                                 {
                                  TB0CCR1 = (450);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3451)
                                 {
                                  TB0CCR1 = (500);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3390)
                                 {
                                  TB0CCR1 = (550);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3329)
                                 {
                                  TB0CCR1 = (600);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3268)
                                 {
                                  TB0CCR1 = (650);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3207)
                                 {
                                  TB0CCR1 = (700);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3146)
                                 {
                                  TB0CCR1 = (750);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3085)
                                 {
                                  TB0CCR1 = (800);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 3024)
                                 {
                                  TB0CCR1 = (850);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2963)
                                 {
                                  TB0CCR1 = (900);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2902)
                                 {
                                  TB0CCR1 = (950);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2841)
                                 {
                                  TB0CCR1 = (1000);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2780)
                                 {
                                  TB0CCR1 = (1050);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2719)
                                 {
                                  TB0CCR1 = (1100);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2658)
                                 {
                                  TB0CCR1 = (1150);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2597)
                                 {
                                  TB0CCR1 = (1200);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2536)
                                 {
                                  TB0CCR1 = (1250);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2475)
                                 {
                                  TB0CCR1 = (1300);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2414)
                                 {
                                  TB0CCR1 = (1350);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2353)
                                 {
                                  TB0CCR1 = (1400);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2292)
                                 {
                                  TB0CCR1 = (1450);
                                  saveX = TB0CCR1;
                                 }
                                 else if(hor > 2231)
                                 {
                                  TB0CCR1 = (1500);
                                  saveX = TB0CCR1;
                                 }


                             }
                             else if (hor < 1800)
                             {

                                 if(hor < 550)
                                 {
                                 TB0CCR1 = (2500);
                                 saveX = TB0CCR1;
                                 }
                                 else if(hor < 610)
                                 {
                                 TB0CCR1 = (2455);
                                 saveX = TB0CCR1;
                                 }
                                 else if(hor < 670)
                                  {
                                 TB0CCR1 = (2410);
                                 saveX = TB0CCR1;
                                  }
                                 else if(hor < 730)
                                 {
                                 TB0CCR1 = (2365);
                                 saveX = TB0CCR1;
                                   }
                                 else if(hor < 790)
                                 {
                                 TB0CCR1 = (2320);
                                 saveX = TB0CCR1;
                                 }
                                 else if(hor < 850)
                                 {
                                 TB0CCR1 = (2275);
                                 saveX = TB0CCR1;
                                 }
                                 else if(hor < 910)
                                   {
                                 TB0CCR1 = (2230);
                                 saveX = TB0CCR1;
                                 }
                                 else if(hor < 970)
                                 {
                                 TB0CCR1 = (2185);
                                 saveX = TB0CCR1;
                                }
                                 else if(hor < 1030)
                                  {
                                  TB0CCR1 = (2140);
                                  saveX = TB0CCR1;
                                  }

                                 else if(hor < 1090)
                                    {
                                   TB0CCR1 = (2095);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1150)
                                    {
                                   TB0CCR1 = (2050);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1210)
                                    {
                                   TB0CCR1 = (2005);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1270)
                                    {
                                   TB0CCR1 = (1960);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1330)
                                    {
                                   TB0CCR1 = (1915);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1390)
                                    {
                                   TB0CCR1 = (1870);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1450)
                                    {
                                   TB0CCR1 = (1825);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1510)
                                    {
                                   TB0CCR1 = (1780);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1570)
                                    {
                                   TB0CCR1 = (1735);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1630)
                                    {
                                   TB0CCR1 = (1690);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1690)
                                    {
                                   TB0CCR1 = (1645);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1750)
                                    {
                                   TB0CCR1 = (1600);
                                   saveX = TB0CCR1;
                                      }
                                 else if(hor < 1820)
                                    {
                                   TB0CCR1 = (1555);
                                   saveX = TB0CCR1;
                                      }
                                  else
                                  {
                                  TB0CCR1 = 1555;
                                  saveX = TB0CCR1;
                                 }
                             }

                  else{
                          TB0CCR1 = saveX;
                  }

return saveX;

}
int ready(int vert){
    // starts checking vertical values
    if (vert > 2200)
        {
           vert = vert + 90;
           if(vert > 4061)
           {
              TB0CCR2 = (0);
              saveY = TB0CCR2;
           }
           else if(vert > 4000)
           {
               TB0CCR2 = (50);
               saveY = TB0CCR2;
           }
           else if(vert > 3939)
           {
            TB0CCR2 = (100);
             saveY = TB0CCR2;
              }
           else if(vert > 3878)
           {
              TB0CCR2 = (150);
              saveY = TB0CCR2;
           }
           else if(vert > 3817)
           {
             TB0CCR2 = (200);
             saveY = TB0CCR2;
           }
           else if(vert > 3756)
           {
             TB0CCR2 = (250);
             saveY = TB0CCR2;
           }
           else if(vert > 3695)
            {
              TB0CCR2 = (300);
              saveY = TB0CCR2;
            }
                                     else if(vert > 3634)
                                     {
                                      TB0CCR2 = (350);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3573)
                                     {
                                      TB0CCR2 = (400);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3512)
                                     {
                                      TB0CCR2 = (450);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3451)
                                     {
                                      TB0CCR2 = (500);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3390)
                                     {
                                      TB0CCR2 = (550);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3329)
                                     {
                                      TB0CCR2 = (600);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3268)
                                     {
                                      TB0CCR2 = (650);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3207)
                                     {
                                      TB0CCR2 = (700);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3146)
                                     {
                                      TB0CCR2 = (750);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3085)
                                     {
                                      TB0CCR2 = (800);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 3024)
                                     {
                                      TB0CCR2 = (850);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2963)
                                     {
                                      TB0CCR2 = (900);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2902)
                                     {
                                      TB0CCR2 = (950);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2841)
                                     {
                                      TB0CCR2 = (1000);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2780)
                                     {
                                      TB0CCR2 = (1050);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2719)
                                     {
                                      TB0CCR2 = (1100);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2658)
                                     {
                                      TB0CCR2 = (1150);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2597)
                                     {
                                      TB0CCR2 = (1200);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2536)
                                     {
                                      TB0CCR2 = (1250);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2475)
                                     {
                                      TB0CCR2 = (1300);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2414)
                                     {
                                      TB0CCR2 = (1350);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2353)
                                     {
                                      TB0CCR2 = (1400);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2292)
                                     {
                                      TB0CCR2 = (1450);
                                      saveY = TB0CCR2;
                                     }
                                     else if(vert > 2231)
                                     {
                                      TB0CCR2 = (1500);
                                      saveY = TB0CCR2;
                                     }


                                 }
                                 else if (vert < 1800)
                                 {

                                     if(vert < 550)
                                     {
                                     TB0CCR2 = (2500);
                                     saveY = TB0CCR2;
                                     }
                                     else if(vert < 610)
                                     {
                                     TB0CCR2 = (2455);
                                     saveY = TB0CCR2;
                                     }
                                     else if(vert < 670)
                                      {
                                     TB0CCR2 = (2410);
                                     saveY = TB0CCR2;
                                      }
                                     else if(vert < 730)
                                     {
                                     TB0CCR2 = (2365);
                                     saveY = TB0CCR2;
                                       }
                                     else if(vert < 790)
                                     {
                                     TB0CCR2 = (2320);
                                     saveY = TB0CCR2;
                                     }
                                     else if(vert < 850)
                                     {
                                     TB0CCR2 = (2275);
                                     saveY = TB0CCR2;
                                     }
                                     else if(vert < 910)
                                       {
                                     TB0CCR2 = (2230);
                                     saveY = TB0CCR2;
                                     }
                                     else if(vert < 970)
                                     {
                                     TB0CCR2 = (2185);
                                     saveY = TB0CCR2;
                                    }
                                     else if(vert < 1030)
                                      {
                                      TB0CCR2 = (2140);
                                      saveY = TB0CCR2;
                                      }

                                     else if(vert < 1090)
                                        {
                                       TB0CCR2 = (2095);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1150)
                                        {
                                       TB0CCR2 = (2050);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1210)
                                        {
                                       TB0CCR2 = (2005);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1270)
                                        {
                                       TB0CCR2 = (1960);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1330)
                                        {
                                       TB0CCR2 = (1915);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1390)
                                        {
                                       TB0CCR2 = (1870);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1450)
                                        {
                                       TB0CCR2 = (1825);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1510)
                                        {
                                       TB0CCR2 = (1780);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1570)
                                        {
                                       TB0CCR2 = (1735);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1630)
                                        {
                                       TB0CCR2 = (1690);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1690)
                                        {
                                       TB0CCR2 = (1645);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1750)
                                        {
                                       TB0CCR2 = (1600);
                                       saveY = TB0CCR2;
                                          }
                                     else if(vert < 1820)
                                        {
                                       TB0CCR2 = (1555);
                                       saveY = TB0CCR2;
                                          }
                                      else
                                      {
                                      TB0CCR2 = 1555;
                                      saveY = TB0CCR2;
                                     }
                                 }

                      else{
                              TB0CCR2 = saveY;
                      }

    return saveY;

    }

// between every step take value divide by max val divided by 200

volatile int hor ;
volatile int vert;
volatile int xpress = 1;
volatile int ypress = 1;
int main(void)
{
    // led red and green
    P2DIR |= BIT1;
    P2DIR |= BIT6;
    P2OUT &= ~BIT1;
    P2OUT &= ~BIT6;

    pulsewidthmodulation();
    config_ADC_JOYSTICK();
    push1and2();
    WDTCTL = WDTPW | WDTHOLD; //Stop Watchdog Timer
    PM5CTL0 &= ~LOCKLPM5; //Enable GPIO
    __enable_interrupt();





    while (1) {

        hor = ADC12MEM0;
        vert = ADC12MEM1;
        ADC12CTL0 |= ADC12SC;

switch(state)
{

case 0 :

    TB0CCR1 = readx(hor);
    TB0CCR2 = ready(vert);

    if(xpress == 1 && ypress == 0)
    {
        state = FreezeX;
    }
    else if(xpress == 0 && ypress == 1)
    {
        state = FreezeY;
    }
    else if(xpress == 0 && ypress == 0)
    {
        state = Move;
    }
    else
    {
        state = FreezeAll;
    }

break;

case 3:

    TB0CCR1 = saveX;
    TB0CCR2 = saveY;
    if(xpress == 1 && ypress == 0)
    {
        state = FreezeX;
    }
    else if(xpress == 0 && ypress == 1)
    {
        state = FreezeY;
    }
    else if(xpress == 0 && ypress == 0)
    {
        state = Move;
    }
    else
    {
        state = FreezeAll;
    }

    break;
case 1:

    TB0CCR1 = saveX;
    TB0CCR2 = ready(vert);
    if(xpress == 1 && ypress == 0)
    {
        state = FreezeX;
    }
    else if(xpress == 0 && ypress == 1)
    {
        state = FreezeY;
    }
    else if(xpress == 0 && ypress == 0)
    {
        state = Move;
    }
    else
    {
        state = FreezeAll;
    }

break;

case 2:
    TB0CCR1 = readx(hor);
    TB0CCR2 = saveY;
    if(xpress == 1 && ypress == 0)
    {
        state = FreezeX;
    }
    else if(xpress == 0 && ypress == 1)
    {
        state = FreezeY;
    }
    else if(xpress == 0 && ypress == 0)
    {
        state = Move;
    }
    else
    {
        state = FreezeAll;
    }

default:
    state = Move;
    break;
}
         }
    return 0;
}


// ask about these vectorts for the iundicidual
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P2OUT |= BIT1;
    P2OUT |= BIT6;

    TB0CCTL0 &= ~CCIFG;// clears interrupt flag

}
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_CCR1(void)
{
    switch (__even_in_range(TB0IV, 14))
            {
                case TB0IV_TBCCR1:


                    P2OUT &= ~BIT1;

                    TB0CCTL1 &= ~CCIFG;

                    break;
                case TB0IV_TBCCR2:


                    P2OUT &= ~BIT6;


                    TB0CCTL2 &= ~CCIFG;

                    break;

                // Add other cases for additional CCRs if needed
                default:
                    break;
            }
}
// Interrupt service routine

#pragma vector = PORT3_VECTOR

__interrupt void PORT3_ISR(void) {

    // Check if interrupt was triggered by S1 (P3.0)

    if (P3IFG & BIT0) {

        if (ypress == 1) { // Interrupt triggered by rising edge

            ypress = 0;

        } else { // Interrupt triggered by falling edge

           ypress = 1;

        }

        P3IFG &= ~BIT0; // Clear interrupt flag for S1

        //P3IES ^= BIT0;  // Toggle edge select bit for S1 to prepare for next edge

    }



    // Check if interrupt was triggered by S2 (P3.1)

    if (P3IFG & BIT1) {

        if (xpress == 1) {

            xpress = 0;

        } else {

            xpress = 1;

        }


        P3IFG &= ~BIT1;
        //P3IES ^= BIT1;

    }
    P3IFG &= ~BIT0;
    P3IFG &= ~BIT1;
}
