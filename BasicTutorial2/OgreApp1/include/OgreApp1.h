#ifndef __OgreApp1_h_
#define __OgreApp1_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


class OgreApp1 : public BaseApplication
{
public:
    OgreApp1(void);
    virtual ~OgreApp1(void);

protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
};

#endif // #ifndef __OgreApp1_h_
