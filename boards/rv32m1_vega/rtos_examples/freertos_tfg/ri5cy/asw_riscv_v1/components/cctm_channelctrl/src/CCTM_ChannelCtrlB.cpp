#include <public/cctm_channelctrl_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCTM_ChannelCtrl::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCTM_ChannelCtrl &act ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	TMChannelCtrl3(EDROOMcomponent.TMChannelCtrl3),
	TMChannelCtrl2(EDROOMcomponent.TMChannelCtrl2),
	TMChannelCtrl(EDROOMcomponent.TMChannelCtrl)
{
}

CCTM_ChannelCtrl::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	TMChannelCtrl3(context.TMChannelCtrl3),
	TMChannelCtrl2(context.TMChannelCtrl2),
	TMChannelCtrl(context.TMChannelCtrl)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCTM_ChannelCtrl::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCTM_ChannelCtrl::EDROOM_CTX_Top_0::FReplyTMQueued()

{

   //Reply synchronous communication
   Msg->reply(STMQueued); 
}



void	CCTM_ChannelCtrl::EDROOM_CTX_Top_0::FSendTMList()

{
   //Handle Msg->data
  CDTMList & varSTxTM = *(CDTMList *)Msg->data;
	
		// Data access
	
	SendTMList(&varSTxTM);

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCTM_ChannelCtrl::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCTM_ChannelCtrl&act):
		EDROOM_CTX_Top_0(act)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCTM_ChannelCtrl::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
			//Next Transition is TxTM
			case (TxTM):
				//Msg->Data Handling 
				FSendTMList();
				//Reply Synchronous Message 
				FReplyTMQueued();
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

void CCTM_ChannelCtrl::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCTM_ChannelCtrl::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CCTM_ChannelCtrl::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (STxTM): 

				 {
					//Next transition is  TxTM
					edroomCurrentTrans.localId= TxTM;
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



