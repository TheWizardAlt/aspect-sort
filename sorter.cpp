#include "sorter.h"

sorter::sorter():sorter("", ""){ } //NOTE you may wanna change this default path here
sorter::sorter(string folderPath, string outPath):sorter(folderPath, -1, -1, outPath){}
sorter::sorter(double minAR, double maxAR):sorter("", minAR, maxAR , ""){} //NOTE you may wanna change this default path here
sorter::sorter(string folderPath, double minAR, double maxAR, string outPath){
    if(folderPath != "" ) setSearchPath(folderPath);
    if(minAR != -1) setMinAR(minAR);
    if(maxAR != -1) setMaxAR(maxAR);
    if(outPath != "" ) setOutputPath(outPath);
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
int sorter::getTotalCreated(){ return sysLinksCreated; }

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
        while(getline(databaseStream, entry)){
            //TODO: This makes it slower, hrmmmmmmmm....
            double imageAspect = getAspectFromCSV(entry);
            bool aspectCheck =  true; //imageAspect >= minAspectRatio && imageAspect <= maxAspectRatio;
            if(aspectCheck && entry.find(searchingPath) != -1)
                imageDatabase.push_back(entry);
            // else if (!aspectCheck){
            //     for(int i = 0; i < imagePaths.size(); i++){
            //         if(imagePaths[0] == entry){
            //             cout << "Yeppers.";
            //             imagePaths.erase(imageDatabase.begin()+i);
            //         }
            //     }
            // }
        }
    databaseStream.close();
    return imageDatabase;
}

void sorter::aspectSort(bool showInfo){
    loadImageDatabase(); //load the images
    //begin by sorting both vectors so it is easier to read from them
    sort(imageDatabase.begin(), imageDatabase.end());
    sort(imagePaths.begin(),imagePaths.end());

    //load bar stuff TODO: refine this a bit :p
    int newCount = 0;
    int oldCount = 0;
    int progressCount = 0;
    int outOf = imagePaths.size();
    int oldBar = 0;
    int updateCount = 0;
    int updater = -1;

    stringstream opbkp(outputPath);
    opbkp << outputPath << minAspectRatio << "-" << maxAspectRatio << "/"; //This may cause problems TODO: fix
    for(string imagePath : imagePaths){
        //check to make sure theres even a point
        if(minAspectRatio > maxAspectRatio){ cout << "Min aspect was bigger then max ascpect?" << endl; break;}
        //create sorting directory
        if(!fs::exists(opbkp.str()))
            fs::create_directories(opbkp.str());
    
        double imageAspect = getImageAspect(imagePath);
        if(imageAspect >= minAspectRatio && imageAspect <= maxAspectRatio){
            //Figure out the name of the file
            string imageName = basename((char*)imagePath.c_str());
            //We can programically create a long-named system link but most operating
            //systems hate this. So lets shrink the name if it's too big
            string ext = imageName.substr(imageName.length() - 4, imageName.length()-1);
            if(imageName.length() > 160)
                imageName = imageName.substr(0,160) + ext;
            //get the SYSTEM LINK path
            string sysLinkPath = opbkp.str() + imageName;
            //check for the SYSTEM LINK
            bool fileExist = fs::exists(sysLinkPath);
            if(!fileExist){
                //sometimes the file exists even though we checked that....
                try{
                    //create the link
                    fs::create_directory_symlink(imagePath, sysLinkPath);
                    if(showInfo) cout << "Created link: " << sysLinkPath << endl;
                    //keep track
                    sysLinksCreated++;
                }catch(exception ex){}
            }else{
                //info for debugging, showing error with link creation
                if(showInfo) cout << "Didn't create link: " << sysLinkPath << endl;
            }

        }else{
            //A invalid aspec ratio, for debugging
            if(showInfo) cout << "Wrong aspect ratio: " << imageAspect << " Image: " << imagePath << endl;
        }
        //TODO: fix this garbage 
        progressCount++;
        bool showProgress = true;
        double progress = 0.0;
        if(showProgress){
            updater++;
            progress = ((double)progressCount / outOf);
            int barSize = 34;
            if(outOf < barSize)
                barSize = outOf;
            int newBar = progressCount / (outOf / barSize);
            if(updater == 0 || updater > 1000 || newBar > oldBar || progress == 1){
                updater = 1;
                system("clear");
                oldBar = newBar;
                cout << "[";
                int curBarSize = (progress * barSize);
                cout << string(curBarSize, '.');
                cout << string(barSize - curBarSize, ' ');
                cout << "] ";
                cout << (int)(progress * 100) << "% " << endl;
                updateCount++;
                cout << "File stat: " << progressCount << "/" << outOf << endl << endl;
                
            }
        }
    }
}

double sorter::getAspectFromCSV(string csv){
     //the values are stored like "path,value"
    double workingAspect = 0.0;
    csv = csv.substr(csv.find(',')+1);
    stringstream ss(csv);
    ss >> workingAspect;
    return workingAspect;
}

double sorter::getImageAspect(string imagePath){
    //quickly check the database to see if we already know the aspect
    //there can DEFINETLY be some optimizations to this...
    for(int i = 0; i < imageDatabase.size(); i++){
        string currentImagePath = imageDatabase[i];
        if(currentImagePath.find(imagePath,0) != -1){
            double savedAspect = getAspectFromCSV(currentImagePath);
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
    ss << "Current maxAR: " << getMaxAspectRatio() << ":1" << endl;
    ss << "Total Image Paths: " << getTotalImagePaths() << endl;
    ss << "Sys links creates: " << getTotalCreated() << endl;
    ss << "Settings to CSV: " << toCSV() << endl;
    ss << endl;
    s = ss.str();
    ss.clear();
    return s;
}

string sorter::toCSV(){
    stringstream ss;
    ss << getSearchPath();

    ss << ",";
    ss << getMinAspectRatio();

    ss << ",";
    ss << getMaxAspectRatio();

    ss << ",";
    ss << getOutputPath();

    ss << "\n";

    return ss.str();
}

void sorter::doWork(){
    findImages();
    aspectSort();
}