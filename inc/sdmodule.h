/*
 * sdmodule.h
 *
 */

#ifndef SDMODULE_H_
#define SDMODULE_H_

#include <string.h>
#include "delay.h"
#include "fpu.h"
#include "spi_sd.h"
#include "ff.h"



void SDmodule_Configuration(void);
uint8_t SDmodule_ReadFile(char* file_name, char * buffer, UINT * loaded_bytes);
uint8_t SDmodule_WriteFile(char * file_name, char * file_content);


#endif /* SDMODULE_H_ */
