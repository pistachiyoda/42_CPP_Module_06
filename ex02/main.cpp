#include "Base.hpp"
#include "Identify.hpp"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q identify");
// }

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        Base *p = generate();
        identify(p);
        identify(*p);
        std::cout << "~~~~~~~~~~~" << std::endl;

        delete p;
    }
    return 0;
}
