#include <ray/api.h>
#include <iostream>
#include <exception>
#include "remote_functions.hpp"



int main() {
    try {
        std::cout << "Initializing Ray..." << std::endl;
        ray::Init();
        std::cout << "Ray initialized successfully." << std::endl;

        std::cout << "Creating task and calling Remote()..." << std::endl;
        try {

      // Call remote function
    auto future = ray::Task(Mul).Remote(MyStruct{3, 3});
    int result = *(ray::Get(future));
    std::cout << " 3 * 3 = " << result << std::endl;

    // Create remote Counter object
    //auto counter_ref = ray::Task(Counter::FactoryCreate).Remote(0);
    //auto counter = ray::Get(counter_ref);

    // Call method on remote object
    //auto add_future = ray::Task(&Counter::Add).Remote(*counter, 5);
    //int count = *(ray::Get(add_future));
    //std::cout << "Counter value after adding 5: " << count << std::endl;

    std::cout << "Remote() called successfully." << std::endl;


            std::cout << "Remote() called successfully." << std::endl;
        } catch (const ray::internal::RayException& e) {
            std::cerr << "Ray exception occurred: " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Runtime error occurred: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Standard exception occurred: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception occurred" << std::endl;
        }

        std::cout << "Shutting down Ray..." << std::endl;
        ray::Shutdown();
        std::cout << "Ray shut down successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}