#include "../Math.hh"
int Factorize(int nbin, double min, double max, double input){
	double delta = max-min;
	double step = delta/nbin;
	int bin = (input-min)/step;
	if(bin<0){
		cout<<"Warining::Unerflow, bin set to 0"<<endl;
		bin=0;
	}
	if(bin>=nbin){
		cout<<"Warining::Overflow, bin set to Max"<<endl;
		bin=nbin-1;
	}
	return bin;
}
void Hough(){
	gRandom->SetSeed();
	const int np=100;
	TCanvas* c1 = new TCanvas("c1","c1",800,800);
	c1->DrawFrame(-10,10,-10,10);
	c1->SetGrid();
	TGraph* gr = new TGraph(np);
	gr->SetMarkerStyle(3);
	double cx,cy;
	cx = gRandom->Uniform(-2,2);
	cy = gRandom->Uniform(-2,2);
	double x[np],y[np];
	for(int i=0;i<100;++i){
		gRandom->Circle(x[i],y[i],gRandom->Gaus(5,0.1));
		x[i]+=cx;y[i]+=cy;
		gr->SetPoint(i,x[i],y[i]);
	}
	gr->Draw("AP");	
	gr->GetXaxis()->SetLimits(-10,10);
	gr->GetYaxis()->SetRangeUser(-10,10);
	const int x_bin = 100/2,y_bin=100/2,r_bin=100;
	double x_m=-10,x_M=10,y_m=-10,y_M=10,r_m=1,r_M=7;
	int Hough[2*x_bin][2*y_bin][r_bin]={0};
	for(int ir=0;ir<r_bin;++ir){
		double rad = r_m+(r_M-r_m)*(double)ir/r_bin-1e-10; 
		for(int ip=0;ip<np;++ip){
			for(int ith=0;ith<360;++ith){
				double hx=x[ip]+rad*cos(ith*Pi()/180.);
				double hy=y[ip]+rad*sin(ith*Pi()/180.);
				int xb = Factorize(2*x_bin,1.5*x_m,1.5*x_M,hx);
				int yb = Factorize(2*y_bin,1.5*y_m,1.5*y_M,hy);
				Hough[xb][yb][ir]++;
			}
		}
	}
	cout<<Form("Center : (%2f,%2f)",cx,cy)<<endl;
	TH2D* h = new TH2D("h3","h3",x_bin,x_m,x_M,y_bin,y_m,y_M);
	double b = 0;
	double b_comp=0;
	double cx_cnd,cy_cnd;
	for(int ix=0;ix<2*x_bin;++ix){
		for(int iy=0;iy<2*y_bin;++iy){
			for(int ir=0;ir<r_bin;++ir){
				b_comp=b;
				b=Max(b,Hough[ix][iy][ir]);
				if(b_comp!=b){
					cx_cnd=1.5*x_m+1.5*(x_M-x_m)/x_bin/2*ix;
					cy_cnd=1.5*y_m+1.5*(y_M-y_m)/y_bin/2*iy;
				}
			}
//			double x_pos = x_m+(x_M-x_m)/x_bin*ix;
//			double y_pos = y_m+(y_M-y_m)/y_bin*iy;
//			h->SetBinContent(x_pos,y_pos,Hough[ix][iy][Factorize(r_bin,r_m,r_M,4)]);	
//			h->SetBinContent(ix,iy,Hough[ix][iy][Factorize(r_bin,r_m,r_M,4)]);	
		}
	}
	cout<<b<<endl;
	cout<<Form("Hough Center : (%2f,%2f)",cx_cnd,cy_cnd)<<endl;
/*
	TH2D* h = new TH2D("h3","h3",x_bin,x_m,x_M,y_bin,y_m,y_M);
	TCanvas* c2 = new TCanvas("c2","c2",800,800);
	c2->DrawFrame(-10,10,-10,10);
	c2->SetGrid();
	h->Draw("colz");
	cout<<h->GetMaximumBin()<<endl;*/
}
