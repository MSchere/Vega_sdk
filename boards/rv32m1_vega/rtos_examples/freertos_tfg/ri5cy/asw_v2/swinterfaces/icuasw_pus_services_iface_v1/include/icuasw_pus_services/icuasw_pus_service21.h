/*
 * icuasw_pus_service21.h
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */

#ifndef PUBLIC__ICUASW_PUS_SERVICE21_H
#define PUBLIC__ICUASW_PUS_SERVICE21_H

class PUSService21:public PUSServices{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static void ProcessSensorTM( CDSensorTMBufferStatus &bufferStatus,
                                CDTMList &List, CDEventList & eventList);

};

#endif

