/*
 * icuasw_pus_service9.h
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#ifndef PUBLIC__ICUASW_PUS_SERVICE9_H
#define PUBLIC__ICUASW_PUS_SERVICE9_H

class PUSService9:public PUSServices{

public:
  static uint32_t NextUniTimeY2KSecns;
  static uint32_t CurrentUniTimeY2KSecns;

  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static uint32_t GetCurrentUniTimeY2K();
  static uint32_t GetCurrentUniTimeNanoSecns();
};
#endif

