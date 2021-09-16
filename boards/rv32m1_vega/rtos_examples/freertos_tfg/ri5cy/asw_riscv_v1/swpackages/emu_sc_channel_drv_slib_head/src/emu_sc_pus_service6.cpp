/*
 * emu_tc_pus_services6.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: user
 */


#include <public/emu_sc_channel_drv_slib_v1.h>

Program6_2TC::Program6_2TC(uint32_t uniTime2YK,
                 char * brief,
                 uint32_t abs_address,uint16_t length,
                 uint8_t * data)
                :ProgramTC(uniTime2YK,6,2,brief){

    SetUInt32(abs_address);
    SetUInt16(length);

    if(length > 250)
      length=250;

    if(data){
        while(length){
             SetUInt8(*data);
             data++;
             length--;
        }
    }

    NewProgram(this);

}

  //Get Parameter
Program6_5TC::Program6_5TC(uint32_t uniTime2YK,
                 char * brief,
                 uint32_t abs_address,
                 uint16_t length)
                  :ProgramTC(uniTime2YK,6,5,brief){

  SetUInt32(abs_address);
  SetUInt16(length);

  NewProgram(this);
}
