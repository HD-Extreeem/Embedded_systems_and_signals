



#ifndef btnConf_h
#define btnConf_h

#include "asf.h"

#define Due_D2 PIO_PB25_IDX
#define Due_D3 PIO_PC28_IDX
#define Due_D4 PIO_PC26_IDX
#define Due_D5 PIO_PC25_IDX

#define Due_D6 PIO_PC24_IDX
#define Due_D7 PIO_PC23_IDX
#define Due_D8 PIO_PC22_IDX
#define Due_D9 PIO_PC21_IDX


#define pin_mask_D6_D9 (0b1111<<21)

int ledconfset(void);
int btnconfset(void);

#endif