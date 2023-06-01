#include <iostream>
#include "Dactyl.Utils.h"
#include "Dactyl.IModel.h"
#include "Dactyl.ModelLocator.h"
#include "Dactyl.FEModel.h"

using Dactyl::Application::Utils;

int main(int argc, char *argv[])
{
    // Parse args
    if(argc > 1)
    {
        Utils::parse_args(argc, const_cast<const char**>(argv));
    }

    // Create a unique FE model and provide it to the model locator
    std::unique_ptr<Dactyl::Model::FEModel> feModel = std::make_unique<Dactyl::Model::FEModel>();
    Dactyl::Model::ModelLocator::provideModel(feModel.get());

    // Test model
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
    auto result = model.loadModel();
    auto n = model.getNodesCount();

    Utils::print_string(Utils::to_string(result));
    
    model.print();

    return 0;
}
