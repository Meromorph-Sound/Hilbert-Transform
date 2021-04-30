//
//  IntegrationRule.h
//  VCO
//
//  Created by Julian Porter on 10/12/2014.
//
//

#ifndef __VCO__IntegrationRule__
#define __VCO__IntegrationRule__

#import <algorithm>
#import <functional>

namespace meromorph {
    
    class IntegrationRule {
    public:
        unsigned length;
        const float* pattern;
        
        IntegrationRule(size_t length_,const float* pattern_) : length(length_), pattern(pattern_) {};
        IntegrationRule(size_t length_,float divisor,const float* pattern_) : length(length_), pattern(pattern_) {};
        IntegrationRule(const IntegrationRule &other) : length(other.length), pattern(other.pattern) {};
        
        
    };

    const float trapezoidal[]={0.5,0.5};
    const IntegrationRule Trapezoidal=IntegrationRule(2,trapezoidal);
    const float simpson[]={1.0/6.0,4.0/6.0,1.0/6.0};
    const IntegrationRule Simpson=IntegrationRule(3,simpson);
    const float simpson38[]={0.125,0.375,0.375,0.125};
    const IntegrationRule Simpson38=IntegrationRule(4,simpson38);
    const float boole[]={7.0/90.0,32.0/90.0,12.0/90.0,32.0/90.0,7.0/90.0};
    const IntegrationRule Boole=IntegrationRule(5,boole);
}

#endif /* defined(__VCO__IntegrationRule__) */
