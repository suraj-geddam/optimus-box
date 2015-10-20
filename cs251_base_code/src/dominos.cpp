/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/*
 * Base code for CS 251 Software Systems Lab
 * Department of Computer Science and Engineering, IIT Bombay
 *
 */

#include <stdlib.h>
#include <time.h>
#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
 /*! \section Ground
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-90.0, -4.0) and (90.0, -4.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //Ground
    b2Body* b1;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, -4.0f), b2Vec2(90.0f, -4.0f));
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

  /*! \section m1 Top horizontal shelf
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 6.0 and half-height 25.0. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (-45.0, 0.25). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(-45.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    /*! \section Dominos
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.1 and half-height 1.0. <br>
    * \b fd -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b shape, density is 20.0 and friction is 0.1. <br>
    * \b bd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of bd to (-49.5 + i, 36.25) (i iterates from 0 to 9). <br>
    * \b body -> body created using the definition bd, then attached to a fixture created from fixture fd. (type - b2Body*) <br>
    */
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-49.5f + 1.0f * i, 36.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }

/*! \section Pendulum
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.25 and half-height 1.5. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (-50.5, 33.0). <br>
    * \b b2 -> body created using the definition bd, then attached to a fixture created from \b shape, and with density 10.0. (type - b2Body*) <br>
    */
    //The pendulum that knocks the dominos off

    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);

	b2BodyDef bd;
	bd.position.Set(-50.5f, 33.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }

      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-54.0f, 38.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-51.0f, 43.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

   /*! \section m6 The revolving horizontal platform
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.15 and half-height 1.5. <br>
    * \b bd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of bd to (-38.5.0, 35.0). <br>
    * \b body -> body created using the definition bd and fixture fd. (type - b2Body*) <br>
    * \b fd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b shape, density is 1.0. <br>
    * \b shape2 -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.1 and half-height 1.0. <br>
    * \b bd2 -> a body defintion (type - b2BodyDef). <br>
    * \b Set -> function which sets coordinates of bd to (14.0, 16.0). <br>
    * \b body2 -> body created using the definition bd2. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b body1 and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
<br>
    */
    //The revolving horizontal platforms

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.15f, 1.5f);

      b2BodyDef bd;
      bd.position.Set(-38.5f, 35.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.1f, 1.0f);
      b2BodyDef bd2;
      bd2.position.Set(-38.5f, 35.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    /*! The path for small ball
    *\b -> Six edges to redirect the small ball to the gears
    */

    // The path for small ball
{

    /*! \section Path edge1
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-38.5f, 33.1f) and (-38.5f, 33.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge1
    b2Body* b2;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-38.5f, 33.1f), b2Vec2(-41.0f, 33.1f));
      b2BodyDef bd;
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 0.0f);
    }


    /*! \section Path edge2
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-41.0f, 28.1f) and (-41.0f, 33.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge2
    b2Body* b3;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-41.0f, 28.1f), b2Vec2(-41.0f, 33.1f));
      b2BodyDef bd;
      b3 = m_world->CreateBody(&bd);
      b3->CreateFixture(&shape, 0.0f);
    }


    /*! \section Path edge3
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-36.0f, 28.1f) and (-41.0f, 28.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge3
    b2Body* b4;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-36.0f, 28.1f), b2Vec2(-41.0f, 28.1f));
      b2BodyDef bd;
      b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 0.0f);
    }

    /*! \section Path edge4
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-43.0f, 34.3f) and (-43.0f, 28.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge4
    b2Body* b5;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-43.0f, 34.3f), b2Vec2(-43.0f, 28.1f));
      b2BodyDef bd;
      b5 = m_world->CreateBody(&bd);
      b5->CreateFixture(&shape, 0.0f);
    }

    /*! \section Path edge5
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-41.0f, 26.1f) and (-36.0f, 26.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge5
    b2Body* b6;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-41.0f, 26.1f), b2Vec2(-36.0f, 26.1f));
      b2BodyDef bd;
      b6 = m_world->CreateBody(&bd);
      b6->CreateFixture(&shape, 0.0f);
    }


    /*! \section Path edge6
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-43.0f, 28.1f) and (-41.0f, 26.1f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //path edge6
    b2Body* b7;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-43.0f, 28.1f), b2Vec2(-41.0f, 26.1f));
      b2BodyDef bd;
      b7 = m_world->CreateBody(&bd);
      b7->CreateFixture(&shape, 0.0f);
    }
}
    /*! \section m7 The small sphere
    * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.5. <br>
    * \b ballfd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b circle, density is 1.0, friction is 0.0, restitution is 0.0. <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of ballbd to (-39.5, 33.2). <br>
    * \b sbody -> body created using the definition ballbd and fixture ballfd. (type - b2Body*) <br>
    */
    //The small sphere
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.5;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-39.5f , 33.2f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);

    }

 /*! \section the Gears 
    * \b gear -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of gear to (-32.5,24.5 ). <br>
    * \b body2 -> body created using the definition gear. (type - b2Body*) <br>
    * \b sbody -> a body definition. (type - b2Body*) <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of ballbd to (-32.5,24.5 ). <br>
    * \b n_b -> a variable assigned the vavlue zero.(type - int32) <br>
    * \b ang_inc -> a variable assigned the vavlue of b2_pi / n_b .(type - float32) <br>
    * \b ang -> a variable assigned the vavlue zero.(type - float32) <br>
    * \b sbody -> body created using the definition ballbd. (type - b2Body*) <br>
    * \b shape1 -> Creates a polygon shape (type - b2PolygonShape).<br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.3 and half-height 3.0 and sets ang by (i+1)*(pi/4) where i varies from 0 to 3. <br>
    * \b fd3 -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b shape1, density is 0.5. <br>
    * \b sbody -> body created using the definition ballbd and fixture fd3. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b sbody and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
<br>
    */

	//the gear
	{
		b2BodyDef bd2;
		bd2.position.Set(-32.5,24.5);
		b2Body* body2 = m_world->CreateBody(&bd2);

		b2Body* sbody;
		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(-32.5, 24.5);
		sbody = m_world->CreateBody(&ballbd);

		int32 n_b = 4;
		float32 ang_inc = b2_pi / n_b;
		float32 ang=0;

		for(int32 i=0;i<n_b;i++,ang+=ang_inc)
		{
		  b2PolygonShape shape1;
		  shape1.SetAsBox(0.3f, 3.0f, b2Vec2(0.0f, 0.0f), ang);
		  b2FixtureDef fd3;
		  fd3.density = 0.5f;
		  fd3.shape = &shape1;
		  sbody->CreateFixture(&fd3);
		}

		b2RevoluteJointDef jointDef;
		jointDef.bodyA = sbody;
		jointDef.bodyB = body2;
		jointDef.localAnchorA.Set(0,0);
		jointDef.localAnchorB.Set(0,0);
		jointDef.collideConnected = false;
		m_world->CreateJoint(&jointDef);
	}
   /*! \section the Gears 
    * \b gear -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of gear to (-27.2,23.0 ). <br>
    * \b body2 -> body created using the definition gear. (type - b2Body*) <br>
    * \b sbody -> a body definition. (type - b2Body*) <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of ballbd to (-27.2,23.0 ). <br>
    * \b n_b -> a variable assigned the vavlue zero.(type - int32) <br>
    * \b ang_inc -> a variable assigned the vavlue of b2_pi / n_b .(type - float32) <br>
    * \b ang -> a variable assigned the vavlue zero.(type - float32) <br>
    * \b sbody -> body created using the definition ballbd. (type - b2Body*) <br>
    * \b shape1 -> Creates a polygon shape (type - b2PolygonShape).<br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.3 and half-height 3.0 and sets ang by (i+1)*(pi/4) where i varies from 0 to 3. <br>
    * \b fd3 -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b shape1, density is 0.5. <br>
    * \b sbody -> body created using the definition ballbd and fixture fd3. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b sbody and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
<br>
    */
  	//the gear
	{

		b2BodyDef bd2;
		bd2.position.Set(-27.2,23.0);
		b2Body* body2 = m_world->CreateBody(&bd2);

		b2Body* sbody;
		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(-27.2, 23.0);
		sbody = m_world->CreateBody(&ballbd);

		int32 n_b = 4;
		float32 ang_inc =  b2_pi / n_b;
		float32 ang=0;

		for(int32 i=0;i<n_b;i++,ang+=ang_inc)
		{
		  b2PolygonShape shape1;
		  shape1.SetAsBox(0.3f, 3.0f, b2Vec2(0.0f, 0.0f), ang);
		  b2FixtureDef fd3;
		  fd3.density = 0.5f;
		  fd3.shape = &shape1;
		  sbody->CreateFixture(&fd3);
		}

		b2RevoluteJointDef jointDef;
		jointDef.bodyA = sbody;
		jointDef.bodyB = body2;
		jointDef.localAnchorA.Set(0,0);
		jointDef.localAnchorB.Set(0,0);
		jointDef.collideConnected = false;
		m_world->CreateJoint(&jointDef);
	}

   /*! \section the Gears 
    * \b gear -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of gear to (-21.9,21.5 ). <br>
    * \b body2 -> body created using the definition gear. (type - b2Body*) <br>
    * \b sbody -> a body definition. (type - b2Body*) <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of ballbd to (-21.9,21.5 ). <br>
    * \b n_b -> a variable assigned the vavlue zero.(type - int32) <br>
    * \b ang_inc -> a variable assigned the vavlue of b2_pi / n_b .(type - float32) <br>
    * \b ang -> a variable assigned the vavlue zero.(type - float32) <br>
    * \b sbody -> body created using the definition ballbd. (type - b2Body*) <br>
    * \b shape1 -> Creates a polygon shape (type - b2PolygonShape).<br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.3 and half-height 3.0 and sets ang by (i+1)*(pi/4) where i varies from 0 to 3. <br>
    * \b fd3 -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b shape1, density is 0.5. <br>
    * \b sbody -> body created using the definition ballbd and fixture fd3. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b sbody and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
<br>
    */
	//the gear
  	{

		b2BodyDef bd2;
		bd2.position.Set(-21.9,21.5);
		b2Body* body2 = m_world->CreateBody(&bd2);

		b2Body* sbody;
		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(-21.9, 21.5);
		sbody = m_world->CreateBody(&ballbd);

		int32 n_b = 4;
		float32 ang_inc =  b2_pi / n_b;
		float32 ang=0;

		for(int32 i=0;i<n_b;i++,ang+=ang_inc)
		{
		  b2PolygonShape shape1;
		  shape1.SetAsBox(0.3f, 3.0f, b2Vec2(0.0f, 0.0f), ang);
		  b2FixtureDef fd3;
		  fd3.density = 0.5f;
		  fd3.shape = &shape1;
		  sbody->CreateFixture(&fd3);
		}

		b2RevoluteJointDef jointDef;
		jointDef.bodyA = sbody;
		jointDef.bodyB = body2;
		jointDef.localAnchorA.Set(0,0);
		jointDef.localAnchorB.Set(0,0);
		jointDef.collideConnected = false;
		m_world->CreateJoint(&jointDef);
	}

