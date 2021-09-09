#include <public/icuasw_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

ICUASW::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(ICUASW &act,
	 Pr_Time & EDROOMpVarVEmuTimeCode ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	Timer(EDROOMcomponent.Timer),
	VEmuTimeCode(EDROOMpVarVEmuTimeCode)
{
}

ICUASW::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	Timer(context.Timer),
	VEmuTimeCode(context.VEmuTimeCode)
{

}

	// EDROOMSearchContextTrans********************************************

bool ICUASW::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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
void * operator new(size_t n)
{
	void * const p = pvPortMalloc(n);
	return p;
}

void operator delete(void * p)
{
	vPortFree(p);
}

void	ICUASW::EDROOM_CTX_Top_0::FEmuPassSecond()

{

 
 EmuPassSecond();
 
 
	

}



void	ICUASW::EDROOM_CTX_Top_0::FInit()

{

for(int i=0; i <256; i++) 
	ForceDataPOOLValue(i,i);
 
//SendProgrammedTCs();

}



void	ICUASW::EDROOM_CTX_Top_0::FProgTimer()

{
   //Define absolute time
  Pr_Time time;
	 
	//Timing Service useful methods
	
  VEmuTimeCode+=Pr_Time(1,0);
 
  time=VEmuTimeCode;
   //Program absolute timer 
   Timer.InformAt( time ); 
}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

ICUASW::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (ICUASW&act):
		EDROOM_CTX_Top_0(act,
			VEmuTimeCode)
{

}

	//***************************** EDROOMBehaviour ********************************

void ICUASW::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
				FInit();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is NextTimeCode
			case (NextTimeCode):
				//Execute Action 
				FEmuPassSecond();
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
				FProgTimer();
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void ICUASW::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId ICUASW::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId ICUASW::EDROOM_SUB_Top_0::EDROOMReadyArrival()
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

					//Next transition is  NextTimeCode
					edroomCurrentTrans.localId= NextTimeCode;
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



