/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
   :  mTerrainGroup(0),
      mTerrainGlobals(0),
      mInfoLabel(0)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    /*Setting up the Camera*/
    mCamera->setPosition(Ogre::Vector3(1683,50,2116));
    mCamera->lookAt(Ogre::Vector3(1963,50,1660));
    mCamera->setNearClipDistance(0.1);
    bool infiniteClip = mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE);
    if(infiniteClip)
      mCamera->setFarClipDistance(0);
    else
      mCamera->setFarClipDistance(50000);
    
    /*Setting up a Light*/
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
    Ogre::Vector3 lightdir(0.55,-0.3,0.75);
    lightdir.normalize();
    Ogre::Light* light = mSceneMgr->createLight("TestLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpeculatColour(Ogre::ColourValue(0.4,0.4,0.4));
    
    /*Configuring the Terrain*/
    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr,Ogre::Terrain::ALIGN_X_Z,513,12000.0);
    mTerrainGroup->setFilenameConvention(Ogre::String("terrain"),Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
    configureTerrainDefaults(light);
    for(long x=0; x<=0; ++x)
      for(long y=0; y<=0; ++y)
         defineTerrain(x,y);
   mTerrainGroup->loadAllTerrains(true);
   if(mTerrainsImported)
   {
      Ogre::TerrainGroup::Terrainiterator ti = mTerrainGroup->getTerrainIterator();
      while(ti.hasMoreElements())
      {
         Ogre::Terrain* t = ti.getNext()->instance;
         initBlendMaps(t);
      }
   }
   mTerrainGroup->freeTemporaryResources();
   
   /*Writing configureTerrainDefaults*/
   /*Writing defineTerrain*/
   /*Writing getTerrainImage*/ //DONE
}

void TutorialApplication::createFrameListener()
{
   BaseApplication::createFrameListener();
}

void TutorialApplication::destroyScene()
{
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
   bool ret = BaseApplication::frameRenderingQueued(fe);
   return ret;
}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
   if(flipX)
      img.flipAroundY();
   if(flipY)
      img.flipAroundX();
}

void TutorialApplication::defineTerrain(long x, long y)
{
   Ogre::String filename = mTerrainGroup->generateFilename(x, y);
   
   bool exists = Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(),filename);
   
   if (exists)
      mTerrainGroup->defineTerrain(x, y);
   else
   {
      Ogre::Image img;
      getTerrainImage(x % 2 != 0,y %2 != 0, img);
      mTerrainGroup->defineTerrain(x, y, &img);
      
      mTerrainsImported = true;
   }
}

void TutorialApplication::initBlendMaps(Ogre::Terrain* terrain)
{
}

void TutorialApplication::configureTerrainDefaults(Ogre::Light* light)
{
/*set how the Terrain is rendered*/
   mTerrainGlobals->setMaxPixelError(8);
   mTerrainGlobals->setCompositeMapDistance(3000);
   
   mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
   mTerrainGlobals->setCompositeMapAmbiant(mSceneMgr->getAmbiantLight());
   mTerrainGlobals->setLightMapDirection(light->getDiffuseColour());
   
   Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
   importData.terrainSize=513;
   importData.worldSize=12000.0;
   importData.inputScale=600;
   importData.minBatchSize=33;
   importData.maxBatchSize=65;
   
   importData.layerList.resize(3);
   
   
   importData.layerList[0].worldSize = 100;
   importData.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
   importData.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
   importData.layerList[1].worldSize = 30;
   importData.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
   importData.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
   importData.layerList[1].worldSize = 200;
   importData.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
   importData.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif