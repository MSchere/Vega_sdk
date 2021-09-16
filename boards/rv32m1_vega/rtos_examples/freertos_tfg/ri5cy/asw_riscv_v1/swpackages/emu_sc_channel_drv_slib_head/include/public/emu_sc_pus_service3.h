/*
 * emu_sc_pus_service3.h
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE3_H_
#define EMU_SC_PUS_SERVICE3_H_

class Program3_5TC:public ProgramTC{

public:
  //Enable
  Program3_5TC(uint32_t uniTime2YK,
                 char * brief,
                 uint16_t SID);
};

class Program3_6TC:public ProgramTC{

public:
  //Set Parameter
  Program3_6TC(uint32_t uniTime2YK,
                 char * brief,
                 uint16_t SID);
};

class Program3_31TC:public ProgramTC{

public:
  //Set Parameter
  Program3_31TC(uint32_t uniTime2YK,
                 char * brief,
                 uint16_t SID,
                 uint16_t interval);
};
#endif /* EMU_SC_PUS_SERVICE3_H_ */
