#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with the pattern. Just remember that the Subject is also called the Publisher
 * and the Observer is often called the Subscriber and vice versa. Also the verbs
 * "observer", "listen" or "track" usually mean the same thing
 */
class IObserver{
public:
	virtual ~IObserver(){}
	virtual void Update(const std::string &message_from_subject) = 0;
};

class ISubject{
public:
	virtual ~ISubject(){};
	virtual void Attach(IObserver *observer) = 0;
	virtual void Dettach(IObserver *observer) = 0;
	virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes
 */
class Subject : public ISubject {
public:
	virtual ~Subject(){
		std::cout << "Good bye, i was the subject" << std::endl;
	}

	void Attach(IObserver *observer) override{
		list_observer_.push_back(observer);
	}

	void Dettach(IObserver *observer) override{
		list_observer_.remove(observer);
	}

	void Notify() override {
		std::list<IObserver *>::iterator iterator = list_observer_.begin();
		HowManyObserver();
		while (iterator != list_observer_.end()){
			(*iterator)->Update(message_);
			++iterator;
		}
	}

	void CreateMessage(std::string message = "Empty"){
		this->message_ = message;
		Notify();
	}

	void HowManyObserver(){
		std::cout << "There are " << list_observer_.size() << " observers in the list" << std::endl;	
	}

	void SomeBusinessLogic(){
		this->message_ = "change message message";
		Notify();
		std::cout << "I'm about to do some thing important" << std::endl;
	}

private:
	std::list<IObserver *> list_observer_;
	std::string message_;
};

class Observer : public IObserver{
public:
	Observer(Subject &subject) : subject_(subject) {
		this->subject_.Attach(this);
		std::cout << "Hi, I'm the observer \"" << ++Observer::static_number_ << "\"." << std::endl;
		this->number_ = Observer::static_number_;
	}

	virtual ~Observer(){
		std::cout << "Good bye" << endl;
	}

	void Update(const std::string &message_from_subject) override {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}

	void RemoveMeFromTheList(){
		subject_.Dettach(this);
		std::cout << "Observer \"" << number_ << "\" removed from the list" << std::endl;
	}

	void PrintInfo(){
		std::cout << "Observer \"" << this->number_ << "\": a new message is available -->" << std::endl;
	}

private:
	std::string message_from_subject_;
	Subject &subject_;
	static int static_number_;
	int number_;
};

int Observer::static_number_ = 0;

void ClientCode(){
	Subject *subject = new Subject;
	Observer *observer1 = new Observer(*subject);
	Observer *observer2 = new Observer(*subject);
	Observer *observer3 = new Observer(*subject);

	Observer *observer4;
	Observer *observer5;

	subject->CreateMessage("Hello world.!");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("The weather is hot today");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("My new car is great");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer2;
	delete observer3;
	delete observer4;
	delete observer1;

	delete subject;
}
int main(){
	ClientCode();
	return 0;
}
