#include <iostream>
#include "Dactyl.Utils.h"
#include "Dactyl.FileParser.h"
#include "Dactyl.IModel.h"
#include "Dactyl.ModelLocator.h"
#include "Dactyl.FEModel.h"
#include "Dactyl.KResult.h"

using Dactyl::Application::Utils;

int main(int argc, char *argv[])
{
    // Parse args
    if(argc > 1)
    {
        Utils::parse_args(argc, const_cast<const char**>(argv));
    }

    // TODO: Fix paths 
    // TEMP File paths
    #ifdef __linux__ 
        // Linux path
    #elif _WIN32
        const auto pathToKFile = "C:\\Users\\Digimat\\Repos\\Dactyl\\Source\\Dactyl.Application\\Resources\\Meshes\\task_mesh_homo2.k";
    #elif __APPLE__
        const auto pathToKFile = "/Users/niko_zvt/Documents/Repos/Dactyl/Source/Dactyl.Application/Resources/Meshes/task_mesh_homo2.k";
    #else
        // Do nothing
    #endif

    // Parse K-file
    Dactyl::Application::KResult kResult;
    Dactyl::Application::FileParser::parseFile(pathToKFile, &kResult);

    // Create a unique FE model and provide it to the model locator
    auto feModel = std::make_unique<Dactyl::Model::FEModel>();
    Dactyl::Model::ModelLocator::provideModel(feModel.get());

    // Use model
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
    auto result = model.loadModel();
    auto n = model.getNodesCount();

    Utils::print_string(Utils::to_string(result));
    
    model.print();

    return 0;
}
