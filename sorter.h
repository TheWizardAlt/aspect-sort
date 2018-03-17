#include<IL/il.h>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<experimental/filesystem>
#include<vector>
#include<algorithm>
#include<libgen.h>
#include<ctime>
#include<cstdio>
using namespace std;
namespace fs = std::experimental::filesystem;

class sorter{
    public:
        //constructors!
        sorter();
        sorter(string folderPath);
        sorter(double minAR);
        sorter(double minAR, double maxAR);
        sorter(string folderPath, double minAR);
        sorter(string folderPath, double minAR, double maxAR);
        //gets and sets!
        void setPath(string path);
        string getPath(); 
        void setMinAR(double minAR);
        double getMinAspectRatio();
        void setMaxAR(double minAR); 
        double getMaxAspectRatio();
        //to string! prints all the infos in a nice format
        string toString();
    private:
        string searchingPath = "~/Pictures/"; //default searching path
        string outputPath = "~/Pictures/AspectSort/"; //the beginning of the end lmao
        double minAspectRatio = 1.3; //Default minimum aspect ratio
        double maxAspectRatio = 1.8; //Default maximum aspect ratio
};