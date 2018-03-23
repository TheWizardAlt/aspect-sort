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
        //run all the major stuff!
        void doWork();
        //constructors!
        sorter();
        sorter(string folderPath, string outPath);
        sorter(double minAR, double maxAR);
        sorter(string folderPath, double minAR, double maxAR, string output);
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
        int getTotalCreated();
        //to string! prints all the infos in a nice format
        string toString();
        //to csv! organizes in order you'd expect
        string toCSV();
        //the meat and the potatoes of functions
        vector<string> findImages(bool showInfo = false); //Note: setting this to true signifigantly slows it down....
        vector<string> loadImageDatabase();
        void aspectSort(bool showInfo = false);
    private:
        string searchingPath = "./"; //default searching path
        stringstream outputPath; //TODO: properly impliment this!
        double minAspectRatio = 1.3; //Default minimum aspect ratio
        double maxAspectRatio = 1.8; //Default maximum aspect ratio
        vector<string> imagePaths;
        int totalImagePaths = 0;
        string databasePath = "Database.csv";
        vector<string> imageDatabase;
        double getImageAspect(string imagePath);
        double getAspectFromCSV(string csv);
        int sysLinksCreated = 0;
};