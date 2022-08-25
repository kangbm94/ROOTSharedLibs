void test2(){
	double a1[] = {2,2};
	double a2[] = {1,2};
	double b1[] = {4,4};
	double b2[] = {2,4};
	TVectorD A1;A1.Use(2,a1);
	TVectorD A2;A2.Use(2,a2);
	TVectorD B1;B1.Use(2,b1);
	TVectorD B2;B2.Use(2,b2);
	TMatrixD A(2,2);
	TMatrixDColumn(A,0)=A1;
	TMatrixDColumn(A,1)=A2;
	TMatrixD B(2,2);
	TMatrixDColumn(B,0)=B1;
	TMatrixDColumn(B,1)=B2;
	TMatrixD C = A<B;
	double a = A<3;
	double b = B<3;
	cout<<a<<endl;
	cout<<b<<endl;
	//	double c = C.Min();
//	cout<<c<<endl;
//	cout<<C.Min()<<endl;;
//	cout<<C.Max()<<endl;;
}
