//
//  ElectrodeState.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__ElectrodeState__
#define __zeek__ElectrodeState__

#include "object/Electrode.h"
#include "state.h"

class ElectrodeState
: public State<Electrode>
{
public:
    static ElectrodeState* getInstance();
    
    virtual void enter(Electrode *);
    
    virtual void execute(float delta,Electrode *);
    
    virtual void exit(Electrode *);
    
protected:
    ElectrodeState();
    
};

#endif /* defined(__zeek__ElectrodeState__) */
