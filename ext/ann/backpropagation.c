
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Ann_BackPropagation) {

	ZEPHIR_REGISTER_CLASS(Ann, BackPropagation, ann, backpropagation, ann_backpropagation_method_entry, 0);

	zend_declare_property_null(ann_backpropagation_ce, SL("delta"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(ann_backpropagation_ce, SL("trainset"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(ann_backpropagation_ce, SL("factor"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(ann_backpropagation_ce, SL("objects"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ann_backpropagation_ce TSRMLS_CC, 1, ann_visitor_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_BackPropagation, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_2;
	zend_bool _0;
	zval *delta, *trainset, *factor, *objects = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &delta, &trainset, &factor, &objects);

	if (!objects) {
		objects = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(delta, ann_delta_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'delta' must be an instance of 'Ann\\Delta'", "", 0);
		return;
	}
	if (!(zephir_is_instance_of(trainset, SL("Ann\\Trainset") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'trainset' must be an instance of 'Ann\\Trainset'", "", 0);
		return;
	}
	_0 = Z_TYPE_P(objects) != IS_NULL;
	if (_0) {
		_0 = !zephir_is_instance_of(objects, SL("SplObjectStorage") TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'objects' must be an instance of 'SplObjectStorage'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("delta"), delta TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("trainset"), trainset TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("factor"), factor TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	if (zephir_is_true(objects)) {
		ZEPHIR_CPY_WRT(_1, objects);
	} else {
		ZEPHIR_INIT_BNVAR(_1);
		_2 = zend_fetch_class(SL("SplObjectStorage"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_1, _2);
		if (zephir_has_constructor(_1 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
			zephir_check_call_status();
		}
	}
	zephir_update_property_this(this_ptr, SL("objects"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ann_BackPropagation, teach) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *network, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &network);



	if (!(zephir_instance_of_ev(network, ann_network_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'network' must be an instance of 'Ann\\Network'", "", 0);
		return;
	}
	ZEPHIR_CALL_METHOD(&_0, network, "accept", NULL, this_ptr);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(_0, "get", NULL, network);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, visitNetwork) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *inputs = NULL, *outputs = NULL;
	zval *network, *inputs_param = NULL, *outputs_param = NULL, *visitor = NULL, *neuron = NULL, **_2, *_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &network, &inputs_param, &outputs_param);

	zephir_get_arrval(inputs, inputs_param);
	zephir_get_arrval(outputs, outputs_param);


	if (!(zephir_instance_of_ev(network, ann_network_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'network' must be an instance of 'Ann\\Network'", "", 0);
		return;
	}
	ZEPHIR_CPY_WRT(visitor, this_ptr);
	zephir_is_iterable(outputs, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(neuron, _2);
		ZEPHIR_CALL_METHOD(&visitor, neuron, "accept", NULL, this_ptr);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_3);
	object_init_ex(_3, ann_network_ce);
	ZEPHIR_CALL_METHOD(&_4, visitor, "getall", NULL, outputs);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, inputs, _4);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(visitor, "set", NULL, network, _3);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, visitNeuron) {

	zend_class_entry *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *neuron, *branch, *function, *visitor = NULL, *_0, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &neuron, &branch, &function);



	if (!(zephir_is_instance_of(neuron, SL("Ann\\Neuron") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'neuron' must be an instance of 'Ann\\Neuron'", "", 0);
		return;
	}
	if (!(zephir_instance_of_ev(branch, ann_branch_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'branch' must be an instance of 'Ann\\Branch'", "", 0);
		return;
	}
	if (!(zephir_instance_of_ev(function, ann_outputfunction_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'function' must be an instance of 'Ann\\OutputFunction'", "", 0);
		return;
	}
	ZEPHIR_CALL_METHOD(&visitor, branch, "accept", NULL, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_0);
	_1 = zend_fetch_class(SL("Ann\\Neuron"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_0, _1);
	if (zephir_has_constructor(_0 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_2, visitor, "get", NULL, branch);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _2, function);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(visitor, "set", NULL, neuron, _0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, visitPeripheral) {

	zval *peripheral;

	zephir_fetch_params(0, 1, 0, &peripheral);



	if (!(zephir_is_instance_of(peripheral, SL("Ann\\Peripheral") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'peripheral' must be an instance of 'Ann\\Peripheral'", "", 0);
		return;
	}
	RETURN_THISW();

}

PHP_METHOD(Ann_BackPropagation, visitBias) {

	zval *bias;

	zephir_fetch_params(0, 1, 0, &bias);



	if (!(zephir_instance_of_ev(bias, ann_bias_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'bias' must be an instance of 'Ann\\Bias'", "", 0);
		return;
	}
	RETURN_THISW();

}

PHP_METHOD(Ann_BackPropagation, visitDendrite) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *synapses = NULL;
	zval *dendrite, *synapses_param = NULL, *visitor = NULL, *synapse = NULL, **_2, *_3 = NULL, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &dendrite, &synapses_param);

	zephir_get_arrval(synapses, synapses_param);


	if (!(zephir_instance_of_ev(dendrite, ann_dendrite_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'dendrite' must be an instance of 'Ann\\Dendrite'", "", 0);
		return;
	}
	ZEPHIR_CPY_WRT(visitor, this_ptr);
	zephir_is_iterable(synapses, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(synapse, _2);
		ZEPHIR_CALL_METHOD(&_3, synapse, "accept", NULL, visitor);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(visitor, _3);
	}
	ZEPHIR_INIT_VAR(_4);
	object_init_ex(_4, ann_dendrite_ce);
	ZEPHIR_CALL_METHOD(&_3, visitor, "getall", NULL, synapses);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, _4, "__construct", NULL, _3);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(visitor, "set", NULL, dendrite, _4);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, visitSynapse) {

	zend_class_entry *_5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *synapse, *neuron, *weight = NULL, *visitor = NULL, delta, weightChange, *_0, *_1, *_2 = NULL, *_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &synapse, &neuron, &weight);

	ZEPHIR_SEPARATE_PARAM(weight);


	if (!(zephir_is_instance_of(synapse, SL("Ann\\Synapse") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'synapse' must be an instance of 'Ann\\Synapse'", "", 0);
		return;
	}
	if (!(zephir_is_instance_of(neuron, SL("Ann\\Neuron") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'neuron' must be an instance of 'Ann\\Neuron'", "", 0);
		return;
	}
	ZEPHIR_CALL_METHOD(&visitor, neuron, "accept", NULL, this_ptr);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("factor"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("delta"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "delta", NULL, synapse);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(delta);
	mul_function(&delta, _0, _2 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_3);
	zephir_read_property(&_3, visitor, SL("trainset"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _3, "output", NULL, neuron);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(weightChange);
	mul_function(&weightChange, &delta, _2 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	zephir_add_function(_4, weight, &weightChange TSRMLS_CC);
	ZEPHIR_CPY_WRT(weight, _4);
	ZEPHIR_INIT_LNVAR(_4);
	_5 = zend_fetch_class(SL("Ann\\Synapse"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_4, _5);
	if (zephir_has_constructor(_4 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_2, visitor, "get", NULL, neuron);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, _4, "__construct", NULL, _2, weight);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(visitor, "set", NULL, synapse, _4);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *key, *value, *_0, *_1 = NULL, *objects = NULL, *_2, *_3, *_4, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key, &value);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("objects"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "contains", NULL, key);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		RETURN_THIS();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("objects"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_3);
	if (zephir_clone(_3, _2 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_CPY_WRT(objects, _3);
	ZEPHIR_CALL_METHOD(NULL, objects, "attach", NULL, key, value);
	zephir_check_call_status();
	object_init_ex(return_value, ann_backpropagation_ce);
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("delta"), PH_NOISY_CC);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("trainset"), PH_NOISY_CC);
	_6 = zephir_fetch_nproperty_this(this_ptr, SL("factor"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _4, _5, _6, objects);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_BackPropagation, get) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *key, *_0, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("objects"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "contains", NULL, key);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("objects"), PH_NOISY_CC);
		ZEPHIR_RETURN_CALL_METHOD(_2, "offsetget", NULL, key);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CCTOR(key);

}

PHP_METHOD(Ann_BackPropagation, getAll) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1;
	HashPosition _0;
	zval *keys, *result, *key = NULL, **_2, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keys);



	ZEPHIR_INIT_VAR(result);
	array_init(result);
	zephir_is_iterable(keys, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(key, _2);
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "get", &_4, key);
		zephir_check_call_status();
		zephir_array_append(&result, _3, PH_SEPARATE);
	}
	RETURN_CCTOR(result);

}

