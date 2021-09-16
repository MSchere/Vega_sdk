#ifndef PUBLIC__ICUASW_PUS_SERVICES_IFACE_V1_H
#define PUBLIC__ICUASW_PUS_SERVICES_IFACE_V1_H

#include <public/config.h>
#include <platform/basic_types.h>
#include <public/cdtcdescriptor_iface_v1.h>
#include <public/cdtmlist_iface_v1.h>
#include <public/cdeventlist_iface_v1.h>
#include <public/cdsensortmbufferstatus_iface_v1.h>
#include <public/cdrecovaction_iface_v1.h>

#define DATAPOOL_PARAMNumber 64

class Serializer{

  friend class PUSServices;
  friend class ProgramTC;
  friend void SendTM(CDTM * tm);
protected:
  static uint16_t GetUInt16(byte_t * aux);
  static uint32_t GetUInt32(byte_t * aux);
  static uint64_t GetUInt64(byte_t * aux);

  static int16_t GetInt16(byte_t * aux);
  static int32_t GetInt32(byte_t * aux);
  static int64_t GetInt64(byte_t * aux);

  static void SetUInt16(uint16_t, byte_t * aux);
  static void SetUInt32(uint32_t,byte_t * aux);
  static void SetUInt64(uint64_t, byte_t * aux);

  static void SetInt16(int16_t, byte_t * aux);
  static void SetInt32(int32_t,byte_t * aux);
  static void SetInt64(int64_t, byte_t * aux);


};

class PUSServices{

public:
  static uint64_t DATAPOOL_PARAMCurrentValue[DATAPOOL_PARAMNumber];
protected:
    static uint8_t GetUInt8(byte_t *&pAppData){
          uint8_t data;
          data=*(uint8_t*)pAppData;
          pAppData+=1;
          return data;
    }
    static uint16_t GetUInt16(byte_t *&pAppData){
      uint16_t data;
      data=Serializer::GetUInt16(pAppData);
      pAppData+=2;
      return data;
    }
    static uint32_t GetUInt32(byte_t *&pAppData){
      uint32_t data;
      data=Serializer::GetUInt32(pAppData);
      pAppData+=4;
      return data;
    }
    static uint64_t GetUInt64(byte_t *&pAppData){
      uint64_t data;
      data=Serializer::GetUInt64(pAppData);
      pAppData+=8;
      return data;
    }

    static int8_t GetInt8(byte_t *&pAppData){
        int8_t data;
        data=*(int8_t*)pAppData;
        pAppData+=1;
        return data;
    }

    static int16_t GetInt16(byte_t *&pAppData){
        int16_t data;
        data=Serializer::GetInt16(pAppData);
        pAppData+=2;
        return data;
      }
    static int32_t GetInt32(byte_t *&pAppData){
        int32_t data;
        data=Serializer::GetInt32(pAppData);
        pAppData+=4;
        return data;
     }
    static int64_t GetInt64(byte_t *&pAppData){
        uint64_t data;
        data=Serializer::GetInt64(pAppData);
        pAppData+=8;
        return data;
    }
    static void SetUInt8(uint8_t & data,byte_t *&pAppData){
         *pAppData=data;
         pAppData+=1;
      }
    static void SetUInt16(uint16_t & data,byte_t *&pAppData){
        Serializer::SetUInt16(data, pAppData);
        pAppData+=2;
      }

    static void SetUInt32(uint32_t & data,byte_t *&pAppData){
        Serializer::SetUInt32(data, pAppData);
        pAppData+=4;
      }
    static void SetUInt64(uint64_t & data,byte_t *&pAppData){
        Serializer::SetUInt64(data, pAppData);
        pAppData+=8;
      }

    static void SetInt8(int8_t & data,byte_t *&pAppData){
         *pAppData=(uint8_t)data;
         pAppData+=1;
      }
    static void SetInt16(int16_t & data,byte_t *&pAppData){
        Serializer::SetInt16(data, pAppData);
        pAppData+=2;
      }

    static void SetInt32(int32_t & data,byte_t *&pAppData){
        Serializer::SetInt32(data, pAppData);
        pAppData+=4;
      }
    static void SetInt64(int64_t & data,byte_t *&pAppData){
        Serializer::SetInt64(data, pAppData);
        pAppData+=8;
      }
};

#include <icuasw_pus_services/icuasw_pus_service1.h>
#include <icuasw_pus_services/icuasw_pus_service3.h>
#include <icuasw_pus_services/icuasw_pus_service5.h>
#include <icuasw_pus_services/icuasw_pus_service6.h>
#include <icuasw_pus_services/icuasw_pus_service9.h>
#include <icuasw_pus_services/icuasw_pus_service12.h>
#include <icuasw_pus_services/icuasw_pus_service17.h>
#include <icuasw_pus_services/icuasw_pus_service19.h>
#include <icuasw_pus_services/icuasw_pus_service21.h>
#include <icuasw_pus_services/icuasw_pus_service20.h>
#include <icuasw_pus_services/icuasw_pus_service128.h>





class PUS_PrioTC{

public:
  static void ExecTC( CDTCDescriptor &TC, CDTMList &List,
                               CDEventList & eventList){

    switch(TC.dataFieldHeader.service){

    case(9):
        PUSService9::ExecTC( TC, List);
      break;
    case(17):
        PUSService17::ExecTC( TC, List);
      break;
    case(128):
        PUSService128::ExecTC( TC, List);
      break;
    default:
      List.Add(1,8);
    }
  }
};

 class PUS_HK_FDIRTC {

  public:
    static void ExecTC( CDTCDescriptor &TC, CDTMList &List,
                                CDEventList & eventList){

      switch(TC.dataFieldHeader.service){

      case(3):
          PUSService3::ExecTC( TC, List);
        break;
      case(5):
          PUSService5::ExecTC( TC, List);
        break;
      case(12):
          PUSService12::ExecTC( TC, List);
        break;
      case(19):
          PUSService19::ExecTC( TC, List);
        break;

      default:
        List.Add(1,8);
    }

  }
};

class PUS_BKGTC {

 public:
   static void ExecTC( CDTCDescriptor &TC, CDTMList &List,
                       CDEventList & eventList){

     switch(TC.dataFieldHeader.service){

     case(6):
         PUSService6::ExecTC( TC, List);
       break;
     case(20):
         PUSService20::ExecTC( TC, List);
       break;

     default:
       List.Add(1,8);
     }
   }
 };

class PUS_SensorsTC {

 public:
   static void ExecTC( CDTCDescriptor &TC, CDTMList &List,
                               CDEventList & eventList){

     switch(TC.dataFieldHeader.service){

     case(21):
         PUSService21::ExecTC( TC, List);
       break;
     default:
       List.Add(1,8);
     }
   }
 };

/*PROTECTED REGION END*/



#endif // PUBLIC__CONSOLE_DRV_IFACE_V1_H
