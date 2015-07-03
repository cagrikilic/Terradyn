//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//
//
// Function : model_draw( MODEL )
//            draw 3D model
//
// y.sato [2004.12]
// G.Ishigami [2005.10]
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//

#include <iostream>
using namespace std;

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawCylinder dsDrawCylinderD
#endif

#include "../matrix/matrix.h"
#include "../matrix/vector.h"
#include "../include/define.h"
#include "../include/spd.h"
#include "../include/rot.h"
#include "../include/draw.h"


void model_draw( MODEL &m )
{
    int i,j,k;
    dVector3 tmp1;
    dMatrix3 tmp2;
    dVector3 tmp3;
    dMatrix3 tmp4;
    
    dReal sides[3] = {BASE,BASE,BASE};
  
    // link0
    for( i=0 ; i<3 ; i++ ) tmp1[i] = m.link_pos[0][i];
    
    for( j=0 ; j<3 ; j++ )
	for( k=0 ; k<3 ; k++ )
	    tmp2[4*j+k] = m.link_R[0][3*j+k];
    
    dsSetColor(1,1,0);
    dsDrawBox( tmp1, tmp2, sides );
    
    
    if( m.LINKNUM != 1 )
    {
	// joint
	for ( i=1 ; i<m.LINKNUM ; i++ )
	{
	    dsSetColor (0,1,1);
	    for( j=0 ; j<3 ; j++ ) tmp1[j] = m.joint_pos[i][j];
	    for( j=0 ; j<3 ; j++ )
		for( k=0 ; k<3 ; k++ )
		    tmp2[4*j+k] = m.link_R[i][3*j+k];
	    
	    dsDrawSphereD (tmp1, tmp2, RAD);
	}
	
	// link
	for ( i=1 ; i<m.LINKNUM ; i++ )
	{
	    dsSetColor (1,1,1);
	    for( j=0 ; j<3 ; j++ ) tmp3[j] = m.link_pos[i][j];
	    for( j=0 ; j<3 ; j++ )
		for( k=0 ; k<3 ; k++ )
		    tmp4[4*j+k] = m.link_R[i][3*j+k];
	    
	    dsDrawBox (tmp3, tmp4, sides );
	}
	
	// end-effector
	for ( i=1 ; i<m.LINKNUM ; i++ )
	{
	    if( m.EE[i] != 0 )
	    {
		dsSetColor (1,1,0);
		for( j=0 ; j<3 ; j++ ) tmp1[j] = m.end_pos[m.EE[i]][j];
		for( j=0 ; j<3 ; j++ )
		    for( k=0 ; k<3 ; k++ )
			tmp2[4*j+k] = m.end_R[m.EE[i]][3*j+k];
		
	        //dsDrawSphereD (tmp1, tmp2, RAD);
		dsDrawCylinder (tmp1, tmp2, 0.02 ,0.092);
	    }
	}
	
	// line
	for ( i=1 ; i<m.LINKNUM ; i++ )
	{
	    dsSetColor (0,1,1);
	    dsDrawLineD ( m.joint_pos[i], m.link_pos[m.JA[i][0]] );
	    dsDrawLineD ( m.joint_pos[i], m.link_pos[m.JA[i][1]] );
	}
	for( i=1 ; i<m.LINKNUM ; i++ )
	{
	    if( m.EE[i] != 0 )
	    {
		dsSetColor (0,1,1);
		dsDrawLineD ( m.end_pos[m.EE[i]], m.link_pos[i] );
	    }
	}
	
    }
}
