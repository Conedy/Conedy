

#include "mapNode.h"

namespace conedy  {




void izhikevichMap::operator()(baseType xprime [], baseType x[])
{
  
	if (x[0] < -100) {
	  x[0] = -100;
	}
	if (x[0] > 30)
	  	{
			registerOneTimeCallBack(_fire_, dynNode::time + timeDelay() );				
//		decreaseKey (_fire_, time + timeDelay());
		x[0] = c();
		x[1] = x[1] + d();
	}
	
	if (noise.getUniform() < pendo())
		{
      xprime[0] = x[0] + 0.5 *(0.04 * x[0]*x[0] + 5 * x[0] + 140 - x[1] + I() + pendoC()   );
		      xprime[0] = xprime[0] + 0.5 *(0.04 * xprime[0]*xprime[0] + 5 * xprime[0] + 140 - x[1] + I() + pendoC()) ;
	}
	else
		{
      xprime[0] = x[0] + 0.5*(0.04 * x[0]*x[0] + 5 * x[0] + 140 - x[1] + I() );
		      xprime[0] = xprime[0] + 0.5*(0.04 * xprime[0]*xprime[0] + 5 * xprime[0] + 140 - x[1] + I() );
	}
	xprime[1] = x[1] +  a() * (b() * x[0] - x[1]); 

}




}

