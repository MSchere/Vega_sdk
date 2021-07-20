

#include <public/cccontrolplant_iface_v1.h>





// ******************************* CONSTRUCTOR ************************************



CCControlPlant::CCControlPlant(TEDROOMComponentID id,
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

		edroomTopState(*this,pActorMemory)


{


}


//**************************************************************************
//**************************   PUBLIC METHODS  *****************************



//************************** EDROOMConfig **********************************


int CCControlPlant::EDROOMConfig()
{


 return 0; 
}



//************************** EDROOMStart **********************************

int CCControlPlant::EDROOMStart()
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



void CCControlPlant::EDROOMBehaviour()
{

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




//********************* ComponentIsFinished **********************************


#ifdef _EDROOM_SYSTEM_CLOSE

bool CCControlPlant::EDROOMIsComponentFinished()
{


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}

#endif


//****************** EDROOMMemory::SetMemory *******************************

void CCControlPlant::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ ,
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

