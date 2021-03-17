## Running Exercises
 Firstly, make sure you have `g++` compiler installed. The instalation can be done in Ubuntu, using the following command:
 ```sh
 sudo apt-get install g++ gcc
 ```
 To run each exercise just open the desired folder and run the build command. Both steps can be done using the commands below:
 ```sh
 cd exercicio#
 g++ -o main main.cpp converter/converter.hpp converter/converter.cpp search/search.hpp search/search.cpp && ./main
 ```
Each library headers - the `.hpp` files- and implementations must be added to the `g++` command. Otherwise the compilation will fail.