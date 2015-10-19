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
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
    b2Body* b1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, -4.0f), b2Vec2(90.0f, -4.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
          
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-45.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

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
     
    //The revolving vertical domino platform
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
     b2Body* b2;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-38.5f, 33.1f), b2Vec2(-41.0f, 33.1f));
      b2BodyDef bd; 
      b2 = m_world->CreateBody(&bd); 
      b2->CreateFixture(&shape, 0.0f);
    }
    b2Body* b3;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-41.0f, 28.1f), b2Vec2(-41.0f, 33.1f));
      b2BodyDef bd; 
      b3 = m_world->CreateBody(&bd); 
      b3->CreateFixture(&shape, 0.0f);
    }
    b2Body* b4;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-36.0f, 28.1f), b2Vec2(-41.0f, 28.1f));
      b2BodyDef bd; 
      b4 = m_world->CreateBody(&bd); 
      b4->CreateFixture(&shape, 0.0f);
    }
    b2Body* b5;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-43.0f, 34.3f), b2Vec2(-43.0f, 28.1f));
      b2BodyDef bd; 
      b5 = m_world->CreateBody(&bd); 
      b5->CreateFixture(&shape, 0.0f);
    }
    b2Body* b6;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-41.0f, 26.1f), b2Vec2(-36.0f, 26.1f));
      b2BodyDef bd; 
      b6 = m_world->CreateBody(&bd); 
      b6->CreateFixture(&shape, 0.0f);
    }
    b2Body* b7;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-43.0f, 28.1f), b2Vec2(-41.0f, 26.1f));
      b2BodyDef bd; 
      b7 = m_world->CreateBody(&bd); 
      b7->CreateFixture(&shape, 0.0f);
    }
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

      
    //Another horizontal shelf
   {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(-17.5f,11.35f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

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
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-21.2f + i*1.0, 17.85f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
 b2Body* b8;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-11.0f, 15.0f), b2Vec2(-11.0f, 5.0f));
      b2BodyDef bd;
      b8 = m_world->CreateBody(&bd);
      b8->CreateFixture(&shape, 0.0f);
    }

    b2Body* b9;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-11.0f, 5.0f), b2Vec2(4.0f, 5.0f));
      b2BodyDef bd;
      b9 = m_world->CreateBody(&bd);
      b9->CreateFixture(&shape, 0.0f);
    }

    b2Body* b10;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(4.0f, 5.0f), b2Vec2(4.0f, 20.0f));
      b2BodyDef bd;
      b10 = m_world->CreateBody(&bd);
      b10->CreateFixture(&shape, 0.0f);
    }

    b2Body* b11;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(1.0f, 20.0f), b2Vec2(1.0f, 8.0f));
      b2BodyDef bd;
      b11 = m_world->CreateBody(&bd);
      b11->CreateFixture(&shape, 0.0f);
    }

    b2Body* b12;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(1.0f, 8.0f), b2Vec2(-8.0f, 8.0f));
      b2BodyDef bd;
      b12 = m_world->CreateBody(&bd);
      b12->CreateFixture(&shape, 0.0f);
    }

    b2Body* b13;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-8.0f, 8.0f), b2Vec2(-8.0f,15.0f));
      b2BodyDef bd;
      b13 = m_world->CreateBody(&bd);
      b13->CreateFixture(&shape, 0.0f);
    }
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.2;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.2f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

      for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 20; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-10.9f + j*0.2, 5.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
	}

	for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 20; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(3.9f - j*0.2, 5.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-10.9f + j*0., 8.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(1.1f + j*0.2, 8.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    }

    {
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

    //The revolving horizontal platforms
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

   //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(12.0f, 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

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

    b2Body* b14;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(18.5f, 13.0f), b2Vec2(16.5f, 13.0f));
      b2BodyDef bd;
      b14 = m_world->CreateBody(&bd);
      b14->CreateFixture(&shape, 0.0f);
    }

// the small box

  {
     b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      b2BodyDef bd2;
      bd2.position.Set(17.5f, 13.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 7.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
