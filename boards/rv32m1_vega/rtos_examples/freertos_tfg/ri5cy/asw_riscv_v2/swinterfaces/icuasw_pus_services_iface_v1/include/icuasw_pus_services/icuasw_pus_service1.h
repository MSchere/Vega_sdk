/*
 * icuasw_pus_service1.h
 *
 *  Created on: Dec 21, 2016
 *      Author: user
 */




#ifndef PUBLIC__ICUASW_PUS_SERVICE1_H
#define PUBLIC__ICUASW_PUS_SERVICE1_H

class PUSService1:public PUSServices{

public:
  static bool_t AcceptTC( CDTCDescriptor &TC, CDTMList &List);

};
#endif

