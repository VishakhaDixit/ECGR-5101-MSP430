/*
 * adc.h
 *
 *  Created on: Aug 27, 2021
 *      Author: vishakha
 */

#ifndef ADC_H_
#define ADC_H_

#include <include/common.h>

typedef enum select_input_ch
{
    CH_0 = INCH_0,
    CH_1 = INCH_1,
    CH_2 = INCH_2,
    CH_3 = INCH_3,
    CH_4 = INCH_4,
    CH_5 = INCH_5,
    CH_6 = INCH_6,
    CH_7 = INCH_7
} input_ch_e;

typedef enum sample_hold_time
{
    FOUR_ADC_CLK = ADC10SHT_0,
    EIGHT_ADC_CLK = ADC10SHT_1,
    SIXTEEN_ADC_CLK = ADC10SHT_2,
    SIXTY_FOUR_ADC_CLK = ADC10SHT_3
} sh_time_e;

typedef enum sample_hold_source
{
    ADC_OSC = SHS_0,
    TIMER_OUT1 = SHS_1,
    TIMER_OUT0 = SHS_2,
    TIMER_OUT2 = SHS_3
} shs_e;

typedef enum select_clk_source
{
    INTERNAL_OSC = ADC10SSEL_0,
    CRYSTAL_CLK = ADC10SSEL_1,               //Low freq clk for peripherals
    CTRL_CLK = ADC10SSEL_2,                  //clk source for CPU
    SUB_MAIN_SYS_CLK = ADC10SSEL_3           //High freq clk for peripherals
} clk_src_e;

typedef enum select_conv_seq_mode
{
    SINGLE_CH_SINGLE_CONV = CONSEQ_0,
    SEQ_OF_CH = CONSEQ_1,
    REPEAT_SINGLE_CH = CONSEQ_2,
    REPEAT_SEQ_OF_CH = CONSEQ_3
} conv_seq_mode_e;

typedef struct adc_config_args
{
    input_ch_e adc_ch;
    sh_time_e sample_hold_time;
    shs_e sample_hold_src;
    clk_src_e clk_src;
    conv_seq_mode_e conv_seq_mode;
} adc_config_args_t;

void ADC_Init(adc_config_args_t *adc_config_params, pin_num_e pin_num);

uint16_t ADC_Read(void);

#endif /* ADC_H_ */
