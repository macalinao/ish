#include <string>

class Command {
  public:
    Command(char* str);
    void execute();
  private:
    std::string str;
};
