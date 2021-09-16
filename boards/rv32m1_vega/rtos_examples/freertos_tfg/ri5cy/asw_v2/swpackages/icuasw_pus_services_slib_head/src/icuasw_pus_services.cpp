/*
 * icuasw_pus_services.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: user
 */


#include <public/icuasw_pus_services_iface_v1.h>

union UINT16Serial_t{
    uint16_t data;
    uint8_t  bytes[2];
};

union UINT32Serial_t{
    uint32_t data;
    uint8_t  bytes[4];
};

union UINT64Serial_t{
    uint64_t data;
    uint8_t  bytes[8];
};

union INT16Serial_t{
    int16_t data;
    uint8_t  bytes[2];
};

union INT32Serial_t{
    int32_t data;
    uint8_t  bytes[4];
};

union INT64Serial_t{
    int64_t data;
    uint8_t  bytes[8];
};



  uint16_t Serializer::GetUInt16(byte_t * aux){
    UINT16Serial_t serializer;
    if(aux){
      #ifdef BIG_ENDIAN
        serializer.bytes[0]=*aux;
        serializer.bytes[1]=*(aux+1);
      #else
        serializer.bytes[1]=*aux;
        serializer.bytes[0]=*(aux+1);
      #endif
    }
    return serializer.data;

  }

  uint32_t Serializer::GetUInt32(byte_t * aux){
    UINT32Serial_t serializer;
    if(aux){
        #ifdef BIG_ENDIAN
        for(int i=0; i < 4; i ++)
          serializer.bytes[i]=*(aux+i);
       #else
        for(int i=0; i < 4; i ++)
          serializer.bytes[3-i]=*(aux+i);
      #endif
    }
    return serializer.data;
  }

  uint64_t Serializer::GetUInt64(byte_t * aux){
    UINT64Serial_t serializer;
    if(aux){
       #ifdef BIG_ENDIAN
        for(int i=0; i < 8; i ++)
          serializer.bytes[i]=*(aux+i);
       #else
        for(int i=0; i < 8; i ++)
          serializer.bytes[7-i]=*(aux+i);
      #endif
    }
    return serializer.data;
  }

  int16_t Serializer::GetInt16(byte_t * aux){
    INT16Serial_t serializer;
      if(aux){
        #ifdef BIG_ENDIAN
          serializer.bytes[0]=*aux;
          serializer.bytes[1]=*(aux+1);
        #else
          serializer.bytes[1]=*aux;
          serializer.bytes[0]=*(aux+1);
        #endif
      }
      return serializer.data;
  }

  int32_t Serializer::GetInt32(byte_t * aux){
    INT32Serial_t serializer;
    if(aux){
        #ifdef BIG_ENDIAN
        for(int i=0; i < 4; i ++)
          serializer.bytes[i]=*(aux+i);
       #else
        for(int i=0; i < 4; i ++)
          serializer.bytes[3-i]=*(aux+i);
      #endif
    }
    return serializer.data;
  }

  int64_t Serializer::GetInt64(byte_t * aux){
    INT64Serial_t serializer;
    if(aux){
        #ifdef BIG_ENDIAN
        for(int i=0; i < 8; i ++)
          serializer.bytes[i]=*(aux+i);
       #else
        for(int i=0; i < 8; i ++)
          serializer.bytes[7-i]=*(aux+i);
      #endif
    }
    return serializer.data;
  }

void Serializer::SetUInt16(uint16_t data , byte_t * aux){
    UINT16Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        *aux=serializer.bytes[0];
        *(aux+1)=serializer.bytes[1];
      #else
        *aux=serializer.bytes[1];
        *(aux+1)=serializer.bytes[0];
      #endif
    }
  }

  void Serializer::SetUInt32(uint32_t data,byte_t * aux){
    UINT32Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        for(int i=0; i < 4; i ++)
          *(aux+i)=serializer.bytes[i];
       #else
        for(int i=0; i < 4; i ++)
          *(aux+i)=serializer.bytes[3-i];
      #endif
    }
  }

  void Serializer::SetUInt64(uint64_t data, byte_t * aux){
    UINT64Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        for(int i=0; i < 8; i ++)
          *(aux+i)=serializer.bytes[i];
       #else
        for(int i=0; i < 8; i ++)
          *(aux+i)=serializer.bytes[7-i];
      #endif
    }
  }

  void Serializer::SetInt16(int16_t data, byte_t * aux){
    INT16Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        *aux=serializer.bytes[0];
        *(aux+1)=serializer.bytes[1];
      #else
        *aux=serializer.bytes[1];
        *(aux+1)=serializer.bytes[0];
      #endif
    }
  }

  void Serializer::SetInt32(int32_t data,byte_t * aux){
    INT32Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        for(int i=0; i < 4; i ++)
          *(aux+i)=serializer.bytes[i];
       #else
        for(int i=0; i < 4; i ++)
          *(aux+i)=serializer.bytes[3-i];
      #endif
    }
  }

  void Serializer::SetInt64(int64_t data, byte_t * aux){

    INT64Serial_t serializer;
    serializer.data=data;
    if(aux){
      #ifdef BIG_ENDIAN
        for(int i=0; i < 8; i ++)
          *(aux+i)=serializer.bytes[i];
       #else
        for(int i=0; i < 8; i ++)
          *(aux+i)=serializer.bytes[7-i];
      #endif
    }
 }


uint64_t PUSServices::DATAPOOL_PARAMCurrentValue[DATAPOOL_PARAMNumber];
