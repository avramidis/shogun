/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Soeren Sonnenburg, Heiko Strathmann, Thoralf Klein, Roman Votyakov
 */

#include <shogun/base/init.h>
#include <shogun/modelselection/ParameterCombination.h>
#include <shogun/modelselection/ModelSelectionParameter.h>
#include <shogun/lib/DynamicObjectArray.h>
#include <shogun/lib/SGVector.h>

#include <stdlib.h>

using namespace std;
using namespace shogun;

void print_message(FILE* target, const char* str)
{
	fprintf(target, "%s", str);
}

void test_parameter_set_multiplication()
{
	SG_SPRINT("\ntest_parameter_set_multiplication()\n");

	DynArray<CModelSelectionParameter*> set1;
	DynArray<CModelSelectionParameter*> set2;

	SGVector<float64_t> param_vector(8);
	SGVector<float64_t>::range_fill_vector(param_vector.vector, param_vector.vlen);

	CModelSelectionParameter parameters[4];

	parameters[0].add_param("0", &param_vector.vector[0]);
	parameters[0].add_param("1", &param_vector.vector[1]);
	set1.append_element(&parameters[0]);

	parameters[1].add_param("2", &param_vector.vector[2]);
	parameters[1].add_param("3", &param_vector.vector[3]);
	set1.append_element(&parameters[1]);

	parameters[2].add_param("4", &param_vector.vector[4]);
	parameters[2].add_param("5", &param_vector.vector[5]);
	set2.append_element(&parameters[2]);

	parameters[3].add_param("6", &param_vector.vector[6]);
	parameters[3].add_param("7", &param_vector.vector[7]);
	set2.append_element(&parameters[3]);

	DynArray<CModelSelectionParameter*>* result=new DynArray<CModelSelectionParameter*>();//CParameterCombination::parameter_set_multiplication(set1, set2);

	for (index_t i=0; i<result->get_num_elements(); ++i)
	{
		CModelSelectionParameter* p=result->get_element(i);
		ParametersMap parameters = p->filter(ParameterProperties::NONE);
		for (ParametersMap::iterator it=parameters.begin(); it!=parameters.end(); ++it)
		{
			SG_SPRINT("%s ", it->first.name());
		}

		SG_SPRINT("\n");
		delete p;
	}
	delete result;
}

void test_leaf_sets_multiplication()
{
	SG_SPRINT("\ntest_leaf_sets_multiplication()\n");
	SGVector<float64_t> param_vector(6);
	SGVector<float64_t>::range_fill_vector(param_vector.vector, param_vector.vlen);

	CDynamicObjectArray sets;
	CParameterCombination* new_root=new CParameterCombination();
	SG_REF(new_root);

	CDynamicObjectArray* current=new CDynamicObjectArray();
	sets.append_element(current);
	CModelSelectionParameter* p=new CModelSelectionParameter();
	p->add_param("0", &param_vector.vector[0]);
	CParameterCombination* pc=new CParameterCombination(p);
	current->append_element(pc);

	p=new CModelSelectionParameter();
	p->add_param("1", &param_vector.vector[1]);
	pc=new CParameterCombination(p);
	current->append_element(pc);

	/* first case: one element */
	CDynamicObjectArray* result_simple=
			CParameterCombination::leaf_sets_multiplication(sets, new_root);

	SG_SPRINT("one set\n");
	for (index_t i=0; i<result_simple->get_num_elements(); ++i)
	{
		CParameterCombination* tpc=(CParameterCombination*)
				result_simple->get_element(i);
		tpc->print_tree();
		SG_UNREF(tpc);
	}
	SG_UNREF(result_simple);

	/* now more elements are created */

	current=new CDynamicObjectArray();
	sets.append_element(current);
	p=new CModelSelectionParameter();
	p->add_param("2", &param_vector.vector[2]);
	pc=new CParameterCombination(p);
	current->append_element(pc);

	p=new CModelSelectionParameter();
	p->add_param("3", &param_vector.vector[3]);
	pc=new CParameterCombination(p);
	current->append_element(pc);

	current=new CDynamicObjectArray();
	sets.append_element(current);
	p=new CModelSelectionParameter();
	p->add_param("4", &param_vector.vector[4]);
	pc=new CParameterCombination(p);
	current->append_element(pc);

	p=new CModelSelectionParameter();
	p->add_param("5", &param_vector.vector[5]);
	pc=new CParameterCombination(p);
	current->append_element(pc);

	/* second case: more element */
	CDynamicObjectArray* result_complex=
			CParameterCombination::leaf_sets_multiplication(sets, new_root);

	SG_SPRINT("more sets\n");
	for (index_t i=0; i<result_complex->get_num_elements(); ++i)
	{
		CParameterCombination* tpc=(CParameterCombination*)
				result_complex->get_element(i);
		tpc->print_tree();
		SG_UNREF(tpc);
	}
	SG_UNREF(result_complex);

	SG_UNREF(new_root);
}

int main(int argc, char **argv)
{
	init_shogun(&print_message, &print_message, &print_message);

	test_parameter_set_multiplication();
	test_leaf_sets_multiplication();

	exit_shogun();

	return 0;
}
