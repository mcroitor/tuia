#ifndef _USM_TEST_FRAMEWORK_HPP_
#define _USM_TEST_FRAMEWORK_HPP_

#include <iostream>

namespace usm
{
    class Test
    {
        static size_t counterTotal;
        static size_t counterPassed;

        static void Next() {
            ++counterTotal;
        }

        static void Pass() {
            ++counterPassed;
        }

    public:

        static void Init() {
            counterTotal = 0;
            counterPassed = 0;
        }

        static size_t GetTotal() {
            return counterTotal;
        }
        
        static size_t GetPassed() {
            return counterPassed;
        }

        template <typename Predicate>
        static void Unit(Predicate& predicate) {
            Next();
            std::cout << "Testing Unit " << GetTotal() << std::endl;
            if(predicate()){
                std::cout << "test " << GetTotal() << " passes " << std::endl;
                Pass();
            }
            else {
                std::cout << "test " << GetTotal() << " fails " << std::endl;
            }
        }

        static void Result() {
            std::cout << "Test Result: " << std::endl;
            std::cout << "\tPassed: " << GetPassed() << std::endl;
            std::cout << "\tTotal tests: " << GetTotal() << std::endl;
        }
    };

    size_t Test::counterTotal = 0;
    size_t Test::counterPassed = 0;
}

#endif