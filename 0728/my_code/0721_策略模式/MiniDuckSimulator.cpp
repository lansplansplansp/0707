#include "MiniDuckSimulator.hpp"
//#include <memory>
#include "MallardDuck.hpp"

int main(int argc,char **argv)
{
	auto_ptr<MallardDuck > mallard(new MallardDuck);
	//auto_ptr<RubberDuck > rubber(new RubberDuck);
	//auto_ptr<DecoyDuck > decoy(new DecoyDuck);
	//auto_ptr<ModelDuck> model(new ModelDuck);
	
	mallard->performFly();
	mallard->performQuack();

	//rubber->performFly();
	//rubber->performQuack();

	//decoy->performFly();
	//decoy->performQuack();

	//model->performFly();
	//model->performQuack();
	
	return 0;
}