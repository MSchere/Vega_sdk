/*
 * emu_sc_pus_service12.h
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE12_H_
#define EMU_SC_PUS_SERVICE12_H_


class Program12_1TC:public ProgramTC{

public:

  Program12_1TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index);

};

class Program12_2TC:public ProgramTC{

public:

  Program12_2TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t index);
};

class Program12_5TC:public ProgramTC{

public:


  Program12_5TC(uint32_t uniTime2YK,
                  char * brief,
                  uint16_t index,
                  uint16_t interval,
                  uint16_t lowLimitRID,
                  uint64_t lowLimit,
                  uint16_t highLimitRID,
                  uint64_t highLimit);
};

#endif /* EMU_SC_PUS_SERVICE12_H_ */
