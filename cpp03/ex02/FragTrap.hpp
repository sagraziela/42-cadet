#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include <iostream>
# include <string>
# include "./ClapTrap.hpp"

class FragTrap : public ClapTrap
{
    public:
        FragTrap(std::string name);
        FragTrap(void);
        FragTrap(FragTrap const &src);
		FragTrap &operator=(FragTrap const &src);
        ~FragTrap(void);

        void highFivesGuys(void);
};

#endif
