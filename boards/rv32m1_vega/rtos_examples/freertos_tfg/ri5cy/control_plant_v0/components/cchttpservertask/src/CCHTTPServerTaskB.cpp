#include <public/cchttpservertask_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCHTTPServerTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCHTTPServerTask &act,
	 TEDROOMUInt8 & EDROOMpVarCHTTP_TASK_ID,
	 CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	SwWatchdog(EDROOMcomponent.SwWatchdog),
	Timer(EDROOMcomponent.Timer),
	CHTTP_TASK_ID(EDROOMpVarCHTTP_TASK_ID),
	EDROOMPoolTEDROOMUInt8(EDROOMpPoolTEDROOMUInt8)
{
}

CCHTTPServerTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	SwWatchdog(context.SwWatchdog),
	Timer(context.Timer),
	CHTTP_TASK_ID(context.CHTTP_TASK_ID),
	EDROOMPoolTEDROOMUInt8(context.EDROOMPoolTEDROOMUInt8 )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCHTTPServerTask::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCHTTPServerTask::EDROOM_CTX_Top_0::FHTTP_Monitor()

{

printf("\t\t\t\t\t\tHTTP TASK\n");

}



void	CCHTTPServerTask::EDROOM_CTX_Top_0::FIamAlive()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSIamAlive_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSIamAlive_Data=CHTTP_TASK_ID;
   //Send message 
   SwWatchdog.send(SIamAlive,pSIamAlive_Data,&EDROOMPoolTEDROOMUInt8); 
}



void	CCHTTPServerTask::EDROOM_CTX_Top_0::FProgHTTP_Monitor()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
interval = Pr_Time(5,0); // interval of X sec + Y microsec
 
   //Program relative timer 
   Timer.InformIn( interval ); 
}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CCHTTPServerTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(
			TEDROOMUInt32 elemCount,TEDROOMUInt8* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMUInt8))
{
}

TEDROOMUInt8 *	CCHTTPServerTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::AllocData()
{
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCHTTPServerTask::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCHTTPServerTask&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			CHTTP_TASK_ID,
			EDROOMPoolTEDROOMUInt8),
		CHTTP_TASK_ID(1),
		EDROOMPoolTEDROOMUInt8(
			10, pEDROOMMemory->poolTEDROOMUInt8,
			pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCHTTPServerTask::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
			//Next Transition is HTTP_Monitor
			case (HTTP_Monitor):
				//Execute Action 
				FHTTP_Monitor();
				//Send Asynchronous Message 
				FIamAlive();
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
				//Execute Entry Action 
				FProgHTTP_Monitor();
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCHTTPServerTask::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCHTTPServerTask::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CCHTTPServerTask::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  HTTP_Monitor
					edroomCurrentTrans.localId= HTTP_Monitor;
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



