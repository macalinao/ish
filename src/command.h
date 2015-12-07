#include <string>

class Command {
  public:
    Command(std::string str);
    void execute();
  private:
    std::string str;
};
