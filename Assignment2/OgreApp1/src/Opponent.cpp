#include "Opponent.h"

Opponent::Opponent(Ogre::SceneManager* mSceneMgr) {
	this->mSceneMgr = mSceneMgr;
	position[0] = 4;
	position[1] = 4;
}
 
Opponent::~Opponent(void) {

}

int* Opponent::getPosition() {
	return position;
}

void Opponent::makeOpponent() {
	mOpponent = mSceneMgr->createEntity("Opponent", "fish.mesh");
    mOpponent->setCastShadows(true);
    mOpponentNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("OpponentNode");
	mOpponentNode->scale(20, 20, 20);
	mOpponentNode->attachObject(mOpponent);
	mOpponentNode->translate(Ogre::Vector3(400, 25, -400));
	Ogre::Light* spotLight2 = mSceneMgr->createLight("OpponentLight");
    spotLight2->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight2->setDiffuseColour(0.1, 0.1, 1.0);
    spotLight2->setSpecularColour(0.1, 0.1, 1.0);
    spotLight2->setDirection(0, -1, 0);
    spotLight2->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(35));
	mOpponentNode->attachObject(spotLight2);
}

void Opponent::tick(const Ogre::FrameEvent& evt) {
 	mOpponentAnimation = mOpponent->getAnimationState("swim");
    mOpponentAnimation->setLoop(true);
    mOpponentAnimation->setEnabled(true);
	mOpponentAnimation->addTime(evt.timeSinceLastFrame);
}