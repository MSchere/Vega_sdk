#include <public/ccmonitor_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCMonitor::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCMonitor &act,
	 TEDROOMUInt8 & EDROOMpVarCMONITOR_TASK_ID,
	 CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	SwWatchdog(EDROOMcomponent.SwWatchdog),
	RS232DataStream(EDROOMcomponent.RS232DataStream),
	KeybDataStream(EDROOMcomponent.KeybDataStream),
	Timer(EDROOMcomponent.Timer),
	CMONITOR_TASK_ID(EDROOMpVarCMONITOR_TASK_ID),
	EDROOMPoolTEDROOMUInt8(EDROOMpPoolTEDROOMUInt8)
{
}

CCMonitor::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	SwWatchdog(context.SwWatchdog),
	RS232DataStream(context.RS232DataStream),
	KeybDataStream(context.KeybDataStream),
	Timer(context.Timer),
	CMONITOR_TASK_ID(context.CMONITOR_TASK_ID),
	EDROOMPoolTEDROOMUInt8(context.EDROOMPoolTEDROOMUInt8 )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCMonitor::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCMonitor::EDROOM_CTX_Top_0::FIamAlive()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSIamAlive_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSIamAlive_Data=CMONITOR_TASK_ID;
   //Send message 
   SwWatchdog.send(SIamAlive,pSIamAlive_Data,&EDROOMPoolTEDROOMUInt8); 
}



void	CCMonitor::EDROOM_CTX_Top_0::FProgIamAliveTimer()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 
	interval = Pr_Time(1,0); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCMonitor::EDROOM_CTX_Top_0::FShowKeyb()

{
   //Handle Msg->data
  TEDROOMByte & varSNewChar = *(TEDROOMByte *)Msg->data;
	
		// Data access
 
 
 
printf("                        MONITOR KeybDisplay %c\n",varSNewChar);

}



void	CCMonitor::EDROOM_CTX_Top_0::FShowRS232()

{
   //Handle Msg->data
  TEDROOMByte & varSNewChar = *(TEDROOMByte *)Msg->data;
	
		// Data access
	
 
printf("            MONITOR RS232Display %c\n",varSNewChar);

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CCMonitor::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(
			TEDROOMUInt32 elemCount,TEDROOMUInt8* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMUInt8))
{
}

TEDROOMUInt8 *	CCMonitor::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::AllocData()
{
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCMonitor::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCMonitor&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			CMONITOR_TASK_ID,
			EDROOMPoolTEDROOMUInt8),
		CMONITOR_TASK_ID(4),
		EDROOMPoolTEDROOMUInt8(
			10, pEDROOMMemory->poolTEDROOMUInt8,
			pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCMonitor::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				FProgIamAliveTimer();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is ShowKeybByte
			case (ShowKeybByte):
				//Msg->Data Handling 
				FShowKeyb();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is ShowRS232
			case (ShowRS232):
				//Msg->Data Handling 
				FShowRS232();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is IamAlive
			case (IamAlive):
				//Execute Action 
				FProgIamAliveTimer();
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
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCMonitor::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCMonitor::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CCMonitor::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (SNewChar): 

				 if (*Msg->GetPInterface() == KeybDataStream)
				{

					//Next transition is  ShowKeybByte
					edroomCurrentTrans.localId= ShowKeybByte;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				 else if (*Msg->GetPInterface() == RS232DataStream)
				{

					//Next transition is  ShowRS232
					edroomCurrentTrans.localId= ShowRS232;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == Timer)
				{

					//Next transition is  IamAlive
					edroomCurrentTrans.localId= IamAlive;
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



