#include "Floor.h"

const Ogre::String Floor::floorNames[5][5] = {
	{"F00","F10","F20","F30","F40"},
	{"F01","F11","F21","F31","F41"},
	{"F02","F12","F22","F32","F42"},
	{"F03","F13","F23","F33","F43"},
	{"F04","F14","F24","F34","F44"}
};
const Ogre::String Floor::floorNodeNames[5][5] = {
	{"N00","N10","N20","N30","N40"},
	{"N01","N11","N21","N31","N41"},
	{"N02","N12","N22","N32","N42"},
	{"N03","N13","N23","N33","N43"},
	{"N04","N14","N24","N34","N44"}
};
const Ogre::String Floor::spotlightNames[5][5] = {
	{"S00","S10","S20","S30","S40"},
	{"S01","S11","S21","S31","S41"},
	{"S02","S12","S22","S32","S42"},
	{"S03","S13","S23","S33","S43"},
	{"S04","S14","S24","S34","S44"}
};

Floor::Floor(Ogre::SceneManager* mSceneMgr, Player* player) {
	this->mSceneMgr = mSceneMgr;
	this->player = player;
	timer = 0.5;
	spotlights = new bool*[5];
	for (int i=0; i<5; i++) {
		spotlights[i] = new bool[5];
	}
}
 
Floor::~Floor() {
	for (int i=0; i<5; i++) {
		delete spotlights[i];
	}
	delete spotlights;
}

void Floor::makeFloor() {
	mSceneMgr->getRootSceneNode()->createChildSceneNode("floor");
	int random1 = (int) Ogre::Math::RangeRandom(0.0,24.0);
	int random2;
	do {
		random2 = (int) Ogre::Math::RangeRandom(0.0,24.0);
	} while (random2 == random1);
	for (int x=0; x<5; x++) {
		for (int z=0; z<5; z++) {
			makePlane(
				floorNames[x][z],
				floorNodeNames[x][z],
				Ogre::Vector3(200*x-400, 0, 200*z-400),
				getTexture(x, z)
			);
			Ogre::Light* spotLight = makeSpotlight(
				spotlightNames[x][z],
				Ogre::Vector3(200*x-400, 300, 200*z-400)
			);
			int index = x*5+z;
			if (index == random1 || index == random2) {
				spotLight->setVisible(true);
				spotlights[x][z] = true;
			} else {
				spotLight->setVisible(false);
				spotlights[x][z] = false;
			}
		}
	}
}

Ogre::Light* Floor::makeSpotlight(const Ogre::String name, Ogre::Vector3 transVector) {
	Ogre::Light* spotLight = mSceneMgr->createLight(name);
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1.0, 0.1, 0.1);
    spotLight->setSpecularColour(1.0, 0.1, 0.1);
    spotLight->setDirection(0, -1, 0);
    spotLight->setPosition(transVector);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(35));
	return spotLight;
}

void Floor::makePlane(const Ogre::String name, const Ogre::String nodeName, Ogre::Vector3 transVector, Ogre::String texture) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 200, 16, 16, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entGround = mSceneMgr->createEntity(name, "ground");
    Ogre::SceneNode *floorPiece = mSceneMgr->getSceneNode("floor")->createChildSceneNode(nodeName);
	floorPiece->translate(transVector);
	floorPiece->attachObject(entGround);
    entGround->setMaterialName(texture);
    entGround->setCastShadows(false);
}

void Floor::tick(const Ogre::FrameEvent& evt) {
	timer -= evt.timeSinceLastFrame;
	if (timer < 0) {
		timer = 0.5;
		this->updateLights();
	}
}

void Floor::updateLights() {
	int random1 = (int) Ogre::Math::RangeRandom(0.0,24.0);
	int random2;
	do {
		random2 = (int) Ogre::Math::RangeRandom(0.0,24.0);
	} while (random2 == random1);
	for (int x=0; x<5; x++) {
		for (int z=0; z<5; z++) {
			Ogre::Light* spotLight = mSceneMgr->getLight(
				spotlightNames[x][z]
			);
			int index = x*5+z;
			if (index == random1 || index == random2) {
				spotLight->setVisible(true);
				spotlights[x][z] = true;
			} else {
				spotLight->setVisible(false);
				spotlights[x][z] = false;
			}
		}
	}
}

bool** Floor::getSpotlights() {
	return spotlights;
}

Ogre::String Floor::getTexture(int x, int z) {
	if ((z + (x % 2)) % 2 == 0) {
		return "Examples/RustySteel";
	} else {
		return "Examples/BumpyMetal";
	}
}