
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Ann_OutputFunction_Threshold) {

	ZEPHIR_REGISTER_CLASS(Ann\\OutputFunction, Threshold, ann, outputfunction_threshold, ann_outputfunction_threshold_method_entry, 0);

	zend_declare_property_null(ann_outputfunction_threshold_ce, SL("threshold"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_class_implements(ann_outputfunction_threshold_ce TSRMLS_CC, 1, ann_outputfunction_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_OutputFunction_Threshold, __construct) {

	zval *threshold = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &threshold);

	if (!threshold) {
		ZEPHIR_INIT_VAR(threshold);
		ZVAL_DOUBLE(threshold, 1.0);
	}


	zephir_update_property_this(this_ptr, SL("threshold"), threshold TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Ann_OutputFunction_Threshold, forward) {

	zval *value, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value);



	ZEPHIR_INIT_VAR(_0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("threshold"), PH_NOISY_CC);
	if (ZEPHIR_GE(value, _1)) {
		ZVAL_DOUBLE(_0, 1.0);
	} else {
		ZVAL_DOUBLE(_0, 0.0);
	}
	RETURN_CCTOR(_0);

}

PHP_METHOD(Ann_OutputFunction_Threshold, derivative) {

	zval *value;

	zephir_fetch_params(0, 1, 0, &value);



	RETURN_LONG(0);

}

