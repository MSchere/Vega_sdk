/*
 * icuaasw_pus_service5.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#ifndef PUBLIC__ICUASW_PUS_SERVICE5_H
#define PUBLIC__ICUASW_PUS_SERVICE5_H

union RIDSerial_t{
    uint16_t RID;
    uint8_t  bytes[2];
};

class PUSService5:public PUSServices{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

};
#endif

