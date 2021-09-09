

#include <public/icuasw_iface_v1.h>





// ******************************* CONSTRUCTOR ************************************



ICUASW::ICUASW(TEDROOMComponentID id,
		TEDROOMUInt32 roomNumMaxMens,
		TEDROOMPriority roomtaskPrio,
		TEDROOMStackSizeType roomStack,
		CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,
				roomtaskPrio,roomStack, pActorMemory ),

		// *********** Timing service access point *********

		EDROOMtimingSAP(this, 3,&pActorMemory->TimingMemory),

		// *******************  Timers  ********************

		Timer(&EDROOMtimingSAP, 2 ),

		// ***************	Top State  *****************

		edroomTopState(*this)


{


}


//**************************************************************************
//**************************   PUBLIC METHODS  *****************************



//************************** EDROOMConfig **********************************


int ICUASW::EDROOMConfig()
{


 return 0; 
}



//************************** EDROOMStart **********************************

int ICUASW::EDROOMStart()
{


	//****************** Timing Task Start*****************

	EDROOMtimingSAP.Start();

	//***************** CEDROOMComponent::EDROOMStart*********

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

	return 0;
}


//**************************************************************************
//***************************    PROTECTED METHODS *************************



//*****************************  EDROOMBehaviour ***************************



void ICUASW::EDROOMBehaviour()
{

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




//********************* ComponentIsFinished **********************************


#ifdef _EDROOM_SYSTEM_CLOSE

bool ICUASW::EDROOMIsComponentFinished()
{


	return ( EPDManager.EDROOMIsComponentFinished() && TM_ChannelCtrl.EDROOMIsComponentFinished() && HK_FDIRMng.EDROOMIsComponentFinished() && BKGTCExec.EDROOMIsComponentFinished() && CEDROOMComponent::EDROOMIsComponentFinished());

}

#endif


//****************** EDROOMMemory::SetMemory *******************************

void ICUASW::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ ,
		CEDROOMMessage * MessagesMem_,
		bool * MessagesMemMarks_,
		TEDROOMUInt32 numberOfNodes_,
		CEDROOMQueue::CQueueNode * QueueNodesMem_,
		bool * QueueNodesMemMarks_)
{

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_,
			numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);

		TimingMemory.SetMemory(3,TimerInf,&TimerInfMarks[0],TimeOutMsgs,&TimeOutMsgsMarks[0]);


}