/*! \section Another horizontal shelf
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 6.0 and half-height 0.25. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (1.0, 6.0.0). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //Another horizontal shelf
   {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(-17.5f,11.35f), 0.0f);

      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
     /*! \section The train of small spheres
    * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.5. <br>
    * \b ballfd -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b circle, density is 1.0 and friction is 0.0 and restitution is 0.0. <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, and with density 10.0. (type - b2Body*) <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of \b ballbd to (-21.2 + i, 17.85) (i iterates from 0 to 1). <br>
    * \b spherebody -> body created using the definition \b ballbd, then attached to a fixture created from \b ballfd. (type - b2Body*) <br>
    */
    //The train of small spheres
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.5;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

      for (int i = 0; i < 2; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-21.2f + i*1.0, 17.85f);
          spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    /*! The hydraulic lift
    *\b Has six edges to form the container
    *\b Two planks to supports the loads
    *\b Fluid is replaced by balls of very smalll sze (radius 0.2f)
    */
    //The hydraulic Lift

{

 /*! \section Hydraulic container edge1
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-11.0, 15.0) and (-11.0, 5.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge1
 b2Body* b8;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-11.0f, 15.0f), b2Vec2(-11.0f, 5.0f));
      b2BodyDef bd;
      b8 = m_world->CreateBody(&bd);
      b8->CreateFixture(&shape, 0.0f);
    }
    /*! \section Hydraulic container edge2
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-11.0, 5.0) and (4.0, 5.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge2
    b2Body* b9;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-11.0f, 5.0f), b2Vec2(4.0f, 5.0f));
      b2BodyDef bd;
      b9 = m_world->CreateBody(&bd);
      b9->CreateFixture(&shape, 0.0f);
    }
    /*! \section Hydraulic container edge3
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (4.0, 5.0) and (4.0, 20.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge3
    b2Body* b10;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(4.0f, 5.0f), b2Vec2(4.0f, 20.0f));
      b2BodyDef bd;
      b10 = m_world->CreateBody(&bd);
      b10->CreateFixture(&shape, 0.0f);
    }

     /*! \section Hydraulic container edge4
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (1.0, 20.0) and (1.0, 8.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge4
    b2Body* b11;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(1.0f, 20.0f), b2Vec2(1.0f, 8.0f));
      b2BodyDef bd;
      b11 = m_world->CreateBody(&bd);
      b11->CreateFixture(&shape, 0.0f);
    }

    /*! \section Hydraulic container edge5
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (1.0, 8.0) and (-8.0, 8.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge5
    b2Body* b12;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(1.0f, 8.0f), b2Vec2(-8.0f, 8.0f));
      b2BodyDef bd;
      b12 = m_world->CreateBody(&bd);
      b12->CreateFixture(&shape, 0.0f);
    }

     /*! \section Hydraulic container edge6
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-8.0, 8.0) and (-8.0, 15.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
   // Hydraulic container edge6
    b2Body* b13;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-8.0f, 8.0f), b2Vec2(-8.0f,15.0f));
      b2BodyDef bd;
      b13 = m_world->CreateBody(&bd);
      b13->CreateFixture(&shape, 0.0f);
    }

    /*!The fluid
    * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.2. <br>
    * \b ballfd -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b circle, density is 0.2 and friction is 0.0 and restitution is 0.0. <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, and with density 10.0. (type - b2Body*) <br>
    * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b spherebody -> body created using the definition \b ballbd, then attached to a fixture created from \b ballfd. (type - b2Body*) <br>
    */
    //The fluid
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.2;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.02f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
//Set -> function which sets coordinates of \b ballbd to (-10.9f + j*0.2, 5.1f+i*0.2) (i iterates from 0 to 8 and j from 0 to 20).
      for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 20; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-10.9f + j*0.2, 5.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
      spherebody->SetGravityScale(0);
	  spherebody->CreateFixture(&ballfd);
	}
	}

