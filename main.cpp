#include <iostream>
#include <string>
#include <map>

template <typename T>
class FootballTeamStatistics {
private:
    T wins;
    T losses;
    T draws;

public:
    FootballTeamStatistics() : wins(0), losses(0), draws(0) {}
    FootballTeamStatistics(T wins, T losses, T draws) : wins(wins), losses(losses), draws(draws) {}

    T getWins() { return wins; }
    T getLosses() { return losses; }
    T getDraws() { return draws; }
};



// Base class for a football team
class FootballTeam {
protected:
    std::string name;
    std::string coach;
    std::string stadium;
    std::map<std::string, int> players;
    FootballTeamStatistics<int> statistics;
public:
    FootballTeam(std::string name, std::string coach, std::string stadium) :
            name(name), coach(coach), stadium(stadium) {}

    virtual ~FootballTeam() {}

    std::string getName() { return name; }
    std::string getCoach() { return coach; }
    std::string getStadium() { return stadium; }
    FootballTeamStatistics<int> getStatistics() {return statistics;}

    virtual void addPlayer(std::string name, int number) { players[name] = number; }
    virtual void removePlayer(std::string name) { players.erase(name); }
    virtual std::map<std::string, int> getPlayers() { return players; }

    virtual FootballTeam* clone() = 0;

    template <typename T>
    void updateStatistics(T wins,T losses,T draws)
    {statistics = FootballTeamStatistics<T>(wins ,losses,draws);}
};

// Derived class for a professional football team
class ProfessionalFootballTeam : public FootballTeam {
public:

    ProfessionalFootballTeam(std::string name, std::string coach, std::string stadium) :
            FootballTeam(name, coach, stadium) {}


    ~ProfessionalFootballTeam() {}

    FootballTeam* clone() {
        return new ProfessionalFootballTeam(*this);
    }
};


// Derived class for an amateur football team
class  AmateurFootballTeam : public FootballTeam {
public:
    AmateurFootballTeam(std::string name, std::string coach, std::string stadium) :
            FootballTeam(name, coach, stadium) {}

    ~AmateurFootballTeam() {}

    FootballTeam* clone() {
        return new AmateurFootballTeam(*this);
    }
};

// Singleton class for generating unique IDs for football teams
class FootballTeamID {
private:
    static FootballTeamID* instance;
    int nextID;

    FootballTeamID() : nextID(0) {}
    FootballTeamID(const FootballTeamID&) = delete;
    FootballTeamID& operator=(const FootballTeamID&) = delete;

public:
    static FootballTeamID* getInstance() {
        if (!instance) {
            instance = new FootballTeamID();
        }
        return instance;
    }

    int getNextID() { return nextID++; }
};
FootballTeamID* FootballTeamID::instance = 0;

// Builder class for creating football teams
class FootballTeamBuilder {
protected:
    std::string name;
    std::string coach;
    std::string stadium;
    std::map<std::string, int> players;

public:
    FootballTeamBuilder &setName(std::string name) {
        this->name = name;
        return *this;
    }

    FootballTeamBuilder &setCoach(std::string coach) {
        this->coach = coach;
        return *this;
    }

    FootballTeamBuilder &setStadium(std::string stadium) {
        this->stadium = stadium;
        return *this;
    }
    std::string getName() {return name;}
    std::string getCoach() {return coach;}
    std::string getStadium() {return stadium;}
};
int main() {
    std::map<int, FootballTeam*> teams;
    int choice = 0;
    while (choice != 9) {
        std::cout << "Welcome to the Football Team Management System" << std::endl;
        std::cout << "1. Create a new professional football team" << std::endl;
        std::cout << "2. Create a new amateur football team" << std::endl;
        std::cout << "3. Add a player to a team" << std::endl;
        std::cout << "4. Remove a player from a team" << std::endl;
        std::cout << "5. Display all teams" << std::endl;
        std::cout << "6. Display the numbers of victories,draws and losses" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, coach, stadium;
                std::cout << "Enter team name: ";
                std::cin >> name;
                std::cout << "Enter coach name: ";
                std::cin >> coach;
                std::cout << "Enter stadium name: ";
                std::cin >> stadium;
                FootballTeamBuilder builder;
                builder.setName(name);
                builder.setCoach(coach);
                builder.setStadium(stadium);
                teams[FootballTeamID::getInstance()->getNextID()] = new ProfessionalFootballTeam(builder.getName(),builder.getCoach(),builder.getStadium());
                break;
            }
            case 2: {
                std::string name, coach, stadium;
                std::cout << "Enter team name: ";
                std::cin >> name;
                std::cout << "Enter coach name: ";
                std::cin >> coach;
                std::cout << "Enter stadium name: ";
                std::cin >> stadium;
                FootballTeamBuilder builder;
                builder.setName(name);
                builder.setCoach(coach);
                builder.setStadium(stadium);
                teams[FootballTeamID::getInstance()->getNextID()] = new AmateurFootballTeam(builder.getName(),builder.getCoach(),builder.getStadium());
                break;
            }
            case 3: {
                int teamID;
                std::string playerName;
                int playerNumber;
                std::cout << "Enter team ID: ";
                std::cin >> teamID;
                std::cout << "Enter player name: ";
                std::cin >> playerName;
                std::cout << "Enter player number: ";
                std::cin >> playerNumber;
                teams[teamID]->addPlayer(playerName, playerNumber);
                break;
            }
            case 4: {
                int teamID;
                std::string playerName;
                std::cout << "Enter team ID: ";
                std::cin >> teamID;
                std::cout << "Enter player name: ";
                std::cin >> playerName;
                teams[teamID]->removePlayer(playerName);
                break;
            }
            case 5: {
                for (auto &team : teams) {
                    std::cout << "Team ID: ";
                    std::cout << team.first << std::endl;
                    std::cout << "Name: " << team.second->getName() << std::endl;
                    std::cout << "Coach: " << team.second->getCoach() << std::endl;
                    std::cout << "Stadium: " << team.second->getStadium() << std::endl;
                    std::cout << "Players: " << std::endl;
                    for (auto &player : team.second->getPlayers()) {
                        std::cout << player.first << " - " << player.second << std::endl;
                    }
                }
                break;
            }
            case 6: {
                int teamID;
                int wins,losses;
                int draws;
                std::cout << "Enter team ID: ";
                std::cin >> teamID;
                std::cout << "Enter number of wins: ";
                std::cin >> wins;
                std::cout << "Enter number of losses: ";
                std::cin >> losses;
                std::cout << "Enter number of draws: ";
                std::cin >> draws;
                teams[teamID]->updateStatistics(wins,losses,draws);
                break;
            }

            case 9: {
                std::cout << "Exit" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }
    }
    return 0;
}
