
extern zend_class_entry *ann_outputfunction_linear_ce;

ZEPHIR_INIT_CLASS(Ann_OutputFunction_Linear);

PHP_METHOD(Ann_OutputFunction_Linear, forward);
PHP_METHOD(Ann_OutputFunction_Linear, derivative);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_linear_forward, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_linear_derivative, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_outputfunction_linear_method_entry) {
	PHP_ME(Ann_OutputFunction_Linear, forward, arginfo_ann_outputfunction_linear_forward, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_OutputFunction_Linear, derivative, arginfo_ann_outputfunction_linear_derivative, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
