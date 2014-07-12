
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
#include "kernel/fcall.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Ann_Synapse) {

	ZEPHIR_REGISTER_CLASS(Ann, Synapse, ann, synapse, ann_synapse_method_entry, 0);

	zend_declare_property_null(ann_synapse_ce, SL("neuron"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_long(ann_synapse_ce, SL("weight"), 0, ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ann_synapse_ce TSRMLS_CC, 1, ann_visitee_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_Synapse, __construct) {

	zval *neuron, *weight;

	zephir_fetch_params(0, 2, 0, &neuron, &weight);



	if (!(zephir_instance_of_ev(neuron, ann_neuron_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'neuron' must be an instance of 'Ann\\Neuron'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("neuron"), neuron TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("weight"), weight TSRMLS_CC);

}

PHP_METHOD(Ann_Synapse, neuron) {


	RETURN_MEMBER(this_ptr, "neuron");

}

PHP_METHOD(Ann_Synapse, weight) {


	RETURN_MEMBER(this_ptr, "weight");

}

PHP_METHOD(Ann_Synapse, output) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *activation = NULL, *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);

	ZEPHIR_SEPARATE_PARAM(activation);


	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("neuron"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "output", NULL, activation);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(activation, _1);
	ZEPHIR_RETURN_CALL_METHOD(activation, "activate", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Synapse, activate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *activation, *_0 = NULL, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);



	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("neuron"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_0, activation, "output", NULL, _1);
	zephir_check_call_status();
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("weight"), PH_NOISY_CC);
	mul_function(return_value, _0, _2 TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Ann_Synapse, accept) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *visitor, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &visitor);



	if (!(zephir_instance_of_ev(visitor, ann_visitor_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'visitor' must be an instance of 'Ann\\Visitor'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("neuron"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("weight"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(visitor, "visitsynapse", NULL, this_ptr, _0, _1);
	zephir_check_call_status();
	RETURN_MM();

}

