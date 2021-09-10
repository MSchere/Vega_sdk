/*
 * icuasw_pus_private_service20.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#ifndef PUBLIC__ICUASW_PUS_SERVICE20_H
#define PUBLIC__ICUASW_PUS_SERVICE20_H

class PUSService20:public PUSServices{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static void Exec20_1TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec20_3TC( CDTCDescriptor &TC, CDTMList &List);

};
#endif
