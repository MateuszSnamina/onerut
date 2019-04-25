#ifndef ONERUT_AKA_HPP
#define ONERUT_AKA_HPP

#include<string>
#include<map>
#include<memory>

std::multimap<std::shared_ptr<void>, std::string>
create_object_akas_map();

std::string
object_to_aka_string(
        std::shared_ptr<void> object,
        std::multimap<std::shared_ptr<void>, std::string> object_akas);

class Aka {
public:
    Aka(std::shared_ptr<void> object,
            std::multimap<std::shared_ptr<void>, std::string> object_akas);
private:
    std::shared_ptr<void> _object;
    std::multimap<std::shared_ptr<void>, std::string> _object_akas;
    friend std::ostream& operator<<(std::ostream&, const Aka&);
};

#endif

