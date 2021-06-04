This is a Utility pack intended for use in ROOT macro.(https://root.cern.ch/)
To implement this pack you should place the source to ROOTSharedLibs(or any name you want), and write
"Rint.Logon: ~/ROOTSharedLibs/rootlogon.C"
into your ~/.rootrc 


####Complex Matrix Packages####
You can Declare complex number a+bi as,
		Complex z=C(a+bi);
And n-dimensional Complex Matrix as
		CMat A=CMat(n,Z);
where Z should be nxn array of Complex numbers. n is constrained up to 10, which can be easily expaned by modifying "Max_dim" in CMatrix.hh
Currently the code supports matrix product/summation/subtraction, taking minor/transpose/dagger/inverse matrix, and determinant calculation.(ofcourse, in Complex number).
Eigenvalue problem is not supported yet.
You can contact me via email kangbm@korea.ac.kr
