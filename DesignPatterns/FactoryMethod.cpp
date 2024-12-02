#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Producer {
public:
	virtual ~Producer() {}
	virtual std::string MakeFilm() const = 0;
};

class SitaraEnts : public Producer{
public:
	std::string MakeFilm() const override{
		return "{Sitara Entertainments}";
	}
};

class NTRArts : public Producer{
public:
	std::string MakeFilm() const override{
		return "{NTR Arts}";
	}
};

class Director{
public:
	virtual ~Director(){};
	virtual std::shared_ptr<Producer> FactoryMethod() const = 0;

	std::string MakeFilm() const {
		std::shared_ptr<Producer> production = this->FactoryMethod();

		std::string result = "Director: The same director's code has just worked with " +
				      production->MakeFilm();
		return result;
	}
};

class Shiva : public Director{
public:
	std::shared_ptr<Producer> FactoryMethod() const override{
		return std::make_shared<NTRArts>();
	}
};

class Trivikram : public Director{
public:
	std::shared_ptr<Producer> FactoryMethod() const override{
		return std::make_shared<SitaraEnts>();
	}
};


void Netflix(const Director& director){
	std::cout << "Netflix: I'm not aware of the director's name, but it still making film \n"
		  << director.MakeFilm() << std::endl;
}

int main(){
	std::cout << "App: Launched with Trivikram\n";
	std::shared_ptr<Director> director = std::make_shared<Trivikram>();
	Netflix(*director);
	std::cout << std::endl;
	std::cout << "App: Launched with Shiva\n";
	std::shared_ptr<Director> director2 = std::make_shared<Shiva>();
	Netflix(*director2);
	std::cout << std::endl;

	return 0;
}
