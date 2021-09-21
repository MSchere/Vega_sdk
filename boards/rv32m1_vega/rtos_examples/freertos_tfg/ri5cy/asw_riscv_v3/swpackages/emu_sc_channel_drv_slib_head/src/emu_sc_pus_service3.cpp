/*
 * emu_sc_pus_service3.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#include <public/emu_sc_channel_drv_slib_v1.h>


Program3_5TC::Program3_5TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t SID):ProgramTC(uniTime2YK,3,5,brief){

  SetUInt16(SID);
  NewProgram(this);
}

Program3_6TC::Program3_6TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t SID):ProgramTC(uniTime2YK,3,6,brief){

  SetUInt16(SID);
  NewProgram(this);
}

Program3_31TC::Program3_31TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t SID,
                uint16_t interval ):ProgramTC(uniTime2YK,3,31,brief){

  SetUInt16(SID);
  SetUInt16(interval);

  NewProgram(this);
}
