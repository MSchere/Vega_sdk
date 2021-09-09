/*
 * sc_channel_drv.c
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */


#include <public/sc_channel_drv_iface_v1.h>
#include <public/emu_sc_channel_drv_slib_v1.h>
#include <stdio.h>


CDTCDescriptor currentTC;

char * currentTCBrief=NULL;

void Init_sc_channel(){}


void GetNextTC(CDTCDescriptor *tc){

  *tc=currentTC;

}

void SetNextTC(CDTCDescriptor *tc){

  currentTC=*tc;

}

void SendTM(CDTM * tm){

  printf("Send TM (%i,%i)",tm->dataFieldHeader.service
      ,tm->dataFieldHeader.subservice);

  switch (tm->dataFieldHeader.service){
    case(3):
        switch (tm->dataFieldHeader.subservice){
          case(25):
            uint8_t param_num=0;
            uint8_t index;
            uint16_t SID;
            SID=Serializer::GetUInt16(tm->appData);
            printf(" SID %i Params:",SID);
            for(int i=0; i< PUS_SERVICE3_SID_NUMBER;i++){
              if(SID==PUSService3::HKConfig[i].SID){
                  param_num=PUSService3::HKConfig[i].ParamNum;

              }
            }
            index=2;
            while(param_num){
                uint64_t aux=Serializer::GetUInt64(tm->appData+index);
                printf(" %i ",(int32_t)aux);
                index+=8;

                param_num--;
            }


          break;
        }
      break;

      case(5):
        printf(" RID %x",Serializer::GetUInt16(tm->appData));
      break;

      case(20):
        switch (tm->dataFieldHeader.subservice){
          case(2):

            printf(" Param %i = ",Serializer::GetUInt16(tm->appData));
            uint64_t aux=Serializer::GetUInt64(tm->appData+2);
            printf("%i",(int32_t)aux);
          break;

        }

      break;
  }

  printf("\n");
}

void SendTMList(CDTMList * tm){
  for(uint8_t i=0; i < tm->GetTMNumber(); i++){
   SendTM(tm->GetTM(i));

  }

}


void EmuPassSecond(){

  //Emulate Hw TimeCode reception
  PUSService9::CurrentUniTimeY2KSecns=PUSService9::NextUniTimeY2KSecns;
  PUSService9::NextUniTimeY2KSecns++;
  printf("Current UniTime is = %i\n\n",PUSService9::CurrentUniTimeY2KSecns);

  SendProgrammedTCs();

  //CCSensorManager::EDROOMEventIRQ5.SignalFromTask();
}

void SendProgrammedTCs(){
  while(ProgramTC::GetTCProgramed(PUSService9::CurrentUniTimeY2KSecns
                                        ,currentTC,currentTCBrief)){

        printf("Next TC(%i,%i) ",
               currentTC.dataFieldHeader.service,
               currentTC.dataFieldHeader.subservice);
        if(currentTCBrief)
          printf(currentTCBrief);

        printf("\n");

        //Signal BottomHalf for TimeCode Interrupt

        CCEPDManager::EDROOMEventIRQ18.SignalFromTask();
        Pr_DelayIn(Pr_Time(0,20000));

    }
}

ProgramTC *ProgramTC::firstProgram=NULL;

ProgramTC::ProgramTC(uint32_t uniTime2YK,uint8_t service, uint8_t subservice,
                       char *brief){

  UniTime2YK=uniTime2YK;
  TC.dataFieldHeader.service=service;
  TC.dataFieldHeader.subservice=subservice;
  mBrief=brief;
  pAppData=TC.appData;
}


bool ProgramTC::GetTCProgramed(uint32_t uniTime2YK,
                             CDTCDescriptor &TC,
                             char * &brief){
  bool encontrado=false;
  if(firstProgram){
      if(firstProgram->UniTime2YK<=uniTime2YK){
          TC=firstProgram->TC;
          brief=firstProgram->mBrief;
          firstProgram=firstProgram->next;
          encontrado=true;
      }
  }
  return encontrado;
}


void ProgramTC::NewProgram(ProgramTC *pTC){
 if(pTC){

   if(NULL==ProgramTC::firstProgram){
      ProgramTC::firstProgram=pTC;
      pTC->next=NULL;
   }else{
      bool encontrado=false;
      ProgramTC *current;
      ProgramTC *prev=NULL;
      current=ProgramTC::firstProgram;
      while(!encontrado){
          if(current->UniTime2YK > pTC->UniTime2YK){
              if(prev){
                 prev->next=pTC;
              }else{
                  ProgramTC::firstProgram=pTC;
              }
              pTC->next=current;
              encontrado=true;
          }else{
              prev=current;
              current=current->next;
              if(NULL==current){
                  prev->next=pTC;
                  pTC->next=NULL;
                  encontrado=true;
              }
          }
      }
   }
 }
}



