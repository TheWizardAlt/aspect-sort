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
        sorter(double minAR, double maxAR);
        sorter(string folderPath, double minAR, double maxAR);
        //gets and sets!
        void setSearchPath(string path);
        string getSearchPath();
        void setOutputPath(string path);
        string getOutputPath(); 
        void setMinAR(double minAR);
        double getMinAspectRatio();
        void setMaxAR(double minAR); 
        double getMaxAspectRatio();
        int getTotalImagePaths();
        //to string! prints all the infos in a nice format
        string toString();
        //the meat and the potatoes of functions
        vector<string> findImages(bool showInfo = false); //Note: setting this to true signifigantly slows it down....
        vector<string> loadImageDatabase();
        void aspectSort(bool showInfo = false);
    private:
        string searchingPath; //default searching path
        string outputPath = "./sort/"; //TODO: properly impliment this!
        double minAspectRatio; //Default minimum aspect ratio
        double maxAspectRatio; //Default maximum aspect ratio
        vector<string> imagePaths;
        int totalImagePaths = 0;
        string databasePath = "d.csv";
        vector<string> imageDatabase;
        double getImageAspect(string imagePath);
};