

/* last modifier: js */
#include "sdeNode.h"



namespace conedy

{




//gslNoise sdeNode::noise;
// -------------------------Node for Stochastic Differential Equations----------------------------- //
// Dieser Ornstein-Uhlenbeck Prozess kann dazu benutzt werden


// Dies ist das EEG-Modell von Fabrice Wendling: (C_i = params[i])
// C_0 = sigma_n, C_1 = mean_n, 
// C_2 = a_0, C_3 = e_0,
// C_4 = v_0, C_5 = r
// C_6 = C_1, C_7 = C_2,
// C_8 = C_3, C_9 = C_4, 
// C_10 = A, C_11 = a, C_12 = B, 
// C_13 = b, 
// K Speichert die Kopplungskonstanten zu den anderen Populationen
// 
/*void wendling::operator()(valarray<double>& y, valarray<double>& dxdt, valarray<double>&dxdW) {  
	dxdt[0] = y[3];
	dxdt[3] = params[10] * params[11] * sigmoid(y[1] - y[2]) - 2.0 * params[11] * y[3] - params[11] * params[11] * y[0];
	dxdt[1] = y[4];
	dxdt[4] = params[10]*params[11]*(couplingSum() + params[1] + params[7]*sigmoid(params[6]*y[0])) - 2 * params[11]*y[4] - params[11]*params[11]*y[1];
	dxdt[2] = y[5];
	dxdt[5] = params[12]*params[13]*(params[9]*sigmoid(params[8]*y[0])) - 2.0*params[13]*y[5] - params[13]*params[13]*y[2];
	dxdt[6] = y[7];
	dxdt[7] = params[10]*params[2]*sigmoid(y[1] - y[2]) - 2.0*params[2]*y[7] - params[2]*params[2]*y[6];
	dxdW[4] = params[10]*params[11]*params[0];
}

void coloredWendling::operator()(valarray<double>& y, valarray<double>& dxdt, valarray<double>&dxdW) {  



	dxdt[0] = y[3];
	dxdt[3] = getParams(10) * getParams(11) * sigmoid(y[1] - y[2]) - 2.0 * getParams(11) * y[3] - getParams(11) * getParams(11) * y[0];
	dxdt[1] = y[4];
	dxdt[4] = getParams(10)*getParams(11)*(couplingSum() + getParams(1) + getParams(0)*y[8] + getParams(7)*sigmoid(getParams(6)*y[0])) - 2 * getParams(11)*y[4] - getParams(11)*getParams(11)*y[1];
	dxdt[2] = y[5];
	dxdt[5] = getParams(12)*getParams(13)*(getParams(9)*sigmoid(getParams(8)*y[0])) - 2.0*getParams(13)*y[5] - getParams(13)*getParams(13)*y[2];
	dxdt[6] = y[7];
	dxdt[7] = getParams(10)*getParams(2)*sigmoid(y[1] - y[2]) - 2.0*getParams(2)*y[7] - getParams(2)*getParams(2)*y[6];
	dxdt[8] = -1/getParams(14)*y[8];
	dxdW[8] = 1.0;

//	cout << getParams(0) << ":" << getParams(3) << ":" << getParams (15) << endl;
//	cout << "TMP:" << x[0] << " "<< x[1] << " "<< x[2] << " "<< x[3]<< " " << x[4] << endl;


}
*/


//void ornUhl::operator()(baseType x[], baseType  dxdt[], baseType dxdW[]) { 
//
//	//cout << getParams(0) << ":" << getParams(1) << endl;
//
//	dxdt[0]=-1.0/params<baseType>::getParams(0) * x[0] + this->couplingSum();
//	dxdW[0]=sqrt(2.0 * params<baseType>::getParams(1))/params<baseType>::getParams(0);
//}
//
/*

void breakspear::operator()(valarray<double>& y, valarray<double>& dxdt, valarray<double>&dxdW) {  
	double coupling = couplingSum();
	Qtmp = S(y[0], params[14], params[15]);
	dxdt[0] = -(params[2] + (1 - params[29])*params[27]*params[19]*Qtmp + params[29]*params[27]*params[19]*coupling)*
				 S(y[0], params[0], params[1])*(y[0] - params[3]) - params[6]*y[2]*(y[0] - params[7]) - params[13]*(y[0] - params[12])
				 - (params[10]*S(y[0], params[8], params[9]) + (1 - params[29])*params[19]*Qtmp + params[29]*params[19]*coupling)*(y[0] - params[11])
				 - params[21]*y[1]*S(y[1], params[16], params[17]);
	dxdt[1] = params[24]*params[20]*y[0]*Qtmp;
	dxdt[2] = params[25]/params[26]*(S(y[0], params[7], params[5]) - y[2]);
	dxdW[0] = params[22]*params[18];
	dxdW[1] = params[24]*params[23]*params[18];
};

void coloredBreakspear::operator()(valarray<double>& y, valarray<double>& dxdt, valarray<double>&dxdW) {  
	double coupling = couplingSum();
	Qtmp = S(y[0], params[14], params[15]);
	dxdt[0] = -(params[2] + (1 - params[29])*params[27]*params[19]*Qtmp + params[29]*params[27]*params[19]*coupling)*
				 S(y[0], params[0], params[1])*(y[0] - params[3]) - params[6]*y[2]*(y[0] - params[7]) - params[13]*(y[0] - params[12])
				 - (params[10]*S(y[0], params[8], params[9]) + (1 - params[29])*params[19]*Qtmp + params[29]*params[19]*coupling)*(y[0] - params[11])
				 - params[21]*y[1]*S(y[1], params[16], params[17]) + params[22]*y[3];
	dxdt[1] = params[24]*params[20]*y[0]*Qtmp + params[24]*params[23]*y[3];
	dxdt[2] = params[25]/params[26]*(S(y[0], params[7], params[5]) - y[2]);
	dxdt[3] = -1.0/params[30]*y[3];
	dxdW[3] = 1.0;
};

*/
}

// Node for Stochastic Differential Equations //
