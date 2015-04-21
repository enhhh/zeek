//
//  LevelSelectLayer.h
//  zeek
//
//  Created by enh on 15/4/21.
//
//

#ifndef __zeek__LevelSelectLayer__
#define __zeek__LevelSelectLayer__

#include "preInclude.h"

class LevelSelectLayer
: public Layer
{
public:
    static LevelSelectLayer*create();
    
protected:
    
    virtual bool init();
    
    
    
};

#endif /* defined(__zeek__LevelSelectLayer__) */
