/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>
#include <tf2/buffer_core.h>
#include <sys/time.h>
#include <ros/ros.h>
#include "LinearMath/btVector3.h"
#include "tf2/exceptions.h"

void seed_rand()
{
  //Seed random number generator with current microseond count
  timeval temp_time_struct;
  gettimeofday(&temp_time_struct,NULL);
  srand(temp_time_struct.tv_usec);
};

void generate_rand_vectors(double scale, uint64_t runs, std::vector<double>& xvalues, std::vector<double>& yvalues, std::vector<double>&zvalues)
{
  seed_rand();
  for ( uint64_t i = 0; i < runs ; i++ )
  {
    xvalues[i] = 1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX;
    yvalues[i] = 1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX;
    zvalues[i] = 1.0 * ((double) rand() - (double)RAND_MAX /2.0) /(double)RAND_MAX;
  }
}



TEST(tf2, setTransformFail)
{
  tf2::BufferCore tfc;
  geometry_msgs::TransformStamped st;
  EXPECT_FALSE(tfc.setTransform(st, "authority1"));
  
}

TEST(tf2, setTransformValid)
{
  tf2::BufferCore tfc;
  geometry_msgs::TransformStamped st;
  st.header.frame_id = "foo";
  st.header.stamp = ros::Time(1.0);
  st.child_frame_id = "child";
  st.transform.rotation.w = 1;
  EXPECT_TRUE(tfc.setTransform(st, "authority1"));
  
}

TEST(tf2_lookupTransform, LookupException_Nothing_Exists)
{
  tf2::BufferCore tfc;
  EXPECT_THROW(tfc.lookupTransform("a", "b", ros::Time().fromSec(1.0)), tf2::LookupException);
  
}

TEST(tf2_canTransform, Nothing_Exists)
{
  tf2::BufferCore tfc;
  EXPECT_FALSE(tfc.canTransform("a", "b", ros::Time().fromSec(1.0)));
  
}

TEST(tf2_lookupTransform, LookupException_One_Exists)
{
  tf2::BufferCore tfc;
  geometry_msgs::TransformStamped st;
  st.header.frame_id = "foo";
  st.header.stamp = ros::Time(1.0);
  st.child_frame_id = "child";
  st.transform.rotation.w = 1;
  EXPECT_TRUE(tfc.setTransform(st, "authority1"));
  EXPECT_THROW(tfc.lookupTransform("foo", "bar", ros::Time().fromSec(1.0)), tf2::LookupException);
  
}

TEST(tf2_canTransform, One_Exists)
{
  tf2::BufferCore tfc;
  geometry_msgs::TransformStamped st;
  st.header.frame_id = "foo";
  st.header.stamp = ros::Time(1.0);
  st.child_frame_id = "child";
  st.transform.rotation.w = 1;
  EXPECT_TRUE(tfc.setTransform(st, "authority1"));
  EXPECT_FALSE(tfc.canTransform("foo", "bar", ros::Time().fromSec(1.0)));
}


int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  ros::Time::init(); //needed for ros::TIme::now()
  ros::init(argc, argv, "tf_unittest");
  return RUN_ALL_TESTS();
}
