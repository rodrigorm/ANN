
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"
#include "kernel/exception.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Ann_Network) {

	ZEPHIR_REGISTER_CLASS(Ann, Network, ann, network, ann_network_method_entry, 0);

	zend_declare_property_null(ann_network_ce, SL("inputs"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(ann_network_ce, SL("outputs"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ann_network_ce TSRMLS_CC, 1, ann_visitee_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_Network, __construct) {

	zval *inputs_param = NULL, *outputs_param = NULL;
	zval *inputs = NULL, *outputs = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &inputs_param, &outputs_param);

	zephir_get_arrval(inputs, inputs_param);
	zephir_get_arrval(outputs, outputs_param);


	zephir_update_property_this(this_ptr, SL("inputs"), inputs TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("outputs"), outputs TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ann_Network, calculate) {

	HashTable *_4;
	HashPosition _3;
	zend_class_entry *_1;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *activation = NULL, *response = NULL, *output = NULL, *temp = NULL, *_2, **_5, *_6 = NULL;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_arrval(data, data_param);


	ZEPHIR_CALL_METHOD(&activation, this_ptr, "activate", &_0, data);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(response);
	_1 = zend_fetch_class(SL("Ann\\Output"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(response, _1);
	if (zephir_has_constructor(response TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, response, "__construct", NULL);
		zephir_check_call_status();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("outputs"), PH_NOISY_CC);
	zephir_is_iterable(_2, &_4, &_3, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HVALUE(output, _5);
		ZEPHIR_CALL_METHOD(&_6, activation, "output", NULL, output);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&temp, response, "set", NULL, output, _6);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(response, temp);
	}
	RETURN_CCTOR(response);

}

PHP_METHOD(Ann_Network, train) {

	zend_class_entry *_3;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, *targets = NULL;
	zval *trainer, *data_param = NULL, *targets_param = NULL, *factor, *activation = NULL, *response = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &trainer, &data_param, &targets_param, &factor);

	zephir_get_arrval(data, data_param);
	zephir_get_arrval(targets, targets_param);


	if (!(zephir_is_instance_of(trainer, SL("Ann\\Trainer") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'trainer' must be an instance of 'Ann\\Trainer'", "", 0);
		return;
	}
	ZEPHIR_CALL_METHOD(&activation, this_ptr, "activate", &_0, data);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&response, this_ptr, "response", &_1, targets);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	_3 = zend_fetch_class(SL("Ann\\Trainset"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_2, _3);
	if (zephir_has_constructor(_2 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, activation, response);
		zephir_check_call_status();
	}
	ZEPHIR_RETURN_CALL_METHOD(trainer, "train", NULL, this_ptr, _2, factor);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Network, activate) {

	HashTable *_6;
	HashPosition _5;
	zend_class_entry *_3;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *data_param = NULL, *activation = NULL, *output = NULL, *_0 = NULL, *_2, *_4, **_7, *_8 = NULL;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_arrval(data, data_param);


	ZEPHIR_INIT_VAR(activation);
	object_init_ex(activation, ann_activation_ce);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "request", &_1, data);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	_3 = zend_fetch_class(SL("Ann\\Output"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(_2, _3);
	if (zephir_has_constructor(_2 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, activation, "__construct", NULL, _0, _2);
	zephir_check_call_status();
	_4 = zephir_fetch_nproperty_this(this_ptr, SL("outputs"), PH_NOISY_CC);
	zephir_is_iterable(_4, &_6, &_5, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
	  ; zephir_hash_move_forward_ex(_6, &_5)
	) {
		ZEPHIR_GET_HVALUE(output, _7);
		ZEPHIR_CALL_METHOD(&_8, output, "output", NULL, activation);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(activation, _8);
	}
	RETURN_CCTOR(activation);

}

PHP_METHOD(Ann_Network, accept) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *visitor, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &visitor);



	if (!(zephir_instance_of_ev(visitor, ann_visitor_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'visitor' must be an instance of 'Ann\\Visitor'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("inputs"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("outputs"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(visitor, "visitnetwork", NULL, this_ptr, _0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Network, request) {

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_0;
	zval *data_param = NULL, *result = NULL, *i = NULL, *value = NULL, *temp = NULL, **_3, *_4, *_5;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_arrval(data, data_param);


	ZEPHIR_INIT_VAR(result);
	_0 = zend_fetch_class(SL("Ann\\Input"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(result, _0);
	if (zephir_has_constructor(result TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, result, "__construct", NULL);
		zephir_check_call_status();
	}
	zephir_is_iterable(data, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(i, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("inputs"), PH_NOISY_CC);
		zephir_array_fetch(&_5, _4, i, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&temp, result, "set", NULL, _5, value);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(result, temp);
	}
	RETURN_CCTOR(result);

}

PHP_METHOD(Ann_Network, response) {

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_0;
	zval *data_param = NULL, *result = NULL, *i = NULL, *value = NULL, *temp = NULL, **_3, *_4, *_5;
	zval *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data_param);

	zephir_get_arrval(data, data_param);


	ZEPHIR_INIT_VAR(result);
	_0 = zend_fetch_class(SL("Ann\\Output"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(result, _0);
	if (zephir_has_constructor(result TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, result, "__construct", NULL);
		zephir_check_call_status();
	}
	zephir_is_iterable(data, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(i, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		_4 = zephir_fetch_nproperty_this(this_ptr, SL("outputs"), PH_NOISY_CC);
		zephir_array_fetch(&_5, _4, i, PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&temp, result, "set", NULL, _5, value);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(result, temp);
	}
	RETURN_CCTOR(result);

}

PHP_METHOD(Ann_Network, create) {

	zephir_nts_static zephir_fcall_cache_entry *_19 = NULL;
	zend_class_entry *_8, *_9, *_15, *_21, *_22;
	int _5, ZEPHIR_LAST_CALL_STATUS;
	zend_bool _4, _7;
	HashTable *_1, *_12;
	HashPosition _0, _11;
	zval *nodes_param = NULL, *inputs, *layer = NULL, *layers, *count = NULL, *i = NULL, *j = NULL, *branch = NULL, *function = NULL, *synapses = NULL, *neuron = NULL, **_2, *_3 = NULL, *_6 = NULL, *_10, **_13, *_14 = NULL, _16 = zval_used_for_init, _17 = zval_used_for_init, *_18 = NULL, *_20 = NULL;
	zval *nodes = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &nodes_param);

	zephir_get_arrval(nodes, nodes_param);


	ZEPHIR_INIT_VAR(inputs);
	array_init(inputs);
	ZEPHIR_INIT_VAR(layers);
	array_init(layers);
	zephir_is_iterable(nodes, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(count, _2);
		ZEPHIR_INIT_NVAR(i);
		ZVAL_LONG(i, zephir_fast_count_int(layers TSRMLS_CC));
		ZEPHIR_INIT_NVAR(_3);
		array_init(_3);
		zephir_array_update_zval(&layers, i, &_3, PH_COPY | PH_SEPARATE);
		ZEPHIR_CPY_WRT(_6, count);
		_5 = 0;
		_4 = 0;
		if (ZEPHIR_GE_LONG(_6, _5)) {
			while (1) {
				if (_4) {
					_5++;
					if (!(ZEPHIR_GE_LONG(_6, _5))) {
						break;
					}
				} else {
					_4 = 1;
				}
				ZEPHIR_INIT_NVAR(j);
				ZVAL_LONG(j, _5);
				_7 = ZEPHIR_IS_LONG(i, (zephir_fast_count_int(nodes TSRMLS_CC) - 1));
				if (_7) {
					_7 = ZEPHIR_IS_EQUAL(j, count);
				}
				if (_7) {
					continue;
				}
				ZEPHIR_INIT_NVAR(branch);
				_8 = zend_fetch_class(SL("Ann\\Peripheral"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
				object_init_ex(branch, _8);
				if (zephir_has_constructor(branch TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, branch, "__construct", NULL);
					zephir_check_call_status();
				}
				ZEPHIR_INIT_NVAR(function);
				_9 = zend_fetch_class(SL("Ann\\OutputFunction\\Sigmoid"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
				object_init_ex(function, _9);
				if (zephir_has_constructor(function TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, function, "__construct", NULL);
					zephir_check_call_status();
				}
				if (zephir_fast_count_int(nodes TSRMLS_CC) == 2) {
					ZEPHIR_INIT_NVAR(function);
					object_init_ex(function, ann_outputfunction_linear_ce);
					if (zephir_has_constructor(function TSRMLS_CC)) {
						ZEPHIR_CALL_METHOD(NULL, function, "__construct", NULL);
						zephir_check_call_status();
					}
				}
				if (ZEPHIR_IS_EQUAL(j, count)) {
					ZEPHIR_INIT_NVAR(branch);
					object_init_ex(branch, ann_bias_ce);
					if (zephir_has_constructor(branch TSRMLS_CC)) {
						ZEPHIR_CALL_METHOD(NULL, branch, "__construct", NULL);
						zephir_check_call_status();
					}
					ZEPHIR_INIT_NVAR(function);
					object_init_ex(function, ann_outputfunction_linear_ce);
					if (zephir_has_constructor(function TSRMLS_CC)) {
						ZEPHIR_CALL_METHOD(NULL, function, "__construct", NULL);
						zephir_check_call_status();
					}
				} else {
					if (ZEPHIR_IS_LONG(i, 0)) {
						ZEPHIR_INIT_NVAR(function);
						object_init_ex(function, ann_outputfunction_linear_ce);
						if (zephir_has_constructor(function TSRMLS_CC)) {
							ZEPHIR_CALL_METHOD(NULL, function, "__construct", NULL);
							zephir_check_call_status();
						}
					} else {
						ZEPHIR_INIT_NVAR(synapses);
						array_init(synapses);
						zephir_array_fetch_long(&_10, layers, (zephir_get_numberval(i) - 1), PH_NOISY | PH_READONLY TSRMLS_CC);
						zephir_is_iterable(_10, &_12, &_11, 0, 0);
						for (
						  ; zephir_hash_get_current_data_ex(_12, (void**) &_13, &_11) == SUCCESS
						  ; zephir_hash_move_forward_ex(_12, &_11)
						) {
							ZEPHIR_GET_HVALUE(neuron, _13);
							ZEPHIR_INIT_LNVAR(_14);
							_15 = zend_fetch_class(SL("Ann\\Synapse"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
							object_init_ex(_14, _15);
							if (zephir_has_constructor(_14 TSRMLS_CC)) {
								ZEPHIR_SINIT_NVAR(_16);
								ZVAL_LONG(&_16, 0);
								ZEPHIR_SINIT_NVAR(_17);
								ZVAL_LONG(&_17, 100);
								ZEPHIR_CALL_FUNCTION(&_18, "rand", &_19, &_16, &_17);
								zephir_check_call_status();
								ZEPHIR_INIT_NVAR(_20);
								ZVAL_DOUBLE(_20, (-1.0 + (zephir_get_numberval(_18) / 50.0)));
								ZEPHIR_CALL_METHOD(NULL, _14, "__construct", NULL, neuron, _20);
								zephir_check_call_status();
							}
							zephir_array_append(&synapses, _14, PH_SEPARATE);
						}
						ZEPHIR_INIT_NVAR(branch);
						_21 = zend_fetch_class(SL("Ann\\Dendrite"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
						object_init_ex(branch, _21);
						if (zephir_has_constructor(branch TSRMLS_CC)) {
							ZEPHIR_CALL_METHOD(NULL, branch, "__construct", NULL, synapses);
							zephir_check_call_status();
						}
					}
				}
				if (zephir_is_instance_of(branch, SL("Ann\\Peripheral") TSRMLS_CC)) {
					zephir_array_append(&inputs, branch, PH_SEPARATE);
				}
				ZEPHIR_INIT_NVAR(neuron);
				_22 = zend_fetch_class(SL("Ann\\Neuron"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
				object_init_ex(neuron, _22);
				if (zephir_has_constructor(neuron TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, neuron, "__construct", NULL, branch, function);
					zephir_check_call_status();
				}
				ZEPHIR_OBS_NVAR(layer);
				zephir_array_fetch(&layer, layers, i, PH_NOISY TSRMLS_CC);
				zephir_array_update_zval(&layer, j, &neuron, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&layers, i, &layer, PH_COPY | PH_SEPARATE);
			}
		}
	}
	object_init_ex(return_value, ann_network_ce);
	zephir_array_fetch_long(&_10, layers, (zephir_fast_count_int(layers TSRMLS_CC) - 1), PH_NOISY | PH_READONLY TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, inputs, _10);
	zephir_check_call_status();
	RETURN_MM();

}

