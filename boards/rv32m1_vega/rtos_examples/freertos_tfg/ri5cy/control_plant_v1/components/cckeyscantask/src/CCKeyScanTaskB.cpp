#include <public/cckeyscantask_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCKeyScanTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCKeyScanTask &act,
	 TEDROOMUInt8 & EDROOMpVarVAuxIndex,
	 TEDROOMByte * EDROOMpVarVAuxKeybChannel,
	 TEDROOMByte * EDROOMpVarVCommandBuffer,
	 TEDROOMInt8 & EDROOMpVarVCommBufferControl,
	 TEDROOMUInt8 & EDROOMpVarVdummyCounter,
	 TEDROOMUInt8 & EDROOMpVarVIndex,
	 Pr_Time & EDROOMpVarVNextTimer,
	 TEDROOMByte & EDROOMpVarVRxChar,
	 CEDROOMPOOLCDControlParam & EDROOMpPoolCDControlParam,
	 CEDROOMPOOLTEDROOMByte & EDROOMpPoolTEDROOMByte,
	 CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	SwWatchdog(EDROOMcomponent.SwWatchdog),
	Command(EDROOMcomponent.Command),
	MonitorDataStream(EDROOMcomponent.MonitorDataStream),
	Timer(EDROOMcomponent.Timer),
	CKEYB_SCAN_ID(2),
	VAuxIndex(EDROOMpVarVAuxIndex),
	VAuxKeybChannel(EDROOMpVarVAuxKeybChannel),
	VCommandBuffer(EDROOMpVarVCommandBuffer),
	VCommBufferControl(EDROOMpVarVCommBufferControl),
	VdummyCounter(EDROOMpVarVdummyCounter),
	VIndex(EDROOMpVarVIndex),
	VNextTimer(EDROOMpVarVNextTimer),
	VRxChar(EDROOMpVarVRxChar),
	EDROOMPoolCDControlParam(EDROOMpPoolCDControlParam),
	EDROOMPoolTEDROOMByte(EDROOMpPoolTEDROOMByte),
	EDROOMPoolTEDROOMUInt8(EDROOMpPoolTEDROOMUInt8)
{
}

CCKeyScanTask::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	SwWatchdog(context.SwWatchdog),
	Command(context.Command),
	MonitorDataStream(context.MonitorDataStream),
	Timer(context.Timer),
	CKEYB_SCAN_ID(2),
	VAuxIndex(context.VAuxIndex),
	VAuxKeybChannel(context.VAuxKeybChannel),
	VCommandBuffer(context.VCommandBuffer),
	VCommBufferControl(context.VCommBufferControl),
	VdummyCounter(context.VdummyCounter),
	VIndex(context.VIndex),
	VNextTimer(context.VNextTimer),
	VRxChar(context.VRxChar),
	EDROOMPoolCDControlParam(context.EDROOMPoolCDControlParam ),
	EDROOMPoolTEDROOMByte(context.EDROOMPoolTEDROOMByte ),
	EDROOMPoolTEDROOMUInt8(context.EDROOMPoolTEDROOMUInt8 )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCKeyScanTask::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
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

void	CCKeyScanTask::EDROOM_CTX_Top_0::FIamAlive()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSIamAlive_Data = EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSIamAlive_Data=CKEYB_SCAN_ID;
   //Send message 
   SwWatchdog.send(SIamAlive,pSIamAlive_Data,&EDROOMPoolTEDROOMUInt8); 
}



void	CCKeyScanTask::EDROOM_CTX_Top_0::FInit()

{

const char * aux="$Kp=0.5# $Ki=0.3# $exit__#";
 
for(int i=0; i <40; i++)
	VAuxKeybChannel[i]='\0';
 
for(int i=0; ((i <39)&& *(aux+i)!='\0'); i++)
	VAuxKeybChannel[i]=*(aux+i);
 
 
VNextTimer.GetTime();

}



