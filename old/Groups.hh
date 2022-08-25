#include "CMatrix.hh"
//SU2
		Complex Paulix[4]={
			C(0,0),C(1,0)
				,C(1,0),C(0,0)};
		Complex Pauliy[4]={
			C(0,0),C(0,-1),
			C(0,1),C(0,0)};
		Complex Pauliz[4]={
			C(1,0),C(0,0),
			C(0,0),C(-1,0)};
		CMat sigma_x(2,Paulix);
		CMat sigma_y(2,Pauliy);
		CMat sigma_z(2,Pauliz);
		

//SU3
		Complex Lambda1[9]={
			C(0,0),C(1,0),C(0,0),
			C(1,0),C(0,0),C(0,0),
			C(0,0),C(0,0),C(0,0)};
		Complex Lambda2[9]={
			C(0,0),C(0,-1),C(0,0),
			C(0,1),C(0,0),C(0,0),
			C(0,0),C(0,0),C(0,0)};
		Complex Lambda3[9]={
			C(1,0),C(0,0),C(0,0),
			C(0,0),C(-1,0),C(0,0),
			C(0,0),C(0,0),C(0,0)};
		Complex Lambda4[9]={
			C(0,0),C(0,0),C(1,0),
			C(0,0),C(0,0),C(0,0),
			C(1,0),C(0,0),C(0,0)};
		Complex Lambda5[9]={
			C(0,0),C(0,0),C(0,-1),
			C(0,0),C(0,0),C(0,0),
			C(0,1),C(0,0),C(0,0)};
		Complex Lambda6[9]={
			C(0,0),C(0,0),C(0,0),
			C(0,0),C(0,0),C(1,0),
			C(0,0),C(1,0),C(0,0)};
		Complex Lambda7[9]={
			C(0,0),C(1,0),C(0,0),
			C(1,0),C(0,0),C(0,0),
			C(0,0),C(0,0),C(0,0)};
		Complex Lambda8[9]={
			C(0,0),C(0,0),C(0,0),
			C(0,0),C(0,0),C(0,-1),
			C(0,0),C(0,1),C(0,0)};
		Complex Lambda9[9]={
			C(1,0),C(0,0),C(0,0),
			C(0,0),C(1,0),C(0,0),
			C(0,0),C(0,0),C(-2,0)};
		CMat l_1(3,Lambda1); 
		CMat l_2(3,Lambda2); 
		CMat l_3(3,Lambda3); 
		CMat l_4(3,Lambda4); 
		CMat l_5(3,Lambda5); 
		CMat l_6(3,Lambda6); 
		CMat l_7(3,Lambda7); 
		CMat l_8(3,Lambda8); 
		CMat l_9(3,Lambda9); 
