#include "Math.hh"
#ifndef Complex_h
#define Complex_h
const double tolerance= 1E-10;
class Complex{
	private:
		double real;
		double img;
		double radious;
		double phase;
		void SetRadious(){
			radious = SquareSum(real,radious);
		}
		void SetPhase(){
			if(img<0){
				phase = 2*Pi()-acos(real/radious);
			}
			else{
				phase = acos(real/radious);
			}
		}
		void SetReal(){
			real = radious*cos(phase);
		}
		void SetImaginary(){
			img = radious*sin(phase);
		}
		void SetRPhy(){
			SetRadious();
			SetPhase();
		}
		void SetXY(){
			SetReal();
			SetImaginary();
		}
	public:
		//Constructors
		Complex(){
			real=0;
			img=0;
			radious=0;
			phase=0;
		};
		Complex(double r, double i){
			real=r;
			img=i;
			SetRPhy();
		};
		Complex(int r, double i){
			real=r;
			img=i;
			SetRPhy();
		};
		Complex(double r, int i){
			real=r;
			img=i;
			SetRPhy();
		};
		Complex(int r, int i){
			real=r;
			img=i;
			SetRPhy();
		};

		//Basic Methods
		Complex This(){
			return Complex(real,img);
		}
		double Real(){
			return real;
		}
		double Imaginary(){
			return img;
		}
		double Radious(){
			return radious;
		}
		double Phase(){
			return phase;
		}
		double Abs(){
			return radious;//Same with Radious() function
		}
		Complex CRPhy(double rad, double phi){
			double r = rad*cos(phi);
			double i = rad*sin(phi);
			return Complex(r,i);
		}
		void Show(){
			if(img>=0){
				cout<<real<<" + "<<img<<" i";
			}
			else{
				cout<<real<<" - "<<-img<<" i";
			}
		}
		Complex Conjugate(){
			double rad = radious;
			double phi = -phase;
			Complex ztmp=CRPhy(rad,phi);
			return ztmp;
		}

		//Overriding Operators
		Complex operator+(Complex z){
			Complex ztmp;
			ztmp.real=real+z.Real();
			ztmp.img=img+z.Imaginary();
			return ztmp;
		}
		Complex operator+(int a){
			Complex ztmp;
			ztmp.real=real+a;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator+(double a){
			Complex ztmp;
			ztmp.real=real+a;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator-(Complex z){
			Complex ztmp;
			ztmp.real=real-z.Real();
			ztmp.img=img-z.Imaginary();
			return ztmp;
		}
		Complex operator-(double a){
			Complex ztmp;
			ztmp.real=real-a;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator-(int a){
			Complex ztmp;
			ztmp.real=real-a;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator-(){
			Complex ztmp;
			ztmp.real=-real;
			ztmp.img=-img;
			return ztmp;
		}
		Complex operator*(Complex z){
			Complex ztmp;
			ztmp.real=real*z.Real()-img*z.Imaginary();
			ztmp.img=img*z.Real()+real*z.Imaginary();
			return ztmp;
		}
		Complex operator*(int a){
			Complex ztmp;
			ztmp.real=real*a;
			ztmp.img=img*a;
			return ztmp;
		}
		Complex operator*(double a){
			Complex ztmp;
			ztmp.real=real*a;
			ztmp.img=img*a;
			return ztmp;
		}
		Complex operator/(double a){
			Complex ztmp;
			ztmp.real=real/a;
			ztmp.img=img/a;
			return ztmp;
		}
		Complex operator/(int a){
			Complex ztmp;
			ztmp.real=real/a;
			ztmp.img=img/a;
			return ztmp;
		}
		Complex operator/(Complex z){
			/*
				 double r1=Abs();
				 double p1=Phase();
				 double r2=z.Abs();
				 double p2=z.Phase();
				 double r=r1/r2;
				 double p=p1-p2;
				 Complex ztmp;
				 ztmp.SetRPhi(r,p);
				 */
			Complex ztmp;
			return ztmp;
		}

		Complex operator=(double a){
			Complex ztmp;
			ztmp.real=a;
			ztmp.img=0;
			return ztmp;
		}
		Complex operator=(int a){
			Complex ztmp;
			ztmp.real=a;
			ztmp.img=0;
			return ztmp;
		}
		Complex operator+=(Complex z){
			Complex ztmp;
			real+=z.real;
			img+=z.img;
			ztmp.real=real;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator+=(double a){
			Complex ztmp;
			real+=a;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator+=(int a){
			Complex ztmp;
			real+=a;
			ztmp.real=real;
			ztmp.img=img;
			return ztmp;
		}
		Complex operator-=(Complex z){
			return This()-z;	
		}
		Complex operator-=(int z){
			return This()-z;	
		}
		Complex operator-=(double z){
			return This()-z;	
		}
//		Complex Pow(Complex z1, Complex z2){
//		}
};
//Operators
Complex operator+(int a,Complex ztmp){
	return ztmp+a;
}
Complex operator+(double a,Complex ztmp){
	return ztmp+a;
}
Complex operator*(double a,Complex ztmp){
	return ztmp*a;
}
Complex operator*(int a,Complex ztmp){
	return ztmp*a;
}
Complex operator-(double a,Complex ztmp){
	return (ztmp-a)*(-1);
}
Complex operator-(int a,Complex ztmp){
	return (ztmp-a)*(-1);
}
Complex operator/(double a,Complex z){
	double zabs=z.Abs();
	Complex z2=z.Conjugate()/zabs/zabs;
	return z2*a;
}
Complex operator/(int a,Complex z){
	double zabs=z.Abs();
	Complex z2=z.Conjugate()/zabs/zabs;
	return z2*a;
}
Complex C(double a, double b){
	return Complex(a,b);
}
Complex CRPhy(double rad, double phi){
	double r = rad*cos(phi);
	double i = rad*sin(phi);
	return Complex(r,i);
};

/*
	 Complex Q1(Complex a Comblex b, Complex c){

	 }
	 */












#endif
