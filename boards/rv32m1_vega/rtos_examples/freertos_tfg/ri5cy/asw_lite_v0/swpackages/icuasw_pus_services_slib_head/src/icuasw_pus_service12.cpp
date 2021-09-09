/*
 * icuasw_pus_service12.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */

#include <public/icuasw_pus_services_iface_v1.h>
#include <stdio.h>

ParamMonitoringConfig_t PUSService12::PARAMMonitoringConfig[DATAPOOL_PARAMNumber]={

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},

    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0},
    {false,1,0}

};

ParamLimitCheckDefinition_t PUSService12::PARAMLimitDefinition[DATAPOOL_PARAMNumber]={

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},

  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0},
  {MonitorUnselected,MonitorUnselected,0,0,0,0,0}

};


void  PUSService12::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                  case(1):
                     Exec12_1TC(TC,List);
                     break;
                  case(2):
                     Exec12_2TC(TC,List);
                     break;
                  case(5):
                    Exec12_5TC(TC,List);
                  break;
                  case(8):
                   List.Add(12,9);
                  break;

                  case(6):
                  case(7):
                   List.Add(1,7);;
                  break;
                  default:
                    List.Add(1,8);
    }

}

void PUSService12::Exec12_5TC( CDTCDescriptor &TC, CDTMList &List){

  uint16_t interval;
  uint16_t paramIndex;
  byte_t *aux=TC.appData;

  interval=GetUInt16(aux);
  paramIndex=GetUInt16(aux);


  if(paramIndex < DATAPOOL_PARAMNumber){

      PUSService12::PARAMMonitoringConfig[paramIndex].interval=interval;
      PUSService12::PARAMMonitoringConfig[paramIndex].intervalControl=0;
      PUSService12::PARAMLimitDefinition[paramIndex].status=MonitorUnchecked;

      PUSService12::PARAMLimitDefinition[paramIndex].lowLimit=
          GetUInt64(aux);

      PUSService12::PARAMLimitDefinition[paramIndex].lowLimitRID=
          GetUInt16(aux);


      PUSService12::PARAMLimitDefinition[paramIndex].highLimit=
          GetUInt64(aux);

      PUSService12::PARAMLimitDefinition[paramIndex].highLimitRID=
          GetUInt16(aux);

      //printf("high limit %i", (uint32_t) PARAMLimitDefinition[paramIndex].highLimit);
      List.Add(1,7);

  }else{
      List.Add(1,8);
  }
}


void PUSService12::Exec12_1TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *aux=TC.appData;
  uint16_t paramIndex;
  paramIndex=GetUInt16(aux);
  if(paramIndex < DATAPOOL_PARAMNumber){
      PUSService12::PARAMMonitoringConfig[paramIndex].enabled=true;
      PUSService12::PARAMMonitoringConfig[paramIndex].intervalControl=0;
      PUSService12::PARAMLimitDefinition[paramIndex].status=MonitorUnchecked;

      List.Add(1,7);
  }else{

      List.Add(1,8);
  }
}

void PUSService12::Exec12_2TC( CDTCDescriptor &TC, CDTMList &List){


  byte_t *aux=TC.appData;
  uint16_t paramIndex;
  paramIndex=GetUInt16(aux);
  if(paramIndex < DATAPOOL_PARAMNumber){
      PUSService12::PARAMMonitoringConfig[paramIndex].enabled=false;
      List.Add(1,7);
  }else{

      List.Add(1,8);
  }

}

void PUSService12::DoMonitoring(CDTMList &List, CDEventList & eventList){

  printf("Do_Monitoring\n");

  for(int i=0; i < DATAPOOL_PARAMNumber; i++){

      if(PARAMMonitoringConfig[i].enabled){

        if(PARAMMonitoringConfig[i].intervalControl>=PARAMMonitoringConfig[i].interval){
          PARAMMonitoringConfig[i].intervalControl=0;
          //Monitor Limits

          if(PARAMLimitDefinition[i].status!=MonitorUnselected){
            if(PARAMLimitDefinition[i].status!=MonitorInvalid){

              if(PARAMLimitDefinition[i].highLimit
                  < PUSServices::DATAPOOL_PARAMCurrentValue[i]){
                  eventList.AddEvent(PARAMLimitDefinition[i].highLimitRID);
                  uint8_t aux[256];
                  byte_t *auxP=aux;
                  SetUInt16(PARAMLimitDefinition[i].highLimitRID,auxP);

                  List.Add(5,4,aux);
                  PARAMLimitDefinition[i].prevstatus=PARAMLimitDefinition[i].status;
                  PARAMLimitDefinition[i].status=MonitorInvalid;


                  PARAMLimitDefinition[i].transition_Y2K=PUSService9::GetCurrentUniTimeY2K();
              }else if(PARAMLimitDefinition[i].lowLimit
                                > PUSServices::DATAPOOL_PARAMCurrentValue[i]){
                  eventList.AddEvent(PARAMLimitDefinition[i].lowLimitRID);
                  uint8_t aux[256];
                  byte_t *auxP=aux;
                  SetUInt16(PARAMLimitDefinition[i].lowLimitRID,auxP);
                  List.Add(5,4,aux);
                  PARAMLimitDefinition[i].prevstatus=PARAMLimitDefinition[i].status;
                  PARAMLimitDefinition[i].status=MonitorInvalid;
                  PARAMLimitDefinition[i].transition_Y2K=PUSService9::GetCurrentUniTimeY2K();
              }else{
                  if(PARAMLimitDefinition[i].status==MonitorUnchecked){
                    PARAMLimitDefinition[i].prevstatus=PARAMLimitDefinition[i].status;
                    PARAMLimitDefinition[i].transition_Y2K=PUSService9::GetCurrentUniTimeY2K();
                    PARAMLimitDefinition[i].status=MonitorCheckValid;
                  }
              }

            }else{
                printf("high limit %i", (int) PARAMLimitDefinition[i].highLimit);
                if((PARAMLimitDefinition[i].highLimit
                                >PUSServices::DATAPOOL_PARAMCurrentValue[i])
                  && (PARAMLimitDefinition[i].lowLimit
                      <PUSServices::DATAPOOL_PARAMCurrentValue[i])){
                printf("Param Valid again\n");
                PARAMLimitDefinition[i].prevstatus=PARAMLimitDefinition[i].status;
                PARAMLimitDefinition[i].status=MonitorCheckValid;
                PARAMLimitDefinition[i].transition_Y2K=PUSService9::GetCurrentUniTimeY2K();
              }
            }
          }
        }else {
            PARAMMonitoringConfig[i].intervalControl++;
        }
      }
  }

}