void	CCKeyScanTask::EDROOM_CTX_Top_0::FProgNextScan()

{
   //Define absolute time
  Pr_Time time;
 
 
	VNextTimer+=Pr_Time(1,500000);
 
	time=VNextTimer;
   //Program absolute timer 
   Timer.InformAt( time ); 
}



void	CCKeyScanTask::EDROOM_CTX_Top_0::FScanKeyb()

{

 
  VdummyCounter++;
 
  if((VAuxIndex<40)&&(VdummyCounter>15)){
	
	VRxChar=VAuxKeybChannel[VAuxIndex];
	VAuxIndex++;	
	
 
	if(0==VCommBufferControl){
 
		if(VRxChar=='#')
			VCommBufferControl=1;
		else if(VIndex<7){
		
			VCommandBuffer[VIndex]=VRxChar;
			VIndex++;
		}
 
	}
 
	if(VRxChar=='$'){
		VIndex=0;
		VCommBufferControl=0;
	}
 
 
  }
 

}



void	CCKeyScanTask::EDROOM_CTX_Top_0::FSendCharToMonitor()

{
   //Allocate data from pool
  TEDROOMByte * pSNewChar_Data = EDROOMPoolTEDROOMByte.AllocData();
	
		// Complete Data 
	*pSNewChar_Data=VRxChar;
   //Send message 
   MonitorDataStream.send(SNewChar,pSNewChar_Data,&EDROOMPoolTEDROOMByte); 
}



void	CCKeyScanTask::EDROOM_CTX_Top_0::FSendCommand()

{
   //Allocate data from pool
  CDControlParam * pSUpdateControlParam_Data = 
                                           EDROOMPoolCDControlParam.AllocData();
int aux=5;
float value=0;
float auxValue=0.1;	
 
 
VCommBufferControl=-1;
 
if(VCommandBuffer[1]=='p')
 
	pSUpdateControlParam_Data->m_id= CDControlParam::Param_Kp;
 
else if (VCommandBuffer[1]=='i')
 
	pSUpdateControlParam_Data->m_id= CDControlParam::Param_Ki;
 
else if (VCommandBuffer[1]=='d')
	pSUpdateControlParam_Data->m_id= CDControlParam::Param_Kd;
 
else
	pSUpdateControlParam_Data->m_id= CDControlParam::Param_Exit;

if( pSUpdateControlParam_Data->m_id != CDControlParam::Param_Exit){
	while(aux < VIndex){
 
	value+=auxValue*(int)(VCommandBuffer[aux]-'0'); 
	aux++;
	auxValue=auxValue/10;
 
	}
	pSUpdateControlParam_Data->m_value=value;
}
	

   //Send message 
   Command.send(SUpdateControlParam,pSUpdateControlParam_Data,
                                                    &EDROOMPoolCDControlParam); 
}



bool	CCKeyScanTask::EDROOM_CTX_Top_0::GCommandCompleted()

{

bool commandCompleted=true;
 
if((VCommandBuffer[0]=='e')&&(VCommandBuffer[1]=='x')
	&&(VCommandBuffer[2]=='i')
	&&(VCommandBuffer[3]=='t'))
	commandCompleted=true;
else if((VCommBufferControl!=1)||(VIndex < 6))
	commandCompleted=false;
else if(VCommandBuffer[0]!='K')
	commandCompleted=false;
else if((VCommandBuffer[1]!='p')&&(VCommandBuffer[1]!='i')
	&& (VCommandBuffer[1]!='d'))
	commandCompleted=false;
else if(VCommandBuffer[2]!='=')
	commandCompleted=false;
else if(VCommandBuffer[3]!='0')
	commandCompleted=false;
else if(VCommandBuffer[4]!='.')
	commandCompleted=false;	
else {
	int aux=5;
	while(aux < VIndex){
 
		if((VCommandBuffer[aux]<'0')
			|| (VCommandBuffer[aux]>'9'))
			commandCompleted=false;
		
 
		aux++;
	}
 
}
 
 
 
 
return (commandCompleted);

}



