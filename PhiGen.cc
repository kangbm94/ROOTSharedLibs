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
void PhiGen(){
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
	TH1* h_ptheta = new TH1D("Theta_PhiLab","Theta_PhiLab",1000,-5,10);
	TH2* h_tvt = new TH2D("KmKpScat_Lab","KmKpScat_Lab",100,11,22,100,11,22);
	TH1* h_tt = new TH1D("Cos_K*Klab","Cos_K*Klab",1000,0.7,1.05);
	TH1* h_p = new TH1D("P","P",1000,0,1000);
	TH1* h_pp = new TH1D("PhiMom","PhiMom",1000,500,1500);
	TH1* h_ppi = new TH1D("PionMom","PionMom",1000,-1500,1500);
	TH1* h_mm = new TH1D("MissMass","MissMass",1000,1000,1200);
	TH1* h_res = new TH1D("MissMassRes","MissMassRes",1000,-20,20);
	TH2* h_pvp = new TH2D("PkpVSPkm","PkpVSPkm",100,450,650,100,450,650);
	double ThCut=500;
	int cnt = 0;
	double ThetaCut = cos(15*Pi()/180);
	double ThetaThreshold = 13;
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
		TLorentzVector* Kp = PhiDecay.GetDecay(0);
		TLorentzVector* Km = PhiDecay.GetDecay(1);
		TLorentzVector* Proton = LambdaDecay.GetDecay(0);
		TLorentzVector* Pim = LambdaDecay.GetDecay(1);
		h_x->Fill(Kp->X()-Km->X());
		h_z->Fill(Kp->Z());
		TLorentzVector PhiRecon = *Km+*Kp;
		TLorentzVector MissMass = Vertex-PhiRecon;
		TLorentzVector Res = *Lambda-MissMass;
		double angle =((Kp->X())*(Km->X())+(Kp->Y())*(Km->Y())+(Kp->Z())*(Km->Z())) /(Kp->P())/(Km->P());
//		h_tvt->Fill(Kp->CosTheta(),Km->CosTheta());
		if((Kp->P()>ThCut&&Km->P()>ThCut)){
			cnt++;
//			h_tvt->Fill(Kp->CosTheta()+0.2,Km->CosTheta()+0.2);
			h_pvp->Fill(Kp->P(),Km->P());
			h_tvt->Fill(Kp->Theta()*180/Pi(),Km->Theta()*180/Pi());
			h_theta->Fill(Kp->CosTheta());
			h_tt->Fill(angle);
			h_mm->Fill(MissMass.Mag());
			h_res->Fill(Res.Mag());
			h_pp->Fill(Phi->P());
			h_ppi->Fill(Pim->P());
			h_ptheta->Fill(Phi->Theta()*180/Pi());
		}
	}
	cout<<(double)cnt/nEvents * 100<<endl;
	TLine* ThetaCutV = new TLine(ThetaThreshold,11,ThetaThreshold,22);
	TLine* ThetaCutH = new TLine(11,ThetaThreshold,22,ThetaThreshold);
	TLine* ThetaCutV2 = new TLine(ThetaThreshold+1,11,ThetaThreshold+1,22);
	TLine* ThetaCutH2 = new TLine(11,ThetaThreshold+1,22,ThetaThreshold+1);
	TLine* KpCut = new TLine(ThCut,100,ThCut,800);
	TLine* KmCut = new TLine(100,ThCut,800,ThCut);
	
	
	KpCut->SetLineWidth(2);
	KpCut->SetLineColor(kRed);
	KmCut->SetLineWidth(2);
	KmCut->SetLineColor(kRed);
	
	ThetaCutV->SetLineWidth(2);
	ThetaCutV->SetLineColor(kRed);
	ThetaCutH->SetLineWidth(2);
	ThetaCutH->SetLineColor(kRed);
	
	ThetaCutV2->SetLineWidth(2);
	ThetaCutV2->SetLineColor(kBlue);
	ThetaCutH2->SetLineWidth(2);
	ThetaCutH2->SetLineColor(kBlue);
	
	c1->cd(1);
//	h_theta->Draw();
//	h_mm->Draw();
	h_pp->Draw();
	c1->cd(2);
	h_ptheta->Draw();
	c1->cd(3);
	h_tvt->Draw("col");
	h_tvt->GetXaxis()->SetTitle("KAngle_Lab[degree]");
	h_tvt->GetYaxis()->SetTitle("KAngle_Lab[degree]");
	ThetaCutV->Draw("same");
	ThetaCutH->Draw("same");
	ThetaCutV2->Draw("same");
	ThetaCutH2->Draw("same");
//	h_tt->Draw();
	c1->cd(4);
//	h_p->Draw();
	h_pvp->Draw("col");
	KpCut->Draw("same");
	KmCut->Draw("same");
	h_pvp->GetXaxis()->SetTitle("KMomentum_Lab[MeV/c]");
	h_pvp->GetYaxis()->SetTitle("KMomentum_Lab[MeV/c]");
}
