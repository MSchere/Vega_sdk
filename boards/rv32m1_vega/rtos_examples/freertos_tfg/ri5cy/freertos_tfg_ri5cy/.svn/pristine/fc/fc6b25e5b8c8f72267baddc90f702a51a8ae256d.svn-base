#include <public/ccledtask_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCLEDTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCLEDTask &act,
	 Pr_Time * EDROOMpVarVAliveMsgTimeout,
	 Pr_Time * EDROOMpVarVTaskIsAlive ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	SwWatchdog5(EDROOMcomponent.SwWatchdog5),
	SwWatchdog4(EDROOMcomponent.SwWatchdog4),
	SwWatchdog3(EDROOMcomponent.SwWatchdog3),
	SwWatchdog2(EDROOMcomponent.SwWatchdog2),
	SwWatchdog(EDROOMcomponent.SwWatchdog),
	Timer(EDROOMcomponent.Timer),
	VAliveMsgTimeout(EDROOMpVarVAliveMsgTimeout),
	VTaskIsAlive(EDROOMpVarVTaskIsAlive)
{
}

CCLEDTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	SwWatchdog5(context.SwWatchdog5),
	SwWatchdog4(context.SwWatchdog4),
	SwWatchdog3(context.SwWatchdog3),
	SwWatchdog2(context.SwWatchdog2),
	SwWatchdog(context.SwWatchdog),
	Timer(context.Timer),
	VAliveMsgTimeout(context.VAliveMsgTimeout),
	VTaskIsAlive(context.VTaskIsAlive)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCLEDTask::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		// Check trigger for signal SIamAlive

		 case (SIamAlive): 

				 {
					//Next transition is  TaskIsAlive
					edroomCurrentTrans.localId= TaskIsAlive;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

			 break;

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCLEDTask::EDROOM_CTX_Top_0::FInit()

{

for(int i=0; i<5; i++){
	VAliveMsgTimeout[i]=Pr_Time(2,0);
}
 
 
VAliveMsgTimeout[1]=Pr_Time(6,0);

}



void	CCLEDTask::EDROOM_CTX_Top_0::FLED_OFF()

{

 
 printf("\n\t\t\t\t\tLED OFF\n");

}



void	CCLEDTask::EDROOM_CTX_Top_0::FLED_ON()

{

bool taskAreOK=true;
Pr_Time currentTime;
 
currentTime.GetTime();
for(int i=0; i<5; i++){
	Pr_Time aux;
	aux=VTaskIsAlive[i];
	aux+=VAliveMsgTimeout[i];
	if(aux<currentTime){
		taskAreOK=false;
		printf("\n\t\t\t\t\tTASK %i FAIL\n", i);
 	}
}
 
if( taskAreOK)
 
	printf("\n\t\t\t\t\tLED GREEN ON\n");
 
else
 
	printf("\n\t\t\t\t\tLED RED ON\n");

}



void	CCLEDTask::EDROOM_CTX_Top_0::FProgTimer()

{
   //Define interval
  Pr_Time interval;
	 
	//Timing Service useful methods
	 	
 interval = Pr_Time(3,0); // interval of X sec + Y microsec
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCLEDTask::EDROOM_CTX_Top_0::FTaskIsAlive()

{
   //Handle Msg->data
  TEDROOMUInt8 & varSIamAlive = *(TEDROOMUInt8 *)Msg->data;
	
		// Data access
	
	if(varSIamAlive<5)
 
		VTaskIsAlive[varSIamAlive].GetTime();

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCLEDTask::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCLEDTask&act):
		EDROOM_CTX_Top_0(act,
			VAliveMsgTimeout,
			VTaskIsAlive)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCLEDTask::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				//Execute Actions 
				FInit();
				FProgTimer();
				//Next State is LED_OFF
				edroomNextState = LED_OFF;
				break;
			//Next Transition is Switch_ON
			case (Switch_ON):
				//Execute Actions 
				FLED_ON();
				FProgTimer();
				//Next State is LED_ON
				edroomNextState = LED_ON;
				break;
			//Next Transition is Switch_OFF
			case (Switch_OFF):
				//Execute Actions 
				FLED_OFF();
				FProgTimer();
				//Next State is LED_OFF
				edroomNextState = LED_OFF;
				break;
			//Next Transition is TaskIsAlive
			case (TaskIsAlive):
				//Msg->Data Handling 
				FTaskIsAlive();
				//Memory Transition 
				edroomNextState = edroomCurrentState;
				edroomCurrentTrans.localId = EDROOMMemoryTrans;
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

				//Go to the state LED_OFF
			case (LED_OFF):
				//Arrival to state LED_OFF
				edroomCurrentTrans=EDROOMLED_OFFArrival();
				break;

				//Go to the state LED_ON
			case (LED_ON):
				//Arrival to state LED_ON
				edroomCurrentTrans=EDROOMLED_ONArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCLEDTask::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCLEDTask::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  LED_OFF

	// ***********************************************************************



TEDROOMTransId CCLEDTask::EDROOM_SUB_Top_0::EDROOMLED_OFFArrival()
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

					//Next transition is  Switch_ON
					edroomCurrentTrans.localId= Switch_ON;
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

	// Leaf SubState  LED_ON

	// ***********************************************************************



TEDROOMTransId CCLEDTask::EDROOM_SUB_Top_0::EDROOMLED_ONArrival()
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

					//Next transition is  Switch_OFF
					edroomCurrentTrans.localId= Switch_OFF;
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



