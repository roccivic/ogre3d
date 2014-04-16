#include "Player.h"

Player::Player(Ogre::SceneManager* mSceneMgr) {
	this->mSceneMgr = mSceneMgr;
	rotated = false;
	position[0] = 0;
	position[1] = 0;
	direction = Direction::NORTH;
	mRotating = false;
	mRotatingLeft = false;
	walking = false;
	dying = false;
	dyingProgress = 1.0;
}
 
Player::~Player() {

}

int* Player::getPosition() {
	return position;
}

void Player::die() {
	dying = true;
}

bool Player::isWalking() {
	return walking;
}

void Player::reset() {
	Ogre::String floorTileName = "N" + Ogre::StringConverter::toString(4-position[1]) + Ogre::StringConverter::toString(position[0]);
	Ogre::SceneNode* floorTile = mSceneMgr->getSceneNode(floorTileName);
	Ogre::Vector3 floorTilePos = floorTile->getPosition();
	floorTilePos.y = 0;
	floorTile->setPosition(floorTilePos);
	mPlayerNode->setPosition(Ogre::Vector3(-400, 0, 400));

	rotated = false;
	position[0] = 0;
	position[1] = 0;
	mRotating = false;
	mRotatingLeft = false;
	walking = false;
	dying = false;
	dyingProgress = 1.0;
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
    spotLight->setDiffuseColour(0.3, 0.3, 0.3);
    spotLight->setSpecularColour(0.3, 0.3, 0.3);
    spotLight->setDirection(0, -1, 0);
    spotLight->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(60));
	mPlayerNode->attachObject(spotLight);
	
 	mPlayerAnimation1 = mPlayer1->getAnimationState("Idle2");
    mPlayerAnimation1->setLoop(true);
    mPlayerAnimation1->setEnabled(true);
 	mPlayerAnimation3 = mPlayer3->getAnimationState("Idle");
    mPlayerAnimation3->setLoop(true);
    mPlayerAnimation3->setEnabled(true);
}

bool Player::tick(const Ogre::FrameEvent& evt) {
	bool retval = false;
	mPlayerAnimation1 = mPlayer1->getAnimationState("Idle2");
	mPlayerAnimation1->setLoop(true);
	mPlayerAnimation1->setEnabled(true);
 	mPlayerAnimation3 = mPlayer3->getAnimationState("Idle");
	mPlayerAnimation3->setLoop(true);
	mPlayerAnimation3->setEnabled(true);

	if (dying) {
		dyingProgress -= evt.timeSinceLastFrame;
		Ogre::Real move = -1000 * evt.timeSinceLastFrame;
		Ogre::String floorTileName = "N" + Ogre::StringConverter::toString(4-position[1]) + Ogre::StringConverter::toString(position[0]);
		mSceneMgr->getSceneNode(floorTileName)->translate(Ogre::Vector3(0, move, 0));
		mPlayerNode->translate(Ogre::Vector3(0, move, 0));
		if (dyingProgress < 0.0) {
			reset();
		}
		retval = true;
	} else if (mRotating) {
		mPlayerAnimation1 = mPlayer1->getAnimationState("Walk");
		mPlayerAnimation1->setLoop(true);
		mPlayerAnimation1->setEnabled(true);
 		mPlayerAnimation3 = mPlayer3->getAnimationState("Walk");
		mPlayerAnimation3->setLoop(true);
		mPlayerAnimation3->setEnabled(true);
		mRotatingTarget -= 4.5;
		if (mRotatingTarget < 0.0) {
			mRotating = false;
		} else {
			if (mRotatingLeft) {
				mPlayerNode->yaw(Ogre::Degree(4.5));
			} else {
				mPlayerNode->yaw(Ogre::Degree(-4.5));
			}
		}
		retval = true;
	} else if (walking) {
		mPlayerAnimation1 = mPlayer1->getAnimationState("Walk");
		mPlayerAnimation1->setLoop(true);
		mPlayerAnimation1->setEnabled(true);
 		mPlayerAnimation3 = mPlayer3->getAnimationState("Walk");
		mPlayerAnimation3->setLoop(true);
		mPlayerAnimation3->setEnabled(true);
		mDirection = mDestination - mPlayerNode->getPosition();
		mDistance = mDirection.normalise();
		Ogre::Real move = 400 * evt.timeSinceLastFrame;
		mDistance -= move;
		if (mDistance <= 0.0f) {
			mPlayerNode->setPosition(mDestination);
			walking = false;
		} else {
			mPlayerNode->translate(mDirection * move);
		}
		mPlayerAnimation1->addTime(evt.timeSinceLastFrame);
		mPlayerAnimation3->addTime(evt.timeSinceLastFrame);
		retval = true;
	}
	mPlayerAnimation1->addTime(evt.timeSinceLastFrame);
	mPlayerAnimation3->addTime(evt.timeSinceLastFrame);
	return retval;
}

