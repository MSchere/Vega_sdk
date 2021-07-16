//##############################################################################
//###############     This file has been generated by EDROOM     ###############
//##############################################################################
 
#include <public/edroom_glue.h>
 
 
//******************************************************************************
// include deployment edroom components
 
#include <public/cccontrolplant_iface_v1.h>
#include <public/ccledtask_iface_v1.h>
#include <public/cchttpservertask_iface_v1.h>
#include <public/cckeyscantask_iface_v1.h>
#include <public/ccrs232task_iface_v1.h>
#include <public/ccmonitor_iface_v1.h>
 
#ifdef CONFIG_EDROOMBP_DEPLOYMENT_NEED_TASK
 
	CEDROOMSystemDeployment systemDeployment;
 
#endif
 
 
 
int main (void){
 
 
 
#ifndef CONFIG_EDROOMBP_DEPLOYMENT_NEED_TASK
 
	CEDROOMSystemDeployment systemDeployment;
 
#endif
 
	CCControlPlant	comp2(2, 13, EDROOMprioVeryHigh, 1024, systemDeployment.GetComp2Memory());
	CCLEDTask	comp3(3, 13, EDROOMprioVeryLow, 1024, systemDeployment.GetComp3Memory());
	CCHTTPServerTask	comp4(4, 13, EDROOMprioVeryLow, 1024, systemDeployment.GetComp4Memory());
	CCKeyScanTask	comp5(5, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp5Memory());
	CCRS232Task	comp6(6, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp6Memory());
	CCMonitor	comp7(7, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp7Memory());
 
	systemDeployment.Config(&comp2, &comp3, &comp4, &comp5, &comp6, &comp7);
 
	systemDeployment.Start();
 
	return 0;
 
}
