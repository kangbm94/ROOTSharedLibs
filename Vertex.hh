#include "FourVector.hh"
class Vertex:public FourVector{
	private:
		FourVector FV;
	public:
		Vertex(FourVector A, FourVector B){
			FV=A+B;
			TV=FV.GetThreeVector();
			t=FV[0];
		}
		void Decay(FourVector& A,FourVector& B);
		void Decay(FourVector& A,FourVector& B,FourVector& C){};
};
void Vertex::Decay(FourVector&A,FourVector&B){
	double MotherMass = this->GetMass();
	double M_A = A.GetMass();
	double M_B = B.GetMass();
	cout<<MotherMass<<endl;
	double Qvalue = MotherMass-A.GetMass()-B.GetMass();
	if(Qvalue<0){
		cout<<"Warning: Kinimetically Forbidden"<<endl;
		cout<<"Mother: ";
			this->ShowElements();
		cout<<"DaughterMass: " << M_A << " , " <<M_B<<endl;
	}
		

}







