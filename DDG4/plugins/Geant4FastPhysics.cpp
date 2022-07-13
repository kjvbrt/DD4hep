//==========================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================
#ifndef DDG4_GEANT4FASTPHYSICS_H
#define DDG4_GEANT4FASTPHYSICS_H

// Framework include files
#include <DDG4/Geant4Action.h>

// Geant4 include files
#include <G4FastSimulationPhysics.hh>

// C/C++ include files
#include <vector>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep  {

  /// Namespace for the Geant4 based simulation part of the AIDA detector description toolkit
  namespace sim  {
    
    /// Wrapper for G4FastSimulationPhysics with properties
    /**
     *  Wrapper for G4FastSimulationPhysics with properties.
     *  The properties supposedly are used to fully configure the object
     *  in 'ConstructProcess'.
     *
     *  \author  M.Frank
     *
     *  \version 1.0
     *  \ingroup DD4HEP_SIMULATION
     */
    class Geant4FastPhysics : public Geant4Action, public G4FastSimulationPhysics    {
    protected:
      /// Define standard assignments and constructors
      DDG4_DEFINE_ACTION_CONSTRUCTORS(Geant4FastPhysics);

      /// Vector of particle names for which fast simulation is enabled
      std::vector<std::string> m_enabledParticles;
      /// Property to set verbosity flag on G4FastSimulationPhysics
      bool m_verbose  { false };

    public:
      /// Standard constructor
      Geant4FastPhysics(Geant4Context* context, const std::string& nam);

      /// Default destructor
      virtual ~Geant4FastPhysics() = default;

      /// This method will be invoked in the Construct() method.
      virtual void ConstructProcess()  override;
    };
  }     /* End namespace sim   */
}       /* End namespace dd4hep */
#endif // DDG4_GEANT4FASTPHYSICS_H

//==========================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================

/// Framework include files
// #include <DDG4/Geant4FastPhysics.h>

using namespace dd4hep;
using namespace dd4hep::sim;

/// Standard constructor
Geant4FastPhysics::Geant4FastPhysics(Geant4Context* ctxt, const std::string& nam)
: Geant4Action(ctxt, nam), G4FastSimulationPhysics()
{
  declareProperty("EnabledParticles", m_enabledParticles);
  declareProperty("BeVerbose",        m_verbose);
}

/// This method will be invoked in the Construct() method.
void Geant4FastPhysics::ConstructProcess()    {
  if ( this->m_verbose ) this->BeVerbose();
  for( const auto& part_name : m_enabledParticles )    {
    this->info("Enable fast simulation for particle type: %s", part_name.c_str());
    this->ActivateFastSimulation(part_name);
  }
  // -- Create a fast simulation physics constructor, used to augment
  // -- the above physics list to allow for fast simulation
  this->G4FastSimulationPhysics::ConstructProcess();
  this->info("Constructed and initialized Geant4 Fast Physics.");
}

#include "DDG4/Factories.h"
DECLARE_GEANT4ACTION(Geant4FastPhysics)
