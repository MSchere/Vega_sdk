/*
 * icuasw_pus_private_service128.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#ifndef PUBLIC__ICUASW_PUS_SERVICE128_H
#define PUBLIC__ICUASW_PUS_SERVICE128_H

class PUSService128:public PUSServices{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static void Exec128_4TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec128_5TC( CDTCDescriptor &TC, CDTMList &List);

};
#endif
