//#include "CMatrix.hh"
#ifndef CVector_h
#define CVector_h
class CVec: public CMat{//By default, Column vector
	private:
		int dim ;
		Complex v[Max_ent];
	public:

};
class CFVec : public CMat{//By default, Column vector
	private:
		Complex v[4];
		int dim=4;
	public:
		CFVec(){
			for(int i=0;i<dim;i++){
				v[i]=Complex(0,0);
			}
		}
		CFVec(int* V){
			for(int i=0;i<dim;i++){
				v[i]=C(V[i],0);
			}
		}
		CFVec(double* V){
			for(int i=0;i<dim;i++){
				v[i]=C(V[i],0);
			}
		}
		CFVec(Complex* V){
			for(int i=0;i<dim;i++){
				v[i]=V[i];
			}
		}
		/*
		void Col(){
			for(int i=0;i<dim;i++){
				M_[dim*i]=v[i];
			}
		}
		*/
		/*
		void Row(){
			for(int i=0;i<dim;i++){
				M_[i]=v[i];
			}
		}
		*/
};
#endif
