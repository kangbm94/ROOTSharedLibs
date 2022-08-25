#include "CMatrix.hh"
#include "Matrix.hh"
#include "Groups.hh"
double PToBeta(double mom,double mass){
	double val=sqrt(mass*mass+mom*mom);
	return mom/val;
}
double BetaToP(double beta, double mass){
	double val=1/sqrt(1-square(beta));
	return val*mass;
}
double Gamma(double beta){
	double val=1/sqrt(1-square(beta));
	return val;
}
double Beta(double gamma){
	double val=1-square(1/gamma);
	return sqrt(val);
}
double TwoBodyCM(double mi, double m1, double m2){
	return sqrt((mi*mi-square(m1+m2))*(mi*mi-square(m1-m2)))/(2*mi);
}
double TotalDecayWidth(double *Gamma,double size){
	//	dumi1=Gamma.length();
	//	cout<<"Size of Entries: "<<dumi1<<endl;
	double val;
	for(int i=0;i<size;i++){
		val+=1/Gamma[i];
	}
	return 1/val;
}
double EC=sqrt(4*Pi()/137.04);
void SetSpinor(double* u1, double* u2, double* d1,double* d2,int k ){
	switch(k){
		case 0:
			u1[0]=1.;
			u2[0]=1.;
			d1[0]=0.;
			d2[0]=0.;
			break;
		case 1:
			u1[0]=1.;
			u2[0]=0.;
			d1[0]=0.;
			d2[0]=1.;
			break;
		case 2:
			u1[0]=0.;
			u2[0]=1.;
			d1[0]=1.;
			d2[0]=0.;
			break;
		case 3:
			u1[0]=0.;
			u2[0]=0.;
			d1[0]=1.;
			d2[0]=1.;
			break;
	}
}




//Basics






//Pauli 


//Gamma Matrices
Complex G0_[16]={
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0)
};
Complex G1_[16]={
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(1,0),
	Complex(0,0),Complex(0,0),Complex(1,0),Complex(0,0),
	Complex(0,0),Complex(-1,0),Complex(0,0),Complex(0,0),
	Complex(-1,0),Complex(0,0),Complex(0,0),Complex(0,0)
};
Complex G2_[16]={
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,-1),
	Complex(0,0),Complex(0,0),Complex(0,1),Complex(0,0),
	Complex(0,0),Complex(0,1),Complex(0,0),Complex(0,0),
	Complex(0,-1),Complex(0,0),Complex(0,0),Complex(0,0)
};
Complex G3_[16]={
	Complex(0,0),Complex(0,0),Complex(1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0),
	Complex(-1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0)
};
Complex G5_[16]={
	Complex(0,0),Complex(0,0),Complex(1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(1,0),
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0)
};

//Spinors







/*
Complex U1_[16]={
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0)
};
Complex U2_[16]={
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0)
};
Complex V1_[16]={
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0)
};
Complex V2_[16]={
	Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),
	Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0)
};
CMat4D U1=CMat4D(U1_);
CMat4D U2=CMat4D(U2_);
CMat4D V1=CMat4D(V1_);
CMat4D V2=CMat4D(V2_);
*/

/*
	 Complex Pauli13[9]={Complex(0,0),Complex(1,0),Complex(0,0),Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,0)};
	 Complex Pauli23[9]={Complex(0,0),Complex(0,-1),Complex(0,0),Complex(0,1),Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,0)};
	 Complex Pauli33[9]={Complex(1,0),Complex(0,0),Complex(0,0),Complex(0,0),Complex(-1,0),Complex(0,0),Complex(0,0),Complex(0,0),Complex(0,0)};
	 CMat3D sig13=CMat3D(Pauli13); 
	 CMat3D sig23=CMat3D(Pauli23); 
	 CMat3D sig33=CMat3D(Pauli33); 
	 */
