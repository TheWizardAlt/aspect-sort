#include "sorter.h"

sorter::sorter(){ }
sorter::sorter(string folderPath){sorter(folderPath, minAspectRatio, maxAspectRatio);}
sorter::sorter(double minAR){sorter(searchingPath, minAR, maxAspectRatio);}
sorter::sorter(double minAR, double maxAR){sorter(searchingPath, minAR, maxAR);}
sorter::sorter(string folderPath, double minAR){sorter(folderPath, minAR, maxAspectRatio);}
sorter::sorter(string folderPath, double minAR, double maxAR){
    setSearchPath(folderPath);
    setMinAR(minAR);
    setMaxAR(maxAR);
}

void sorter::setSearchPath(string path){ searchingPath = path; }
string sorter::getSearchPath(){ return searchingPath; }
void sorter::setOutputPath(string path){ outputPath = path; }
string sorter::getOutputPath(){ return outputPath; }
void sorter::setMinAR(double minAR){ minAspectRatio = minAR; }
double sorter::getMinAspectRatio(){ return minAspectRatio; }
void sorter::setMaxAR(double maxAR){ maxAspectRatio = maxAR; }
double sorter::getMaxAspectRatio(){ return maxAspectRatio; }

string sorter::toString(){
    stringstream ss;
    string s;

    ss << "Current searching path: " << getSearchPath() << endl;
    ss << "Current output folder: " << getOutputPath() << endl;
    ss << "Current minAR: " << getMinAspectRatio() << ":1" << endl;
    ss << "Current mazAR: " << getMaxAspectRatio() << ":1" << endl;
    
    ss << endl;
    s = ss.str();
    ss.clear();
    return s;
}