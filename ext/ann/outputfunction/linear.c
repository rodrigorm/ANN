
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
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Ann_OutputFunction_Linear) {

	ZEPHIR_REGISTER_CLASS(Ann\\OutputFunction, Linear, ann, outputfunction_linear, ann_outputfunction_linear_method_entry, 0);

	zend_class_implements(ann_outputfunction_linear_ce TSRMLS_CC, 1, ann_outputfunction_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_OutputFunction_Linear, forward) {

	zval *value;

	zephir_fetch_params(0, 1, 0, &value);



	RETURN_CCTORW(value);

}

PHP_METHOD(Ann_OutputFunction_Linear, derivative) {

	zval *value;

	zephir_fetch_params(0, 1, 0, &value);



	RETURN_LONG(1);

}

