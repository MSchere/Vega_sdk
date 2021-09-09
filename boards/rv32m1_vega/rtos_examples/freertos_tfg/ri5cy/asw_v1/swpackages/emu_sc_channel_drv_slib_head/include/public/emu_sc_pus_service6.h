/*
 * emu_sc_pus_service6.h
 *
 *  Created on: Jan 17, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE6_H_
#define EMU_SC_PUS_SERVICE6_H_


class Program6_2TC:public ProgramTC{

public:
  //Set Parameter
  Program6_2TC(uint32_t uniTime2YK,
                 char * brief,
                 uint32_t abs_address,
                 uint16_t length,
                 uint8_t * data);
};

class Program6_5TC:public ProgramTC{

public:
  //Get Parameter
  Program6_5TC(uint32_t uniTime2YK,
                 char * brief,
                 uint32_t abs_address,
                 uint16_t length);

};


#endif /* EMU_SC_PUS_SERVICE6_H_ */
