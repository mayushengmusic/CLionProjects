#include "network.hpp"

int main(int argc,char *argv[]) {
    google::InitGoogleLogging(argv[0]);
    std::shared_ptr<fliter> test(new fliter("/home/jaken/machine.list"));
    test->init();
    std::shared_ptr<write_redis> redis(new write_redis());


    io_context context;
    server server_(context,redis,test);
    std::thread t1([&context](){
        context.run();
    });
    std::thread t2([&context](){
        context.run();
    });

    context.run();

    return 0;
}