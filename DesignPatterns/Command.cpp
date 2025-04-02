#include<iostream>

/**
 * The Command interface declares a method for executing
 * a command.
 */
class Command{
public:
	virtual ~Command(){}
	virtual void Execute() const = 0;
};

/**
 * Some commands can implement simple operations on their own
 */
class SimpleCommand : public Command{
private:
	std::string pay_load_;
public:
	explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load){}
	void Execute() const override {
		std::cout << "SimpleCommand: See, I can do simple things like printing("
			  << this->pay_load_ << std::endl;
	}
};

/**
 * The Receiver classes contain some important business logic. they know how to
 * perform all kinds of operations, associated with carrying out a request. In
 * fact, any class may server as a Receiver
 */
class Receiver{
public:
	void DoSomething(const std::string &a){
		std::cout << "Receiver: working on (" << a << ".)" << endl;
	}

	void DoSomethingelse(const std::string &b){
		std::cout << "Receiver: Also working on (" << b << ".)" << endl;
	}
};

class ComplexCommand : public Command{
private:
	Receiver *receiver_;
	std::string a_;
	std::string b_;
public:
	ComplexCommand(Receiver *receiver, std::string a, std::string b) :
		receiver_
};



int main(){
	Invoker *invoker = new Invoker;
	invoker->SetOnStart(new SimpleCommand("Say Hi!"));
	Receiver *receiver = new Receiver;
	invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
	invoker->DoSomethingImportant();

	delete invoker;
	delete receiver;

	return 0;
}
