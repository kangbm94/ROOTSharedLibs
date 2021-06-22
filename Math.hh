#include "Variables.hh"
#ifndef Math_h
#define Math_h
double square(double a){ 
	return a*a;
}
int PM(int a){
	if(a%2==0){
		return 1;
	}
	else{
		return -1;
	}
}
double Min(double a, double b){
	if(a>b){
		return b;
	}
	else{
		return a;
	}
}
double Max(double a, double b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}
double Power(double x,int n){
		double value=1;
		for(int i=0;i<n;i++){
			value=value*x;
		}
		return value;
}
double Polynomial(double x, double* p,int n){
	double value=0;
	for(int i=0;i<n+1;i++){
		value+=p[i]*Power(x,i);
	}
	return value;
}
double SquareSum(double a, double b){
	return sqrt(a*a+b*b);
}
double Gaussian(double x, double mean, double sigma, double amplitude){
	double par=(x-mean)/sigma;
	double val = amplitude*exp(-par*par/2)/sigma/sqrt(2*Pi());
	return val;
}
double Step(double a){
	if(a>0){
		return 1;
	}
	else{
		return 0;
	}
}
//
double QuadRoot(double a,double b,double c, int conf){
	if(conf<0){
		return  (-b -sqrt(b*b-4*a*c))/(2*a);
	}
	else{
		return (-b +sqrt(b*b-4*a*c))/(2*a);
	}
}
double T1(double a,double b, double c, double d){
	double p0=1/(3*a);
	double p1=2*b*b*b-9*a*b*c+27*a*a*d;
	double p2 = b*b-3*a*c;
	double val= -b*p0-p0*(
			pow((p1+sqrt(p1*p1-4*p2*p2*p2))/2,1./3)
		 +pow((p1-sqrt(p1*p1-4*p2*p2*p2))/2,1./3)
			);
		return val;
}


double Qr1(double a, double b, double c, double d, double e){
	return 4;
}





//Randoms
double GenUniformRandom(double range){
	double rnd=gRandom->Rndm();
	return range*rnd;
}
double GenUniformRandom(){
	return GenUniformRandom(1);
}
void GenSphericalRandom(double &theta, double &phi){
	phi=GenUniformRandom(2*Pi());
	double cth= GenUniformRandom(2)-1;
	theta=acos(cth);
}

void FunctionDigitize(TF1* func, int npar, double* par, double xmin, double xmax, double ){
	double x =xmin+(xmax-xmin)*gRandom->Rndm();

};










#endif
