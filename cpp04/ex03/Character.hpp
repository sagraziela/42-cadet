#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <string>
# include "./AMateria.hpp"
# include "ICharacter.hpp"

class Character : public ICharacter
{
    private:
        AMateria	*_inventory[4];
	    std::string	_name;

    public:
        Character();
        Character(std::string const &name);
        Character(Character const &src);
        Character &operator=(Character const &src);
        virtual	~Character();

        std::string const & getName() const;
        void equip(AMateria* m) = 0;
        void unequip(int idx) = 0;
        void use(int idx, ICharacter& target);

};

#endif
