#include "CCShakeUIWidget.h"

CShakeUIWidget::CShakeUIWidget()
{

}

CShakeUIWidget::~CShakeUIWidget()
{	
	
}

/*( 按钮瞄点：0.5，0.5，帧频：0.06秒/帧，动画共7帧，全为XY缩放 )
	【长形：（7帧）】
	--------------------
	1: 1.07,0.96
	2: 0.97,1.07
	3: 1.05,0.96
	4: 0.97,1.04
	5: 1.01,0.97
	6: 0.99,1.02
	7: 1.00,1.00
	============
	【方形圆形：（7帧）】
	--------------------
	1：1.12,0.90
	2：0.94,1.10
	3：1.08,0.92
	4：0.95,1.05
	5：1.04,0.94
	6：0.97,1.04
	7：1.00,1.00
	--------------------*/

void CShakeUIWidget::OnPushWidget(Node* pWidget,ShakeType nType)
{
	ActionInterval* pAction = NULL;
	ActionInterval* scaleTo1 = NULL;
	ActionInterval* scaleTo2 = NULL;
	ActionInterval* scaleTo3 = NULL;
	ActionInterval* scaleTo4 = NULL;
	ActionInterval* scaleTo5 = NULL;
	ActionInterval* scaleTo6 = NULL;
	ActionInterval* scaleTo7 = NULL;

	switch(nType)
	{
	case  ShakeType_Rectangle:
		//按钮的抖动
		scaleTo1 = ScaleTo::create(0.05, 1.07,0.96);
		scaleTo2 = ScaleTo::create(0.05, 0.97,1.07);
		scaleTo3 = ScaleTo::create(0.05, 1.05,0.96);
		scaleTo4 = ScaleTo::create(0.05, 0.97,1.04);
		scaleTo5 = ScaleTo::create(0.05, 1.01,0.97);
		scaleTo6 = ScaleTo::create(0.05, 0.99,1.02);
		scaleTo7 = ScaleTo::create(0.05, 1.00,1.00);
		pAction = Sequence::create(scaleTo1,scaleTo2,scaleTo3,scaleTo4,scaleTo5,scaleTo6,scaleTo7,NULL);
		break;
	case ShakeType_Square:
		//按钮的抖动
		scaleTo1 = ScaleTo::create(0.05, 1.12,0.90);
		scaleTo2 = ScaleTo::create(0.05, 0.94,1.10);
		scaleTo3 = ScaleTo::create(0.05, 1.08,0.92);
		scaleTo4 = ScaleTo::create(0.05, 0.95,1.05);
		scaleTo5 = ScaleTo::create(0.05, 1.04,0.94);
		scaleTo6 = ScaleTo::create(0.05, 0.97,1.04);
		scaleTo7 = ScaleTo::create(0.05, 1.00,1.00);
		pAction = Sequence::create(scaleTo1,scaleTo2,scaleTo3,scaleTo4,scaleTo5,scaleTo6,scaleTo7,NULL);
		break;
	default:
		break;
	}
	
	if(pAction != NULL)
	{
        
		pWidget->runAction(pAction);
        
	}
}

ActionInterval* CShakeUIWidget::BtnAction(ShakeType nType){
    
    ActionInterval* pAction = NULL;
	ActionInterval* scaleTo1 = NULL;
	ActionInterval* scaleTo2 = NULL;
	ActionInterval* scaleTo3 = NULL;
	ActionInterval* scaleTo4 = NULL;
	ActionInterval* scaleTo5 = NULL;
	ActionInterval* scaleTo6 = NULL;
	ActionInterval* scaleTo7 = NULL;
    
    switch(nType)
	{
        case  ShakeType_Rectangle:
            //按钮的抖动
            scaleTo1 = ScaleTo::create(0.05, 1.07,0.96);
            scaleTo2 = ScaleTo::create(0.05, 0.97,1.07);
            scaleTo3 = ScaleTo::create(0.05, 1.05,0.96);
            scaleTo4 = ScaleTo::create(0.05, 0.97,1.04);
            scaleTo5 = ScaleTo::create(0.05, 1.01,0.97);
            scaleTo6 = ScaleTo::create(0.05, 0.99,1.02);
            scaleTo7 = ScaleTo::create(0.05, 1.00,1.00);
            pAction = Sequence::create(scaleTo1,scaleTo2,scaleTo3,scaleTo4,scaleTo5,scaleTo6,scaleTo7,NULL);
            break;
        case ShakeType_Square:
            //按钮的抖动
            scaleTo1 = ScaleTo::create(0.05, 1.12,0.90);
            scaleTo2 = ScaleTo::create(0.05, 0.94,1.10);
            scaleTo3 = ScaleTo::create(0.05, 1.08,0.92);
            scaleTo4 = ScaleTo::create(0.05, 0.95,1.05);
            scaleTo5 = ScaleTo::create(0.05, 1.04,0.94);
            scaleTo6 = ScaleTo::create(0.05, 0.97,1.04);
            scaleTo7 = ScaleTo::create(0.05, 1.00,1.00);
            pAction = Sequence::create(scaleTo1,scaleTo2,scaleTo3,scaleTo4,scaleTo5,scaleTo6,scaleTo7,NULL);
            break;
        default:
            break;
	}
    
    if(pAction != NULL)
	{
		return pAction;
	}
    
    return NULL;

}