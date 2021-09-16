/*
 * emu_sc_pus_service17.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: user
 */



#include <public/emu_sc_channel_drv_slib_v1.h>

Program17_1TC::Program17_1TC(uint32_t uniTime2YK,
                         char * brief)
                        :ProgramTC(uniTime2YK,17,1,brief){

     NewProgram(this);
}

