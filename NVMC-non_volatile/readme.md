Simple library (simple_nv.c and simple_nv.h) to save some non volatile variables on a nRF chip. It uses the last page in flash. One page is 0x1000 in size. If you need more, you can set the define #define NUMBER_OF_PAGES 1 to a higher value.

To use this library:

Make a struct in your code containing all your nv variable's. This struct can contain other structs as well:
```
Struct
{
  uint32_t nv_variable_1;
  float nv_variable_2;
} nv_struct;

//init
simple_nv_init();

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
