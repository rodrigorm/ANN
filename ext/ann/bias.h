
extern zend_class_entry *ann_bias_ce;

ZEPHIR_INIT_CLASS(Ann_Bias);

PHP_METHOD(Ann_Bias, output);
PHP_METHOD(Ann_Bias, activate);
PHP_METHOD(Ann_Bias, accept);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_bias_output, 0, 0, 1)
	ZEND_ARG_INFO(0, activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_bias_activate, 0, 0, 1)
	ZEND_ARG_INFO(0, Activation)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_bias_accept, 0, 0, 1)
	ZEND_ARG_INFO(0, visitor)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_bias_method_entry) {
	PHP_ME(Ann_Bias, output, arginfo_ann_bias_output, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Bias, activate, arginfo_ann_bias_activate, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_Bias, accept, arginfo_ann_bias_accept, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
