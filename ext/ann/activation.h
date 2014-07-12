
extern zend_class_entry *ann_activation_ce;

ZEPHIR_INIT_CLASS(Ann_Activation);

PHP_METHOD(Ann_Activation, __construct);
PHP_METHOD(Ann_Activation, activate);
PHP_METHOD(Ann_Activation, input);
PHP_METHOD(Ann_Activation, set);
PHP_METHOD(Ann_Activation, output);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_activation___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, input)
	ZEND_ARG_INFO(0, output)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_activation_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_activation_input, 0, 0, 1)
	ZEND_ARG_INFO(0, peripheral)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_activation_set, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_activation_output, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_activation_method_entry) {
	PHP_ME(Ann_Activation, __construct, arginfo_ann_activation___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_Activation, activate, arginfo_ann_activation_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Activation, input, arginfo_ann_activation_input, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Activation, set, arginfo_ann_activation_set, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Activation, output, arginfo_ann_activation_output, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
