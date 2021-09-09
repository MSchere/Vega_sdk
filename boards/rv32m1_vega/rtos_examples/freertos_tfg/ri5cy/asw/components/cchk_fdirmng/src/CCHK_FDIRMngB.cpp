#include <public/cchk_fdirmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCHK_FDIRMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCHK_FDIRMng &act,
	 CDRecovAction & EDROOMpVarVCurrentRecAction,
	 CDTMList & EDROOMpVarVCurrentTMList,
	 Pr_Time & EDROOMpVarVNextTimeout,
	 CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList,
	 CEDROOMPOOLCDRecovAction & EDROOMpPoolCDRecovAction ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	HK_FDIRCtrl(EDROOMcomponent.HK_FDIRCtrl),
	TMChannelCtrl(EDROOMcomponent.TMChannelCtrl),
	HK_FDIR_Timer(EDROOMcomponent.HK_FDIR_Timer),
	VCurrentRecAction(EDROOMpVarVCurrentRecAction),
	VCurrentTMList(EDROOMpVarVCurrentTMList),
	VNextTimeout(EDROOMpVarVNextTimeout),
	EDROOMPoolCDTMList(EDROOMpPoolCDTMList),
	EDROOMPoolCDRecovAction(EDROOMpPoolCDRecovAction)
{
}

CCHK_FDIRMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	HK_FDIRCtrl(context.HK_FDIRCtrl),
	TMChannelCtrl(context.TMChannelCtrl),
	HK_FDIR_Timer(context.HK_FDIR_Timer),
	VCurrentRecAction(context.VCurrentRecAction),
	VCurrentTMList(context.VCurrentTMList),
	VNextTimeout(context.VNextTimeout),
	EDROOMPoolCDTMList(context.EDROOMPoolCDTMList ),
	EDROOMPoolCDRecovAction(context.EDROOMPoolCDRecovAction )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCHK_FDIRMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FDoHK_FDIR()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
 CDEventList eventList;
 VNextTimeout+=Pr_Time(1,0);
 time=VNextTimeout;
 PUSService3::DoHK(VCurrentTMList);
 PUSService12::DoMonitoring(VCurrentTMList, eventList);
 PUSService19::QueueEventListRecAct(eventList); 
   //Program absolute timer 
   HK_FDIR_Timer.InformAt( time ); 
}



void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FExecHK_FDIR_TC()

{
   //Handle Msg->data
  CDTCDescriptor & varSHK_FDIR_TC = *(CDTCDescriptor *)Msg->data;
	
		// Data access
	
 CDEventList TCExecEventList;
 PUS_HK_FDIRTC::ExecTC(varSHK_FDIR_TC,VCurrentTMList,TCExecEventList);

}



void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FGetNextRecAction()

{

 PUSService19::GetNextRecAction(VCurrentRecAction);

}



void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FInitHK_FDIR()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
	 
  time.GetTime(); // Get current monotonic time
  time+=Pr_Time(1,0);
  VNextTimeout=time;
   //Program absolute timer 
   HK_FDIR_Timer.InformAt( time ); 
}



void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FSendRecAction()

{
   //Allocate data from pool
  CDRecovAction * pSRecAction_Data = EDROOMPoolCDRecovAction.AllocData();
	
		// Complete Data 
	
	
*pSRecAction_Data=VCurrentRecAction;   
   //Send message 
   HK_FDIRCtrl.send(SRecAction,pSRecAction_Data,&EDROOMPoolCDRecovAction); 
}



void	CCHK_FDIRMng::EDROOM_CTX_Top_0::FTxTMList()

{
   //Allocate data from pool
  CDTMList * pSTxTM_Data = EDROOMPoolCDTMList.AllocData();
	
		// Complete Data 
	
	*pSTxTM_Data=VCurrentTMList;
 
	VCurrentTMList.Clear();
   //Invoke synchronous communication 
   MsgBack=TMChannelCtrl.invoke(STxTM,pSTxTM_Data,&EDROOMPoolCDTMList); 
}



bool	CCHK_FDIRMng::EDROOM_CTX_Top_0::GSendRecAction()

{

return (!PUSService19::IsRecActQueueEmpty());

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDTMList

CCHK_FDIRMng::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::CEDROOMPOOLCDTMList(
			TEDROOMUInt32 elemCount,CDTMList* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTMList))
{
}

CDTMList *	CCHK_FDIRMng::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::AllocData()
{
	return(CDTMList*)CEDROOMProtectedMemoryPool::AllocData();
}

	//CEDROOMPOOLCDRecovAction

CCHK_FDIRMng::EDROOM_CTX_Top_0::CEDROOMPOOLCDRecovAction::CEDROOMPOOLCDRecovAction(
			TEDROOMUInt32 elemCount,CDRecovAction* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDRecovAction))
{
}

CDRecovAction *	CCHK_FDIRMng::EDROOM_CTX_Top_0::CEDROOMPOOLCDRecovAction::AllocData()
{
	return(CDRecovAction*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCHK_FDIRMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCHK_FDIRMng&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VCurrentRecAction,
			VCurrentTMList,
			VNextTimeout,
			EDROOMPoolCDTMList,
			EDROOMPoolCDRecovAction),
		EDROOMPoolCDTMList(
			10, pEDROOMMemory->poolCDTMList,
			pEDROOMMemory->poolMarkCDTMList),
		EDROOMPoolCDRecovAction(
			10, pEDROOMMemory->poolCDRecovAction,
			pEDROOMMemory->poolMarkCDRecovAction)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCHK_FDIRMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				//Execute Action 
				FInitHK_FDIR();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is ExecTC
			case (ExecTC):
				//Msg->Data Handling 
				FExecHK_FDIR_TC();
				//Invoke Synchronous Message 
				FTxTMList();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point DoHK_FDIR
			case (DoHK_FDIR):

				//Execute Action 
				FDoHK_FDIR();
				//Invoke Synchronous Message 
				FTxTMList();
				//Evaluate Branch SendRecAction
				if( GSendRecAction() )
				{
					//Execute Action 
					FGetNextRecAction();
					//Send Asynchronous Message 
					FSendRecAction();

					//Branch taken is DoHK_FDIR_SendRecAction
					edroomCurrentTrans.localId =
						DoHK_FDIR_SendRecAction;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Default Branch NoRecAction
				else
				{

					//Branch taken is DoHK_FDIR_NoRecAction
					edroomCurrentTrans.localId =
						DoHK_FDIR_NoRecAction;

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

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCHK_FDIRMng::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCHK_FDIRMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCHK_FDIRMng::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SHK_FDIR_TC): 

				 if (*Msg->GetPInterface() == HK_FDIRCtrl)
				{

					//Next transition is  ExecTC
					edroomCurrentTrans.localId= ExecTC;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == HK_FDIR_Timer)
				{

					//Next transition is  DoHK_FDIR
					edroomCurrentTrans.localId = DoHK_FDIR;
					edroomCurrentTrans.distanceToContext = 0 ;
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