void Player::keyUp() {
	if (! mRotating && ! walking && ! dying) {
		if (updatePosition(direction)) {
			walking = true;
			mDestination = Ogre::Vector3(position[0]*200-400, 0, -(position[1]*200-400));
			mDirection = mDestination - mPlayerNode->getPosition();
		}
	}
}

void Player::keyDown() {
	if (! mRotating && ! walking && ! dying) {
		int dir = direction + 4;
		if (dir > 7) {
			dir -= 8;
		}
		if (updatePosition(dir)) {
			walking = true;
			mDestination = Ogre::Vector3(position[0]*200-400, 0, -(position[1]*200-400));
			mDirection = mDestination - mPlayerNode->getPosition();
		}
	}
}

void Player::keyLeft() {
	if (! mRotating && ! walking && ! dying) {
		mRotating = true;
		mRotatingLeft = true;
		direction--;
		if (direction < 0) {
			direction = 7;
		}
		rotated = !rotated;
		mRotatingTarget = 45.0;
	}
}

void Player::keyRight() {
	if (! mRotating && ! walking && ! dying) {
		mRotating = true;
		mRotatingLeft = false;
		direction++;
		if (direction > 7) {
			direction = 0;
		}
		rotated = !rotated;
		mRotatingTarget = 45.0;
	}
}

bool Player::updatePosition(int dir) {
	bool moved = false;
	if (dir == Direction::NORTH && position[1] < 4) {
		position[1]++;
		moved = true;
	} else if (dir == Direction::NORTH_EAST && position[1] < 4 && position[0] < 4) {
		position[0]++;
		position[1]++;
		moved = true;
	} else if (dir == Direction::EAST && position[0] < 4) {
		position[0]++;
		moved = true;
	} else if (dir == Direction::SOUTH_EAST && position[1] > 0 && position[0] < 4) {
		position[0]++;
		position[1]--;
		moved = true;
	} else if (dir == Direction::SOUTH && position[1] > 0) {
		position[1]--;
		moved = true;
	} else if (dir == Direction::SOUTH_WEST && position[1] > 0 && position[0] > 0) {
		position[0]--;
		position[1]--;
		moved = true;
	} else if (dir == Direction::WEST && position[0] > 0) {
		position[0]--;
		moved = true;
	} else if (dir == Direction::NORTH_WEST && position[1] < 4 && position[0] > 0) {
		position[0]--;
		position[1]++;
		moved = true;
	}
	return moved;
}

void Player::character1() {
	if (! dying) {
		mPlayer1->setVisible(true);
		mPlayer2->setVisible(false);
		mPlayer3->setVisible(false);
	}
}

void Player::character2() {
	if (! dying) {
		mPlayer1->setVisible(false);
		mPlayer2->setVisible(true);
		mPlayer3->setVisible(false);
	}
}

void Player::character3() {
	if (! dying) {
		mPlayer1->setVisible(false);
		mPlayer2->setVisible(false);
		mPlayer3->setVisible(true);
	}
}