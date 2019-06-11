/*
 * tcc_conf.c
 * Konfigurerar en timer counter
 * Created: 2017-01-11 15:24:19
 *  Author: Hadi & Leo
 */ 
#include "asf.h"
#include <inttypes.h>

/*Konfigurerar en timer counter interrup med en viss frekvens och vilken klocka som skall användas*/
void configure_tc(void){
	
	uint32_t divisor;
	uint32_t tcclock;
	uint32_t sysclock = sysclk_get_cpu_hz();
    
	pmc_enable_periph_clk(ID_TC5); //Sätter igång timer klockan
	tc_find_mck_divisor(28464, sysclock, &divisor, &tcclock, sysclock);
	tc_init(TC1, 2, tcclock | TC_CMR_CPCTRG);//initierar timern
	tc_write_rc(TC1, 2, (sysclock/divisor) /28464);
	NVIC_EnableIRQ((IRQn_Type) TC5_IRQn);
	tc_enable_interrupt(TC1, 2 , TC_IER_CPCS);
	tc_start(TC1,2); //startar timern
}
