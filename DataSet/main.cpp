
#include "stick.hpp"
#include "splitnumber.hpp"

void handle1(){
    std::string Path("/home/jaken/WorkSpace/single");
    std::vector<std::string> IMGPath;
    IMGPath.reserve(1000);
    ReadFloader(Path,IMGPath);

    std::vector<cv::Mat> IMG;
    IMG.reserve(IMGPath.size());

    for(auto & path:IMGPath)
        IMG.emplace_back(cv::imread(path.c_str(),CV_LOAD_IMAGE_GRAYSCALE));

    for(auto & image: IMG)
        stickIMG(image);


    for(auto &x: IMGPath) {

        std::regex jpg(".+/(.+\\.jpg:?)$");
        std::smatch m;
        std::regex_match(x,m,jpg);
        x=m[1];
    }

    for(auto i=0;i<IMG.size();i++)
    {
        std::string path("/home/jaken/WorkSpace/single-split/");
        path+=IMGPath[i];
        cv::imwrite(path,IMG[i]);
    }

};


void BlackToWhite(cv::Mat & image)
{
    image.convertTo(image,CV_8UC1);
    int nl= image.rows;
    int nc= image.cols;
    for(int j=0;j<nl;j++){
        uchar * data = image.ptr<uchar>(j);
        for(int i=0;i<nc;i++)
        {


            data[i]= 255-data[i];
        }


    }
}


void ReadLabel(std::vector<std::pair<int,std::string>> & namesandlabel)
{
    std::ifstream ss("/home/jaken/WorkSpace/MINST/train_mnist_label.txt");
    while(ss.good()) {
        std::string name;
        int number=0;
        ss>>name>>number;
        std::cout<<name<<" "<<number<<std::endl;
        namesandlabel.emplace_back(std::make_pair(number,name));
    }
}


int main() {

    cv::Mat image=cv::imread("/home/jaken/DATA/TEST/0/0.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    std::cout<<image<<std::endl;



   /* cv::Mat image=cv::imread("/home/jaken/test.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    std::vector<cv::Mat> collimage;
    splitImage(image,collimage);
    for(auto & x: collimage)
    {
        BlackToWhite(x);
        stickIMG(x);
    }

    for(int i=0;i<collimage.size();i++)
    {
        std::string path("/home/jaken/DATA/");
        path+=std::to_string(i);
        path+=std::string(".jpg");
        cv::imwrite(path,collimage[i]);
    }*/



    return 0;
}