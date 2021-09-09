/*
 * emu_sc_pus_service20.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */
#include <public/emu_sc_channel_drv_slib_v1.h>

Program20_3TC::Program20_3TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index,
                uint64_t paramValue):ProgramTC(uniTime2YK,20,3,brief){


  SetUInt16(index);
  SetUInt64(paramValue);
  NewProgram(this);
}

Program20_1TC::Program20_1TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index):ProgramTC(uniTime2YK,20,1,brief){

  SetUInt16(index);
  NewProgram(this);
}

