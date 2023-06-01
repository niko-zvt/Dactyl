#include <iostream>
#include "Dactyl.Utils.h"
#include "Dactyl.ModelAliases.h"
#include "Dactyl.IModel.h"
#include "Dactyl.ModelLocator.h"
#include "Dactyl.FEModel.h"

int main(int argc, char *argv[])
{
    // Parse args
    if(argc > 1)
    {
        Dactyl::Application::Utils::parse_args(argc, const_cast<const char**>(argv));
    }

    // Create a unique FE model and provide it to the model locator
    Dactyl::Model::FEModelPtr feModel = std::make_unique<Dactyl::Model::FEModel>();
    Dactyl::Model::ModelLocator::provideModel(feModel.get());

    // Test model
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
    model.print();

    return 0;
}
