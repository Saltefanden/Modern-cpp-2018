#include<iostream>
#include<cstdlib>
#include<ctime>


int create_random_number(int max){
    std::srand(std::time(0) + std::time(0)%3 + std::time(0)%1 + std::time(0)%5 + std::time(0)%11 + + std::time(0)%7 + std::time(0)%23);
    std::cout << std::time(0) << std::endl;
    return std::rand()%max;
}


int main(){

    int num_2_guess{create_random_number(99)};

    std::cout << "Welcome to the number guessing game!" << std::endl;
    std::cerr << num_2_guess << std::endl;
    std::cout << "Try and guess my number you nerd: ";
    int num_guessed;
    
    while(true){
        
        std::cin >> num_guessed;
        
        if(num_guessed < num_2_guess){
            std::cout << "Your guess was too small" << std::endl;
        }
        else if (num_guessed > num_2_guess){
            std::cout << "Your guess was too big" << std::endl;
        }
        else{
            break;
        }

        std::cout << "Try again: ";
    }

    std::cout << "Your guess was: " << num_guessed << " and the correct number was: " << num_2_guess << std::endl;
    std::cout << "Congratulations, you won!";
    return 0;
}