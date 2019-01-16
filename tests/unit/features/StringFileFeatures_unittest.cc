/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Eleftherios Avramidis
 */

#include "utils/Utils.h"
#include <gtest/gtest.h>
#include <shogun/features/StringFileFeatures.h>
#include <shogun/lib/SGStringList.h>
#include <shogun/lib/memory.h>

using namespace shogun;

TEST(StringFileFeaturesTest,clone)
{
	CStringFileFeatures<char>* f=new CStringFileFeatures<char>();
	CStringFileFeatures<char>* f_clone = (CStringFileFeatures<char>*)f->clone();

	EXPECT_EQ(f->get_alphabet()->get_alphabet(), f_clone->get_alphabet()->get_alphabet());
	EXPECT_EQ(f->get_file_name(), f_clone->get_file_name());

	SG_UNREF(f);
	SG_UNREF(f_clone);
}

TEST(StringFileFeaturesTest,clone_bool)
{
	CStringFileFeatures<bool>* f=new CStringFileFeatures<bool>();
	CStringFileFeatures<bool>* f_clone = (CStringFileFeatures<bool>*)f->clone();

	EXPECT_EQ(f->get_alphabet()->get_alphabet(), f_clone->get_alphabet()->get_alphabet());
	EXPECT_EQ(f->get_file_name(), f_clone->get_file_name());

	SG_UNREF(f);
	SG_UNREF(f_clone);
}

TEST(StringFileFeaturesTest,equals)
{
	// SGStringList<char> strings = generateRandomStringData();

	// CStringFeatures<char>* f=new CStringFeatures<char>(strings, ALPHANUM);
	// CStringFeatures<char>* f_clone = (CStringFeatures<char>*)f->clone();
	// EXPECT_EQ(f->equals(*f_clone), true);

	// SG_UNREF(f);
	// SG_UNREF(f_clone);
}
