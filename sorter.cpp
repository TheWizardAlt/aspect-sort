#include "sorter.h"

sorter::sorter():sorter(""){ } //NOTE you may wanna change this default path here
sorter::sorter(string folderPath):sorter(folderPath, 1.3, 1.8){}
sorter::sorter(double minAR, double maxAR):sorter("/home/", minAR, maxAR){} //NOTE you may wanna change this default path here
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
int sorter::getTotalImagePaths(){ return totalImagePaths; }

vector<string> sorter::findImages(bool showInfo){
    //clear of previous runs (just in case)
    imagePaths.clear();
    totalImagePaths = 0;
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
                if(showInfo) system("clear"); //TODO: Make protable
                if(showInfo) cout << "Searching Files: " << imagePaths.size() << "/" << checkedCount << " : " << curPath << endl;
                break; //bad code but leave the for loop
            }
        } //you could also peek the bytes, this is much faster though
        checkedCount++;
    }
    totalImagePaths = imagePaths.size();
    if(showInfo) cout << "Found " << totalImagePaths << " images!" << endl;
    return imagePaths;
}

vector<string> sorter::loadImageDatabase(){
    ifstream databaseStream;
    databaseStream.open(databasePath, ifstream::in);
    string entry = "";
    if(!databaseStream.fail())
        while(getline(databaseStream, entry))
            imageDatabase.push_back(entry);
    databaseStream.close();
    return imageDatabase;
}

void sorter::aspectSort(bool showInfo){
    //begin by sorting both vectors so it is easier to read from them
    sort(imageDatabase.begin(), imageDatabase.end());
    sort(imagePaths.begin(),imagePaths.end());
    //TODO: remove entries that are not in the imagepaths from the imagedatabase
    for(string imagePath : imagePaths){
        //check to make sure theres even a point
        if(minAspectRatio > maxAspectRatio){ cout << "Min aspect was bigger then max ascpect?" << endl; break;}
        double imageAspect = getImageAspect(imagePath);
        if(imageAspect >= minAspectRatio && imageAspect <= maxAspectRatio){
            string imageName = basename((char*)imagePath.c_str());
            string sysLinkPath = outputPath + imageName;
            if(!fileExists(sysLinkPath.c_str())){
                fs::create_directory_symlink(imagePath, sysLinkPath);
                if(showInfo) cout << "Created link: " << sysLinkPath << endl;
            }else{
                if(showInfo) cout << "Didn't create link: " << sysLinkPath << endl;
            }
        }else{
            if(showInfo) cout << "Wrong aspect ratio: " << imageAspect << " Image: " << imagePath << endl;
        }
    }

}

double sorter::getImageAspect(string imagePath){
    //quickly check the database to see if we already know the aspect
    //there can DEFINETLY be some optimizations to this...
    for(int i = 0; i < imageDatabase.size(); i++){
        string currentImagePath = imageDatabase[i];
        if(currentImagePath.find(imagePath,0) != -1){
            double savedAspect;
            //the values are stored like "path,value"
            string s = currentImagePath.substr(currentImagePath.find(',')+1);
            stringstream ss(s); //convert the number to a string stream
            ss >> savedAspect; //convert the string stream to a double
            imageDatabase.erase(imageDatabase.begin()+i); //remove current item to make future searches quicker
            return savedAspect;
        }
    }
    //we didn't have the value in the database so we need to fetch it using devIL
    //This could be done by looking at the specs for each image type and reading
    //in the bytes but thats a lot of work, lets not reinvent the wheel...
    ilInit();
    ILuint texid;
    ilGenImages(1, &texid);
    ilBindImage(texid);
    const ILstring pathCharArr = imagePath.c_str();
    bool success = ilLoadImage(pathCharArr);
    if(success){
        ILuint Width, Height;
        Width = ilGetInteger(IL_IMAGE_WIDTH);
        Height = ilGetInteger(IL_IMAGE_HEIGHT);
        unsigned int h = Height;
        unsigned int w = Width;
        double aspect = (double)w / (int)h;
        ilDeleteImages(1, &texid);
        ilClearImage();
        //TODO: database
        ofstream databaseStream;
        databaseStream.open(databasePath, ios::out | ios::app);
        databaseStream << imagePath << "," << aspect << "\n";
        databaseStream.close();

        return aspect;
    }
    return -1;
}

string sorter::toString(){
    stringstream ss;
    string s;

    ss << "Current searching path: " << getSearchPath() << endl;
    ss << "Current output folder: " << getOutputPath() << endl;
    ss << "Current minAR: " << getMinAspectRatio() << ":1" << endl;
    ss << "Current mazAR: " << getMaxAspectRatio() << ":1" << endl;
    ss << "Total Image Paths: " << getTotalImagePaths() << endl;

    ss << endl;
    s = ss.str();
    ss.clear();
    return s;
}

bool sorter::fileExists(const char *fileName){
    ifstream infile(fileName);
    return infile.good();
}