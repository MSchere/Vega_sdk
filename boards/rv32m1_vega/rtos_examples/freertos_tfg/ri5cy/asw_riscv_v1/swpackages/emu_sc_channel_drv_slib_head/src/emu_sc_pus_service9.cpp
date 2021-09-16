/*
 * emu_sc_pus_service9.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */

#include <public/emu_sc_channel_drv_slib_v1.h>

Program9_129TC::Program9_129TC(uint32_t uniTime2YK,
                         char * brief,
                         uint32_t nextUniTime2YK)
                        :ProgramTC(uniTime2YK,9,129,brief){

     SetUInt32(nextUniTime2YK);
     NewProgram(this);
  }
