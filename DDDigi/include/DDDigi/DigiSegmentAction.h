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
#ifndef DDDIGI_DIGISEGMENTACTION_H
#define DDDIGI_DIGISEGMENTACTION_H

// Framework include files
#include <DDDigi/DigiData.h>
#include <DDDigi/DigiEventAction.h>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  /// Namespace for the Digitization part of the AIDA detector description toolkit
  namespace digi {

    /// Forward declarations
    class DigiSegmentAction;
    class DigiSegmentContext;
    class DigiSegmentationSplitter;

    /// Default base class for all Digitizer actions and derivates thereof.
    /**
     *  This is a utility class supporting properties, output and access to
     *  event and run objects through the context.
     *
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_SIMULATION
     */
    class DigiSegmentAction : public DigiEventAction   {
    private:
      friend class DigiSegmentationSplitter;

      /// Implementation declaration
#if defined(G__ROOT) || defined(__CLING__) || defined(__ROOTCLING__)
      typedef long internals_t;
#else
      class internals_t;
#endif
      /// Reference to the implementation
      std::unique_ptr<internals_t> internals;

      /// Define standard assignments and constructors
      DDDIGI_DEFINE_ACTION_CONSTRUCTORS(DigiSegmentAction);

    public:
      /// Standard constructor
      DigiSegmentAction(const DigiKernel& kernel, const std::string& name);
      /// Default destructor
      virtual ~DigiSegmentAction();
      /// Main functional callback
      virtual void execute(DigiContext& context)  const  final;
      /// Main functional callback. Default implementnation is noop.
      virtual DepositVector handleSegment(DigiContext&              context,
					  const DigiSegmentContext& segment,
					  const DepositMapping&     deposits)  const;
    };
  }    // End namespace digi
}      // End namespace dd4hep
#endif // DDDIGI_DIGISEGMENTACTION_H