#include "GLViewdisplacement_grid.h"


#include "WorldList.h"
#include "ManagerOpenGLState.h"
#include "Axes.h"
#include "PhysicsEngineODE.h"

#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"
#include "MGLIndexedGeometry.h"
#include "IndexedGeometrySphereTriStrip.h"
#include "WOAxesTubes.h"
#include "AftrTimer.h"
#include <chrono>
#include "GLSLShader.h"
#include "GLSLUniform.h"
#include "ManagerShader.h"
#include "ManagerTex.h"
#include "GLSLShaderDisplacement.h"
using namespace Aftr;

GLViewdisplacement_grid* GLViewdisplacement_grid::New( const std::vector< std::string >& args )
{
   GLViewdisplacement_grid* glv = new GLViewdisplacement_grid( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}

GLViewdisplacement_grid::GLViewdisplacement_grid( const std::vector< std::string >& args ) : GLView( args )
{
}

void GLViewdisplacement_grid::onCreate()
{
   if( this->pe != NULL )
   {
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV );
}

GLViewdisplacement_grid::~GLViewdisplacement_grid()
{
}

void GLViewdisplacement_grid::updateWorld()
{
    GLView::updateWorld();

    // Update time for animation
    if (this->displacementShader != nullptr && this->displacementShader->time != nullptr)
    {
        static float currentTime = 0.0f;
        currentTime += 0.016f;
        this->displacementShader->time->setValues(&currentTime);

        // SET DISPLACEMENT SCALE (uniform already exists!)
        static bool scaleSet = false;
        if (!scaleSet && this->displacementShader->displacementScale != nullptr)
        {
            float scaleValue = 10.0f;  // CHANGE THIS for taller waves!
            this->displacementShader->displacementScale->setValues(&scaleValue);
            scaleSet = true;
        }
    }

    if (this->gulfstream != nullptr && this->moon != nullptr)
        this->moon->setPose(
            this->orbit_gui.compute_pose(this->gulfstream->getModel()->getPose()));
}
void GLViewdisplacement_grid::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height );
}

void GLViewdisplacement_grid::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
}

void GLViewdisplacement_grid::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}

void GLViewdisplacement_grid::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}

void GLViewdisplacement_grid::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );
}

void GLViewdisplacement_grid::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
}

