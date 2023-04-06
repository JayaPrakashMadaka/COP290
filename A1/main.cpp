#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <thread>
#include"dnn_weights.h"
#include"libaudio.h"
using namespace std;

string get(int a){
	string sound[12]={"_silence_", "_unknown_", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
	return sound[a];
}

int main(int argc,char* argv[]){
	
	pred_t p[3]={{0,0},{0,0},{0,0}};
	pred_t* pred =p;
	pred = libaudioAPI(argv[1],pred);
	ofstream outfile;
	
	outfile.open(argv[2],ios_base::app); // append instead of overwrite
	string sound1=get(pred[0].label);
	string sound2=get(pred[1].label);
	string sound3=get(pred[2].label);
  	outfile <<argv[1]<<" "<<sound1<<" "<<sound2<<" "<<sound3<<" "<<pred[0].prob<<" "<<pred[1].prob<<" "<<pred[2].prob<<"\n"; 
  	return 0;
}
