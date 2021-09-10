#include <public/ccbkgtcexec_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCBKGTCExec::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCBKGTCExec &act,
	 CDEventList & EDROOMpVarVCurrentEvList,
	 CDTMList & EDROOMpVarVCurrentTMList,
	 CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	BKGExecCtrl(EDROOMcomponent.BKGExecCtrl),
	TMChannelCtrl(EDROOMcomponent.TMChannelCtrl),
	VCurrentEvList(EDROOMpVarVCurrentEvList),
	VCurrentTMList(EDROOMpVarVCurrentTMList),
	EDROOMPoolCDTMList(EDROOMpPoolCDTMList)
{
}

CCBKGTCExec::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	BKGExecCtrl(context.BKGExecCtrl),
	TMChannelCtrl(context.TMChannelCtrl),
	VCurrentEvList(context.VCurrentEvList),
	VCurrentTMList(context.VCurrentTMList),
	EDROOMPoolCDTMList(context.EDROOMPoolCDTMList )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCBKGTCExec::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCBKGTCExec::EDROOM_CTX_Top_0::FExecBKGTC()

{
   //Handle Msg->data
  CDTCDescriptor & varSBKGTC = *(CDTCDescriptor *)Msg->data;
	
		// Data access
	
	PUS_BKGTC::ExecTC(varSBKGTC,VCurrentTMList,VCurrentEvList);

}



void	CCBKGTCExec::EDROOM_CTX_Top_0::FTxTMList()

{
   //Allocate data from pool
  CDTMList * pSTxTM_Data = EDROOMPoolCDTMList.AllocData();
	
		// Complete Data 
	
	*pSTxTM_Data=VCurrentTMList;    
	VCurrentTMList.Clear();
   //Invoke synchronous communication 
   MsgBack=TMChannelCtrl.invoke(STxTM,pSTxTM_Data,&EDROOMPoolCDTMList); 
}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDTMList

CCBKGTCExec::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::CEDROOMPOOLCDTMList(
			TEDROOMUInt32 elemCount,CDTMList* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTMList))
{
}

CDTMList *	CCBKGTCExec::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::AllocData()
{
	return(CDTMList*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCBKGTCExec::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCBKGTCExec&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VCurrentEvList,
			VCurrentTMList,
			EDROOMPoolCDTMList),
		EDROOMPoolCDTMList(
			10, pEDROOMMemory->poolCDTMList,
			pEDROOMMemory->poolMarkCDTMList)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCBKGTCExec::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
			//Next Transition is ExecTC
			case (ExecTC):
				//Msg->Data Handling 
				FExecBKGTC();
				//Invoke Synchronous Message 
				FTxTMList();
				//Next State is Ready
				edroomNextState = Ready;
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

void CCBKGTCExec::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCBKGTCExec::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CCBKGTCExec::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SBKGTC): 

				 if (*Msg->GetPInterface() == BKGExecCtrl)
				{

					//Next transition is  ExecTC
					edroomCurrentTrans.localId= ExecTC;
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



