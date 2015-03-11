#include "config.h"
#include "System.h"

int main( void )
{
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	
	System_Init();
	
	while(1)
	{
	}
	
	return 0;
}
 