void test(){
	const int nrvar = 2;
	const int nrpnt = 4;
	double ax[] = {0,1,2,3};
	double ay[] = {1.4,1.5,3.7,4.1};
	double ae[] = {0.5,0.2,1,0.5};
	
	TVectorD x; x.Use(nrpnt,ax);
	TVectorD y; y.Use(nrpnt,ax);
	TVectorD e; e.Use(nrpnt,ax);

	TMatrixD A(nrpnt,nrvar);
	TMatrixDColumn(A,0)=1.;
	TMatrixDColumn(A,1)=x;
	const TVectorD c_norm = NormalEqn(A,y,e);
	TMatrixD Aw = A;	
	TMatrixD yw = y;
	for( int row = 0;row<A.GetNrows();row++){
		TMatrixDRow(Aw,row) *= 1/e(irow);
		yw(irow) /=e(irow);
	}
}
