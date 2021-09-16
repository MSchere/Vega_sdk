/*
 * icuasw_pus_service12.h
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */

#ifndef PUBLIC__ICUASW_PUS_SERVICE12_H
#define PUBLIC__ICUASW_PUS_SERVICE12_H

struct ParamMonitoringConfig_t{
  bool  enabled;
  uint8_t interval;
  uint8_t intervalControl;


};

enum CheckStatus_t{
  MonitorUnselected,MonitorUnchecked,MonitorInvalid, MonitorCheckValid
};

struct ParamLimitCheckDefinition_t{

  CheckStatus_t  prevstatus;
  CheckStatus_t  status;
  uint32_t transition_Y2K;
  uint16_t highLimitRID;
  uint64_t highLimit;
  uint16_t lowLimitRID;
  uint64_t lowLimit;

};

class PUSService12:public PUSServices{

public:

  static ParamMonitoringConfig_t  PARAMMonitoringConfig[DATAPOOL_PARAMNumber];
  static ParamLimitCheckDefinition_t PARAMLimitDefinition[DATAPOOL_PARAMNumber];

  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static void DoMonitoring(CDTMList &List, CDEventList & eventList);

protected:

  static void Exec12_5TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec12_1TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec12_2TC( CDTCDescriptor &TC, CDTMList &List);
};

#endif
