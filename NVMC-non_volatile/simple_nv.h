#ifndef SIMPLE_NV_H
#define SIMPLE_NV_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include <stdint.h>


void flash_page_erase(void);
void flash_write(uint32_t,uint32_t*);
void flash_read(uint32_t, uint32_t*);


#ifdef __cplusplus
} // extern "C"
#endif
#endif