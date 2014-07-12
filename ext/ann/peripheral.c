
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


ZEPHIR_INIT_CLASS(Ann_Peripheral) {

	ZEPHIR_REGISTER_CLASS(Ann, Peripheral, ann, peripheral, ann_peripheral_method_entry, 0);

	zend_class_implements(ann_peripheral_ce TSRMLS_CC, 1, ann_branch_ce);
	return SUCCESS;

}

PHP_METHOD(Ann_Peripheral, output) {

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

PHP_METHOD(Ann_Peripheral, activate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *activation;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &activation);



	if (!(zephir_instance_of_ev(activation, ann_activation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'activation' must be an instance of 'Ann\\Activation'", "", 0);
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(activation, "input", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Ann_Peripheral, accept) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *visitor;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &visitor);



	if (!(zephir_instance_of_ev(visitor, ann_visitor_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'visitor' must be an instance of 'Ann\\Visitor'", "", 0);
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(visitor, "visitperipheral", NULL, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

