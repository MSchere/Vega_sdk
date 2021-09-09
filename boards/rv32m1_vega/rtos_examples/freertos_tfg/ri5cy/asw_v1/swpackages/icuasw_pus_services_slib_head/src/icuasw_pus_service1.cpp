/*
 * icuasw_pus_service1.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: user
 */


#include <public/icuasw_pus_services_iface_v1.h>


bool_t  PUSService1::AcceptTC( CDTCDescriptor &TC, CDTMList &List){

  bool_t accepted=false;

  TC.tcexecCtrl=ExecAsPrioTC;

  switch(TC.dataFieldHeader.service){

    case(3):
        TC.tcexecCtrl=ExecAsHK_FDIRTC;

        switch(TC.dataFieldHeader.subservice){
          case(5):
          case(6):
          case(129):
          accepted=true;
          break;
          default:
            accepted=false;
        }
      break;
    case(5):
        TC.tcexecCtrl=ExecAsHK_FDIRTC;
        switch(TC.dataFieldHeader.subservice){
              case(5):
              case(6):
              //accepted=true;
              break;
              default:
                accepted=false;
            }
      break;
    case(6):
        TC.tcexecCtrl=ExecAsBKGTC;
        switch(TC.dataFieldHeader.subservice){
              case(2):
              case(5):
              case(9):
              //accepted=true;
            break;
              default:
                accepted=false;
            }
      break;
    case(9):
        TC.tcexecCtrl=ExecAsPrioTC;
        switch(TC.dataFieldHeader.subservice){
              case(129):
              accepted=true;
              break;
              default:
                accepted=false;
            }
      break;
    case(12):
          switch(TC.dataFieldHeader.subservice){
                  case(1):
                  case(2):
                  case(5):
                  case(6):
                  case(7):
                    accepted=true;
                    TC.tcexecCtrl=ExecAsHK_FDIRTC;
                    break;
                  case(8):
                      //accepted=true;
                      TC.tcexecCtrl=ExecAsBKGTC;
                  break;
                  default:
                    accepted=false;
          }
       break;
     case(17):
        TC.tcexecCtrl=ExecAsPrioTC;
        switch(TC.dataFieldHeader.subservice){
              case(1):
              accepted=true;
              break;
              default:
                accepted=false;
            }
      break;
    case(19):
        TC.tcexecCtrl=ExecAsHK_FDIRTC;
        switch(TC.dataFieldHeader.subservice){
              case(1):
              case(2):
              case(4):
              case(5):
              accepted=true;
              break;
              default:
                accepted=false;
            }
      break;
    case(21):
        TC.tcexecCtrl=ExecAsSensorMngTC;
        switch(TC.dataFieldHeader.subservice){
              case(1):
              case(2):
              case(128):
              //accepted=true;
              break;
              default:
                accepted=false;
            }
      break;
     case(128):
      switch(TC.dataFieldHeader.subservice){
              case(1):
                  TC.tcexecCtrl=ExecAsChangeModeTC;
                break;
              case(3):
                  TC.tcexecCtrl=ExecAsResetTC;
              	  accepted=true;
                break;
              case(2):
              case(4):
              case(5):
                  TC.tcexecCtrl=ExecAsBKGTC;
                  accepted=true;
              break;
              default:
                accepted=false;
      }
      break;
    default:
      accepted=false;
  }

  if(accepted)
    List.Add(1,1);
  else
    List.Add(1,2);

  return accepted;
}

