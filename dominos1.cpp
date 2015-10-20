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
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    b2Body* b2;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(0.0f, 30.0f), b2Vec2(0.0f, 20.0f));
      b2BodyDef bd;
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 0.0f);
    }

    b2Body* b3;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(0.0f, 20.0f), b2Vec2(15.0f, 20.0f));
      b2BodyDef bd;
      b3 = m_world->CreateBody(&bd);
      b3->CreateFixture(&shape, 0.0f);
    }

    b2Body* b4;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(15.0f, 20.0f), b2Vec2(15.0f, 30.0f));
      b2BodyDef bd;
      b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 0.0f);
    }

    b2Body* b5;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(12.0f, 30.0f), b2Vec2(12.0f, 23.0f));
      b2BodyDef bd;
      b5 = m_world->CreateBody(&bd);
      b5->CreateFixture(&shape, 0.0f);
    }

    b2Body* b6;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(12.0f, 23.0f), b2Vec2(3.0f, 23.0f));
      b2BodyDef bd;
      b6 = m_world->CreateBody(&bd);
      b6->CreateFixture(&shape, 0.0f);
    }

    b2Body* b7;
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(3.0f, 23.0f), b2Vec2(3.0f,30.0f));
      b2BodyDef bd;
      b7 = m_world->CreateBody(&bd);
      b7->CreateFixture(&shape, 0.0f);
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
	  ballbd.position.Set(0.1f + j*0.2, 20.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
	}

	for (int i = 0; i < 8; ++i){
      for (int j = 0; j < 20; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(14.9f - j*0.2, 20.1f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(0.1f + j*0.2, 23.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
     for (int i = 0; i < 18; ++i){
      for (int j = 0; j < 8; ++j)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(12.1f + j*0.2, 23.0f+i*0.2);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    }

    {
     b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(1.5f, 28.5f);
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
      bd3.position.Set(13.5f,28.5f);
      bd3.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd3);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }

  {
     b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
      b2BodyDef bd4;
      bd4.position.Set(15.0f, 30.0f);
      bd4.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd4);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
    }

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
      ballbd.position.Set(1.5f, 31.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

  }



  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
