#pragma once  
#include <math.h>  
class vector2D  
{  
public:  
   float x, z;  

   vector2D(float xi=0.0f, float zi=0.0f);  
   virtual ~vector2D();  

   float modulo() const;  
   float argumento() const;  
   vector2D operator + (vector2D v);  
   vector2D operator - (vector2D v);  
   bool operator==(const vector2D& other) const;  
};