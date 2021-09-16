/*
 * emu_tc_programming.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */

#include <public/emu_sc_channel_drv_slib_v1.h>

#define UNITIME_AFTER_POWER_ON 100001

//Casted all strings to (char*)

//Uni Time
Program9_129TC prog_tc1(0,(char*)"Set Power-On Universal Time",UNITIME_AFTER_POWER_ON);


Program17_1TC prog_tc1_b(UNITIME_AFTER_POWER_ON + 2,(char*)"Connection Test");


//**********************************
//Define Monitoring
//**********************************

//Add Param 0 monitoring definition


Program12_5TC prog_tc2 (UNITIME_AFTER_POWER_ON + 2 ,
		(char*)"Define Monitoring Param 0",
                0,
                10,
                0x4001,
                0,
                0x4002,
                5);


//**********************************
//Event-Action
//**********************************

//Event 0x4002- Action


Program19_1TC prog_tc5(UNITIME_AFTER_POWER_ON + 3,
		(char*)"Assign TC(128,2) as action of Event 0x4002",
                       0x4002,
                       128,2);


//Enable Event 0x4002- Action

Program19_4TC prog_tc6(UNITIME_AFTER_POWER_ON + 3,
		(char*)"Enable Action of Event 0x4002",
                       0x4002);



//**********************************
//Enable Monitoring
//**********************************

//Enable Param 0 Monitoring


Program12_1TC prog_tc7(UNITIME_AFTER_POWER_ON + 4,
		(char*)"Enable Monitoring Param 0",0);


//**********************************
//Memory Management
//**********************************


/*
Program6_2TC prog_tc8 (UNITIME_AFTER_POWER_ON + 5,
                         "Memory Patch",0x10000,32,NULL);

Program6_5TC prog_tc9 (UNITIME_AFTER_POWER_ON + 6,
                         "Memory Dump",0x10000,32);
*/

//**********************************
//Housekeeping
//**********************************

/*
Program3_129TC prog_tcx(UNITIME_AFTER_POWER_ON + 12,
		(char*)"Change period of SID 0 to 5 seconds",
             0,5);
*/
Program3_6TC prog_tc_disable_SID_0(UNITIME_AFTER_POWER_ON + 25,
		(char*)"DISABLE SID 0", 0);

Program3_5TC prog_tc_enable_SID_0(UNITIME_AFTER_POWER_ON + 50,
		(char*)"ENABLE SID 0", 0);


//**********************************
//Private Service System Data Pool Mng
//**********************************


//Set Param 0 to 6
Program128_4TC prog_tc10 (UNITIME_AFTER_POWER_ON + 12,
                         (char*)"Set Param 0 to value 6",0,6);

//Read Param 0 value
Program128_5TC prog_tc11(UNITIME_AFTER_POWER_ON + 13,
		(char*)"Get Param 0 value",0);


//Set Param 0 to 6
Program128_4TC prog_tc12 (UNITIME_AFTER_POWER_ON + 35,
		(char*)"Set Param 0 to value 3",0,3);


//Set Param 0 to 6
Program128_4TC prog_tc13 (UNITIME_AFTER_POWER_ON + 55,
		(char*)"Set Param 0 to value 7",0,7);
/*
Program128_3TC prog_exit (UNITIME_AFTER_POWER_ON + 60,
		(char*)"exit");
*/
