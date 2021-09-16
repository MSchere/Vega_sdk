/*
 * emu_sc_pus_service19.h
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE19_H_
#define EMU_SC_PUS_SERVICE19_H_


class Program19_1TC:public ProgramTC{

public:

  Program19_1TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID,
                uint8_t service,
                uint8_t subservice);
};

class Program19_2TC:public ProgramTC{

public:

  //Clear
  Program19_2TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID);

};

class Program19_4TC:public ProgramTC{

public:

  //Enable
  Program19_4TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID);
};


class Program19_5TC:public ProgramTC{

public:

  //Disable
  Program19_5TC(uint32_t uniTime2YK,
                char * brief,
                uint16_t RID);
};



#endif /* EMU_SC_PUS_SERVICE19_H_ */
