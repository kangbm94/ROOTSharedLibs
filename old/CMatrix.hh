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
		/*
		 * void SetElement(int row, int column, int a){
		 int i=row-1,j=column-1;
		 M_[dim_*i+j]=Complex(a,0);
		 }
		 void SetElement(int row, int column, double a){
		 int i=row-1,j=column-1;
		 M_[dim_*(i-1)+j-1]=Complex(a,0);
		 }
		 */
		void SetElement(int row, int column, Complex Z){//Beware of Usage
			int i=row-1,j=column-1;
			M_[dim_*(i-1)+j-1]=Z;
		}
		CMat This(){
			return CMat(dim_,M_);
		}
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
		void Show();
		Complex GetElement(int row, int column);
		CMat GetRow(int n);
		CMat GetColumn(int n);
		CMat MoveRow(int bf, int af);
		CMat MoveColumn(int bf, int af);
		CMat ChangeRow(int r1, int r2);
		CMat ChangeColumn(int c1, int c2);

		//Matrix Methods
		CMat Minor(int row,int column);
		Complex Determinant();
		CMat operator=(CMat B);
		CMat operator+(CMat B);
		CMat operator-(CMat B);
		CMat operator*(CMat B);
		//Advanced Operation
		Complex Trace();
		CMat Transpose();
		CMat Conjugate();
		CMat Inverse();
		CMat Diagonalize();
};
void CMat::Show(){
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
Complex CMat::GetElement(int row,int column){
	int i=row-1,j=column-1;
	if(i<dim_&&j<dim_){
		return M_[dim_*i+j];
	}
	else{
		cout<<"Dimmesion Error"<<endl;
		return Complex(0,0);
	}
}
CMat CMat::Minor(int row, int col){
	int i = col-1,j=row-1;
	Complex M[Max_ent];
	ReduceDim(M_,M,dim_,i,j);
	return CMat(dim_-1,M);
}
Complex CMat::Determinant(){
	Complex Z=Complex(0,0);
	if(dim_==1){
		return M_[0];
	}
	else{
		for(int i=0;i<dim_;i++){
			Z=Z+PM(i)*M_[i]*(Minor(1,i+1).Determinant());
		}
	}
	return Z;	
}
CMat CMat::operator=(CMat B){
	Complex M[Max_ent];
	for(int i=0;i<dim_;i++){
		for(int j=0;j<dim_;j++){
			M[i*dim_+j]=M_[i*dim_+j];
		}
	}
	return CMat(dim_,M);
}
CMat CMat::operator+(CMat B){
	Complex M[Max_ent];
	if(dim_!=	B.Dim()){
		cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
		return B;
	}
	else{
		for(int i=0;i<dim_;i++){
			for(int j=0;j<dim_;j++){
				M[dim_*i+j]=M_[dim_*i+j]+B.GetElement(i+1,j+1);
			}
		}
	}
	return CMat(dim_,M);
}
CMat CMat::operator-(CMat B){
	Complex M[Max_ent];
	if(dim_!=	B.Dim()){
		cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
		return B;
	}
	else{
		for(int i=0;i<dim_;i++){
			for(int j=0;j<dim_;j++){
				M[dim_*i+j]=M_[dim_*i+j]-B.GetElement(i+1,j+1);
			}
		}
	}
	return CMat(dim_,M);
}
CMat CMat::operator*(CMat B){
	Complex M[Max_ent];
	if(dim_!=	B.Dim()){
		cout<<"Warning:: Summing Matrices with different dimensions!"<<endl;
	}
	else{
		for(int i=0;i<dim_;i++){
			for(int j=0;j<dim_;j++){
				for(int k=0;k<dim_;k++){
					M[dim_*j+i]+=This().GetElement(j+1,k+1)*B.GetElement(k+1,i+1);
				}
			}
		}
	}
	return CMat(dim_,M);
}
Complex CMat::Trace(){
	Complex Z;
	for(int i=0;i<dim_;i++){
		Z+=M_[i*i];
	}
	return Z;
}
CMat CMat::Transpose(){
	Complex M[Max_ent];
	for(int i=0;i<dim_;i++){
		for(int j=0;j<dim_;j++){
			M[j*dim_+i]=M_[i*dim_+j];
		}
	}
	return CMat(dim_,M);
}
CMat CMat::Conjugate(){
	Complex M[Max_ent];
	for(int i=0;i<dim_;i++){
		for(int j=0;j<dim_;j++){
			M[j*dim_+i]=M_[i*dim_+j].Conjugate();
		}
	}
	return CMat(dim_,M);
}
CMat CMat::Inverse(){
	Complex M[Max_ent];	
	for(int i=0;i<dim_;i++){
		for(int j=0;j<dim_;j++){
			M[i*dim_+j]=PM(i+j)*(Minor(j+1,i+1).Determinant())/Determinant();
		}
	}
	return CMat(dim_,M);
}
CMat CMat::Diagonalize(){
	return CMat(dim_,M_);
}
CMat CMat::GetRow(int n){
	Complex M[Max_ent];
	for(int row=0;row<dim_;row++){
		for(int col=0;col<dim_;col++){
			if(row==n-1){
				M[row*dim_+col]=M_[row*dim_+col];
			}
			else{
				M[row*dim_+col]=C(0,0);
			}
		}
	}
	return CMat(dim_,M);
}
CMat CMat::GetColumn(int n){
	Complex M[Max_ent];
	for(int row=0;row<dim_;row++){
		for(int col=0;col<dim_;col++){
			if(col==n-1){
				M[row*dim_+col]=M_[row*dim_+col];
			}
			else{
				M[col*dim_+col]=C(0,0);
			}
		}
	}
	return CMat(dim_,M);
}
CMat CMat::MoveRow(int bf, int af){
	Complex M[Max_ent];
	for(int row=0;row<dim_;row++){
		for(int col=0;col<dim_;col++){
			M[(af-1)*dim_+col]= This().GetRow(bf).GetElement(bf,col+1);
		}
	}
	return CMat(dim_,M);
}
CMat CMat::MoveColumn(int bf, int af){
	Complex M[Max_ent];
	for(int row=0;row<dim_;row++){
		for(int col=0;col<dim_;col++){
			M[row*dim_+af-1]= This().GetColumn(bf).GetElement(row+1,bf);
		}
	}
	return CMat(dim_,M);
}
CMat CMat::ChangeRow(int r1, int r2){
	CMat R1 = This().GetRow(r1);
	CMat R1_=R1.MoveRow(r1,r2);
	CMat R2 = This().GetRow(r2);
	CMat R2_=R2.MoveRow(r2,r1);
	return This()-R1-R2+R1_+R2_;
}
CMat CMat::ChangeColumn(int c1, int c2){
	CMat C1 = This().GetColumn(c1);
	CMat C1_=C1.MoveColumn(c1,c2);
	CMat C2 = This().GetColumn(c2);
	CMat C2_=C2.MoveColumn(c2,c1);
	return This()-C1-C2+C1_+C2_;
}




CMat operator*( Complex B,CMat A){
	int dim=A.Dim();
	Complex MOut[dim*dim];
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			MOut[dim*i+j]=A.GetElement(i+1,j+1)*B;
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
