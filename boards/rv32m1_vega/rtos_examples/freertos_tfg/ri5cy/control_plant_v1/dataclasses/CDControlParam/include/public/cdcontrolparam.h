#ifndef FCDControlParamH
#define FCDControlParamH

class CDControlParam{
	
	public:

	enum TParamID{ Param_Kp, Param_Ki, Param_Kd, Param_Exit};

	TParamID m_id;
	float m_value; 	

	CDControlParam(){
	
		m_id=Param_Kp;
		m_value=0.2; 
	}
	

	CDControlParam( TParamID id, float value){
	
		m_id=id;
		m_value=value; 
	}
	
	protected:
	
	private:
	
};

#endif
