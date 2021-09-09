#include <public/ccepdmanager_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCEPDManager::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCEPDManager &act,
	 CDEventList & EDROOMpVarVCurrentEvList,
	 CDTCDescriptor & EDROOMpVarVCurrentTC,
	 CDTMList & EDROOMpVarVCurrentTMList,
	 CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList,
	 CEDROOMPOOLCDTCDescriptor & EDROOMpPoolCDTCDescriptor ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	BKGExecCtrl(EDROOMcomponent.BKGExecCtrl),
	HK_FDIRCtrl(EDROOMcomponent.HK_FDIRCtrl),
	TMChannelCtrl(EDROOMcomponent.TMChannelCtrl),
	RxTC(EDROOMcomponent.RxTC),
	VCurrentEvList(EDROOMpVarVCurrentEvList),
	VCurrentTC(EDROOMpVarVCurrentTC),
	VCurrentTMList(EDROOMpVarVCurrentTMList),
	EDROOMPoolCDTMList(EDROOMpPoolCDTMList),
	EDROOMPoolCDTCDescriptor(EDROOMpPoolCDTCDescriptor)
{
}

CCEPDManager::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	BKGExecCtrl(context.BKGExecCtrl),
	HK_FDIRCtrl(context.HK_FDIRCtrl),
	TMChannelCtrl(context.TMChannelCtrl),
	RxTC(context.RxTC),
	VCurrentEvList(context.VCurrentEvList),
	VCurrentTC(context.VCurrentTC),
	VCurrentTMList(context.VCurrentTMList),
	EDROOMPoolCDTMList(context.EDROOMPoolCDTMList ),
	EDROOMPoolCDTCDescriptor(context.EDROOMPoolCDTCDescriptor )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCEPDManager::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCEPDManager::EDROOM_CTX_Top_0::FExecPrioTC()

{

 PUS_PrioTC::ExecTC(VCurrentTC,VCurrentTMList,VCurrentEvList);

}



void	CCEPDManager::EDROOM_CTX_Top_0::FFwdBKGTC()

{
   //Allocate data from pool
  CDTCDescriptor * pSBKGTC_Data = EDROOMPoolCDTCDescriptor.AllocData();
	
		// Complete Data 
	
	*pSBKGTC_Data=VCurrentTC;
   //Send message 
   BKGExecCtrl.send(SBKGTC,pSBKGTC_Data,&EDROOMPoolCDTCDescriptor); 
}



void	CCEPDManager::EDROOM_CTX_Top_0::FFwdHK_FDIRTC()

{
   //Allocate data from pool
  CDTCDescriptor * pSHK_FDIR_TC_Data = EDROOMPoolCDTCDescriptor.AllocData();
	
		// Complete Data 
	
	*pSHK_FDIR_TC_Data=VCurrentTC;
   //Send message 
   HK_FDIRCtrl.send(SHK_FDIR_TC,pSHK_FDIR_TC_Data,
                                                    &EDROOMPoolCDTCDescriptor); 
}



void	CCEPDManager::EDROOM_CTX_Top_0::FGetTC()

{
   //Handle Msg->data
  CDTCDescriptor & varEDROOMIRQsignal = *(CDTCDescriptor *)Msg->data;
	
		// Data access
	
	VCurrentTC=varEDROOMIRQsignal;

}



void	CCEPDManager::EDROOM_CTX_Top_0::FHandleRecAction()

{
   //Handle Msg->data
  CDRecovAction & varSRecAction = *(CDRecovAction *)Msg->data;
	
		// Data access
	
 PUSService19::GetRecActionTCDescriptor(varSRecAction, VCurrentTC);

}



void	CCEPDManager::EDROOM_CTX_Top_0::FTxTMList()

{
   //Allocate data from pool
  CDTMList * pSTxTM_Data = EDROOMPoolCDTMList.AllocData();
	
		// Complete Data 
	
	*pSTxTM_Data=VCurrentTMList;    
	VCurrentTMList.Clear();
   //Invoke synchronous communication 
   MsgBack=TMChannelCtrl.invoke(STxTM,pSTxTM_Data,&EDROOMPoolCDTMList); 
}



bool	CCEPDManager::EDROOM_CTX_Top_0::GAcceptTC()

{

return PUSService1::AcceptTC(VCurrentTC,VCurrentTMList);

}



bool	CCEPDManager::EDROOM_CTX_Top_0::GFwdToBKG()

{

return VCurrentTC.IsBKGTC();

}



bool	CCEPDManager::EDROOM_CTX_Top_0::GFwdToHK_FDIR()

{

return VCurrentTC.IsHK_FDIRTC();

}



bool	CCEPDManager::EDROOM_CTX_Top_0::GToReboot()