bool	CCKeyScanTask::EDROOM_CTX_Top_0::GNewChar()

{

return ((VAuxIndex<40)&& (VRxChar!='$') && (VRxChar!='#') && (VRxChar!='\0')
	&&(VdummyCounter>15));

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDControlParam

CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLCDControlParam::CEDROOMPOOLCDControlParam(
			TEDROOMUInt32 elemCount,CDControlParam* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDControlParam))
{
}

CDControlParam *	CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLCDControlParam::AllocData()
{
	return(CDControlParam*)CEDROOMProtectedMemoryPool::AllocData();
}

	//CEDROOMPOOLTEDROOMByte

CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMByte::CEDROOMPOOLTEDROOMByte(
			TEDROOMUInt32 elemCount,TEDROOMByte* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMByte))
{
}

TEDROOMByte *	CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMByte::AllocData()
{
	return(TEDROOMByte*)CEDROOMProtectedMemoryPool::AllocData();
}

	//CEDROOMPOOLTEDROOMUInt8

CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(
			TEDROOMUInt32 elemCount,TEDROOMUInt8* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(TEDROOMUInt8))
{
}

TEDROOMUInt8 *	CCKeyScanTask::EDROOM_CTX_Top_0::CEDROOMPOOLTEDROOMUInt8::AllocData()
{
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCKeyScanTask::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCKeyScanTask&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VAuxIndex,
			VAuxKeybChannel,
			VCommandBuffer,
			VCommBufferControl,
			VdummyCounter,
			VIndex,
			VNextTimer,
			VRxChar,
			EDROOMPoolCDControlParam,
			EDROOMPoolTEDROOMByte,
			EDROOMPoolTEDROOMUInt8),
		VAuxIndex(0),
		VdummyCounter(0),
		VIndex(0),
		VRxChar(' '),
		EDROOMPoolCDControlParam(
			10, pEDROOMMemory->poolCDControlParam,
			pEDROOMMemory->poolMarkCDControlParam),
		EDROOMPoolTEDROOMByte(
			100, pEDROOMMemory->poolTEDROOMByte,
			pEDROOMMemory->poolMarkTEDROOMByte),
		EDROOMPoolTEDROOMUInt8(
			10, pEDROOMMemory->poolTEDROOMUInt8,
			pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCKeyScanTask::EDROOM_SUB_Top_0::EDROOMBehaviour()
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
			//To Choice Point ScanKeyb
			case (ScanKeyb):

				//Execute Action 
				FScanKeyb();
				//Send Asynchronous Message 
				FIamAlive();
				//Evaluate Branch CommandCompleted
				if( GCommandCompleted() )
				{
					//Send Asynchronous Message 
					FSendCommand();

					//Branch taken is ScanKeyb_CommandCompleted
					edroomCurrentTrans.localId =
						ScanKeyb_CommandCompleted;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch NewChar
				else if( GNewChar() )
				{
					//Send Asynchronous Message 
					FSendCharToMonitor();

					//Branch taken is ScanKeyb_NewChar
					edroomCurrentTrans.localId =
						ScanKeyb_NewChar;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Default Branch NoChar
				else
				{

					//Branch taken is ScanKeyb_NoChar
					edroomCurrentTrans.localId =
						ScanKeyb_NoChar;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
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
				FProgNextScan();
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCKeyScanTask::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCKeyScanTask::EDROOM_SUB_Top_0::EDROOMIArrival()
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



TEDROOMTransId CCKeyScanTask::EDROOM_SUB_Top_0::EDROOMReadyArrival()
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

					//Next transition is  ScanKeyb
					edroomCurrentTrans.localId = ScanKeyb;
					edroomCurrentTrans.distanceToContext = 0 ;
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



