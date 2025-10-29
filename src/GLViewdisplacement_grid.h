#pragma once

#include "GLView.h"
#include "AftrImGui_MenuBar.h"
#include "AftrImGui_WO_Editor.h"
#include "AftrImGui_displacement_grid.h"


namespace Aftr { class GLSLShaderDisplacement; }

namespace Aftr
{
   class Camera;
   class WOImGui;

/**
   \class GLViewdisplacement_grid
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewdisplacement_grid : public GLView
{
public:
   static GLViewdisplacement_grid* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewdisplacement_grid();
   virtual void updateWorld() override; ///< Called once per frame
   virtual void loadMap() override; ///< Called once at startup to build this module's scene
   virtual void createdisplacement_gridWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height ) override;
   virtual void onMouseDown( const SDL_MouseButtonEvent& e ) override;
   virtual void onMouseUp( const SDL_MouseButtonEvent& e ) override;
   virtual void onMouseMove( const SDL_MouseMotionEvent& e ) override;
   virtual void onKeyDown( const SDL_KeyboardEvent& key ) override;
   virtual void onKeyUp( const SDL_KeyboardEvent& key ) override;

protected:
   GLViewdisplacement_grid( const std::vector< std::string >& args );
   virtual void onCreate();

   WOImGui* gui = nullptr; //The GUI which contains all ImGui widgets
   AftrImGui_MenuBar menu;      //The Menu bar at the top of the GUI window
   AftrImGui_WO_Editor wo_editor;//The WO Editor to mutate a selected WO
   AftrImGui_displacement_grid orbit_gui;
   WO* moon = nullptr;
   WO* gulfstream = nullptr;
   GLSLShaderDisplacement* displacementShader = nullptr;
};

/** \} */

} //namespace Aftr
