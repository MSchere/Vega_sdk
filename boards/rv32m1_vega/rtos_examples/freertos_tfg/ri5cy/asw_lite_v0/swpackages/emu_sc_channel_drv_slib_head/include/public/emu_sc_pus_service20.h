/*
 * emu_sc_pus_service20.h
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE20_H_
#define EMU_SC_PUS_SERVICE20_H_


class Program20_3TC:public ProgramTC{

public:
  //Set Parameter
  Program20_3TC(uint32_t uniTime2YK,
                 char * brief,uint16_t index,uint64_t paramValue);
};

class Program20_1TC:public ProgramTC{

public:
  //Get Parameter
  Program20_1TC(uint32_t uniTime2YK,
                 char * brief, uint16_t index);

};


#endif /* EMU_SC_PUS_SERVICE128_H_ */
