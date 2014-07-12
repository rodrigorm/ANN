
extern zend_class_entry *ann_outputfunction_threshold_ce;

ZEPHIR_INIT_CLASS(Ann_OutputFunction_Threshold);

PHP_METHOD(Ann_OutputFunction_Threshold, __construct);
PHP_METHOD(Ann_OutputFunction_Threshold, forward);
PHP_METHOD(Ann_OutputFunction_Threshold, derivative);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_threshold___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, threshold)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_threshold_forward, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ann_outputfunction_threshold_derivative, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ann_outputfunction_threshold_method_entry) {
	PHP_ME(Ann_OutputFunction_Threshold, __construct, arginfo_ann_outputfunction_threshold___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ann_OutputFunction_Threshold, forward, arginfo_ann_outputfunction_threshold_forward, ZEND_ACC_PUBLIC)
	PHP_ME(Ann_OutputFunction_Threshold, derivative, arginfo_ann_outputfunction_threshold_derivative, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
