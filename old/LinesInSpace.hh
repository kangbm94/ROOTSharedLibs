#ifndef Lines_h 
#define Lines_h 1
vector<double> CrossProduct(vector<double> a, vector<double>b){
	vector<double> c(3);
	c[0]=a[1]*b[2]-b[1]*a[1];
	c[1]=a[2]*b[0]-b[2]*a[0];
	c[2]=a[0]*b[1]-b[0]*a[1];
	for(int i=0;i<3;i++){
//		cout<<c[i]<<endl;
	}
	return c;
}
double DotProduct(vector<double>a,vector<double>b){
	double val=0;
	for(int i=0;i<3;i++){
//		cout<<Form("a%d=%f,b%d=%f",i,a[i],i,b[i])<<endl;;
		val+=a[i]*b[i];
	}
//	cout<<val<<endl;
	return val;
}
double mag(vector<double>a){
	return sqrt(DotProduct(a,a));
}
class Line{
	private:
		double x0,y0,u0,v0;
		vector<double> dir;
	public:
		Line(double x, double y, double u, double v){
			x0=x;y0=y,u0=u;v0=v;
			double norm = sqrt(u*u+v*v+1);
			dir.resize(3);
			dir[0]=u/norm;
			dir[1]=v/norm;
			dir[2]=1./norm;
			
		}
		double GetX(double z){
			return x0+u0*z;
		}
		double GetY(double z){
			return y0+v0*z;
		}
		double GetU(){
			return u0;
		}
		double GetV(){
			return v0;
		}
		vector<double> Direction(){
			return dir;
		}
		double Distance(Line Other){
			vector<double> c = CrossProduct(Other.Direction(),dir);	
			vector<double> a(3) ;
			a[0]=Other.GetX(0)-x0;
			a[1]=Other.GetY(0)-y0;
			a[2]=0;
			double value = DotProduct(a,c)/mag(c);
			value= abs(value);
			return value;
		}
		double Angle(Line Other){
			double cosine = DotProduct(Other.Direction(),dir);
			return acos(cosine);
		}
		double Similarity(Line Other, double z1, double z2){
			double dx = x0-Other.GetX(0);	
			double du = u0-Other.GetU();	
			double dy = y0-Other.GetY(0);	
			double dv = v0-Other.GetV();
			double dz = abs(z2 - z1);
			double Dx= dx*dx+dx*du*dz+du*du*dz*dz/3;
			double Dy= dy*dy+dy*dv*dz+dv*dv*dz*dz/3;
			return Dx+Dy;
		}
};
#endif
