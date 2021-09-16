#ifndef CCHK_FDIRMNG_H_
#define CCHK_FDIRMNG_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdrecovaction_iface_v1.h>
#include <public/cdtmlist_iface_v1.h>
#include <public/cdtcdescriptor_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/icuasw_pus_services_iface_v1.h>
#include <public/sc_channel_drv_iface_v1.h>


/**
 * \class   CCHK_FDIRMng
 *
 */
class CCHK_FDIRMng: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCHK_FDIRMngSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCHK_FDIRMngSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SHK_FDIR_TC, 
							SRecAction, 
							STxTM, 
							STMQueued };

	/**
	 * \class CCHK_FDIRMng::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[3];
			//!Component Timing Service Timer Info Marks Memory
			bool TimerInfMarks[3];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[3];
			//!Component Timing Service TimeOut Messages Marks Memory
			bool TimeOutMsgsMarks[3];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

			//! CDTMList Data Pool Memory
			CDTMList	poolCDTMList[10+1];
			//! CDTMList Data Pool Marks Memory
			bool	poolMarkCDTMList[10];
			//! CDRecovAction Data Pool Memory
			CDRecovAction	poolCDRecovAction[10+1];
			//! CDRecovAction Data Pool Marks Memory
			bool	poolMarkCDRecovAction[10];


			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, bool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, bool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! HK_FDIRCtrl Component Port
	CEDROOMInterface	HK_FDIRCtrl;
	//! TMChannelCtrl Component Port
	CEDROOMInterface	TMChannelCtrl;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! HK_FDIR_Timer Timing Port
	CEDROOMTimingInterface	HK_FDIR_Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCHK_FDIRMng(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
		TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	bool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOM_CTX_Top_0

	// ***********************************************************************



	class EDROOM_CTX_Top_0 {

	protected:

	/**
	 * \enum TEDROOMCCHK_FDIRMngSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCHK_FDIRMngSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SHK_FDIR_TC,
		SRecAction,
		STxTM,
		STMQueued };


		friend class CCHK_FDIRMng;

		//!component reference
		CCHK_FDIRMng &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & HK_FDIRCtrl;
		CEDROOMInterface & TMChannelCtrl;
		CEDROOMTimingInterface & HK_FDIR_Timer;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			ExecTC,
			DoHK_FDIR,
			DoHK_FDIR_SendRecAction,
			DoHK_FDIR_NoRecAction,
			EDROOMMemoryTrans };



		//!Variables
		CDRecovAction &VCurrentRecAction;
		CDTMList &VCurrentTMList;
		Pr_Time &VNextTimeout;


		// Pools *************************************************

		class CEDROOMPOOLCDTMList:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDTMList(TEDROOMUInt32 elemCount,CDTMList *pMem, bool *pMarks);
			CDTMList	* AllocData();
		};
		CEDROOMPOOLCDTMList	& EDROOMPoolCDTMList;
		class CEDROOMPOOLCDRecovAction:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDRecovAction(TEDROOMUInt32 elemCount,CDRecovAction *pMem, bool *pMarks);
			CDRecovAction	* AllocData();
		};
		CEDROOMPOOLCDRecovAction	& EDROOMPoolCDRecovAction;


		//!Constructor
		EDROOM_CTX_Top_0 (CCHK_FDIRMng &act,
				CDRecovAction & EDROOMpVarVCurrentRecAction,
				CDTMList & EDROOMpVarVCurrentTMList,
				Pr_Time & EDROOMpVarVNextTimeout,
				CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList,
				CEDROOMPOOLCDRecovAction & EDROOMpPoolCDRecovAction );

		//!Copy constructor
		EDROOM_CTX_Top_0 (EDROOM_CTX_Top_0 &context);

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		bool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage()
		{ EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

		// User-defined Functions

		/**
		 * \brief  
		 */
		void	FDoHK_FDIR();

		/**
		 * \brief  
		 */
		void	FExecHK_FDIR_TC();

		/**
		 * \brief  
		 */
		void	FGetNextRecAction();

		/**
		 * \brief  
		 */
		void	FInitHK_FDIR();

		/**
		 * \brief  
		 */
		void	FSendRecAction();

		/**
		 * \brief  
		 */
		void	FTxTMList();

		/**
		 * \brief  
		 */
		bool	GSendRecAction();

	};

	// ***********************************************************************

	// class EDROOM_SUB_Top_0

	// ***********************************************************************



	class EDROOM_SUB_Top_0 : public EDROOM_CTX_Top_0 {

	protected:



		//!current state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomCurrentState;

		//!next state identifier
		EDROOM_CTX_Top_0::TEDROOMStateID edroomNextState;

		//!Variables
		CDRecovAction VCurrentRecAction;
		CDTMList VCurrentTMList;
		Pr_Time VNextTimeout;


		// Pools**************************************************
		CEDROOMPOOLCDTMList	EDROOMPoolCDTMList;
		CEDROOMPOOLCDRecovAction	EDROOMPoolCDRecovAction;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCHK_FDIRMng &act, CEDROOMMemory *pEDROOMMemory  );


		//! Top Context Behaviour 

		void EDROOMBehaviour();

		//!Top Context Init
		void EDROOMInit();

		//! Initial substate arrival
		TEDROOMTransId EDROOMIArrival();

		// ***********************************************************************

		// Leaf SubState Ready

		// ***********************************************************************



		TEDROOMTransId EDROOMReadyArrival();

	};

protected:

	//!Top State
	EDROOM_SUB_Top_0 edroomTopState;



};
#endif
