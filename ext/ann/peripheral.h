
extern zend_class_entry *ann_peripheral_ce;

ZEPHIR_INIT_CLASS(Ann_Peripheral);

PHP_METHOD(Ann_Peripheral, output);
PHP_METHOD(Ann_Peripheral, activate);
PHP_METHOD(Ann_Peripheral, accept);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_peripheral_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_peripheral_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_peripheral_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_peripheral_method_entry) {
	PHP_ME(Ann_Peripheral, output, arginfo_ann_peripheral_output, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Peripheral, activate, arginfo_ann_peripheral_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Peripheral, accept, arginfo_ann_peripheral_accept, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
