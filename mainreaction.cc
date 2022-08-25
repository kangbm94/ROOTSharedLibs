#include "Constants.hh"
double shift(double x,double p){
	return x-p;
}
double shiftl(double x,double p){
	return x+p;
}
double p2(double (*f) (double,double),double x, double* p,double a){
	return p[0]+p[1]*f(x,a)+p[2]*f(x,a)*f(x,a);
}
double Gamma(double v){
	return 1/sqrt(1-v*v);
}
double Beta(double gamma){
	return sqrt(1-1/gamma/gamma);
}
void mainreaction(){
	double pK18 = 1800;
	TLorentzVector KBeam(0,0,0,KaonMass);
	TLorentzVector PTarget(0,0,0,ProtonMass);
	double gamma = sqrt(pK18*pK18+KaonMass*KaonMass)/KaonMass;
	double beta =Beta(gamma);
	KBeam.Boost(0,0,beta);
//	cout<<beta<<endl;
//	cout<<KBeam.Z()<<endl;
	TLorentzVector Vertex = KBeam+PTarget;
	double Mass[2]={XiMass,KaonMass};
//	double LambdaDaughter[2]={KaonMass,KaonMass};

	int nEvents = 100000;
	TGenPhaseSpace Event;
	Event.SetDecay(Vertex,2,Mass);
	TCanvas* c1 = new TCanvas("C1","C1",1500,900);
	c1->Divide(2,2);
	TH1* h_x = new TH1D("Px","Px",1000,-500,500);
	TH1* h_z = new TH1D("Pz","Pz",1000,0,1000);
	TH1* h_theta = new TH1D("Cos_lab","Cos_lab",1000,-1.05,1.05);
	TH2* h_tvt = new TH2D("Cos_labScat","Cos_labScat",100,-1.1,1.1,100,0.8,1.1);
	TH1* h_p = new TH1D("PKp","PKp",1000,0,2000);
	TH1* h_px = new TH1D("PXi","PXi",1000,000,2000);
	TH2* h_pvp = new TH2D("PkpVSPkm","PkpVSPkm",1000,0,1000,1000,0,1000);
	for(int i=0;i<nEvents;++i){
		Event.Generate();
		TLorentzVector* Xi = Event.GetDecay(0);
		TLorentzVector* Kp = Event.GetDecay(1);
		h_p->Fill(Kp->P());
		h_px->Fill(Xi->P());
		h_pvp->Fill(Kp->P(),Xi->P());
		h_theta->Fill(Kp->CosTheta());
		h_tvt->Fill(Kp->CosTheta(),Xi->CosTheta());
	}
	c1->cd(1);
	h_theta->Draw();
	c1->cd(2);
	h_tvt->Draw("col");
	c1->cd(3);
	h_px->Draw();
	c1->cd(4);
	h_p->Draw();
//	h_pvp->Draw("col");
}
