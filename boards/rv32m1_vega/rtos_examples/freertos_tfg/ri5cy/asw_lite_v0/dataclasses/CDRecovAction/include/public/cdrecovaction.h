#ifndef FCDRecovActionH
#define FCDRecovActionH

#include <platform/basic_types.h>

class CDRecovAction{
	
	friend class PUSService19;

	int16_t m_RecActionIndex;

	void SetActionIndex(int16_t index){
		m_RecActionIndex=index;
	}	

	public:
	
	bool IsEmpty(){	  
	  return (m_RecActionIndex<0);
	}
	
	void Done(){
	   m_RecActionIndex=-1;
	}

	CDRecovAction(){
	   m_RecActionIndex=-1;
	}

	protected:
	
	private:
	
};
#endif
