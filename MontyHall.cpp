#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Door
{
private:
    string content;
public:
    Door(string content)
    {
        this->content = content;
    }
        
    string getContent()
    {
        return this->content;
    }
};

// Simulating a round
bool playBySwitching(Door** Room)
{
    // Player's first choice
    int playerChoice = rand() % 3;  
    
    // Remaining choices for Monty 

    /*
    Two conditions 
        1. It should not be the player's choice and 
        2. It should have a Goat
    */

    vector<int> remainingDoors;

    for (int i = 0; i < 3; ++i)
        if (i != playerChoice && Room[i]->getContent() != "Car")
            remainingDoors.push_back(i);
          
    // Door to be opened by Monty  
    int openedByMonty = remainingDoors[rand() % remainingDoors.size()];
    
    // Door chosen by player and door opened by Monty is uniquely characterized by their sum
    int sum = playerChoice + openedByMonty; 
    int leftChoice; // This represents which door to switch to
    
    switch(sum)
    {
        case 1: 
            leftChoice = 2;
            break;
        case 2:
            leftChoice = 1;
            break;
        case 3:
            leftChoice = 0;
            break;
    }
    
    if (Room[leftChoice]->getContent() == "Car")
        return true;
    
    return false;
}

int main() {
    Door* Room[3];  // Represents the 3 doors
    
    Room[0] = new Door("Goat");
    Room[1] = new Door("Goat");
    Room[2] = new Door("Car");
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
 
    // Shuffle the doors
    shuffle(Room, Room + 3, default_random_engine(seed));   
    
    int wins = 0, losses = 0, rounds = 100000;
    
    for (int round = 1; round <= rounds; ++round)
    {
        // Play the game
        bool result = playBySwitching(Room); 

        if (result)
            wins++;
        else losses++;
    }
    
    cout << wins << " wins out of " << rounds << endl;
    cout << losses << " losses out of " << rounds << endl;
	return 0;
}
