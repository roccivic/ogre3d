#include "Opponent.h"

Opponent::Opponent(Ogre::SceneManager* mSceneMgr, Player* player) {
	this->mSceneMgr = mSceneMgr;
	this->player = player;
	position[0] = 4;
	position[1] = 4;
	timer = 5.0;
	busy = false;
	mRotating1 = false;
	mRotating2 = false;
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
	mOpponentNode->yaw(Ogre::Degree(180));
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
	lookAtOrigin();
}

void Opponent::tick(const Ogre::FrameEvent& evt) {
 	mOpponentAnimation = mOpponent->getAnimationState("swim");
    mOpponentAnimation->setLoop(true);
    mOpponentAnimation->setEnabled(true);
	mOpponentAnimation->addTime(evt.timeSinceLastFrame);
	timer -= evt.timeSinceLastFrame;
	if (timer < 0) {
		timer = 5.0;
		move();
	}
	if (busy) {
		if (mRotating1) {
			mRotProgress += mRotFactor;
			if(mRotProgress>1) {
				mRotating1 = false;
			} else {
				Ogre::Quaternion delta = Ogre::Quaternion::Slerp(mRotProgress, mOrientSrc, mOrientDest, true);
				mOpponentNode->setOrientation(delta);
			}
		} else if (mRotating2) {
			mRotProgress += mRotFactor;
			if(mRotProgress>1) {
				mRotating2 = false;
				busy = false;
			} else {
				Ogre::Quaternion delta = Ogre::Quaternion::Slerp(mRotProgress, mOrientSrc, mOrientDest, true);
				mOpponentNode->setOrientation(delta);
			}
		} else {
			mDirection = mDestination - mOpponentNode->getPosition();
			mDistance = mDirection.normalise();
			Ogre::Real move = 800 * evt.timeSinceLastFrame;
			mDistance -= move;
			if (mDistance <= 0.0f) {
				mOpponentNode->setPosition(mDestination);
				mDestination = Ogre::Vector3(0, 25, 0);
				mDirection = mDestination - mOpponentNode->getPosition();
				Ogre::Vector3 src = mOpponentNode->getOrientation() * -Ogre::Vector3::UNIT_X;
				Ogre::Quaternion quat = src.getRotationTo(mDirection);
				mRotating2 = true;
				mRotFactor = 1.0f / 25;
				mOrientSrc = mOpponentNode->getOrientation();
				mOrientDest = quat * mOrientSrc;
				mRotProgress = 0;
			} else {
				mOpponentNode->translate(mDirection * move);
			}
		}
	}
}

void Opponent::lookAtOrigin() {
	mDestination = Ogre::Vector3(0, 25, 0);
	mDirection = mDestination - mOpponentNode->getPosition();
	Ogre::Vector3 src = mOpponentNode->getOrientation() * -Ogre::Vector3::UNIT_X;
	Ogre::Quaternion quat = src.getRotationTo(mDirection);
	mOpponentNode->rotate(quat);
}

void Opponent::move() {
	if (! busy) {
		busy = true;
		int position1[2];
		int position2[2];
		if ((position[0] == 0 && position[1] == 0) || (position[0] == 4 && position[1] == 4)) {
			position1[0] = 0;
			position1[1] = 4;
			position2[0] = 4;
			position2[1] = 0;
		} else if ((position[0] == 0 && position[1] == 4) || (position[0] == 4 && position[1] == 0)) {
			position1[0] = 0;
			position1[1] = 0;
			position2[0] = 4;
			position2[1] = 4;
		}
		int* playerPosition = player->getPosition();
		Ogre::Real distanceToPos1X = (Ogre::Real)(playerPosition[0] - position1[0]);
		Ogre::Real distanceToPos1Z = (Ogre::Real)(playerPosition[1] - position1[1]);
		Ogre::Real distanceToPosition1 = Ogre::Math::Sqrt(distanceToPos1X*distanceToPos1X+distanceToPos1Z*distanceToPos1Z);
		Ogre::Real distanceToPos2X = (Ogre::Real)(playerPosition[0] - position2[0]);
		Ogre::Real distanceToPos2Z = (Ogre::Real)(playerPosition[1] - position2[1]);
		Ogre::Real distanceToPosition2 = Ogre::Math::Sqrt(distanceToPos2X*distanceToPos2X+distanceToPos2Z*distanceToPos2Z);
		if (distanceToPosition1 > distanceToPosition2) {
			position[0] = position1[0];
			position[1] = position1[1];
		} else {
			position[0] = position2[0];
			position[1] = position2[1];
		}
		mDestination = Ogre::Vector3(position[0]*200-400, 25, position[1]*200-400);
		mDirection = mDestination - mOpponentNode->getPosition();
		Ogre::Vector3 src = mOpponentNode->getOrientation() * -Ogre::Vector3::UNIT_X;
		Ogre::Quaternion quat = src.getRotationTo(mDirection);
		mRotating1 = true;
		mRotFactor = 1.0f / 10;
		mOrientSrc = mOpponentNode->getOrientation();
		mOrientDest = quat * mOrientSrc;
		mRotProgress = 0;
	}
}