//Set -> function which sets coordinates of \b ballbd to (3.9f - j*0.2, 5.1f+i*0.2) (i iterates from 0 to 8 and j from 0 to 20).
	for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 20; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(3.9f - j*0.2, 5.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
      spherebody->SetGravityScale(0);
	  spherebody->CreateFixture(&ballfd);
	}
    }

//Set -> function which sets coordinates of \b ballbd to (-10.9f + j*0., 8.0f+i*0.2) (i iterates from 0 to 18 and j from 0 to 8).
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-10.9f + j*0., 8.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
      spherebody->SetGravityScale(0);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    //Set -> function which sets coordinates of \b ballbd to (1.1f + j*0.2, 8.0f+i*0.2) (i iterates from 0 to 18 and j from 0 to 8).
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(1.1f + j*0.2, 8.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
      spherebody->SetGravityScale(0);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    }


    {
    /*! \section Horizontal plank1 for lift
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 1.5 and half-height 0.2. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (-9.5, 13.5). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //horizontal plank1 for lift
     b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(-9.5f, 13.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }

    {
    /*! \section horizontal plank2 for lift
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 1.5 and half-height 0.2. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (2.5, 13.5). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //Another horizontal shelf
     b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
      b2BodyDef bd3;
      bd3.position.Set(2.5f,13.5f);
      bd3.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd3);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }

     /*! \section m6 The revolving horizontal platform
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 1.8 and half-height 0.2. <br>
    * \b bd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of bd to (4.0, 20.0). <br>
    * \b body -> body created using the definition bd and fixture fd. (type - b2Body*) <br>
    * \b fd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b shape, density is 1.0. <br>
      * \b shape2 -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.2 and half-height 2.0. <br>
    * \b bd2 -> a body defintion (type - b2BodyDef). <br>
    * \b Set -> function which sets coordinates of bd to (4.0, 20.0). <br>
    * \b body2 -> body created using the definition bd2. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b body1 and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
    */
    //Revolving platform attatched to hydraulic lift
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.8f, 0.2f);

      b2BodyDef bd;
      bd.position.Set(4.0f, 20.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.8f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(4.0f, 20.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      }

      }

       /*! \section The heavy spheres on the platform
        * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 1.0. <br>
        * \b ballfd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b circle, density is 50.0, friction is 0.0, restitution is 0.0. <br>
        * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
        * \b Set -> function which sets coordinates of ballbd to (4.0, 21.2.0). <br>
        * \b sbody -> body created using the definition ballbd and fixture ballfd. (type - b2Body*) <br>
        */
    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(4.0f, 21.2f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

    /*! \section Another horizontal shelf
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 6.0 and half-height 25.0. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (12.0, 15.0). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
    //Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);

      b2BodyDef bd;
      bd.position.Set(12.0f, 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

       /*! \section Another Dominos
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.1 and half-height 1.0. <br>
    * \b fd -> a fixture defintion (type - b2FixtureDef), whose attributes are set as follows: shape is \b shape, density is 20.0 and friction is 0.1. <br>
    * \b bd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of bd to (7.5 + i, 16.25) (i iterates from 0 to 9). <br>
    * \b body -> body created using the definition bd, then attached to a fixture created from fixture fd. (type - b2Body*) <br>
    */
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(7.5f + 1.0f * i, 16.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }

   /*! \section The revolving vertical domino platform
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.15 and half-height 1.5. <br>
    * \b bd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
    * \b Set -> function which sets coordinates of bd to (18.5, 15.0). <br>
    * \b body -> body created using the definition bd and fixture fd. (type - b2Body*) <br>
    * \b fd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b shape, density is 1.0. <br>
      * \b shape2 -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.1 and half-height 1.0. <br>
    * \b bd2 -> a body defintion (type - b2BodyDef). <br>
    * \b Set -> function which sets coordinates of bd to (18.5, 15.0). <br>
    * \b body2 -> body created using the definition bd2. (type - b2Body*) <br>
    * \b jointDef -> a revolute joint definition (type - b2RevoluteJointDef) <br>
    * \b jointDef is then initialized as a revolute joint joining \b body1 and \b body2 by \b (0,0), whose bodies collide independently (collideConnected = false) then created in the world.
    */
    //The revolving vertical domino platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.15f, 1.5f);

      b2BodyDef bd;
      bd.position.Set(18.5f, 15.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.1f, 1.0f);
      b2BodyDef bd2;
      bd2.position.Set(18.5f, 15.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }


    /*! \section Platform for box
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape to (-17.0, 13.0) and (18.0, 13.0). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b1 -> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
//The platform for box
    b2Body* b14;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(17.0f, 13.0f), b2Vec2(18.0f, 13.0f));
      b2BodyDef bd;
      b14 = m_world->CreateBody(&bd);
      b14->CreateFixture(&shape, 0.0f);
    }

    /*! \section The small box
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.5 and half-height 0.5. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (17.5, 13.5). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with 5 density. (type - b2Body*) <br>
    */
// the small box

  {
     b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      b2BodyDef bd2;
      bd2.position.Set(17.5f, 13.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density =5.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }


  //Suraj's part

    {
    /*! \sectionThe fluid container contraption
    * \b shape -> Creates an edge shape (type - b2EdgeShape). <br>
    * \b Set -> function which sets the end vertices of the edge shape b15 to (15.0f, 10.0f) and (16.5f, 9.0f). <br>
    * \b Set -> function which sets the end vertices of the edge shape b16 to (16.5f, 9.0f) and (16.5f, 7.0f). <br>
    * \b Set -> function which sets the end vertices of the edge shape b17to (16.5f, 7.0f) and (20.5f, 7.0f). <br>
    * \b Set -> function which sets the end vertices of the edge shape b18to (20.5f, 7.0f) and (20.5f, 9.0f). <br>
    * \b bd -> a body defintion (holds the data needed to construct a rigid body, type - b2BodyDef) <br>
    * \b b15,b16,b17,b18-> body created using the definition bd, then attached to a fixture created from \b shape, with zero density. (type - b2Body*) <br>
    */
        //The 'fluid' container contraption

        b2Body* b15;
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(15.0f, 10.0f), b2Vec2(16.5f, 9.0f));
            b2BodyDef bd;
            b15 = m_world->CreateBody(&bd);
            b15->CreateFixture(&shape, 0.0f);
        }

        b2Body* b16;
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(16.5f, 9.0f), b2Vec2(16.5f, 7.0f));
            b2BodyDef bd;
            b16 = m_world->CreateBody(&bd);
            b16->CreateFixture(&shape, 0.0f);
        }

        b2Body* b17;
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(16.5f, 7.0f), b2Vec2(20.5f, 7.0f));
            b2BodyDef bd;
            b17 = m_world->CreateBody(&bd);
            b17->CreateFixture(&shape, 0.0f);
        }

        b2Body* b18;
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(20.5f, 7.0f), b2Vec2(20.5f, 9.0f));
            b2BodyDef bd;
            b18 = m_world->CreateBody(&bd);
            b18->CreateFixture(&shape, 0.0f);
        }


        {
         /*! \section The liquid body
        * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.2. <br>
        * \b ballfd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b circle, density is 2.0, friction is 0.0, restitution is 0.0. <br>
        * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
        * \b Set -> function which sets coordinates of ballbd to (16.7f + i*0.4, 8.8f - j*0.4) where i iterates from0 to 9 and j from 0 to 4. <br>
        * \b sbody -> body created using the definition ballbd and fixture ballfd. (type - b2Body*) <br>
        */

        b2Body* spherebody;

        b2CircleShape circle;
        circle.m_radius = 0.2;

        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 2.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;

        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                b2BodyDef ballbd;
                ballbd.type = b2_dynamicBody;
                ballbd.position.Set(16.7f + i*0.4, 8.8f - j*0.4);
                spherebody = m_world->CreateBody(&ballbd);
                spherebody->CreateFixture(&ballfd);
            }
        }

        }

        {
         /*! \section The boat
        * \b b2Polygonshape-> declares the shape as poly <br>
        * \b vertices.set-> sets the 4 vertex positions <br>
        * \b poly.set-> creates the body with 4 vertices<br>
        */
        //Boat
            b2Body* sbody;
            b2PolygonShape poly;
            b2Vec2 vertices[4];
            vertices[0].Set(16.9, 9);
            vertices[1].Set(17.7, 9);
            vertices[2].Set(18.3, 10);
            vertices[3].Set(16.3, 10);
            poly.Set(vertices, 4);


            b2FixtureDef ballfd;
            ballfd.shape = &poly;
            ballfd.density = 1.0f;
            b2BodyDef ballbd;
            ballbd.type = b2_dynamicBody;
            ballbd.position.Set(0.0f, 0.0f);
            sbody = m_world->CreateBody(&ballbd);
            sbody->CreateFixture(&ballfd);
        }

    }

    {
        // the platform for the ball

        b2PolygonShape shape;
        shape.SetAsBox(1.5f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(22.0f, 9.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);
    }


        /*! \section The liquid body
        * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.25. <br>
        * \b ballfd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b circle, density is 25.0, friction is 0.0, restitution is 0.0. <br>
        * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
        * \b Set -> function which sets coordinates of ballbd to 20.5,9.5. <br>
        * \b sbody -> body created using the definition ballbd and fixture ballfd. (type - b2Body*) <br>
        */

    {   // Impulse ball
        b2Body* sbody;
        b2CircleShape circle;
        circle.m_radius = 0.25;

        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 20.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(20.5f, 9.5f);
        sbody = m_world->CreateBody(&ballbd);
        sbody->CreateFixture(&ballfd);
     }


    {
        //Pulleys
     /*! \section Pulley system
    * \b bd1-> rotating impulse plank at position 25.5,7.0 <br>
    * \b ball 1, ball 2, ball 3, ball4-> the pulleys at 4 different positions to connected to each other<br>
   */
//The platform for box

        // Impulse plank

        b2BodyDef bd1;
        bd1.position.Set(25.5, 7.0);
        b2Body* body1 = m_world->CreateBody(&bd1);

        b2Body* sbody1;
        b2BodyDef ballbd1;
        ballbd1.type = b2_dynamicBody;
        ballbd1.position.Set(25.5, 7.0);
        sbody1 = m_world->CreateBody(&ballbd1);

        b2PolygonShape shape1;
        shape1.SetAsBox(1.5f, 0.25f);
        b2FixtureDef fd1;
        fd1.density = 0.5f;
        fd1.shape = &shape1;
        sbody1->CreateFixture(&fd1);

        b2RevoluteJointDef jointDef1;
        jointDef1.bodyA = sbody1;
        jointDef1.bodyB = body1;
        jointDef1.localAnchorA.Set(0,0);
        jointDef1.localAnchorB.Set(0,0);
        jointDef1.collideConnected = false;
        m_world->CreateJoint(&jointDef1);

        //ball1

        b2BodyDef bd2;
        bd2.position.Set(27.5, 4.0);
        b2Body* body2 = m_world->CreateBody(&bd2);

        b2Body* sbody2;
        b2BodyDef ballbd2;
        ballbd2.type = b2_dynamicBody;
        ballbd2.position.Set(27.5, 4.0);
        sbody2 = m_world->CreateBody(&ballbd2);

        b2CircleShape shape2;
        shape2.m_radius = 0.5;
        b2FixtureDef fd2;
        fd2.density = 0.5f;
        fd2.shape = &shape2;
        sbody2->CreateFixture(&fd2);

        b2RevoluteJointDef jointDef2;
        jointDef2.bodyA = sbody2;
        jointDef2.bodyB = body2;
        jointDef2.localAnchorA.Set(0,0);
        jointDef2.localAnchorB.Set(0,0);
        jointDef2.collideConnected = false;
        m_world->CreateJoint(&jointDef2);

        //ball2

        b2BodyDef bd3;
        bd3.position.Set(28.5, 6.5);
        b2Body* body3 = m_world->CreateBody(&bd3);

        b2Body* sbody3;
        b2BodyDef ballbd3;
        ballbd3.type = b2_dynamicBody;
        ballbd3.position.Set(28.5, 6.5);
        sbody3 = m_world->CreateBody(&ballbd3);

        b2CircleShape shape3;
        shape3.m_radius = 0.5;
        b2FixtureDef fd3;
        fd3.density = 0.5f;
        fd3.shape = &shape3;
        sbody3->CreateFixture(&fd3);

        b2RevoluteJointDef jointDef3;
        jointDef3.bodyA = sbody3;
        jointDef3.bodyB = body3;
        jointDef3.localAnchorA.Set(0,0);
        jointDef3.localAnchorB.Set(0,0);
        jointDef3.collideConnected = false;
        m_world->CreateJoint(&jointDef3);

        //ball3

        b2BodyDef bd4;
        bd4.position.Set(36.5, 6.5);
        b2Body* body4 = m_world->CreateBody(&bd4);

        b2Body* sbody4;
        b2BodyDef ballbd4;
        ballbd4.type = b2_dynamicBody;
        ballbd4.position.Set(36.5, 6.5);
        sbody4 = m_world->CreateBody(&ballbd4);

        b2CircleShape shape4;
        shape4.m_radius = 0.5;
        b2FixtureDef fd4;
        fd4.density = 0.5f;
        fd4.shape = &shape4;
        sbody4->CreateFixture(&fd4);

        b2RevoluteJointDef jointDef4;
        jointDef4.bodyA = sbody4;
        jointDef4.bodyB = body4;
        jointDef4.localAnchorA.Set(0,0);
        jointDef4.localAnchorB.Set(0,0);
        jointDef4.collideConnected = false;
        m_world->CreateJoint(&jointDef4);

        //ball4

        b2BodyDef bd5;
        bd5.position.Set(36.5, 4.0);
        b2Body* body5 = m_world->CreateBody(&bd5);

        b2Body* sbody5;
        b2BodyDef ballbd5;
        ballbd5.type = b2_dynamicBody;
        ballbd5.position.Set(36.5, 4.0);
        sbody5 = m_world->CreateBody(&ballbd5);

        b2CircleShape shape5;
        shape5.m_radius = 0.5;
        b2FixtureDef fd5;
        fd5.density = 0.5f;
        fd5.shape = &shape2;
        sbody5->CreateFixture(&fd5);

        b2RevoluteJointDef jointDef5;
        jointDef5.bodyA = sbody5;
        jointDef5.bodyB = body5;
        jointDef5.localAnchorA.Set(0,0);
        jointDef5.localAnchorB.Set(0,0);
        jointDef5.collideConnected = false;
        m_world->CreateJoint(&jointDef5);

        //final box

        b2PolygonShape shape6;
        shape6.SetAsBox(1.0f, 0.2f);
        b2BodyDef bd6;
        bd6.position.Set(31.0f, 3.45f);
        bd6.type = b2_dynamicBody;
        b2Body* body6 = m_world->CreateBody(&bd6);
        b2FixtureDef *fd6 = new b2FixtureDef;
        fd6->density = 2.0f;
        fd6->shape = new b2PolygonShape;
        fd6->shape = &shape6;
        body6->CreateFixture(fd6);

        /*! \section The cherry
        * \b circle -> Creates a circle shape (type - b2CircleShape) and its radius is set to 0.25. <br>
        * \b ballfd -> a fixture defintion (type - b2FixtureDef*), whose attributes are set as follows: shape is \b circle, density is 20.0, friction is 100.0, restitution is 0.0. <br>
        * \b ballbd -> a body defintion (type - b2BodyDef), with its attribute type set to b2_dynamicBody (which allows it to be acted upon by external forces). <br>
        * \b Set -> function which sets coordinates of ball to 31.0, 3.6 . <br>
        * \b sbody -> body created using the definition ballbd and fixture ballfd. (type - b2Body*) <br>
        */
        //cherry

        b2Body* sbody7;
        b2CircleShape circle7;
        circle7.m_radius = 0.25;

        b2FixtureDef ballfd7;
        ballfd7.shape = &circle7;
        ballfd7.density = 20.0f;
        ballfd7.friction = 100.0f;
        ballfd7.restitution = 0.0f;
        b2BodyDef ballbd7;
        ballbd7.type = b2_dynamicBody;
        ballbd7.position.Set(31.0f, 3.6f);
        sbody7 = m_world->CreateBody(&ballbd7);
        sbody7->CreateFixture(&ballfd7);

 /*! \section The cake
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 3.0 and half-height 1.0. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (28.0, -3.0). <br>
    * \b ground -> body created using the definition bd, then attached to a fixture created from \b shape, with 5 density and friction 100. (type - b2Body*) <br>
    */
        //cake

        b2PolygonShape shape8;
        shape8.SetAsBox(3.0f, 1.0f);
        b2BodyDef bd8;
        bd8.position.Set(28.0f, -3.0f);
        bd8.type = b2_staticBody;
        b2Body* body8 = m_world->CreateBody(&bd8);
        b2FixtureDef *fd8 = new b2FixtureDef;
        fd8->density = 5.0f;
        fd8->friction = 100.0f;
        fd8->shape = new b2PolygonShape;
        fd8->shape = &shape8;
        body8->CreateFixture(fd8);


        //Distance Joint implementation (works, approximately)

        //plank - ball1 joint
        b2DistanceJointDef* myjoint1 = new b2DistanceJointDef();
        myjoint1->Initialize(sbody1, sbody2, b2Vec2(27.0, 7.0), b2Vec2(27.0, 4.0));
        myjoint1->collideConnected = true;
        m_world->CreateJoint(myjoint1);

        //ball1 - ball2 joint
        b2DistanceJointDef* myjoint2 = new b2DistanceJointDef();
        myjoint2->Initialize(sbody2, sbody3, b2Vec2(28.0, 4.0), b2Vec2(28.0, 6.5));
        myjoint2->collideConnected = true;
        m_world->CreateJoint(myjoint2);

        //ball2 - ball3 joint
        b2DistanceJointDef* myjoint3 = new b2DistanceJointDef();
        myjoint3->Initialize(sbody3, sbody4, b2Vec2(28.5, 7.0), b2Vec2(36.5, 7.0));
        myjoint3->collideConnected = true;
        m_world->CreateJoint(myjoint3);

        //ball3 - ball4 joint
        b2DistanceJointDef* myjoint4 = new b2DistanceJointDef();
        myjoint4->Initialize(sbody4, sbody5, b2Vec2(37.0, 6.5), b2Vec2(37.0, 4.0));
        myjoint4->collideConnected = true;
        m_world->CreateJoint(myjoint4);

        //ball4 - final box joint
        b2DistanceJointDef* myjoint5 = new b2DistanceJointDef();
        myjoint5->Initialize(sbody5, body6, b2Vec2(36.5, 3.5), b2Vec2(32.0, 3.5));
        myjoint5->collideConnected = true;
        m_world->CreateJoint(myjoint5);


        //final platforms
 /*! \section platform final
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.875 and half-height 0.25. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (32.625, 3.0). <br>
    */
        {
            b2PolygonShape shape;
            shape.SetAsBox(0.875f, 0.25f);

            b2BodyDef bd;
            bd.position.Set(32.625f, 3.0f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->CreateFixture(&shape, 0.0f);
        }
 /*! \section The platform final 2
    * \b shape -> Creates a polygon shape (type - b2PolygonShape). <br>
    * \b SetAsBox -> function which sets the polygon to a box shape with half-width 0.875 and half-height 0.25. <br>
    * \b bd -> a body defintion (type - b2BodyDef) <br>
    * \b Set -> function which sets coordinates of bd to (29.375, 3.0). <br>
*/
        {
            b2PolygonShape shape;
            shape.SetAsBox(0.875f, 0.25f);

            b2BodyDef bd;
            bd.position.Set(29.375f, 3.0f);
            b2Body* ground = m_world->CreateBody(&bd);
            ground->CreateFixture(&shape, 0.0f);
        }


    }
        b2Body* b19;
        {
            b2EdgeShape shape;
            shape.Set(b2Vec2(28.0f,-2.5f), b2Vec2(28.0f, -1.5f));
            b2BodyDef bd;
            b19 = m_world->CreateBody(&bd);
            b19->CreateFixture(&shape, 0.0f);
        }

}




  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
