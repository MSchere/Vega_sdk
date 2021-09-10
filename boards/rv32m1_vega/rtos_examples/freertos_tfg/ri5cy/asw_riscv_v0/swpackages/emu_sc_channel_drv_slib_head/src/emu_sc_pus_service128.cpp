/*
 * emu_sc_pus_service128.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */
#include <public/emu_sc_channel_drv_slib_v1.h>

Program128_4TC::Program128_4TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index,
                uint64_t paramValue):ProgramTC(uniTime2YK,128,4,brief){


  SetUInt16(index);
  SetUInt64(paramValue);
  NewProgram(this);
}

Program128_5TC::Program128_5TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index):ProgramTC(uniTime2YK,128,5,brief){

  SetUInt16(index);
  NewProgram(this);
}

