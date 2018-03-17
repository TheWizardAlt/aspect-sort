#include "sorter.h"

sorter::sorter(){ }
sorter::sorter(string folderPath){sorter(folderPath, minAspectRatio, maxAspectRatio);}
sorter::sorter(double minAR){sorter(searchingPath, minAR, maxAspectRatio);}
sorter::sorter(double minAR, double maxAR){sorter(searchingPath, minAR, maxAR);}
sorter::sorter(string folderPath, double minAR){sorter(folderPath, minAR, maxAspectRatio);}
sorter::sorter(string folderPath, double minAR, double maxAR){
    setPath(folderPath);
    setMinAR(minAR);
    setMaxAR(maxAR);
}

void sorter::setPath(string path){ searchingPath = path; }
string sorter::getPath(){ return searchingPath; }
void sorter::setMinAR(double minAR){ minAspectRatio = minAR; }
double sorter::getMinAspectRatio(){ return minAspectRatio; }
void sorter::setMaxAR(double maxAR){ maxAspectRatio = maxAR; }
double sorter::getMaxAspectRatio(){ return maxAspectRatio; }

string sorter::toString(){
    stringstream ss;
    string s;
    
    ss << "Current searching path: " << searchingPath << endl;
    ss << "Current output folder: " << outputPath << endl;
    ss << "Current minAR: " << minAspectRatio << ":1" << endl;
    ss << "Current mazAR: " << maxAspectRatio << ":1" << endl;

    s = ss.str();
    ss.clear();
    return s;
}