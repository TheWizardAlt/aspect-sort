#include "sorter.h"

sorter::sorter():sorter("~/Pictures/"){ }
sorter::sorter(string folderPath):sorter(folderPath, 1.3, 1.8){}
sorter::sorter(double minAR, double maxAR):sorter("~/Pictures/", minAR, maxAR){}
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

vector<string> sorter::findImages(bool showInfo){
    //clear vector of previous runs (just in case)
    imagePaths.clear();
    //search directories recursively
    //TODO: add a non recursive flag
    int checkedCount = 0; //keep track of how many files checked
    for(auto &p : fs::recursive_directory_iterator(searchingPath)){
        //convert the path given to a string
        stringstream ss; ss << p;
        string curPath = ss.str();
        //list of extenstions we want
        vector<string> exts = {".jpg",".jpeg",".png"}; //devIL can handle many TODO: add a selection for filetypes
        for(string ext :exts){ //run through the list and take files that match
            //dont look at the output path files
            if(curPath.find(outputPath) == -1 && curPath.find(ext) != -1){
                //remove the "" from the path (The path is converted to something like "/path/to/file/file.ext")
                curPath.erase(remove(curPath.begin(),curPath.end(),'"'),curPath.end());
                imagePaths.push_back(curPath);
                if(showInfo) system("clear");
                if(showInfo) cout << "Searching Files: " << imagePaths.size() << "/" << checkedCount << " : " << curPath << endl;
                break; //bad code but leave the for loop
            }
        } //you could also peek the bytes, this is much faster though
        checkedCount++;
    }
    return imagePaths;
}

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