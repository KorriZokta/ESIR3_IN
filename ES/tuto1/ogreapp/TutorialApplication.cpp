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
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)
    /*LumièreAmbiante*/
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5)); //valeur RGB [0,1] //mSceneMgr vient de BasicApplication
    
    /*Caméra*/
    mCamera->setPosition(0,47,222);//Le setting de la position de la caméra se fait là
    
    /*Ogre1*/
    Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh"); //le mesh doit être loaded par le resource manager, ici c'est BasicApplication qui s'en occupe
    Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(ogreEntity); //on attache l'entité au noeud :)
    
    /*Ogre2*/
    Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
    //Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84,48,0)); //on peut donner la position à la création
    Ogre::SceneNode* ogreNode2 = ogreNode->createChildSceneNode(Ogre::Vector3(84,48,0)); //on peut donner des coordonnées relatives aussi
    ogreNode2->attachObject(ogreEntity2); //on attache l'entité au noeud :)
    
    /*Ogre3*/
    Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode3->setPosition(0,104,0);
    ogreNode3->setScale(2,1.2,1);
    ogreNode3->attachObject(ogreEntity3);
    
    /*Ogre4*/
    Ogre::Entity* ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode4->setPosition(-84,48,0);
    ogreNode4->roll(Ogre::Degree(-90));
    ogreNode4->setScale(1,1.2,2);
    ogreNode4->attachObject(ogreEntity4);
    
    /*Lumière*/
    Ogre::Light* light = mSceneMgr->createLight("MainLight"); //un nom unique et dans les ténèbres les lier (bah non c'est une lumière)
    light->setPosition(20,80,50);
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