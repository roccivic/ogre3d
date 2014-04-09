#include "Player.h"

Player::Player(Ogre::SceneManager* mSceneMgr) {
	this->mSceneMgr = mSceneMgr;
	rotated = false;
}
 
Player::~Player(void) {

}

void Player::makePlayer() {
	mPlayer1 = mSceneMgr->createEntity("Ninja", "ninja.mesh");
    mPlayer1->setCastShadows(true);
	
	mPlayer2 = mSceneMgr->createEntity("Jaiqua", "jaiqua.mesh");
    mPlayer2->setCastShadows(true);
	mPlayer2->setVisible(false);

	mPlayer3 = mSceneMgr->createEntity("Robot", "robot.mesh");
    mPlayer3->setCastShadows(true);
	mPlayer3->setVisible(false);

	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
	
	mPlayerNode->attachObject(mPlayer1);

	mPlayerNode->createChildSceneNode("JaiquaNode");
	mSceneMgr->getSceneNode("JaiquaNode")->scale(10, 10, 10);
	mSceneMgr->getSceneNode("JaiquaNode")->attachObject(mPlayer2);
	mSceneMgr->getSceneNode("JaiquaNode")->translate(Ogre::Vector3(0, 0, 500));

	mPlayerNode->createChildSceneNode("RobotNode");
	mSceneMgr->getSceneNode("RobotNode")->scale(2, 2, 2);
	mSceneMgr->getSceneNode("RobotNode")->attachObject(mPlayer3);
	mSceneMgr->getSceneNode("RobotNode")->translate(Ogre::Vector3(0, 0, 0));
	mSceneMgr->getSceneNode("RobotNode")->yaw(Ogre::Degree(90));

	mPlayerNode->translate(Ogre::Vector3(-400, 0, 400));

	Ogre::Light* spotLight = mSceneMgr->createLight("PlayerLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(0.1, 1.0, 0.1);
    spotLight->setSpecularColour(0.1, 1.0, 0.1);
    spotLight->setDirection(0, -1, 0);
    spotLight->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(35));
	mPlayerNode->attachObject(spotLight);
	
 	mPlayerAnimation1 = mPlayer1->getAnimationState("Idle2");
    mPlayerAnimation1->setLoop(true);
    mPlayerAnimation1->setEnabled(true);
 	mPlayerAnimation3 = mPlayer3->getAnimationState("Idle");
    mPlayerAnimation3->setLoop(true);
    mPlayerAnimation3->setEnabled(true);
}

void Player::tick(const Ogre::FrameEvent& evt) {
	mPlayerAnimation1 = mPlayer1->getAnimationState("Idle2");
	mPlayerAnimation1->setLoop(true);
	mPlayerAnimation1->setEnabled(true);
 	mPlayerAnimation3 = mPlayer3->getAnimationState("Idle");
	mPlayerAnimation3->setLoop(true);
	mPlayerAnimation3->setEnabled(true);
	mPlayerAnimation1->addTime(evt.timeSinceLastFrame);
	mPlayerAnimation3->addTime(evt.timeSinceLastFrame);
}

void Player::keyUp() {
	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	if (! rotated) {
		transVector = Ogre::Vector3(0,0,-200);
	} else {
		transVector = Ogre::Vector3(0,0,-282.8427);
	}
	mSceneMgr->getSceneNode("PlayerNode")->translate(transVector, Ogre::Node::TS_LOCAL);
}

void Player::keyDown() {
	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	if (! rotated) {
		transVector = Ogre::Vector3(0,0,200);
	} else {
		transVector = Ogre::Vector3(0,0,282.8427);
	}
	mSceneMgr->getSceneNode("PlayerNode")->translate(transVector, Ogre::Node::TS_LOCAL);
}

void Player::keyLeft() {
	rotated = !rotated;
	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(45));
}

void Player::keyRight() {
	rotated = !rotated;
	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-45));
}

void Player::character1() {
	mPlayer1->setVisible(true);
	mPlayer2->setVisible(false);
	mPlayer3->setVisible(false);
}

void Player::character2() {
	mPlayer1->setVisible(false);
	mPlayer2->setVisible(true);
	mPlayer3->setVisible(false);
}

void Player::character3() {
	mPlayer1->setVisible(false);
	mPlayer2->setVisible(false);
	mPlayer3->setVisible(true);
}