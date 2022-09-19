#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

typedef function<void()> FlyBehavior;
typedef function<void()> QuackBehavior;
typedef function<void()> DanceBehavior;

FlyBehavior flyWithWings = [flightsCount = 0]() mutable {
	cout << "I'm flying with wings!!" << endl;
	flightsCount++;
	cout << "This is flight number " << flightsCount << endl;
};

FlyBehavior flyNoWay = []() {};

QuackBehavior quackBehavior = []() {
	cout << "Quack Quack!!!" << endl;
};

QuackBehavior squeakBehavior = []() {
	cout << "Squeek!!!" << endl;
};

QuackBehavior muteQuackBehavior = []() {};

DanceBehavior danceWaltz = []() {
	cout << "I'm dancing waltz." << endl;
};

DanceBehavior danceMinuet = []() {
	cout << "I'm dancing minuet." << endl;
};

DanceBehavior danceNoWay = []() {};

class Duck
{
public:
	Duck(const FlyBehavior& flyBehavior,
		const QuackBehavior& quackBehavior,
		const DanceBehavior& danceBehavior)
		: m_quackBehavior(quackBehavior)
	{
		assert(m_quackBehavior);
		SetFlyBehavior(flyBehavior);
		SetDanceBehavior(danceBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	virtual void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const FlyBehavior& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(const DanceBehavior& danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck(){};

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(flyWithWings, quackBehavior, danceWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(flyWithWings, quackBehavior, danceMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(flyNoWay, muteQuackBehavior, danceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(flyNoWay, squeakBehavior, danceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(flyNoWay, quackBehavior, danceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
};

void DrawDuck(const Duck& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(flyWithWings);
	PlayWithDuck(modelDuck);
}
