#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

//forward declaration
class NewsTopic;

//Observer Interface
class ISubscriber{
public:
	virtual ~ISubscriber();
	virtual void update(const string& topic, const string& news) = 0;
};

//Concrete Observer: User
class User : public ISubscriber {
private:
	string name;
public:
	explicit User(string name):name(std::move(name)){}

	void update(const string& topic, const string& news) override{
		cout << "[User: " << name << "] received update on '" << topic << "': " << news << endl;
	}	

	string getName() const {return name;}
};

//Subject Interface
class INewsTopic{
public:
	virtual ~INewsTopic() = default;
	virtual void subscribe(shared_ptr<ISubscriber> user) = 0;
	virtual void unsubscribe(shared_ptr<ISubscriber> user) = 0;
	virtual void notifySubscribers(const string& news) = 0;
};

//Concrete subject: NewsTopic
class NewsTopic : public INewsTopic{
private:
	string topicName;
	vector<shared_ptr<ISubscriber>> subscribers;
public:
	explicit NewsTopic(string name) : topicName(std::move(name)) {}

	void subscribe(shared_ptr<ISubscriber> user) override{
		subscribers.push_back(user);
		cout << user->getName() << " subscribed to " << topicName << endl;
	}

	void unsubscribe(shared_ptr<ISubscriber> user) override{
		subscribers.erase(remove(subscribers.begin(), subscribers.end(), user),
				  subscribers.end());
		cout << user->getName() << " unsubscribed from " << topicName << endl;
	}

	void notifySubscribers(const string& news) override{
		cout << "[News Update] " << topicName << ": " << news << endl;
		for (auto& sub : subscribers){
			sub->update(topicName, news);
		}
	}

	string getTopicName() const { return topicName; }
};

// News Publisher (Manages topics)
class NewsPublisher{
private:
	unordered_map<string, shared_ptr<NewsTopic>> topics;
public:
	void createTopic(const string& topicName){
		topics[topicName] = make_shared<NewsTopic>(topicName);
		cout << "Topic '" << topicName << "' created" << endl;
	}

	shared_ptr<NewsTopic> getTopic(const string& topicName){
		return topics.count(topicName) ? topics[topicName] : nullptr;
	}

	void publishNews(const string& topicName, const string& news){
		if (topics.count(topicName)){
			topics[topicName]->notifySubscribers(news);
		} else {
			cout << "No such topic: " << topicName << endl;
		}
	}
};

//Main function
int main(){
	NewsPublisher publisher;

	//Creating Topics
	publisher.createTopic("Sports");
	publisher.createTopic("Politics");

	//Creating Users
	auto user1 = make_shared<User>("Alice");
	auto user2 = make_shared<User>("Bob");

	//Subscribing Users to Topics
	auto sports = publisher.getTopic("Sports");
	auto politics = publisher.getTopic("Politics");

	if (sports) sports->subscribe(user1);
	if (sports) sports->subscribe(user2);
	if (politics) politics->subscribe(user2);

	//Publishing news
	publisher.publishNews("Sports", "Team A won the championship");
	publisher.publishNews("Politics", "New policy announced by the governmer");

	if (sports) sports->unsubscribe(user1);

	//More news
	publisher.publishNews("Sports", "Player X scored a hat-trick");

	return 0;
}
