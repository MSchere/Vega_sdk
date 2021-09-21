/*
 * icuaasw_pus_service3.h
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#ifndef PUBLIC__ICUASW_PUS_SERVICE3_H
#define PUBLIC__ICUASW_PUS_SERVICE3_H

struct HKConfig_t{
  bool  enabled;
  uint16_t SID;
  uint8_t interval;
  uint8_t intervalControl;
  uint8_t ParamNum;
  uint8_t ParamDef[16];
};

#define PUS_SERVICE3_SID_NUMBER 8

class PUSService3:public PUSServices{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);

  static void DoHK(CDTMList &List);

  static HKConfig_t HKConfig[PUS_SERVICE3_SID_NUMBER];
protected:
  static bool GetSIDIndex(uint16_t SID, uint8_t &index);

  static void ExecEnableConfigTC(CDTCDescriptor &TC, CDTMList &List,
                                 bool newEnableConfig);

  static void Exec3_5TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec3_6TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec3_31TC( CDTCDescriptor &TC, CDTMList &List);

};
#endif

