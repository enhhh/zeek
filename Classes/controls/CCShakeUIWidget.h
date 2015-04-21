#ifndef CCShakeUIWidget_h__
#define CCShakeUIWidget_h__
#include "cocos2d.h"
USING_NS_CC;
//抖动的类
enum ShakeType
{
	ShakeType_Rectangle = 1,     //长方形
	ShakeType_Square    = 2,     //正方形
};

/************************************************************************/
/* 按钮的扭动动画                                      */
/************************************************************************/
class CShakeUIWidget: public Ref
{
public:
	CShakeUIWidget();
	~CShakeUIWidget();
	
public: 

	static void OnPushWidget(Node* pWidget,ShakeType nType = ShakeType_Rectangle);
    
    static ActionInterval* BtnAction(ShakeType nType = ShakeType_Rectangle);
};

#endif // CCShakeUIWidget_h__