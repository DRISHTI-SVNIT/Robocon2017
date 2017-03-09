  #ifndef pwm_gen
#define pwm_gen

/*
for reference :-

M0PWM0 PINB6
M0PWM1 PINB7
M0PWM2 PINB4
M0PWM3 PINB5
M0PWM4 PINE4
M0PWM5 PINE5
M0PWM6 PINC4
M0PWM7 PINC5

M1PWM0 PIND0
M1PWM1 PIND1
M1PWM2 PINA6
M1PWM3 PINA7
M1PWM4 PINF0
M1PWM5 PINF1
M1PWM6 PINF2
M1PWM7 PINF3

NOTE :- pins 4 to 7 on both modules are not available for use
*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"


#define PWM_PRESCALE_1 SYSCTL_PWMDIV_1
#define PWM_PRESCALE_2 SYSCTL_PWMDIV_2
#define PWM_PRESCALE_4 SYSCTL_PWMDIV_4
#define PWM_PRESCALE_8 SYSCTL_PWMDIV_8
#define PWM_PRESCALE_16 SYSCTL_PWMDIV_16
#define PWM_PRESCALE_32 SYSCTL_PWMDIV_32
#define PWM_PRESCALE_64 SYSCTL_PWMDIV_64

#define M0PWM0 10
#define M0PWM1 11
#define M0PWM2 12
#define M0PWM3 13

#define M0PWM4 14
#define M0PWM5 15
#define M0PWM6 16
#define M0PWM7 17

#define M1PWM0 20
#define M1PWM1 21
#define M1PWM2 22
#define M1PWM3 23
/*
#define M1PWM0 24
#define M1PWM1 25
#define M1PWM2 26
#define M1PWM3 27
*/
#define COUNT_DOWN 0
#define COUNT_UP_DOWN 1

extern volatile float ticks_for_pwm_frequency;
extern volatile float ticks_for_duty_cycle;
extern volatile uint8_t prescalar;

void enable_pwm_clock(uint8_t pwm_clk_prescalar);
void config_pwm(uint8_t MPWM,uint8_t count_dir,uint8_t pwm_frequency);
void set_pwm(uint8_t MPWM,uint8_t select,uint8_t duty_cycle,float time_period_in_sec);

#endif
