#include "simple_nv.h"
#include <nrf.h>

/*
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52832.ps.v1.1%2Fmemory.html&anchor=memory
1 page is 0x1000
1 block is 0x200 (8 blocks in 1 page)

I want to use the last page for my data
Can be read from FICR for now it's hardcoded
From SWD FICR CODESIZE (Page's) is 0x80

Start adress last page is (0x1000*0x80=0x80000) - 0x1000 = 0x7f000

First implementation is every time saving a nv variable, erasing the page and then write all nv variables again.
Later on I want to first check if flash part to write has bit value's of 1 (can only write 1 to 0 and not visa verca)
If not than buffer page, erase page and write all again from buffer and new value's to flash
*/

//#define NV_BASE_ADRRESS 0x7f000ul

#define NUMBER_OF_PAGES 1

volatile uint32_t nv_base_address;

static void nvmc_wait_until_ready(void)
{
  while (NRF_NVMC->READY != NVMC_READY_READY_Ready)
  {
          // Wait until NVMC is done with its current operation.
  }
  return;
}

void simple_nv_init(void)
{
  nv_base_address = (NRF_FICR->CODESIZE-NUMBER_OF_PAGES) * NRF_FICR->CODEPAGESIZE;
}


void flash_page_erase(void)
{
  // Enable erase.
  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
  __ISB();
  __DSB();

  // Erase the page
  NRF_NVMC->ERASEPAGE = nv_base_address;
  nvmc_wait_until_ready();

  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
  __ISB();
  __DSB();
}

void flash_write(uint32_t size, uint32_t* data)
{
  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
  //Last values can be outside variable, because of 32 bit alignement, should not be a problem
  for (uint32_t i = 0; (i << 2) < size; i++)
  {
    *((uint32_t*)nv_base_address + i) = *(data+i);
    nvmc_wait_until_ready();
  }
  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
  nvmc_wait_until_ready();
}

void flash_read(uint32_t size, uint32_t* data)
{
  //reading also aligned in 32 bit size ?, I guess not
  for (uint32_t i = 0; (i << 2) < size; i++)
  { 
    *(data+i) = *((uint32_t *)nv_base_address + i);
    nvmc_wait_until_ready();
  }
}