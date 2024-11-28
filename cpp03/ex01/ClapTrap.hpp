#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
    private:
        std::string _name;
        int         _hit = 10;
        int         _energy = 10;
        int         _attackDamage = 0;

    public:
        ClapTrap(std::string name);
        ClapTrap(void);
        //copy
        //operator
        ~ClapTrap(void);
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif