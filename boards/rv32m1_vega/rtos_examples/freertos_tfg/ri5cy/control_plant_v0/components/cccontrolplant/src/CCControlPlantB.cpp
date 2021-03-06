#include <public/cccontrolplant_iface_v1.h>
//New includes for exit() function
#include <stdlib.h>
// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCControlPlant::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCControlPlant &act,
	 TEDROOMUInt8 & EDROOMpVarCCONTROL_PLANT_ID,
	 TEDROOMFloat & EDROOMpVarVKd,
	 TEDROOMFloat & EDROOMpVarVKi,
	 TEDROOMFloat & EDROOMpVarVKp,
	 Pr_Time & EDROOMpVarVNextTimer,
	 CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	SwWatchdog(EDROOMcomponent.SwWatchdog),
	RS232Command(EDROOMcomponent.RS232Command),
	KeybCommand(EDROOMcomponent.KeybCommand),
	Timer(EDROOMcomponent.Timer),
	CCONTROL_PLANT_ID(EDROOMpVarCCONTROL_PLANT_ID),
	VKd(EDROOMpVarVKd),
	VKi(EDROOMpVarVKi),
	VKp(EDROOMpVarVKp),
	VNextTimer(EDROOMpVarVNextTimer),
	EDROOMPoolTEDROOMUInt8(EDROOMpPoolTEDROOMUInt8)
{
}

CCControlPlant::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	SwWatchdog(context.SwWatchdog),
	RS232Command(context.RS232Command),
	KeybCommand(context.KeybCommand),
	Timer(context.Timer),
	CCONTROL_PLANT_ID(context.CCONTROL_PLANT_ID),
	VKd(context.VKd),
	VKi(context.VKi),
	VKp(context.VKp),
	VNextTimer(context.VNextTimer),
	EDROOMPoolTEDROOMUInt8(context.EDROOMPoolTEDROOMUInt8 )
{

}

void * operator new(size_t n)
{
  void * const p = pvPortMalloc(n);
  // handle p == 0
  return p;
}

void operator delete(void * p) //Corrects undefined ref 'operator delete(void*)'
{
	vPortFree(p);
}

	// EDROOMSearchContextTrans********************************************

bool CCControlPlant::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		// Check trigger for signal SUpdateControlParam

		 case (SUpdateControlParam): 

				 {
					//Next transition is  UpdateControlParam
					edroomCurrentTrans.localId= UpdateControlParam;
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

void	CCControlPlant::EDROOM_CTX_Top_0::FApplyControl()

{
   //Define absolute time
  Pr_Time time;
	 
 
 VNextTimer+=Pr_Time(0,500000); // Add X sec + Y microsec
 
 time=VNextTimer;
 
 printf("\n+Apply Control\n");
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	CCControlPlant::EDROOM_CTX_Top_0::FControlAlgorithm()

{
   //Define absolute time
  Pr_Time time;
 
  
  VNextTimer+=Pr_Time(0,500000); // Add X sec + Y microsec
 
  time=VNextTimer;
 
  printf("\n+Req Data Sensor 1\n");
  printf("+Req Data Sensor 2\n");
  printf("+Control Algorithm Kp =%f, Ki=%f, Kd=%f\n", VKp, VKi, VKd);
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	CCControlPlant::EDROOM_CTX_Top_0::FIamAlive()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSIamAlive_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSIamAlive_Data=CCONTROL_PLANT_ID;
   //Send message 
   SwWatchdog.send(SIamAlive,pSIamAlive_Data,&EDROOMPoolTEDROOMUInt8); 
}



void	CCControlPlant::EDROOM_CTX_Top_0::FInitTimer()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
	 
  VNextTimer.GetTime(); // Get current monotonic time
  VNextTimer+=Pr_Time(0,500000); // Add X sec + Y microsec
 
 
  time=VNextTimer;
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	CCControlPlant::EDROOM_CTX_Top_0::FUpdateAlgorithmParam()

{
   //Handle Msg->data
  CDControlParam & varSUpdateControlParam = *(CDControlParam *)Msg->data;
 
 
	switch(varSUpdateControlParam.m_id){
 
		case(CDControlParam::Param_Kp):
			 VKp=varSUpdateControlParam.m_value;
			 printf("\t\t\t\t\t\tUpdate Kp = %f\n",VKp);
 
		break;
	
		case(CDControlParam::Param_Ki):
			VKi=varSUpdateControlParam.m_value;
			printf("\t\t\t\t\t\tUpdate Ki = %f\n",VKi);
		break;
 
		case(CDControlParam::Param_Kd):
			VKd=varSUpdateControlParam.m_value;
			printf("\t\t\t\t\t\tUpdate Kd = %f\n",VKd);
 
		break;
		case(CDControlParam::Param_Exit):
			printf("\t\t\t\t\t\tExit\n");
			exit(0); //Requires stdlib
 
		break;
 
 
	}
 
 

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8
//Member declaration not found
CCControlPlant::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(
			TEDROOMUInt32 elemCount,TEDROOMUInt8* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMUInt8))
{
}

TEDROOMUInt8 *	CCControlPlant::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::AllocData()
{
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCControlPlant::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCControlPlant&act //Warning: Member 'edroomCurrentState' was not initialized in this constructor
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			CCONTROL_PLANT_ID,
			VKd,
			VKi,
			VKp,
			VNextTimer,
			EDROOMPoolTEDROOMUInt8),
		CCONTROL_PLANT_ID(0),
		VKd(0.2),
		VKi(0.25),
		VKp(0.35),
		EDROOMPoolTEDROOMUInt8( //Symbol 'CEDROOMPOOLTEDROOMUInt8' could not be resolved
			10, pEDROOMMemory->poolTEDROOMUInt8,
			pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCControlPlant::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				FInitTimer();
				//Next State is ProgAlgorithmExec
				edroomNextState = ProgAlgorithmExec;
				break;
			//Next Transition is ControlAlgorithm
			case (ControlAlgorithm):
				//Execute Action 
				FControlAlgorithm();
				//Next State is ProgControl
				edroomNextState = ProgControl;
				break;
			//Next Transition is ApplyControl
			case (ApplyControl):
				//Execute Action 
				FApplyControl();
				//Next State is ProgAlgorithmExec
				edroomNextState = ProgAlgorithmExec;
				break;
			//Next Transition is UpdateControlParam
			case (UpdateControlParam):
				//Msg->Data Handling 
				FUpdateAlgorithmParam();
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

				//Go to the state ProgAlgorithmExec
			case (ProgAlgorithmExec):
				//Send Asynchronous Message at Entry
				FIamAlive();
				//Arrival to state ProgAlgorithmExec
				edroomCurrentTrans=EDROOMProgAlgorithmExecArrival();
				break;

				//Go to the state ProgControl
			case (ProgControl):
				//Arrival to state ProgControl
				edroomCurrentTrans=EDROOMProgControlArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCControlPlant::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCControlPlant::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  ProgAlgorithmExec

	// ***********************************************************************



TEDROOMTransId CCControlPlant::EDROOM_SUB_Top_0::EDROOMProgAlgorithmExecArrival()
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

					//Next transition is  ControlAlgorithm
					edroomCurrentTrans.localId= ControlAlgorithm;
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

	// Leaf SubState  ProgControl

	// ***********************************************************************



TEDROOMTransId CCControlPlant::EDROOM_SUB_Top_0::EDROOMProgControlArrival()
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

					//Next transition is  ApplyControl
					edroomCurrentTrans.localId= ApplyControl;
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



