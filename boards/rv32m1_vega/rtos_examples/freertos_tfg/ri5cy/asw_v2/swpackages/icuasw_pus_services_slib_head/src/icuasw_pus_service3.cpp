/*
 * icuaasw_pus_service3.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#include <public/icuasw_pus_services_iface_v1.h>
#include <stdio.h>


HKConfig_t PUSService3::HKConfig[PUS_SERVICE3_SID_NUMBER]={
    {true,0,10,0,4,{0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0}},
    {true,10,30,0,4,{4,5,6,7,0,0,0,0,0,0,0,0,0,0,0,0}},
    {true,11,60,0,5,{8,9,10,11,12,0,0,0,0,0,0,0,0,0,0,0}},
    {false,100,60,0,2,{13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {false,110,60,0,2,{15,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {false,120,60,0,2,{17,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {false,200,60,0,2,{19,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {false,210,60,0,2,{21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
};


void  PUSService3::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(5):
                    Exec3_5TC(TC,List);
                    break;
                case(6):
                    Exec3_6TC(TC,List);
                    break;
                case(31):
                    Exec3_31TC(TC,List);
                    break;
                default:
                  List.Add(1,8);
  }
}

bool PUSService3::GetSIDIndex(uint16_t SID, uint8_t &index){
  bool encontrado=false;
  for (int j=0; ((j<PUS_SERVICE3_SID_NUMBER)&&!encontrado) ; j++ ){
           if(SID==HKConfig[j].SID)
             {
               index=j;
               encontrado=true;
           }
  }
  return encontrado;
}

void PUSService3::ExecEnableConfigTC(CDTCDescriptor &TC, CDTMList &List,
                                 bool newEnableConfig){

  uint8_t index;
  byte_t *aux=TC.appData;
  uint16_t SID=GetUInt16(aux);

  if(GetSIDIndex(SID,index)){
      HKConfig[index].enabled=newEnableConfig;
      HKConfig[index].intervalControl=0;
      List.Add(1,7);
  }else{
      List.Add(1,8);
  }

}

void PUSService3::Exec3_5TC( CDTCDescriptor &TC, CDTMList &List){

  ExecEnableConfigTC(TC, List,true);

}
void PUSService3::Exec3_6TC( CDTCDescriptor &TC, CDTMList &List){

  ExecEnableConfigTC(TC, List,false);


}
void PUSService3::Exec3_31TC( CDTCDescriptor &TC, CDTMList &List){
   uint8_t index;
   byte_t *aux=TC.appData;
   uint16_t SID=GetUInt16(aux);

   if(GetSIDIndex(SID,index)){
       uint16_t interval=GetUInt16(aux);
       HKConfig[index].interval=interval;
       printf("Cambio SID % i period a %i\n", index, HKConfig[index].interval);
       List.Add(1,7);
   }else{
       List.Add(1,8);
   }

}


void PUSService3::DoHK(CDTMList &List){

  printf("Do_HK\n");

  for (int i=0; i < PUS_SERVICE3_SID_NUMBER ; i++){
      if(HKConfig[i].enabled){
          HKConfig[i].intervalControl++;
          if(HKConfig[i].intervalControl>=HKConfig[i].interval){
              uint8_t aux[256];
              byte_t *auxP=aux;

              SetUInt16(HKConfig[i].SID,auxP);
              for(int j=0; j < HKConfig[i].ParamNum; j++){

                  SetUInt64(
                     PUSServices::DATAPOOL_PARAMCurrentValue[HKConfig[i].ParamDef[j]]
                     ,auxP);

              }

              List.Add(3,25,aux);
              HKConfig[i].intervalControl=0;
          }
      }
  }


}

