/*
 * da.c
 * Initierar en da omvandlare för dacc 1
 * Created: 2017-01-11 10:37:52
 *  Author: Leonard & Hadi
 */ 

#include <asf.h>
#include "da.h"

int daccInit(){
	
	int ok=1;
	pmc_enable_periph_clk(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC,0);
	dacc_set_timing(DACC,1,1,0);
	dacc_set_channel_selection(DACC,1);
	ok = dacc_enable_channel(DACC,1);
	return ok;
}
