

#include <public/ccepdmanager_iface_v1.h>



	// ******************* HANDLING IRQ 7********************

Pr_IRQEvent	CCEPDManager::EDROOMEventIRQ7(7);
Pr_SemaphoreBin	CCEPDManager::EDROOMSemEndIRQ7(0);


		// ******************* DATA ***************

CDTCDescriptor	CCEPDManager::	EDROOMVarIRQ7;


		// ******************* DATA POOL *******

CCEPDManager::CEDROOMPOOLIRQ7CDTCDescriptor	CCEPDManager::EDROOMPoolIRQ7;


		// ******************* Aux IRQ Handler **************

void 	CCEPDManager::EDROOMIRQ7HandlerTopHalfFunction(void){

	bool EDROOMIRQ7BottomHalfSignal=true;
	//if error

	//EDROOMIRQ7BottomHalfSignal=false;

	if (EDROOMIRQ7BottomHalfSignal)
		EDROOMEventIRQ7.Signal();

}



		// ******************* IRQ Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ7Handler(void){

	EDROOMIRQ7HandlerTopHalfFunction();

}



		// ******************* IRQ Idle Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ7IdleHandler(void){

}



		// ******************* Bottom Half Task **************

Pr_TaskRV_t 	CCEPDManager::EDROOMIRQ7BottomHalfTask(Pr_TaskP_t){

	bool endTask=false;

	do
	{

		EDROOMEventIRQ7.Wait();

		bool EDROOMIRQ7SendMsgToCmp=true;

		if(!EDROOMSemEndIRQ7.WaitCond()){

			GetNextTC(&EDROOMVarIRQ7);

			if(EDROOMIRQ7SendMsgToCmp){
				CDTCDescriptor	*pEDROOMVarIRQ;

				pEDROOMVarIRQ=EDROOMPoolIRQ7.AllocData();

				*pEDROOMVarIRQ=EDROOMVarIRQ7;

				RxTC.NewIRQMsg(EDROOMIRQsignal, pEDROOMVarIRQ, &EDROOMPoolIRQ7);

			}
			Pr_IRQManager::EnableIRQ(7);

		}else endTask=1;

	}while(!endTask);

}



		// ******************* IRQPort **************

CEDROOMIRQInterface CCEPDManager::RxTC( 
		CCEPDManager::EDROOMIRQ7Handler 
		,CCEPDManager::EDROOMIRQ7IdleHandler 
		,CCEPDManager::EDROOMEventIRQ7
		,CCEPDManager::EDROOMSemEndIRQ7
		,7 );




// ******************************* CONSTRUCTOR ************************************



CCEPDManager::CCEPDManager(TEDROOMComponentID id,
		TEDROOMUInt32 roomNumMaxMens,
		TEDROOMPriority roomtaskPrio,
		TEDROOMStackSizeType roomStack,
		CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,
				roomtaskPrio,roomStack, pActorMemory ),

		// ***************   BOTTOM HALF IRQ TASKS  ********************

		EDROOMIRQ7BottomHalfT( EDROOMIRQ7BottomHalfTask,EDROOMprioURGENT,256),

		// ***************	Top State  *****************

		edroomTopState(*this,pActorMemory)


{


}


//**************************************************************************
//**************************   PUBLIC METHODS  *****************************



//************************** EDROOMConfig **********************************


int CCEPDManager::EDROOMConfig()
{


 return 0; 
}



//************************** EDROOMStart **********************************

int CCEPDManager::EDROOMStart()
{


	//***************** CEDROOMComponent::EDROOMStart*********

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

	return 0;
}


//**************************************************************************
//***************************    PROTECTED METHODS *************************



//*****************************  EDROOMBehaviour ***************************



void CCEPDManager::EDROOMBehaviour()
{

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();


		// *************** PUERTOS IRQ ********************

	RxTC.EndIRQHandlerTask();
}




//********************* ComponentIsFinished **********************************


#ifdef _EDROOM_SYSTEM_CLOSE

bool CCEPDManager::EDROOMIsComponentFinished()
{


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}

#endif


//****************** EDROOMMemory::SetMemory *******************************

void CCEPDManager::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ ,
		CEDROOMMessage * MessagesMem_,
		bool * MessagesMemMarks_,
		TEDROOMUInt32 numberOfNodes_,
		CEDROOMQueue::CQueueNode * QueueNodesMem_,
		bool * QueueNodesMemMarks_)
{

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_,
			numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

