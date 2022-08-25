#include "Math.hh"
class ThreeVector{
	private:
		vector<double>TV;
		double R(){
			return sqrt(TV[0]*TV[0]+TV[1]*TV[1]);
		}
		int Polarity = 1;
		double PhiInMemory = 0;
	public:
		ThreeVector(){}
		ThreeVector(double x,double y,double z){
			TV={x,y,z};
			if(Norm()==TV[2]){
				PhiInMemory=0;
			}
			if(GetSinPhi()>=0){
				PhiInMemory=acos(GetCosPhi());
			}
			else{
				PhiInMemory= 2*Pi()-acos(GetCosPhi());
			}
		}
		ThreeVector operator+(ThreeVector B);	
		ThreeVector operator-(ThreeVector B);
		double operator*(ThreeVector B);

		double Norm(){
			//			return sqrt(This() * This());
			return sqrt((*this) * (*this));
		}
		double operator[](int index) const {
			return TV[index];
		}
		void Add(int index, double content){
			TV[index]+=content;
			PhiInMemory = GetPhi();
		}
		double GetCosTheta(){
			return TV[2]/Norm();
		}
		double GetSinPhi();
		double GetCosPhi();
		double GetPhi();
		double GetTheta();
		void RotatePhi(double Phi);
		void RotateTheta(double Theta);


		void ShowElements(){
			cout<<Form("( %f , %f , %f )",TV[0],TV[1],TV[2])<<endl;
		}
};
ThreeVector ThreeVector::operator+(ThreeVector B){
	double x=TV[0]+B[0];	
	double y=TV[1]+B[1];	
	double z=TV[2]+B[2];	
	return ThreeVector(x,y,z);
}

ThreeVector ThreeVector::operator-(ThreeVector B){
	double x=TV[0]-B[0];	
	double y=TV[1]-B[1];	
	double z=TV[2]-B[2];	
	return ThreeVector(x,y,z);
}


double ThreeVector::operator*(ThreeVector B){
	double prod = 0;
	for(int i=0;i<3;++i){
		prod+=TV[i]*B[i];
	}
	return prod;
}

double ThreeVector::GetTheta(){
	if(Polarity>0){
		return acos(GetCosTheta());
	}
	else{
		return -acos(GetCosTheta());
	}
}


double ThreeVector::GetSinPhi(){
	if(Norm()==TV[2]){
		return sin(PhiInMemory);//Phi is considered to be 0 if theta = 0.
	}
	else{
		return Polarity*TV[1]/R();
	}
}

double ThreeVector::GetCosPhi(){
	if(Norm()==TV[2]){
		return cos(PhiInMemory);
	}
	else{
		return Polarity*TV[0]/R();
	}
}

double ThreeVector::GetPhi(){
	if(Norm()==TV[2]){
		return PhiInMemory;// Phi range is [0,2Pi)
	}
	if(GetSinPhi()>=0){
		return acos(GetCosPhi());
	}
	else{
		return 2*Pi()-acos(GetCosPhi());
	}
}




void ThreeVector::RotateTheta(double Theta){
	double x,y,z;
//	cout<<GetTheta()<<endl;
	while(Theta>Pi()){
		Theta-=2*Pi();
	}
	while(Theta<-Pi()){
		Theta+=2*Pi();
	}
	if(Polarity>0){
		if(Theta+GetTheta()>=0&&Theta+GetTheta()<Pi()){
			z =cos(Theta)*TV[2]-sin(Theta)*R();
			double R_proj = cos(Theta)*R()+sin(Theta)*TV[2];
			x = R_proj*GetCosPhi();
			y = R_proj*GetSinPhi();
		}
		else{
			cout<<"Warning!! Polarity flipped!, (1->-1)" <<endl;
			Polarity = -1;
			z =cos(Theta)*TV[2]-sin(Theta)*R();
			double R_proj = cos(Theta)*R()+sin(Theta)*TV[2];
			x = -R_proj*GetCosPhi();
			y = -R_proj*GetSinPhi();
		}
	}
	else{
		Theta=-Theta;
		if(-Theta+GetTheta()>=Pi()&&-Theta+GetTheta()<2*Pi()){
			z =cos(Theta)*TV[2]-sin(Theta)*R();
			double R_proj = cos(Theta)*R()+sin(Theta)*TV[2];
			x = -R_proj*GetCosPhi();
			y = -R_proj*GetSinPhi();
		}
		else{
			cout<<"Warning!! Polarity flipped!, (-1->1)" <<endl;
			Polarity = 1;
			z =cos(Theta)*TV[2]-sin(Theta)*R();
			double R_proj = cos(Theta)*R()+sin(Theta)*TV[2];
			x = R_proj*GetCosPhi();
			y = R_proj*GetSinPhi();
		}
	}
	TV={x,y,z};
}

void ThreeVector::RotatePhi(double Phi){
	double x =cos(Phi)*TV[0]-sin(Phi)*TV[1];
	double y =sin(Phi)*TV[0]+cos(Phi)*TV[1];
	double z =TV[2];
	TV={x,y,z};
	PhiInMemory+=Phi;
}
