/*
 * emu_sc_pus_service128.h
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE128_H_
#define EMU_SC_PUS_SERVICE128_H_


class Program128_4TC:public ProgramTC{

public:
  //Set Parameter
  Program128_4TC(uint32_t uniTime2YK,
                 char * brief,uint16_t index,uint64_t paramValue);
};

class Program128_5TC:public ProgramTC{

public:
  //Get Parameter
  Program128_5TC(uint32_t uniTime2YK,
                 char * brief, uint16_t index);

};


#endif /* EMU_SC_PUS_SERVICE128_H_ */
