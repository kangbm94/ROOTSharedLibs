int LeapYear(int year){
	int first = year/4;
	int second = year/100;
	int third = year/400;
	return first-second+third;
}
/*
int YearToDay(int year){//on Jan.1.
	year = year-1;
	return year*365+LeapYear(year);
}
*/
int MonthToDay(int Month,int year){//On the 1st day
	int Months[12]={
		31,28,31,30,
		31,30,31,31,
		30,31,30,31
	};
	int Feb = LeapYear(year)-LeapYear(year-1);
	Months[1]+=Feb;
	int Days=0;
	for(int i=0;i<Month-1;i++){
		Days+=Months[i];	
	}
	return Days;
}
int Day(int year,int month, int day){
	int Days=0;
	Days+=365*year+MonthToDay(month,year)+day;
	return Days;
}
