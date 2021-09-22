

#include <public/ccepdmanager_iface_v1.h>



	// ******************* HANDLING IRQ 17********************

Pr_IRQEvent	CCEPDManager::EDROOMEventIRQ17(17);
Pr_SemaphoreBin	CCEPDManager::EDROOMSemEndIRQ17(0);


		// ******************* DATA ***************

CDTCDescriptor	CCEPDManager::	EDROOMVarIRQ17;


		// ******************* DATA POOL *******

CCEPDManager::CEDROOMPOOLIRQ17CDTCDescriptor	CCEPDManager::EDROOMPoolIRQ17;


		// ******************* Aux IRQ Handler **************

void 	CCEPDManager::EDROOMIRQ17HandlerTopHalfFunction(void){

	bool EDROOMIRQ17BottomHalfSignal=true;
	//if error

	//EDROOMIRQ17BottomHalfSignal=false;
	
	EDROOMIRQ17BottomHalfSignal=EDROOMVarIRQ17.HandleIRQ();

	if (EDROOMIRQ17BottomHalfSignal)
		EDROOMEventIRQ17.Signal();

}



		// ******************* IRQ Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ17Handler(void){

	EDROOMIRQ17HandlerTopHalfFunction();

}



		// ******************* IRQ Idle Handler **************

Pr_IRQHandler_RetType	CCEPDManager::EDROOMIRQ17IdleHandler(void){

}



		// ******************* Bottom Half Task **************

Pr_TaskRV_t 	CCEPDManager::EDROOMIRQ17BottomHalfTask(Pr_TaskP_t){

	bool endTask=false;

	do
	{

		EDROOMEventIRQ17.Wait();

		bool EDROOMIRQ17SendMsgToCmp=true;

		if(!EDROOMSemEndIRQ17.WaitCond()){

			//GetNextTC(&EDROOMVarIRQ17);

			if(EDROOMIRQ17SendMsgToCmp){
				CDTCDescriptor	*pEDROOMVarIRQ;

				pEDROOMVarIRQ=EDROOMPoolIRQ17.AllocData();

				*pEDROOMVarIRQ=EDROOMVarIRQ17;

				RxTC.NewIRQMsg(EDROOMIRQsignal, pEDROOMVarIRQ, &EDROOMPoolIRQ17);

			}
			Pr_IRQManager::EnableIRQ(17);

		}else endTask=1;

	}while(!endTask);

}



		// ******************* IRQPort **************

CEDROOMIRQInterface CCEPDManager::RxTC( 
		CCEPDManager::EDROOMIRQ17Handler 
		,CCEPDManager::EDROOMIRQ17IdleHandler 
		,CCEPDManager::EDROOMEventIRQ17
		,CCEPDManager::EDROOMSemEndIRQ17
		,17 );




// ******************************* CONSTRUCTOR ************************************



CCEPDManager::CCEPDManager(TEDROOMComponentID id,
		TEDROOMUInt32 roomNumMaxMens,
		TEDROOMPriority roomtaskPrio,
		TEDROOMStackSizeType roomStack,
		CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,
				roomtaskPrio,roomStack, pActorMemory ),

		// ***************   BOTTOM HALF IRQ TASKS  ********************

		EDROOMIRQ17BottomHalfT( EDROOMIRQ17BottomHalfTask,EDROOMprioURGENT,256),

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

