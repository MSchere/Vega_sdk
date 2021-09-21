

#include <public/ccepdmanager_iface_v1.h>



	// ******************* HANDLING IRQ 45********************

Pr_IRQEvent	CCEPDManager::EDROOMEventIRQ45(45);
Pr_SemaphoreBin	CCEPDManager::EDROOMSemEndIRQ45(0);


		// ******************* DATA ***************

CDTCDescriptor	CCEPDManager::	EDROOMVarIRQ45;


		// ******************* DATA POOL *******

CCEPDManager::CEDROOMPOOLIRQ45CDTCDescriptor	CCEPDManager::EDROOMPoolIRQ45;


		// ******************* Aux IRQ Handler **************

void 	CCEPDManager::EDROOMIRQ45HandlerTopHalfFunction(void){

	bool EDROOMIRQ45BottomHalfSignal=true;
	//if error

	//EDROOMIRQ45BottomHalfSignal=false;
	
	//EDROOMIRQ18BottomHalfSignal=EDROOMVarIRQ45.HandleIRQ();

	if (EDROOMIRQ45BottomHalfSignal)
		EDROOMEventIRQ45.Signal();

}



		// ******************* IRQ Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ45Handler(void){

	EDROOMIRQ45HandlerTopHalfFunction();

}



		// ******************* IRQ Idle Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ45IdleHandler(void){

}



		// ******************* Bottom Half Task **************

Pr_TaskRV_t 	CCEPDManager::EDROOMIRQ45BottomHalfTask(Pr_TaskP_t){

	bool endTask=false;

	do
	{

		EDROOMEventIRQ45.Wait();

		bool EDROOMIRQ45SendMsgToCmp=true;

		if(!EDROOMSemEndIRQ45.WaitCond()){

			GetNextTC(&EDROOMVarIRQ45);

			if(EDROOMIRQ45SendMsgToCmp){
				CDTCDescriptor	*pEDROOMVarIRQ;

				pEDROOMVarIRQ=EDROOMPoolIRQ45.AllocData();

				*pEDROOMVarIRQ=EDROOMVarIRQ45;

				//RxTC.NewIRQMsg(EDROOMIRQsignal, pEDROOMVarIRQ, &EDROOMPoolIRQ45);

			}
			Pr_IRQManager::EnableIRQ(45);

		}else endTask=1;

	}while(!endTask);

}



		// ******************* IRQPort **************

CEDROOMIRQInterface CCEPDManager::RxTC( 
		CCEPDManager::EDROOMIRQ45Handler
		,CCEPDManager::EDROOMIRQ45IdleHandler
		,CCEPDManager::EDROOMEventIRQ45
		,CCEPDManager::EDROOMSemEndIRQ45
		,45 );




// ******************************* CONSTRUCTOR ************************************



CCEPDManager::CCEPDManager(TEDROOMComponentID id,
		TEDROOMUInt32 roomNumMaxMens,
		TEDROOMPriority roomtaskPrio,
		TEDROOMStackSizeType roomStack,
		CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,
				roomtaskPrio,roomStack, pActorMemory ),

		// ***************   BOTTOM HALF IRQ TASKS  ********************

		EDROOMIRQ45BottomHalfT( EDROOMIRQ45BottomHalfTask,EDROOMprioURGENT,256),

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

