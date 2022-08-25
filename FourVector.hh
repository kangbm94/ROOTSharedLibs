#include "ThreeVector.hh"
double Gamma(double v){
	return 1/sqrt(1-v*v);
}
class FourVector{
	private:
		double Momentum(){
			return GetMomentum();
		}
	protected:
		double t;
		ThreeVector TV;
		ThreeVector Position;
		bool Spacelike = false;
	public:
		FourVector(){}
		FourVector(double t_,double x_, double y_, double z_ ){
			t=t_;
			TV=ThreeVector(x_,y_,z_);
			if(t*t<x_*x_+y_*y_+z_*z_){
				cout<<"Warning! This four-vector is Spacelike!"<<endl; 
				Spacelike = true;
			}
		}

		ThreeVector GetThreeVector(){
			return TV;
		}
		ThreeVector GetDirection(){
			double x = TV[0]/TV.Norm();
			double y = TV[1]/TV.Norm();
			double z = TV[2]/TV.Norm();
			return ThreeVector(x,y,z);
		}

		double GetMomentum(){
			return TV.Norm();
		}
		double GetMass(){
			return sqrt(t*t-Momentum()*Momentum());
		};
		double GetBeta(){
			return sqrt(Momentum()*Momentum()/t/t)/Mass(); 
		}
		double GetGamma(){
			return 1/sqrt(1-Beta()*Beta()); 
		}


		void Boost(int dir,double v);
		void AddMomentum(int dir, double P);
		void ShowElements(){
			cout<<Form("(%f,%f,%f,%f)",t,TV[0],TV[1],TV[2])<<endl;
		}

		double operator[](int index) const {
			if(index==0)return t;
			else return TV[index-1];
    }
		FourVector operator+(FourVector B);
		FourVector operator-(FourVector B);


		void SetPosition(double x, double y, double z){
			Position = ThreeVector(x,y,z);
		}
		void Proceed(double time){
				
		}




	private:
		double Mass(){
			return GetMass();
		}
		double Beta(){
			return GetBeta();
		}
		double Gamma(){
			return GetGamma();
		}
};
void FourVector::Boost(int dir, double v){
	double gamma = 1/sqrt(1-v*v);
	double t_=gamma*(t - v*TV[dir]);
	double p_=gamma*(TV[dir]-v*t);
	t=t_;
	TV.Add(dir,p_-TV[dir]);
}
void FourVector::AddMomentum(int dir, double P){
			double mass = Mass();
			TV.Add(dir,P);
			t = sqrt(mass*mass+Momentum()*Momentum());
}
FourVector FourVector::operator+(FourVector B){
			double t_=t+B[0];
			double x_=TV[0]+B[1];	
			double y_=TV[1]+B[2];	
			double z_=TV[2]+B[3];	
			return FourVector(t_,x_,y_,z_);
};
FourVector FourVector::operator-(FourVector B){
			double t_=t-B[0];
			double x_=TV[0]-B[1];	
			double y_=TV[1]-B[2];	
			double z_=TV[2]-B[3];	
			return FourVector(t_,x_,y_,z_);
};