void Aftr::GLViewdisplacement_grid::loadMap()
{
   this->worldLst = new WorldList();
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   ManagerOpenGLState::GL_CLIPPING_PLANE( 1000.0 );
   ManagerOpenGLState::GL_NEAR_PLANE( 0.1f );
   ManagerOpenGLState::enableFrustumCulling( false );
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false );

   this->cam->setPosition(-80, 0, 30);


   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   
   std::vector< std::string > skyBoxImageNames;
   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );

   {
      float ga = 0.1f;
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }

   {
      WO* wo = WOSkyBox::New( skyBoxImageNames.at( 0 ), this->getCameraPtrPtr() );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->setLabel( "Sky Box" );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      worldLst->push_back( wo );
   }

   {
      this->gulfstream = WO::New( ManagerEnvironmentConfiguration::getSMM() + "models/Aircraft/Gulfstream3/G3.obj", Vector(1.0f, 1.0f, 1.0f ), MESH_SHADING_TYPE::mstAUTO );
      this->gulfstream->setPosition( Vector( 0, 0, 10 ) );
      this->gulfstream->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      this->gulfstream->upon_async_model_loaded( [this]()
         {
            ModelMeshSkin& skin = this->gulfstream->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
            skin.setAmbient( aftrColor4f( 0.1f, 0.1f, 0.1f, 1.0f ) );
            skin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) );
            skin.setSpecularCoefficient( 10 );
         } );
      gulfstream->setLabel( "Gulfstream GIII" );
      worldLst->push_back( this->gulfstream );
   }

   {
      this->moon = WO::New();
      MGLIndexedGeometry* mglSphere = MGLIndexedGeometry::New( this->moon );
      IndexedGeometrySphereTriStrip* geoSphere = IndexedGeometrySphereTriStrip::New( 3.0f, 12, 12, true, true );
      mglSphere->setIndexedGeometry( geoSphere );
      this->moon->setModel( mglSphere );
      this->moon->setLabel( "Moon" );
      this->moon->setPosition( { 15,15,15 } );
      this->moon->renderOrderType = RENDER_ORDER_TYPE::roTRANSPARENT;
      this->worldLst->push_back( this->moon );

      fmt::print( "To the moon...\n" );
      Tex tex = *ManagerTex::loadTexAsync( ManagerEnvironmentConfiguration::getSMM() + "/images/moonMap.jpg" );
      this->moon->getModel()->getSkin().getMultiTextureSet().at( 0 ) = tex;
      this->moon->setPosition( {15,2,10});

      WO* axes = WOAxesTubes::New( { 15.0f,15.0f,15.0f }, .2f );
      axes->setParentWorldObject( this->moon );
      axes->setPosition( this->moon->getPosition() );
      axes->lockWRTparent();
      this->moon->getChildren().push_back( axes );     
   }
   // In GLViewdisplacement_grid.cpp loadMap() function:

   {
       fmt::print("\n=== Creating Displacement Mapped Grid ===\n");

       // Create grass plane
       WO* grid = WO::New(grass, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
       grid->setPosition(Vector(0, 0, 0));
       grid->setLabel("Displacement Grid");
       grid->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
       worldLst->push_back(grid);

       /// Apply displacement shader when model loads
       grid->upon_async_model_loaded([this, grid]()
           {
               fmt::print("Applying displacement shader...\n");

               // Create custom displacement shader
               GLSLShaderDisplacement* shader = GLSLShaderDisplacement::New();
               if (shader == nullptr)
               {
                   fmt::print("ERROR: Failed to create displacement shader!\n");
                   return;
               }
               this->displacementShader = shader;

               // Load heightmap texture
               std::string heightmapPath = ManagerEnvironmentConfiguration::getSMM() + "/images/concentric_circles.jpg";
               auto heightmapOpt = ManagerTex::loadTexAsync(heightmapPath);
               if (!heightmapOpt.has_value())
               {
                   fmt::print("ERROR: Failed to load heightmap!\n");
                   return;
               }
               Tex heightmap = *heightmapOpt;

               fmt::print("Heightmap loaded successfully!\n");

               // Apply shader to all meshes
               auto& meshes = grid->getModel()->getModelDataShared()->getModelMeshes();
               fmt::print("Applying to {} meshes...\n", meshes.size());

               for (auto* mesh : meshes)
               {
                   for (auto& skin : mesh->getSkins())
                   {
                       // Set the custom shader
                       skin.setShader(shader);

                       // Add heightmap to texture unit 1
                       auto& texSet = skin.getMultiTextureSet();
                       if (texSet.size() < 2)
                           texSet.resize(2);
                       texSet.at(1) = heightmap;

                       fmt::print("  Texture applied to skin!\n");
                   }
               }
               fmt::print("Displacement shader applied!\n");
           });

       fmt::print("Grass grid created, waiting for model load...\n");
   }

   {
      this->gui = WOImGui::New( nullptr );
      gui->setLabel( "My Gui" );
      
      auto woEditFunc = [this]() { this->wo_editor.draw( this->getLastSelectionQuery(), *this->getWorldContainer(), this->getCamera_functor() ); };
      auto showDemoWindow_ImGui     = [this]() { ImGui::ShowDemoWindow(); };
      auto showDemoWindow_AftrDemo  = [this]() { WOImGui::draw_AftrImGui_Demo(this->gui); };
      auto showDemoWindow_ImGuiPlot = [this]() { ImPlot::ShowDemoWindow(); };
      auto show_moon_orbit_params   = [this]() { this->orbit_gui.draw(); };
      this->gui->subscribe_drawImGuiWidget(
         [=,this]()
         {
            menu.attach( "Edit", "Show WO Editor", woEditFunc );
            menu.attach( "Demos", "Show Default ImGui Demo", showDemoWindow_ImGui );
            menu.attach( "Demos", "Show Default ImPlot Demo", showDemoWindow_ImGuiPlot );
            menu.attach( "Demos", "Show Aftr ImGui w/ Markdown & File Dialogs", showDemoWindow_AftrDemo );
            menu.attach( "Orbit Gui", "Show Orbit", show_moon_orbit_params, true );
            menu.draw();
         } );
      this->worldLst->push_back( this->gui );
   }
   
   createdisplacement_gridWayPoints();
}

void GLViewdisplacement_grid::createdisplacement_gridWayPoints()
{
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}
