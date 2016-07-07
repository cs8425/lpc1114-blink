#ifndef __systick_H
#define __systick_H

#ifdef __cplusplus
extern "C" {
#endif

#define TICKER_TIMER          ((LPC_TMR_TypeDef *)LPC_CT32B1_BASE)
#define TICKER_TIMER_IRQn     TIMER_32_1_IRQn

volatile uint32_t sys_tick = 0;

void ticker_init(void);
void ticker_irq_handler(void);

void ticker_init(void){
/*
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);    // Enable TIMER32_1 clock
    LPC_TMR32B1->MR0 = 48000;          // MR0 = 1ms
    LPC_TMR32B1->MCR = (1 << 0)|(1 << 1);        // MR0 resets timer & interrupt
    LPC_TMR32B1->PWMC = (1 << 0);        // Enable PWM0
    LPC_TMR32B1->TCR = TCR_CNT_EN;            // Enable Timer4
    
    NVIC_EnableIRQ(TIMER_32_1_IRQn);*/

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10); // Clock TIMER_1
    uint32_t PCLK = SystemCoreClock;
 
    TICKER_TIMER->TCR = 0x2;  // reset
 
    uint32_t prescale = PCLK / 4000000; // default to 4MHz (0.25 us ticks)
    TICKER_TIMER->PR = prescale - 1;
    TICKER_TIMER->TCR = 1; // enable = 1, reset = 0
 
    //NVIC_SetVector(TICKER_TIMER_IRQn, (uint32_t)ticker_irq_handler);
    //NVIC_EnableIRQ(TICKER_TIMER_IRQn);

}

uint32_t ticker_read(void) {
    return TICKER_TIMER->TC;
}

void TIMER32_1_IRQHandler(void)
//void ticker_irq_handler(void)
{
    if ( LPC_TMR32B1->IR & 0x01 ){
        LPC_TMR32B1->IR = 0x01;    /* clear interrupt flag */
        sys_tick++;
    }
    return;
}

void ticker_set_interrupt(uint32_t timestamp) {
    // set match value
    TICKER_TIMER->MR0 = timestamp;
    // enable match interrupt
    TICKER_TIMER->MCR |= 1;
}
 
void ticker_disable_interrupt(void) {
    TICKER_TIMER->MCR &= ~1;
}
 
void ticker_clear_interrupt(void) {
    TICKER_TIMER->IR = 1;
}

#ifdef __cplusplus
}
#endif

/*
typedef volatile uint32_t REG32;
#define pREG32 (REG32 *)

//  STCTRL (System Timer Control and status register)
//  The STCTRL register contains control information for the System Tick Timer, and provides
//  a status flag.
#define SYSTICK_STCTRL                            (*(pREG32 (0xE000E010)))    // System tick control
#define SYSTICK_STCTRL_ENABLE                     (0x00000001)    // System tick counter enable
#define SYSTICK_STCTRL_TICKINT                    (0x00000002)    // System tick interrupt enable
#define SYSTICK_STCTRL_CLKSOURCE                  (0x00000004)    // NOTE: This isn't documented but is based on NXP examples
#define SYSTICK_STCTRL_COUNTFLAG                  (0x00010000)    // System tick counter flag


uint32_t sys_tick = 0;

void SysTick_init(void)
{
    // Turn on the system tick timer with an interval of once per millisecond.
    //SysTick_Config(SystemCoreClock / 1000000);
    // Enable systick IRQ and timer
    SYSTICK_STCTRL = SYSTICK_STCTRL_CLKSOURCE |
                   SYSTICK_STCTRL_TICKINT |
                   SYSTICK_STCTRL_ENABLE;
}

void SysTick_Handler(void)
{
    sys_tick++;
}
*/
#endif

