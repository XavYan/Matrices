#include "../include/matrix.hpp"
#include <fstream>

int main (void) {

    matrix<int> A,B;
    A.read(std::cin);
    B.read(std::cin);

   std::cout << A << "\n\t+\n\n" << B << "\n\t=\n\n" << A + B << '\n';
   std::cout << "-------------------------------------------------------\n";
   std::cout << A << "\n\t-\n\n" << B << "\n\t=\n\n" << A - B << '\n';
   std::cout << "-------------------------------------------------------\n";
   std::cout << A << "\n\tx\n\n" << B << "\n\t=\n\n" << A * B << '\n';
   std::cout << "-------------------------------------------------------\n";
   std::cout << "Producto escalar de " << "\n\n3\n\n\tx\n\n" << A << "\n\t=\n\n";
   std::cout << A.scal_prod(3) << '\n';

   std::cout << "A = B:\n" << (A=B) << '\n';

   std::cout << "Fin del programa\n";

    return 0;
}