{

return VCurrentTC.IsRebootTC();

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDTMList

CCEPDManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::CEDROOMPOOLCDTMList(
			TEDROOMUInt32 elemCount,CDTMList* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTMList))
{
}

CDTMList *	CCEPDManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::AllocData()
{
	return(CDTMList*)CEDROOMProtectedMemoryPool::AllocData();
}

	//CEDROOMPOOLCDTCDescriptor

CCEPDManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTCDescriptor::CEDROOMPOOLCDTCDescriptor(
			TEDROOMUInt32 elemCount,CDTCDescriptor* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTCDescriptor))
{
}

CDTCDescriptor *	CCEPDManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTCDescriptor::AllocData()
{
	return(CDTCDescriptor*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCEPDManager::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCEPDManager&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VCurrentEvList,
			VCurrentTC,
			VCurrentTMList,
			EDROOMPoolCDTMList,
			EDROOMPoolCDTCDescriptor),
		EDROOMPoolCDTMList(
			10, pEDROOMMemory->poolCDTMList,
			pEDROOMMemory->poolMarkCDTMList),
		EDROOMPoolCDTCDescriptor(
			10, pEDROOMMemory->poolCDTCDescriptor,
			pEDROOMMemory->poolMarkCDTCDescriptor)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCEPDManager::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point NewRxTC
			case (NewRxTC):

				//Msg->Data Handling 
				FGetTC();
				//Evaluate Branch Accepted
				if( GAcceptTC() )
				{
					//Invoke Synchronous Message 
					FTxTMList();

					//Branch taken is NewRxTC_Accepted
					edroomCurrentTrans.localId =
						NewRxTC_Accepted;

					//Next State is ValidTC
					edroomNextState = ValidTC;
				 } 
				//Default Branch NotAccepted
				else
				{
					//Invoke Synchronous Message 
					FTxTMList();

					//Branch taken is NewRxTC_NotAccepted
					edroomCurrentTrans.localId =
						NewRxTC_NotAccepted;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
			//Next Transition is RecActionTC
			case (RecActionTC):
				//Msg->Data Handling 
				FHandleRecAction();
				//Next State is ValidTC
				edroomNextState = ValidTC;
				break;
			//To Choice Point HandleTC
			case (HandleTC):

				//Evaluate Branch ToReboot
				if( GToReboot() )
				{
					//Execute Action 
					FExecPrioTC();
					//Invoke Synchronous Message 
					FTxTMList();

					//Branch taken is HandleTC_ToReboot
					edroomCurrentTrans.localId =
						HandleTC_ToReboot;

					//Next State is Reboot
					edroomNextState = Reboot;
				 } 
				//Evaluate Branch FwdHK_FDIRTC
				else if( GFwdToHK_FDIR() )
				{
					//Send Asynchronous Message 
					FFwdHK_FDIRTC();

					//Branch taken is HandleTC_FwdHK_FDIRTC
					edroomCurrentTrans.localId =
						HandleTC_FwdHK_FDIRTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch FwdBKGTC
				else if( GFwdToBKG() )
				{
					//Send Asynchronous Message 
					FFwdBKGTC();

					//Branch taken is HandleTC_FwdBKGTC
					edroomCurrentTrans.localId =
						HandleTC_FwdBKGTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Default Branch ExecPrioTC
				else
				{
					//Execute Action 
					FExecPrioTC();
					//Invoke Synchronous Message 
					FTxTMList();

					//Branch taken is HandleTC_ExecPrioTC
					edroomCurrentTrans.localId =
						HandleTC_ExecPrioTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state Ready
			case (Ready):
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

				//Go to the state Reboot
			case (Reboot):
				//Arrival to state Reboot
				edroomCurrentTrans=EDROOMRebootArrival();
				break;

				//Go to the join point ValidTC
			case (ValidTC):
				//Arrival to join point ValidTC
				edroomCurrentTrans=EDROOMValidTCArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCEPDManager::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCEPDManager::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



//	 ***********************************************************************

//	 JoinPoint ValidTC

//	 ***********************************************************************



TEDROOMTransId CCEPDManager::EDROOM_SUB_Top_0::EDROOMValidTCArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  HandleTC
	edroomCurrentTrans.localId = HandleTC;
	edroomCurrentTrans.distanceToContext = 0 ;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCEPDManager::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMIRQsignal): 

				 if (*Msg->GetPInterface() == RxTC)
				{

					//Next transition is  NewRxTC
					edroomCurrentTrans.localId = NewRxTC;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SRecAction): 

				 if (*Msg->GetPInterface() == HK_FDIRCtrl)
				{

					//Next transition is  RecActionTC
					edroomCurrentTrans.localId= RecActionTC;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Reboot

	// ***********************************************************************



TEDROOMTransId CCEPDManager::EDROOM_SUB_Top_0::EDROOMRebootArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



