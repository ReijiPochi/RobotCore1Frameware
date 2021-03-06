/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  DistanceMeter                          */
/*      FILE         :  reset_program.c                        */
/*      DESCRIPTION  :  Reset program                          */
/*      CPU SERIES   :  RX600                                  */
/*      CPU TYPE     :  RX63T                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                


#include	<machine.h>
#include	<_h_c_lib.h>
#include	"..\typedefine.h"		// Define Types
#include	"stacksct.h"		// Stack Sizes (Interrupt and User)

#ifdef __cplusplus
extern "C" {
#endif
void PowerON_Reset_PC(void);
void main(void);
#ifdef __cplusplus
}
#endif

//extern void srand(_UINT);		// Remove the comment when you use rand()
//extern _SBYTE *_s1ptr;		// Remove the comment when you use strtok()


#define FPSW_init 0x00000000	// FPSW bit base pattern

		
#ifdef __cplusplus				// Use Hardware Setup
extern "C" {
#endif
extern void HardwareSetup(void);
#ifdef __cplusplus
}
#endif
	
#ifdef __cplusplus			// Remove the comment when you use global class object
extern "C" {					// Sections C$INIT and C$END will be generated
#endif
extern void _CALL_INIT(void);
extern void _CALL_END(void);
#ifdef __cplusplus
}
#endif

#pragma section ResetPRG		// output PowerON_Reset to PResetPRG section

#pragma entry PowerON_Reset_PC
void PowerON_Reset_PC(void)
{
#ifdef __RXV2
	set_extb(__sectop("EXCEPTVECT"));
#endif
	set_intb(__sectop("C$VECT"));

#ifdef __FPU
#ifdef __ROZ					// Initialize FPSW
#define _ROUND 0x00000001			// Let FPSW RMbits=01 (round to zero)
#else
#define _ROUND 0x00000000			// Let FPSW RMbits=00 (round to nearest)
#endif
#ifdef __DOFF
#define _DENOM 0x00000100			// Let FPSW DNbit=1 (denormal as zero)
#else
#define _DENOM 0x00000000			// Let FPSW DNbit=0 (denormal as is)
#endif
	set_fpsw(FPSW_init | _ROUND | _DENOM);
#endif

	_INITSCT();

	clrpsw_i();						// マスカブル割り込みを禁止
	HardwareSetup();				// Use Hardware Setup
    nop();

	_CALL_INIT();					// Use global class object

	setpsw_i();						// マスカブル割り込みを許可
	main();
	
	_CALL_END();					// Use global class object

	brk();
}
