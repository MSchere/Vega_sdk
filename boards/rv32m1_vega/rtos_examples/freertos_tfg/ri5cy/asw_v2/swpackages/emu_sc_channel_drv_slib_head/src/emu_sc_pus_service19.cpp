/*
 * emu_sc_pus_pus_service19.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: user
 */

#include <public/emu_sc_channel_drv_slib_v1.h>

Program19_1TC::Program19_1TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID,
                uint8_t service,
                uint8_t subservice):ProgramTC(uniTime2YK,19,1,brief){


  SetUInt16(RID);
  SetUInt8(service);
  SetUInt8(subservice);
  NewProgram(this);

}


Program19_2TC::Program19_2TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID):ProgramTC(uniTime2YK,19,2,brief){

  SetUInt16(RID);

  NewProgram(this);
}

Program19_4TC::Program19_4TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID):ProgramTC(uniTime2YK,19,4,brief){

  SetUInt16(RID);

  NewProgram(this);
}


Program19_5TC::Program19_5TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID):ProgramTC(uniTime2YK,19,5,brief){

  SetUInt16(RID);

  NewProgram(this);
}


