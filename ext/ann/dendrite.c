
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
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/fcall.h"


ZEPHIR_INIT_CLASS(Ann_Dendrite) {

	ZEPHIR_REGISTER_CLASS(Ann, Dendrite, ann, dendrite, ann_dendrite_method_entry, 0);

	zend_declare_property_null(ann_dendrite_ce, SL("synapses"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ann_dendrite_ce TSRMLS_CC, 1, ann_branch_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_Dendrite, __construct) {

	zval *synapses_param = NULL;
	zval *synapses = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &synapses_param);

	zephir_get_arrval(synapses, synapses_param);


	zephir_update_property_this(this_ptr, SL("synapses"), synapses TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ann_Dendrite, output) {

	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	zval *activation = NULL, *synapse = NULL, *_0, **_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);

	ZEPHIR_SEPARATE_PARAM(activation);


	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("synapses"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(synapse, _3);
		ZEPHIR_CALL_METHOD(&_4, synapse, "output", NULL, activation);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(activation, _4);
	}
	ZEPHIR_RETURN_CALL_METHOD(activation, "activate", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Dendrite, activate) {

	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_2;
	HashPosition _1;
	zval *activation, *result, *synapse = NULL, *_0, **_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);



	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	ZEPHIR_INIT_VAR(result);
	ZVAL_LONG(result, 0);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("synapses"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(synapse, _3);
		ZEPHIR_CALL_METHOD(&_4, activation, "output", &_5, synapse);
		zephir_check_call_status();
		ZEPHIR_ADD_ASSIGN(result, _4);
	}
	RETURN_CCTOR(result);

}

PHP_METHOD(Ann_Dendrite, accept) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *visitor, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &visitor);



	if (!(zephir_instance_of_ev(visitor, ann_visitor_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'visitor' must be an instance of 'Ann\\Visitor'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("synapses"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(visitor, "visitdendrite", NULL, this_ptr, _0);
	zephir_check_call_status();
	RETURN_MM();

}

