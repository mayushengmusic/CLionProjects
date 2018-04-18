# CaffeHTTP

this is my study project in UESTC(a university located in China)

thanks for the [Simple-Web-Server](https://github.com/eidheim/Simple-Web-Server/blob/master/http_examples.cpp) Project.

this project using caffe trained CNN to predict the image,

if you want use this code ,I think you need to modify this code to fit your project.

* first 
    modify those string
```
const string model="/home/jaken/CaffeModel/google_net/deploy.prototxt";//modify this string for your model define file location
    const string trained = "/home/jaken/CaffeModel/google_net/google_net.caffemodel";//modify this string for your trained file
```
those string located in *main* function.
if your project have the means file, it may be not easy to change.
those time most CNN code using the means provide by google net.

change this for your model prototxt and trained file.

* second
    modify the basepath string
    
```
    std::string basepath("/home/jaken/Temp/test/0/");//the path where your images with put in
```

this the base location to tell the program which path is the right path to find the image files.

* third

```
HttpServer server(8080, 1);//8080 represent the server port,1 represent the thread number
```

this code is the place to change the listening port and thread number.

* fourth

```
//you maybe need to modify this code
            //
            jsontable["sex"]=ans[0];
            jsontable["sexy"]=ans[1];
            jsontable["normal"]=ans[2];
            //
```
this place located in *special.hpp* file line 34 which in the floder named *include*.

because our project just need three generic classifier. so the jsontable just have three generic. I think your project is different from us. so you may change it to fit your project. just change the code in my way.

* fifth

you should install caffe developed by Jia in your ubuntu system.
modify the *CMakeList.txt caffe include directory and lib directory in the follow line. 

```
include_directories("/home/jaken/caffe/include")
link_directories("/home/jaken/caffe/build/lib")
```

* sixth
those project support to use GPU to accelerate your predict speed.
if you have the nvidia GPU which support CUDA. and installed the CUDA driver.you can turn ON it by this way.

delete the # in the front of the line:

```
#include_directories("/usr/local/cuda/include")
```

modify the directory to tell the Cmake which place to find cude include head file.

then add the # to the line:

```
#ADD_DEFINITIONS(-DCPU_ONLY)
```

if your computer have multi GPU, you can also modify the follow line to tell the program which GPU the code can use

```
 Caffe::SetDevice(0);
```

this line located in the file named *uestc_classifier.cpp* in src directory.
you can check your GPU id by command:

```
nvidia-smi
```

if you just have only one GPU.you not need to modify it.

* final

this project using Boost and Opencv,so you should install Boost and Opencv,if you use Ubuntu. you can install by this command

```
sudo apt-get install --no-install-recommends libboost-all-dev

sudo apt-get install libopencv-dev
```

I think if you install caffe correctly those lib may be already  installed in your system.


* compile

```
cd *Floder*

mkdir build

cd build

cmake ..

make

```

OK , you may find a bin file in the build directory.

* run

run it by the next command:

```
./CaffeProject 1>log.txt 2>&1 &
```

ok now you can try the request http url in your web brower:

http://127.0.0.1:8080/caffe/image-file-name-located-in-the-base-path.json

you may get a json like this:

```
{"normal":9.1058300313307e-06,"sex":0.990410685539246,"sexy":0.00958018749952316}
```

Thank you.

My gmail: mayushengmusic@icloud.com


    
