#ifndef CCBKGTCEXEC_H_
#define CCBKGTCEXEC_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdtmlist_iface_v1.h>
#include <public/cdeventlist_iface_v1.h>
#include <public/cdtcdescriptor_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/icuasw_pus_services_iface_v1.h>
#include <public/sc_channel_drv_iface_v1.h>


/**
 * \class   CCBKGTCExec
 *
 */
class CCBKGTCExec: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCBKGTCExecSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCBKGTCExecSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SBKGTC, 
							STxTM, 
							STMQueued };

	/**
	 * \class CCBKGTCExec::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

		public:

			//! CDTMList Data Pool Memory
			CDTMList	poolCDTMList[10+1];
			//! CDTMList Data Pool Marks Memory
			bool	poolMarkCDTMList[10];


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

	//! BKGExecCtrl Component Port
	CEDROOMInterface	BKGExecCtrl;
	//! TMChannelCtrl Component Port
	CEDROOMInterface	TMChannelCtrl;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCBKGTCExec(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCBKGTCExecSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCBKGTCExecSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		SBKGTC,
		STxTM,
		STMQueued };


		friend class CCBKGTCExec;

		//!component reference
		CCBKGTCExec &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & BKGExecCtrl;
		CEDROOMInterface & TMChannelCtrl;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			ExecTC,
			EDROOMMemoryTrans };



		//!Variables
		CDEventList &VCurrentEvList;
		CDTMList &VCurrentTMList;


		// Pools *************************************************

		class CEDROOMPOOLCDTMList:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLCDTMList(TEDROOMUInt32 elemCount,CDTMList *pMem, bool *pMarks);
			CDTMList	* AllocData();
		};
		CEDROOMPOOLCDTMList	& EDROOMPoolCDTMList;


		//!Constructor
		EDROOM_CTX_Top_0 (CCBKGTCExec &act,
				CDEventList & EDROOMpVarVCurrentEvList,
				CDTMList & EDROOMpVarVCurrentTMList,
				CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList );

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
		void	FExecBKGTC();

		/**
		 * \brief  
		 */
		void	FTxTMList();

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
		CDEventList VCurrentEvList;
		CDTMList VCurrentTMList;


		// Pools**************************************************
		CEDROOMPOOLCDTMList	EDROOMPoolCDTMList;


	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCBKGTCExec &act, CEDROOMMemory *pEDROOMMemory  );


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
