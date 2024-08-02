#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
#define pub push_back
#define mp make_pair
#define pob pop_back
#define X first
#define Y second
#define out '\n'
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int inf=0x3f3f3f3f;

struct SParameter{
	double freq;
	pair <double, double> s11;
	pair <double, double> sx1;
	pair <double, double> s1x;
	pair <double, double> sxx;
	double s11val, sx1val, s1xval, sxxval;
	string s11type="", sx1type="", s1xtype="", sxxtype="", unit="";
};

vector<SParameter> data;
int type;

bool stringToDouble(string& str, double& result) {
    std::stringstream ss(str);
    ss >> result;
    return !ss.fail() && ss.eof(); // Ensure entire string was converted
}

void solve(string filename){
	data.clear();
	vector<string> nums;
	type=0;
	while (data.size()){
		data.pob();
	}
	ifstream input(filename);
	if (!input.is_open()){
		cout<<"Error opening file or couldn't find file"<<out;
		return;
	}
	string line, s; //line is the read line, and nums stores the values
	while(getline(input, line)){//extract input to lines
		nums.clear();
		//after stores the line after replacing spaces with tabs
		int pos=0;
		for (int i=0; i<line.size(); ++i){
			if (line[i]==' '){
				pos=i;
				break;
			}
		}
		line.erase(line.begin(), line.begin()+pos);
		if (!isdigit(line[0]) && !type){
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			size_t found = line.find("mag");
			if (found != string::npos){
				type=1;
			}
			found = line.find("db");
			if (found != string::npos){
				type=2;
			}
			found = line.find("im");
			if (found != string::npos){
				type=3;
			}
			continue;
		}
		if (!type){
			cout<<"no file format found, please enter data type"<<out;
			cout<<"Mag+Ang press 1"<<out;
			cout<<"dB+Ang press 2"<<out;
			cout<<"Re+Im press 3"<<out;
			cin>>type;
		}
		stringstream ss(line);
		while (getline(ss, s, '\t')){
			nums.pub(s);
		}
		for (int i=0; i<nums.size(); ++i){
			if (nums[i].size()==0){
				nums.erase(nums.begin()+i);
				i-=1;
			}
		}
		SParameter tmp;
		stringToDouble(nums[0], tmp.freq);
		stringToDouble(nums[1], tmp.s11.X);
		stringToDouble(nums[2], tmp.s11.Y);
		stringToDouble(nums[3], tmp.sx1.X);
		stringToDouble(nums[4], tmp.sx1.Y);
		stringToDouble(nums[5], tmp.s1x.X);
		stringToDouble(nums[6], tmp.s1x.Y);
		stringToDouble(nums[7], tmp.sxx.X);
		stringToDouble(nums[8], tmp.sxx.Y);
		switch(type){
			case 1:
				tmp.s11val=20*log10(tmp.s11.X);
				tmp.sx1val=20*log10(tmp.sx1.X);
				tmp.s1xval=20*log10(tmp.s1x.X);
				tmp.sxxval=20*log10(tmp.sxx.X);
				break;
			case 2:
				tmp.s11val=tmp.s11.X;
				tmp.sx1val=tmp.sx1.X;
				tmp.s1xval=tmp.s1x.X;
				tmp.sxxval=tmp.sxx.X;
				break;
			case 3:
				tmp.s11val=20*log10(sqrt(tmp.s11.X*tmp.s11.X+tmp.s11.Y*tmp.s11.Y));
				tmp.sx1val=20*log10(sqrt(tmp.sx1.X*tmp.sx1.X+tmp.sx1.Y*tmp.sx1.Y));
				tmp.s1xval=20*log10(sqrt(tmp.s1x.X*tmp.s1x.X+tmp.s1x.Y*tmp.s1x.Y));
				tmp.sxxval=20*log10(sqrt(tmp.sxx.X*tmp.sxx.X+tmp.sxx.Y*tmp.sxx.Y));
				break;
		}
		data.pub(tmp);
	}
	/*
	for (int i=0; i<data.size(); ++i){
		cout<<i<<": "<<data[i].freq<<" "<<data[i].s11val<<" "<<data[i].sx1val<<" "<<data[i].s1xval<<" "<<data[i].sxxval<<out;
	}
	*/
	if (data.size()==0){
		cout<<"Database error, no data in database"<<out;
		return;
	}
	cout<<"For average, please enter starting and end points"<<out;
	cout<<"Range is "<<data[0].freq<<" to "<<data[data.size()-1].freq<<out;
	double start, end, s11avg=0, sx1avg=0, s1xavg=0, sxxavg=0;
	int cnt=0; 
	while (cin>>start>>end){
		if (start>end){
			cout<<"Starting point is greater than end point, please re-enter"<<out;
		}
		else
			break;
	}
	for (int i=0; i<data.size(); ++i){
		if (data[i].freq>=start && data[i].freq<=end){
			cnt++;
			s11avg+=data[i].s11val;
			sx1avg+=data[i].sx1val;
			s1xavg+=data[i].s1xval;
			sxxavg+=data[i].sxxval;
		}
	}
	if (cnt==0){
		cout<<"there are no valid numbers in this database, please try again"<<out;
		return;
	}
	s11avg/=cnt;
	sx1avg/=cnt;
	s1xavg/=cnt;
	sxxavg/=cnt;
	cout<<"s11avg sx1avg s1xavg sxxavg"<<out;
	cout<<s11avg<<" "<<sx1avg<<" "<<s1xavg<<" "<<sxxavg<<out;
	input.close();
}
int main(){
	char exit='c';
	while (exit!='q'){
		cout<<"press q to quit, c to continue"<<out;
		cin>>exit;
		if (exit=='c'){
			string s;
			cout<<"please enter file name"<<out;
			cin>>s;
			s+=".s2p";
			solve(s);
		}
		else if (exit=='q')
			break;
		else{
			cout<<"invalid input, please try again."<<out;
		}
	}
}