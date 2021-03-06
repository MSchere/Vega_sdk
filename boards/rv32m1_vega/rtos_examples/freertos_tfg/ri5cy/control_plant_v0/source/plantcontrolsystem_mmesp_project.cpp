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
	PRINTF("\r\nSystem deployment:%p\r\n", systemDeployment);
	CCControlPlant	*comp2= new CCControlPlant (2, 13, EDROOMprioVeryHigh, 1024, systemDeployment.GetComp2Memory());
	PRINTF("\r\ncomp2:%p\r\n", comp2);

	CCLEDTask	*comp3 = new CCLEDTask (3, 13, EDROOMprioVeryLow, 1024, systemDeployment.GetComp3Memory());
	PRINTF("\r\ncomp3:%p\r\n", comp3);

	CCHTTPServerTask	*comp4 = new CCHTTPServerTask(4, 13, EDROOMprioVeryLow, 1024, systemDeployment.GetComp4Memory());
	PRINTF("\r\ncomp4:%p\r\n", comp4);

	CCKeyScanTask	*comp5 = new CCKeyScanTask(5, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp5Memory());
	PRINTF("\r\ncomp5:%p\r\n", comp5);

	CCRS232Task	*comp6 = new CCRS232Task(6, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp6Memory());
	PRINTF("\r\ncomp6:%p\r\n", comp6);

	CCMonitor	*comp7 = new CCMonitor(7, 13, EDROOMprioNormal, 1024, systemDeployment.GetComp7Memory());
	PRINTF("\r\ncomp7:%p\r\n", comp7);

	systemDeployment.Config(comp2, comp3, comp4, comp5, comp6, comp7);
 
	systemDeployment.Start();
 
	return 0;
 
}
