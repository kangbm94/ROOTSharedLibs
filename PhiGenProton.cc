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
void PhiGenProton(){
	double pK18 = 1800;
	TLorentzVector KBeam(0,0,0,KaonMass);
	TLorentzVector PTarget(0,0,0,ProtonMass);
	double gamma = sqrt(pK18*pK18+KaonMass*KaonMass)/KaonMass;
	double beta =Beta(gamma);
	KBeam.Boost(0,0,beta);
//	cout<<beta<<endl;
//	cout<<KBeam.Z()<<endl;
	TLorentzVector Vertex = KBeam+PTarget;
	double Mass[2]={LambdaMass,PhiZeroMass};
	double PhiDaughter[2]={KaonMass,KaonMass};
	double LambdaDaughter[2]={ProtonMass,PionMass};

	int nEvents = 1000000;
	TGenPhaseSpace Event;
	Event.SetDecay(Vertex,2,Mass);
	TCanvas* c1 = new TCanvas("C1","C1",1500,900);
	c1->Divide(2,2);
	TH1* h_x = new TH1D("Px","Px",1000,-500,500);
	TH1* h_z = new TH1D("Pz","Pz",1000,0,1000);
	TH1* h_theta = new TH1D("Cos_lab","Cos_lab",1000,0.8,1.05);
	TH2* h_tvt = new TH2D("Cos_labScat","Cos_labScat",100,0.85,1.05,100,0.85,1.05);
	TH1* h_tt = new TH1D("Cos_K*Klab","Cos_K*Klab",1000,0.7,1.05);
//	TH1* h_p = new TH1D("P","P",1000,500,1500);
	TH1* h_p = new TH1D("P","P",1000,-500,500);
	TH2* h_pvp = new TH2D("PionVsProton","PionVsProton",100,100,1200,100,-100,800);
	double ThCut=500;
	int cnt = 0;
	double ThetaCut = cos(15*Pi()/180);
	for(int i=0;i<nEvents;++i){
		Event.Generate();
		TLorentzVector* Lambda = Event.GetDecay(0);
		TLorentzVector* Phi = Event.GetDecay(1);
		TGenPhaseSpace PhiDecay;
		PhiDecay.SetDecay(*Phi,2,PhiDaughter);
		PhiDecay.Generate();
		TGenPhaseSpace LambdaDecay;
		LambdaDecay.SetDecay(*Lambda,2,LambdaDaughter);
		LambdaDecay.Generate();
		TLorentzVector* Proton = LambdaDecay.GetDecay(0);
		TLorentzVector* Pion = LambdaDecay.GetDecay(1);
		TLorentzVector* Kp = PhiDecay.GetDecay(0);
		TLorentzVector* Km = PhiDecay.GetDecay(1);
		h_x->Fill(Kp->X()-Km->X());
		h_z->Fill(Kp->Z());
		h_pvp->Fill(Kp->P(),Km->P());
		double angle =((Kp->X())*(Km->X())+(Kp->Y())*(Km->Y())+(Kp->Z())*(Km->Z())) /(Kp->P())/(Km->P());
//		h_tvt->Fill(Kp->CosTheta(),Km->CosTheta());
			h_pvp->Fill(Proton->P(),Pion->P());
			h_p->Fill(Phi->Py());
//			h_tvt->Fill(Kp->CosTheta(),Km->CosTheta());
			h_theta->Fill(Proton->CosTheta());
//			h_tt->Fill(angle);
		if(Kp->P()>ThCut&&Km->P()>ThCut&&Kp->CosTheta()<ThetaCut&&Km->CosTheta()<ThetaCut){
			cnt++;
//			h_tvt->Fill(Kp->CosTheta()+0.2,Km->CosTheta()+0.2);
		}
	}
	cout<<(double)cnt/nEvents * 100<<endl;
	TLine* ThetaCutV = new TLine(ThetaCut,0.9,ThetaCut,1.1);
	TLine* ThetaCutH = new TLine(0.9,ThetaCut,1.1,ThetaCut);
	TLine* KpCut = new TLine(ThCut,-100,ThCut,800);
	TLine* KmCut = new TLine(100,ThCut,1200,ThCut);
	
	
	KpCut->SetLineWidth(2);
	KpCut->SetLineColor(kRed);
	KmCut->SetLineWidth(2);
	KmCut->SetLineColor(kRed);
	
	ThetaCutV->SetLineWidth(2);
	ThetaCutV->SetLineColor(kRed);
	ThetaCutH->SetLineWidth(2);
	ThetaCutH->SetLineColor(kRed);
	
	c1->cd(1);
	h_theta->Draw();
	c1->cd(2);
	h_tvt->Draw("col");
//	ThetaCutV->Draw("same");
//	ThetaCutH->Draw("same");
	c1->cd(3);
	h_tt->Draw();
	c1->cd(4);
	h_p->Draw();
//	h_pvp->Draw("col");
//	KpCut->Draw("same");
//	KmCut->Draw("same");
}
