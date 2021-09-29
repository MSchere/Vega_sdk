#ifndef CCTM_CHANNELCTRL_H_
#define CCTM_CHANNELCTRL_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

//******************************************************************************
// Data Classes

#include <public/cdtmlist_iface_v1.h>


//******************************************************************************
// Required software interfaces

#include <public/icuasw_pus_services_iface_v1.h>
#include <public/sc_channel_drv_iface_v1.h>


/**
 * \class   CCTM_ChannelCtrl
 *
 */
class CCTM_ChannelCtrl: public CEDROOMComponent {

public:

	/**
	 * \enum TEDROOMCCTM_ChannelCtrlSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum TEDROOMCCTM_ChannelCtrlSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							STxTM, 
							STMQueued };

	/**
	 * \class CCTM_ChannelCtrl::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

		public:



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

	//! TMChannelCtrl3 Component Port
	CEDROOMInterface	TMChannelCtrl3;
	//! TMChannelCtrl2 Component Port
	CEDROOMInterface	TMChannelCtrl2;
	//! TMChannelCtrl Component Port
	CEDROOMInterface	TMChannelCtrl;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCTM_ChannelCtrl(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, 
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
	 * \enum TEDROOMCCTM_ChannelCtrlSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	enum TEDROOMCCTM_ChannelCtrlSignal { EDROOMSignalTimeout,
		EDROOMSignalDestroy,
		STxTM,
		STMQueued };


		friend class CCTM_ChannelCtrl;

		//!component reference
		CCTM_ChannelCtrl &EDROOMcomponent;

		//!Current message pointer reference
		CEDROOMMessage * &Msg;

		//!Synchronous message back pointer reference
		CEDROOMMessage * &MsgBack;

		//!Component ports
		CEDROOMInterface & TMChannelCtrl3;
		CEDROOMInterface & TMChannelCtrl2;
		CEDROOMInterface & TMChannelCtrl;


		//! State Identifiers
		enum TEDROOMStateID{I,
			Ready};

		//!Transition Identifiers
		enum TEDROOMTransitionID{Init,
			TxTM,
			EDROOMMemoryTrans };







		//!Constructor
		EDROOM_CTX_Top_0 (CCTM_ChannelCtrl &act );

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
		void	FReplyTMQueued();

		/**
		 * \brief  
		 */
		void	FSendTMList();

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





	public:

		//! Constructor
		EDROOM_SUB_Top_0 (CCTM_ChannelCtrl &act );


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
