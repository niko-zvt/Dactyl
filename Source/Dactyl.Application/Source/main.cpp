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

    // 3. Create FE model. Create a unique pointer and provide it to the model locator
    auto feModel = std::make_unique<Dactyl::Model::FEModel>();
    Dactyl::Model::ModelLocator::provideModel(feModel.get());
    // USE MESH AS: Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();

    // 4. Try parse K-file from context
    auto kData = std::make_unique<Dactyl::Model::KData>();
    auto parsingResult = Dactyl::Application::FileParser::tryParseKFile(*kData);
    if(parsingResult == false)
    {
        Utils::print_string("\tError! K-file was not found at '" + gContex->getPathToKFile() + "' path or was corrupted.");
        Utils::print_string("\tTry loading the corrected K-file or build the FE model manually.");
        return 1;
    }

    // 5. Build by K-file and clear temp data
    auto openResult = feModel->LoadMesh(*kData);
    kData->~KData();
    
    // 6. Set constraints
    std::any any;
    auto tolerance = 0.001;
    auto UX = feModel->SetConstraintsByCoords(0.0, any, Dactyl::Model::ConstraintType::FixUX, tolerance);
    auto UY = feModel->SetConstraintsByCoords(any, 0.0, Dactyl::Model::ConstraintType::FixUY, tolerance);

    // 7. Set loads
    auto q = 1000;  // kN/m
    auto h = 0.5;   // m
    auto w = 0.3;   // m

    auto forceResult1 = feModel->SetNodalForceByCoords(w/2, any, q, 0, tolerance);
    auto forceResult2 = feModel->SetNodalForceByCoords(w/2, 0.0, q/2, 0, tolerance);
    auto forceResult3 = feModel->SetNodalForceByCoords(w/2, h, q/2, 0, tolerance);

    // 8. Calculate and postprocessing
    auto calcResult = feModel->Calculate();

    // 9. Get results
    feModel->Print();

    // 10. End
    return 0;
}

void Utils::ConfigurateTest1()
{
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
    
    // 1. Set constraints
    std::any any;
    auto tolerance = 0.001;
    auto UXY_0 = model.SetConstraintsByCoords(any, 0.0, Dactyl::Model::ConstraintType::FixUXY, tolerance);

    // 2. Set loads
    auto forceResult = model.SetNodalForceByCoords(any, 3.0, 0.0, 5.0, tolerance);
}

void Utils::ConfigurateTest2()
{
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();

    // 1. Set constraints
    std::any any;
    auto tolerance = 0.001;
    auto UX = model.SetConstraintsByCoords(-1.2, any, Dactyl::Model::ConstraintType::FixUX, tolerance);
    auto UY = model.SetConstraintsByCoords(any, 0.0, Dactyl::Model::ConstraintType::FixUY, tolerance);

    // 2. Set loads
    auto forceResult = model.SetNodalForceByCoords(1.5, 4.0, 1.0, -3.0, tolerance);
}

void Utils::ConfigurateTest3()
{
    Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();

    // 1. Set constraints
    std::any any;
    auto tolerance = 0.001;
    auto UX = model.SetConstraintsByCoords(-1.2, any, Dactyl::Model::ConstraintType::FixUX, tolerance);
    auto UY = model.SetConstraintsByCoords(any, 0.0, Dactyl::Model::ConstraintType::FixUY, tolerance);

    // 2. Set loads
    auto forceResult1 = model.SetNodalForceByCoords(1.5, 4.0, 0.5, 0, tolerance);
    auto forceResult2 = model.SetNodalForceByCoords(1.5, 1.5, 1.0, 0, tolerance);
    auto forceResult3 = model.SetNodalForceByCoords(1.5, 0.0, 0.5, 0, tolerance);
}
