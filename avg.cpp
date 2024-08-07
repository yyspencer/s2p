#include <bits/stdc++.h>
//file system???
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
	double stype1val, stype2val, stype3val, stype4val;
};

vector<SParameter> data;
int type, unit;
string stype1, stype2, stype3, stype4;

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
		//cout<<line<<out;
		nums.clear();
		SParameter tmp;
		//after stores the line after replacing spaces with tabs
		if (!isdigit(line[0])){
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			size_t found=line.find("freq");
			if (found != string::npos){
				found = line.find("mag");
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
				int current=0;
				for (int i=0; i<line.size(); ++i){
					if (line[i]=='s'){
						if (current==0){
							stype1+=line[i];
							stype1+=line[i+1];
							stype1+=line[i+2];
						}
						else if (current==1){
							stype2+=line[i];
							stype2+=line[i+1];
							stype2+=line[i+2];
						}
						else if (current==2){
							stype3+=line[i];
							stype3+=line[i+1];
							stype3+=line[i+2];
						}
						else{
							stype4+=line[i];
							stype4+=line[i+1];
							stype4+=line[i+2];
						}
						current++;
					}
				}
			}
			found=line.find("khz");
			if (found != string::npos){
				unit=1000;
			}
			found=line.find("mhz");
			if (found != string::npos){
				unit=1000000;
			}
			found=line.find("ghz");
			if (found != string::npos){
				unit=1000000000;
			}
			continue;
		}
		if (stype1=="" && !isdigit(line[0])){
			int current=0;
			for (int i=0; i<line.size(); ++i){
				if (line[i]=='s' && i+2<line.size()){
					if (current==0){
						stype1+=line[i];
						stype1+=line[i+1];
						stype1+=line[i+2];
					}
					else if (current==1){
						stype2+=line[i];
						stype2+=line[i+1];
						stype2+=line[i+2];
					}
					else if (current==2){
						stype3+=line[i];
						stype3+=line[i+1];
						stype3+=line[i+2];
					}
					else{
						stype4+=line[i];
						stype4+=line[i+1];
						stype4+=line[i+2];
					}
					current++;
				}
			}
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
		if (!nums.size())
			cout<<"line extraction error"<<out;
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
				tmp.stype1val=20*log10(tmp.s11.X);
				tmp.stype2val=20*log10(tmp.sx1.X);
				tmp.stype3val=20*log10(tmp.s1x.X);
				tmp.stype4val=20*log10(tmp.sxx.X);
				break;
			case 2:
				tmp.stype1val=tmp.s11.X;
				tmp.stype2val=tmp.sx1.X;
				tmp.stype3val=tmp.s1x.X;
				tmp.stype4val=tmp.sxx.X;
				break;
			case 3:
				tmp.stype1val=20*log10(sqrt(tmp.s11.X*tmp.s11.X+tmp.s11.Y*tmp.s11.Y));
				tmp.stype2val=20*log10(sqrt(tmp.sx1.X*tmp.sx1.X+tmp.sx1.Y*tmp.sx1.Y));
				tmp.stype3val=20*log10(sqrt(tmp.s1x.X*tmp.s1x.X+tmp.s1x.Y*tmp.s1x.Y));
				tmp.stype4val=20*log10(sqrt(tmp.sxx.X*tmp.sxx.X+tmp.sxx.Y*tmp.sxx.Y));
				break;
		}
		if (unit==1){
			//hz
			tmp.freq/=1000000;
		}
		else if (unit==1000){
			//khz
			tmp.freq/=1000;
		}
		else if (unit==1000000000){
			//ghz
			tmp.freq*=1000;
		}
		//mhz can be ignored
		data.pub(tmp);
	}
	if (!data.size()){
		cout<<"Data extraction error"<<out;
		return;
	}
	/*
	for (int i=0; i<data.size(); ++i){
		cout<<i<<": "<<data[i].freq<<" "<<data[i].stype1val<<" "<<data[i].stype2val<<" "<<data[i].stype3val<<" "<<data[i].stype4val<<out;
	}
	*/
	if (data.size()==0){
		cout<<"Database error, no data in database"<<out;
		return;
	}
	char dec='c';
	while (dec!='q'){
		cout<<"Do you wish to continue calculating average on "<<filename<<"?"<<out;
		cout<<"press c to continue, q to quit: ";
		cin>>dec;
		if (dec=='q'){
			break;
		}
		cout<<"For average, please enter starting and end points in MHz"<<out;
		cout<<"Range is "<<data[0].freq<<" to "<<data[data.size()-1].freq<<" MHz"<<out;
		cout<<"You're entering starting value: ";
		double start, end, s11avg=0, sx1avg=0, s1xavg=0, sxxavg=0;
		int cnt=0; 
		while (cin>>start){
			cout<<"You're entering ending value: ";
			cin>>end;
			if (start>end){
				cout<<"Starting point is greater than end point, please re-enter"<<out;
				cout<<"You're entering starting value: ";
			}
			else
				break;
		}
		for (int i=0; i<data.size(); ++i){
			if (data[i].freq>=start && data[i].freq<=end){
				cnt++;
				s11avg+=data[i].stype1val;
				sx1avg+=data[i].stype2val;
				s1xavg+=data[i].stype3val;
				sxxavg+=data[i].stype4val;
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
		cout<<"The average values for the range are"<<out;
		cout<<stype1<<": "<<s11avg<<out;
		cout<<stype2<<": "<<sx1avg<<out;
		cout<<stype3<<": "<<s1xavg<<out;
		cout<<stype4<<": "<<sxxavg<<out;
	}
	input.close();
}

int main(){
	char exit='c';
	while (exit!='q'){
		cout<<"press q to quit, c to continue to perform on new file: ";
		cin>>exit;
		if (exit=='c'){
			stype1=stype2=stype3=stype4="";
			unit=1;
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