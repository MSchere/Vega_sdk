/*
 * icuasw_pus_service19.h
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#ifndef PUBLIC__ICUASW_PUS_SERVICE19_H
#define PUBLIC__ICUASW_PUS_SERVICE19_H

#define EVENT_ACTION_TABLE_DIMENSION 16

struct EventActionDefinition_t{
  bool_t enabled;
  uint16_t RID;
  CDTCDescriptor TC;
};

class PUSService19:public PUSServices{

  static bool GetRIDRecActionIndex(uint16_t RID, uint8_t &i);
  static bool GetFreeRecActionIndex(uint8_t &i);

  static void Exec19_1TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec19_2TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec19_4TC( CDTCDescriptor &TC, CDTMList &List);
  static void Exec19_5TC( CDTCDescriptor &TC, CDTMList &List);

public:


  static void ExecTC( CDTCDescriptor &TC, CDTMList &List);
  static void GetNextRecAction( CDRecovAction &RecAction);
  static bool IsRecActQueueEmpty();
  static void QueueEventListRecAct( CDEventList & eventList);
  static void GetRecActionTCDescriptor(CDRecovAction &RecAction,
                                       CDTCDescriptor &TC);

  static EventActionDefinition_t EventAction[EVENT_ACTION_TABLE_DIMENSION];
  static uint8_t PendingActionIndex[EVENT_ACTION_TABLE_DIMENSION];
  static uint8_t PendingActionNumber;



};
#endif

