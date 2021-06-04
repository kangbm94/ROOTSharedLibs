#include "Complex.hh"
#ifndef CMatrix_h
#define CMatrix_h
const int Max_dim=10;
const int Max_ent=Max_dim*Max_dim;
bool ReduceDim(Complex* Min, Complex* Mout, int dim, int row, int col){
	int cnt=0;
	if(dim>1){
		for(int i=0;i<dim;i++){
			if(i%dim==col){
				continue;
			}
			else{
				for(int j=0;j<dim;j++){
					if(j%dim==row){
						continue;
					}
					else{
						Mout[cnt]=Min[dim*i+j];
						cnt++;
					}
				}
			}
		}
		return true;
	}
	else{
		cout<<"Warning: dimension < 2!!"<<endl;
		return false;
	}
}//


class CMat{
	private: 
		int dim_;
		Complex M_[Max_ent];
		Complex EigenValue[Max_dim];
		Complex EigenVector[Max_dim][Max_dim];
	public:
		//Constructors
		CMat(int dim ){
			dim_=dim;
			for(int i=0;i<dim*dim;i++){
				M_[i]=C(0,0);
			}
			for(int i=0;i<dim;i++){
				M_[i*i]=C(1,1);
			}
		}
		CMat(){
			return CMat(Max_dim);
		}
		CMat(int dim, int* M){
			dim_=dim;
			for(int i=0;i<dim*dim;i++){
				M_[i]=C(M[i],0);
			}
		}
		CMat(int dim, double* M){
			dim_=dim;
			for(int i=0;i<dim*dim;i++){
				M_[i]=C(M[i],0);
			}
		}
		CMat(int dim, Complex* M){
			dim_=dim;
			for(int i=0;i<dim*dim;i++){
				M_[i]=M[i];
			}
		}

		//Elementary Methods
		int Dim(){
			return dim_;
		}
		void Init(){
			for(int i=0;i<dim_*dim_;i++){
				M_[i]=Complex(0,0);
			}
		}
		void Show(){
			for(int i=0;i<dim_;i++){
				cout<<"|";
				for(int j=0;j<dim_;j++){
					M_[i*dim_+j].Show();
					if(j<dim_-1){
						cout<<" , ";
					}
				}
				cout<<"|"<<endl;
			}
		}
		Complex GetElement(int i, int j){
			if(i<dim_&&j<dim_){
				return M_[dim_*i+j];
			}
			else{
				cout<<"Dimmesion Error"<<endl;
				return Complex(0,0);
			}
		}
		void SetElement(int i, int j, int a){
			M_[dim_*i+j]=Complex(a,0);
		}
		void SetElement(int i, int j, double a){
			M_[dim_*i+j]=Complex(a,0);
		}
		void SetElement(int i, int j, Complex Z){
			M_[dim_*i+j]=Z;
		}

		//Matrix Methods
		CMat Minor(int i,int j){
			Complex M[Max_ent];
			ReduceDim(M_,M,dim_,i,j);
			return CMat(dim_-1,M);
		}
		Complex Determinant(){
			Complex Z=Complex(0,0);
			if(dim_==1){
				return M_[0];
			}
			else{
				for(int i=0;i<dim_;i++){
					Z=Z+PM(i)*M_[i]*(Minor(i,0).Determinant());
				}
			}
			return Z;	
		}
		CMat operator=(CMat B){
			Complex M[Max_ent];
			for(int i=0;i<dim_;i++){
				for(int j=0;j<dim_;j++){
					M[i*dim_+j]=M_[i*dim_+j];
				}
			}
			return CMat(dim_,M);
		}
		CMat operator+(CMat B){
			Complex M[Max_ent];
			if(dim_!=	B.Dim()){
				cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
				return B;
			}
			else{
				for(int i=0;i<dim_;i++){
					for(int j=0;j<dim_;j++){
						M[dim_*i+j]=M_[dim_*i+j]+B.GetElement(i,j);
					}
				}
			}
			return CMat(dim_,M);
		}
		CMat operator-(CMat B){
			Complex M[Max_ent];
			if(dim_!=	B.Dim()){
				cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
				return B;
			}
			else{
				for(int i=0;i<dim_;i++){
					for(int j=0;j<dim_;j++){
						M[dim_*i+j]=M_[dim_*i+j]-B.GetElement(i,j);
					}
				}
			}
			return CMat(dim_,M);
		}
		CMat operator*(CMat B){
			Complex M[Max_ent];
			if(dim_!=	B.Dim()){
				cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
			}
			else{
				for(int i=0;i<dim_;i++){
					for(int j=0;j<dim_;j++){
						for(int k=0;k<dim_;k++){
							M[dim_*i+j]+=M_[j*dim_+k]*B.GetElement(k,i);
						}
					}
				}
			}
			return CMat(dim_,M);
		}

		//Advanced Operation
		Complex Trace(){
			Complex Z;
			for(int i=0;i<dim_;i++){
				Z+=M_[i*i];
			}
			return Z;
		}
		CMat Transpose(){
			Complex M[Max_ent];
			for(int i=0;i<dim_;i++){
				for(int j=0;j<dim_;j++){
					M[j*dim_+i]=M_[i*dim_+j];
				}
			}
			return CMat(dim_,M);
		}
		CMat Conjugate(){
			Complex M[Max_ent];
			for(int i=0;i<dim_;i++){
				for(int j=0;j<dim_;j++){
					M[j*dim_+i]=M_[i*dim_+j].Conjugate();
				}
			}
			return CMat(dim_,M);
		}
		CMat Inverse(){
			Complex M[Max_ent];	
			for(int i=0;i<dim_;i++){
				for(int j=0;j<dim_;j++){
					M[j*dim_+i]=PM(i+j)*(Minor(j,i).Determinant())/Determinant();
				}
			}
			return CMat(dim_,M);
		}
};
CMat operator*( Complex B,CMat A){
	int dim=A.Dim();
	Complex MOut[dim*dim];
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			MOut[dim*i+j]=0;
			MOut[dim*i+j]=A.GetElement(i,j)*B;
		}
	}
	CMat C(dim,MOut);
	return C;
}
CMat operator*( int B,CMat A){
	return C(B,0)*A;
}
CMat operator*( double B,CMat A){
	return C(B,0)*A;
}

CMat Bracket(CMat A, CMat B){
	return A*B-B*A;
}
#endif
