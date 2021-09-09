/*
 * icuasw_pus_service16.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#include <public/icuasw_pus_services_iface_v1.h>
#include <stdio.h>

EventActionDefinition_t PUSService19::EventAction[EVENT_ACTION_TABLE_DIMENSION];

uint8_t PUSService19::PendingActionIndex[EVENT_ACTION_TABLE_DIMENSION];
uint8_t PUSService19::PendingActionNumber=0;

bool PUSService19::GetRIDRecActionIndex(uint16_t RID, uint8_t &index){
  bool encontrado=false;
  for (int j=0; ((j<EVENT_ACTION_TABLE_DIMENSION)&&!encontrado) ; j++ ){
           if(RID==EventAction[j].RID)
             {
               index=j;
               encontrado=true;
           }
  }
  return encontrado;
}

bool PUSService19::GetFreeRecActionIndex(uint8_t &index){
  bool encontrado=false;
    for (int j=0; ((j<EVENT_ACTION_TABLE_DIMENSION)&&!encontrado) ; j++ ){
             if(0==EventAction[j].RID)
               {
                 index=j;
                 encontrado=true;
             }
    }
    return encontrado;

}

void PUSService19::Exec19_1TC( CDTCDescriptor &TC, CDTMList &List){

  uint8_t index;
  byte_t *aux=TC.appData;
  uint16_t RID=GetUInt16(aux);

  bool encontrado=false;
  if(GetRIDRecActionIndex(RID,index)){
      encontrado=true;
  }else if(GetFreeRecActionIndex(index)){
      encontrado=true;
  }
  if(encontrado){
      EventAction[index].enabled=false;
      EventAction[index].RID=RID;
      EventAction[index].TC.dataFieldHeader.service=TC.appData[2];
      EventAction[index].TC.dataFieldHeader.subservice=TC.appData[3];
      List.Add(1,7);
  }else
    List.Add(1,8);

}

void PUSService19::Exec19_2TC( CDTCDescriptor &TC, CDTMList &List){

  uint8_t index;
  byte_t *aux=TC.appData;
  uint16_t RID=GetUInt16(aux);

  bool encontrado=false;
  if(GetRIDRecActionIndex(RID,index)){
      encontrado=true;
  }
  if(encontrado){
      EventAction[index].enabled=false;
      EventAction[index].RID=0;
      List.Add(1,7);
  }else
    List.Add(1,8);
}
void PUSService19::Exec19_4TC( CDTCDescriptor &TC, CDTMList &List){

  uint8_t index;
  byte_t *aux=TC.appData;
  uint16_t RID=GetUInt16(aux);

  bool encontrado=false;
  if(GetRIDRecActionIndex(RID,index)){
      encontrado=true;
  }
  if(encontrado){
      EventAction[index].enabled=true;
      List.Add(1,7);
  }else
    List.Add(1,8);
}

void PUSService19::Exec19_5TC( CDTCDescriptor &TC, CDTMList &List){

  uint8_t index;
  byte_t *aux=TC.appData;
  uint16_t RID=GetUInt16(aux);

  bool encontrado=false;
  if(GetRIDRecActionIndex(RID,index)){
      encontrado=true;
  }
  if(encontrado){
      EventAction[index].enabled=false;

      List.Add(1,7);
  }else
    List.Add(1,8);
}

void  PUSService19::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(1):
                    Exec19_1TC(TC,List);
                  break;
                case(2):
                    Exec19_2TC(TC,List);
                      break;
                case(4):
                    Exec19_4TC(TC,List);
                      break;
                case(5):
                    Exec19_5TC(TC,List);
                      break;
                break;
                default:
                  List.Add(1,8);
  }

}



void  PUSService19::GetNextRecAction( CDRecovAction &RecAction){

  if(PendingActionNumber>0){
    RecAction.SetActionIndex(PendingActionIndex[0]);
    PendingActionNumber--;
    for(int i=0; i< PendingActionNumber; i++)
      PendingActionIndex[i]=PendingActionIndex[i+1];
  }else
    RecAction.SetActionIndex(-1);
}

void  PUSService19::QueueEventListRecAct( CDEventList & eventList){

 for (int i=0; i< eventList.GetNumberOfEvents(); i++ ){
     uint8_t index;
     if(GetRIDRecActionIndex(eventList.GetEventRID(i),index)){
         PendingActionIndex[PendingActionNumber]=index;
         PendingActionNumber++;
     }
 }
}

bool  PUSService19::IsRecActQueueEmpty(){

  return (0==PendingActionNumber);
}

void  PUSService19::GetRecActionTCDescriptor(CDRecovAction &RecAction,
                                       CDTCDescriptor &TC){

  TC=EventAction[RecAction.m_RecActionIndex].TC;
  printf("Exec Rec Action from RID %x ",
         EventAction[RecAction.m_RecActionIndex].RID);
  printf("TC (%i,%i)\n ",
          TC.dataFieldHeader.service, TC.dataFieldHeader.subservice);

  TC.tcexecCtrl=ExecAsPrioTC;
  switch(TC.dataFieldHeader.service){
      case(3):
      case(5):
      case(12):
      case(19):
            TC.tcexecCtrl=ExecAsHK_FDIRTC;
        break;
      case(6):
          TC.tcexecCtrl=ExecAsBKGTC;
       break;
      case(9):
      case(17):
          TC.tcexecCtrl=ExecAsPrioTC;
        break;
        case(21):
          TC.tcexecCtrl=ExecAsSensorMngTC;
       case(128):
        switch(TC.dataFieldHeader.subservice){
                case(1):
                    TC.tcexecCtrl=ExecAsChangeModeTC;
                  break;
                case(3):
                    TC.tcexecCtrl=ExecAsResetTC;
                  break;
                case(2):
                case(4):
                case(5):
                    TC.tcexecCtrl=ExecAsBKGTC;
                break;
        }
  }

}
