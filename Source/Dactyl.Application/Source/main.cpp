#include <iostream>

#include "Dactyl.IContext.h"
#include "Dactyl.GlobalContext.h"
#include "Dactyl.ContextLocator.h"

#include "Dactyl.Utils.h"
#include "Dactyl.FileParser.h"

#include "Dactyl.IModel.h"
#include "Dactyl.ModelLocator.h"
#include "Dactyl.FEModel.h"

#include "Dactyl.KData.h"

using Dactyl::Application::Utils;

int main(int argc, char *argv[])
{
    // 0. Create global context. Create a unique pointer and provide it to the context locator
    auto gContex = std::make_unique<Dactyl::Application::GlobalContext>();
    Dactyl::Application::ContextLocator::provideContext(gContex.get());

    // 1. Parse args and update context
    if(argc > 1)
    {
        Utils::parse_args(argc, const_cast<const char**>(argv));
    }

    // 2. Check is runable model
    if (gContex->isRunable() == false)
    {
        return 0;
    }

    // 3. Try parse K-file from context
    Dactyl::Model::KData kData;
    auto parsingResult = Dactyl::Application::FileParser::tryParseKFile(&kData);
    if(parsingResult == false)
    {
        Utils::print_string("\tError! K-file was not found at '" + gContex->getPathToKFile() + "' path or was corrupted.");
        Utils::print_string("\tTry loading the corrected K-file or build the FE model manually.");
        return 1;
    }

    // 4. Create FE model. Create a unique pointer and provide it to the model locator
    auto feModel = std::make_unique<Dactyl::Model::FEModel>();
    Dactyl::Model::ModelLocator::provideModel(feModel.get());
    // USE MESH AS: Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();

    // 5.1 Build by K-file
    auto result = feModel->loadMesh(kData);
    
    // 5.2 Set constraints
    // 5.3 Set loads
    // 5.4 Calculate

    auto n = feModel->getNodesCount();
    Utils::print_string(Utils::to_string(result));
    feModel->print();

    // 6. Get results

    // 7. End
    return 0;
}
