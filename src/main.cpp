#include "kolejka.h"
#include <iostream>
#include <sstream>

int main() {
    PriorityQueue<std::string> queue_A, queue_B, queue_C;
    std::string sentence, word;
    std::cout<<"Proszę wpisać wiadomość od Jana do Anny:"<<std::endl;

    std::getline(std::cin, sentence); // Reading the entire input line as a message
    std::istringstream word_amount(sentence); // Splitting the message into packets (one packet is one word)

    for (int i = 0; word_amount >> word; ++i) // Loop storing the message entered by John into a variable
        queue_A.PushSort(i, word); 

    std::cout << std::endl;
    std::cout<<"Wiadmość zapisana na komputerze Jana:"<<std::endl;
    queue_A.Display();
    std::cout << std::endl;

    std::cout<<"Wiadmość przesyłana na komputer Anny:"<<std::endl;
    queue_B = queue_A.RandomPop(); // Randomizing the message, creating a new queue with randomly arranged words as the "sent" message
    queue_B.Display();
    std::cout << std::endl;

    std::cout<<"Wiadmość odebrana oraz posortowana przez komputer Anny:"<<std::endl;
    queue_C = queue_B.Pop(); // Receiving the message by Anna's computer and sorting it to obtain the original message transmission
    queue_C.Display();
    return 0;
}