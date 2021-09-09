/*
 * emu_sc_channel_drv_slib_v1.h
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */

#ifndef EMU_SC_CHANNEL_DRV_SLIB_V1_H_
#define EMU_SC_CHANNEL_DRV_SLIB_V1_H_


#include <public/ccepdmanager_iface_v1.h>
//#include <public/ccsensormanager_iface_v1.h>


void EmuPassSecond();

void SendProgrammedTCs();

class ProgramTC{

protected:
  CDTCDescriptor TC;
  uint32_t UniTime2YK;
  ProgramTC *next;
  char * mBrief;
  static ProgramTC *firstProgram;

  byte_t *pAppData;


  static void NewProgram(ProgramTC *);

  ProgramTC(uint32_t uniTime2YK,
            uint8_t service,
            uint8_t subservice,
            char * brief);
public:
  static bool GetTCProgramed(uint32_t uniTime2YK,
                                 CDTCDescriptor &TC,
                                 char * &brief);

protected:

  void SetUInt8(uint8_t & data){
     *pAppData=data;
     pAppData+=1;
  }
  void SetUInt16(uint16_t & data){
    Serializer::SetUInt16(data, pAppData);
    pAppData+=2;
  }

  void SetUInt32(uint32_t & data){
    Serializer::SetUInt32(data, pAppData);
    pAppData+=4;
  }
  void SetUInt64(uint64_t & data){
    Serializer::SetUInt64(data, pAppData);
    pAppData+=8;
  }

  void SetInt8(int8_t & data){
     *pAppData=(uint8_t)data;
     pAppData+=1;
  }
  void SetInt16(int16_t & data){
    Serializer::SetInt16(data, pAppData);
    pAppData+=2;
  }

  void SetInt32(int32_t & data){
    Serializer::SetInt32(data, pAppData);
    pAppData+=4;
  }
  void SetInt64(int64_t & data){
    Serializer::SetInt64(data, pAppData);
    pAppData+=8;
  }

};

#include <public/emu_sc_pus_service3.h>
#include <public/emu_sc_pus_service6.h>
#include <public/emu_sc_pus_service9.h>
#include <public/emu_sc_pus_service12.h>
#include <public/emu_sc_pus_service17.h>
#include <public/emu_sc_pus_service19.h>
#include <public/emu_sc_pus_service20.h>
#include <public/emu_sc_pus_service128.h>


#endif /* EMU_SC_CHANNEL_DRV_SLIB_V1_H_ */
