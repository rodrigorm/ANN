
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


ZEPHIR_INIT_CLASS(Ann_Delta) {

	ZEPHIR_REGISTER_CLASS(Ann, Delta, ann, delta, ann_delta_method_entry, 0);

	zend_declare_property_null(ann_delta_ce, SL("synapses"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Ann_Delta, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zend_class_entry *_2;
	zend_bool _0;
	zval *synapses = NULL, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &synapses);

	if (!synapses) {
		synapses = ZEPHIR_GLOBAL(global_null);
	}


	_0 = Z_TYPE_P(synapses) != IS_NULL;
	if (_0) {
		_0 = !zephir_is_instance_of(synapses, SL("SplObjectStorage") TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'synapses' must be an instance of 'SplObjectStorage'", "", 0);
		return;
	}
	ZEPHIR_INIT_VAR(_1);
	if (zephir_is_true(synapses)) {
		ZEPHIR_CPY_WRT(_1, synapses);
	} else {
		ZEPHIR_INIT_BNVAR(_1);
		_2 = zend_fetch_class(SL("SplObjectStorage"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
		object_init_ex(_1, _2);
		if (zephir_has_constructor(_1 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL);
			zephir_check_call_status();
		}
	}
	zephir_update_property_this(this_ptr, SL("synapses"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ann_Delta, set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *synapse, *delta, *synapses = NULL, *_0, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &synapse, &delta);



	if (!(zephir_is_instance_of(synapse, SL("Ann\\Synapse") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'synapse' must be an instance of 'Ann\\Synapse'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("synapses"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	if (zephir_clone(_1, _0 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_CPY_WRT(synapses, _1);
	ZEPHIR_CALL_METHOD(&_2, synapses, "contains", NULL, synapse);
	zephir_check_call_status();
	if (zephir_is_true(_2)) {
		RETURN_THIS();
	}
	ZEPHIR_CALL_METHOD(NULL, synapses, "attach", NULL, synapse, delta);
	zephir_check_call_status();
	object_init_ex(return_value, ann_delta_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, synapses);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Delta, delta) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *synapse, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &synapse);



	if (!(zephir_is_instance_of(synapse, SL("Ann\\Synapse") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'synapse' must be an instance of 'Ann\\Synapse'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("synapses"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "offsetget", NULL, synapse);
	zephir_check_call_status();
	RETURN_MM();

}

