/*
 * emu_sc_pus_service12.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */


#include <public/emu_sc_channel_drv_slib_v1.h>

Program12_1TC::Program12_1TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index):ProgramTC(uniTime2YK,12,1,brief){

     SetUInt16(index);

     NewProgram(this);
  }

Program12_2TC::Program12_2TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index):ProgramTC(uniTime2YK,12,2,brief){

     SetUInt16(index);

     NewProgram(this);
  }


Program12_5TC::Program12_5TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index,
                uint16_t interval,
                uint16_t lowLimitRID,
                uint64_t lowLimit,
                uint16_t highLimitRID,
                uint64_t highLimit):ProgramTC(uniTime2YK,12,5,brief){


     SetUInt16(interval);
     SetUInt16(index);
     SetUInt64(lowLimit);
     SetUInt16(lowLimitRID);
     SetUInt64(highLimit);
     SetUInt16(highLimitRID);

     NewProgram(this);
  }
