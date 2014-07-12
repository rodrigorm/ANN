
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
#include "kernel/fcall.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Ann_Bias) {

	ZEPHIR_REGISTER_CLASS(Ann, Bias, ann, bias, ann_bias_method_entry, 0);

	zend_class_implements(ann_bias_ce TSRMLS_CC, 1, ann_branch_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_Bias, output) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *activation;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);



	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(activation, "activate", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Bias, activate) {

	zval *Activation;

	zephir_fetch_params(0, 1, 0, &Activation);



	if (!(zephir_instance_of_ev(Activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'Activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	RETURN_DOUBLE(1.0);

}

PHP_METHOD(Ann_Bias, accept) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *visitor;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &visitor);



	if (!(zephir_instance_of_ev(visitor, ann_visitor_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'visitor' must be an instance of 'Ann\\Visitor'", "", 0);
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(visitor, "visitbias", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

