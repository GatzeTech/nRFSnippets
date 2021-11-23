Simple library (simple_nv.c and simple_nv.h) to save some non volatile variables on a nRF chip. Be aware that you have to set the location your self. I'm using the nRF52832 with a flash size of 512kb. It has 0x80 flash pages of 0x1000 size so the last page (which is usually alway's free) is 0x7f * 0x1000=0x7f000, this is the base adress. You should change this to your desired value.

For example if you use the 256 kb version than the chip has 0x40 pages and adress of the begin of the last pages is: 0x3f * 0x1000=0x3f000 This is the base address.

The base address is a define:
#define NV_BASE_ADRRESS 0x7f000ul

To use this library:

Make a struct in your code containing all your nv variable's. This struct can contain other structs as well:
```
Struct
{
  uint32_t nv_variable_1;
  float nv_variable_2;
} nv_struct;


//Saving
flash_page_erase();
flash_write(sizeof(nv_struct), (uint32_t*)&nv_struct);

//Reading
flash_read(sizeof(nv_struct),(uint32_t*)&nv_struct);`
```

Some more info:

[NVMC controller](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52832.ps.v1.1%2Fsaadc.html)

[Memory Layout](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52832.ps.v1.1%2Fmemory.html&anchor=memory)

[Memory Map](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsds_s140%2FSDS%2Fs1xx%2Fmem_usage%2Fmem_resource_map_usage.html)

Be aware that it alway's uses the same place in Flash, Flash memory doesn't have unlimited write possibility. The FDS example of Nordic uses constantly different places in flash to write.
