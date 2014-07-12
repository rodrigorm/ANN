
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


ZEPHIR_INIT_CLASS(Ann_Activation) {

	ZEPHIR_REGISTER_CLASS(Ann, Activation, ann, activation, ann_activation_method_entry, 0);

	zend_declare_property_null(ann_activation_ce, SL("input"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(ann_activation_ce, SL("output"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Ann_Activation, __construct) {

	zval *input, *output;

	zephir_fetch_params(0, 2, 0, &input, &output);



	if (!(zephir_is_instance_of(input, SL("Ann\\Input") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'input' must be an instance of 'Ann\\Input'", "", 0);
		return;
	}
	if (!(zephir_is_instance_of(output, SL("Ann\\Output") TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'output' must be an instance of 'Ann\\Output'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("input"), input TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("output"), output TSRMLS_CC);

}

PHP_METHOD(Ann_Activation, activate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *object, *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &object);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("output"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "contains", NULL, object);
	zephir_check_call_status();
	if (zephir_is_true(_1)) {
		RETURN_THIS();
	}
	ZEPHIR_CALL_METHOD(&_1, object, "activate", NULL, this_ptr);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "set", NULL, object, _1);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Activation, input) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *peripheral, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &peripheral);



	if (!(zephir_instance_of_ev(peripheral, ann_peripheral_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'peripheral' must be an instance of 'Ann\\Peripheral'", "", 0);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("input"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "get", NULL, peripheral);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Activation, set) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *key, *value, *_0, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key, &value);



	object_init_ex(return_value, ann_activation_ce);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("input"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("output"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_2, _1, "set", NULL, key, value);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _0, _2);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Activation, output) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *key, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("output"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "get", NULL, key);
	zephir_check_call_status();
	RETURN_MM();

}

