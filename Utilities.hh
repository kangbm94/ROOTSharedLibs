void Indicator(int i, int ent){
	int tot =ent/100;
	bool stat= i%tot;
	if(!stat){
		cout<<"\r"<<flush<<setw(2)<<i/tot<<" \%";
	}
	if(i==ent-1){
		cout<<"\r"<<flush<<"Loop 100%"<<endl;
	}
}
void Indicator(int i, int ent, TString Loopname){
	int tot =ent/100;
	bool stat= i%tot;
	if(i==0){
		cout<<Loopname+" :"<<endl;
}
	if(!stat){
		cout<<"\r"<<flush<<setw(2)<<"\r"<<i/tot<<" \%";
	}
	if(i==ent-1){
		cout<<"\r"<<flush;
		cout<<Loopname<< " : 100%"<<endl;
	}
}
void PressAnyKey(){	
		gSystem->ProcessEvents();
		cout<<"Press Enter to continue"<<endl;
		cin.ignore();
}
void FillHist(TString title, TTree* tree,TString branch,TCut cut){
	tree->Draw(branch+">>"+title,cut);
}
void FillHistColz(TString title, TTree* tree,TString branch,TCut cut){
	tree->Draw(branch+">>"+title,cut,"colz");
}





void ReadCSV(fstream& file, double* data){//
	string line,token;
	stringstream iss;
	int cnt=0;
		getline(file,line);
	iss<<line;
	while(getline(iss,token,',')){
		data[cnt]=stod(token);
		cnt++;
	}
}

