#include "Constants.hh"
#include "Math.hh"
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
void PressEnter(){	
	PressAnyKey();
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
void ReadCSV(fstream& file, string* data){//
	string line,token;
	stringstream iss;
	int cnt=0;
	getline(file,line);
	iss<<line;
	while(getline(iss,token,',')){
		data[cnt]=token;
		cnt++;
	}
}
bool ReadingCSV(fstream& file, string* data){//
	string line,token;
	stringstream iss;
	int cnt=0;
	if(getline(file,line)){
	iss<<line;
		while(getline(iss,token,',')){
			data[cnt]=token;
			cnt++;
		}
	return true;}
	else{
		return false;
	}
}
void ReadTSV(fstream& file, double* data){//
	string line,token;
	stringstream iss;
	int cnt=0;
	getline(file,line);
	iss<<line;
	while(getline(iss,token,'	')){
		data[cnt]=stod(token);
		cnt++;
	}
}
void ReadTSV(fstream& file, string* data){//
	string line,token;
	stringstream iss;
	int cnt=0;
	getline(file,line);
	iss<<line;
	while(getline(iss,token,'	')){
		data[cnt]=token;
		cnt++;
	}
}
double DetectPeak(double* data, int nlength, int polarity){//polarity >0 -> positive; polarity <=0->negative;
	double var=data[0];
	if(polarity>0){
		for(int i=0;i<nlength;i++){
			var=Max(var,data[i]);
		}
	}
	else{
		for(int i=0;i<nlength;i++){
			var=Min(var,data[i]);
		}
	}
	return var;
}
